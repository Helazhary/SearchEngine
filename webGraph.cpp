#include "webGraph.h"
#include <bits/stdc++.h>
using namespace std;

webGraph::webGraph()
{
    adjList = {};
    webPages = {};
    searchList = {};

    //--Insert webPages into vector for ease of external access--//
    //---Copy impressions to the webPage struct variable---//
    ifstream impressionsFile("impressions.csv");
    if (!impressionsFile.is_open())
    {
        cout << "Error: Unable to open impressions file.\n";
    }
    string line_i;
    while (getline(impressionsFile, line_i))
    {
        stringstream ss(line_i);
        string impressionNum, webAddress;
        getline(ss, webAddress, ',');
        getline(ss, impressionNum);
        while (impressionNum[0] == ' ')
            impressionNum.erase(impressionNum.begin());

        webPage *temp = new webPage(webAddress);
        temp->impressions = stof(impressionNum);
        temp->URL = webAddress;
        webPages.push_back(temp);
        searchList[webAddress] = temp;
    }

    //---Insert webPages into graph---//

    ifstream edgesFile("edges.csv");
    if (!edgesFile.is_open())
    {
        cout << "Error: Unable to open edges file.\n";
    }

    string line_e;
    while (getline(edgesFile, line_e))
    {
        stringstream ss(line_e);
        string src, dst;
        getline(ss, src, ',');
        getline(ss, dst);
        while (dst[0] == ' ')
            dst.erase(dst.begin());
        addEdge(searchList[src], searchList[dst]);
    }

    //---Add keyWords to vector in webPages---//
    string line_k;
    ifstream keyWordFile("keywords.csv");
    if (!keyWordFile.is_open())
    {
        cout << "Error: Unable to open keyWords file.\n";
    }
    vector<string> keyWords;
    while (getline(keyWordFile, line_k))
    {
        stringstream ss(line_k);
        string web, preKeyWords;
        getline(ss, web, ',');
        getline(ss, preKeyWords);
        while (preKeyWords[0] == ' ')
        {
            preKeyWords.erase(preKeyWords.begin());
        }
        parsingKeyWords("hello,bello");
        //keyWords = parsingKeyWords(preKeyWords);
    }
}
vector<string> parsingKeyWords(string sentence)
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
void webGraph::addEdge(webPage *src, webPage *dst)
{
    adjList[src].push_back(dst);
}

webGraph::~webGraph()
{
}
