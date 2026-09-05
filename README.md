# 🏢 Rental Management System (C++ & Web UI)

A comprehensive Object-Oriented Programming (OOP) project demonstrating all core OOP principles in **C++** with an interactive **Web UI Dashboard**.

---

## 🌟 Key Features

- **Multi-Category Management**: Manage Rentals for **Vehicles** (Cars, Bikes, Trucks), **Properties** (Houses, Apartments, Shops), and **Equipment** (Tools, Electronics, Furniture).
- **OOP Architecture**: Demonstrates Abstraction, Inheritance, Polymorphism, Encapsulation, Composition, Templates, Operator Overloading, and Friend Functions.
- **Dual Interface**:
  - 🖥️ **Interactive C++ Terminal Interface**
  - 🌐 **Modern Dark Glassmorphism Web UI**
- **Persistent Web State**: Browser changes to items, users, and rentals are stored in `localStorage` and restored with their JavaScript class behavior after reload.
- **Validated Rentals**: The web UI requires an end date after the start date, and the C++ manager rejects zero-day rentals and repeated returns.

---

## 🎓 Object-Oriented Programming (OOP) Concepts

| Concept | Implementation Details |
|---|---|
| **Abstraction** | Pure virtual functions in `RentalItem` & `User` base classes. |
| **Inheritance** | Base `RentalItem` → `Vehicle`, `Property`, `Equipment` → Subclasses (`Car`, `Bike`, `Truck`, etc.). |
| **Polymorphism** | Dynamic virtual function overrides (`calculateRent()`, `displayDetails()`, `toJSON()`). |
| **Encapsulation** | Protected/private member variables with strict getter/setter interfaces. |
| **Composition** | `Rental` class composes `User` and `RentalItem` relationships. |
| **Templates** | Generic template search and sorting utilities (`searchByName<T>()`). |
| **Operator Overloading** | Overloaded `operator<<`, `operator==`, and comparison operators (`<`, `>`). |
| **Friend Functions** | `friend ostream& operator<<` for formatted output streams. |

---

## 🚀 Getting Started

### 1. Running the C++ Console Program

Ensure you have a C++ compiler installed (GCC / g++ / MSVC).

```powershell
# Compile the project
g++ -std=c++17 main.cpp -o rental_system.exe

# Run the application
.\rental_system.exe
```

### 2. Running the Web UI

Open `web/index.html` in any web browser, or host it locally:

```powershell
cd web
python -m http.server 8080
```
Then visit `http://localhost:8080` in your web browser.

The web dashboard seeds sample data on first load. After that, new items, users, rentals, and returned items persist in the browser automatically.

---

## 📁 Project Structure

```
.
├── RentalItem.h          # Abstract Base Class
├── Vehicle.h             # Vehicle Hierarchy (Car, Bike, Truck)
├── Property.h            # Property Hierarchy (House, Apartment, Shop)
├── Equipment.h           # Equipment Hierarchy (Tool, Electronic, Furniture)
├── User.h                # User Hierarchy (Admin, Customer)
├── Rental.h              # Rental Composition Class
├── RentalManager.h       # Encapsulated Business Logic & Templates
├── main.cpp              # Entry Point & CLI Interface
└── web/                  # Web Dashboard Application
    ├── index.html        # HTML Dashboard Layout
    ├── style.css         # Dark Glassmorphism Design
    └── app.js            # JavaScript OOP Logic & Interactivity
```
