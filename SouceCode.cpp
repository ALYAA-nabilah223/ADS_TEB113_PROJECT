#include <iostream>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

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
    auto start = chrono::high_resolution_clock::now();

    for (string id : bookIds) {
        steps++;
        if (id == book_id) {
            if (catalog[id].available_copies > 0) {
                catalog[id].available_copies--;
                cout<<"Successfully Borrowed! (Scanned "<<steps<<" books)\n";
            } else {
                cout<<"Uhh, Book is Unavailable!!. (Scanned "<<steps<<" books)\n";
            }
            break;
        }
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout<<"Time taken: "<<duration.count()<<" microseconds\n";
    
}

//Borrow: Optimized Function O(1)
void optimized_borrow(string student_id, string book_id) {
    cout<<"\n2. OPTIMIZED (O(1))\n";
    auto start = chrono::high_resolution_clock::now();

    Book &book = catalog[book_id];
    
    if (book.available_copies > 0) {
        book.available_copies--;
        cout<<"Successfully Borrowed! (1 lookup)\n";
    } else {
        book.waitlist.push(student_id);
        cout<<"Successfully added "<<student_id<<" to queue. (Pos: "<< book.waitlist.size()<<")\n";
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout<<"Time taken: "<<duration.count()<<" microseconds\n";
}

//Return: Optimized Function O(1)
void optimized_return(string book_id) {
    cout << "\n1. RETURN & NOTIFY\n";
    Book &book = catalog[book_id];
    book.available_copies++;

    if (!book.waitlist.empty()) {
        string next = book.waitlist.front();
        book.waitlist.pop();
        cout<<"Notifying "<<next<<" (Queue left: "<<book.waitlist.size()<< ")\n";
    } else {
        cout<<"Book Returned. No one waiting.\n";
    }
}


int main() {
    loadBooksFromFile();
    cout << "\nInitial Waitlist for B0001: "<< catalog["B0001"].waitlist.size()<< "\n";
    //1. Test Baseline Borrow
    baseline_borrow("B0001");

    //2. Test Optimized Borrow
    optimized_borrow("S1006", "B0001");

    //3. Test Optimized Return
    optimized_return("B0001");

    //Final Output:
    cout << "\nFinal Waitlist for B0001: "<<catalog["B0001"].waitlist.size()<<"\n";
    system("pause");
    return 0;
}
