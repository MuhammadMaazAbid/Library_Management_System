#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>

using namespace std;

// Structure for storing book data
struct Book
{
    string title, author, description;
    double rating;
};

// Function declarations for better code organization
void displayBooks(string bookGenre);
void addNewBookToFile(string fileName);
Book getNewBookDetails();
void deleteBookByTitle(string genreFile);
void addtofavorite(string genreFile);
void displayfavoritelist();

// Function to choose and handle book genres based on user actions
void chooseGenre(string action)
{
    system("cls"); // Clear the console screen
    cout << "Choose a Genre:" << endl;
    cout << "1. Fantasy" << endl;
    cout << "2. Science Fiction" << endl;
    cout << "3. Mystery/Thriller" << endl;
    cout << "4. Historical Fiction" << endl;
    cout << "5. Biography/Memoir" << endl;

    int choice;
    cin >> choice;

    string fileName;
    // Map user's choice to the corresponding genre file
    if (choice == 1)
        fileName = "1.Fantasy.txt";
    else if (choice == 2)
        fileName = "2.Science Fiction.txt";
    else if (choice == 3)
        fileName = "3.Mystery.txt";
    else if (choice == 4)
        fileName = "4.Historical Fiction.txt";
    else if (choice == 5)
        fileName = "5.Biography.txt";
    else
    {
        cout << "Invalid choice!" << endl;
        return;
    }

    // Perform the action based on the user's input
    if (action == "display")
        displayBooks(fileName);
    else if (action == "add")
        addNewBookToFile(fileName);
    else if (action == "delete")
        deleteBookByTitle(fileName);
}

// Function to display books in a specific genre
void displayBooks(string bookGenre)
{
    ifstream file(bookGenre); // Open the genre file for reading

    if (!file.is_open()) // Check if the file opened successfully
    {
        cout << "Error: Could not open file!" << endl;
        return;
    }

    char user_choice;
    string line;

    // Display all lines from the file
    while (getline(file, line))
    {
        cout << line << endl;
    }

    cout << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << "Do You Want to Add some Books to your Favorite List (y/n) :" << endl;
    cout << "-------------------------------------------------------------" << endl;
    cin >> user_choice;

    // Allow the user to add books to their favorite list
    if (user_choice == 'Y' || user_choice == 'y')
    {
        addtofavorite(bookGenre);
    }

    file.close(); // Close the file after reading
}

// Function to get details for a new book
Book getNewBookDetails()
{
    Book book;
    cin.ignore(); // Clear the input buffer
    cout << "Enter Book Title: ";
    getline(cin, book.title);
    cout << "Enter Author Name: ";
    getline(cin, book.author);
    cout << "Enter Rating (Out of 5): ";
    cin >> book.rating;
    cin.ignore(); // Clear the buffer again
    cout << "Enter Description: ";
    getline(cin, book.description);
    return book; // Return the filled book object
}

// Function to add a new book to a file
void addNewBookToFile(string fileName)
{
    Book book = getNewBookDetails(); // Get details for the new book
    ofstream file(fileName, ios::app); // Open the file in append mode

    if (!file.is_open()) // Check if the file opened successfully
    {
        cout << "Error: Could not open file!" << endl;
        return;
    }

    // Write the book details to the file
    file << "Book Title: " << book.title << endl;
    file << "Author: " << book.author << endl;
    file << "Rating: " << book.rating << "/5" << endl;
    file << "Description: " << book.description << endl;
    file << "----------------------------------------" << endl;

    file.close(); // Close the file after writing
    cout << "-----------------------------------------" << endl;
    cout << "        Book added successfully!      " << endl;
    cout << "-----------------------------------------" << endl;
}

