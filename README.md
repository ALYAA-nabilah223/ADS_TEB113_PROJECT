# ADS_TEB113_PROJECT
# Library Book Borrowing System

## ADS Group Assignment

## 1. Project Title

**Library Book Borrowing System: Comparison Between O(n) and O(1) Book Lookup**

---

## 2. Project Overview

This project is a console-based Library Book Borrowing System developed in C++.

The purpose of the project is to demonstrate how selecting an appropriate data structure can improve the efficiency of an algorithm.

The program implements two different approaches for borrowing a library book:

1. A baseline linear-search approach using a `vector`
2. An optimised direct-lookup approach using an `unordered_map`

The baseline approach searches through book IDs one by one and has a time complexity of **O(n)**.

The optimised approach uses a hash table to locate a book directly by its ID and has an average time complexity of **O(1)**.

The system also uses a queue to manage students waiting for unavailable books.

---

## 3. Project Objectives

The main objectives of this project are:

* To develop a functional library borrowing system using C++
* To apply suitable data structures to a real-world problem
* To compare a baseline algorithm with an optimised algorithm
* To demonstrate the difference between O(n) and O(1) operations
* To use a queue for handling book waiting lists
* To read book records from a text file
* To save updated book records back to a text file
* To measure the execution time of selected operations
* To analyse the efficiency of the algorithms used in the system

---

## 4. Problem Statement

A library may contain a large number of books. When a student requests a book, the system must locate the book and determine whether a copy is available.

A simple implementation may store book IDs in a list and scan the list from the beginning until the requested book is found. As the number of books increases, this operation becomes slower because more records may need to be checked.

To improve this process, the project uses an `unordered_map`, which stores books using their IDs as keys. This allows the system to locate a book directly without scanning every book.

When a requested book is unavailable, the student is added to a waiting list. The waiting list follows the First-In, First-Out principle, meaning the student who joined first receives the book first when it is returned.

---

## 5. Main Features

The system provides the following functions:

1. Search for a book by its ID
2. Borrow a book using the baseline O(n) algorithm
3. Borrow a book using the optimised O(1) algorithm
4. Add a student to the waiting list when a book is unavailable
5. Return a book
6. Automatically assign a returned book to the first waiting student
7. Display all books in the catalogue
8. Load book data from `books.txt`
9. Save updated book data to `books.txt`
10. Measure execution time in microseconds

---

## 6. Data Structures Used

### 6.1 Structure: `Book`

Each book is represented using the following structure:

```cpp
struct Book {
    string id;
    string title;
    int total_copies;
    int available_copies;
    queue<string> waitlist;
};
```

The fields are:

| Field              | Data type       | Description                                    |
| ------------------ | --------------- | ---------------------------------------------- |
| `id`               | `string`        | Unique identifier of the book                  |
| `title`            | `string`        | Title of the book                              |
| `total_copies`     | `int`           | Total number of copies owned by the library    |
| `available_copies` | `int`           | Number of copies currently available           |
| `waitlist`         | `queue<string>` | Queue containing students waiting for the book |

---

### 6.2 `unordered_map`

```cpp
unordered_map<string, Book> catalog;
```

The `unordered_map` stores the books in the library catalogue.

The book ID is used as the key, while the complete `Book` object is stored as the value.

For example:

```text
Key: B001

Value:
ID: B001
Title: Data Structures
Total copies: 5
Available copies: 3
```

Using an `unordered_map` allows the program to search for books directly using their IDs.

The average time complexity for searching is:

```text
O(1)
```

In the worst case, hash collisions may cause the operation to approach:

```text
O(n)
```

However, the expected or average performance is O(1).

---

### 6.3 `vector`

```cpp
vector<string> bookIds;
```

The vector stores the IDs of all books.

It is used by the baseline borrowing function to demonstrate linear searching.

The function checks each ID one by one until it finds the requested book.

The time complexity is:

```text
O(n)
```

---

### 6.4 `queue`

```cpp
queue<string> waitlist;
```

A queue is used to store students waiting for an unavailable book.

The queue follows the First-In, First-Out principle:

```text
FIFO: First In, First Out
```

The first student added to the queue is the first student to receive the book when it becomes available.

Important queue operations include:

| Operation | Purpose                                 | Complexity |
| --------- | --------------------------------------- | ---------: |
| `push()`  | Adds a student to the back of the queue |       O(1) |
| `front()` | Reads the student at the front          |       O(1) |
| `pop()`   | Removes the student at the front        |       O(1) |
| `empty()` | Checks whether the queue is empty       |       O(1) |
| `size()`  | Returns the number of students          |       O(1) |

