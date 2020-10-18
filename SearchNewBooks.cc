// ECS 36C Program 1
// 
// Filename:	SearchNewBooks.cc
// Developer:	Peter Reynolds
// Date:	October 07, 2020
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>


// Class for storing book information
class Book
{
	private:
	    std::string ISBN;
	    std::string language;
	    std::string bookType;

	public:
	    Book(std::string);	// Constructor takes a comma delimited string with the ISBN, name, and type
	    void testOutput();
            bool operator<(const Book&) const;
            bool operator==(const Book&) const;
            bool operator>(const Book&) const;
};

Book::Book(std::string bookData)
{
    // Create a stream from the given data
    std::stringstream sStream(bookData);

    // Read each section of the line for the book's information
    getline(sStream, ISBN, ',');
    getline(sStream, language, ',');
    getline(sStream, bookType, ',');
}

void Book::testOutput()
{
    std::cout << "Book - " << ISBN << ", " << language << ", " << bookType;
}

bool Book::operator<(const Book& other) const
{
    // Sort on ISBN number first if they are different
    if (ISBN != other.ISBN)
        return (ISBN < other.ISBN);

    // Sort on language second if they are different
    if (language == other.language)
        return (language > other.language);

    // Sort by book type third
    return (bookType == "new" ||                                        // If the first book is "new" then it is sorted first
            (bookType == "used" && other.bookType != "new") ||          // If the first book is "used" then it is sorted first unless the second book is "new"
            (bookType == "digital" && other.bookType == "digital"));    // If the first book is "digital" then it is only sorted first if the second book is also "digital"
}

bool Book::operator==(const Book& other) const
{
    return ((ISBN == other.ISBN) && (language == other.language) && (bookType == other.bookType));
}

bool Book::operator>(const Book& other) const
{
    // Sort on ISBN number first if they are different
    if (ISBN != other.ISBN)
        return (ISBN > other.ISBN);

    // Sort on language second if they are different
    if (language == other.language)
        return (language > other.language);

    // Sort by book type third
    return (bookType == "digital" ||                                        // If the first book is "new" then it is sorted first
            (bookType == "used" && other.bookType != "digital") ||          // If the first book is "used" then it is sorted first unless the second book is "new"
            (bookType == "new" && other.bookType == "new"));    // If the first book is "digital" then it is only sorted first if the second book is also "digital"
}


void ReadBookFileIntoVector(std::string filename, std::vector<Book> &bookVector)
{
    // Open the given file for reading
    std::ifstream newBooksFile;
    newBooksFile.open(filename);

    // Check that the file opened correctly
    if (newBooksFile.is_open())
    {
        // Data read from file into the newBook string
	std::string newBook;

        // Read the next line from the file
	while (getline(newBooksFile, newBook))
	{
            // Construct a new book from the data read from the file
            Book book (newBook);

            // Add book to the vector
            bookVector.push_back(book);
	}
        // Close the file
	newBooksFile.close();
    }
    // Report a problem if the file fails to open
    else std::cout << "File failed to open!" << '\n';


}

// Linear search for a book through a vector
bool LinearSearch(const Book &book, const std::vector<Book> &bookVect)
{
    // Loop through each index of the vector
    for (int i=0; i<(int)bookVect.size(); i++)
    {
        // If the book is found at position i, return true
        if (bookVect[i] == book)
            return true;
    }

    // Retrun false if the book is not found
    return false;
}

// Binary search for a book through a vector
bool BinarySearch(const Book &book, const std::vector<Book> &bookVect)
{
    // The book being searched for will be between positions i and j
    int i=0;
    int j=bookVect.size()-1;

    // Continue searching while there is more than one book between i and j
    while (i < j)
    {
        // Find the mid position between i and j
        int m = (i + j) / 2;

        // Check if the book is to the left or right of m
        if (book > bookVect[m])
            i = m + 1;          // Book is in the right half
        else
            j = m;              // Book is in the left half
    }

    if (book == bookVect[i])
        return true;            // Book is at the ending position, return true
    else
        return false;           // Book is not at the ending position, return false
}

// Function for debugging vector data
void DisplayBookVector(std::string header, std::vector<Book> &bookVect)
{
    std::cout << header << "\n\t";

    for (std::vector<Book>::iterator it=bookVect.begin(); it!=bookVect.end(); ++it)
    {
        it->testOutput();
        std::cout << "\n\t";
    }

    std::cout << "\n";
}


// Main Function
int main(int argc, char *argv[])
{
    // Check that the right number of arguments were given to the program
    if (argc < 4)
    {
        std::cerr << "Missing filename arguments\n\n";
        return 0;
    }

    // Vector with the available books
    std::vector<Book> bookVector;
    // Read the books from newbooks into the vector
    ReadBookFileIntoVector(argv[1], bookVector);

    // Vector with the books being requested
    std::vector<Book> reqVector;
    // Read the books from request into the vector
    ReadBookFileIntoVector(argv[2], reqVector);

    std::sort(bookVector.begin(), bookVector.end());

    // Number for requested books found
    int booksFound = 0;
    for (std::vector<Book>::iterator reqIt=reqVector.begin(); reqIt!=reqVector.end(); reqIt++)
    {
        booksFound += (BinarySearch(*reqIt, bookVector));
    }

    std::cout << "Found " << booksFound << " of the books reqested.\n\n";




    return 0;
}
