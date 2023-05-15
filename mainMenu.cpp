#include "mainMenu.h"
#include "webGraph.h"
#include "utilities.h"
#include <bits/stdc++.h>
using namespace std;

mainMenu::mainMenu()
{
    int menuChoices = 0;
    cout << "Search Engine Menu: \n\n"
         << "1. Perform a Search\n"
         << "2. Exit\n";
    cin >> menuChoices;
    while (menuChoices < 1 || menuChoices > 2)
    {
        cout << "Invalid input, try again: ";
        cin >> menuChoices;
    }
    switch (menuChoices)
    {
    case (1):
        system("clear");
        searchDisplay();
        break;

    case (2):
        break;
    }
}
void mainMenu::searchDisplay()
{
    // Assuming 2 words seperated by AND, OR, Quotations, or nothing(considered OR)
    system("clear");
    string query;
    vector<string> searchWords;
    vector<webPage *> relevantWebPages = {};
    cout << "Searching for: ";
    cin.ignore();
    getline(cin, query);
    searchWords = utilities::parsingSentence(query);
    map<string, bool> keys;
    int pageNum = 0;

cout<<"\n";
for(auto word : searchWords)
cout<<word<<"\n";
cout<<"\n";

    // 1 word case
    if (searchWords.size() == 1)
    {
        for (int web = 0; web < webPages.size(); web++)
        {
            for (int i = 0; i < webPages[web]->keyWords.size(); i++)
            {
                if (webPages[web]->keyWords[i] == searchWords[0])
                {
                    relevantWebPages.push_back(webPages[web]);
                }
            }
        }
        
        interactiveDisplay(relevantWebPages);
        relevantWebPages = {};
        clearVisited();
    } // parentheses case
    else if (searchWords[0].front() == '\"')
    {
        cout << "\n";
        cout << searchWords[0] << "\n";
        cout << searchWords[1] << "\n";
        searchWords[1].pop_back();
        searchWords[0].erase(searchWords[0].begin());
        cout << "\n";
        cout << searchWords[0] << "\n";
        cout << searchWords[1] << "\n";

        for (int web = 0; web < webPages.size(); web++)
        {
            for (int i = 0; i < webPages[web]->keyWords.size(); i++)
            {
                if ((webPages[web]->keyWords[i] == (searchWords[0] + " " + searchWords[1]) && visited[webPages[web]] == false))
                {

                    relevantWebPages.push_back(webPages[web]);
                    visited[webPages[web]] = true;
                }
            }
        }
      
        interactiveDisplay(relevantWebPages);
        relevantWebPages = {};
        clearVisited();
    }
    // OR case
    else if (searchWords[1] == "OR")
    {
        if (searchWords.size() == 2)
        {
            searchWords.insert(searchWords.begin() + 1, "OR");
        }
        for (int web = 0; web < webPages.size(); web++)
        {
            for (int i = 0; i < webPages[web]->keyWords.size(); i++)
            {
                if ((webPages[web]->keyWords[i] == searchWords[0] || webPages[web]->keyWords[i] == searchWords[2]) && visited[webPages[web]] == false)
                {

                    relevantWebPages.push_back(webPages[web]);
                    visited[webPages[web]] = true;
                }
            }
        }

       
        interactiveDisplay(relevantWebPages);
        relevantWebPages = {};
        clearVisited();
    } // AND case
    else if (searchWords[1] == "AND")
    {
        keys[searchWords[0]] = false;
        keys[searchWords[2]] = false;
        for (int web = 0; web < webPages.size(); web++)
        {
            for (int i = 0; i < webPages[web]->keyWords.size(); i++)
            {
                if (webPages[web]->keyWords[i] == searchWords[0])
                {
                    keys[searchWords[0]] = true;
                }
                if (webPages[web]->keyWords[i] == searchWords[2])
                {
                    keys[searchWords[2]] = true;
                }
                if (keys[searchWords[0]] == true && keys[searchWords[2]] == true && visited[webPages[web]] == false)
                {
                    relevantWebPages.push_back(webPages[web]);
                    visited[webPages[web]] = true;

                    keys[searchWords[0]] = false;
                    keys[searchWords[2]] = false;
                    continue;
                }
            }
        }
        keys[searchWords[0]] = false;
        keys[searchWords[2]] = false;

   
        interactiveDisplay(relevantWebPages);
        relevantWebPages = {};
        clearVisited();
    }
}

// Displays the websites the user can choose to select or make a new search//
void mainMenu::interactiveDisplay(vector<webPage *> searchResults)
{
    for (auto page : searchResults)
    {
        page->impressions++;
    }
    if (!searchResults.size() == 0)
        cout << "Here are the results:\n";
    else
        cout << "No Results\n";

    int pagenum = 0;
    for (auto page : searchResults)
    {
        pagenum++;
        cout << pagenum << ": " << page->URL << "\n";
    }
    cout << "\nPlease select an option: \n1. Select website \n2.New Search \n3.Exit\n";
    int userChoice = -1;
    cin >> userChoice;
    while (userChoice < 1 || userChoice > 3)
    {
        cout << "Invalid input, try again: ";
        cin >> userChoice;
    }

    if (userChoice == 1)
    {
        int webSelection = -1;
        cout << "Which website would you like to visit: ";
        cin >> webSelection;
        while (webSelection > (int)searchResults.size() || webSelection <= 0)
        {
            cout << "Invalid Input, try again: ";
            cin >> webSelection;
        }
        searchResults[webSelection - 1]->clicks++;
        cout << "Visited: " << searchResults[webSelection - 1]->URL << "\n";
        interactiveDisplay(searchResults);
    }
    else if (userChoice == 2)
    {
        searchDisplay();
    }
    else
    {
        ofstream imp_click("impressions.csv");
        if (!imp_click.is_open())
        {
            cout << "Error: Unable to open imp_click file.\n";
        }

        for (auto it : webPages)
        {
            imp_click << it->URL << "," << it->impressions << "," << it->clicks << endl;
        }

        // printAll();
        exit(1);
    }
}

mainMenu::~mainMenu()
{
}