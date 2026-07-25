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

void loadBooksFromFile() {
    //check if book file exixst
    ifstream file("books.txt");
    if (!file.is_open()) {
        cout<<"ERROR: books.txt not found!\n";
        return;
    }

    string line;
    int count = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        count++;

        stringstream ss(line);
        string id, title, totalStr, availStr, waitlistStr;
        getline(ss, id, '|');
        getline(ss, title, '|');
        getline(ss, totalStr, '|');
        getline(ss, availStr, '|');
        getline(ss, waitlistStr, '|');

        Book b;
        b.title = title;
        b.total_copies = stoi(totalStr);
        b.available_copies = stoi(availStr);

        if (!waitlistStr.empty()) {
            stringstream wlStream(waitlistStr);
            string student;
            while (getline(wlStream, student, ',')) {
                if (!student.empty()) b.waitlist.push(student);
            }
        }

        catalog[id] = b;
        bookIds.push_back(id);
    }
    file.close();
    cout<<"Loaded "<<count<<" books from books.txt\n";
}

//Borrow: Base Function O(n)
void baseline_borrow(string book_id) {
    int steps = 0;
    cout<<"\n1. BASELINE (O(n))\n";
    for (string id : bookIds) {
        steps++;
        if (id == book_id) {
            if (catalog[id].available_copies > 0) {
                catalog[id].available_copies--;
                cout<<"Successfully Borrowed! (Scanned "<<steps<<" books)\n";
            } else {
                cout<<"Uhh, Book is Unavailable!!. (Scanned"<<steps<<" books)\n";
            }
            break;
        }
    }
    
}

//Borrow: Optimized Function O(1)
void optimized_borrow(string student_id, string book_id) {
    cout<<"\n2. OPTIMIZED (O(1))\n";
    Book &book = catalog[book_id];
    
    if (book.available_copies > 0) {
        book.available_copies--;
        cout<<"SuccessfullyBorrowed! (1 lookup)\n";
    } else {
        book.waitlist.push(student_id);
        cout<<"Successfully added "<<student_id<<" to queue. (Pos: "<< book.waitlist.size()<<")\n";
    }
}

int main() {
    cout<<"Testing file loader\n";
    loadBooksFromFile();
    cout<<"Total books in catalog: "<<catalog.size()<<"\n";
    cout<<"Total book IDs in vector: "<<bookIds.size()<<"\n";
    return 0;
}
