# Password Strength Checker - C++ Console Application

A console-based application built in C++ that analyzes password strength based on multiple security criteria and provides a detailed evaluation report.

This project focuses on **input analysis, rule-based validation, and structured reporting**, simulating real-world password validation logic.

---

## Features

- Analyze password based on:
  - Minimum length (>= 8)
  - Bonus length (>= 12)
  - Uppercase characters
  - Lowercase characters
  - Digits
  - Special characters
  - Absence of spaces
- Score-based evaluation system
- Strength classification:
  - Weak
  - Fair
  - Good
  - Strong
  - Very Strong
- Detailed feedback report
- Continuous checking loop

---

## Core Concepts Applied

- Enums (`enum`) for strength classification
- Structs (`struct`) for:
  - Password report data
  - Character tracking
- Character classification using:
  - `isupper`, `islower`, `isdigit`, `ispunct`, `isspace`
- Rule-based scoring system
- Modular function design
- Console formatting using `iomanip`
- Basic system interaction (`system`, `Sleep`)

---

## How It Works

1. User enters a password
2. Program analyzes:
   - Length requirements
   - Character composition
3. A score is calculated based on conditions met
4. Password is classified into a strength level
5. A detailed report is displayed

---

## How to Run

### Compile (Windows):
```bash
g++ -std=c++17 main.cpp -o app
./app
