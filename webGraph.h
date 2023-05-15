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
    float clicks;
    float pageRank;
    float tempPageRank;
    float CTR;
    float score;
    int hyperLinksCount;

    vector<string> keyWords;

    //-----Initializing a webPage----------//
    webPage(string url)
    {
        URL = url;
        impressions = 0;
        clicks = 0;
        CTR = 0;
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
    // visisted checklist for search results
    map<webPage *, bool> visited;
    void clearVisited();
    // for use in displaying results
    vector<webPage *> webPageResults;
    vector<string> parsingKeyWords(string sentence);

    void addEdge(webPage *src, webPage *dst);
    void addInvEdge(webPage *src, webPage *dst);

    void pageRankIteration();
    void CTRCalc();
    void scoreCalc();

    void printAll();

    bool cmpPages(webPage *a, webPage *b)
    {
        return a->score > b->score;
    }

    webGraph();
    ~webGraph();
};

#endif