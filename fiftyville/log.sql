-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports
-- scene coducted around 10:15 AM
-- going to the bakery for following the leads from it
SELECT * FROM bakery_security_logs
-- Identifying some potential plates
-- Going to people to look at some connections
SELECT * FROM people
-- Find any of the same plates seen at the day of the theft
SELECT * FROM people WHERE license_plate = (SELECT license_plate FROM bakery_security_logs)
-- | 354903 | Marilyn | (568) 555-3190 | 7441135547      | 0R0FW39       |
-- Check the interviews table
SELECT * FROM interviews
-- Give a more thorough selection
SELECT * FROM interviews WHERE month = 7 ORDER BY month, day ASC
-- within 10 minutes of the theft, the thief goes in his car
-- In the call, I heard the thief say that they were planning to take the earliest flight
-- out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
SELECT * FROM phone_calls
SELECT * FROM phone_calls WHERE month = 7 AND day = 28
-- Go to the atm transactions
SELECT * FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Leggett Street"
-- | 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
-- | 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
-- | 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
-- | 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
-- | 275 | 86363979       | 2021 | 7     | 28  | Leggett Street | deposit          | 10     |
-- | 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
-- | 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
SELECT * FROM interviews WHERE month = 7 AND day = 28 ORDER BY month, day ASC
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--  If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket. |
SELECT * FROM phone_calls WHERE month = 7 AND day = 28 AND duration <= 60
-- | 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
-- | 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
-- | 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
-- | 234 | (609) 555-5876 | (389) 555-5198 | 2021 | 7     | 28  | 60       |
-- | 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
-- | 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
-- | 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
-- | 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       |
-- | 279 | (826) 555-1652 | (066) 555-9701 | 2021 | 7     | 28  | 55       |
-- | 281 | (338) 555-6650 | (704) 555-2131 | 2021 | 7     | 28  | 54       |
SELECT * FROM airports
SELECT * FROM flights WHERE month = 7 AND day = 28 AND origin_airport_id = 8
-- | 1  | 8                 | 7                      | 2021 | 7     | 28  | 17   | 50     |
-- | 6  | 8                 | 5                      | 2021 | 7     | 28  | 13   | 49     |
-- | 17 | 8                 | 4                      | 2021 | 7     | 28  | 20   | 16     |
-- | 34 | 8                 | 5                      | 2021 | 7     | 28  | 17   | 20     |
-- | 35 | 8                 | 4                      | 2021 | 7     | 28  | 16   | 16     |
-- The flight to Dallas is the earliest one
SELECT * FROM passengers WHERE flight_id = 6
-- | flight_id | passport_number | seat |
-- +-----------+-----------------+------+
-- | 6         | 3835860232      | 9A   |
-- | 6         | 1618186613      | 2C   |
-- | 6         | 7179245843      | 3B   |
-- | 6         | 1682575122      | 4B   |
-- | 6         | 7597790505      | 5D   |
-- | 6         | 6128131458      | 6B   |
-- | 6         | 6264773605      | 7D   |
-- | 6         | 3642612721      | 8A   |
SELECT * FROM people WHERE passport_number = (SELECT passport_number FROM passengers WHERE flight_id = 6)
-- |   id   |  name  |  phone_number  | passport_number | license_plate |
-- +--------+--------+----------------+-----------------+---------------+
-- | 780088 | Nicole | (123) 555-5144 | 3835860232      | 91S1K32       |
SELECT * FROM bakery_security_logs WHERE license_plate = "91S1K32" -- no success with it
SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 6)
-- | 341739 | Rebecca | (891) 555-5672 | 6264773605      |               |
-- | 423393 | Carol   | (168) 555-6126 | 6128131458      | 81MNC9R       |
-- | 505688 | Jean    | (695) 555-0348 | 1682575122      | JN7K44M       |
-- | 632023 | Amanda  | (821) 555-5262 | 1618186613      | RS7I6A0       |
-- | 745650 | Sophia  | (027) 555-1068 | 3642612721      | 13FNH73       |
-- | 750165 | Daniel  | (971) 555-6468 | 7597790505      | FLFN3W0       |
-- | 780088 | Nicole  | (123) 555-5144 | 3835860232      | 91S1K32       |
-- | 872102 | Joyce   |                | 7179245843      | 594IBK6       |
SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 6) AND phone_number IN (SELECT caller FROM phone_calls WHERE duration <= 60)
SELECT * FROM people WHERE license_plate IN  (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28)
SELECT * FROM people WHERE license_plate IN  (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28)
SELECT * FROM atm_transactions WHERE atm_location = "Leggett Street" AND month = 7 and day = 28