---

## 7. Libraries Used

The program uses the following C++ libraries:

```cpp
#include <iostream>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
```

| Library           | Purpose                                           |
| ----------------- | ------------------------------------------------- |
| `<iostream>`      | Handles console input and output                  |
| `<unordered_map>` | Stores books using hash-based lookup              |
| `<queue>`         | Manages the waiting list                          |
| `<fstream>`       | Reads from and writes to files                    |
| `<sstream>`       | Separates values from each line of the input file |
| `<vector>`        | Stores book IDs for baseline linear searching     |
| `<chrono>`        | Measures the execution time of operations         |

---

## 8. Program Functions

## 8.1 `loadBooksFromFile()`

```cpp
void loadBooksFromFile()
```

This function loads book records from `books.txt`.

It performs the following operations:

1. Opens `books.txt`
2. Reads the file line by line
3. Separates each field using the `|` character
4. Converts the number fields from strings to integers
5. Reads the waiting-list students
6. Stores each book in the `unordered_map`
7. Stores each book ID in the vector

The function uses:

```cpp
catalog[id] = b;
bookIds.push_back(id);
```

The book is inserted into the hash table, while its ID is also inserted into the vector.

### Complexity

If there are `n` books in the file, the overall loading complexity is approximately:

```text
O(n)
```

Each book must be read and inserted once.

---

## 8.2 `saveBooks()`

```cpp
void saveBooks(string filename)
```

This function saves the current book records into a file.

For each book, it saves:

* Book ID
* Book title
* Total copies
* Available copies

The values are separated using the `|` character.

### Complexity

The function visits every book once:

```text
O(n)
```

### Important limitation

The current implementation does not save the waiting-list students.

The program loads a waiting list from the file, but the `saveBooks()` function only writes:

```text
ID | Title | Total Copies | Available Copies
```

Therefore, waiting-list information will be lost after the program exits.

A corrected save function should also write every student in the queue.

---

## 8.3 `searchBook()`

```cpp
void searchBook(string id)
```

This function searches for a book using:

```cpp
catalog.find(id);
```

Because `catalog` is an `unordered_map`, the average search time is:

```text
O(1)
```

If the book is found, the function displays:

* Book ID
* Book title
* Available copies
* Total copies
* Number of students in the waiting list
* Search execution time

If the book is not found, it displays an error message.

---

## 8.4 `baseline_borrow()`

```cpp
void baseline_borrow(string book_id)
```

This is the baseline borrowing function.

It searches through the `bookIds` vector using a loop:

```cpp
for (string id : bookIds)
```

Each book ID is checked until the requested ID is found.

### Best case

The requested book is the first item:

```text
O(1)
```

### Average case

Approximately half of the IDs are checked:

```text
O(n)
```

### Worst case

The requested book is last or does not exist:

```text
O(n)
```

When the book is found and a copy is available, the function decreases the available copies:

```cpp
catalog[id].available_copies--;
```

The program also reports how many books were scanned.

### Limitation

If the book does not exist, the function finishes without displaying a clear “Book not found” message.

---

## 8.5 `optimized_borrow()`

```cpp
void optimized_borrow(string student_id, string book_id)
```

This is the optimised borrowing function.

It uses:

```cpp
auto it = catalog.find(book_id);
```

The book is searched directly in the hash table.

### When a copy is available

The number of available copies is decreased:

```cpp
it->second.available_copies--;
```

The program then displays:

* Success message
* Student ID
* Remaining copies
* Execution time

### When no copy is available

The student is added to the waiting list:

```cpp
it->second.waitlist.push(student_id);
```

The program displays the student's current position in the queue.

### Complexity

Average hash-table lookup:

```text
O(1)
```

Decreasing the copy count:

```text
O(1)
```

Adding a student to the queue:

```text
O(1)
```

Therefore, the average overall complexity is:

```text
O(1)
```

---

## 8.6 `optimized_return()`

```cpp
void optimized_return(string book_id)
```

This function processes a returned book.

First, the book is located using the hash table.

### Case 1: The waiting list is not empty

The first student is retrieved:

```cpp
string student = it->second.waitlist.front();
```

The student is then removed:

```cpp
it->second.waitlist.pop();
```

The returned book is automatically assigned to that student.

