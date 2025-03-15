#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

std::string current_account;

// For creating accounts
class User {
public:
    std::string username;
    std::string password;
    std::string email;
    bool admin = false;
};

// Stores all of the accounts in the database.
std::unordered_map<std::string, User> users = {
    { "admin",          {"admin", "password", "abc@site.com", true} },
    { "appleman",       {"appleman", "01234567", "applemanner@hotmail.com"} },
    { "plague23",       {"plague23", "securepassword", "plaguebringer@gmail.com"} },
    { "squeamish",      {"squeamish", "honey6moneykicks", "johndoe@gmail.com"} },
    { "__dunder__",     {"__dunder__", "^knighted^", "notnormal@yahoo.com"} },
    { "fireworker",     {"fireworker", "#hello%hacker", "hahahaha@yahoo.com"} },
    { "96pear",         {"96pear", "nullpassword", "mrmoneybags@aol.com"} },
    { "spacetronaut",   {"spacetronaut", "nullpassword", "studentname@schoolsisd.edu"} },
    { "big_pig333",     {"big_pig333", "nullpassword", "biggypiggy@lifejacket.org"} },
    { "1stack2grass3",  {"1stack2grass3", "nullpassword", "cowseatgrass@lifejacket.org"} },
    { "healthyhippo",   {"healthyhippo", "nullpassword", "hungryhippo@lifejacket.org"} },
    { "cupcakedestroyerofworlds", {"cupcakedestroyerofworlds", "1234five", "youremom@yadig.net"} }
};

void user_signup() {
    std::cout << "Sign-up" << std::endl;
    while (true) {

        // Input an email
        std::string new_email;
        std::cout << "New email: "; std::getline(std::cin, new_email);
        size_t pos_atsign = new_email.find("@");
        size_t pos_period = new_email.rfind(".");
        /*
        * For debugging
        std::cout << pos_atsign << std::endl;
        std::cout << pos_period << std::endl;
        std::cout << new_email.substr(0, pos_atsign).empty()  << std::endl;
        std::cout << new_email.substr(pos_atsign + 1, (pos_period - pos_atsign - 1)) << std::endl;
        std::cout << new_email.substr(pos_period + 1) << std::endl;
        */
        if  (   new_email.find_first_of("@") == std::string::npos // Does NOT contain "@" for domain
            ||  new_email.rfind(".") == std::string::npos // Does NOT contain "." for TLD
            ||  new_email.find(" ") != std::string::npos // Contains whitespace
            ||  new_email.substr(0, pos_atsign).empty() // Contains nothing before "@"
            ||  new_email.substr(pos_atsign+1, (pos_period - pos_atsign - 1)).empty() // Nothing between "@" and "."; nothing in 2LD
            ||  new_email.substr(pos_period+1).empty() // Contains nothing after "."; nothing in TLD
            )
        {
            std::cout << "You must use a valid email!" << std::endl;
            continue;
        }

        // Input a username
        std::string new_username;
        std::cout << "New username: "; std::getline(std::cin, new_username);
        size_t invalidusernamecharacters = new_username.find_first_of(" ~`!@#$%^&*()-+=[]{}\\|;:'\",.<>/?");
        if (invalidusernamecharacters != std::string::npos) // Contains any of the characters in invalidusernamecharacters
        {
            std::cout << "Your username cannot only contain alphanumeric characters, hyphens and underscores!" << std::endl;
            continue;
        }
        else if (new_username.size() < 3 || new_username.size() > 25) // Shorter than 3 or longer than 25 characters
        {
            std::cout << "Your username cannot be fewer than 3 or greater than 25 characters!" << std::endl;
            continue;
        }
        else if (new_username.empty()) // Contains nothing
        {
            std::cout << "Invalid username!" << std::endl;
            continue;
        }

        // Input a password
        std::string new_password;
        std::cout << "New password: "; std::getline(std::cin, new_password);
        if (new_password.find(" ") != std::string::npos) // Contains whitespace
        {
            std::cout << "Your password cannot contain spaces!" << std::endl;
            continue;
        }
        else if (new_password.size() < 8 || new_password.size() > 40) // Shorter than 8 or longer than 40 characters
        {
            std::cout << "Your username cannot be fewer than 8 or greater than 40 characters!" << std::endl;
            continue;
        }
        else if (new_password.empty()) // Contains nothing
        {
            std::cout << "Invalid password!" << std::endl;
            continue;
        }

        std::string verify_password;
        std::cout << "Verify your password: "; std::getline(std::cin, verify_password);
        if (verify_password != new_password)
        {
            std::cout << "Passwords don't match!" << std::endl;
            continue;
        }
        else
        {
            // Add new user to database
            std::pair<std::string, User> newuser (new_username, { new_username, new_password, new_email });
            users.insert(newuser);
            std::cout << "Account \"" << users[new_username].username << "\" has been created." << std::endl;
            break;
        }
    }
}

