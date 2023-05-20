#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
using namespace std;


vector<string> decoder(string contents, list<string> keywords, int currentPlace)
{
    char currentLetter;
    string currentKeyword;
    string targetKeyword;

    int a=0;
    for(int i=currentPlace; i<(contents.length()); i++)
    {
        currentLetter = contents[i];

        if(a != 0)
        {
            if(currentLetter == targetKeyword[currentKeyword.length()])
            {
                currentKeyword += currentLetter;
                if(currentKeyword.length()>=targetKeyword.length())
                {
                    return {targetKeyword ,to_string(currentKeyword.length()+currentPlace)};
                }
            }else
            {
                return {"Could not find keyword on first attempt"};
            }
        }
        
        for(string keyword : keywords)
        {
            if(a == 0)
            {
                if(currentLetter == keyword[currentKeyword.length()])
                {
                    currentKeyword += currentLetter;
                    targetKeyword = keyword;
                    a++;
                }
            }
        }
        
    }
    return {};
};

int main()
{
    string path;
    list<string> keywords = {"print", "if"};
    vector<std::vector<string>> foundKeywords;
    cout << "What is the full path of your code: ";
    cin >> path;

    ifstream file(path);
    stringstream buffer;
    buffer << file.rdbuf();
    string contents = buffer.str();

    cout << "File contents:\n" << contents << endl << endl;

    foundKeywords.insert(foundKeywords.begin(), decoder(contents, keywords, 0));

    cout << "First keyword found: " << foundKeywords[0][0] << endl;
    cout << "Second keyword found: " << decoder(contents, keywords, 5).front() << endl;
    
    return 0;
}