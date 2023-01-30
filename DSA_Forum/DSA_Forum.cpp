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

bool IsLoggedIn()   {
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

bool authenticate(const string& username, const string& password) {
    std::ifstream file("Profile.txt");
    std::string fusername, fpassword;

    while (file) {
        getline(file, fusername, ';'); // use ; as delimiter
        getline(file, fpassword); // use line end as delimiter
        // remember - delimiter readed from input but not added to output
        if (fusername == username && fpassword == password)
            return true;
    }

    return false;
}

 int main()   {
        int choice;
        cout << "1:Register\n2:Login\nYour Choice: "; cin >> choice;
        if (choice == 1)
        {
            string username, password;

            cout << "Enter a username: "; cin >> username;
            cout << "Enter a password: "; cin >> password;

            ofstream file;
            file.open("Profile.txt", ios_base::app);
            file << username << ";" << password << endl;
            file.close();
            main();
        }
        else if (choice == 2)
        {
            string username, password;

            cout << "Enter a username: "; cin >> username;
            cout << "Enter a password: "; cin >> password;
            bool status = authenticate(username, password);
            return (int)authenticate(username, password);
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

