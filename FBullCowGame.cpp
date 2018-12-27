#include "FBullCowGame.h"
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std; 
vector <string> words; 
unordered_map <int32, vector<string>> words_organized; 


FBullCowGame::FBullCowGame()
{	
	words.reserve(300000);
	fillWordsCollection("words_sample.txt");
	Reset(); 
}

FBullCowGame::FBullCowGame(int32 word_length, Difficulty level)
{
	
	srand(time(0)); 
	int randV = rand() % (words_organized[word_length].size() - 1);

	MyHiddenWord = words_organized[word_length][randV]; 
	cout << "\nMy Hidden Word: \n" << MyHiddenWord << endl; 
	GameOver = false; 
	MyMaxTries = ComputeDifficulty(level, word_length); 
	MyCurrentTry = 0; 
	return; 


}

void FBullCowGame::Reset()
{
	srand(time(0));
	int32 randWL = rand() % 14 + 1;
	int32 randD = rand() % 3 + 1;
	Difficulty randomDiff; 

	switch (randD) {
	case 1:
		randomDiff = Difficulty::Beginner;

	case 2:
		randomDiff = Difficulty::Amateur;

	case 3:
		randomDiff = Difficulty::Professional;

	case 4:
		randomDiff = Difficulty::Legendary;
	}

	FBullCowGame(randWL, randomDiff); 
	return; 
}

int32 FBullCowGame::GetMaxTries() const
{
	return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry; 
}

int32 FBullCowGame::GetWordLength() const
{
	return MyHiddenWord.length();
}

int32 FBullCowGame::ComputeDifficulty(Difficulty lev, int32 len) const
{
	int32 beginnerBonus = 5; 
	int32 amateurBonus = 3; 

	if (lev == Difficulty::Beginner) {
		return len + beginnerBonus; 
	}

	else if (lev == Difficulty::Amateur) {
		return len + amateurBonus; 
	}

	else if (lev == Difficulty::Legendary) {
		return len; 
	}

	else {

		return max(5, len - 2); 
	}


}

bool FBullCowGame::GetGameStatus() const
{
	return GameOver;
}

void FBullCowGame::IsGameWon(BullCowCount score) 
{
	if (score.Bulls == MyHiddenWord.length()) {
		cout << "You win!!\n"; 
		GameOver = true; 
	}
}

void FBullCowGame::fillWordsCollection(FString file_name)
{
	ifstream Reader; 
	Reader.open(file_name);

	string oneWord; 

	if (!Reader) {

		cout << "File not found";
	} 

	while (Reader.good()) 
	{
		getline(Reader, oneWord, ','); 

		if (IsIsogram(oneWord)) {

			words.push_back(oneWord);

		}
		
	}

	Reader.close(); 

	for (int i = 0; i < words.size(); i++) {
		
		words_organized[words[i].length()].push_back(words[i]);
	}
}

bool FBullCowGame::IsIsogram(FString guess) const
{
	unordered_map<char, int> words; 
	for (int i = 0; i < guess.length(); i++) 
	{
		if (words.find(guess[i]) == words.end()) {
			words[guess[i]] = i; 
		}

		else {

			return false; 

		}
	}

	return true; 
	
}

bool FBullCowGame::IsAllLowerCase(FString guess) const
{
	for (int i = 0; i < guess.length(); i++) {

		if (isupper(guess[i])) {
			return false; 
		}
	}
	return true;
}

bool FBullCowGame::IsEmptyGuess(FString guess) const
{
	if (guess.length() == 0) {
		return true;
	}
	else {
		return false; 
	}; 
}

bool FBullCowGame::HasNoNumericCharacters(FString guess) const
{
	for (int i = 0; i < guess.length(); i++) {
		if (isdigit(guess[i])) {
			return false; 
		}
	};

	return true;
}

EWordStatus FBullCowGame::CheckGuessValidity (FString guess) const
{

	if (IsEmptyGuess(guess)) {
		return EWordStatus::Empty_Guess;
	}

	else if (!(guess.length() == GetWordLength())) {
		return EWordStatus::Guess_Is_Of_Invalid_Length;
	}
	
	else if (!IsIsogram(guess)) {
		return EWordStatus::Not_Isogram; 
	}

	else if (!IsAllLowerCase(guess)) {
		return EWordStatus::Not_LowerCase; 
	}

	else if (!HasNoNumericCharacters(guess)) {
		return EWordStatus::Is_Numeric; 
	}

	else {
		return EWordStatus::OK; 
	}
}

BullCowCount FBullCowGame::SubmitGuess(FString guess)
{
	MyCurrentTry += 1; 
	int32 lengthOfWOrd = MyHiddenWord.length(); 
	BullCowCount CurrentScore; 

	for (int32 i = 0; i < lengthOfWOrd; i ++ ) {

		for (int32 j = 0; j < lengthOfWOrd; j++) {

			if (guess[i] == MyHiddenWord[j]) {
				
				if (i == j) {
					CurrentScore.Bulls ++; 
				} 
				else {
					CurrentScore.Cows ++; 
				}
				continue;
			} 
		}
	}

	return CurrentScore; 
	
}

