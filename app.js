/*
 * ============================================================
 *  app.js — JavaScript OOP & Dashboard Application Logic
 * ============================================================
 *  Mirrors C++ OOP structure in JavaScript ES6 Classes:
 *    - Abstract RentalItem base class
 *    - Vehicle -> Car, Bike, Truck
 *    - Property -> House, Apartment, Shop
 *    - Equipment -> Tool, Electronic, Furniture
 *    - User -> Admin, Customer
 *    - Rental composition & Manager
 * ============================================================
 */

// ── OOP Base Class: RentalItem ────────────────────────────────
class JS_RentalItem {
    constructor(id, name, description, dailyRate, category, available = true) {
        if (this.constructor === JS_RentalItem) {
            throw new Error("Abstract class RentalItem cannot be instantiated directly.");
        }
        this.id = id;
        this.name = name;
        this.description = description;
        this.dailyRate = parseFloat(dailyRate);
        this.category = category;
        this.available = available;
    }

    // Abstract methods
    calculateRent(days) { throw new Error("Method calculateRent() must be implemented."); }
    getSubType() { throw new Error("Method getSubType() must be implemented."); }
}

// ── Vehicle Hierarchy ─────────────────────────────────────────
class JS_Vehicle extends JS_RentalItem {
    constructor(id, name, desc, rate, brand, model, year, fuel, regNo, available = true) {
        super(id, name, desc, rate, "Vehicle", available);
        this.brand = brand;
        this.model = model;
        this.year = year;
        this.fuelType = fuel;
        this.registrationNo = regNo;
    }
}

class JS_Car extends JS_Vehicle {
    constructor(id, name, desc, rate, brand, model, year, fuel, regNo, seats, trans, ac, carType, available = true) {
        super(id, name, desc, rate, brand, model, year, fuel, regNo, available);
        this.seats = seats;
        this.transmission = trans;
        this.hasAC = ac;
        this.carType = carType;
    }
    getSubType() { return `Car (${this.carType})`; }
    calculateRent(days) {
        let base = this.dailyRate * days;
        if (this.carType === "Luxury") base *= 1.20;
        if (this.hasAC) base += 5 * days;
        return base;
    }
}

class JS_Bike extends JS_Vehicle {
    constructor(id, name, desc, rate, brand, model, year, fuel, regNo, cc, bikeType, helmet, available = true) {
        super(id, name, desc, rate, brand, model, year, fuel, regNo, available);
        this.engineCC = cc;
        this.bikeType = bikeType;
        this.hasHelmet = helmet;
    }
    getSubType() { return `Bike (${this.bikeType})`; }
    calculateRent(days) {
        let base = this.dailyRate * days;
        if (this.bikeType === "Sport") base *= 1.15;
        if (this.hasHelmet) base += 2 * days;
        return base;
    }
}

class JS_Truck extends JS_Vehicle {
    constructor(id, name, desc, rate, brand, model, year, fuel, regNo, capacity, axles, truckType, available = true) {
        super(id, name, desc, rate, brand, model, year, fuel, regNo, available);
        this.loadCapacity = capacity;
        this.axles = axles;
        this.truckType = truckType;
    }
    getSubType() { return `Truck (${this.truckType})`; }
    calculateRent(days) {
        let base = this.dailyRate * days;
        if (this.loadCapacity > 10) base *= 1.30;
        return base;
    }
}

// ── Property Hierarchy ────────────────────────────────────────
class JS_Property extends JS_RentalItem {
    constructor(id, name, desc, rate, address, area, rooms, furnished, age, available = true) {
        super(id, name, desc, rate, "Property", available);
        this.address = address;
        this.areaSqFt = area;
        this.rooms = rooms;
        this.furnished = furnished;
        this.propertyAge = age;
    }
}

