# COMP3004 Deliverable 2 — HintonMarket Vertical Prototype

## Overview
A Qt-based C++ application simulating the HintonMarket stall booking system. Vendors can browse market dates, book stalls, join waitlists, and view their dashboard. The Market Operator can book/cancel stalls and manage waitlists on behalf of vendors. All data is persisted using SQLite. The system supports three user roles: Vendor, Market Operator, and System Administrator.

## How to Build & Run
1. Open `FirstProject.pro` in Qt Creator on the course VM.
2. Build and run the project.
3. The pre-populated database file `hintonMarket.sqlite3` is automatically copied to the build directory.

Alternatively, from the command line:
```bash
qmake FirstProject.pro
make
./FirstProject
```

**Database file:** `hintonMarket.sqlite3` — included with all required default data. No initialization steps needed.

## Users
The system loads 10 users at startup from the SQLite database. Enter any username on the login screen:

| Username | Role | Category |
|---|---|---|
| `thebreadcompany` | Vendor | Food |
| `jiyoungwoo` | Vendor | Food |
| `mattsoup` | Vendor | Food |
| `jamsdiego` | Vendor | Food |
| `poppyjules` | Vendor | Artisan |
| `homemade98` | Vendor | Artisan |
| `chetana` | Vendor | Artisan |
| `yijunart` | Vendor | Artisan |
| `boss` | Market Operator | — |
| `admin` | System Administrator | — |

## Features

### Vendor Features
- **Login** — Enter a username; the system routes to the correct interface based on user type (polymorphic dispatch).
- **Browse Market Dates** — View 4 weeks of markets with food/artisan stall availability.
- **Book a Stall** — Book one stall per vendor. Max 2 food + 2 artisan vendors per market day.
- **Cancel Booking** — Frees the stall and notifies the next vendor on the waitlist.
- **Join Waitlist** — When a category is full, vendors can queue up (FIFO, per category per week).
- **Leave Waitlist** — Remove yourself; remaining positions update automatically.
- **Vendor Dashboard** — Shows business info, compliance docs, active bookings, waitlist positions, and system notifications.

### Market Operator Features (New in D2)
- **Book a stall on behalf of a vendor** — Select a vendor and market date, then book.
- **Cancel a booking on behalf of a vendor** — Select a vendor and market date, then cancel.
- **Remove a vendor from a waitlist** — Select a vendor and market date, then remove from waitlist.
- All changes are reflected in the vendor's dashboard when the vendor logs in.

### Data Persistence (New in D2)
- All data (users, vendors, market schedule, bookings, waitlists) is stored in an SQLite database (`hintonMarket.sqlite3`).
- Data persists between program executions. Bookings and waitlist entries survive restarts.
- Object-relational mapping: SQL query results are used to create in-memory objects on startup.

## Architecture
Data is persisted using SQLite via the `DatabaseManager` singleton. On startup, all data is loaded from the database into in-memory objects. Changes are written to both memory and the database.

| Class | Purpose |
|---|---|
| `User` | Abstract base class (polymorphic `getUserType()`) |
| `Vendor`, `Organizer`, `Admin` | User subclasses |
| `Storage` | Loads users and market dates from SQLite into memory |
| `DatabaseManager` | Singleton managing the SQLite database connection |
| `MarketDate` | A market week with `BookingSlots` (capacity 2 per category) |
| `BookingSlots` | Fixed-size slot array for a vendor category |
| `Booking` | Links a vendor to a market date |
| `BookingList` | Collection of all active bookings |
| `Waitlist` | FIFO queue for one category on one market week |
| `WaitlistManager` | Manages all waitlists (keyed by date + category) |
| `StallBookingControl` | Coordinates booking/cancellation/waitlist logic + SQL persistence |
| `DashboardControl` | Gathers dashboard data for a vendor |
| `MainWindow` | Qt GUI — login, navigation, market browser, dashboard, operator page |

## Business Rules
- Vendors can hold only **one active booking** at a time.
- Each market day supports **max 2 food** and **max 2 artisan** vendors.
- Waitlists are **per category per week** (up to 8 total), FIFO order.
- Cancelling a booking **notifies the next waitlisted vendor** in that category.