// Function to delete a book by its title
void deleteBookByTitle(string genreFile)
{
    ifstream file(genreFile); // Open the file for reading

    if (!file.is_open()) // Check if the file opened successfully
    {
        cout << "Error: Could not open file!" << endl;
        return;
    }

    vector<string> lines; // Store all lines from the file
    string Filedata;

    // Read all lines from the file and store them
    while (getline(file, Filedata))
    {
        lines.push_back(Filedata);
    }
    file.close(); // Close the file after reading

    if (lines.empty()) // Check if the file is empty
    {
        cout << "No books available in this genre!" << endl;
        return;
    }

    cin.ignore(); // Clear the input buffer
    cout << "Enter the title of the book to delete: ";
    string bookTitle;
    getline(cin, bookTitle);

    vector<string> updatedLines; // To store the updated data
    bool found = false;
    bool skipBlock = false;

    // Iterate over lines to find and skip the target book's block
    for (int i = 0; i < lines.size(); i++)
    {
        if (lines[i].find("Book Title: ") == 0 && lines[i].substr(12) == bookTitle)
        {
            found = true;
            skipBlock = true; // Start skipping this block
        }

        if (skipBlock && lines[i] == "----------------------------------------")
        {
            skipBlock = false; // End of the target book block
            continue; // Skip the separator line as well
        }

        if (!skipBlock) // Add lines not part of the target book
        {
            updatedLines.push_back(lines[i]);
        }
    }

    if (!found) // If the book is not found
    {
        cout << "Book not found!" << endl;
        return;
    }

    // Write the updated data back to the file
    ofstream outFile(genreFile);
    for (const string &updatedLine : updatedLines)
    {
        outFile << updatedLine << endl;
    }
    outFile.close();

    cout << "Book deleted successfully!" << endl;
}

// Function to add a book to the favorite list
void addtofavorite(string genreFile)
{
    ifstream file(genreFile); // Open the genre file to read book details

    if (!file.is_open()) // Check if the file opened successfully
    {
        cout << "Error: Could not open file!" << endl;
        return;
    }

    vector<string> lines; // Store all lines from the file
    string Filedata;

    while (getline(file, Filedata))
    {
        lines.push_back(Filedata);
    }
    file.close();

    if (lines.empty()) // Check if the file is empty
    {
        cout << "No books available in this genre!" << endl;
        return;
    }

    cin.ignore(); // Clear the input buffer
    cout << "Enter the title of the book you want to add: ";
    string title;
    getline(cin, title);

    ofstream outfile("favoritebooklist.txt", ios::app); // Open the favorite list file to append

    if (!outfile.is_open()) // Check if the file opened successfully
    {
        cout << "Error: Could not open favorite book list file!" << endl;
        return;
    }

    bool found = false;

    // Find the book in the genre file and add it to the favorite list
    for (int i = 0; i < lines.size(); i++)
    {
        if (lines[i].find("Book Title: ") == 0 && lines[i].substr(12) == title)
        {
            found = true;
            while (i < lines.size())
            {
                outfile << lines[i] << endl;

                if (lines[i] == "----------------------------------------")
                {
                    break;
                }
                i++;
            }
            break;
        }
    }

    outfile.close();

    if (found)
    {
        cout << "Book added to your favorite list!" << endl;
    }
    else
    {
        cout << "Book not found!" << endl;
    }
}

// Function to display the favorite book list
void displayfavoritelist()
{
    ifstream outfile("favoritebooklist.txt"); // Open the file in reading mode
    string filedata;

    cout << endl;
    cout << "-------------------------------" << endl;
    cout << "          Favorite List        " << endl;
    cout << "-------------------------------" << endl;

    while (getline(outfile, filedata)) // Display all lines from the file
    {
        cout << filedata << endl;
    }
}

// Main function to display the menu and handle user choices
int main()
{
    int choice;

    do
    {
        cout << "------------------------------------" << endl;
        cout << "          Menu         " << endl;
        cout << "1. Display Books" << endl;
        cout << "2. Add a New Book" << endl;
        cout << "3. Delete a Book" << endl;
        cout << "4. Favorite List" << endl;
        cout << "5. Exit" << endl;
        cout << "------------------------------------" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            chooseGenre("display");
            break;
        case 2:
            chooseGenre("add");
            break;
        case 3:
            chooseGenre("delete");
            break;
        case 4:
            displayfavoritelist();
            break;
        case 5:
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