class JS_House extends JS_Property {
    constructor(id, name, desc, rate, addr, area, rooms, furnished, age, floors, garden, garage, plotArea, available = true) {
        super(id, name, desc, rate, addr, area, rooms, furnished, age, available);
        this.floors = floors;
        this.hasGarden = garden;
        this.hasGarage = garage;
        this.plotArea = plotArea;
    }
    getSubType() { return "House"; }
    calculateRent(days) {
        let base = this.dailyRate * days;
        if (this.furnished) base *= 1.25;
        if (this.hasGarden) base += 10 * days;
        return base;
    }
}

class JS_Apartment extends JS_Property {
    constructor(id, name, desc, rate, addr, area, rooms, furnished, age, floor, elevator, balcony, aptType, available = true) {
        super(id, name, desc, rate, addr, area, rooms, furnished, age, available);
        this.floor = floor;
        this.hasElevator = elevator;
        this.hasBalcony = balcony;
        this.apartmentType = aptType;
    }
    getSubType() { return `Apartment (${this.apartmentType})`; }
    calculateRent(days) {
        let base = this.dailyRate * days;
        if (this.apartmentType === "Penthouse") base *= 1.40;
        if (this.furnished) base *= 1.20;
        return base;
    }
}

class JS_Shop extends JS_Property {
    constructor(id, name, desc, rate, addr, area, rooms, furnished, age, shopType, parking, storage, available = true) {
        super(id, name, desc, rate, addr, area, rooms, furnished, age, available);
        this.shopType = shopType;
        this.hasParking = parking;
        this.hasStorage = storage;
    }
    getSubType() { return `Shop (${this.shopType})`; }
    calculateRent(days) {
        let base = this.dailyRate * days;
        if (this.shopType === "Restaurant") base *= 1.15;
        return base;
    }
}

// ── Equipment Hierarchy ───────────────────────────────────────
class JS_Equipment extends JS_RentalItem {
    constructor(id, name, desc, rate, cat, cond, weight, mfr, available = true) {
        super(id, name, desc, rate, "Equipment", available);
        this.equipmentCat = cat;
        this.condition = cond;
        this.weight = weight;
        this.manufacturer = mfr;
    }
}

class JS_Tool extends JS_Equipment {
    constructor(id, name, desc, rate, cat, cond, wt, mfr, tType, power, pSource, available = true) {
        super(id, name, desc, rate, cat, cond, wt, mfr, available);
        this.toolType = tType;
        this.requiresPower = power;
        this.powerSource = pSource;
    }
    getSubType() { return `Tool (${this.toolType})`; }
    calculateRent(days) {
        let base = this.dailyRate * days;
        if (this.requiresPower) base *= 1.15;
        return base;
    }
}

class JS_Electronic extends JS_Equipment {
    constructor(id, name, desc, rate, cat, cond, wt, mfr, eType, warranty, specs, available = true) {
        super(id, name, desc, rate, cat, cond, wt, mfr, available);
        this.electronicType = eType;
        this.warrantyMonths = warranty;
        this.specifications = specs;
    }
    getSubType() { return `Electronic (${this.electronicType})`; }
    calculateRent(days) {
        let base = this.dailyRate * days;
        if (this.electronicType === "Drone" || this.electronicType === "Camera") base *= 1.20;
        return base;
    }
}

class JS_Furniture extends JS_Equipment {
    constructor(id, name, desc, rate, cat, cond, wt, mfr, fType, material, color, available = true) {
        super(id, name, desc, rate, cat, cond, wt, mfr, available);
        this.furnitureType = fType;
        this.material = material;
        this.color = color;
    }
    getSubType() { return `Furniture (${this.furnitureType})`; }
    calculateRent(days) {
        let base = this.dailyRate * days;
        if (this.material === "Wood") base *= 1.10;
        return base;
    }
}

// ── User Hierarchy ────────────────────────────────────────────
class JS_User {
    constructor(id, name, email, phone, role) {
        this.userId = id;
        this.name = name;
        this.email = email;
        this.phone = phone;
        this.role = role;
    }
}

class JS_Customer extends JS_User {
    constructor(id, name, email, phone, address, membership = "Standard") {
        super(id, name, email, phone, "Customer");
        this.address = address;
        this.membershipType = membership;
    }
}

