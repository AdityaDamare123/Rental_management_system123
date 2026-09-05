/*
 * ============================================================
 *  RentalItem.h — Abstract Base Class
 * ============================================================
 *  OOP Concepts Demonstrated:
 *    - ABSTRACTION      : Pure virtual functions
 *    - ENCAPSULATION     : Private/protected data members
 *    - POLYMORPHISM      : Virtual functions for runtime binding
 *    - OPERATOR OVERLOAD : << and == operators
 *    - FRIEND FUNCTION   : operator<< as friend
 * ============================================================
 */

#ifndef RENTALITEM_H
#define RENTALITEM_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// ─── Abstract Base Class ─────────────────────────────────────
class RentalItem {
protected:
    // Encapsulation: Protected data members
    int id;
    string name;
    string description;
    double dailyRate;
    bool available;

public:
    // ── Constructor ──
    RentalItem() : id(0), name(""), description(""), dailyRate(0.0), available(true) {}

    RentalItem(int id, string name, string desc, double rate)
        : id(id), name(name), description(desc), dailyRate(rate), available(true) {}

    // ── Virtual Destructor (important for polymorphism) ──
    virtual ~RentalItem() {}

    // ══════════════════════════════════════════════════════════
    //  PURE VIRTUAL FUNCTIONS — Abstraction
    //  Subclasses MUST implement these
    // ══════════════════════════════════════════════════════════
    virtual string displayDetails() const = 0;
    virtual double calculateRent(int days) const = 0;
    virtual string getType() const = 0;
    virtual string getSubType() const = 0;
    virtual string toJSON() const = 0;

    // ══════════════════════════════════════════════════════════
    //  ENCAPSULATION — Getters and Setters
    // ══════════════════════════════════════════════════════════
    int getId() const { return id; }
    string getName() const { return name; }
    string getDescription() const { return description; }
    double getDailyRate() const { return dailyRate; }
    bool isAvailable() const { return available; }

    void setId(int newId) { id = newId; }
    void setName(const string& newName) { name = newName; }
    void setDescription(const string& desc) { description = desc; }
    void setDailyRate(double rate) {
        if (rate >= 0) dailyRate = rate;
        else cout << "Error: Rate cannot be negative!" << endl;
    }
    void setAvailable(bool status) { available = status; }

    // ══════════════════════════════════════════════════════════
    //  OPERATOR OVERLOADING
    // ══════════════════════════════════════════════════════════

    // Equality operator — compare by ID
    bool operator==(const RentalItem& other) const {
        return this->id == other.id;
    }

    // Less-than operator — compare by daily rate (for sorting)
    bool operator<(const RentalItem& other) const {
        return this->dailyRate < other.dailyRate;
    }

    // Greater-than operator
    bool operator>(const RentalItem& other) const {
        return this->dailyRate > other.dailyRate;
    }

    // ══════════════════════════════════════════════════════════
    //  FRIEND FUNCTION — operator<< for formatted output
    // ══════════════════════════════════════════════════════════
    friend ostream& operator<<(ostream& os, const RentalItem& item);
};

// Friend function definition
ostream& operator<<(ostream& os, const RentalItem& item) {
    os << "╔══════════════════════════════════════════╗" << endl;
    os << "║  ID: " << item.id << endl;
    os << "║  Name: " << item.name << endl;
    os << "║  Type: " << item.getType() << " > " << item.getSubType() << endl;
    os << "║  Rate: $" << item.dailyRate << "/day" << endl;
    os << "║  Status: " << (item.available ? "✅ Available" : "❌ Rented") << endl;
    os << "║  " << item.description << endl;
    os << "╚══════════════════════════════════════════╝" << endl;
    return os;
}

#endif // RENTALITEM_H
