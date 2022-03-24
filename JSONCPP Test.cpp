// JSONCPP Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <json/json.h>

int main()
{
    std::vector<std::string> list{ "CIGAR", "REBUT", "SISSY", "HUMPH", "AWAKE", "BLUSH", "FOCAL", "EVADE", "NAVAL", "SERVE", "HEATH", "DWARF", "MODEL", "KARMA", "STINK", "GRADE", "QUIET", "BENCH", "ABATE", "FEIGN", "MAJOR", "DEATH", "FRESH", "CRUST", "STOOL", "COLON", "ABASE", "MARRY", "REACT", "BATTY", "PRIDE", "FLOSS", "HELIX" };

    int word_length = 5;
    int max_word_length = 8;

    Json::Value root;
    root["word length"] = word_length;
    root["dictionary"] = {};

    for (int i = 0; i < list.size(); ++i) {

        root["dictionary"][i]["valid"] = false;

        std::string word = list[i];

        root["dictionary"][i]["word"] = word;

        for (int j = 0; j < word_length; ++j) {

            //std::string index = "char " + std::to_string(j);
            std::string index = std::to_string(j);

            root["dictionary"][i][index] = word.substr(j, 1);
        }

        /*for (int k = word_length; k < max_word_length; ++k) {

            std::string index = std::to_string(k);

            root["dictionary"][i][index] = "null";
        }//*/

    }

    Json::StreamWriterBuilder builder;
    //builder["commentStyle"] = "None";
    //builder["indentation"] = "\t";

    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());

    std::ofstream outputFileStream("test.json");

    writer->write(root, &outputFileStream);

    return 0;
}