class JS_Admin extends JS_User {
    constructor(id, name, email, phone, dept) {
        super(id, name, email, phone, "Admin");
        this.department = dept;
    }
}

// ── Rental Manager Store ──────────────────────────────────────
const Store = {
    items: [],
    users: [],
    rentals: [],
    storageKey: "rentify-state-v1",
    searchQuery: "",

    init() {
        // Load initial sample data
        this.items = [
            new JS_Car(1, "Tesla Model 3", "Electric sedan with autopilot", 85, "Tesla", "Model 3", 2024, "Electric", "TS-001", 5, "Automatic", true, "Sedan", true),
            new JS_Car(2, "BMW X5", "Luxury SUV with premium features", 120, "BMW", "X5", 2023, "Diesel", "BW-002", 7, "Automatic", true, "Luxury", true),
            new JS_Bike(3, "Harley Davidson Iron 883", "Classic cruiser motorcycle", 55, "Harley", "Iron 883", 2023, "Petrol", "HD-004", 883, "Cruiser", true, true),
            new JS_Truck(4, "Ford F-150", "Heavy-duty pickup truck", 95, "Ford", "F-150", 2023, "Diesel", "FF-006", 3.5, 2, "Pickup", true),
            new JS_House(5, "Sunset Villa", "Beautiful villa with ocean view", 200, "123 Ocean Drive, Miami", 3500, 5, true, "1-5 yrs", 2, true, true, 5000, true),
            new JS_Apartment(6, "City Center Studio", "Modern studio apartment", 65, "456 Main St, NY", 600, 1, true, "New", 15, true, true, "Studio", true),
            new JS_Shop(7, "Downtown Retail", "Prime retail space", 150, "100 Commerce St, LA", 1200, 2, false, "5-10 yrs", "Retail", true, true, true),
            new JS_Tool(8, "DeWalt Power Drill", "Professional power drill", 15, "Power", "New", 2.5, "DeWalt", "Power Tool", true, "Battery", true),
            new JS_Electronic(9, "Canon EOS R5", "Professional mirrorless camera", 75, "Photo", "New", 0.7, "Canon", "Camera", 24, "45MP, 8K Video", true),
            new JS_Furniture(10, "Herman Miller Aeron", "Ergonomic office chair", 12, "Office", "New", 20, "Herman Miller", "Chair", "Metal", "Black", true)
        ];

        this.users = [
            new JS_Admin(1, "John Admin", "admin@rentalsys.com", "+1-555-0100", "Management"),
            new JS_Customer(2, "Alice Johnson", "alice@email.com", "+1-555-0201", "123 Main St, New York", "Standard"),
            new JS_Customer(3, "Bob Smith", "bob@email.com", "+1-555-0202", "456 Oak Ave, Chicago", "Premium"),
            new JS_Customer(4, "Carol Davis", "carol@email.com", "+1-555-0203", "789 Pine Rd, LA", "VIP")
        ];

        this.rentals = [
            { rentalId: 101, userId: 2, userName: "Alice Johnson", itemId: 1, itemName: "Tesla Model 3", itemType: "Vehicle > Car", startDate: "2024-01-15", endDate: "2024-01-20", durationDays: 5, totalCost: 425, status: "Completed" },
            { rentalId: 102, userId: 3, userName: "Bob Smith", itemId: 5, itemName: "Sunset Villa", itemType: "Property > House", startDate: "2024-02-01", endDate: "2024-02-08", durationDays: 7, totalCost: 1400, status: "Active" }
        ];

        this.loadState();

        // Mark rented items
        const rentedItemIds = this.rentals.filter(r => r.status === "Active").map(r => r.itemId);
        this.items.forEach(item => {
            if (rentedItemIds.includes(item.id)) item.available = false;
        });

        this.renderAll();
    },

    saveState() {
        const state = {
            items: this.items.map(item => ({ ...item, className: item.constructor.name })),
            users: this.users.map(user => ({ ...user, className: user.constructor.name })),
            rentals: this.rentals
        };
        localStorage.setItem(this.storageKey, JSON.stringify(state));
    },

    loadState() {
        const saved = localStorage.getItem(this.storageKey);
        if (!saved) return;

        try {
            const state = JSON.parse(saved);
            const itemClasses = { JS_Car, JS_Bike, JS_Truck, JS_House, JS_Apartment, JS_Shop, JS_Tool, JS_Electronic, JS_Furniture };
            const userClasses = { JS_Admin, JS_Customer };
            this.items = (state.items || []).map(item => Object.assign(Object.create(itemClasses[item.className]?.prototype || JS_RentalItem.prototype), item));
            this.users = (state.users || []).map(user => Object.assign(Object.create(userClasses[user.className]?.prototype || JS_User.prototype), user));
            this.rentals = state.rentals || [];
        } catch (error) {
            localStorage.removeItem(this.storageKey);
            console.warn("Saved rental data was invalid and has been reset.", error);
        }
    },

    renderAll() {
        this.saveState();
        this.updateStats();
        this.renderDashboardTable();
        this.renderVehicles();
        this.renderProperties();
        this.renderEquipment();
        this.renderRentalsTable();
        this.renderUsers();
        this.populateModalSelects();
    },

    updateStats() {
        const totalItems = this.items.length;
        const availableItems = this.items.filter(i => i.available).length;
        const vehiclesCount = this.items.filter(i => i.category === "Vehicle").length;
        const propsCount = this.items.filter(i => i.category === "Property").length;
        const equipCount = this.items.filter(i => i.category === "Equipment").length;

        const totalRevenue = this.rentals.reduce((sum, r) => sum + r.totalCost, 0);
        const activeRentals = this.rentals.filter(r => r.status === "Active").length;

        document.getElementById('stat-total-items').textContent = totalItems;
        document.getElementById('stat-available-items').textContent = `${availableItems} Available`;
        document.getElementById('stat-vehicles').textContent = vehiclesCount;
        document.getElementById('stat-properties').textContent = propsCount;
        document.getElementById('stat-revenue').textContent = `$${totalRevenue.toFixed(2)}`;
        document.getElementById('stat-active-rentals').textContent = `${activeRentals} Active Rentals`;

        // Progress bars
        const pVeh = totalItems ? Math.round((vehiclesCount / totalItems) * 100) : 0;
        const pProp = totalItems ? Math.round((propsCount / totalItems) * 100) : 0;
        const pEquip = totalItems ? Math.round((equipCount / totalItems) * 100) : 0;

        document.getElementById('pct-vehicles').textContent = `${pVeh}%`;
        document.getElementById('pct-properties').textContent = `${pProp}%`;
        document.getElementById('pct-equipment').textContent = `${pEquip}%`;

        document.getElementById('bar-vehicles').style.width = `${pVeh}%`;
        document.getElementById('bar-properties').style.width = `${pProp}%`;
        document.getElementById('bar-equipment').style.width = `${pEquip}%`;
    },

    renderDashboardTable() {
        const tbody = document.getElementById('dashboard-rentals-list');
        tbody.innerHTML = '';

        this.rentals.forEach(r => {
            const tr = document.createElement('tr');
            tr.innerHTML = `
                <td><strong>#${r.rentalId}</strong></td>
                <td>${r.userName}</td>
                <td>${r.itemName}</td>
                <td><span class="badge-mini">${r.itemType}</span></td>
                <td>${r.durationDays} Days</td>
                <td><strong>$${r.totalCost.toFixed(2)}</strong></td>
                <td><span class="badge-status ${r.status.toLowerCase()}">${r.status}</span></td>
                <td>
                    ${r.status === 'Active' ? `<button class="btn-text" onclick="Store.completeRental(${r.rentalId})">Return Item</button>` : '—'}
                </td>
            `;
            tbody.appendChild(tr);
        });
    },

    renderVehicles() {
        const grid = document.getElementById('vehicles-grid');
        grid.innerHTML = '';
        const filter = document.getElementById('vehicle-filter').value;

        const vehicles = this.items.filter(i => i.category === "Vehicle" && (filter === 'ALL' || i.constructor.name.includes(filter)) && this.matchesSearch(i));

        vehicles.forEach(v => {
            const card = document.createElement('div');
            card.className = 'item-card';
            card.innerHTML = `
                <div class="item-card-header">
                    <span class="item-type-tag">${v.getSubType()}</span>
                    <h3>${v.name}</h3>
                </div>
                <div class="item-card-body">
                    <p>${v.description}</p>
                    <div class="item-spec-list">
                        <span>Brand / Model: <strong>${v.brand} ${v.model} (${v.year})</strong></span>
                        <span>Fuel Type: <strong>${v.fuelType}</strong></span>
                        <span>Status: <strong class="${v.available ? 'badge-status available' : 'badge-status rented'}">${v.available ? 'Available' : 'Rented'}</strong></span>
                    </div>
                </div>
                <div class="item-card-footer">
                    <div class="item-price">$${v.dailyRate} <span>/ day</span></div>
                    ${v.available ? `<button class="btn btn-primary" onclick="openRentModalWithItem(${v.id})">Rent Now</button>` : `<button class="btn btn-secondary" disabled>Rented</button>`}
                </div>
            `;
            grid.appendChild(card);
        });
    },

    renderProperties() {
        const grid = document.getElementById('properties-grid');
        grid.innerHTML = '';
        const filter = document.getElementById('property-filter').value;

        const properties = this.items.filter(i => i.category === "Property" && (filter === 'ALL' || i.constructor.name.includes(filter)) && this.matchesSearch(i));

        properties.forEach(p => {
            const card = document.createElement('div');
            card.className = 'item-card';
            card.innerHTML = `
                <div class="item-card-header">
                    <span class="item-type-tag">${p.getSubType()}</span>
                    <h3>${p.name}</h3>
                </div>
                <div class="item-card-body">
                    <p>${p.description}</p>
                    <div class="item-spec-list">
                        <span>Address: <strong>${p.address}</strong></span>
                        <span>Area / Rooms: <strong>${p.areaSqFt} sq ft | ${p.rooms} Rooms</strong></span>
                        <span>Furnished: <strong>${p.furnished ? 'Yes' : 'No'}</strong></span>
                        <span>Status: <strong class="${p.available ? 'badge-status available' : 'badge-status rented'}">${p.available ? 'Available' : 'Rented'}</strong></span>
                    </div>
                </div>
                <div class="item-card-footer">
                    <div class="item-price">$${p.dailyRate} <span>/ day</span></div>
                    ${p.available ? `<button class="btn btn-primary" onclick="openRentModalWithItem(${p.id})">Rent Now</button>` : `<button class="btn btn-secondary" disabled>Rented</button>`}
                </div>
            `;
            grid.appendChild(card);
        });
    },

    renderEquipment() {
        const grid = document.getElementById('equipment-grid');
        grid.innerHTML = '';
        const filter = document.getElementById('equipment-filter').value;

        const equip = this.items.filter(i => i.category === "Equipment" && (filter === 'ALL' || i.constructor.name.includes(filter)) && this.matchesSearch(i));

        equip.forEach(e => {
            const card = document.createElement('div');
            card.className = 'item-card';
            card.innerHTML = `
                <div class="item-card-header">
                    <span class="item-type-tag">${e.getSubType()}</span>
                    <h3>${e.name}</h3>
                </div>
                <div class="item-card-body">
                    <p>${e.description}</p>
                    <div class="item-spec-list">
                        <span>Mfr / Cond: <strong>${e.manufacturer} (${e.condition})</strong></span>
                        <span>Weight: <strong>${e.weight} kg</strong></span>
                        <span>Status: <strong class="${e.available ? 'badge-status available' : 'badge-status rented'}">${e.available ? 'Available' : 'Rented'}</strong></span>
                    </div>
                </div>
                <div class="item-card-footer">
                    <div class="item-price">$${e.dailyRate} <span>/ day</span></div>
                    ${e.available ? `<button class="btn btn-primary" onclick="openRentModalWithItem(${e.id})">Rent Now</button>` : `<button class="btn btn-secondary" disabled>Rented</button>`}
                </div>
            `;
            grid.appendChild(card);
        });
    },

    renderRentalsTable() {
        const tbody = document.getElementById('rentals-table-body');
        tbody.innerHTML = '';

        this.rentals.forEach(r => {
            const tr = document.createElement('tr');
            tr.innerHTML = `
                <td><strong>#${r.rentalId}</strong></td>
                <td>${r.userName}</td>
                <td>${r.itemName}</td>
                <td><span class="badge-mini">${r.itemType}</span></td>
                <td>${r.startDate}</td>
                <td>${r.endDate}</td>
                <td>${r.durationDays} Days</td>
                <td><strong>$${r.totalCost.toFixed(2)}</strong></td>
                <td><span class="badge-status ${r.status.toLowerCase()}">${r.status}</span></td>
                <td>
                    ${r.status === 'Active' ? `<button class="btn btn-secondary" onclick="Store.completeRental(${r.rentalId})">Return</button>` : '—'}
                </td>
            `;
            tbody.appendChild(tr);
        });
    },

    renderUsers() {
        const grid = document.getElementById('users-grid');
        grid.innerHTML = '';

        this.users.forEach(u => {
            const card = document.createElement('div');
            card.className = 'user-card';
            card.innerHTML = `
                <div class="user-avatar"><i class="fa-solid ${u.role === 'Admin' ? 'fa-user-shield' : 'fa-user'}"></i></div>
                <div class="user-info">
                    <h3>${u.name} <span class="badge">${u.role}</span></h3>
                    <p><i class="fa-solid fa-envelope"></i> ${u.email}</p>
                    <p><i class="fa-solid fa-phone"></i> ${u.phone}</p>
                    ${u.address ? `<p><i class="fa-solid fa-location-dot"></i> ${u.address}</p>` : ''}
                </div>
            `;
            grid.appendChild(card);
        });
    },

    populateModalSelects() {
        const userSelect = document.getElementById('rent-user-select');
        const itemSelect = document.getElementById('rent-item-select');

        userSelect.innerHTML = this.users.map(u => `<option value="${u.userId}">${u.name} (${u.role})</option>`).join('');
        itemSelect.innerHTML = this.items.filter(i => i.available).map(i => `<option value="${i.id}">${i.name} — $${i.dailyRate}/day (${i.getSubType()})</option>`).join('');
    },

    matchesSearch(item) {
        if (!this.searchQuery) return true;
        const haystack = `${item.name} ${item.description} ${item.getSubType()}`.toLowerCase();
        return haystack.includes(this.searchQuery);
    },

    completeRental(rentalId) {
        const rental = this.rentals.find(r => r.rentalId === rentalId);
        if (rental) {
            rental.status = "Completed";
            const item = this.items.find(i => i.id === rental.itemId);
            if (item) item.available = true;
            this.renderAll();
        }
    }
};

