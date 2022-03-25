// JSONCPP Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <array>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <unordered_set>
#include <string>
#include <vector>

#include <json/json.h>

#include "ScoredWord.h"
#include "LetterCounter.h"


std::vector<std::string> testList{ "CIGAR", "REBUT", "SISSY", "HUMPH", "AWAKE", "BLUSH", "FOCAL", "EVADE", "NAVAL", "SERVE", "HEATH", "DWARF", "MODEL", "KARMA", "STINK", "GRADE", "QUIET", "BENCH", "ABATE", "FEIGN", "MAJOR", "DEATH", "FRESH", "CRUST", "STOOL", "COLON", "ABASE", "MARRY", "REACT", "BATTY", "PRIDE", "FLOSS", "HELIX" };

std::vector<ScoredWord> words{};

// total count of letters in words
std::array<int, 26> tScore;

int dictionarySize = 0;

int word_length = 5;
int max_word_length = 8;

LetterCounter* lC = nullptr;

std::string inputFile = "Wordle List.txt";
std::string outputFile = "Scored Words.json";

Json::Value root;


int main()
{
    std::cout << "Initializing.\n";

    /* open input file */
    std::ifstream input;
    input.open(inputFile);
    
    if (!input.good())
    {
        std::cout << "\nInput file\"" << inputFile << " not found.\n";
        input.close();
        return 0;
    }


    /* read from input file */
    std::cout << "\nInput file \"" << inputFile << "\" found.\n";

    words.clear();

    std::string newWord;

    while (!input.eof())
    {
        getline(input, newWord, ' ');

        words.push_back(ScoredWord(newWord));
    }


    /* close input file */
    input.close();


    /* prepare output data */

    /* sort and tally dictionary*/
    std::cout << "\nPreparing output data.\n";

    //std::sort(words.begin(), words.end(), [](const ScoredWord& a, const ScoredWord& b) { return a.word < b.word; });

    lC = new LetterCounter(words, word_length);

    lC->setTScore(tScore);

    for (ScoredWord& s : words) 
    {
        std::unordered_set<char> uniqueLetters {};

        for (char c : s.word)
        {
            uniqueLetters.emplace(c);

            s.score += tScore[c - 'A'];
        }

        s.score *= uniqueLetters.size();
    }

    std::cout << "\nSorting dictionary.\n";

    std::sort(words.begin(), words.end(), [](const ScoredWord& a, const ScoredWord& b) {return a.score > b.score; });

    root["word length"] = word_length;
    root["dictionary"] = {};
    root["dictionary size"] = words.size();

    for (int i = 0; i < words.size(); ++i) 
    {
        root["dictionary"][i]["valid"] = true;

        root["dictionary"][i]["score"] = words[i].score;

        std::string word = words[i].word;

        root["dictionary"][i]["word"] = word;

        for (int j = 0; j < word_length; ++j) 
        {
            //std::string index = "char " + std::to_string(j);
            std::string index = std::to_string(j);

            root["dictionary"][i][index] = word.substr(j, 1);
        }

        /*for (int k = word_length; k < max_word_length; ++k) 
        {
            std::string index = std::to_string(k);

            root["dictionary"][i][index] = "null";
        }//*/
    }

    std::cout << "\nOutput data ready.\n";


    /* open output file */
    std::ofstream outputFileStream(outputFile);

    std::cout << "\nOutput file \"" + outputFile + "\" created.\n";

    Json::StreamWriterBuilder builder;
    //builder["commentStyle"] = "None";
    //builder["indentation"] = "\t";

    std::cout << "\nJson Stream Writer Builder initialized.\n";

    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

    std::cout << "\nJson Stream Writer initialized.\n";


    /* write to output file */
    writer->write(root, &outputFileStream);

    std::cout << "\nWrite to output file completed.\n";

    return 0;
}