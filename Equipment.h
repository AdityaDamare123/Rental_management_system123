/*
 * ============================================================
 *  Equipment.h — Equipment Hierarchy
 * ============================================================
 *  OOP Concepts Demonstrated:
 *    - INHERITANCE        : Equipment inherits RentalItem
 *    - MULTI-LEVEL INHERIT: Tool, Electronic, Furniture inherit Equipment
 *    - POLYMORPHISM       : Override virtual functions
 *    - ENCAPSULATION      : Private members with accessors
 * ============================================================
 */

#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "RentalItem.h"

// ─── Equipment Base Class (inherits RentalItem) ─────────────
class Equipment : public RentalItem {
protected:
    string category;
    string condition;     // New, Good, Fair, Poor
    double weight;        // in kg
    string manufacturer;

public:
    Equipment() : RentalItem(), category(""), condition("Good"), weight(0), manufacturer("") {}

    Equipment(int id, string name, string desc, double rate,
              string cat, string cond, double wt, string mfr)
        : RentalItem(id, name, desc, rate),
          category(cat), condition(cond), weight(wt), manufacturer(mfr) {}

    virtual ~Equipment() {}

    // ── Encapsulation: Getters ──
    string getCategory() const { return category; }
    string getCondition() const { return condition; }
    double getWeight() const { return weight; }
    string getManufacturer() const { return manufacturer; }

    // ── Encapsulation: Setters ──
    void setCategory(const string& c) { category = c; }
    void setCondition(const string& c) { condition = c; }
    void setWeight(double w) { if (w >= 0) weight = w; }
    void setManufacturer(const string& m) { manufacturer = m; }

    // ── Polymorphism ──
    string getType() const override { return "Equipment"; }
};


// ═══════════════════════════════════════════════════════════════
//  Tool — Inherits from Equipment
// ═══════════════════════════════════════════════════════════════
class Tool : public Equipment {
private:
    string toolType;       // Power Tool, Hand Tool, Garden Tool, Construction
    bool requiresPower;
    string powerSource;    // Electric, Battery, Manual, Gas

public:
    Tool() : Equipment(), toolType("Hand Tool"), requiresPower(false), powerSource("Manual") {}

    Tool(int id, string name, string desc, double rate,
         string cat, string cond, double wt, string mfr,
         string tType, bool power, string pSource)
        : Equipment(id, name, desc, rate, cat, cond, wt, mfr),
          toolType(tType), requiresPower(power), powerSource(pSource) {}

    // ── Getters ──
    string getToolType() const { return toolType; }
    bool getRequiresPower() const { return requiresPower; }
    string getPowerSource() const { return powerSource; }

    // ── Polymorphism ──
    string getSubType() const override { return "Tool (" + toolType + ")"; }

    double calculateRent(int days) const override {
        double base = dailyRate * days;
        // Power tools cost more
        if (requiresPower) base *= 1.15;
        // Condition discount/premium
        if (condition == "New") base *= 1.10;
        else if (condition == "Poor") base *= 0.80;
        return base;
    }

    string displayDetails() const override {
        stringstream ss;
        ss << "🔧 TOOL: " << name << endl;
        ss << "   Type: " << toolType << " | Manufacturer: " << manufacturer << endl;
        ss << "   Condition: " << condition << " | Weight: " << weight << " kg" << endl;
        ss << "   Power: " << (requiresPower ? powerSource : "No power needed") << endl;
        ss << "   Rate: ₹" << dailyRate << "/day | " << (available ? "Available" : "Rented") << endl;
        return ss.str();
    }

    string toJSON() const override {
        stringstream ss;
        ss << "{\"type\":\"Tool\",\"id\":" << id
           << ",\"name\":\"" << name << "\",\"description\":\"" << description
           << "\",\"dailyRate\":" << dailyRate << ",\"available\":" << (available ? "true" : "false")
           << ",\"category\":\"" << category << "\",\"condition\":\"" << condition
           << "\",\"weight\":" << weight << ",\"manufacturer\":\"" << manufacturer
           << "\",\"toolType\":\"" << toolType
           << "\",\"requiresPower\":" << (requiresPower ? "true" : "false")
           << ",\"powerSource\":\"" << powerSource << "\"}";
        return ss.str();
    }
};


// ═══════════════════════════════════════════════════════════════
//  Electronic — Inherits from Equipment
// ═══════════════════════════════════════════════════════════════
class Electronic : public Equipment {
private:
    string electronicType;  // Laptop, Camera, Projector, Sound System, Drone
    int warrantyMonths;
    string specifications;

public:
    Electronic() : Equipment(), electronicType("Laptop"), warrantyMonths(0), specifications("") {}

