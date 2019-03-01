#include <string.h>   
#include <unistd.h> 
#include <arpa/inet.h> 
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <sys/time.h>
#include <iostream>
#include <sstream>
#include "Handler.h"

#define PORT 2999

using namespace std;

int main(int argc, char * argv[]) 
{
  Handler* h = new Handler();
  int temp = 1;
  int masterSocket, newSocket;
  int i, j, f, sd, md, val;

  int socketForClients[10] = 
  {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
  };  

  //set of socket descriptors  
  fd_set readfds;

  //Welcome message to all that join the server
  char * WelcomeMessage = "\u001b[35;1m Welcome to COS 332 Practical Two\n **********MENU**********\n1. Enter '1 user number' to insert an user\n2. Enter '2' to get a list of all numbers stored\n3. Enter '3 name' to retrieve the specific user details\n4. Enter '4 userId' to remove the user\n5. Enter '5 userId name number' to update user details\n\u001b[0m";
  char * receivedMessage = "The server received the following input: ";
  int lengthOfReceivedMessage = strlen(receivedMessage);

  char buffer[1025]; //Buffer for the data   

  struct sockaddr_in address={0};

  //Create the main socket    
  if ((masterSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
  {
    cout << "\u001b[31m An error has occured while creating the master socket" << endl;
    return -1;
  }
  if (setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &temp, sizeof(temp))) 
  { 
        cout<<"\u001b[31m Error with setsockopt function"<<endl;
        return -1;
  } 
  //Set the port and rest of the information on the address struct
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  int lengthOfTheAddress = sizeof(address);

  //Now we need to bind the socket to PORT 3030
  if (bind(masterSocket, (struct sockaddr * ) & address, sizeof(address)) < 0) 
  {
    cout << "\u001b[31m Error has occured while trying to bind to port "<<PORT<<". Might already be in use" << endl;
    return -1;
  }

  cout << "\u001b[32;1m Port "<<PORT<<" is being listened to. " << endl;
  cout << "\u001b[32;1m Waiting for clients to connect!" << endl;

  if (listen(masterSocket, 5) < 0) 
  {
    cout << " \u001b[31m Some error occured  while trying to set the max number of clients trying to connect" << endl;
    return -1;
  }

  while (1) 
  {
    FD_ZERO( & readfds);

    //Add the main socket to the set
    FD_SET(masterSocket, & readfds);
    md = masterSocket;
    //add the clients to the set
    for (int k = 0; k < 10; k++) 
    {
      sd = socketForClients[k];
      if (sd > 0) 
      {
        FD_SET(sd, & readfds);
      }

      if (sd > masterSocket) 
      {
        md = sd;
      }
    }
    int activity = select(md + 1, & readfds, NULL, NULL, NULL);

    if (FD_ISSET(masterSocket, & readfds)) {
      if ((newSocket = accept(masterSocket, (struct sockaddr * ) & address, (socklen_t * ) & lengthOfTheAddress)) < 0) 
      {
        cout << "\u001b[31m Error in the accepting of new Socket" << endl;
        return -1;
      }

      if (send(newSocket, WelcomeMessage, strlen(WelcomeMessage), 0) != strlen(WelcomeMessage)) 
      {
        cout << " \u001b[31m Welcome message was not sent successfully" << endl;
      } else 
      {
        cout << "\u001b[44m Welcome message was sent\u001b[0m" << endl;
      }
      //Add the newly created socket to the socket array
      f = 0;
      while (f < 10) 
      {
        if (socketForClients[f] == 0) 
        {
          socketForClients[f] = newSocket;
          cout << "\u001b[32;1m Socket list was updated with new connection at index " << f << endl;
          break;
        }
        f++;
      }
    }
    //This is for when clients input 
    f = 0;
    while (f < 10) 
    {
      sd = socketForClients[f];
      if (FD_ISSET(sd, & readfds)) 
      {
        if ((val = read(sd, buffer, 1024)) == 0) 
        {
          //Some client disconnected
          cout << " \u001b[31m Client with port " << ntohs(address.sin_port) << " disconnected from the server" << endl;
          //Delete the client form the clientSocket and close that socket
          close(sd);
          socketForClients[f] = 0;
        } else 
        {
          //The client sent a message
          //First echo back what they said
          //Temnate the string read
          buffer[val] = '\0';         

          //Send input back to user
          send(sd, receivedMessage, strlen(receivedMessage), 0);
          send(sd, buffer, strlen(buffer), 0);

          string arr[4];
          stringstream bufTemp(buffer);
          int temp =0;
           while (bufTemp.good() && temp<4)
           {
              bufTemp >> arr[temp];
              ++temp;
           }
                  
          if(arr[0] == "1")
          {
              //user wants to add
              string name =arr[1];
              string num = arr[2];
              if(h->addUser(name,num))
              {
                cout<<"\u001b[32;1m"<<name<<"'s details have been saved"<<endl;
              }
              else 
              {
                cout<<"\u001b[31m An error occured while trying to store the values"<<endl;
              }
          }
          else if(arr[0] == "2")
          {
              h->getAllUsers(sd);
            // const char* tempor = h->getAllUsers();
            // send(sd,tempor,strlen(tempor),0);
          }
          else if(arr[0] == "3")
          {
              string n = arr[1];
              h->getUser(n,sd);
            // const char* tempor = h->getAllUsers();
            // send(sd,tempor,strlen(tempor),0);
          }
          else if(arr[0] == "4")
          {
              int n = stoi(arr[1]);
              if(h->deleteUser(n,sd))
              {
                cout<<"\u001b[32;1m"<<"User has been deleted"<<endl;
                h->getAllUsers(sd);
              }
              else 
              {
                cout<<"\u001b[31m An error occured while trying to delete the user"<<endl;
              }
              
          }
          else if(arr[0]=="5")
          {
            //update the user
            int n = stoi(arr[1]);
            string name =arr[2];
            string sur = arr[3];
            if(h->updateUser(n,name,sur,sd))
            {
               cout<<"\u001b[32;1m"<<"User has been updated"<<endl;
                h->getAllUsers(sd);
            }
            else 
            {
              cout<<"\u001b[31m An error occured while trying to update the user"<<endl;

            }
          }
        }
      }
      f++;
    }
  }  
  return 0;
}