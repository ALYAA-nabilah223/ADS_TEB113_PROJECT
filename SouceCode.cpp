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
        b.id = id;
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

// Search Book: Baseline
void baseline_search(string book_id) {
    int steps = 0;
    cout<<"\n--- BASELINE SEARCH (O(n)) ---\n";

    auto start = chrono::high_resolution_clock::now();

    for (string id : bookIds) {
        steps++;
        if (id == book_id) {
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

            cout<<"Book found!\n";
            cout<<"Book ID : "<<catalog[id].id<<"\n";
            cout<<"Title : "<<catalog[id].title<<"\n";
            cout<<"Available : "<<catalog[id].available_copies<<"/"<<catalog[id].total_copies<<"\n";
            cout<<"Waitlist : "<<catalog[id].waitlist.size()<<" student(s)\n";
            cout<<"Scanned "<<steps<<" book(s).\n";
            cout<<"Search time: "<<duration.count()<<" microseconds\n";
            return;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout<<"Book not found.\n";
    cout<<"Scanned "<<steps<<" book(s).\n";
    cout<<"Search time: "<<duration.count()<<" microseconds\n";
}

//Search Book: Optimized
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

// Return: Baseline Function O(n)
void baseline_return(string book_id) {
    int steps = 0;
    cout << "\n--- BASELINE RETURN (O(n)) ---\n";

    auto start = chrono::high_resolution_clock::now();

    for (string id : bookIds) {
        steps++;

        if (id == book_id) {

            // No waitlist handling in the baseline approach
            catalog[id].available_copies++;

            auto end = chrono::high_resolution_clock::now();
            auto duration =
                chrono::duration_cast<chrono::microseconds>(end - start);

            cout << "Book returned successfully.\n";
            cout << "Available copies: "
                 << catalog[id].available_copies
                 << "/" << catalog[id].total_copies << endl;
            cout << "Scanned " << steps << " book(s).\n";
            cout << "Time taken: " << duration.count() << " microseconds\n";

            return;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration =
        chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "Book not found.\n";
    cout << "Scanned " << steps << " book(s).\n";
    cout << "Time taken: " << duration.count() << " microseconds\n";
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

//Additional function: Performance Graph Data Generation
void runPerformanceTest() {
    cout<<"\n--- PERFORMANCE TEST ---\n";

    vector<int> testSizes = {10,50,100,500,1000,2000,3000,4000,5000};
    
    ofstream dataFile("performance_data.csv");
    dataFile<<"Books,BaselineSteps,BaselineTime,OptimizedTime\n";
    
    for (int size : testSizes) {
        vector<string> testBookIds;
        for (int i = 0; i < size && i < bookIds.size(); i++) {
            testBookIds.push_back(bookIds[i]);
        }
        
        cout<<"Testing with "<<size<<" books\n";
        int steps = 0;
        for (string id : testBookIds) {
            steps++;
            if (id == "B0001") break;
        }
        
        auto start = chrono::high_resolution_clock::now();
        for (string id : testBookIds) {
            if (id == "B0001") break;
        }
        auto end = chrono::high_resolution_clock::now();
        auto baselineTime = chrono::duration_cast<chrono::microseconds>(end - start);
        
        auto startOpt = chrono::high_resolution_clock::now();
        auto it = catalog.find("B0001");
        auto endOpt = chrono::high_resolution_clock::now();
        auto optimizedTime = chrono::duration_cast<chrono::microseconds>(endOpt - startOpt);
        
        dataFile<<size<<","<<steps<<","<<baselineTime.count()<<","<<optimizedTime.count()<<"\n";
        
        cout<<"   Baseline: "<<steps<<" steps, "<<baselineTime.count()<<" μs\n";
        cout<<"   Optimized: 1 step, "<<optimizedTime.count()<<" μs\n\n";
    }
    
    dataFile.close();
    cout<<"Data saved to 'performance_data.csv'\n";
}

int main() {
    cout<< "LIBRARY BOOK BORROWING SYSTEM\n";
    cout<< "BASELINE (O(n)) vs OPTIMIZED (O(1))\n";

    loadBooksFromFile();
    int choice;

    do {
        cout<<"\n1. Search Book (O(1))\n";
        cout<<"2. Borrow Book - BASELINE (O(n))\n";
        cout<<"3. Borrow Book - OPTIMIZED (O(1))\n";
        cout << "4. Return Book - BASELINE (O(n))\n";
        cout << "5. Return Book - OPTIMIZED (O(1))\n";
        cout << "6. Display All Books\n";
        cout << "7. Save & Exit\n";
        cout<<"========================================\n";
        cout<<"Choice : ";
        cin>>choice;

        switch(choice) {
            case 1:{
                string id;
                cout<<"Enter Book ID : ";
                cin >> id;
                searchBook(id);
                break;}

            case 2:{
                string id;
                cout<<"Enter Book ID : ";
                cin>>id;
                baseline_borrow(id);
                break;}

            case 3:{
                string student_id, book_id;
                cout<<"Enter Student ID : ";
                cin>>student_id;
                cout<<"Enter Book ID : ";
                cin>>book_id;
                optimized_borrow(student_id, book_id);
                break;}

            case 4: {
                string id;
                cout << "Enter Book ID : ";
                cin >> id;
                baseline_return(id);
                break;
            }

            case 5: {
                string id;
                cout << "Enter Book ID : ";
                cin >> id;
                optimized_return(id);
                break;
            }

            case 6:
                displayBooks();
                break;

            case 7:
                saveBooks("books.txt");
                cout << "Data saved. Goodbye!\n";
                break;

            default:
                cout<<"Invalid choice. Please try again.\n";
                break;
        }

    } while(choice != 7);


    return 0;
}
