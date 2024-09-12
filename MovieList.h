// File Name: MovieList.h
//
// Author: Vladyslav Prokopenko, Jill Seaman
// Date: 10/26/2020
// Assignment Number: 5
// CS 2308/CS 5301
// Instructor: Jill Seaman

#include <string>
#include <iostream>
using namespace std;

struct MovieNode {
    string title;
    MovieNode *next;
};

class MovieList {
public:
    MovieList();
    ~MovieList();
    int count();
    void display(ostream& out);
    void addToTop(string title);
    void addToBottom(string title);
    bool remove(int position);
    bool moveToTop(string title);
    string nextLarger(string title);
    void displaySorted(ostream& out);
private:
    MovieNode* top;
};