// ── Tab Navigation ────────────────────────────────────────────
function switchTab(tabId) {
    document.querySelectorAll('.nav-item').forEach(btn => {
        btn.classList.toggle('active', btn.dataset.tab === tabId);
    });

    document.querySelectorAll('.tab-view').forEach(view => {
        view.classList.toggle('active', view.id === `view-${tabId}`);
    });
}

document.querySelectorAll('.nav-item').forEach(btn => {
    btn.addEventListener('click', () => switchTab(btn.dataset.tab));
});

// ── Filter Change Listeners ───────────────────────────────────
document.getElementById('vehicle-filter').addEventListener('change', () => Store.renderVehicles());
document.getElementById('property-filter').addEventListener('change', () => Store.renderProperties());
document.getElementById('equipment-filter').addEventListener('change', () => Store.renderEquipment());

// ── Search Listener (Template Search Simulation) ──────────────
document.getElementById('global-search').addEventListener('input', (e) => {
    const query = e.target.value.toLowerCase().trim();
    Store.searchQuery = query;
    Store.renderVehicles();
    Store.renderProperties();
    Store.renderEquipment();
    if (!query) {
        return;
    }

    // Filter items across grids
    const matched = Store.items.filter(i => i.name.toLowerCase().includes(query) || i.description.toLowerCase().includes(query));

    // If query typed, switch active tab to matching section or show matching cards
    if (matched.length > 0) {
        if (matched[0].category === "Vehicle") switchTab("vehicles");
        else if (matched[0].category === "Property") switchTab("properties");
        else if (matched[0].category === "Equipment") switchTab("equipment");
    }
});

