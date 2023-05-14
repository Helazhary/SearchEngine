#include "mainMenu.h"
#include <bits/stdc++.h>
using namespace std;

mainMenu::mainMenu()
{
    int menuChoices = 0;
    cout << "Search Engine Menu: \n\n"
         << "1. Perform a Search\n"
         << "2. Exit\n";
    cin >> menuChoices;
    switch (menuChoices)
    {
    case (1):
        system("clear");
        cout<<"the next options\n";
        break;

    case (2):
        break;
    }
}

mainMenu::~mainMenu()
{

}