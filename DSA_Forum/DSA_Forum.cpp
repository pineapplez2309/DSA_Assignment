#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;


/*bool IsLoggedIn() {
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
}*/

bool authenticate(const string& username, const string& password) {
    std::ifstream file("Profile.txt");
    std::string fusername, fpassword;

    while (file) {
        getline(file, fusername, ';'); // use ; as delimiter
        getline(file, fpassword); // use line end as delimiter
        if (fusername == username && fpassword == password)
            return true;
    }

    return false;
}

bool isNumber(string Schoice) {
    regex e("^-?\\d+");
    if (regex_match(Schoice, e)) return true;
    else return false;
}

 int main()   {
        string Schoice;
        int choice = 0;
        cout << "1:Register\n2:Login\nYour Choice: "; cin >> Schoice;
        bool check = isNumber(Schoice);
        if (check == true)
        {
            choice = stoi(Schoice);
        }
        else
        {
            cout << "Please enter a number!\n";
            main();
        }
       
        if (choice == 1)
        {
            string username, password;

            cout << "Enter a username: "; cin >> username;
            cout << "Enter a password: "; cin >> password;

            ofstream file;
            file.open("Profile.txt", ios_base::app);
            file << username << ";" << password << endl;
            file.close();
            cout << "\n";
            main();
        }
        else if (choice == 2)
        {
            string username, password;

            cout << "Enter a username: "; cin >> username;
            cout << "Enter a password: "; cin >> password;
            bool status = authenticate(username, password);
            if (status == true)
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
        else
        {
            cout << "Please enter either 1 or 2!\n";
            main();
        }
       
 }

