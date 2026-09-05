/*
 * ============================================================
 *  Vehicle.h — Vehicle Hierarchy
 * ============================================================
 *  OOP Concepts Demonstrated:
 *    - INHERITANCE        : Vehicle inherits RentalItem
 *    - MULTI-LEVEL INHERIT: Car, Bike, Truck inherit Vehicle
 *    - POLYMORPHISM       : Override virtual functions
 *    - ENCAPSULATION      : Private members with accessors
 * ============================================================
 */

#ifndef VEHICLE_H
#define VEHICLE_H

#include "RentalItem.h"

// ─── Vehicle Base Class (inherits RentalItem) ────────────────
class Vehicle : public RentalItem {
protected:
    string brand;
    string model;
    int year;
    string fuelType;      // Petrol, Diesel, Electric, Hybrid
    string registrationNo;

public:
    Vehicle() : RentalItem(), brand(""), model(""), year(0), fuelType(""), registrationNo("") {}

    Vehicle(int id, string name, string desc, double rate,
            string brand, string model, int year, string fuel, string regNo)
        : RentalItem(id, name, desc, rate),
          brand(brand), model(model), year(year), fuelType(fuel), registrationNo(regNo) {}

    virtual ~Vehicle() {}

    // ── Encapsulation: Getters ──
    string getBrand() const { return brand; }
    string getModel() const { return model; }
    int getYear() const { return year; }
    string getFuelType() const { return fuelType; }
    string getRegistrationNo() const { return registrationNo; }

    // ── Encapsulation: Setters ──
    void setBrand(const string& b) { brand = b; }
    void setModel(const string& m) { model = m; }
    void setYear(int y) { if (y > 1900) year = y; }
    void setFuelType(const string& f) { fuelType = f; }
    void setRegistrationNo(const string& r) { registrationNo = r; }

    // ── Polymorphism: Override base class ──
    string getType() const override { return "Vehicle"; }
};


// ═══════════════════════════════════════════════════════════════
//  Car — Inherits from Vehicle (Multi-level Inheritance)
// ═══════════════════════════════════════════════════════════════
class Car : public Vehicle {
private:
    int seats;
    string transmission;  // Manual, Automatic
    bool hasAC;
    string carType;       // Sedan, SUV, Hatchback, Luxury

public:
    Car() : Vehicle(), seats(4), transmission("Manual"), hasAC(true), carType("Sedan") {}

    Car(int id, string name, string desc, double rate,
        string brand, string model, int year, string fuel, string regNo,
        int seats, string trans, bool ac, string cType)
        : Vehicle(id, name, desc, rate, brand, model, year, fuel, regNo),
          seats(seats), transmission(trans), hasAC(ac), carType(cType) {}

    // ── Getters ──
    int getSeats() const { return seats; }
    string getTransmission() const { return transmission; }
    bool getHasAC() const { return hasAC; }
    string getCarType() const { return carType; }

    // ── Polymorphism: Override virtual functions ──
    string getSubType() const override { return "Car (" + carType + ")"; }

    double calculateRent(int days) const override {
        double base = dailyRate * days;
        // Luxury cars have 20% premium
        if (carType == "Luxury") base *= 1.20;
        // AC surcharge
        if (hasAC) base += 5.0 * days;
        return base;
    }

    string displayDetails() const override {
        stringstream ss;
        ss << "🚗 CAR: " << name << endl;
        ss << "   Brand: " << brand << " " << model << " (" << year << ")" << endl;
        ss << "   Type: " << carType << " | Seats: " << seats << endl;
        ss << "   Fuel: " << fuelType << " | Transmission: " << transmission << endl;
        ss << "   AC: " << (hasAC ? "Yes" : "No") << " | Reg: " << registrationNo << endl;
        ss << "   Rate: $" << dailyRate << "/day | " << (available ? "Available" : "Rented") << endl;
        return ss.str();
    }

    string toJSON() const override {
        stringstream ss;
        ss << "{\"type\":\"Car\",\"id\":" << id
           << ",\"name\":\"" << name << "\",\"description\":\"" << description
           << "\",\"dailyRate\":" << dailyRate << ",\"available\":" << (available ? "true" : "false")
           << ",\"brand\":\"" << brand << "\",\"model\":\"" << model
           << "\",\"year\":" << year << ",\"fuelType\":\"" << fuelType
           << "\",\"registrationNo\":\"" << registrationNo
           << "\",\"seats\":" << seats << ",\"transmission\":\"" << transmission
           << "\",\"hasAC\":" << (hasAC ? "true" : "false")
           << ",\"carType\":\"" << carType << "\"}";
        return ss.str();
    }
};


// ═══════════════════════════════════════════════════════════════
//  Bike — Inherits from Vehicle
// ═══════════════════════════════════════════════════════════════
class Bike : public Vehicle {
private:
    int engineCC;
    string bikeType;    // Sport, Cruiser, Commuter, Scooter
    bool hasHelmet;

public:
    Bike() : Vehicle(), engineCC(150), bikeType("Commuter"), hasHelmet(true) {}

