#include "utilities.h"
#include <bits/stdc++.h>
using namespace std;

utilities::utilities()
{

}
vector<string> parsingSentence(string sentence)
    {
        string word = "";
        vector<string> words;

        for (auto letter : sentence)
        {
            if (letter == ' ')
            {
                words.push_back(word);
                word = "";
            }
            else
            {
                word+= letter;
            }
        }
        words.push_back(word);

        return words;
    }



utilities::~utilities()
{

}