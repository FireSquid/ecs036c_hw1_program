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
            bool operator<(const Book&);
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
    std::cout << "Book - " << ISBN << ", " << language << ", " << bookType << "\n\n";
}

bool Book::operator<(const Book& other)
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

            book.testOutput();

            // Add book to the vector
            bookVector.push_back(book);
	}
        // Close the file
	newBooksFile.close();
    }
    // Report a problem if the file fails to open
    else std::cout << "File failed to open!" << '\n';


}


// Main Function
int main(int argc, char *argv[])
{
    // Vector with the available books
    std::vector<Book> bookVector;
    // Read the books from newbooks into the vector
    ReadBookFileIntoVector("newbooks.dat", bookVector);

    bookVector[2].testOutput();

    // Vector with the books being requested
    std::vector<Book> reqVector;
    // Read the books from request into the vector
    ReadBookFileIntoVector("request.dat", reqVector);

    reqVector[1].testOutput();

    std::cout << " --- SORTED --- \n\n";

    std::sort(bookVector.begin(), bookVector.end());

    for (std::vector<Book>::iterator it=bookVector.begin(); it!=bookVector.end(); ++it)
        it->testOutput();

    return 0;
}
