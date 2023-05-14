#include "webGraph.h"
#include "utilities.h"
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
    vector<string> extracKeyWords = {};
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

        //cout<<web<<" ~ "<<preKeyWords<<"\n";

      extracKeyWords = utilities::parsingKeyWords(preKeyWords);
        // searchList[web]->keyWords.push_back("test");
        // cout<<searchList[web]->impressions;
    }
   // printGraph();
}

void webGraph::addEdge(webPage *src, webPage *dst)
{
    adjList[src].push_back(dst);   
}

void webGraph::printGraph()
{
    for (auto it : adjList)
    {
        cout << (it.first)->URL;
        for(int i=0; i<it.second.size(); i++)
        cout<<" ~ "<<it.second[i]->URL;
        cout<<"\n";
        
        
        /*
                     To print keywords

        for(int i=0; i<it.first->keyWords.size(); i++)
        cout<<it.first->keyWords[i];
        cout<<"\n";

        */ 
    }
    
}

webGraph::~webGraph()
{
}