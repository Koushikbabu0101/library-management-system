#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool isIssued;
    string issuedTo;

    Book(int id, string title, string author) 
        : id(id), title(title), author(author), isIssued(false) {}
};

class Library {
private:
    vector<Book> books;

    vector<Book>::iterator findBookById(int id) {
        return find_if(books.begin(), books.end(), [&](const Book& book) { return book.id == id; });
    }

public:
    void addBook(int id, string title, string author) {
        books.push_back(Book(id, title, author));
        cout << "Book added successfully.\n";
    }

    void searchBook(string keyword) {
        for (const auto& book : books) {
            if (to_string(book.id) == keyword || book.title.find(keyword) != string::npos) {
                cout << "ID: " << book.id << "\nTitle: " << book.title << "\nAuthor: " << book.author
                     << "\nStatus: " << (book.isIssued ? "Issued to " + book.issuedTo : "Available") << "\n";
                return;
            }
        }
        cout << "Book not found.\n";
    }

    void issueBook(int id, string studentName) {
        auto it = findBookById(id);
        if (it != books.end() && !it->isIssued) {
            it->isIssued = true;
            it->issuedTo = studentName;
            cout << "Book issued to " << studentName << ".\n";
        } else {
            cout << (it != books.end() ? "Book is already issued.\n" : "Book not found.\n");
        }
    }

    void returnBook(int id) {
        auto it = findBookById(id);
        if (it != books.end() && it->isIssued) {
            it->isIssued = false;
            it->issuedTo = "";
            cout << "Book returned successfully.\n";
        } else {
            cout << (it != books.end() ? "Book was not issued.\n" : "Book not found.\n");
        }
    }

    void listAllBooks() {
        sort(books.begin(), books.end(), [](const Book &a, const Book &b) { return a.title < b.title; });
        cout << "Listing all books:\n";
        for (const auto& book : books) {
            cout << "ID: " << book.id << "\nTitle: " << book.title << "\nAuthor: " << book.author
                 << "\nStatus: " << (book.isIssued ? "Issued to " + book.issuedTo : "Available") << "\n\n";
        }
    }

    void deleteBook(int id) {
        auto it = findBookById(id);
        if (it != books.end()) {
            books.erase(it);
            cout << "Book deleted successfully.\n";
        } else {
            cout << "Book not found.\n";
        }
    }
};

int main() {
    Library lib;
    int choice, id;
    string title, author, studentName;

    do {
        cout << "\nLibrary Management System:\n";
        cout << "1. Add New Book\n2. Search for a Book\n3. Issue a Book\n4. Return a Book\n";
        cout << "5. List All Books\n6. Delete a Book\n7. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter book title: ";
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                lib.addBook(id, title, author);
                break;
            case 2:
                cout << "Enter book title or ID to search: ";
                cin.ignore();
                getline(cin, title);
                lib.searchBook(title);
                break;
            case 3:
                cout << "Enter book ID to issue: ";
                cin >> id;
                cin.ignore();
                cout << "Enter student name: ";
                getline(cin, studentName);
                lib.issueBook(id, studentName);
                break;
            case 4:
                cout << "Enter book ID to return: ";
                cin >> id;
                lib.returnBook(id);
                break;
            case 5:
                lib.listAllBooks();
                break;
            case 6:
                cout << "Enter book ID to delete: ";
                cin >> id;
                lib.deleteBook(id);
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}