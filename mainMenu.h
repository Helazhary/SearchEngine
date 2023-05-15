#ifndef MAINMENU_H
#define MAINMENU_H
#include <bits/stdc++.h>
#include "webGraph.h"
using namespace std;

#pragma once

class mainMenu : public webGraph
{
public:
    mainMenu();                                               // constructor (runs program)
    void searchDisplay();                                     // Opens up action options
    void interactiveDisplay(vector<webPage *> searchResults); // displays all websites from search
    static bool cmpScore(webPage *x, webPage *y);             // used to sort webpage results by score
    ~mainMenu();                                              // deconstructor for program termination
};

#endif