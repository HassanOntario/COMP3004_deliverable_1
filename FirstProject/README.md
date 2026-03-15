# COMP3004 Deliverable 1 — HintonMarket Vertical Prototype

## Overview
A Qt-based C++ application simulating the HintonMarket stall booking system. Vendors can browse market dates, book stalls, join waitlists, and view their dashboard. The system supports three user roles: Vendor, Market Operator, and System Administrator.

## How to Build & Run
```bash
qmake FirstProject.pro
make
./FirstProject
```

## Users
The system loads 10 users at startup. Enter any username on the login screen:

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
- **Login** — Enter a username; the system routes to the correct interface based on user type (polymorphic dispatch).
- **Browse Market Dates** — View 4 weeks of markets with food/artisan stall availability.
- **Book a Stall** — Book one stall per vendor. Max 2 food + 2 artisan vendors per market day.
- **Cancel Booking** — Frees the stall and notifies the next vendor on the waitlist.
- **Join Waitlist** — When a category is full, vendors can queue up (FIFO, per category per week).
- **Leave Waitlist** — Remove yourself; remaining positions update automatically.
- **Vendor Dashboard** — Shows business info, compliance docs, active bookings, waitlist positions, and system notifications.

## Architecture
All data is held in memory. No database or file persistence — everything resets on restart.

| Class | Purpose |
|---|---|
| `User` | Abstract base class (polymorphic `getUserType()`) |
| `Vendor`, `Organizer`, `Admin` | User subclasses |
| `Storage` | Holds all users and market dates |
| `MarketDate` | A market week with `BookingSlots` (capacity 2 per category) |
| `BookingSlots` | Fixed-size slot array for a vendor category |
| `Booking` | Links a vendor to a market date |
| `BookingList` | Collection of all active bookings |
| `Waitlist` | FIFO queue for one category on one market week |
| `WaitlistManager` | Manages all waitlists (keyed by date + category) |
| `StallBookingControl` | Coordinates booking/cancellation/waitlist logic |
| `DashboardControl` | Gathers dashboard data for a vendor |
| `MainWindow` | Qt GUI — login, navigation, market browser, dashboard |

## Business Rules
- Vendors can hold only **one active booking** at a time.
- Each market day supports **max 2 food** and **max 2 artisan** vendors.
- Waitlists are **per category per week** (up to 8 total), FIFO order.
- Cancelling a booking **notifies the next waitlisted vendor** in that category.
