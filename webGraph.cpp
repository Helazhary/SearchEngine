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

    // initializing page rank for furhter iterations
    for (auto it : webPages)
    {
        it->pageRank = (1 / (float)webPages.size());
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


        extracKeyWords = utilities::parsingKeyWords(preKeyWords);
        searchList[web]->keyWords = extracKeyWords;
    }
    // printAll();

    //--Constructing inverse adjacency list--//
    for (auto it : adjList)
    {
        for (auto node : adjList[it.first])
        {
            addInvEdge(node, it.first);
        }
    }

    int iterations = 10;
    for(int i=0; i<iterations; i++)
    {
        pageRankIteration(); 
    }

    clearVisited();
    
}

void webGraph::addEdge(webPage *src, webPage *dst)
{
    adjList[src].push_back(dst);
    src->hyperLinksCount++;
}
void webGraph::addInvEdge(webPage *src, webPage *dst)
{
    inv_adjList[src].push_back(dst);
}

void webGraph::printAll()
{
    for (auto it : adjList)
    {
        cout << (it.first)->URL << "\n\n";
        cout << "Hyperlinks:\n";
        for (int i = 0; i < it.second.size(); i++)
            cout << " ~ " << it.second[i]->URL;
        cout << "\n\n";

        cout << "Keywords:\n";
        for (int i = 0; i < it.first->keyWords.size(); i++)
            cout << " ~ " << it.first->keyWords[i];
        cout << "\n";

        cout << "\nLogistics:\n";
        cout << "Impressions: " << it.first->impressions << "\n";
        cout << "Clicks: " << it.first->clicks << "\n";
        cout << "CTR: " << it.first->ctr << "\n";
        cout << "pageRank: " << it.first->pageRank << "\n";
        cout << "Score: " << it.first->score << "\n";
        cout << "hyperLinksCount: " << it.first->hyperLinksCount << "\n";

        cout << "\n\n";
    }
}

void webGraph::pageRankIteration()
{
    for (auto it : inv_adjList)
    {
        it.first->tempPageRank = 0;
      //  cout<<it.first->URL<<"\n";
        for (auto node : inv_adjList[it.first])
        {
          //  cout<<node->URL<<" - "<<node->pageRank<<" - "<<node->hyperLinksCount<<"\n";
            it.first->tempPageRank += node->pageRank / node->hyperLinksCount;
        }
    }
    for (auto it2 : webPages)
    {
        it2->pageRank = it2->tempPageRank;
       // cout<<it2->URL<<"~~"<<it2->pageRank<<"\n";
    }
   // cout<<"\n\n";
}
void webGraph::clearVisited()
{
    //initialize bool map to false/unvisited
    for(auto page : webPages)
    visited[page]=false;
}
webGraph::~webGraph()
{
}