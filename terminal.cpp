#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <time.h>
#include <sys/time.h>

using namespace std;

#define MAX_SIZE 200
#define WORD_CHOICES 10

#define EASY_FILE_NAME "easy.txt"
#define MEDIUM_FILE_NAME "medium.txt"
#define HARD_FILE_NAME "hard.txt"

enum wordGroup {EASY, MEDIUM, HARD};

class Dictionary{
	private:
		string easyWords[MAX_SIZE];
		string mediumWords[MAX_SIZE];
		string hardWords[MAX_SIZE];
		int secretSpot; //position of the secret answer word
		int totalEasyWords;
	public:
		Dictionary();
		int wordCount; //number of choice words so far
		string chooseWord(wordGroup); //picks random word from dictionary list
		string choiceWords[WORD_CHOICES]; //holds randomly selected words from list
		void printWordList(wordGroup);
		void printChoicesList();
		int guesses;
};

Dictionary::Dictionary()
{
	wordCount = 0;

	ifstream wordsFile;
	wordsFile.open(EASY_FILE_NAME, ifstream::in);

	if(!wordsFile.is_open())
	{
		cerr << "Error upon opening \"" << EASY_FILE_NAME << "\"" << endl;
	}

	//populate string arrays with words
	//cout << "\t\tBuilding easy words list..." << endl;
	int j = 0;
	for(int i = 0; i < MAX_SIZE && !wordsFile.eof(); i++)
	{
		getline(wordsFile, easyWords[i], ' ');
		j++;
	}
	totalEasyWords = j;
}

void Dictionary::printWordList(wordGroup type)
{
	switch(type)
	{
		case EASY: 
			cout << "\t\tPrinting easy words list..." << endl;
			for(int i = 0; i < MAX_SIZE && easyWords[i] != ""; i++)
				cout << easyWords[i] << endl;
			break;
		case MEDIUM:
			break;
		case HARD:
			break;		
	}
}

string Dictionary::chooseWord(wordGroup type)
{
	string word;
	int random;
	int i = 0;
	struct timeval t1;
	gettimeofday(&t1, NULL);
	srand(t1.tv_usec * t1.tv_sec);

	switch(type)
	{
		case EASY: 
			//cout << "\t\tSelecting random easy word..." << endl;
			random = rand() % totalEasyWords;
			while(i < wordCount)
			{
				if(easyWords[random] == choiceWords[i])
				{
					random = rand() % totalEasyWords;
					i = 0;
				}
				else
					i++;
			}
			choiceWords[wordCount] = easyWords[random];
			break;
		case MEDIUM:
			break;
		case HARD:
			break;		
	}

	return easyWords[random];
}

void Dictionary::printChoicesList()
{
	//cout << "\t\t Printing choices alphabetically..." << endl;
	for(int i = 0; i < 26; i++)
	{
		for(int j = 0; j < WORD_CHOICES; j++)
			if(choiceWords[j][0] == 'a' + i)
				cout << j << " " << choiceWords[j] << "\t";
		//cout << (WORD_CHOICES - i) << " " << choiceWords[WORD_CHOICES - i] << endl;
	}
	cout << endl;
}

int main(int argc, char **argv)
{
	Dictionary dict;

	//dict.printWordList(EASY);
	string word;

	//populate random word list
	for(int i = 0; i < WORD_CHOICES; i++)
	{
		dict.choiceWords[i] = dict.chooseWord(EASY);
		dict.wordCount++;
	}

	dict.printChoicesList();

	string answer = dict.choiceWords[rand() % WORD_CHOICES]; //random number
	string guess;
	int guessesLeft = 4;
	bool incorrect = true;
	int sameLetterPosition;
	do{
		sameLetterPosition = 0;
		for(int i = 0; i < guessesLeft; i++)
			cout << "* " ;
		cout << endl << "Your guess: " ;
		getline(cin, guess);
		if(guess == answer)
			incorrect = false;
		else
		{
			guessesLeft--;
			for(int i = 0; i < 4; i++)
				if(answer[i] == guess[i])
					sameLetterPosition++;
			cout << "Matched: " << sameLetterPosition << " letters" << endl;
		}
	} while(incorrect && guessesLeft);

	if(!incorrect)
		cout << "Congratulations!" << endl;
	else
		cout << "System has locked you out. Contact an administrator." << endl;

	return 0;
}
