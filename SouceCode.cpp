#include <iostream>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Book {
    string title;
    int total_copies;
    int available_copies;
    queue<string> waitlist;
};

unordered_map<string, Book> catalog;
vector<string> bookIds;