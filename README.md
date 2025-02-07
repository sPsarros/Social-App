# Photo Managing (C++)
A simple, console-based Photo Management System written in C++.  This project demonstrates fundamental C++ programming concepts and provides basic photo management functionalities. It's designed for educational purposes and showcases a command-line interface approach.

## Features

*   **User Authentication:**  Secure login using credentials stored in a `users.txt` file.
*   **Photo Upload:** Upload photos with associated metadata (description, filename, location).
*   **Photo Details:** View detailed information about uploaded photos.
*   **User Tagging:** Tag other users in photos.
*   **Tag Removal:** Remove tags from photos.
*   **Photo Deletion:** Delete photos from the system.
*   **Logout Functionality:** Securely log out of the application.

## Getting Started

### Prerequisites

*   C++ compiler (e.g., g++)
*   `users.txt` file

### Installation

1.  Clone the repository:
    ```bash
    git clone https://github.com/sPsarros/Social-App.git
    cd Social-App
    ```

2.  Compile the program:
    ```bash
    g++ main.cpp -o Social-App
    ```

### User Credentials (`users.txt`)

The `users.txt` file should contain usernames and passwords, one pair per line, separated by a space.  For example:
*    user1 password1
*    user2 password2
*    (Storing passwords in plain text is highly insecure.  This is for demonstration purposes only.)


### Future Improvements
*  User Registration
*  Security Enhancements
