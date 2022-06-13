-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';
-- | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |

SELECT * FROM interviews WHERE month = 7 AND day = 28;
-- | 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- | 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- | 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
-- | 193 | Emma    | 2021 | 7     | 28  | I'm the bakery owner, and someone came in, suspiciously whispering into a phone for about half an hour. They never bought anything.                                                                                                                                                                                 |

SELECT * FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute > 15 AND minute <= 25;
-- | 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
-- | 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
-- | 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
-- | 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
-- | 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
-- | 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
-- | 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
-- | 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |

SELECT * FROM atm_transactions WHERE day = 28 AND month = 7 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
-- | 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
-- | 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
-- | 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
-- | 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
-- | 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
-- | 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |

SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'));
-- | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
-- | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
-- | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
-- | 458378 | Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
-- | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |

SELECT * FROM (SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE day = 28 AND month = 7 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'))) WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute > 15 AND minute <= 25);
-- | 396669 | Iman  | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 467400 | Luca  | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |

SELECT * FROM flights WHERE day = 29 AND month = 7 ORDER BY hour;
SELECT * FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE day = 29 AND month = 7 ORDER BY hour LIMIT 1);
SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE day = 29 AND month = 7 ORDER BY hour LIMIT 1));
-- | 395717 | Kenny  | (826) 555-1652 | 9878712108      | 30G67EN       |
-- | 398010 | Sofia  | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       |
-- | 467400 | Luca   | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 651714 | Edward | (328) 555-1152 | 1540955065      | 130LD9Z       |
-- | 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       | THIEF
-- | 953679 | Doris  | (066) 555-9701 | 7214083635      | M51FA04       |

SELECT * FROM phone_calls WHERE day = 28 AND month = 7 AND duration <= 60;
-- | 221 | (130) 555-0289 | (996) 555-8899 | 2021 | 7     | 28  | 51       |
-- | 224 | (499) 555-9472 | (892) 555-8872 | 2021 | 7     | 28  | 36       |
-- | 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       | THIEF CALL
-- | 234 | (609) 555-5876 | (389) 555-5198 | 2021 | 7     | 28  | 60       |
-- | 251 | (499) 555-9472 | (717) 555-1342 | 2021 | 7     | 28  | 50       |
-- | 254 | (286) 555-6063 | (676) 555-6554 | 2021 | 7     | 28  | 43       |
-- | 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
-- | 261 | (031) 555-6622 | (910) 555-3251 | 2021 | 7     | 28  | 38       |
-- | 279 | (826) 555-1652 | (066) 555-9701 | 2021 | 7     | 28  | 55       |
-- | 281 | (338) 555-6650 | (704) 555-2131 | 2021 | 7     | 28  | 54       |
SELECT * FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day = 28 AND month = 7 and duration <= 60);
-- | 395717 | Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
-- | 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 438727 | Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
-- | 449774 | Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 561160 | Kathryn | (609) 555-5876 | 6121106406      | 4ZY7I8T       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- | 907148 | Carina  | (031) 555-6622 | 9628244268      | Q12B3Z3       |
SELECT * FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE day = 28 AND month = 7 and duration <= 60);
-- | 250277 | James      | (676) 555-6554 | 2438825627      | Q13SVG6       |
-- | 251693 | Larry      | (892) 555-8872 | 2312901747      | O268ZZ0       |
-- | 467400 | Luca       | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 484375 | Anna       | (704) 555-2131 |                 |               |
-- | 567218 | Jack       | (996) 555-8899 | 9029462229      | 52R0Y8U       |
-- | 626361 | Melissa    | (717) 555-1342 | 7834357192      |               |
-- | 712712 | Jacqueline | (910) 555-3251 |                 | 43V0R5D       |
-- | 847116 | Philip     | (725) 555-3243 | 3391710505      | GW362R6       |
-- | 864400 | Robin      | (375) 555-8161 |                 | 4V16VO0       | THE ACCOMPLICE
-- | 953679 | Doris      | (066) 555-9701 | 7214083635      | M51FA04       |

SELECT * FROM passengers WHERE passport_number = 5773159633;
-- | 36        | 5773159633      | 4A   |
SELECT * FROM flights WHERE id = 36;
SELECT * FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE id = 36);