    Bike(int id, string name, string desc, double rate,
         string brand, string model, int year, string fuel, string regNo,
         int cc, string bType, bool helmet)
        : Vehicle(id, name, desc, rate, brand, model, year, fuel, regNo),
          engineCC(cc), bikeType(bType), hasHelmet(helmet) {}

    // ── Getters ──
    int getEngineCC() const { return engineCC; }
    string getBikeType() const { return bikeType; }
    bool getHasHelmet() const { return hasHelmet; }

    // ── Polymorphism ──
    string getSubType() const override { return "Bike (" + bikeType + ")"; }

    double calculateRent(int days) const override {
        double base = dailyRate * days;
        // Sport bikes have 15% premium
        if (bikeType == "Sport") base *= 1.15;
        // Helmet included surcharge
        if (hasHelmet) base += 2.0 * days;
        return base;
    }

    string displayDetails() const override {
        stringstream ss;
        ss << "🏍️ BIKE: " << name << endl;
        ss << "   Brand: " << brand << " " << model << " (" << year << ")" << endl;
        ss << "   Type: " << bikeType << " | Engine: " << engineCC << "cc" << endl;
        ss << "   Fuel: " << fuelType << " | Helmet: " << (hasHelmet ? "Included" : "Not Included") << endl;
        ss << "   Reg: " << registrationNo << endl;
        ss << "   Rate: $" << dailyRate << "/day | " << (available ? "Available" : "Rented") << endl;
        return ss.str();
    }

    string toJSON() const override {
        stringstream ss;
        ss << "{\"type\":\"Bike\",\"id\":" << id
           << ",\"name\":\"" << name << "\",\"description\":\"" << description
           << "\",\"dailyRate\":" << dailyRate << ",\"available\":" << (available ? "true" : "false")
           << ",\"brand\":\"" << brand << "\",\"model\":\"" << model
           << "\",\"year\":" << year << ",\"fuelType\":\"" << fuelType
           << "\",\"registrationNo\":\"" << registrationNo
           << "\",\"engineCC\":" << engineCC << ",\"bikeType\":\"" << bikeType
           << "\",\"hasHelmet\":" << (hasHelmet ? "true" : "false") << "}";
        return ss.str();
    }
};


// ═══════════════════════════════════════════════════════════════
//  Truck — Inherits from Vehicle
// ═══════════════════════════════════════════════════════════════
class Truck : public Vehicle {
private:
    double loadCapacity;   // in tonnes
    int axles;
    string truckType;      // Pickup, Semi, Box, Flatbed

public:
    Truck() : Vehicle(), loadCapacity(0), axles(2), truckType("Pickup") {}

    Truck(int id, string name, string desc, double rate,
          string brand, string model, int year, string fuel, string regNo,
          double capacity, int axles, string tType)
        : Vehicle(id, name, desc, rate, brand, model, year, fuel, regNo),
          loadCapacity(capacity), axles(axles), truckType(tType) {}

    // ── Getters ──
    double getLoadCapacity() const { return loadCapacity; }
    int getAxles() const { return axles; }
    string getTruckType() const { return truckType; }

    // ── Polymorphism ──
    string getSubType() const override { return "Truck (" + truckType + ")"; }

    double calculateRent(int days) const override {
        double base = dailyRate * days;
        // Heavy-duty surcharge based on load capacity
        if (loadCapacity > 10.0) base *= 1.30;
        else if (loadCapacity > 5.0) base *= 1.15;
        return base;
    }

    string displayDetails() const override {
        stringstream ss;
        ss << "🚛 TRUCK: " << name << endl;
        ss << "   Brand: " << brand << " " << model << " (" << year << ")" << endl;
        ss << "   Type: " << truckType << " | Axles: " << axles << endl;
        ss << "   Load Capacity: " << loadCapacity << " tonnes" << endl;
        ss << "   Fuel: " << fuelType << " | Reg: " << registrationNo << endl;
        ss << "   Rate: $" << dailyRate << "/day | " << (available ? "Available" : "Rented") << endl;
        return ss.str();
    }

    string toJSON() const override {
        stringstream ss;
        ss << "{\"type\":\"Truck\",\"id\":" << id
           << ",\"name\":\"" << name << "\",\"description\":\"" << description
           << "\",\"dailyRate\":" << dailyRate << ",\"available\":" << (available ? "true" : "false")
           << ",\"brand\":\"" << brand << "\",\"model\":\"" << model
           << "\",\"year\":" << year << ",\"fuelType\":\"" << fuelType
           << "\",\"registrationNo\":\"" << registrationNo
           << "\",\"loadCapacity\":" << loadCapacity << ",\"axles\":" << axles
           << ",\"truckType\":\"" << truckType << "\"}";
        return ss.str();
    }
};

#endif // VEHICLE_H
