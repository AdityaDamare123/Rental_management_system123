/*
 * ============================================================
 *  RentalManager.h — Business Logic Manager
 * ============================================================
 *  OOP Concepts Demonstrated:
 *    - ENCAPSULATION : Hides internal data structures & file I/O
 *    - COMPOSITION   : Contains vectors of all entity types
 *    - TEMPLATES     : Generic search function
 *    - FILE HANDLING : Persistent data storage
 *    - POLYMORPHISM  : Works with RentalItem pointers
 * ============================================================
 */

#ifndef RENTALMANAGER_H
#define RENTALMANAGER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>

#include "RentalItem.h"
#include "Vehicle.h"
#include "Property.h"
#include "Equipment.h"
#include "User.h"
#include "Rental.h"

using namespace std;

// ══════════════════════════════════════════════════════════════
//  TEMPLATE FUNCTION — Generic search by name
//  OOP Concept: Templates (Generic Programming)
// ══════════════════════════════════════════════════════════════
template <typename T>
vector<T*> searchByName(vector<T*>& items, const string& query) {
    vector<T*> results;
    string lowerQuery = query;
    transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

    for (auto& item : items) {
        string itemName = item->getName();
        transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);
        if (itemName.find(lowerQuery) != string::npos) {
            results.push_back(item);
        }
    }
    return results;
}

// Template function to find by ID
template <typename T>
T* findById(vector<T*>& items, int id) {
    for (auto& item : items) {
        if (item->getId() == id) {
            return item;
        }
    }
    return nullptr;
}

// Template function to sort by daily rate
template <typename T>
void sortByRate(vector<T*>& items, bool ascending = true) {
    sort(items.begin(), items.end(), [ascending](T* a, T* b) {
        return ascending ? (*a < *b) : (*a > *b);
    });
}


// ═══════════════════════════════════════════════════════════════
//  RentalManager Class — Encapsulates all business logic
// ═══════════════════════════════════════════════════════════════
class RentalManager {
private:
    // ── COMPOSITION: Contains collections of all entities ──
    vector<RentalItem*> allItems;
    vector<User*> allUsers;
    vector<Rental> allRentals;

    int nextItemId;
    int nextUserId;
    int nextRentalId;

    // ── ENCAPSULATION: Private helper methods ──
    string getDataFilePath(const string& filename) const {
        return "data/" + filename;
    }

public:
    // ── Constructor ──
    RentalManager() : nextItemId(1), nextUserId(1), nextRentalId(1) {}

    // ── Destructor: Clean up dynamic memory ──
    ~RentalManager() {
        for (auto item : allItems) delete item;
        for (auto user : allUsers) delete user;
    }

    // ══════════════════════════════════════════════════════════
    //  ITEM MANAGEMENT — CRUD Operations
    // ══════════════════════════════════════════════════════════

    // Add items — Polymorphism in action (stores different types in one vector)
    void addItem(RentalItem* item) {
        item->setId(nextItemId++);
        allItems.push_back(item);
        cout << "✅ Item added: " << item->getName()
             << " [" << item->getType() << " > " << item->getSubType() << "]" << endl;
    }

    // Get all items
    vector<RentalItem*>& getItems() { return allItems; }

    // Find item by ID
    RentalItem* getItemById(int id) {
        for (auto& item : allItems) {
            if (item->getId() == id) return item;
        }
        return nullptr;
    }

    // Remove item by ID
    bool removeItem(int id) {
        for (auto it = allItems.begin(); it != allItems.end(); ++it) {
            if ((*it)->getId() == id) {
                cout << "🗑️ Removed: " << (*it)->getName() << endl;
                delete *it;
                allItems.erase(it);
                return true;
            }
        }
        cout << "❌ Item not found with ID: " << id << endl;
        return false;
    }

    // Display all items — Polymorphism: displayDetails() behaves differently for each type
    void displayAllItems() const {
        if (allItems.empty()) {
            cout << "📭 No items in the system." << endl;
            return;
        }
        cout << "\n═══════════════ ALL RENTAL ITEMS ═══════════════" << endl;
        for (const auto& item : allItems) {
            cout << *item;  // Uses overloaded << operator
        }
        cout << "Total items: " << allItems.size() << endl;
    }