The available-copy count is not increased because the returned copy is immediately borrowed by the next student.

### Case 2: The waiting list is empty

The available-copy count is increased:

```cpp
it->second.available_copies++;
```

### Complexity

Hash-table lookup:

```text
O(1) average
```

Queue operations:

```text
O(1)
```

Therefore, the average complexity is:

```text
O(1)
```

---

## 8.7 `displayBooks()`

```cpp
void displayBooks()
```

This function displays every book in the catalogue.

For each book, it displays:

* Book ID
* Book title
* Available copies
* Total copies
* Waiting-list size

Because all books must be visited, the time complexity is:

```text
O(n)
```

---

## 8.8 `main()`

The `main()` function controls the menu and calls the appropriate function based on the user's choice.

The menu contains the following options:

```text
1. Search Book (O(1))
2. Borrow Book - BASELINE (O(n))
3. Borrow Book - OPTIMIZED (O(1))
4. Return Book (O(1))
5. Display All Books
6. Save & Exit
```

The menu repeats until the user selects option 6.

---

## 9. Algorithm Comparison

| Operation                    | Baseline approach | Optimised approach    |
| ---------------------------- | ----------------- | --------------------- |
| Data structure               | Vector            | Unordered map         |
| Search method                | Sequential scan   | Hash-table lookup     |
| Average lookup complexity    | O(n)              | O(1)                  |
| Worst-case lookup complexity | O(n)              | O(n)                  |
| Number of records checked    | Potentially many  | Usually one lookup    |
| Suitable for large data      | Less suitable     | More suitable         |
| Implementation complexity    | Simple            | Slightly more complex |

---

## 10. Why the Optimised Algorithm Is Better

Assume the library has 10,000 books.

With the baseline algorithm, the program may need to compare the requested book ID with thousands of entries.

For example, if the requested book is near the end of the vector, almost all 10,000 IDs may be scanned.

The number of operations grows with the number of books:

```text
T(n) = n
```

Therefore:

```text
O(n)
```

With the optimised algorithm, the book ID is used as a hash-table key.

The program can normally locate the book without scanning the complete catalogue.

The expected number of lookup operations remains approximately constant:

```text
T(n) = 1
```

Therefore:

```text
O(1)
```

This improvement becomes more important as the catalogue becomes larger.

---

## 11. Time-Complexity Summary

| Function              | Main operation                        | Time complexity |
| --------------------- | ------------------------------------- | --------------: |
| `loadBooksFromFile()` | Read all book records                 |            O(n) |
| `saveBooks()`         | Save all book records                 |            O(n) |
| `searchBook()`        | Hash-table lookup                     |    O(1) average |
| `baseline_borrow()`   | Linear search                         |            O(n) |
| `optimized_borrow()`  | Hash-table lookup and queue insertion |    O(1) average |
| `optimized_return()`  | Hash-table lookup and queue removal   |    O(1) average |
| `displayBooks()`      | Display all books                     |            O(n) |

---

## 12. Space-Complexity Analysis

The program stores books in two main containers:

```cpp
unordered_map<string, Book> catalog;
vector<string> bookIds;
```

If there are `n` books:

* The unordered map stores `n` books
* The vector stores `n` book IDs

Therefore, the primary storage requirement is:

```text
O(n)
```

The waiting lists may contain `w` total students.

Including the waiting lists, the total space complexity is:

```text
O(n + w)
```

---

## 13. Input File Format

The program expects a file named:

```text
books.txt
```

The file must be placed in the same folder as the compiled program.

Each record uses the following format:

```text
BookID|BookTitle|TotalCopies|AvailableCopies|WaitingList
```

Example:

```text
B001|Data Structures and Algorithms|5|3|
B002|Database Systems|2|0|ST001,ST002
B003|Operating Systems|4|4|
B004|Computer Networks|3|1|ST003
```

### Field explanation

| Position | Field                 | Example                          |
| -------: | --------------------- | -------------------------------- |
|        1 | Book ID               | `B001`                           |
|        2 | Book title            | `Data Structures and Algorithms` |
|        3 | Total copies          | `5`                              |
|        4 | Available copies      | `3`                              |
|        5 | Waiting-list students | `ST001,ST002`                    |

The `|` character separates book fields.

A comma separates multiple students in the waiting list.

---

## 14. Example `books.txt`

