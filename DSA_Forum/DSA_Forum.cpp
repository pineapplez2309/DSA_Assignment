#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "List1.h"
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

fstream& GotoLine(fstream& file, unsigned int num) {
    file.seekg(std::ios::beg);
    for (int i = 0; i < num - 1; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return file;
}

void posts(string topicchoice) {
    cout << "\n";
    cout << "\n";
    cout << "Topic: " + topicchoice << endl;
    cout << "\n";
    cout << "Posts:" << endl;
}

void topicmenu() {
    int inttchoice = 0;
    string tchoice;
    std::cout << "\nFood Forum\n\n";
    fstream file("Topic.txt");
    string topic;
    int count = 1;
    while (!file.eof()) {
        getline(file, topic);
        std::cout << count << ". " << topic << endl;
        count++;
    }
    std::cout << endl;
    std::cout << "Enter \"new\" to enter a new topic: " << endl;
    cin >> tchoice;
    bool check = isNumber(tchoice);
    if (check == false) {
        if (tchoice == "new") {
            Createtopic();
        }
        else {
            cout << "Text entered is not an option!" << endl;
            topicmenu();
        }
    }
    else {
        inttchoice = stoi(tchoice);
        if (inttchoice > count-1 || inttchoice <= 0) {
            cout << "Please choose a number that correspond to the choice avaliable!" << endl;
            topicmenu();
        }
        else {
            string topicchoice;
            GotoLine(file, inttchoice);
            file >> topicchoice;
            posts(topicchoice);
        }
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
            cout << "\nPlease enter a number!" << endl;
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
            cout << "\nPlease enter either 1 or 2!" << endl;
            main();
        }

       
 }
 string* split(string str, char del) {
     string temp = "";
     static string tempArray[5];
     int counter = 0;
     for (int i = 0; i < (int)str.size(); i++) {
         if (str[i] != del) {
             temp += str[i];
         }
         else {
             if (str[i] != '\n')
             {
                 tempArray[counter] = temp;
                 temp = "";
                 counter++;
             }

         }
     }
     tempArray[counter] = temp;
     return tempArray;
 }
 //Creates a post if not found in database.Input is name of topic fileand username.
 void createPost(string fileName, string username)
 {
	 string line;
	 ifstream file;
	 string name;
	 string content;
	 int counter = 0;
	 file.open(fileName + ".txt");
	 if (!file)
	 {
		 ofstream file2(fileName + ".txt");
		 file2.close();
	 }
	 file.close();
	 string postName;
	 cout << "Topic Name(0 to exit): ";
	 cin.ignore();
	 getline(cin, postName);
	 if (postName != "0")
	 {
		 file.open(fileName + ".txt");
		 while (getline(file, line))
		 {
			 string* array = split(line, '`');
			 if (postName == array[1])
			 {
				 cout << "Post already exists!" << endl;
				 return;
			 }
		 }
		 cout << endl;
		 ofstream file2;
		 time_t raw_time;
		 time(&raw_time);

		 // Convert to tm (struct tm)
		 tm time_info;
		 localtime_s(&time_info, &raw_time);
		 string date = to_string(time_info.tm_mday) + "/" + to_string(time_info.tm_mon + 1) + "/" + to_string(time_info.tm_year + 1900);
		 string time = to_string(time_info.tm_hour) + ":" + to_string(time_info.tm_min) + ":" + to_string(time_info.tm_sec);
		 file2.open(fileName + ".txt", ios::app);
		 string combined = postName + "`" + username + "`" + date + "`" + time + "\n";
		 file2 << combined;
		 cout << "Post created" << endl;
		 file2.close();
	 }

 }
 
 /*
 void replyPost(string fileName, string username)
 {
	 string line;
	 ifstream file;


	 string name;
	 string content;
	 file.open(fileName + ".txt");
	 if (!file)
	 {
		 ofstream file2(fileName + ".txt");
		 file2.close();
	 }
	 ofstream file2;
	 file2.open(fileName + ".txt", ios::app);
	 string reply;
	 cout << "Replying: ";
	 cin.ignore();
	 getline(cin, reply);
	 if (reply != "0")
	 {
		 cout << endl;
		 time_t raw_time;
		 time(&raw_time);

		 tm time_info;
		 localtime_s(&time_info, &raw_time);
		 string date = to_string(time_info.tm_mday) + "/" + to_string(time_info.tm_mon + 1) + "/" + to_string(time_info.tm_year + 1900);
		 string time = to_string(time_info.tm_hour) + ":" + to_string(time_info.tm_min) + ":" + to_string(time_info.tm_sec);
		 string combined = to_string(postList.getLength() + 1) + "`" + username + "`" + reply + "`" + date + "`" + time + "\n";
		 file2 << combined;
		 cout << "Reply sent" << endl << endl;
		 file2.close();
	 }

 }
 */