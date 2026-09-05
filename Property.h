/*
 * ============================================================
 *  Property.h — Property Hierarchy
 * ============================================================
 *  OOP Concepts Demonstrated:
 *    - INHERITANCE        : Property inherits RentalItem
 *    - MULTI-LEVEL INHERIT: House, Apartment, Shop inherit Property
 *    - POLYMORPHISM       : Override virtual functions
 *    - ENCAPSULATION      : Private members with accessors
 * ============================================================
 */

#ifndef PROPERTY_H
#define PROPERTY_H

#include "RentalItem.h"

// ─── Property Base Class (inherits RentalItem) ──────────────
class Property : public RentalItem {
protected:
    string address;
    double areaSqFt;
    int rooms;
    bool furnished;
    string propertyAge;   // New, 1-5 years, 5-10 years, 10+ years

public:
    Property() : RentalItem(), address(""), areaSqFt(0), rooms(0), furnished(false), propertyAge("New") {}

    Property(int id, string name, string desc, double rate,
             string addr, double area, int rooms, bool furnished, string age)
        : RentalItem(id, name, desc, rate),
          address(addr), areaSqFt(area), rooms(rooms), furnished(furnished), propertyAge(age) {}

    virtual ~Property() {}

    // ── Encapsulation: Getters ──
    string getAddress() const { return address; }
    double getAreaSqFt() const { return areaSqFt; }
    int getRooms() const { return rooms; }
    bool isFurnished() const { return furnished; }
    string getPropertyAge() const { return propertyAge; }

    // ── Encapsulation: Setters ──
    void setAddress(const string& a) { address = a; }
    void setAreaSqFt(double a) { if (a > 0) areaSqFt = a; }
    void setRooms(int r) { if (r >= 0) rooms = r; }
    void setFurnished(bool f) { furnished = f; }
    void setPropertyAge(const string& a) { propertyAge = a; }

    // ── Polymorphism ──
    string getType() const override { return "Property"; }
};


// ═══════════════════════════════════════════════════════════════
//  House — Inherits from Property
// ═══════════════════════════════════════════════════════════════
class House : public Property {
private:
    int floors;
    bool hasGarden;
    bool hasGarage;
    double plotArea;

public:
    House() : Property(), floors(1), hasGarden(false), hasGarage(false), plotArea(0) {}

    House(int id, string name, string desc, double rate,
          string addr, double area, int rooms, bool furnished, string age,
          int floors, bool garden, bool garage, double plotArea)
        : Property(id, name, desc, rate, addr, area, rooms, furnished, age),
          floors(floors), hasGarden(garden), hasGarage(garage), plotArea(plotArea) {}

    // ── Getters ──
    int getFloors() const { return floors; }
    bool getHasGarden() const { return hasGarden; }
    bool getHasGarage() const { return hasGarage; }
    double getPlotArea() const { return plotArea; }

    // ── Polymorphism ──
    string getSubType() const override { return "House"; }

    double calculateRent(int days) const override {
        double base = dailyRate * days;
        // Furnished premium
        if (furnished) base *= 1.25;
        // Garden and garage extras
        if (hasGarden) base += 10.0 * days;
        if (hasGarage) base += 8.0 * days;
        return base;
    }

    string displayDetails() const override {
        stringstream ss;
        ss << "🏠 HOUSE: " << name << endl;
        ss << "   Address: " << address << endl;
        ss << "   Area: " << areaSqFt << " sq.ft | Plot: " << plotArea << " sq.ft" << endl;
        ss << "   Rooms: " << rooms << " | Floors: " << floors << endl;
        ss << "   Furnished: " << (furnished ? "Yes" : "No") << " | Age: " << propertyAge << endl;
        ss << "   Garden: " << (hasGarden ? "Yes" : "No") << " | Garage: " << (hasGarage ? "Yes" : "No") << endl;
        ss << "   Rate: ₹" << dailyRate << "/day | " << (available ? "Available" : "Rented") << endl;
        return ss.str();
    }

    string toJSON() const override {
        stringstream ss;
        ss << "{\"type\":\"House\",\"id\":" << id
           << ",\"name\":\"" << name << "\",\"description\":\"" << description
           << "\",\"dailyRate\":" << dailyRate << ",\"available\":" << (available ? "true" : "false")
           << ",\"address\":\"" << address << "\",\"areaSqFt\":" << areaSqFt
           << ",\"rooms\":" << rooms << ",\"furnished\":" << (furnished ? "true" : "false")
           << ",\"propertyAge\":\"" << propertyAge
           << "\",\"floors\":" << floors << ",\"hasGarden\":" << (hasGarden ? "true" : "false")
           << ",\"hasGarage\":" << (hasGarage ? "true" : "false")
           << ",\"plotArea\":" << plotArea << "}";
        return ss.str();
    }
};


// ═══════════════════════════════════════════════════════════════
//  Apartment — Inherits from Property
// ═══════════════════════════════════════════════════════════════
class Apartment : public Property {
private:
    int floor;
    bool hasElevator;
    bool hasBalcony;
    string apartmentType;  // Studio, 1BHK, 2BHK, 3BHK, Penthouse

public:
    Apartment() : Property(), floor(0), hasElevator(false), hasBalcony(false), apartmentType("1BHK") {}

