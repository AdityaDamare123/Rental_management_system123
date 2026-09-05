/*
 * ============================================================
 *  main.cpp — Entry Point for Rental Management System
 * ============================================================
 *  OOP Concepts Demonstrated:
 *    - Main entry point demonstrating system functionality
 *    - Console UI interacting with RentalManager OOP system
 *    - Full lifecycle demo of OOP components
 * ============================================================
 */

#include <iostream>
#include <string>
#include <limits>
#include "RentalManager.h"

using namespace std;

void displayOOPConceptsExplanation() {
    cout << "\n============================================================\n";
    cout << "          🎓 OOP CONCEPTS DEMONSTRATED IN THIS PROJECT      \n";
    cout << "============================================================\n";
    cout << " 1. ABSTRACTION:\n";
    cout << "    - Base abstract classes: RentalItem & User with pure virtual functions.\n";
    cout << "    - Hides internal implementation details while defining standard interfaces.\n\n";
    cout << " 2. INHERITANCE:\n";
    cout << "    - RentalItem -> Vehicle, Property, Equipment\n";
    cout << "    - Vehicle -> Car, Bike, Truck (Multi-level Inheritance)\n";
    cout << "    - Property -> House, Apartment, Shop\n";
    cout << "    - Equipment -> Tool, Electronic, Furniture\n";
    cout << "    - User -> Admin, Customer\n\n";
    cout << " 3. POLYMORPHISM:\n";
    cout << "    - Virtual functions: displayDetails(), calculateRent(), toJSON()\n";
    cout << "    - Runtime binding via base class pointers (RentalItem*, User*)\n";
    cout << "    - Operator Overloading (<<, ==, <, >)\n\n";
    cout << " 4. ENCAPSULATION:\n";
    cout << "    - Protected & Private attributes with public getters/setters\n";
    cout << "    - RentalManager hides internal vector structures and file I/O\n\n";
    cout << " 5. COMPOSITION:\n";
    cout << "    - Rental class composes User and RentalItem references\n";
    cout << "    - RentalManager contains collections of objects\n\n";
    cout << " 6. TEMPLATES & FRIEND FUNCTIONS:\n";
    cout << "    - Generic template functions: searchByName(), findById(), sortByRate()\n";
    cout << "    - Friend functions: friend ostream& operator<<\n";
    cout << "============================================================\n\n";
}

void printBanner() {
    cout << "============================================================\n";
    cout << "           🏢 COMPREHENSIVE RENTAL MANAGEMENT SYSTEM       \n";
    cout << "                     (C++ OOP Demonstration)               \n";
    cout << "============================================================\n";
}

void showMenu() {
    cout << "\n---------------- MENU SELECTION ----------------\n";
    cout << " 1. 📊 View Dashboard / Statistics\n";
    cout << " 2. 📦 Display All Rental Items (Polymorphism)\n";
    cout << " 3. 🚗 Filter Items by Type (Vehicles, Properties, Equipment)\n";
    cout << " 4. 🔍 Search Items by Name (Templates)\n";
    cout << " 5. ➕ Add New Rental Item\n";
    cout << " 6. 👤 Display All Users (Inheritance)\n";
    cout << " 7. ➕ Register New User\n";
    cout << " 8. 📋 Create New Rental Transaction (Composition)\n";
    cout << " 9. 📜 View All Rentals\n";
    cout << "10. ✅ Complete / Return Rental\n";
    cout << "11. 🎓 Explain OOP Concepts Used in Code\n";
    cout << "12. 💾 Save Data to File\n";
    cout << " 0. ❌ Exit\n";
    cout << "------------------------------------------------\n";
    cout << "Enter your choice: ";
}

