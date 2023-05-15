#ifndef MAINMENU_H
#define MAINMENU_H
#include <bits/stdc++.h>
#include "webGraph.h"
using namespace std;

#pragma once


class mainMenu : public webGraph
{
public:
    mainMenu();
    void searchDisplay();
    void interactiveDisplay(vector<webPage*> searchResults);
   static bool cmpScore(webPage *x, webPage *y);
    void sortSearchResults(vector<webPage*> searchResults);
    ~mainMenu();    

private:

};

#endif