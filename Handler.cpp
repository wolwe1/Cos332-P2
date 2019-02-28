#include "Handler.h"

Handler::Handler()
{
    string line;
    userCount = 0;

    file.open("Users.txt");
    while (getline(file, line))
        ++userCount;

    cout << userCount;
    filename = "Users.txt";
    file.close();
}

Handler::~Handler()
{
}

bool Handler::addUser(string name,string num){

    User* newUser = new User(name,num,userCount++,filename);
    delete newUser;
    return true;
}

bool Handler::deleteUser(int){
    return true;
}

User* Handler::getUser(int){
return nullptr;
}

User** Handler::getAllUsers(){

    file.open("Users.txt");
    string line;
    
    if (file){

        cout << "\n=============== Users ==============="<< endl;
        int count = 0;

        while (count < userCount) {

        file >> line;
        temp.id = stoi(line);

        file >> line;
        temp.name = line;

        file >> line;
        temp.number = line;

        temp.user = "ID:"+ to_string(temp.id) + " "+temp.name +" "+ temp.number;

        cout << temp.user << endl;
        count++;
    }
 }
file.close();

return nullptr;
}