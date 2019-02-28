#include "User.h"

User::User(string name_,string number_,int id_,string filename)
{
    name = name_;
    number = number_;
    id = id_;

    file.open(filename, std::ios_base::app);
    file <<id<<" "<<name<<" "<<number << endl;
}

User::~User()
{
}