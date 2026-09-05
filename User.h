/*
 * ============================================================
 *  User.h — User Hierarchy
 * ============================================================
 *  OOP Concepts Demonstrated:
 *    - ABSTRACTION   : Abstract User base class
 *    - INHERITANCE   : Admin, Customer inherit from User
 *    - ENCAPSULATION : Private data with public interface
 *    - POLYMORPHISM  : Virtual getRole() method
 *    - FRIEND FUNC   : operator<< overloading
 * ============================================================
 */

#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// ─── Abstract User Base Class ────────────────────────────────
class User {
protected:
    int userId;
    string name;
    string email;
    string phone;
    string password;    // Encapsulation: sensitive data is private

public:
    User() : userId(0), name(""), email(""), phone(""), password("") {}

    User(int id, string name, string email, string phone, string pwd)
        : userId(id), name(name), email(email), phone(phone), password(pwd) {}

    virtual ~User() {}

    // ══════════════════════════════════════════════════════════
    //  PURE VIRTUAL FUNCTIONS — Abstraction
    // ══════════════════════════════════════════════════════════
    virtual string getRole() const = 0;
    virtual string displayInfo() const = 0;
    virtual string toJSON() const = 0;

    // ══════════════════════════════════════════════════════════
    //  ENCAPSULATION — Getters and Setters
    // ══════════════════════════════════════════════════════════
    int getUserId() const { return userId; }
    string getName() const { return name; }
    string getEmail() const { return email; }
    string getPhone() const { return phone; }

    void setUserId(int id) { userId = id; }
    void setName(const string& n) { name = n; }
    void setEmail(const string& e) { email = e; }
    void setPhone(const string& p) { phone = p; }

    // Password is write-only externally (Encapsulation)
    void setPassword(const string& pwd) { password = pwd; }

    // Authentication method — password is never exposed
    bool authenticate(const string& pwd) const {
        return password == pwd;
    }

    // ══════════════════════════════════════════════════════════
    //  OPERATOR OVERLOADING
    // ══════════════════════════════════════════════════════════
    bool operator==(const User& other) const {
        return this->userId == other.userId;
    }

    // ── Friend Function ──
    friend ostream& operator<<(ostream& os, const User& user);
};

// Friend function definition
ostream& operator<<(ostream& os, const User& user) {
    os << "┌──────────────────────────────────┐" << endl;
    os << "│ User ID: " << user.userId << endl;
    os << "│ Name: " << user.name << endl;
    os << "│ Role: " << user.getRole() << endl;
    os << "│ Email: " << user.email << endl;
    os << "│ Phone: " << user.phone << endl;
    os << "└──────────────────────────────────┘" << endl;
    return os;
}


// ═══════════════════════════════════════════════════════════════
//  Admin — Inherits from User
// ═══════════════════════════════════════════════════════════════
class Admin : public User {
private:
    string department;
    string accessLevel;   // Full, Limited

public:
    Admin() : User(), department(""), accessLevel("Full") {}

    Admin(int id, string name, string email, string phone, string pwd,
          string dept, string access)
        : User(id, name, email, phone, pwd),
          department(dept), accessLevel(access) {}

    // ── Getters ──
    string getDepartment() const { return department; }
    string getAccessLevel() const { return accessLevel; }

    // ── Polymorphism ──
    string getRole() const override { return "Admin"; }

    string displayInfo() const override {
        stringstream ss;
        ss << "👤 ADMIN: " << name << endl;
        ss << "   Email: " << email << " | Phone: " << phone << endl;
        ss << "   Department: " << department << " | Access: " << accessLevel << endl;
        return ss.str();
    }

    string toJSON() const override {
        stringstream ss;
        ss << "{\"role\":\"Admin\",\"userId\":" << userId
           << ",\"name\":\"" << name << "\",\"email\":\"" << email
           << "\",\"phone\":\"" << phone
           << "\",\"department\":\"" << department
           << "\",\"accessLevel\":\"" << accessLevel << "\"}";
        return ss.str();
    }
};


// ═══════════════════════════════════════════════════════════════
//  Customer — Inherits from User
// ═══════════════════════════════════════════════════════════════
class Customer : public User {
private:
    string address;
    string membershipType;  // Standard, Premium, VIP
    int totalRentals;
    double totalSpent;

public:
    Customer() : User(), address(""), membershipType("Standard"), totalRentals(0), totalSpent(0) {}

    Customer(int id, string name, string email, string phone, string pwd,
             string addr, string membership)
        : User(id, name, email, phone, pwd),
          address(addr), membershipType(membership), totalRentals(0), totalSpent(0) {}

    // ── Getters ──
    string getAddress() const { return address; }
    string getMembershipType() const { return membershipType; }
    int getTotalRentals() const { return totalRentals; }
    double getTotalSpent() const { return totalSpent; }

    // ── Setters ──
    void setAddress(const string& a) { address = a; }
    void setMembershipType(const string& m) { membershipType = m; }

    // ── Business Logic ──
    void addRental(double amount) {
        totalRentals++;
        totalSpent += amount;
        // Auto-upgrade membership
        if (totalRentals >= 20) membershipType = "VIP";
        else if (totalRentals >= 10) membershipType = "Premium";
    }

    double getDiscount() const {
        if (membershipType == "VIP") return 0.15;      // 15% discount
        else if (membershipType == "Premium") return 0.10; // 10% discount
        return 0.0;
    }

    // ── Polymorphism ──
    string getRole() const override { return "Customer"; }

    string displayInfo() const override {
        stringstream ss;
        ss << "👤 CUSTOMER: " << name << endl;
        ss << "   Email: " << email << " | Phone: " << phone << endl;
        ss << "   Address: " << address << endl;
        ss << "   Membership: " << membershipType << " | Rentals: " << totalRentals << endl;
        ss << "   Total Spent: ₹" << totalSpent << " | Discount: " << (getDiscount() * 100) << "%" << endl;
        return ss.str();
    }

    string toJSON() const override {
        stringstream ss;
        ss << "{\"role\":\"Customer\",\"userId\":" << userId
           << ",\"name\":\"" << name << "\",\"email\":\"" << email
           << "\",\"phone\":\"" << phone
           << "\",\"address\":\"" << address
           << "\",\"membershipType\":\"" << membershipType
           << "\",\"totalRentals\":" << totalRentals
           << ",\"totalSpent\":" << totalSpent << "}";
        return ss.str();
    }
};

#endif // USER_H
