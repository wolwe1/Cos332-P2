#include "Handler.h"

Handler::Handler()
{
    string line;
    userCount = 0;

    file.open("Users.txt");
    while (getline(file, line))
        ++userCount;

    //cout << userCount;
    filename = "Users.txt";
    file.close();
    loadUsers();
}

Handler::~Handler()
{
}

bool Handler::addUser(string name,string num){

    User* newUser = new User(name,num,userCount++);
    newUser->write(filename);
    delete newUser;
    return true;
}

bool Handler::deleteUser(int id,int sd)
{
    vector<User*>::iterator it = users.begin();
 
    for(;it < users.end();it++){
        if((*it)->getId() == id){
            users.erase(it);
            
            if(rewriteFile())
            {
                char* a= "\u001b[32;1m User has been deleted\n\u001b[0m";
                send(sd,a,strlen(a),0);
                return true;  
            }                      
        } 
    }
    return false;
}

User* Handler::getUser(string n,int sd)
{
    loadUsers();
    vector<User*>::iterator it = users.begin();
    char * arr ="\u001b[36m=============== User ===============\n";
    char* newline="\n\u001b[0m";

            send(sd,arr,strlen(arr),0);
    for(;it < users.end();it++){
        if((*it)->getName() == n)
        {
            cout << "\u001b[36m\n=============== User ===============\u001b[0m"<< endl;
            cout <<"\u001b[36m"<<(*it)->getId()<<" "<<(*it)->getName()<<" "<<(*it)->getNumber()<< endl;
            string s =(*it)->getAllDetails();
            char* a = &s[0u];
            send(sd,a,strlen(a),0);
            send(sd,newline,strlen(newline),0);
            return (*it);
        }
        
    }
//     return nullptr;
//     file.open("Users.txt");
//     string line;
    
//     send(sd,arr,strlen(arr),0);

//     if (file){

//         cout << "\u001b[36m\n=============== User ==============="<< endl;
//         int count = 0;

//         while (count < userCount) {

//         file >> line;
//         temp.id = stoi(line);

//         file >> line;
//         temp.name = line;

//         file >> line;
//         temp.number = line;

//         temp.user = "ID:"+ to_string(temp.id) + " "+temp.name +" "+ temp.number;

//         char* a = &temp.user[0u];
//         if(temp.name == n)
//         {  
//             cout << temp.user << endl;
//             send(sd,a,strlen(a),0);
//             send(sd,newline,strlen(newline),0);
//             return nullptr;
//         }
        
//         count++;
//     }
//  }
// file.close();
return nullptr;
}

User* Handler::getAllUsers(int sd){

    loadUsers();
    vector<User*>::iterator it = users.begin();
    char * arr ="\u001b[36m=============== Users ===============\n";
    char* newline="\n\u001b[0m";
    cout << "\u001b[36m\n=============== Users ==============="<< endl;

            send(sd,arr,strlen(arr),0);
    for(;it < users.end();it++)
    {
            
            cout <<"\u001b[36m"<<(*it)->getId()<<" "<<(*it)->getName()<<" "<<(*it)->getNumber()<< endl;
            string s ="\u001b[36m"+(*it)->getAllDetails();
            char* a = &s[0u];
            send(sd,a,strlen(a),0);
            send(sd,newline,strlen(newline),0);     
    }
    return (*it);
//     file.open("Users.txt");
//     string line;
//     char * arr ="\u001b[34m =============== Users ===============\n";
//     char* newline="\n";
//     send(sd,arr,strlen(arr),0);
//     if (file){

//         cout << "\u001b[34m\n=============== Users ==============="<< endl;
//         int count = 0;

//         while (count < userCount) {

//         file >> line;
//         temp.id = stoi(line);

//         file >> line;
//         temp.name = line;

//         file >> line;
//         temp.number = line;

//         temp.user = "ID:"+ to_string(temp.id) + " "+temp.name +" "+ temp.number;

//         char* a = &temp.user[0u];

//         cout << temp.user << endl;
//         send(sd,a,strlen(a),0);
//         send(sd,newline,strlen(newline),0);
//         count++;
//     }
//  }
// file.close();
// //return arr;
}

bool Handler::rewriteFile(){

    loadUsers();
    file.open(filename,ofstream::out | std::ofstream::trunc); //Clear file
    file.close();
    
    vector<User*>::iterator it = users.begin();
     
    for(;it < users.end();it++){
     (*it)->write(filename);
    }

    return true;
}

bool Handler::updateUser(int id,string name,string num,int sd){

    User* user;

    if( (user = getUser(id)) != nullptr){
        user->changeDetails(name,num);

        char* a = "\u001b[32;1mUser has been updated\u001b[0m";
        send(sd,a,strlen(a),0);
        rewriteFile();
        return true;
    }
    return false;
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