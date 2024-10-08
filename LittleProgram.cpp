// update

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class LittleProgram
{
private:
    string userName;
    string password;
    string confirmPassword;

public:
    void createNewAccount()
    {
        // Variable
        string userName, password, confirmPassword;
        int userCount = 0;
        string line;
        bool spaceChecking;

        // Open and read file, then count 'User #' and store in userCount. After that then userCount++ one more time to match the next 'User #'.
        ifstream readFile("user data.txt");
        if (readFile.is_open())
        {
            while (getline(readFile, line))
            {
                if (line.find("User #") != string::npos)
                {
                    userCount++;
                }
            }
            readFile.close();
        }

        userCount++;

        // Asking for user data and store in variable
        cout << "Please input your username: ";
        getline(cin, userName);

        do
        {
            cout << "Please input your password (Your password can't contain any space): ";
            getline(cin, password);

            // Checking for space in password
            int lenPassword = password.length();

            for (int i = 0; i < lenPassword; i++)
            {
                if (isspace(password[i]))
                {
                    spaceChecking = false;
                    break;
                }
                else
                {
                    spaceChecking = true;
                }
            }

            if (!spaceChecking)
            {
                cout << "Your password contain space. Please input your password again.\n";
                continue;
            }

            cout << "Please confirm your password: ";
            getline(cin, confirmPassword);

            if (password != confirmPassword)
            {
                cout << "Both password aren't same. Please input your password again.\n";
            }

        } while (!spaceChecking || password != confirmPassword);

        // Open and Edit file. Store data into 'user data.txt'
        ofstream editFile("user data.txt", ios::app);

        editFile << "User #" << userCount << "\n";
        editFile << "Username: " << userName << "\n";
        editFile << "Password: " << password << "\n";
        editFile << "------------------------" << "\n";

        editFile.close();

        cout << "Data stored successfully!\n";
    }

    bool userLogin()
    {
        // Asking for user data
        cout << "Please input your username: ";
        getline(cin, userName);

        cout << "Please input your password: ";
        getline(cin, password);

        ifstream readFile("user data.txt");

        if (!readFile.is_open())
        {
            cout << "Error to open file!\n";
            return false;
        }

        string fileLine, storedUsername, storedPassword;
        while (getline(readFile, fileLine))
        {
            if (fileLine.find("Username:") != string::npos)
            {
                storedUsername = fileLine.substr(fileLine.find(":") + 2);

                // Read next line to find password
                getline(readFile, fileLine);
                if (fileLine.find("Password:") != string::npos)
                {
                    storedPassword = fileLine.substr(fileLine.find(":") + 2);

                    // Check credentials
                    if (storedUsername == userName && storedPassword == password)
                    {
                        readFile.close();
                        cout << "Congrats Login Successfully!\n";
                        return true;
                    }
                }
            }
        }
        // incase wrong username or password
        readFile.close();
        cout << "Unable to Login. Invalid Username or Password.\n";
        return false;
    };
};