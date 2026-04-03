BEGIN TRANSACTION;

CREATE TABLE IF NOT EXISTS users (
    user_id   INTEGER PRIMARY KEY AUTOINCREMENT,
    username  TEXT NOT NULL UNIQUE,
    role      TEXT NOT NULL CHECK(role IN ('vendor','organizer','administrator'))
);

CREATE TABLE IF NOT EXISTS vendors (

    -- Identification
    vendor_id          INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id            INTEGER NOT NULL UNIQUE,

    -- Category
    vendor_type        TEXT NOT NULL CHECK(vendor_type IN ('food','artisan')),


    -- BusinessInfo
    business_name      TEXT NOT NULL,
    owner_name         TEXT NOT NULL,
    email_address      TEXT NOT NULL,
    phone_number       INTEGER NOT NULL,
    mailing_address    TEXT NOT NULL,

    -- Documentation

        -- BusinessLicense
    licenseNum                 INTEGER,
    businessExpirationDate     TEXT,

        -- Insurance
    policyNum                  INTEGER,
    insuranceProvider          TEXT,
    insuranceExpirationDate    TEXT,

        -- Certification -- Food Handlers ONLY

    certNum                  INTEGER,
    certExpirationDate       TEXT,

    FOREIGN KEY (user_id) REFERENCES users(user_id)
);

CREATE TABLE IF NOT EXISTS market_schedule (
    market_id         INTEGER PRIMARY KEY AUTOINCREMENT,
    market_date       TEXT NOT NULL UNIQUE,
    max_food_stalls   INTEGER NOT NULL DEFAULT 2,
    max_artisan_stalls INTEGER NOT NULL DEFAULT 2
);

CREATE TABLE IF NOT EXISTS stall_bookings (
    booking_id  INTEGER PRIMARY KEY AUTOINCREMENT,
    market_id   INTEGER NOT NULL,
    vendor_id   INTEGER NOT NULL,

    FOREIGN KEY (market_id) REFERENCES market_schedule(market_id),
    FOREIGN KEY (vendor_id) REFERENCES vendors(vendor_id),
    UNIQUE(market_id, vendor_id)
);

CREATE TABLE IF NOT EXISTS waitlist (
    waitlist_id INTEGER PRIMARY KEY AUTOINCREMENT,
    market_id   INTEGER NOT NULL,
    vendor_id   INTEGER NOT NULL,
    position    INTEGER NOT NULL,
    joined_at   TEXT DEFAULT CURRENT_TIMESTAMP,
    status      TEXT DEFAULT 'waiting' CHECK(status IN ('waiting','promoted','withdrawn')),
    FOREIGN KEY (market_id) REFERENCES market_schedule(market_id),
    FOREIGN KEY (vendor_id) REFERENCES vendors(vendor_id),
    UNIQUE(market_id, vendor_id)
);

-- Populate the fields


INSERT INTO users (username, role) VALUES
('admin', 'administrator'),
('boss', 'organizer'),
('thebreadcompany', 'vendor'),
('jiyoungwoo', 'vendor'),
('mattsoup', 'vendor'),
('jamsdiego', 'vendor'),
('poppyjules', 'vendor'),
('homemade98', 'vendor'),
('chetana', 'vendor'),
('yijunart', 'vendor');

INSERT INTO vendors (user_id, vendor_type,
                    business_name, owner_name, email_address, phone_number, mailing_address,
                    licenseNum, businessExpirationDate,
                    policyNum, insuranceProvider, insuranceExpirationDate,
                    certNum, certExpirationDate) VALUES
(3, 'food',
'The Bread Company', 'Elfi Lutz', 'mail@thebreadcompany.com', 6135587921, '39 St Clair Avenue W, Toronto, ON, M6A 2T2',
493756908, '2030-06-30',
109874567, 'Algoma Mutual Insurance Company', '2030-06-30',
475846, '2030-06-30'),

(4, 'food', 'Bubba Tea', 'Jiyoung Woo', 'info@bubbatea.ca', 6138667357, '21 Pharmacy Drive, Hintonville, ON, N4P 1R9', 748755634, '2030-06-30', 108564734, 'Allstate Insurance Company', '2030-06-30', 574835, '2030-06-30'),
(5, 'food', 'Matthiew''s Soup Spot', 'Matthieau Parfait', 'matt_soup@gmail.com', 6138540909, '46 Old Lane, Hintonville, ON, L5T 7Y6', 584735287, '2030-06-30', 100846385, 'Echelon Insurance', '2030-06-30', 746356, '2030-06-30'),
(6, 'food', 'Jams by Diego', 'Lauro Diego', 'jamsbydiego@gmail.com', 5147294419, '59 Rue Guy, Montreal, QC, H3H 2L5', 539345664, '2030-06-30', 107768535, 'Allstate Insurance Company', '2030-06-30', 305123, '2030-06-30'),
(7, 'artisan', 'Poppy''s Earrings', 'Poppy Jules', 'poppys_earrings@outlook.com', 6137628641, '100 Wellington Street, Ottawa, ON, K1A 0A9', 985237121, '2030-06-30', 102384203, 'Reliance Insurance Company', '2030-06-30', 320232, '2030-06-30'),
(8, 'artisan', 'Homemade Hintonville', 'Percy Nikolas', 'homemadehandmade@gmail.com', 3437658998, '75 Port Lane, Hintonville, ON, L3R 5Y7', 232131214, '2030-06-30', 101239112, 'Westport Insurance Corporation', '2030-06-30', 201933, '2030-06-30'),
(9, 'artisan', 'Subcontinental Attire Homemade', 'Chetana Jai', 'contact@subcontinentalattire.ca', 6139986780, '10 Rideau Street, Ottawa, ON, K1N 9J7', 101921123, '2030-06-30', 100032325, 'Westport Insurance Corporation', '2030-06-30', 987332, '2030-06-30'),
(10, 'artisan', 'Yijun''s Art', 'Yijun Ying', 'yijunart@hotmail.com', 6139681138, '342 Garden Parkway, Hintonville, ON, L4N 6Y3', 342244536, '2030-06-30', 107593443, 'Westport Insurance Corporation', '2030-06-30', 759322, '2030-06-30');

INSERT INTO market_schedule (market_date) VALUES
('2026-06-07'), ('2026-06-14'), ('2026-06-21'), ('2026-06-28');



COMMIT;
