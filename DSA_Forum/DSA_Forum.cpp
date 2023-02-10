#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "List1.h"
using namespace std;


void Createtopic(string username);

void posts(string username, string topicchoice);

template<class T>
void editReply(string fileName, string username, List<string> postList);


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

//Creates a post if not found in database.Input is name of topic file and username.
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
    cout << "Content of post: ";
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
        string combined = "`" + postName + "`" + username + "`" + date + "`" + time + "`" + "\n";
        file2 << combined;
        cout << "Post created" << endl;
        file2.close();
        posts(username, fileName);
    }

}

//Delete a post if owner of post, input is name of post file. return deletion status
bool deletePost(string fileName)
{
    fileName += ".txt";
    char* char_array = new char[fileName.length() + 1];
    char_array[fileName.length()] = '\0';
    for (int i = 0; i < fileName.length(); i++) {
        char_array[i] = fileName[i];
    }
    bool status = remove(char_array);
    delete[] char_array;
    return status;
}

//Edit a post if owner of post, input is name of post file, username, lists of post, contents of post file. returns name of new file
template<class T>
void editPost(string fileName, string username, List<string> topicContentList)
{
    cout << "Editing post(0 to exit): ";
    string* array = split(fileName, '`');
    string edit;
    cin.ignore();
    getline(cin, edit);
    if (edit != "0")
    {
        string line;
        ifstream file;
        string name;
        string content;
        string newFileName = array[0] + "`" + edit + "`" + username;
        file.open(newFileName + ".txt");
        if (!file)
        {
            ofstream file2(newFileName + ".txt");
            file2.close();
            file2.open(newFileName + ".txt", ios::app);
            for (int i = 0; i < topicContentList.getLength(); i++)
            {
                file2 << topicContentList.get(i);

            }

            file2.close();
            int status = deletePost(fileName);
            if (status == 0)
            {

                string* array = split(fileName, '`');
                file.open(array[0] + ".txt");
                int i = 0;
                while (getline(file, line))
                {
                    if (line == array[1] + "`" + array[2])
                    {
                        string* array = split(newFileName, '`');
                        topicContentList.remove(i);
                        if (i == topicContentList.getLength())
                        {
                            topicContentList.add(array[1] + "`" + array[2]);
                        }
                        else
                        {
                            topicContentList.add(i, array[1] + "`" + array[2]);
                        }
                    }
                    i++;
                }
                file.close();
                file2.open(array[0] + ".txt");
                file2.close(); //remove content of file

                file2.open(array[0] + ".txt", ios::app);

                for (int i = 0; i < topicContentList.getLength(); i++)
                {
                    file2 << topicContentList.get(i) << "\n";

                }
                file2.close();
                cout << "Post edited successfully!" << endl;

            }

            else
            {
                cout << "Error occurred!" << endl;

            }
            //return newFileName;

        }
        else
        {
            cout << "Post already exists" << endl;
        }




    }
}

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

bool postcheck(const string& toppicchoice, const string& post) {
    ifstream file(toppicchoice + ".txt");
    string Post;
    while (file) {
        getline(file, Post, '`');
        auto noSpaceEnd = std::remove(Post.begin(), Post.end(), ' ');
        Post.erase(noSpaceEnd, Post.end());
        cout << Post << endl;
        if (Post == post) {
            return true;
        }
    }
    return false;
}