// ── Modal Handling ────────────────────────────────────────────
function openModal(id) {
    document.getElementById(id).classList.add('open');
}

function closeModal(id) {
    document.getElementById(id).classList.remove('open');
}

document.getElementById('btn-quick-add').addEventListener('click', () => {
    toggleCategoryFields();
    openModal('modal-add-item');
});

document.getElementById('btn-quick-rent').addEventListener('click', () => {
    Store.populateModalSelects();
    openModal('modal-new-rent');
});

function openRentModalWithItem(itemId) {
    Store.populateModalSelects();
    document.getElementById('rent-item-select').value = itemId;
    openModal('modal-new-rent');
}

function openUserModal() {
    openModal('modal-new-user');
}

// Dynamic Form Fields for Add Item
function toggleCategoryFields() {
    const cat = document.getElementById('item-category-select').value;
    const container = document.getElementById('dynamic-fields');

    if (['Car', 'Bike', 'Truck'].includes(cat)) {
        container.innerHTML = `
            <div class="form-row">
                <div class="form-group"><label>Brand</label><input type="text" id="df-brand" class="form-control" required placeholder="e.g. Toyota"></div>
                <div class="form-group"><label>Model</label><input type="text" id="df-model" class="form-control" required placeholder="e.g. Camry"></div>
            </div>
            <div class="form-row">
                <div class="form-group"><label>Year</label><input type="number" id="df-year" class="form-control" value="2024"></div>
                <div class="form-group"><label>Fuel Type</label><input type="text" id="df-fuel" class="form-control" value="Petrol"></div>
            </div>
        `;
    } else if (['House', 'Apartment', 'Shop'].includes(cat)) {
        container.innerHTML = `
            <div class="form-group"><label>Address</label><input type="text" id="df-address" class="form-control" required placeholder="123 Street Name"></div>
            <div class="form-row">
                <div class="form-group"><label>Area (sq ft)</label><input type="number" id="df-area" class="form-control" value="1200"></div>
                <div class="form-group"><label>Rooms</label><input type="number" id="df-rooms" class="form-control" value="3"></div>
            </div>
        `;
    } else {
        container.innerHTML = `
            <div class="form-row">
                <div class="form-group"><label>Manufacturer</label><input type="text" id="df-mfr" class="form-control" value="Generic"></div>
                <div class="form-group"><label>Condition</label><input type="text" id="df-cond" class="form-control" value="New"></div>
            </div>
        `;
    }
}

