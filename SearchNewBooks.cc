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
	std::stringstream sStream(bookData);

	getline(sStream, ISBN, ',');
	getline(sStream, name, ',');
	getline(sStream, bookType, ',');
}

void Book::testOutput()
{
	std::cout << "Book - " << ISBN << ", " << name << ", " << bookType << "\n\n";
}


// Main Function
int main(int argc, char *argv[])
{
	std::ifstream newBooksFile;

	newBooksFile.open("newbooks.dat");

	if (newBooksFile.is_open())
	{
		std::string newBook, newISBN, newName, newType;

		while (getline(newBooksFile, newBook))
		{			
			Book book (newBook);

			book.testOutput();
		}

		newBooksFile.close();
	}
	else std::cout << "File failed to open!" << '\n';

	return 0;
}
