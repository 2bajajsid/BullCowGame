#pragma once
#include <iostream>
#include <unordered_map>

using FString = std::string;
using int32 = int; 

struct BullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;

};

enum class EWordStatus 
{ 
	OK,
	Not_Isogram, 
	Guess_Is_Of_Invalid_Length,
	Empty_Guess,
	Not_LowerCase, 
	Is_Numeric
};

enum class EResetStatus
{
	No_Hidden_Word,
	OK
};

enum class Difficulty 
{
	Beginner,
	Amateur, 
	Professional, 
	Legendary
};

class FBullCowGame {
public:

	FBullCowGame(); 
	FBullCowGame(int32, Difficulty); 
	void Reset(); //TODO make a more rich return value
	int32 GetMaxTries() const; 
	int32 GetCurrentTry() const; 
	int32 GetWordLength() const; 
	int32 ComputeDifficulty(Difficulty, int32) const; 
	bool GetGameStatus() const; 
	void IsGameWon(BullCowCount); 
	void fillWordsCollection(FString); 
	bool IsIsogram(FString) const; 
	bool IsAllLowerCase(FString) const; 
	bool IsEmptyGuess(FString) const; 
	bool HasNoNumericCharacters(FString) const; 
	EWordStatus CheckGuessValidity(FString) const; 
	BullCowCount SubmitGuess(FString); 


private: 
	int32 MyCurrentTry; 
	int32 MyMaxTries; 
	FString MyHiddenWord; 
	bool GameOver; 
};