void handleAddItem(RentalManager& manager) {
    cout << "\n--- Add New Rental Item ---\n";
    cout << "Select Category:\n";
    cout << " 1. Car (Vehicle)\n";
    cout << " 2. Bike (Vehicle)\n";
    cout << " 3. House (Property)\n";
    cout << " 4. Apartment (Property)\n";
    cout << " 5. Tool (Equipment)\n";
    cout << " 6. Electronic (Equipment)\n";
    cout << "Choice: ";
    int cat;
    cin >> cat;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string name, desc;
    double rate;

    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Description: ";
    getline(cin, desc);
    cout << "Enter Daily Rate ($): ";
    cin >> rate;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (cat == 1) { // Car
        string brand, model, fuel, regNo, carType, trans;
        int year, seats;
        cout << "Brand: "; getline(cin, brand);
        cout << "Model: "; getline(cin, model);
        cout << "Year: "; cin >> year; cin.ignore();
        cout << "Fuel Type (Petrol/Diesel/Electric): "; getline(cin, fuel);
        cout << "Reg No: "; getline(cin, regNo);
        cout << "Seats: "; cin >> seats; cin.ignore();
        cout << "Transmission (Manual/Automatic): "; getline(cin, trans);
        cout << "Car Type (Sedan/SUV/Luxury): "; getline(cin, carType);

        manager.addItem(new Car(0, name, desc, rate, brand, model, year, fuel, regNo, seats, trans, true, carType));
    }
    else if (cat == 2) { // Bike
        string brand, model, fuel, regNo, bikeType;
        int year, cc;
        cout << "Brand: "; getline(cin, brand);
        cout << "Model: "; getline(cin, model);
        cout << "Year: "; cin >> year; cin.ignore();
        cout << "Fuel Type: "; getline(cin, fuel);
        cout << "Reg No: "; getline(cin, regNo);
        cout << "Engine CC: "; cin >> cc; cin.ignore();
        cout << "Bike Type (Sport/Cruiser/Commuter): "; getline(cin, bikeType);

        manager.addItem(new Bike(0, name, desc, rate, brand, model, year, fuel, regNo, cc, bikeType, true));
    }
    else if (cat == 3) { // House
        string addr, age;
        double area, plot;
        int rooms, floors;
        cout << "Address: "; getline(cin, addr);
        cout << "Area (sq ft): "; cin >> area; cin.ignore();
        cout << "Rooms: "; cin >> rooms; cin.ignore();
        cout << "Age: "; getline(cin, age);
        cout << "Floors: "; cin >> floors; cin.ignore();
        cout << "Plot Area: "; cin >> plot; cin.ignore();

        manager.addItem(new House(0, name, desc, rate, addr, area, rooms, true, age, floors, true, true, plot));
    }
    else if (cat == 4) { // Apartment
        string addr, age, aType;
        double area;
        int rooms, floor;
        cout << "Address: "; getline(cin, addr);
        cout << "Area (sq ft): "; cin >> area; cin.ignore();
        cout << "Rooms: "; cin >> rooms; cin.ignore();
        cout << "Age: "; getline(cin, age);
        cout << "Floor Number: "; cin >> floor; cin.ignore();
        cout << "Apartment Type (Studio/1BHK/Penthouse): "; getline(cin, aType);

        manager.addItem(new Apartment(0, name, desc, rate, addr, area, rooms, true, age, floor, true, true, aType));
    }
    else if (cat == 5) { // Tool
        string catName, cond, mfr, tType, pSource;
        double weight;
        cout << "Category: "; getline(cin, catName);
        cout << "Condition (New/Good/Fair): "; getline(cin, cond);
        cout << "Weight (kg): "; cin >> weight; cin.ignore();
        cout << "Manufacturer: "; getline(cin, mfr);
        cout << "Tool Type: "; getline(cin, tType);
        cout << "Power Source (Electric/Battery/Manual): "; getline(cin, pSource);

        manager.addItem(new Tool(0, name, desc, rate, catName, cond, weight, mfr, tType, true, pSource));
    }
    else if (cat == 6) { // Electronic
        string catName, cond, mfr, eType, specs;
        double weight;
        int warranty;
        cout << "Category: "; getline(cin, catName);
        cout << "Condition: "; getline(cin, cond);
        cout << "Weight (kg): "; cin >> weight; cin.ignore();
        cout << "Manufacturer: "; getline(cin, mfr);
        cout << "Electronic Type (Camera/Laptop/Drone): "; getline(cin, eType);
        cout << "Warranty (Months): "; cin >> warranty; cin.ignore();
        cout << "Specifications: "; getline(cin, specs);

        manager.addItem(new Electronic(0, name, desc, rate, catName, cond, weight, mfr, eType, warranty, specs));
    }
    else {
        cout << "Invalid choice.\n";
    }
}

int main() {
    printBanner();

    RentalManager manager;

    // Seed initial data
    cout << "\nInitializing system with sample data...\n";
    manager.seedSampleData();

    int choice = -1;
    while (choice != 0) {
        showMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                manager.displayStats();
                break;
            case 2:
                manager.displayAllItems();
                break;
            case 3: {
                cout << "Select Type to Filter (Vehicle, Property, Equipment): ";
                string type;
                getline(cin, type);
                manager.displayItemsByType(type);
                break;
            }
            case 4: {
                cout << "Enter Search Keyword: ";
                string query;
                getline(cin, query);
                manager.searchItems(query);
                break;
            }
            case 5:
                handleAddItem(manager);
                break;
            case 6:
                manager.displayAllUsers();
                break;
            case 7: {
                cout << "Register New User (1. Admin, 2. Customer): ";
                int uChoice;
                cin >> uChoice; cin.ignore();
                string uname, email, phone, pwd;
                cout << "Name: "; getline(cin, uname);
                cout << "Email: "; getline(cin, email);
                cout << "Phone: "; getline(cin, phone);
                cout << "Password: "; getline(cin, pwd);

                if (uChoice == 1) {
                    string dept;
                    cout << "Department: "; getline(cin, dept);
                    manager.addUser(new Admin(0, uname, email, phone, pwd, dept, "Full"));
                } else {
                    string addr;
                    cout << "Address: "; getline(cin, addr);
                    manager.addUser(new Customer(0, uname, email, phone, pwd, addr, "Standard"));
                }
                break;
            }
            case 8: {
                int uId, iId, days;
                string start, end;
                cout << "Enter User ID: "; cin >> uId;
                cout << "Enter Item ID: "; cin >> iId; cin.ignore();
                cout << "Enter Start Date (YYYY-MM-DD): "; getline(cin, start);
                cout << "Enter End Date (YYYY-MM-DD): "; getline(cin, end);
                cout << "Enter Duration (Days): "; cin >> days; cin.ignore();

                manager.createRental(uId, iId, start, end, days);
                break;
            }
            case 9:
                manager.displayAllRentals();
                break;
            case 10: {
                cout << "Enter Rental ID to Complete: ";
                int rId;
                cin >> rId; cin.ignore();
                manager.completeRental(rId);
                break;
            }
            case 11:
                displayOOPConceptsExplanation();
                break;
            case 12:
                manager.saveToFile("data_export.json");
                break;
            case 0:
                cout << "\nThank you for using the Rental Management System! Goodbye.\n";
                break;
            default:
                cout << "Invalid selection. Try again.\n";
                break;
        }
    }

    return 0;
}
