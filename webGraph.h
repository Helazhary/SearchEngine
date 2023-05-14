#ifndef WEBGRAPH_H
#define WEBGRAPH_H
#include <bits/stdc++.h>
using namespace std;

#pragma once
struct webPage
{
    //--------Components of a webPage-------//
    string URL;
    float impressions;
    int clicks;
    int pageRank;
    int score;
    vector<string> keyWords;

    //----overloading Comparison Operator Using webPage score----//
    bool operator<(const webPage &other) const
    {
        return score < other.score;
    }

    //-----Initializing a webPage----------//
    webPage(string url)
    {
        URL = url;
        impressions = 0;
        clicks = 0;
        pageRank = 0;
        score = 0;
        keyWords = {};
    }
};

class webGraph
{
public:
    // adjacency list to represent the webGraph
    map<webPage *, list<webPage *>> adjList;
    // vector to store the individual webPages
    vector<webPage *> webPages;
    // search list by webAddress/name
    map<string, webPage *> searchList;

    vector<string> parsingKeyWords(string sentence);
    
    void addEdge(webPage *src, webPage *dst);
     

    webGraph();
    ~webGraph();
};

#endif