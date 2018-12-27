#include <iostream>
#include "FBullCowGame.h"
#include <string>
#include <fstream>

using namespace std;
using FText = string;
using int32 = int; 
int32 WORD_LENGTH;

void PrintIntro(); 
int32 AskforWordLength(); 
void PlayGame(); 
bool askUser();  
Difficulty AskforDifficulty(); 
FText getFileContents(ifstream&); 
FText GetGuess(); 
FBullCowGame BCGame; // instantiate a new game

ifstream ReaderB("BullsASCii.txt");
ifstream ReaderC("CowsASCii.txt");

FText ArtB = getFileContents(ReaderB);
FText ArtC = getFileContents(ReaderC);

// the entry point32 for our application
int main() 
{	

	bool Wants_To_Play = true; 
	 
	do {
		PrintIntro();
		PlayGame(); 
		Wants_To_Play = askUser();
		BCGame.Reset();
	} while (Wants_To_Play); 
	
	return 0; 
}

bool askUser()
{
	cout << "Do you want to play again?\n";
	FText response;
	getline(cin, response);

	if (response[0] == 'y' || (response[0] == 'Y')) {

		return true;
	}

	else {

		return false; 

	}

}

FText getFileContents(ifstream& File) {

	FText Lines = ""; 

	if (File) {

		while (File.good()) 
		{
			FText TempLine; 
			getline(File, TempLine); 
			TempLine += "\n"; 
			Lines += TempLine; 
		}

		return Lines; 
	}

	else {

		return "Error!!"; 
	}
}

void PrintIntro()
{
	int32 WORD_LENGTH; 
	Difficulty diff; 
	cout << "Welcome to Bulls and Cows!!\n";
	FText userDifficulty; 
	cout << "Do you want to chose difficulty?"; 
	getline(cin, userDifficulty); 

	if (userDifficulty[0] == 'y' || (userDifficulty[0] == 'Y')) {

		WORD_LENGTH = AskforWordLength(); 
		diff = AskforDifficulty();
		BCGame = FBullCowGame(WORD_LENGTH, diff); 
	}

	cout << "Can you guess the ";
	cout << BCGame.GetWordLength(); 
	cout << " letter isogram I'm thinking of?\n";
	return; 

}

int32 AskforWordLength() 
{
	int32 len; 
	cout << "Enter number of words required from 2 - 15\n"; 
	cin >> len; 
	return len; 
}

Difficulty AskforDifficulty() {
	int32 DifficultyInteger; 
	cout << "Choose your difficulty level \n";
	cout << "Enter 1 for Beginner Level\n";
	cout << "Enter 2 for Amateur Level\n";
	cout << "Enter 3 for Professional Level\n"; 
	cout << "Enter 4 for Legendary Level\n"; 
	cin >> DifficultyInteger; 
	cout << "\nDifficulty Level is " << DifficultyInteger; 

	switch (DifficultyInteger) {
		case 1:
			return Difficulty::Beginner;

		case 2:
			return Difficulty::Amateur;

		case 3:
			return Difficulty::Professional;

		case 4:
			return Difficulty::Legendary; 
	}
}

void PlayGame() 
{ 
	int32 MaxTries = BCGame.GetMaxTries(); 
	int32 i = 0; 
	while ((i < MaxTries) && (!BCGame.GetGameStatus())) {
		
		FText guess = GetGuess();
	
	}

	// TODO ADD GAME SUMMARY 

}


string GetGuess() {

	EWordStatus status = EWordStatus::Empty_Guess; 
	FText User_Input;

	do {

		int32 CurrentTry = BCGame.GetCurrentTry(); 
		//get a guess from the player
		cout << "Try " << CurrentTry << " Enter your guess: ";
		getline(cin, User_Input);

		status = BCGame.CheckGuessValidity(User_Input);

		switch (status) {

		case EWordStatus::Empty_Guess:

			cout << "An Empty Input is invalid.\n";
			break;

		case EWordStatus::Guess_Is_Of_Invalid_Length:
				
			cout << "Your input was of invalid length!!";
			cout << "\nPlease enter a " << WORD_LENGTH << " letter word!\n"; 
			break; 

		case EWordStatus::Not_Isogram:

			cout << "Your input must be an isogram\n";
			break;

		case EWordStatus::Not_LowerCase:
			cout << "Please ensure your guess is comprised of only lower case characters\n"; 
			break; 

		case EWordStatus::Is_Numeric:
			cout << "No numeric characters are allowed in your input.\n"; 
			break; 

		default:

			BullCowCount BullCowCount = BCGame.SubmitGuess(User_Input);
			// repeat the guess back to them
			cout << ArtB << "\n"; 
			cout << "Number of bulls: " << BullCowCount.Bulls;
			cout << "\n";
			cout << ArtC << "\n"; 
			cout << "Number of cows: " << BullCowCount.Cows; 
			cout << "\n\n";
			BCGame.IsGameWon(BullCowCount); 
			break; 

		}

	} while (status != EWordStatus::OK); 
	return User_Input; 
}