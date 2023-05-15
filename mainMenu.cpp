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
    webGraph setup;
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

    // 1 word case
    if (searchWords.size() == 1)
    {
        for (int web = 0; web < setup.webPages.size(); web++)
        {
            for (int i = 0; i < setup.webPages[web]->keyWords.size(); i++)
            {
                if (setup.webPages[web]->keyWords[i] == searchWords[0])
                {
                    relevantWebPages.push_back(setup.webPages[web]);
                }
            }
        }
        interactiveDisplay(relevantWebPages);
        relevantWebPages = {};
        setup.clearVisited();
    }
    // OR case
    else if (searchWords[1] == "OR"||searchWords.size()==2)
    {
        if(searchWords.size()==2)
        {
            searchWords.insert(searchWords.begin()+1, "OR");
        }
        for (int web = 0; web < setup.webPages.size(); web++)
        {
            for (int i = 0; i < setup.webPages[web]->keyWords.size(); i++)
            {
                if ((setup.webPages[web]->keyWords[i] == searchWords[0] || setup.webPages[web]->keyWords[i] == searchWords[2]) && setup.visited[setup.webPages[web]] == false)
                {

                    relevantWebPages.push_back(setup.webPages[web]);
                    setup.visited[setup.webPages[web]] = true;
                }
            }
        }

        interactiveDisplay(relevantWebPages);
        relevantWebPages = {};
        setup.clearVisited();
    }
    else if (searchWords[1] == "AND")
    {
        keys[searchWords[0]] = false;
        keys[searchWords[2]] = false;
        for (int web = 0; web < setup.webPages.size(); web++)
        {
            for (int i = 0; i < setup.webPages[web]->keyWords.size(); i++)
            {
                if (setup.webPages[web]->keyWords[i] == searchWords[0])
                {
                    keys[searchWords[0]] = true;
                }
                if (setup.webPages[web]->keyWords[i] == searchWords[2])
                {
                    keys[searchWords[2]] = true;
                }
                if (keys[searchWords[0]] == true && keys[searchWords[2]] == true && setup.visited[setup.webPages[web]] == false)
                {
                    relevantWebPages.push_back(setup.webPages[web]);
                    setup.visited[setup.webPages[web]] = true;

                    keys[searchWords[0]] = false;
                    keys[searchWords[2]] = false;
                }
            }
        }
        keys[searchWords[0]] = false;
        keys[searchWords[2]] = false;

        interactiveDisplay(relevantWebPages);
        relevantWebPages = {};
        setup.clearVisited();
    }
}

void mainMenu::interactiveDisplay(vector<webPage *> searchResults)
{
    for(auto page : searchResults)
    {
        page->impressions++;
    }
    if(!searchResults.size()==0)
    cout << "Here are the results:\n";
    else
    cout<<"No Results\n";

    int pagenum = 0;
    for (auto page : searchResults)
    {
        pagenum++;
        cout << pagenum << ": " << page->URL << "\n";
    }
    cout << "\nPlease select an option: \n1. Select website \n2.New Search \n3.Exit\n";
    int userChoice = -1;
    cin >> userChoice;

    if(userChoice==1)
    {
        int webSelection=-1;
        cout<<"Which website would you like to visit: ";
        cin>>webSelection;
        while(webSelection>searchResults.size()||webSelection<=0)
        {
            cout<<"Invalid Input, try again: "
            cin>>webSelection;
        }
        searchResults[webSelection]->clicks++;
        
        
    }
    else if(userChoice==2)
    {
        searchDisplay();
    }
    else
    {
        //store impressions and clicks
    exit(1);
    }
    
    
}

mainMenu::~mainMenu()
{
}