#pragma once

#include <string>

struct ScoredWord
{
	std::string word = "";	// text of the word

	int score = 0;			// the score of the word

	bool validGuess = true;	// is the word possibly a correct answer

	ScoredWord(std::string w) : word(w) {}
};