```text
B001|Data Structures and Algorithms|5|3|
B002|Database Management Systems|3|0|S101,S102
B003|Introduction to Programming|4|2|
B004|Operating System Concepts|2|0|S103
B005|Computer Networks|6|5|
B006|Artificial Intelligence|3|1|
B007|Software Engineering|4|0|S104,S105,S106
B008|Discrete Mathematics|5|4|
B009|Algorithm Design|2|1|
B010|Object-Oriented Programming|3|3|
```

---

## 15. How to Compile the Program

### Using g++

Open a terminal in the project folder and enter:

```bash
g++ main.cpp -o library_system
```

Run the program on Windows:

```bash
library_system.exe
```

Run the program on Linux or macOS:

```bash
./library_system
```

---

## 16. Project Folder Structure

```text
Library-Book-Borrowing-System/
│
├── main.cpp
├── books.txt
└── README.md
```

---

## 17. How to Use the Program

### Step 1: Start the program

When the program begins, it loads records from `books.txt`.

Example:

```text
Loaded 10 books from books.txt
```

### Step 2: Select a menu option

```text
1. Search Book (O(1))
2. Borrow Book - BASELINE (O(n))
3. Borrow Book - OPTIMIZED (O(1))
4. Return Book (O(1))
5. Display All Books
6. Save & Exit
```

### Step 3: Search for a book

Select:

```text
1
```

Enter a book ID:

```text
B001
```

Possible output:

```text
Book ID : B001
Title : Data Structures and Algorithms
Available : 3/5
Waitlist : 0 student(s)
Search time: 1 microseconds
```

### Step 4: Borrow using the baseline algorithm

Select:

```text
2
```

Enter a book ID:

```text
B008
```

Possible output:

```text
1. BASELINE (O(n))
Successfully Borrowed! (Scanned 8 books)
Time taken: 4 microseconds
```

### Step 5: Borrow using the optimised algorithm

Select:

```text
3
```

Enter the student ID:

```text
S201
```

Enter the book ID:

```text
B001
```

Possible output:

```text
--- OPTIMIZED (O(1)) ---
Successfully Borrowed! (1 lookup)
Student: S201
Remaining copies: 2/5
Time taken: 1 microseconds
```

### Step 6: Join a waiting list

When no copies are available, the output may be:

```text
Book unavailable. Added to waitlist.
Student: S202 (Position: 3)
Time taken: 1 microseconds
```

### Step 7: Return a book

Select:

```text
4
```

Enter the book ID.

If there is a waiting student:

```text
Book automatically assigned to S101
Remaining in queue: 1 student(s)
Time taken: 1 microseconds
```

If there is no waiting student:

```text
Book returned successfully.
Available copies: 2/3
Time taken: 1 microseconds
```

### Step 8: Save and exit

Select:

```text
6
```

The program saves the updated catalogue and closes.

---

## 18. Performance Measurement

The program uses the `<chrono>` library to measure execution time.

The timer starts using:

```cpp
auto start = chrono::high_resolution_clock::now();
```

The timer ends using:

```cpp
auto end = chrono::high_resolution_clock::now();
```

The duration is calculated in microseconds:

```cpp
auto duration =
    chrono::duration_cast<chrono::microseconds>(end - start);
```

The measured time is then displayed:

```cpp
cout << duration.count() << " microseconds";
```

### Important observation

For a small catalogue, both O(n) and O(1) operations may display a value of zero or a very small number of microseconds.

This does not mean that the algorithms have equal efficiency.

Time complexity describes how the execution time grows as the input size increases. The difference becomes clearer when the program contains thousands or millions of book records or when the same operation is repeated many times.

---

## 19. Functional Requirements

The system should be able to:

* Load book records from a text file
* Search for a book using its ID
* Display book information
* Borrow an available book
* Reduce the available-copy count after borrowing
* Add a student to the waiting list when no copies are available
* Return a borrowed book
* Assign a returned book to the next waiting student
* Display all books
* Save modified records before exiting
* Compare baseline and optimised algorithms
* Display execution time

---

## 20. Non-Functional Requirements

The system should:

* Be written in standard C++
* Provide a menu-based interface
* Use suitable data structures
* Produce readable console output
* Handle missing book IDs
* Process book operations efficiently
* Store data persistently using a file
* Demonstrate algorithmic complexity clearly

---

## 21. Current Limitations

The current program has several limitations.

### 21.1 Waiting lists are not saved

The `saveBooks()` function does not save student IDs from the waiting queue.

Therefore, waiting-list data loaded from the file may be lost when the program exits.