    // Display items by type — Polymorphism
    void displayItemsByType(const string& type) const {
        cout << "\n═══════════════ " << type << "S ═══════════════" << endl;
        int count = 0;
        for (const auto& item : allItems) {
            if (item->getType() == type) {
                cout << item->displayDetails() << endl;
                count++;
            }
        }
        if (count == 0) cout << "No " << type << "s found." << endl;
        else cout << "Total: " << count << endl;
    }

    // Get available items count
    int getAvailableCount() const {
        int count = 0;
        for (const auto& item : allItems) {
            if (item->isAvailable()) count++;
        }
        return count;
    }

    // ══════════════════════════════════════════════════════════
    //  USER MANAGEMENT
    // ══════════════════════════════════════════════════════════

    void addUser(User* user) {
        user->setUserId(nextUserId++);
        allUsers.push_back(user);
        cout << "✅ User added: " << user->getName() << " [" << user->getRole() << "]" << endl;
    }

    vector<User*>& getUsers() { return allUsers; }

    User* getUserById(int id) {
        for (auto& user : allUsers) {
            if (user->getUserId() == id) return user;
        }
        return nullptr;
    }

    bool removeUser(int id) {
        for (auto it = allUsers.begin(); it != allUsers.end(); ++it) {
            if ((*it)->getUserId() == id) {
                cout << "🗑️ Removed user: " << (*it)->getName() << endl;
                delete *it;
                allUsers.erase(it);
                return true;
            }
        }
        return false;
    }

    void displayAllUsers() const {
        if (allUsers.empty()) {
            cout << "📭 No users in the system." << endl;
            return;
        }
        cout << "\n═══════════════ ALL USERS ═══════════════" << endl;
        for (const auto& user : allUsers) {
            cout << *user;  // Uses overloaded << operator
        }
        cout << "Total users: " << allUsers.size() << endl;
    }

    // ══════════════════════════════════════════════════════════
    //  RENTAL MANAGEMENT — Core Business Logic
    // ══════════════════════════════════════════════════════════

    bool createRental(int userId, int itemId, string startDate, string endDate, int days) {
        if (days <= 0) {
            cout << "❌ Rental duration must be at least one day!" << endl;
            return false;
        }

        User* user = getUserById(userId);
        RentalItem* item = getItemById(itemId);

        if (!user) { cout << "❌ User not found!" << endl; return false; }
        if (!item) { cout << "❌ Item not found!" << endl; return false; }
        if (!item->isAvailable()) { cout << "❌ Item is not available!" << endl; return false; }

        // Calculate cost using POLYMORPHISM — each item type calculates differently
        double cost = item->calculateRent(days);

        // Apply customer discount
        double discount = 0.0;
        Customer* customer = dynamic_cast<Customer*>(user);
        if (customer) {
            discount = customer->getDiscount();
        }

        Rental rental(nextRentalId++, userId, itemId, user->getName(),
                       item->getName(), item->getType() + " > " + item->getSubType(),
                       startDate, endDate, days, cost, discount);

        allRentals.push_back(rental);
        item->setAvailable(false);

        // Update customer stats
        if (customer) {
            customer->addRental(rental.getFinalAmount());
        }

        cout << "✅ Rental created successfully!" << endl;
        cout << rental;
        return true;
    }

    bool completeRental(int rentalId) {
        for (auto& rental : allRentals) {
            if (rental.getRentalId() == rentalId) {
                if (rental.getStatus() != RentalStatus::ACTIVE) {
                    cout << "❌ Only active rentals can be returned!" << endl;
                    return false;
                }
                rental.completeRental();
                // Make item available again
                RentalItem* item = getItemById(rental.getItemId());
                if (item) item->setAvailable(true);
                cout << "✅ Rental #" << rentalId << " completed!" << endl;
                return true;
            }
        }
        cout << "❌ Rental not found!" << endl;
        return false;
    }

    bool cancelRental(int rentalId) {
        for (auto& rental : allRentals) {
            if (rental.getRentalId() == rentalId) {
                rental.cancelRental();
                RentalItem* item = getItemById(rental.getItemId());
                if (item) item->setAvailable(true);
                cout << "✅ Rental #" << rentalId << " cancelled!" << endl;
                return true;
            }
        }
        return false;
    }