// ── Form Submit Handling ──────────────────────────────────────
document.getElementById('form-add-item').addEventListener('submit', (e) => {
    e.preventDefault();
    const cat = document.getElementById('item-category-select').value;
    const name = document.getElementById('item-name').value;
    const rate = parseFloat(document.getElementById('item-rate').value);
    const desc = document.getElementById('item-desc').value;
    const id = Store.items.length + 1;

    const value = field => document.getElementById(field)?.value || "";
    const numberValue = field => parseFloat(value(field)) || 0;
    const integerValue = field => parseInt(value(field), 10) || 0;
    const brand = value('df-brand');
    const model = value('df-model');
    const year = integerValue('df-year');
    const fuel = value('df-fuel');
    const address = value('df-address');
    const area = numberValue('df-area');
    const rooms = integerValue('df-rooms');
    const manufacturer = value('df-mfr');
    const condition = value('df-cond');

    let newItem;
    switch (cat) {
        case 'Car':
            newItem = new JS_Car(id, name, desc, rate, brand, model, year, fuel, "REG-NEW", 5, "Automatic", true, "Sedan");
            break;
        case 'Bike':
            newItem = new JS_Bike(id, name, desc, rate, brand, model, year, fuel, "REG-NEW", 150, "Commuter", true);
            break;
        case 'Truck':
            newItem = new JS_Truck(id, name, desc, rate, brand, model, year, fuel, "REG-NEW", 5, 2, "Pickup");
            break;
        case 'House':
            newItem = new JS_House(id, name, desc, rate, address, area, rooms, true, "New", 2, true, true, 2000);
            break;
        case 'Apartment':
            newItem = new JS_Apartment(id, name, desc, rate, address, area, rooms, true, "New", 1, true, true, "Apartment");
            break;
        case 'Shop':
            newItem = new JS_Shop(id, name, desc, rate, address, area, rooms, false, "New", "Retail", true, true);
            break;
        case 'Electronic':
            newItem = new JS_Electronic(id, name, desc, rate, "Electronics", condition, 5, manufacturer, "Device", 12, "General");
            break;
        case 'Furniture':
            newItem = new JS_Furniture(id, name, desc, rate, "Furniture", condition, 5, manufacturer, "Furniture", "Wood", "Natural");
            break;
        default:
            newItem = new JS_Tool(id, name, desc, rate, "Tools", condition, 5, manufacturer, "Hand Tool", false, "Manual");
    }

    Store.items.push(newItem);
    Store.renderAll();
    closeModal('modal-add-item');
});