### 21.2 Duplicate book IDs are not checked

If `books.txt` contains duplicate book IDs, the later record replaces the earlier record inside the `unordered_map`.

However, both IDs may remain in the `bookIds` vector.

### 21.3 Invalid numeric values may crash the program

The program uses:

```cpp
stoi(totalStr);
stoi(availStr);
```

If a field contains invalid text, `stoi()` may throw an exception.

### 21.4 Available copies may exceed total copies

During a return, the program increases `available_copies` without checking whether it is already equal to `total_copies`.

Repeated returns could therefore produce an invalid value.

### 21.5 Student borrowing records are not stored

The system displays the student ID when borrowing, but it does not permanently store which student borrowed which book.

### 21.6 Baseline borrowing does not use a student ID

The baseline borrowing function only accepts a book ID.

It does not identify the student performing the borrowing operation.

### 21.7 Baseline borrowing has no waiting-list support

When a book is unavailable, the baseline function only displays a message.

It does not add the student to the waiting queue.

### 21.8 Book-not-found message is missing in the baseline function

If the requested book ID is absent from the vector, the baseline function ends without clearly reporting that the book was not found.

### 21.9 Unordered display order

The `displayBooks()` and `saveBooks()` functions iterate through an `unordered_map`.

Therefore, books may not appear in the same order as they appeared in `books.txt`.

---

## 22. Suggested Improvements

The project could be improved by adding:

* Complete waiting-list saving
* Student borrowing records
* Book-return validation
* Input validation
* Exception handling
* Duplicate-ID detection
* The ability to add new books
* The ability to remove books
* The ability to edit book details
* Search by title
* Student account management
* Borrowing dates and due dates
* Late-return penalties
* File backup support
* A graphical user interface
* A database instead of a text file
* More accurate performance testing using repeated operations
* Sorting books by ID or title
* Separate classes for books, students, and the library system

---

## 23. Recommended Correction for Saving the Waiting List

The current save function removes the waiting-list information.

A corrected version can copy the queue and save each student:

```cpp
void saveBooks(const string& filename)
{
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "ERROR: Could not open " << filename << " for writing.\n";
        return;
    }

    int count = 0;

    for (const auto& entry : catalog) {
        const Book& book = entry.second;

        file << book.id << "|";
        file << book.title << "|";
        file << book.total_copies << "|";
        file << book.available_copies << "|";

        queue<string> tempQueue = book.waitlist;
        bool first = true;

        while (!tempQueue.empty()) {
            if (!first) {
                file << ",";
            }

            file << tempQueue.front();
            tempQueue.pop();
            first = false;
        }

        file << "\n";
        count++;
    }

    file.close();
    cout << "Saved " << count << " books to " << filename << "\n";
}
```

A copy of the queue is used because the original queue should not be changed while saving.

---

## 24. Recommended Correction for Baseline Borrowing

The baseline function can be improved by displaying a message when the book does not exist:

```cpp
void baseline_borrow(const string& book_id)
{
    int steps = 0;
    bool found = false;

    cout << "\n--- BASELINE O(n) ---\n";

    auto start = chrono::high_resolution_clock::now();

    for (const string& id : bookIds) {
        steps++;

        if (id == book_id) {
            found = true;

            if (catalog[id].available_copies > 0) {
                catalog[id].available_copies--;

                cout << "Successfully borrowed.\n";
                cout << "Scanned books: " << steps << "\n";
            } else {
                cout << "Book is unavailable.\n";
                cout << "Scanned books: " << steps << "\n";
            }

            break;
        }
    }

    if (!found) {
        cout << "Book not found.\n";
        cout << "Scanned books: " << steps << "\n";
    }

    auto end = chrono::high_resolution_clock::now();

    auto duration =
        chrono::duration_cast<chrono::microseconds>(end - start);

    cout << "Time taken: "
         << duration.count()
         << " microseconds\n";
}
```

---

## 25. Recommended Validation for Returning Books

The return function should prevent available copies from exceeding total copies:

```cpp
if (it->second.available_copies >= it->second.total_copies &&
    it->second.waitlist.empty()) {

    cout << "Return rejected: all copies are already available.\n";
    return;
}
```

---

## 26. Testing Scenarios

The following tests can be used to evaluate the system.

### Test 1: Search for an existing book

Input:

```text
Book ID: B001
```

Expected result:

* The book is found
* Book details are displayed
* Search time is displayed

