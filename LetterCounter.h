#pragma once

#include "ScoredWord.h"
#include <array>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

class LetterCounter
{
private:
	bool _parsed = false;

	int _displaySize = 5;

	const std::string _vowels = "AEIOU";


	std::vector<std::array<int, 26>> _pScore; // count of each letter at each position, used for sorting

	std::vector<std::array<std::pair<int, char>, 26>> _plc {{}}; // count of each letter for each 


	std::array<std::pair<int, char>, 26> _tlc{}; // total count of letters across every word and position

	void _mcl(const std::array<std::pair<int, char>, 26> &arr, int listSize); // calculate most common letters

	void _mcc(const std::array<std::pair<int, char>, 26> &arr, const int listSize); // calculate most common consonants (includes y)

	void _mcv(const std::array<std::pair<int, char>, 26> &arr, int listSize); // calculate most common vowels (excludes y)

protected:
	LetterCounter();

public:
	LetterCounter(std::vector<ScoredWord>& vectorName, const int wordLength);

	//---

	void setTScore(std::array<int, 26> &tScore);

	const std::vector<std::array<int, 26>> &PScore() { return _pScore; }
	 
	//---

	void parse(std::vector<ScoredWord> &wordVector, const int wordLength);

	void parseNewText(std::vector<ScoredWord> &newVector, const int wordLength);

	//---

	void mostCommonLetters(const int listSize);

	void mostCommonLettersAt(int position, const int listSize, const int wordLength);

	void mostCommonLettersAllPos(const int listSize, const int wordLength);

	//---

	void mostCommonConsonants(int listSize);

	void mostCommonConsonantsAt(int position, int listSize, const int wordLength);

	void mostCommonConsonantsAllPos(int listSize, const int wordLength);

	//---

	void mostCommonVowels();

	void mostCommonVowelsAt(int position, const int wordLength);

	void mostCommonVowelsAllPos(const int wordLength);
};