bool topiccheck(const string& topic) {
    ifstream file("Topic.txt");
    string Topic;

    while (file) {
        getline(file, Topic);
        if (Topic == topic)
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

void topicmenu(string username) {
    int inttchoice = 0;
    string tchoice;
    std::cout << "\nFood Forum\n" << endl;
    cout << "Welcome, " + username << endl;
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
    cout << "Enter \"posts\" to make a new post" << endl;
    cin >> tchoice;
    bool check = isNumber(tchoice);
    if (check == false) {
        if (tchoice == "new") {
            string Username;
            Username = username;
            Createtopic(Username);
        }
        else if (tchoice == "posts") {
            string Username;
            string Tchoice;
            Username = username;
            cout << "Enter the topic to make a post for: ";
            cin >> Tchoice;
            bool status = topiccheck(Tchoice);
            if (status == false) {
                cout << "Please enter a topic that exsits!";
                topicmenu(Username);
            }
            else {
                createPost(Tchoice, Username);

            }
        }
        else {
            cout << "Text entered is not an option!" << endl;
            string Username;
            Username = username;
            topicmenu(Username);
        }
    }
    else {
        inttchoice = stoi(tchoice);
        if (inttchoice > count - 1 || inttchoice <= 0) {
            cout << "Please choose a number that correspond to the choice avaliable!" << endl;
            string Username;
            Username = username;
            topicmenu(Username);
        }
        else {
            string Username;
            string topicchoice;
            Username = username;
            GotoLine(file, inttchoice);
            file >> topicchoice;
            posts(Username, topicchoice);
        }
    }
}

void PostReply(string fileName, string username)
{
    string line;
    ifstream file;
    List<string> postList;
    string name;
    string content;
    file.open(fileName + "Reply" + ".txt");
    if (!file)
    {
        ofstream file2(fileName + "Reply" + ".txt");
        file2.close();
    }
    ofstream file2;
    file2.open(fileName + "Reply" + ".txt", ios::app);
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

void search(string username,string topicchoice) {
    ifstream file;
    string Search;
    string result;
    string result2;
    int offset;
    int i = 1;
    file.open(topicchoice + ".txt");
    cout << "Type the word you would like to search (Case senstitive): ";
    cout << "\n";
    cin >> Search;
    cout << "\n";
    while (!file.eof()) {
        getline(file, result, '`');
        result2 = result;
        auto noSpaceEnd = std::remove(result2.begin(), result2.end(), ' ');
        result2.erase(noSpaceEnd, result2.end());
        if (offset = result.find(Search, 0) != string::npos) {
            cout << i << ". " << result << " (Copy and paste if you want to reply to this topic: " << result2 << ")" << endl;
            i++;
        }
    }
    cout << "\n";
    string Username;
    Username = username;
    posts(Username, topicchoice);

}


void posts(string username, string topicchoice) {
    string replychoice;
    ifstream file;
    string Posts;
    cout << "\n";
    cout << "\n";
    cout << "Topic: " + topicchoice << endl;
    cout << "\n";
    cout << "Posts:\n\n(Format is:\nTitle:\nUser which posted:\nDate posted:\nTime posted:)" << endl;
    file.open(topicchoice + ".txt");
    while (file) {
        getline(file, Posts, '`');
        cout << Posts << endl;
    }
    cout << "\nEnter \"reply\" to make a reply, \"search\" to search, \"edit\" to edit post, \"delete\" to delete a post or \"back\" to go back: ";
    cin >> replychoice;
    bool check = isNumber(replychoice);
    if (check == false) {
        if (replychoice == "reply") {
            string pchoice;
            cout << "Enter name of post you would like to reply too (Without spaces and case sensitive E.g.,Muttoncurryforpotato): ";
            cin >> pchoice;
            bool status = postcheck(topicchoice,pchoice);
            if (status == false) {
                string Username;
                string Topicchoice;
                Username = username;
                Topicchoice = topicchoice;
                cout << "Please Enter a topic that exists!" << endl;
                posts(Username, Topicchoice);
            }
            else {
                string Username;
                Username = username;
                PostReply(pchoice, Username);
            }
        }
        else if (replychoice == "back") {
            string Username;
            Username = username;
            topicmenu(Username);
        }
        else if (replychoice == "search") {
            string Topicchoice;
            Topicchoice = topicchoice;
            string Username;
            Username = username;
            search(Username, Topicchoice);
        }
        else if (replychoice == "edit") {
            /*string result;
            string Topicchoice;
            Topicchoice = topicchoice;
            string Username;
            Username = username;
            List<string> Postlist;
            file.open(topicchoice + ".txt");
            while (!file.eof()) {
                getline(file, result, '`');
                Postlist.add(result);
            }
            editPost(Topicchoice, Username, Postlist);*/
        }
        else if (replychoice == "delete") {
            string Topicchoice;
            Topicchoice = topicchoice;
            bool status = deletePost(Topicchoice);
            if (status == true) {
                cout << "Delete success" << endl;
            }
            else {
                cout << "Delete failed" << endl;
            }
        }
        else {
            cout << "Please enter a valid option!\n" << endl;
            string Username;
            string Topicchoice;
            Username = username;
            Topicchoice = topicchoice;
            posts(Username, Topicchoice);
        }
    }
    else {
        cout << "Don't input a number!" << endl;
        string Username;
        string Topicchoice;
        Username = username;
        Topicchoice = topicchoice;
        posts(Username, Topicchoice);
    }
}

void Createtopic(string username) {
    string topic;

    cout << "\nEnter a new topic: "; cin >> topic;

    ofstream file;
    file.open("Topic.txt", ios_base::app);
    file << "\n"<<topic;
    file.close();
    cout << "\n";
    string Username;
    Username = username;
    topicmenu(Username);
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
                topicmenu(username);
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

 //Displays content of selected post. Input is name of post file. Returns Lists of replies
 List<string> DisplayContent(string fileName)
 {
     string line;
     ifstream file;
     string name;
     string username;
     string content;
     int counter = 0;
     List<string> postList;
     file.open(fileName + ".txt");
     if (!file)
     {
         ofstream file2(fileName + ".txt");
         file2.close();
     }
     cout << fileName;
     string* array = split(fileName, '`');
     name = array[1];
     username = array[2];


     cout << name << endl << "------------------------------------------------------------------------------------" << endl;

     while (getline(file, line))
     {
         string* array = split(line, '`');
         name = array[1];
         content = array[2];
         string date = array[3];
         string time = array[4];
         string combined = to_string(counter + 1) + "`" + name + "`" + content + "`" + date + "`" + time + "\n";
         cout << to_string(counter + 1) << ". " << name << ": " << content << "\t\t\t\t\t\t" << date << " " << time << endl;

         postList.add(combined);


         counter++;

     }
     file.close();
     return postList;
 }
 


 template<class T>
 void editReply(string fileName, string username, List<string> postList)
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
     file.close();

     string reply;
     cout << "Choose reply to edit: ";
     string choice;
     cin >> choice;
     cout << endl;
     string* array = split(postList.get(stoi(choice) - 1), '`');
     if (array[1] == username) //Author
     {
         cout << "Edited reply: ";
         string editedReply;
         cin.ignore();
         getline(cin, editedReply);
         cout << endl;
         postList.remove(stoi(choice) - 1);
         string combined = array[0] + "`" + username + "`" + editedReply + "`" + array[2] + "`" + array[3] + "\n";
         if (stoi(choice) == postList.getLength() + 1)
         {
             postList.add(combined);
         }
         else
         {
             postList.add(stoi(choice) - 1, combined);
         }

         ofstream file2;

         file2.open(fileName + ".txt");
         file2.close(); //remove content of file

         file2.open(fileName + ".txt", ios::app);

         for (int i = 0; i < postList.getLength(); i++)
         {
             file2 << postList.get(i);

         }
         cout << "Edited" << endl << endl;;
         file2.close();
     }
     else //Not author
     {
         cout << "You are not the author!" << endl;
     }




 }
 //Delete a reply to a post if owner of reply. Input is name of post file, username and contents of post.
 template<class T>
 void deleteReply(string fileName, string username, List<string> postList)
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
     file.close();

     string reply;
     cout << "Choose reply to delete(0 to exit): ";
     int choice;
     cin >> choice;
     if (choice == 0)
     {

     }
     else
     {
         string* array = split(postList.get(choice - 1), '`');
         if (array[1] == username) //Author
         {

             postList.remove(choice - 1);
             ofstream file2;
             file2.open(fileName + ".txt");
             file2.close(); //Reset contents

             file2.open(fileName + ".txt", ios::app);
             for (int i = 0; i < postList.getLength(); i++)
             {
                 file2 << postList.get(i);
             }

             file2.close();


         }
         else //Not author
         {
             cout << "You are not the author of this reply." << endl;
         }
     }





 }

 //Edit a post if owner of post, input is name of post file, username, lists of post, contents of post file. returns name of new file
 /*template<class T>
 string editPost(string fileName, string username, List<string> postList, List<string> topicContentList)
 {
     cout << "Editing post(0 to exit): ";
     string* array = split(fileName, '`');
     string edit;
     cin.ignore();
     getline(cin, edit);
     if (edit != "0")
     {
         string line;
         ifstream file;
         string name;
         string content;
         string newFileName = array[0] + "`" + edit + "`" + username;
         file.open(newFileName + ".txt");
         if (!file)
         {
             ofstream file2(newFileName + ".txt");
             file2.close();
             file2.open(newFileName + ".txt", ios::app);
             for (int i = 0; i < postList.getLength(); i++)
             {
                 file2 << postList.get(i);

             }

             file2.close();
             int status = deletePost(fileName);
             if (status == 0)
             {

                 string* array = split(fileName, '`');
                 file.open(array[0] + ".txt");
                 int i = 0;
                 while (getline(file, line))
                 {
                     if (line == array[1] + "`" + array[2])
                     {
                         string* array = split(newFileName, '`');
                         topicContentList.remove(i);
                         if (i == topicContentList.getLength())
                         {
                             topicContentList.add(array[1] + "`" + array[2]);
                         }
                         else
                         {
                             topicContentList.add(i, array[1] + "`" + array[2]);
                         }
                     }
                     i++;
                 }
                 file.close();
                 file2.open(array[0] + ".txt");
                 file2.close(); //remove content of file

                 file2.open(array[0] + ".txt", ios::app);

                 for (int i = 0; i < topicContentList.getLength(); i++)
                 {
                     file2 << topicContentList.get(i) << "\n";

                 }
                 file2.close();
                 cout << "Post edited successfully!" << endl;

             }

             else
             {
                 cout << "Error occurred!" << endl;

             }
             //return newFileName;

         }
         else
         {
             cout << "Post already exists" << endl;
         }




     }
     return fileName;
 }*/