### Test 2: Search for a missing book

Input:

```text
Book ID: B999
```

Expected result:

```text
Book not found.
```

### Test 3: Baseline borrow with available copies

Expected result:

* The vector is scanned
* The copy count decreases by one
* The number of scanned books is displayed

### Test 4: Optimised borrow with available copies

Expected result:

* The book is located through the hash table
* The copy count decreases by one
* One lookup is reported

### Test 5: Optimised borrow with no copies

Expected result:

* The student is added to the queue
* The queue position is displayed

### Test 6: Return with a non-empty waiting list

Expected result:

* The first student is removed from the queue
* The returned copy is assigned to that student
* Available copies remain unchanged

### Test 7: Return with an empty waiting list

Expected result:

* Available copies increase by one

### Test 8: Display all books

Expected result:

* Every book is displayed
* Availability and waiting-list size are shown

### Test 9: Save and exit

Expected result:

* Updated data is written to `books.txt`
* The program closes successfully

---

## 27. Example Complexity Experiment

To make the performance comparison more meaningful, the system can be tested using different catalogue sizes:

| Test   | Number of books |
| ------ | --------------: |
| Test 1 |              10 |
| Test 2 |             100 |
| Test 3 |           1,000 |
| Test 4 |          10,000 |
| Test 5 |         100,000 |

For each catalogue size:

1. Search for the first book
2. Search for a middle book
3. Search for the final book
4. Search for a book that does not exist
5. Record the baseline execution time
6. Record the optimised execution time
7. Repeat each operation several times
8. Calculate the average execution time

Expected result:

* Baseline execution time grows as the number of books grows
* Optimised lookup time remains approximately constant on average

---

## 28. Algorithm Pseudocode

### Baseline Borrowing Algorithm

```text
Algorithm BaselineBorrow(bookID)

    steps ← 0

    FOR each ID in book ID list
        steps ← steps + 1

        IF ID = bookID THEN
            IF available copies > 0 THEN
                available copies ← available copies - 1
                display success
            ELSE
                display unavailable
            END IF

            stop loop
        END IF
    END FOR

    display steps
End Algorithm
```

### Optimised Borrowing Algorithm

```text
Algorithm OptimisedBorrow(studentID, bookID)

    search for bookID in hash table

    IF book does not exist THEN
        display book not found
        stop
    END IF

    IF available copies > 0 THEN
        available copies ← available copies - 1
        display borrowing success
    ELSE
        add studentID to waiting queue
        display queue position
    END IF

End Algorithm
```

### Return Algorithm

```text
Algorithm ReturnBook(bookID)

    search for bookID in hash table

    IF book does not exist THEN
        display book not found
        stop
    END IF

    IF waiting queue is not empty THEN
        student ← front of waiting queue
        remove student from waiting queue
        assign book to student
    ELSE
        available copies ← available copies + 1
    END IF

End Algorithm
```

---

## 29. Conclusion

This project demonstrates the importance of choosing an appropriate data structure when designing an algorithm.

The baseline method uses a vector and performs a linear search. Its time complexity is O(n), meaning the number of comparisons may increase as the number of books increases.

The optimised method uses an `unordered_map`. It provides an average lookup complexity of O(1), allowing books to be located efficiently using their IDs.

The project also demonstrates the practical use of a queue. Students waiting for unavailable books are served according to the First-In, First-Out principle.

Overall, the optimised solution is more suitable for a large library catalogue because it provides faster average lookup operations, while the queue provides a fair and efficient method for managing unavailable books.

---

## 30. Group Members

Add the group members below:

| No. | Name            | Student ID     | 
| --: | --------------- | -------------- | 
|   1 | `Mohamamd Nazri Aizad bin Mohammad Nazroel` | `25014457` | 
|   2 | `Nur Alyaa Nabilah binti Mazlan` | `25014139` | 
|   3 | `Ivy Rachel Richard` | `25014556` | 
|   4 | `Ahmed Mohammed Mahmoud AbuAlrub` | `25005930` |
|   5 | `Mahiru Maisha Raiyena ` | `25008084` | 

---

## 31. Course Information

| Item                 | Details                        |
| -------------------- | ------------------------------ |
| Course               | Algorithms and Data Structures |
| Assignment           | Group Assignment               |
| Project              | Library Book Borrowing System  |
| Programming language | C++                            |
| Lecturer             | `Dr Farahida Hanim Bt Mausor`              |
| Group                | `Group 14`               |
