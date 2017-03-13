#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define MAX_SIZE 100

#define EASY_FILE_NAME "easy.txt"
#define MEDIUM_FILE_NAME "medium.txt"
#define HARD_FILE_NAME "hard.txt"

enum wordGroup {EASY, MEDIUM, HARD};

class Dictionary{
	private:
		string easyWords[MAX_SIZE];
		string mediumWords[MAX_SIZE];
		string hardWords[MAX_SIZE];
	public:
		Dictionary();
		string chooseWord(wordGroup);
		void printWordList(wordGroup);
};

Dictionary::Dictionary()
{
	ifstream wordsFile;
	wordsFile.open(EASY_FILE_NAME, ifstream::in);

	if(!wordsFile.is_open())
	{
		cerr << "Error upon opening \"" << EASY_FILE_NAME << "\"" << endl;
	}
	string str;

	//populate string arrays with words
	for(int i = 0; i < MAX_SIZE && !wordsFile.eof(); i++)
		wordsFile.getline(str, 40);
}

void Dictionary::printWordList(wordGroup type)
{
	switch(type)
	{
		case EASY: 
			for(int i = 0; i < MAX_SIZE && easyWords[i] != ""; i++)
				cout << easyWords[i] << endl;
			break;
		case MEDIUM:
			break;
		case HARD:
			break;		
	}
}

int main(int argc, char ** argv)
{
	Dictionary dict;

	dict.printWordList(EASY);

	return 0;
}