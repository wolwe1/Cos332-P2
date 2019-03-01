#include "Handler.h"

Handler::Handler()
{
    string line;
    userCount = 0;

    file.open("Users.txt");
    while (getline(file, line))
        ++userCount;

    filename = "Users.txt";
    file.close();

    loadUsers();
}

Handler::~Handler()
{
}

bool Handler::addUser(string name,string num){

    User* newUser = new User(name,num,userCount++);
    newUser->write(filename); // No longer write on creation because i want to create users in functions without adding
    delete newUser;
    return true;
}

bool Handler::deleteUser(int id){

     vector<User*>::iterator it = users.begin();
 
    for(;it < users.end();it++){
        if((*it)->getId() == id){
            users.erase(it);
            if(rewriteFile())
            return true;
            
        } 
    }
    return false;
}

vector<User*> Handler::loadUsers(){

    file.open("Users.txt");
    vector<User*> users_;
    string line,data,data2;
    int id;
    User* temp;

    if (file){
        int count = 0;

        while (count < userCount) {

        file >> line;
        id = stoi(line);

        file >> line;
        data = line;

        file >> line;
        data2 = line;

        temp = new User(data,data2,id);
        users_.insert(users_.end(),temp);
        count++;
    }
 }
file.close();
this->users = users_;

return users;

}
User* Handler::getUser(int id){

 vector<User*>::iterator it = users.begin();
 
    for(;it < users.end();it++){
        if((*it)->getId() == id){
            return (*it);
        }
        
    }
    return nullptr;
}

bool Handler::updateUser(int id,string name,string num){

    User* user;

    if( (user = getUser(id)) != nullptr){
        user->changeDetails(name,num);
        return true;
    }
    return false;
}
string* Handler::getAllUsers(){ //Completely new way thanks to loadUsers but I maintained your array adding

    string arr[userCount];
    int count = 0;

    if (file){

    vector<User*>::iterator it = users.begin();

    cout << "\n=============== Users ==============="<< endl;
 
    for(;it < users.end();it++){
        
        arr[count++] = (*it)->print();
        cout << (*it)->print() << endl;
    }
 }

return arr;
}

bool Handler::rewriteFile(){

    file.open(filename,ofstream::trunc); //Clear file
    file.close();

    vector<User*>::iterator it = users.begin();
     
    for(;it < users.end();it++){
     (*it)->write(filename);
    }

    return true;
}