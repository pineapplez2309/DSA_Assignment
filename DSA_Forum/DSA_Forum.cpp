#include <iostream>
#include <fstream>
#include <string>
using namespace std;
/*
int main()
{
    
    int choice;
    cout << "Forum\n" << endl;
    cout << "1. C++ Programming" << endl;
    cout << "2. Battle Cats" << endl;
    cout << "What's your choice?" << endl;
    cin >> choice;
    if (choice == 1)
        cout << "I love C++!";
    else
        cout << "CATS!" << endl;

    fstream newfile;
    newfile.open("Profile.txt", ios::out);  // open a file to perform write operation using file object
    if (newfile.is_open()) { //checking whether the file is open {
        newfile << "Username: Denzel Lee \nPassword: Pass123\n";
    }//inserting text
        newfile.close(); //close the file object
    
    newfile.open("Profile.txt", ios::in); //open a file to perform read operation using file object
    if (newfile.is_open()) { //checking whether the file is open
        string tp;
        while (getline(newfile, tp)) { //read data from file object and put it into string.
            cout << tp << "\n"; //print the data of the string
        }
        newfile.close(); //close the file object.
    }
}
*/

    bool IsLoggedIn()
    {
        string username, password, un, pw;

        cout << "Enter username: "; cin >> username;
        cout << "Enter password: "; cin >> password;

        ifstream read("data\\" + username + ".txt");
        getline(read, un);
        getline(read, pw);

        if (un == username && pw == password)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    int main()
    {
        int choice;
        cout << "1:Register\n2:Login\nYour Choice: "; cin >> choice;
        if (choice == 1)
        {
            string username, password;

            cout << "Enter a username: "; cin >> username;
            cout << "Enter a password: "; cin >> password;

            ofstream file;
            file.open("data\\" + username + ".txt");
            file << username << endl << password;
            file.close();

            main();
        }
        else if (choice == 2)
        {
            bool status = IsLoggedIn();

            if (status)
            {
                cout << "Successfully logged in" << endl;
                system("pause");
                return 1;
            }
            else
            {
                cout << "Failed to login!" << endl;
                system("Pause");
                return 0;
            }
        }
    }

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
