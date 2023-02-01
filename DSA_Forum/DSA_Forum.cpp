#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "List.h"
using namespace std;

void Createtopic();

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


void topicmenu() {
    string choice;
    std::cout << "\nFood Forum\n\n";
    ifstream file("Topic.txt");
    string topic;
    int count = 1;
    while (!file.eof()) {
        getline(file, topic);
        std::cout << count << ". " << topic << endl;
        count++;
    }
    std::cout << endl;
    std::cout << "Enter \"new\" to enter a new topic: " << endl;
    cin >> choice;
    if (choice == "new") {
        Createtopic();
    }
}

void Createtopic() {
    string topic;

    cout << "\nEnter a new topic: "; cin >> topic;

    ofstream file;
    file.open("Topic.txt", ios_base::app);
    file << "\n"<<topic;
    file.close();
    cout << "\n";
    topicmenu();
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
                topicmenu();
            }
            else
            {
                cout << "Failed to login!\n" << endl;
                main();
            }
        }
        else
        {
            cout << "Please enter either 1 or 2!\n";
            main();
        }
       
 }

