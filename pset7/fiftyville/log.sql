-- Keep a log of any SQL queries you execute as you solve the mystery.

-- for parking lot
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE activity = "exit" AND year =2020 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25);

-- atm trasection

SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"));

-- phone call

SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year =2020 AND month = 7 AND day = 28 AND duration < 60);

-- flights

SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND hour = 8 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville")));

-- connect all the above four query to find theif.

-- city
SELECT city FROM airports WHERE id IN (SELECT destination_airport_id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND hour = 8 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville"));

-- saathi

SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE year =2020 AND month = 7 AND day = 28 AND duration < 60 AND caller = (SELECT DISTINCT(phone_calls.caller) FROM phone_calls JOIN people ON people.phone_number = phone_calls.caller WHERE people.name = "Ernest"));