    Apartment(int id, string name, string desc, double rate,
              string addr, double area, int rooms, bool furnished, string age,
              int floor, bool elevator, bool balcony, string aType)
        : Property(id, name, desc, rate, addr, area, rooms, furnished, age),
          floor(floor), hasElevator(elevator), hasBalcony(balcony), apartmentType(aType) {}

    // ── Getters ──
    int getFloor() const { return floor; }
    bool getHasElevator() const { return hasElevator; }
    bool getHasBalcony() const { return hasBalcony; }
    string getApartmentType() const { return apartmentType; }

    // ── Polymorphism ──
    string getSubType() const override { return "Apartment (" + apartmentType + ")"; }

    double calculateRent(int days) const override {
        double base = dailyRate * days;
        // Furnished premium
        if (furnished) base *= 1.20;
        // Penthouse premium
        if (apartmentType == "Penthouse") base *= 1.40;
        // Balcony extra
        if (hasBalcony) base += 5.0 * days;
        return base;
    }

    string displayDetails() const override {
        stringstream ss;
        ss << "🏢 APARTMENT: " << name << endl;
        ss << "   Address: " << address << " (Floor " << floor << ")" << endl;
        ss << "   Type: " << apartmentType << " | Area: " << areaSqFt << " sq.ft" << endl;
        ss << "   Rooms: " << rooms << " | Furnished: " << (furnished ? "Yes" : "No") << endl;
        ss << "   Elevator: " << (hasElevator ? "Yes" : "No") << " | Balcony: " << (hasBalcony ? "Yes" : "No") << endl;
        ss << "   Age: " << propertyAge << endl;
        ss << "   Rate: ₹" << dailyRate << "/day | " << (available ? "Available" : "Rented") << endl;
        return ss.str();
    }

    string toJSON() const override {
        stringstream ss;
        ss << "{\"type\":\"Apartment\",\"id\":" << id
           << ",\"name\":\"" << name << "\",\"description\":\"" << description
           << "\",\"dailyRate\":" << dailyRate << ",\"available\":" << (available ? "true" : "false")
           << ",\"address\":\"" << address << "\",\"areaSqFt\":" << areaSqFt
           << ",\"rooms\":" << rooms << ",\"furnished\":" << (furnished ? "true" : "false")
           << ",\"propertyAge\":\"" << propertyAge
           << "\",\"floor\":" << floor << ",\"hasElevator\":" << (hasElevator ? "true" : "false")
           << ",\"hasBalcony\":" << (hasBalcony ? "true" : "false")
           << ",\"apartmentType\":\"" << apartmentType << "\"}";
        return ss.str();
    }
};


// ═══════════════════════════════════════════════════════════════
//  Shop — Inherits from Property
// ═══════════════════════════════════════════════════════════════
class Shop : public Property {
private:
    string shopType;       // Retail, Restaurant, Office, Warehouse
    bool hasParking;
    bool hasStorage;

public:
    Shop() : Property(), shopType("Retail"), hasParking(false), hasStorage(false) {}

    Shop(int id, string name, string desc, double rate,
         string addr, double area, int rooms, bool furnished, string age,
         string sType, bool parking, bool storage)
        : Property(id, name, desc, rate, addr, area, rooms, furnished, age),
          shopType(sType), hasParking(parking), hasStorage(storage) {}

    // ── Getters ──
    string getShopType() const { return shopType; }
    bool getHasParking() const { return hasParking; }
    bool getHasStorage() const { return hasStorage; }

    // ── Polymorphism ──
    string getSubType() const override { return "Shop (" + shopType + ")"; }

    double calculateRent(int days) const override {
        double base = dailyRate * days;
        // Commercial premium
        if (shopType == "Restaurant") base *= 1.15;
        else if (shopType == "Warehouse") base *= 1.10;
        // Parking extra
        if (hasParking) base += 15.0 * days;
        return base;
    }

    string displayDetails() const override {
        stringstream ss;
        ss << "🏪 SHOP: " << name << endl;
        ss << "   Address: " << address << endl;
        ss << "   Type: " << shopType << " | Area: " << areaSqFt << " sq.ft" << endl;
        ss << "   Rooms: " << rooms << " | Furnished: " << (furnished ? "Yes" : "No") << endl;
        ss << "   Parking: " << (hasParking ? "Yes" : "No") << " | Storage: " << (hasStorage ? "Yes" : "No") << endl;
        ss << "   Age: " << propertyAge << endl;
        ss << "   Rate: ₹" << dailyRate << "/day | " << (available ? "Available" : "Rented") << endl;
        return ss.str();
    }

    string toJSON() const override {
        stringstream ss;
        ss << "{\"type\":\"Shop\",\"id\":" << id
           << ",\"name\":\"" << name << "\",\"description\":\"" << description
           << "\",\"dailyRate\":" << dailyRate << ",\"available\":" << (available ? "true" : "false")
           << ",\"address\":\"" << address << "\",\"areaSqFt\":" << areaSqFt
           << ",\"rooms\":" << rooms << ",\"furnished\":" << (furnished ? "true" : "false")
           << ",\"propertyAge\":\"" << propertyAge
           << "\",\"shopType\":\"" << shopType
           << "\",\"hasParking\":" << (hasParking ? "true" : "false")
           << ",\"hasStorage\":" << (hasStorage ? "true" : "false") << "}";
        return ss.str();
    }
};

#endif // PROPERTY_H
