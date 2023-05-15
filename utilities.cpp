#include "utilities.h"
#include <bits/stdc++.h>
using namespace std;

utilities::utilities()
{
}
// useful function for breaking sentence into its component words vector
vector<string> utilities::parsingSentence(string sentence)
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
            word += letter;
        }
    }
    words.push_back(word);

    return words;
}

// useful function for dissecting webPage keywords into its component words vector
vector<string> utilities::parsingKeyWords(string sentence)
{
    string word = "";
    vector<string> words;

    for (auto letter : sentence)
    {
        if (letter == ',')
        {
            words.push_back(word);
            word = "";
        }
        else
        {
            word += letter;
        }
    }
    words.push_back(word);

    return words;
}

utilities::~utilities()
{
}