document.getElementById('form-new-rent').addEventListener('submit', (e) => {
    e.preventDefault();
    const uId = parseInt(document.getElementById('rent-user-select').value);
    const iId = parseInt(document.getElementById('rent-item-select').value);
    const start = document.getElementById('rent-start').value;
    const end = document.getElementById('rent-end').value;

    const user = Store.users.find(u => u.userId === uId);
    const item = Store.items.find(i => i.id === iId);

    const d1 = new Date(start);
    const d2 = new Date(end);
    if (Number.isNaN(d1.getTime()) || Number.isNaN(d2.getTime()) || d2 <= d1) {
        alert('End date must be after the start date.');
        return;
    }
    const days = Math.max(1, Math.ceil((d2 - d1) / (1000 * 60 * 60 * 24)));

    const cost = item.calculateRent(days);

    const newRental = {
        rentalId: Store.rentals.length + 101,
        userId: uId,
        userName: user.name,
        itemId: iId,
        itemName: item.name,
        itemType: `${item.category} > ${item.getSubType()}`,
        startDate: start,
        endDate: end,
        durationDays: days,
        totalCost: cost,
        status: "Active"
    };

    item.available = false;
    Store.rentals.push(newRental);
    Store.renderAll();
    closeModal('modal-new-rent');
});

document.getElementById('form-new-user').addEventListener('submit', (e) => {
    e.preventDefault();
    const role = document.getElementById('user-role-select').value;
    const name = document.getElementById('user-name').value;
    const email = document.getElementById('user-email').value;
    const phone = document.getElementById('user-phone').value;
    const id = Store.users.length + 1;

    let newUser;
    if (role === 'Admin') {
        newUser = new JS_Admin(id, name, email, phone, "Management");
    } else {
        const addr = document.getElementById('cust-address').value;
        newUser = new JS_Customer(id, name, email, phone, addr);
    }

    Store.users.push(newUser);
    Store.renderAll();
    closeModal('modal-new-user');
});

// Initialize on page load
window.addEventListener('DOMContentLoaded', () => {
    Store.init();
});
