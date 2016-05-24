// Name: Ben Wilfong
// File Name: whodoneit.cpp
// Date: 17 November, 2014
// Program Description:
//     This program implements the queue ADT to figure out
// "who done it" in a police case. A file containing
// the friends of each person in a town is accepted
// and processed to figure out who the criminal is
// in the case. By using a breadth-first search,
// we are able to figure out exactly who knows about
// the crime in a network of friends for each person.
// Whichever network matches the police's known-network
// of people who know about the crime will be deemed
// to be the network of the criminal.


#include <iostream>

using namespace std;

#include "queue.h"
#include <fstream>
#include <string>
#include <cstring>

void createKnowList(char, string[], int[]);
bool isTheVillain(int[], const int[]);

int main()
{
    string friendList[26] = ""; // Will hold the friend data for each person
    int i = 0;

    ifstream friendFile;
    friendFile.open("friends.txt");

    if (!friendFile)
        cout << "File open failed!" << endl;

    for (int i = 0; i < 26; i++)
        getline(friendFile, friendList[i]); // populate array elements
                                            // with "friend" lists

    const int policeKnowList[26] = {1,1,1,1,1,0,0,0,1,1,1,1,1,
                                    1,1,1,1,1,1,1,1,1,1,1,1,1};

    // ^^this array contains info on who knows about the robbery

    for (int i = 0; i < 26; i++)
    {
        int suspectKnowList[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,
                                   0,0,0,0,0,0,0,0,0,0,0,0,0};

        char suspect = (char)(i + 65); // create index for suspect
                                       // to be checked

        createKnowList(suspect, friendList, suspectKnowList);

        if (isTheVillain(suspectKnowList, policeKnowList)) // check lists
        {
            cout << "I know who the burglar is, it is "
                 << suspect << endl;

            break; // I checked to see if it found the correct suspect
                   // without this statement.
                   // I added it afterward for time efficiency in the
                   // code. (If its S, then why check T,U,V...?)
        }
    }// end for
}// end main()


/*
   The createKnowList() function creates a list by first marking
   the suspects position in the suspectKnowList array and then
   adds the suspect to a queue. Then, a loop executes until
   all of the suspect's friends and friend's friends (and so on)
   are marked on the suspectKnowList array. This code WILL NOT
   add a suspect to the queue if he/she has already been
   marked on the suspectKnowList array. Because of this,
   when the queue is empty, all suspects have been accounted for.

   For the "friends list," the string holding the suspect's
   friends is converted into a c-style string and then processed.
   This is to be able to account for any white space in the string,
   and to be able to handle the friend-string character-by-character.
*/

void createKnowList(char suspect, string friendList[26], int suspectKnowList[])
{
    int suspectIndex = (int)(suspect - 65);
    Queue<char> friendQueue;

    suspectKnowList[suspectIndex] = 1; // mark the suspect as known

    friendQueue.enqueue(suspect); // add the suspect to the queue

    while(!friendQueue.isEmpty())
    {
        char temp;

        friendQueue.dequeue(temp);

        suspectIndex = (int)(temp - 65); // get new sus. index to obtain friend's list

        char* friendOfSuspect = new char[friendList[suspectIndex].length() + 1];
        strcpy(friendOfSuspect, friendList[suspectIndex].c_str());

        // ^^ this creates a c-style string of the suspect's friends   ^^
        // ^^ so we can enqueue the friends of the suspect more easily.^^

        for (int i = 0; i < friendList[suspectIndex].length(); i++) // check friends list
        {
            if (friendOfSuspect[i] >= 'A' && friendOfSuspect[i] <= 'Z') // making sure the character is a letter
            {
                int friendIndex = (int)(friendOfSuspect[i] - 65); //get friend's index

                if (suspectKnowList[friendIndex] == 0) // if the friend hasn't been handled
                {
                    suspectKnowList[friendIndex] = 1; // mark it as checked
                    friendQueue.enqueue(friendOfSuspect[i]); // enqueue to be processed
                }
            }
        } // end for loop
    }// end while loop
}// end createKnowList()


/*
    The isTheVillain() function simply accepts the newly create
    suspectKnowList and the police's existing know list and checks
    to see if they are equal. If at any time, while processing,
    the arrays are found to be NOT EQUAL, the loop breaks and
    the isGuilty flag is set to false and returned. However,
    if the loop is never broken, then all elements were equal
    and we have found our burglar.
*/

bool isTheVillain(int suspectKnowList[26], const int policeKnowList[26])
{
    bool isGuilty = true;

    for (int i = 0; i < 26; i++)
    {
        if (suspectKnowList[i] != policeKnowList[i])
        {
            isGuilty = false; // suspect is not the villain
            break; // stop iterating loop
        }
    }

    return isGuilty; // in this function, the suspect is guilty until
                     // proven innocent, ie a discrepancy b/t the
                     // police list and the suspect list is found
}// end isTheVillain()