void user_login() {
    std::cout << "Login" << std::endl;
    while (true)
    {
        std::string temp_username;
        std::cout << "Username: "; std::getline(std::cin, temp_username);
        std::string temp_password;
        std::cout << "Password: "; std::getline(std::cin, temp_password);

        if (users.find(temp_username) == users.end()) // Does not find username in database
        {
            std::cout << "There is no account with that username!" << std::endl;
            continue;
        }
        else if (temp_password != users[temp_username].password) // Password doesn't match
        {
            std::cout << "That password is incorrect!" << std::endl;
            continue;
        }
        else
        {
            // Change current account
            current_account = users[temp_username].username;
            std::cout << "Welcome, " << users[temp_username].username << "!" << std::endl;
            break;
        }
    }
}

void user_signout() {
    if (users.find(current_account) != users.end()) {
        std::cout << "Goodbye, " << current_account << "!" << std::endl;
        current_account = "";
    }
}

// If admin: view all of the accounts in the database
void accounts() {
    if (users.find(current_account) != users.end() && users[current_account].admin) {
        for (auto& [username, user] : users) {
            std::cout << user.username << 
                " | password: " << user.password << " | email: " << user.email << std::endl;
        }
    }
}

void change_password() {
    if (users.find(current_account) != users.end()) {
        while (true) {
            std::string old_password;
            std::cout << "Old password: "; getline(std::cin, old_password); std::cout << std::endl;

            if (old_password != users[current_account].password) {
                std::cout << "That is not your password!" << std::endl;
                continue;
            }
            else
            {
                // Same checks as in user_signup
                std::string new_password;
                std::cout << "New password: "; getline(std::cin, new_password);
                if (new_password.find(" ") != std::string::npos)
                {
                    std::cout << "Your password cannot contain spaces!" << std::endl;
                    continue;
                }
                else if (new_password.size() < 8 || new_password.size() > 40)
                {
                    std::cout << "Your username cannot be fewer than 8 or greater than 40 characters!" << std::endl;
                    continue;
                }
                else if (new_password.empty())
                {
                    std::cout << "Invalid password!" << std::endl;
                    continue;
                }
                else {
                    std::string verify_password;
                    std::cout << "Verify your password: "; std::getline(std::cin, verify_password);
                    if (verify_password != new_password) {
                        std::cout << "Passwords don't match!" << std::endl;
                        continue;
                    }
                    else {
                        users[current_account].password = new_password;
                        std::cout << "Your password has been changed! Please log in again." << std::endl;
                        current_account = "";
                        break;
                    }
                }
            }
        }
    }
}

void change_username() {
    if (users.find(current_account) != users.end()) {
        while (true) {
            std::string password;
            std::cout << "Enter your password: "; getline(std::cin, password); std::cout << std::endl;

            if (password != users[current_account].password) {
                std::cout << "That is not your password!" << std::endl;
                continue;
            }

            while (true)
            {
                std::string new_username;
                std::cout << "New username: "; std::getline(std::cin, new_username);
                size_t invalidusernamecharacters = new_username.find_first_of(" ~`!@#$%^&*()-+=[]{}\\|;:'\",.<>/?");
                if (invalidusernamecharacters != std::string::npos) // Contains any of the characters in invalidusernamecharacters
                {
                    std::cout << "Your username cannot only contain alphanumeric characters, hyphens and underscores!" << std::endl;
                    continue;
                }
                else if (new_username.size() < 3 || new_username.size() > 25) // Shorter than 3 or longer than 25 characters
                {
                    std::cout << "Your username cannot be fewer than 3 or greater than 25 characters!" << std::endl;
                    continue;
                }
                else if (new_username.empty()) // Contains nothing
                {
                    std::cout << "Invalid username!" << std::endl;
                    continue;
                }
                else
                {
                    std::pair<std::string, User> replacement_user(new_username, { new_username, users[current_account].password, users[current_account].email });
                    users.insert(replacement_user);
                    users.erase(current_account);
                    current_account = new_username;
                    std::cout << "Your username is now \"" << users[current_account].username << "\"!" << std::endl;
                    break;
                }
            }
            break;
        }
    }
}