    Electronic(int id, string name, string desc, double rate,
               string cat, string cond, double wt, string mfr,
               string eType, int warranty, string specs)
        : Equipment(id, name, desc, rate, cat, cond, wt, mfr),
          electronicType(eType), warrantyMonths(warranty), specifications(specs) {}

    // ── Getters ──
    string getElectronicType() const { return electronicType; }
    int getWarrantyMonths() const { return warrantyMonths; }
    string getSpecifications() const { return specifications; }

    // ── Polymorphism ──
    string getSubType() const override { return "Electronic (" + electronicType + ")"; }

    double calculateRent(int days) const override {
        double base = dailyRate * days;
        // High-value electronics insurance surcharge
        if (electronicType == "Drone" || electronicType == "Camera") base *= 1.20;
        // Warranty discount
        if (warrantyMonths > 12) base *= 0.95;
        // Condition factor
        if (condition == "New") base *= 1.15;
        return base;
    }

    string displayDetails() const override {
        stringstream ss;
        ss << "💻 ELECTRONIC: " << name << endl;
        ss << "   Type: " << electronicType << " | Manufacturer: " << manufacturer << endl;
        ss << "   Condition: " << condition << " | Weight: " << weight << " kg" << endl;
        ss << "   Warranty: " << warrantyMonths << " months" << endl;
        ss << "   Specs: " << specifications << endl;
        ss << "   Rate: ₹" << dailyRate << "/day | " << (available ? "Available" : "Rented") << endl;
        return ss.str();
    }

    string toJSON() const override {
        stringstream ss;
        ss << "{\"type\":\"Electronic\",\"id\":" << id
           << ",\"name\":\"" << name << "\",\"description\":\"" << description
           << "\",\"dailyRate\":" << dailyRate << ",\"available\":" << (available ? "true" : "false")
           << ",\"category\":\"" << category << "\",\"condition\":\"" << condition
           << "\",\"weight\":" << weight << ",\"manufacturer\":\"" << manufacturer
           << "\",\"electronicType\":\"" << electronicType
           << "\",\"warrantyMonths\":" << warrantyMonths
           << ",\"specifications\":\"" << specifications << "\"}";
        return ss.str();
    }
};


// ═══════════════════════════════════════════════════════════════
//  Furniture — Inherits from Equipment
// ═══════════════════════════════════════════════════════════════
class Furniture : public Equipment {
private:
    string furnitureType;   // Chair, Table, Sofa, Bed, Desk, Cabinet
    string material;        // Wood, Metal, Plastic, Fabric
    string color;

public:
    Furniture() : Equipment(), furnitureType("Chair"), material("Wood"), color("Brown") {}

    Furniture(int id, string name, string desc, double rate,
              string cat, string cond, double wt, string mfr,
              string fType, string mat, string clr)
        : Equipment(id, name, desc, rate, cat, cond, wt, mfr),
          furnitureType(fType), material(mat), color(clr) {}

    // ── Getters ──
    string getFurnitureType() const { return furnitureType; }
    string getMaterial() const { return material; }
    string getColor() const { return color; }

    // ── Polymorphism ──
    string getSubType() const override { return "Furniture (" + furnitureType + ")"; }

    double calculateRent(int days) const override {
        double base = dailyRate * days;
        // Premium material surcharge
        if (material == "Wood") base *= 1.10;
        // Condition factor
        if (condition == "New") base *= 1.15;
        else if (condition == "Poor") base *= 0.75;
        return base;
    }

    string displayDetails() const override {
        stringstream ss;
        ss << "🪑 FURNITURE: " << name << endl;
        ss << "   Type: " << furnitureType << " | Material: " << material << endl;
        ss << "   Color: " << color << " | Manufacturer: " << manufacturer << endl;
        ss << "   Condition: " << condition << " | Weight: " << weight << " kg" << endl;
        ss << "   Rate: ₹" << dailyRate << "/day | " << (available ? "Available" : "Rented") << endl;
        return ss.str();
    }

    string toJSON() const override {
        stringstream ss;
        ss << "{\"type\":\"Furniture\",\"id\":" << id
           << ",\"name\":\"" << name << "\",\"description\":\"" << description
           << "\",\"dailyRate\":" << dailyRate << ",\"available\":" << (available ? "true" : "false")
           << ",\"category\":\"" << category << "\",\"condition\":\"" << condition
           << "\",\"weight\":" << weight << ",\"manufacturer\":\"" << manufacturer
           << "\",\"furnitureType\":\"" << furnitureType
           << "\",\"material\":\"" << material
           << "\",\"color\":\"" << color << "\"}";
        return ss.str();
    }
};

#endif // EQUIPMENT_H