    vector<Rental>& getRentals() { return allRentals; }

    void displayAllRentals() const {
        if (allRentals.empty()) {
            cout << "📭 No rentals in the system." << endl;
            return;
        }
        cout << "\n═══════════════ ALL RENTALS ═══════════════" << endl;
        for (const auto& rental : allRentals) {
            cout << rental;
        }
        cout << "Total rentals: " << allRentals.size() << endl;
    }

    // ══════════════════════════════════════════════════════════
    //  SEARCH — Uses template functions
    // ══════════════════════════════════════════════════════════

    void searchItems(const string& query) {
        auto results = searchByName(allItems, query);
        if (results.empty()) {
            cout << "🔍 No items found matching: " << query << endl;
            return;
        }
        cout << "\n🔍 Search Results for \"" << query << "\":" << endl;
        for (auto& item : results) {
            cout << item->displayDetails() << endl;
        }
    }

    // ══════════════════════════════════════════════════════════
    //  STATISTICS & ANALYTICS
    // ══════════════════════════════════════════════════════════

    void displayStats() const {
        cout << "\n════════════════ DASHBOARD ════════════════" << endl;
        cout << "📦 Total Items: " << allItems.size() << endl;
        cout << "   ├─ Available: " << getAvailableCount() << endl;
        cout << "   └─ Rented: " << (allItems.size() - getAvailableCount()) << endl;

        // Count by type
        int vehicles = 0, properties = 0, equipment = 0;
        for (const auto& item : allItems) {
            if (item->getType() == "Vehicle") vehicles++;
            else if (item->getType() == "Property") properties++;
            else if (item->getType() == "Equipment") equipment++;
        }
        cout << "   Vehicles: " << vehicles
             << " | Properties: " << properties
             << " | Equipment: " << equipment << endl;

        cout << "👤 Total Users: " << allUsers.size() << endl;
        cout << "📋 Total Rentals: " << allRentals.size() << endl;

        // Revenue
        double totalRevenue = 0;
        int activeRentals = 0;
        for (const auto& rental : allRentals) {
            totalRevenue += rental.getFinalAmount();
            if (rental.getStatus() == RentalStatus::ACTIVE) activeRentals++;
        }
        cout << "💰 Total Revenue: ₹" << totalRevenue << endl;
        cout << "🔄 Active Rentals: " << activeRentals << endl;
        cout << "════════════════════════════════════════════" << endl;
    }

