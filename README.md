# Train Trip Search and Booking Application

## Description
This application allows users to search for train trips and make reservations and operators to manage trip details. The app ensures secure operations with password strength validation and robust exception handling.

---

## Features

### Operator Functionalities:
1. **Login**:
   - Existing operators can log in using predefined credentials stored in a CSV file.
   - Handles errors for incorrect username or password.
2. **Add or Remove Trips**:
   - Operators can add or delete trips with details such as departure city, arrival city, date, and time.
   - Validates input to avoid incorrect data:
     - Invalid date format.
     - Past dates.
     - Nonexistent characters in city names.

### User Functionalities:
1. **Account Creation**:
   - Users can create an account with a valid email and secure password.
   - Validates:
     - Email format.
     - Password strength (weak passwords are rejected).
     - Matching repeated passwords.
2. **Authentication**:
   - Users can log in to access booking features.
   - Handles errors for invalid credentials or weak passwords.
3. **Search for Trips**:
   - Users can search for available train trips based on their preferences.
   - Handles cases where no matching trips are found.
4. **Reserve Seats**:
   - Allows users to book a seat by specifying:
     - Train class (e.g., first class, second class).
     - Reservation time.
   - Validates reservation details.

---

## Password Strength Estimation
- Passwords are classified as:
  - **Weak**: Rejected; must be re-entered.
  - **Ok**: Acceptable.
  - **Good**: Strong password.
- Factors influencing strength:
  - Length.
  - Use of uppercase, lowercase, numbers, and special characters.

---

## Exception Handling
### Operator:
- Handles:
  - Incorrect login credentials.
  - Errors in trip details (date format, past dates, invalid city names).

### User:
- Handles:
  - Incorrect login or authentication errors.
  - Invalid input for account creation or trip reservations.
  - Nonexistent trips or reservation errors.

---

## Technologies Used
- Programming Language: `C++` and `Kotlin`
- Data Storage: `CSV` files for storing user and trip details.
- Exception Handling: `try-catch` blocks.

---