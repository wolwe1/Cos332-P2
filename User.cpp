#include "User.h"

User::User(string name_,string number_,int id_)
{
    name = name_;
    number = number_;
    id = id_;
}
void User::write(string filename){
    file.open(filename, std::ios_base::app);
    file <<id<<" "<<name<<" "<<number << endl;
}

string User::print(){
    string str = "ID:"+to_string(id)+" Name:"+name+" Number:"+number;
    
    return str;
}

int User::getId(){
    return this->id;
}
string User::getName()
{
    return this->name; 
}
string User::getNumber()
{
    return this->number;
}
string User::getAllDetails()
{
    return to_string(id)+" "+name+" " +number;
}
bool User::changeDetails(string name,string num){
    this->name = name;
    this->number = num;
    
    return true;
}

User::~User()
{
}