#ifndef WEBGRAPH_H
#define WEBGRAPH_H
#include <bits/stdc++.h>
using namespace std;

#pragma once
struct webPage
{
    //--------Components of a webPage-------//
    string URL;
    int impressions;
    int clicks;
    float pageRank;
    float tempPageRank;
    int ctr;
    int score;
    int hyperLinksCount;
    
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
        ctr = 0;
        pageRank = 0;
        score = 0;
        hyperLinksCount = 0;
    }
};

class webGraph
{
public:
    // adjacency list to represent the webGraph
    map<webPage *, vector<webPage *>> adjList;
    // inverse adjacency list to represent the webPages that point to a webPage
    map<webPage *, vector<webPage *>> inv_adjList;
    // vector to store the individual webPages
    vector<webPage *> webPages;
    // search list by webAddress/name
    map<string, webPage *> searchList;

    vector<string> parsingKeyWords(string sentence);

    void addEdge(webPage *src, webPage *dst);
    void addInvEdge(webPage *src, webPage *dst);

    void pageRankIteration();

    void printAll();

    webGraph();
    ~webGraph();
};

#endif