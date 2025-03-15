#include <iostream>
#include "classes_functions.h"

int main()
{
    // Run command prompt
    while (true) {
        std::string cmd;
        std::cout << ">> "; std::getline(std::cin, cmd); std::cout << std::endl;
        if (cmd == "accounts")
            accounts();
        else if (cmd == "signup")
            user_signup();
        else if (cmd == "login")
            user_login();
        else if (cmd == "signout")
            user_signout();
        else if (cmd == "changepassword")
            change_password();
        else if (cmd == "changeusername")
            change_username();
        else if (cmd == "end")
            return 0;
    }

    return 0;
}