    // ══════════════════════════════════════════════════════════
    //  FILE HANDLING — Data Persistence
    //  OOP Concept: Encapsulation of I/O operations
    // ══════════════════════════════════════════════════════════

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "❌ Error: Cannot open file for writing: " << filename << endl;
            return;
        }

        // Save items
        file << "[ITEMS]" << endl;
        for (const auto& item : allItems) {
            file << item->toJSON() << endl;
        }

        // Save users
        file << "[USERS]" << endl;
        for (const auto& user : allUsers) {
            file << user->toJSON() << endl;
        }

        // Save rentals
        file << "[RENTALS]" << endl;
        for (const auto& rental : allRentals) {
            file << rental.toJSON() << endl;
        }

        file.close();
        cout << "💾 Data saved to " << filename << " successfully!" << endl;
    }

    // ══════════════════════════════════════════════════════════
    //  SEED DATA — Pre-populate with sample data
    // ══════════════════════════════════════════════════════════

    void seedSampleData() {
        // ── Vehicles ──
        addItem(new Car(0, "Tesla Model 3", "Electric sedan with autopilot", 85.0,
                        "Tesla", "Model 3", 2024, "Electric", "TS-001",
                        5, "Automatic", true, "Sedan"));
        addItem(new Car(0, "BMW X5", "Luxury SUV with premium features", 120.0,
                        "BMW", "X5", 2023, "Diesel", "BW-002",
                        7, "Automatic", true, "Luxury"));
        addItem(new Car(0, "Honda City", "Reliable city commuter", 45.0,
                        "Honda", "City", 2023, "Petrol", "HC-003",
                        5, "Manual", true, "Sedan"));
        addItem(new Bike(0, "Harley Davidson Iron 883", "Classic cruiser motorcycle", 55.0,
                         "Harley Davidson", "Iron 883", 2023, "Petrol", "HD-004",
                         883, "Cruiser", true));
        addItem(new Bike(0, "Yamaha R15", "Sport bike for thrill seekers", 35.0,
                         "Yamaha", "R15 V4", 2024, "Petrol", "YM-005",
                         155, "Sport", true));
        addItem(new Truck(0, "Ford F-150", "Heavy-duty pickup truck", 95.0,
                          "Ford", "F-150", 2023, "Diesel", "FF-006",
                          3.5, 2, "Pickup"));
        addItem(new Truck(0, "Volvo FH16", "Long-haul semi truck", 180.0,
                          "Volvo", "FH16", 2022, "Diesel", "VL-007",
                          25.0, 3, "Semi"));

        // ── Properties ──
        addItem(new House(0, "Sunset Villa", "Beautiful villa with ocean view", 200.0,
                          "123 Ocean Drive, Miami", 3500, 5, true, "1-5 years",
                          2, true, true, 5000));
        addItem(new Apartment(0, "City Center Studio", "Modern studio apartment", 65.0,
                              "456 Main St, New York", 600, 1, true, "New",
                              15, true, true, "Studio"));
        addItem(new Apartment(0, "Skyline Penthouse", "Luxury penthouse with skyline view", 350.0,
                              "789 High Rise Ave, Chicago", 2800, 4, true, "New",
                              42, true, true, "Penthouse"));
        addItem(new Shop(0, "Downtown Retail Space", "Prime retail location", 150.0,
                         "100 Commerce St, LA", 1200, 2, false, "5-10 years",
                         "Retail", true, true));

        // ── Equipment ──
        addItem(new Tool(0, "DeWalt Power Drill", "Professional-grade power drill", 15.0,
                         "Power Tools", "New", 2.5, "DeWalt",
                         "Power Tool", true, "Battery"));
        addItem(new Tool(0, "Husqvarna Chainsaw", "Gas-powered chainsaw for heavy duty", 35.0,
                         "Garden Tools", "Good", 5.5, "Husqvarna",
                         "Garden Tool", true, "Gas"));
        addItem(new Electronic(0, "Canon EOS R5", "Professional mirrorless camera", 75.0,
                               "Photography", "New", 0.7, "Canon",
                               "Camera", 24, "45MP Full Frame, 8K Video"));
        addItem(new Electronic(0, "DJI Mavic 3 Pro", "Professional drone with 4K camera", 95.0,
                               "Aerial", "New", 0.9, "DJI",
                               "Drone", 12, "4K/120fps, 43min flight time"));
        addItem(new Furniture(0, "Herman Miller Aeron", "Ergonomic office chair", 12.0,
                              "Office", "New", 20.0, "Herman Miller",
                              "Chair", "Metal", "Black"));
        addItem(new Furniture(0, "IKEA MALM Desk", "Spacious work desk", 8.0,
                              "Office", "Good", 35.0, "IKEA",
                              "Desk", "Wood", "Oak"));

        // ── Users ──
        addUser(new Admin(0, "John Admin", "admin@rentalsys.com", "+1-555-0100", "admin123",
                          "Management", "Full"));
        addUser(new Customer(0, "Alice Johnson", "alice@email.com", "+1-555-0201", "pass123",
                             "123 Main St, New York", "Standard"));
        addUser(new Customer(0, "Bob Smith", "bob@email.com", "+1-555-0202", "pass456",
                             "456 Oak Ave, Chicago", "Premium"));
        addUser(new Customer(0, "Carol Davis", "carol@email.com", "+1-555-0203", "pass789",
                             "789 Pine Rd, LA", "VIP"));

        // ── Sample Rentals ──
        createRental(2, 1, "2024-01-15", "2024-01-20", 5);
        createRental(3, 5, "2024-01-18", "2024-01-25", 7);
        createRental(4, 15, "2024-02-01", "2024-02-10", 9);

        cout << "\n🌱 Sample data loaded successfully!\n" << endl;
    }
};

#endif // RENTALMANAGER_H
