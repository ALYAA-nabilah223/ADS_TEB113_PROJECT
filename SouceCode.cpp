#include <iostream>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;

struct Book {
    string id;
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

//Save books to file
void saveBooks(string filename)
{
    ofstream file(filename);
    int count = 0;
    for (auto &b : catalog) {
        file << b.second.id << "|";
        file << b.second.title << "|";
        file << b.second.total_copies << "|";
        file << b.second.available_copies << "|" << endl;
        count++;
    }

    file.close();
    cout<<"Saved "<<count<<" books to "<<filename<<"\n";
}

//Search book by ID
void searchBook(string id) {
    auto start = chrono::high_resolution_clock::now();

    auto it = catalog.find(id);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    if (it == catalog.end()) {
        cout << "Book not found.\n";
        cout << "Search time: " << duration.count() << " microseconds\n";
        return;
    }

    cout << "Book ID : " << it->second.id << endl;
    cout << "Title : " << it->second.title << endl;
    cout << "Available : " << it->second.available_copies << "/" << it->second.total_copies << endl;
    cout << "Waitlist : " << it->second.waitlist.size() << " student(s)" << endl;
    cout << "Search time: " << duration.count() << " microseconds\n";
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
    cout<<"\n--- OPTIMIZED (O(1)) ---\n";
    auto start = chrono::high_resolution_clock::now();

    auto it = catalog.find(book_id);

    if (it == catalog.end()) {
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout<<"Book not found.\n";
        cout<<"Time taken: " << duration.count()<< " microseconds\n";
        return;
    }

    if (it->second.available_copies > 0) {
        it->second.available_copies--;
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout<<"Successfully Borrowed! (1 lookup)\n";
        cout<<"Student: " << student_id << endl;
        cout<<"Remaining copies: "<< it->second.available_copies<< "/"<< it->second.total_copies<<endl;
        cout<<"Time taken: " << duration.count()<<" microseconds\n";
    } else {
        it->second.waitlist.push(student_id);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout<<"Book unavailable. Added to waitlist.\n";
        cout<<"Student: "<< student_id<< " (Position: "<< it->second.waitlist.size() << ")\n";
        cout<<"Time taken: "<< duration.count()<<" microseconds\n";
    }
}

//Return: Optimized Function O(1)
void optimized_return(string book_id) {
    cout<<"\n--- RETURN & NOTIFY ---\n";
    auto start = chrono::high_resolution_clock::now();

    auto it = catalog.find(book_id);

    if (it == catalog.end()) {
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout<<"Book not found.\n";
        cout<<"Time taken: "<< duration.count()<<" microseconds\n";
        return;
    }

    if (!it->second.waitlist.empty()) {
        string student = it->second.waitlist.front();
        it->second.waitlist.pop();
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout<<"Book automatically assigned to "<< student << endl;
        cout<<"Remaining in queue: "<< it->second.waitlist.size()<< " student(s)\n";
        cout<<"Time taken: "<< duration.count() << " microseconds\n";
    } else {
        it->second.available_copies++;
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout<<"Book returned successfully.\n";
        cout<<"Available copies: "<< it->second.available_copies << "/" << it->second.total_copies << endl;
        cout<<"Time taken: "<< duration.count() << " microseconds\n";
    }
}

//Additional function to display all books in the catalog
void displayBooks() {
    cout<<"\\nBOOK LIST\\n";
    cout<<"----------------------------------------\\n";

    for (auto &b : catalog) {
        cout<<b.second.id << " | "
             << b.second.title << " | "
             << b.second.available_copies
             << "/"
             << b.second.total_copies
             << " | Waitlist: " << b.second.waitlist.size()
             << endl;
    }

    cout<< "----------------------------------------\n";
    cout<< "Total books: "<<catalog.size()<< endl;
}


int main() {
    cout<< "\n========================================\n";
    cout<< "LIBRARY BOOK BORROWING SYSTEM\n";
    cout<< "BASELINE (O(n)) vs OPTIMIZED (O(1))\n";
    cout<< "========================================\n";

    loadBooksFromFile();

    cout<< "\nInitial Waitlist for B0001: "<< catalog["B0001"].waitlist.size()<< " student(s)\n";

    //1. Test Search (O(1) - Hash Map Lookup)
    cout<< "\nTEST 1: SEARCH BOOK (O(1))\n";
    searchBook("B0001");

    //2. Test Baseline Borrow (O(n) - Linear Scan)
    cout << "\nTEST 2: BASELINE BORROW (O(n))\n";
    baseline_borrow("B0001");

    //3. Test Optimized Borrow (O(1) - Hash Map + Queue)
    cout<< "\nTEST 3: OPTIMIZED BORROW (O(1))\n";
    optimized_borrow("S1006", "B0001");

    //4. Test Optimized Return (O(1) - Hash Map + Queue)
    cout<< "\nTEST 4: OPTIMIZED RETURN (O(1))\n";
    optimized_return("B0001");

    //Final Output
    cout << "\nFinal Waitlist for B0001: " << catalog["B0001"].waitlist.size() << " student(s)\n";
    system("pause");
    return 0;
}
