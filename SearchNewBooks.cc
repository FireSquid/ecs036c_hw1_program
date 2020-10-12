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


// Class for storing book information
class Book
{
	private:
		std::string ISBN;
		std::string name;
		std::string bookType;

	public:
		Book(std::string);	// Constructor takes a comma delimited string with the ISBN, name, and type
		void testOutput();
};

Book::Book(std::string bookData)
{
        // Create a stream from the given data
	std::stringstream sStream(bookData);

        // Read each section of the line for the book's information
	getline(sStream, ISBN, ',');
	getline(sStream, name, ',');
	getline(sStream, bookType, ',');
}

void Book::testOutput()
{
	std::cout << "Book - " << ISBN << ", " << name << ", " << bookType << "\n\n";
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

    return 0;
}
