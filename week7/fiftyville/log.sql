-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT *
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';

--The theft took place at 10:15 am at the Humphrey Street bakery. the reports mentioned the existence of
--some interviews that might bring valuable information to the case

SELECT *
FROM interviews
WHERE month = 7 AND day = 28;

--In the interviews from the day of the robbery ruth, id: 161, Eugene, id: 162 and Raymon, id: 163, mention to have witnessed the thief
--at some point throughout the day

SELECT *
FROM interviews
WHERE month = 7 AND day = 28 AND transcript LIKE '%bakery%';

--From the interviews of the witnesses that mentioned the bakery, we can elaborate a possible timeline of the thief's actions:
--_in the morning the thief was withdrawing some money from the ATM on Leggett Street.
--__After the theft, the thief got into a car in the bakery parking lot and drove away, the security footage from the
--bakery parking lot night valuable information to the case.
--__As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, the thief say that they were
--planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT *
FROM atm_transactions
WHERE month = 7 AND day = 28
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

--First thing we'll do is look into the atm transactions, more precisely withdrawals, made the day of the robbery, then we'll use the list of bank accounts
--and the information provided by the bank to have a list of people that withdraw money from the ATM on Leggett Street, the day of the robbery, and their information.

SELECT people.id, people.name, people.phone_number, people.passport_number, people.license_plate
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.month = 7 AND atm_transactions.day = 28
AND atm_transactions.atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw';

--Next is to check the security footage from the bakery parking lot, here we're looking for records of a car exiting the parking lot the day of the theft through 10 AM.
--Now we have a list of license plates.

SELECT *
FROM bakery_security_logs
WHERE month = 7 AND day = 28
AND hour = 10
AND activity = 'exit';

--And with the next query and the information of the license plates we have a list of people that withdraw money from ATM on Leggett Street on 7/28 and exited the bakery
--parking lot on 7/28 at around 10 AM

SELECT people.id, people.name, people.phone_number, people.passport_number, people.license_plate
FROM (people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate)
WHERE atm_transactions.month = 7 AND atm_transactions.day = 28
AND atm_transactions.atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw'
AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.activity = 'exit';


SELECT *
FROM flights
WHERE month = 7 AND day = 29 ORDER BY hour, minute;

--With the next query we'd have a list of people's passports, people that took the first flight, from Fiftyville, the next day of the theft

SELECT passengers.flight_id, passengers.passport_number, flights.hour, flights.minute, airports.city
FROM (passengers
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.origin_airport_id = airports.id)
WHERE flights.month = 7 AND flights.day = 29 AND airports.city = 'Fiftyville'
AND flights.hour = (SELECT hour FROM flights WHERE month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1)
AND flights.minute = (SELECT minute FROM flights WHERE month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1);

--Joining the 2 big queries from before with an Inner join on the passport number we'd have a bigger query that return us a list of people who withdraw money from ATM on
--Leggett Street on 7/28 and exited the bakery parking lot on 7/28 at the first half of 10 AM and took the first flight, from Fiftyville, the next day of the theft.

SELECT people.id, people.name, people.phone_number, people.passport_number, people.license_plate, passengers.flight_id, flights.hour, flights.minute, airports.city
FROM (people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate)
INNER JOIN (passengers
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.origin_airport_id = airports.id) ON people.passport_number = passengers.passport_number
WHERE atm_transactions.month = 7 AND atm_transactions.day = 28
AND atm_transactions.atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw'
AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute < 30
AND bakery_security_logs.activity = 'exit'
AND flights.month = 7 AND flights.day = 29 AND airports.city = 'Fiftyville'
AND flights.hour = (SELECT hour FROM flights WHERE month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1)
AND flights.minute = (SELECT minute FROM flights WHERE month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1);


SELECT *
FROM phone_calls
WHERE month = 7 AND day = 28;

--Joining the last bigger query with a list of people who made a phone call the day of the theft, that took less than 60 seconds using an inner join we have a list of 1 suspect.
--Now we just have to track the accomplice.

SELECT people.id, people.name, people.phone_number, people.passport_number, people.license_plate, passengers.flight_id, flights.hour, flights.minute, airports.city, flights.destination_airport_id, phone_calls.receiver, phone_calls.duration
FROM ((people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate)
INNER JOIN (passengers
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.origin_airport_id = airports.id) ON people.passport_number = passengers.passport_number)
INNER JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE atm_transactions.month = 7 AND atm_transactions.day = 28
AND atm_transactions.atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw'
AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute < 30
AND bakery_security_logs.activity = 'exit'
AND flights.month = 7 AND flights.day = 29 AND airports.city = 'Fiftyville'
AND flights.hour = (SELECT hour FROM flights WHERE month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1)
AND flights.minute = (SELECT minute FROM flights WHERE month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1)
AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration <= 60;


--With the next query we have one person who was called by the suspect the day of the theft, whose call lasted less then 60 seconds.

SELECT *
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE month = 7 AND day = 28
AND caller IN(
    SELECT people.phone_number
FROM ((people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate)
INNER JOIN (passengers
JOIN flights ON passengers.flight_id = flights.id
JOIN airports ON flights.origin_airport_id = airports.id) ON people.passport_number = passengers.passport_number)
INNER JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE atm_transactions.month = 7 AND atm_transactions.day = 28
AND atm_transactions.atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw'
AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute < 30
AND bakery_security_logs.activity = 'exit'
AND flights.month = 7 AND flights.day = 29 AND airports.city = 'Fiftyville'
AND flights.hour = (SELECT hour FROM flights WHERE month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1)
AND flights.minute = (SELECT minute FROM flights WHERE month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1)
AND phone_calls.month = 7 AND phone_calls.day = 28
)
AND phone_calls.duration <= 60;

--And with the next and last query we can get the destination city of the suspect.

SELECT DISTINCT airports.full_name, airports.city
FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
WHERE flights.destination_airport_id IN(
    SELECT flights.destination_airport_id
    FROM ((people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate)
    INNER JOIN (passengers
    JOIN flights ON passengers.flight_id = flights.id
    JOIN airports ON flights.origin_airport_id = airports.id) ON people.passport_number = passengers.passport_number)
    INNER JOIN phone_calls ON people.phone_number = phone_calls.caller
    WHERE atm_transactions.month = 7 AND atm_transactions.day = 28
    AND atm_transactions.atm_location = 'Leggett Street'
    AND atm_transactions.transaction_type = 'withdraw'
    AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28
    AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute < 30
    AND bakery_security_logs.activity = 'exit'
    AND flights.month = 7 AND flights.day = 29 AND airports.city = 'Fiftyville'
    AND flights.hour = (SELECT hour FROM flights WHERE month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1)
    AND flights.minute = (SELECT minute FROM flights WHERE month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1)
    AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration <= 60
);
