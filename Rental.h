/*
 * ============================================================
 *  Rental.h — Rental Transaction Class
 * ============================================================
 *  OOP Concepts Demonstrated:
 *    - COMPOSITION : Contains User and RentalItem references
 *    - ENCAPSULATION : Private data, public interface
 *    - OPERATOR OVERLOADING : << operator
 * ============================================================
 */

#ifndef RENTAL_H
#define RENTAL_H

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

using namespace std;

// ─── Rental Status Enum ──────────────────────────────────────
enum class RentalStatus {
    ACTIVE,
    COMPLETED,
    OVERDUE,
    CANCELLED
};

// Helper function to convert status to string
string rentalStatusToString(RentalStatus status) {
    switch (status) {
        case RentalStatus::ACTIVE:    return "Active";
        case RentalStatus::COMPLETED: return "Completed";
        case RentalStatus::OVERDUE:   return "Overdue";
        case RentalStatus::CANCELLED: return "Cancelled";
        default: return "Unknown";
    }
}


// ═══════════════════════════════════════════════════════════════
//  Rental Class — Composition of User + RentalItem
// ═══════════════════════════════════════════════════════════════
class Rental {
private:
    // ── Encapsulation: Private data ──
    int rentalId;
    int userId;           // COMPOSITION: references a User
    int itemId;           // COMPOSITION: references a RentalItem
    string userName;
    string itemName;
    string itemType;
    string startDate;
    string endDate;
    int durationDays;
    double totalCost;
    double discount;
    double finalAmount;
    RentalStatus status;

public:
    // ── Constructors ──
    Rental() : rentalId(0), userId(0), itemId(0), userName(""), itemName(""),
               itemType(""), startDate(""), endDate(""), durationDays(0),
               totalCost(0), discount(0), finalAmount(0), status(RentalStatus::ACTIVE) {}

    Rental(int rId, int uId, int iId, string uName, string iName, string iType,
           string start, string end, int days, double cost, double disc)
        : rentalId(rId), userId(uId), itemId(iId), userName(uName), itemName(iName),
          itemType(iType), startDate(start), endDate(end), durationDays(days),
          totalCost(cost), discount(disc), status(RentalStatus::ACTIVE) {
        finalAmount = cost - (cost * disc);
    }

    // ══════════════════════════════════════════════════════════
    //  ENCAPSULATION — Getters
    // ══════════════════════════════════════════════════════════
    int getRentalId() const { return rentalId; }
    int getUserId() const { return userId; }
    int getItemId() const { return itemId; }
    string getUserName() const { return userName; }
    string getItemName() const { return itemName; }
    string getItemType() const { return itemType; }
    string getStartDate() const { return startDate; }
    string getEndDate() const { return endDate; }
    int getDurationDays() const { return durationDays; }
    double getTotalCost() const { return totalCost; }
    double getDiscount() const { return discount; }
    double getFinalAmount() const { return finalAmount; }
    RentalStatus getStatus() const { return status; }
    string getStatusString() const { return rentalStatusToString(status); }

    // ══════════════════════════════════════════════════════════
    //  ENCAPSULATION — Setters
    // ══════════════════════════════════════════════════════════
    void setRentalId(int id) { rentalId = id; }
    void setStatus(RentalStatus s) { status = s; }

    void completeRental() {
        status = RentalStatus::COMPLETED;
    }

    void cancelRental() {
        status = RentalStatus::CANCELLED;
    }

    void markOverdue() {
        status = RentalStatus::OVERDUE;
    }

    // ══════════════════════════════════════════════════════════
    //  Display and Serialization
    // ══════════════════════════════════════════════════════════
    string displayDetails() const {
        stringstream ss;
        ss << "📋 RENTAL #" << rentalId << endl;
        ss << "   Customer: " << userName << " (ID: " << userId << ")" << endl;
        ss << "   Item: " << itemName << " [" << itemType << "] (ID: " << itemId << ")" << endl;
        ss << "   Period: " << startDate << " to " << endDate << " (" << durationDays << " days)" << endl;
        ss << "   Cost: ₹" << totalCost << " | Discount: " << (discount * 100) << "%" << endl;
        ss << "   Final Amount: ₹" << finalAmount << endl;
        ss << "   Status: " << rentalStatusToString(status) << endl;
        return ss.str();
    }

    string toJSON() const {
        stringstream ss;
        ss << "{\"rentalId\":" << rentalId
           << ",\"userId\":" << userId << ",\"itemId\":" << itemId
           << ",\"userName\":\"" << userName << "\",\"itemName\":\"" << itemName
           << "\",\"itemType\":\"" << itemType
           << "\",\"startDate\":\"" << startDate << "\",\"endDate\":\"" << endDate
           << "\",\"durationDays\":" << durationDays
           << ",\"totalCost\":" << totalCost << ",\"discount\":" << discount
           << ",\"finalAmount\":" << finalAmount
           << ",\"status\":\"" << rentalStatusToString(status) << "\"}";
        return ss.str();
    }

    // ══════════════════════════════════════════════════════════
    //  OPERATOR OVERLOADING
    // ══════════════════════════════════════════════════════════
    bool operator==(const Rental& other) const {
        return this->rentalId == other.rentalId;
    }

    // ── Friend Function ──
    friend ostream& operator<<(ostream& os, const Rental& rental);
};

// Friend function definition
ostream& operator<<(ostream& os, const Rental& rental) {
    os << "╔═══════════════════════════════════════════╗" << endl;
    os << "║  Rental #" << rental.rentalId << " — " << rentalStatusToString(rental.status) << endl;
    os << "║  Customer: " << rental.userName << endl;
    os << "║  Item: " << rental.itemName << " [" << rental.itemType << "]" << endl;
    os << "║  Period: " << rental.startDate << " → " << rental.endDate << endl;
    os << "║  Duration: " << rental.durationDays << " days" << endl;
    os << "║  Cost: ₹" << rental.totalCost << " (Discount: " << (rental.discount * 100) << "%)" << endl;
    os << "║  Final: ₹" << rental.finalAmount << endl;
    os << "╚═══════════════════════════════════════════╝" << endl;
    return os;
}

#endif // RENTAL_H
