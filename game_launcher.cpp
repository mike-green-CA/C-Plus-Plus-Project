// Solution for game_launcher.cpp for soultion COMP2618_Assignment08-A01045801
// 
// Author: Michael Green
// Date: 2020 March, 23.
// Version 1.1

#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

//Function proto-types

void display_Body(int errors);
void prepare_word(const string, string&);
bool check_for_letters(const string, char, string&);
bool isGuessed(const char, const vector<char>);



int main() {

	const vector<string> WORDS = { "execute", "compile", "skating", "cplusplus", "eggplant", "knife", "hello", "world", "canada", "coding" };
	bool play = true;
	bool game_playing = true;

	while (play != false) {

		vector<char> guessedLetters;
		char guess = 0;
		int error_count = 0;
		srand(time(0));	//We need this line to ensure true randomness.
		int random_number = rand() % 10;
		//string theWord = WORDS[random_number];
		string hiddenWord;

		//Copy the randomly chose word into theWord the player must guess.
		prepare_word(WORDS[random_number], hiddenWord);

		cout << "Guess the word: ";
		for (char x : hiddenWord) {
			cout << "X";
		}
		cout << endl;

		while (game_playing == true) { //Used to prompt the user.

			cout << "\n\nGuess a letter: ";
			for (char x : hiddenWord) {
				if (x == '?') {
					cout << "?";
				}
				else {
					cout << static_cast<char>(toupper(x));
				}
			}
			cout << endl;
			cout << "?";
			cin >> guess;	//User is prompted for a letter.

			if (isGuessed(guess, guessedLetters) == false) {

				//Check to see if user entered a letter.
				if (isalpha(guess) == false) {
					cout << "Letters only please.";
				}
				else if (check_for_letters(WORDS[random_number], guess, hiddenWord) == true) { //If the user guessed a correct letter.
						//This algorithm iterates through our vector and checks to see if there is a '?'
						//position will become hiddenWord.end() if there is no '?'.
						auto position = find(hiddenWord.begin(), hiddenWord.end(), '?');

						if (position == hiddenWord.end()) { //If the player has guessed all the letters
							cout << "\n";
							display_Body(error_count);
							cout << "\n";
							guessedLetters.push_back(' ');
							guessedLetters.push_back(toupper(guess));
							cout << "\nYour guesses: \n";
							for (auto letter : guessedLetters) {
								cout << letter;
							}
							cout << "\n\nWord: ";
							for (auto letter : hiddenWord) {
								cout << static_cast<char>(toupper(letter));
							}
							cout << "\n\n\nCongratulations!!! You guessed my word." << endl;
							game_playing = false; //Signal that the game has ended
						}					
						else { //If the player has more letter to guess.
							cout << "\n";
							display_Body(error_count);
							cout << "\n";
							guessedLetters.push_back(' ');
							guessedLetters.push_back(toupper(guess));
							cout << "\nYour guesses: \n";
							for (auto letter : guessedLetters) {
								cout << letter;
							}
						}
				}
				else { //If the player guessed an incorrect letter.
					error_count++; //Increment the error_count
					cout << "\n";
					display_Body(error_count);
					cout << "\n";
					guessedLetters.push_back(' ');
					guessedLetters.push_back(toupper(guess));
					cout << "\nYour guesses: \n";
					for (auto letter : guessedLetters) {
						cout << letter;
					}
				}
			}
			else {
				cout << "'" << static_cast<char>(toupper(guess)) << "' was already guessed. Try another letter.";
			}



			//Game Ending check
			if (error_count >= 7) {
				game_playing = false; //Signal the game has ended

				cout << "\n\n\nSorry - you have run out of guesses ; - (" << endl;
				cout << "The correct answer was: ";
				for (char letter : WORDS[random_number]) {
					cout << static_cast<char>(toupper(letter));
				}
				cout << "\n\n...GAME OVER..." << endl;
			}

		}//End of main game.
		
		//Refresh all containers.
		hiddenWord.clear();
		guessedLetters.clear();

		cout << "\n\nPlay again? (y/n) ";
		cin >> guess;

		if (guess == 'y' || guess == toupper('y')) {
			game_playing = true;
			continue;
		}
		else {
			play = false;
		}
	}//End of the programm entirely. WILL trigger if user enters anything other than Y, or y.

	return 0;
}; //end of main


//Function definitions


// This method is very simple.
// Take the error_count value represented as 'errors' and use a switch statement to print out body parts...
// That corespond to the amount of errors made by the user.
void display_Body(int errors) {

	const int RIGHT_LEG = 92;	// RIGHT_LEG being the ASCII table code for a '\' in decimal.

	switch (errors) {

	case 0: 
		break;

	case 1: cout << " o ";
		break;

	case 2: cout << " o " << endl;
		cout << "/  " << endl;
		break;

	case 3: cout << " o " << endl;
		cout << "/| " << endl;
		break;

	case 4: cout << " o " << endl;
		cout << "/|" << static_cast<char>(RIGHT_LEG) << endl;
		break;

	case 5: cout << " o " << endl;
		cout << "/|" << static_cast<char>(RIGHT_LEG) << endl;
		cout << " | " << endl;
		break;

	case 6: cout << " o " << endl;
		cout << "/|" << static_cast<char>(RIGHT_LEG) << endl; 
		cout << " | " << endl;
		cout << "/  " << endl;
		break;

	case 7: cout << " o " << endl;
		cout << "/|" << static_cast<char>(RIGHT_LEG) << endl;
		cout << " | " << endl;
		cout << "/ " << static_cast<char>(RIGHT_LEG) << endl;
		break;

	default: cerr << "WARNING AN ERROR HAS OCCURED WITH game_launcher.cpp error_count in main()!";
	}
};

//This method takes the randomly chosen word and adds X characters to the hiddenWord for the player to guess.
void prepare_word(const string theWord, string& hiddenWord) {
	
	string holder = theWord;

	for (string::iterator it = holder.begin(); it != holder.end(); it++) {
		hiddenWord.push_back('?');
	}
};

//This method iterates through word and checks to see if the User's guessed letter is in the word.
// If it IS: remove a 'X' from the hiddenWord and replace it with a capital letter version of the user's guess. Then wasFound = true.
// If it ISN'T:  simply return false.
bool check_for_letters(string word, char letter, string& hiddenWord) {

	bool wasFound = false;
	int i = 0;

	for (string::iterator it = word.begin(); it != word.end(); it++, i++) {
		if (letter == *it || toupper(letter) == *it){
			hiddenWord[i] = letter;
			wasFound = true;
		}
	}//Finished scanning the word

	if (wasFound == true) {
		return true;
	}
	else {
		return false;
	}
};

//This method checks to see if the letter the user guessed is already in his guessed letters vector.
// returns FALSE: If the user has input an original guess.
// returns TRUE: If the user has already inputted the value.
bool isGuessed(const char letter, const vector<char> guessed) {

	bool wasGuessed = false;

	for (char item : guessed) {
		if (toupper(letter) == item) {
			wasGuessed = true;
			break;
		}
	}

	return wasGuessed;
};