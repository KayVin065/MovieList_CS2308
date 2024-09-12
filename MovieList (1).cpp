// File Name: MovieList.cpp
//
// Author: Kayla Vincent
// Collaborators: Makenna Wilson
// Date: 4/1/2023
// Assignment Number: 5
// CS 2308 Spring 2023
//
// Defines the member functions of the MovieList class. 
// Includes a default constructor and destructor. The 
// member functions are count, display, addToTop, 
// addToBottom, remove, moveToTop, nextLarger, and 
// displaySorted. The MovieList class allows the user to
// create and manipulate a list of movies, emulating some 
// functionality of a Netflix DVD queue. 

#include <iostream>
#include <fstream>
#include "MovieList.h"
using namespace std;

//***********************************************************
// MovieList(): default constructor for the MovieList class.
//     Takes no arguments, but assigns the private MovieNode
//     top to be NULL
//***********************************************************
MovieList :: MovieList() {
  top = nullptr;
}

//***********************************************************
// ~MovieList(): destructor for the MovieList class. 
//     Deallocates memory assigned to the MovieNodes.
//***********************************************************
MovieList :: ~MovieList() {
  delete top; 
}

//***********************************************************
// count: a function that counts the number of movies added
//     to the Netflix movie queue
// returns: number of movies in the list (int)
//***********************************************************
int MovieList :: count() {
  int count = 0;
  MovieNode *p;
  p = top;

  while(p != nullptr) {
    count++;
    p = p->next;
  }
  
  return count;
}

//***********************************************************
// display: prints the list of movies the user has added
// out: ostream variable to output the movies
// returns: void
//***********************************************************
void MovieList :: display(ostream& out) {
  int count = 0;
  MovieNode *p;
  p = top;

  while(p != nullptr) {
    out << count << ": ";
    out << p->title << endl;
    p = p->next;
    count++;
  }
}

//***********************************************************
// addToTop: adds the user input movie to the top of the list
//     of movies in the Netflix queue
// title: movie title the user wants to add (string)
// returns: void
//***********************************************************
void MovieList :: addToTop(string title) {
  MovieNode *topNode = new MovieNode;
  topNode->title = title; 
  topNode->next = top;
  top = topNode;
}

//***********************************************************
// addToBottom: adds the user input movie to the end of the 
//     list of movies in the Netflix queue
// title: movie title the user wants to add (string)
// returns: void
//***********************************************************
void MovieList :: addToBottom(string title) {
  MovieNode *botNode = new MovieNode;
  botNode->title = title;
  botNode->next = nullptr;
  
  if(top == nullptr) {
    top = botNode;
  }
  else{
    MovieNode *p = top;
    while(p->next != nullptr) {
      p = p->next;
    }
    p->next = botNode;
  }
}

//***********************************************************
// remove: removes the movie at a given position and shifts
//     order of movies accordingly
// position: position of the target movie to remove (int)
// returns: true if the movie was removed, false if position
//     is out of bounds or movie is not removed
//***********************************************************
bool MovieList :: remove(int position) {
  if(top == nullptr) { //if list is empty
    return false;    
  }

  int num = count(); //length of list
  MovieNode *p = top;
  MovieNode *n = nullptr; 

  if(position == 0) { //if target position is first node
    top = top->next;
    delete p;
    return true; 
  }
  else if(position >= num) { //if target position is out of bounds  
    return false;
  }
  else { //if target position is in bounds and not the first node
    for(int i = 0; i < position-1; i++) {
      p = p->next;
    }
    
    n = p; 
    p = p->next;
    n->next = p->next;
    
    delete p;
    return true;
  }
}

//***********************************************************
// moveToTop: given the title of a movie, that movie is moved
//     to the top of the list (position 0). If the title is 
//     not in the list, the list is unchanged.
// title: target movie title (string)
// returns: true if the movie was moved to the top of the list,
//     false if the movie is not found.
//***********************************************************
bool MovieList :: moveToTop(string title) {
  int c = 0; //counter for position of movie in list
  int size = count();
  MovieNode *p = top;
  while(p != nullptr && p->title != title) {
    p = p->next;
    c++; 
  }

  if(p == nullptr && c == size) { //if title isn't in list
    return false;
  }
  else {
    addToTop(p->title); //move to position 0
    remove(c+1); //remove duplicate 
    return true;
  }
}

//***********************************************************
// nextLarger: given the title of a movie, the next largest
//     movie in the list is found.
// title: target movie title (string)
// returns: title of the next largest movie (string)
//***********************************************************
string MovieList :: nextLarger(string title) {  
  string minStr = "a";
  MovieNode *p = top;
  
  while(p != nullptr) {
    // if p isn't title and is larger alphabetically than title
    if((p->title != title) && (p->title > title)) { 
      if(p->title < minStr) {
        minStr = p->title;
      }
    }
    p = p->next;
  }
  
  if(minStr == "a") { //if title has no next largest in list
    return "";
  }
  
  return minStr;
}

//***********************************************************
// displaySorted: displays the list of movies in alphabetical
//     order. Does not change the original order of movies.
// out: ostream variable to output the movies
// returns: void
//***********************************************************
void MovieList :: displaySorted(ostream& out) {
  string prev = "@", //comes before letters in ASCII table
         curr;
  int count = 0;
  MovieNode *p = top;

  while(p != nullptr) {
    curr = nextLarger(prev);
    out << count << ": " << curr << endl;
    prev = curr; 
    count++;
    p = p->next;
  }
}