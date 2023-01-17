#include "HashTable.h"
#include "WordEntry.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable (int s) {
    //create an array of lists of wordentry
    size = s;
    hashTable = new list<WordEntry>[size];
}


/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to 
*  ensure array index doesn't go out of bounds
*/
int HashTable::computeHash(const string &s) {
    int val = 0; 
    int len = s.size();

    for(int i = 0; i < len; ++i) {
        val += s[i];
    }

    //create a value from the string and compute hash using modulus and size arr

    return val % size;
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void HashTable::put(const string &s, int score) {
    //store bucket index as an int
    int bucket = computeHash(s);
    
    if(contains(s)) {
        //if the list at index bucket contains the string to insert
        //then we must increment the counter and nothing else
        
        //iterators to traverse the list
        list<WordEntry>::iterator itr;
        itr = hashTable[bucket].begin();

        //traverse the list until we find the instance of the str and increment
        for(; itr != hashTable[bucket].end(); itr++) {
            if(itr->getWord() == s) {
                itr->addNewAppearance(score);
            }
        }        
    } else {
        /* if the word does not already exist
        create a new wordEntry object using the string and the rating
        and push this object into the back of the list at bucket index*/
        WordEntry * newEntry = new WordEntry(s, score);
        hashTable[bucket].push_back(*newEntry);        
    }
}

/* getAverage
*  input: string word 
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/

double HashTable::getAverage(const string &s) {
    /*save the index of the bucket as an int, and define the 
    return variable as 2.0 by default if avg cannot be foudn*/
    int bucket = computeHash(s);
    double result = 2.0;
    
    if(!contains(s)) {
        /*if the word does note exist, return 2.0*/
        return result;
    } else {
        /*if the word does exists, then iterate through the list
        until we come across it, then return its avg value using getAvg*/
        list<WordEntry>::iterator itr;
        itr = hashTable[bucket].begin();

        for(; itr != hashTable[bucket].end(); itr++) {
            if(itr->getWord() == s) {
                //set the return variable equal to the value of the getAvg getter func
                result = itr->getAverage();
            }
        }
    }

    return result;
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(const string &s) {
    int bucket = computeHash(s);

    /*if the list at the specified bucket is not empty, we can assume that
    word has a chance of existing within it*/
    if(!(hashTable[bucket].empty())) {
        list<WordEntry>::iterator itr;
        itr = hashTable[bucket].begin();

        /*define iterators to traverse the list at this location, if word is found
        return true*/
        for(; itr != hashTable[bucket].end(); ++itr) {
            //cout << bucket << endl;
            cout << itr->getWord();
            if(itr->getWord() == s) {
                return true;
            }
        }        
    }
    //if the list here is empty, word cannot exist->false
    return false;
}