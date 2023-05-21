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
                    return {targetKeyword , to_string(currentPlace),to_string(currentKeyword.length()+currentPlace)};
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
    vector<string> statements;
    cout << "What is the full path of your code: ";
    cin >> path;

    ifstream file(path);
    stringstream buffer;
    buffer << file.rdbuf();
    string contents = buffer.str();

    cout << "File contents:\n" << contents << endl << "length: " << contents.length() << endl;

    int end = 0;
    int cursor = 0;//This cursor is relative
    string currentChar;
    bool stateEnd = false;
    string statement;
    while (end <= (contents.length() - 1))
    {
        foundKeywords.insert(foundKeywords.begin(), decoder(contents, keywords, end));
        end = stoi(foundKeywords[0][2]);
        statement = foundKeywords[0][0];
        cout << "keyword: " << foundKeywords[0][0] << " length: " << foundKeywords.size() << endl;
        cout << "end: " << end << endl;
        stateEnd = false;
        cursor += end;

        while(stateEnd == false)
        {
            cursor++;
            currentChar = contents[cursor];
            if(currentChar == ";")
            {
                stateEnd = true;
                statements.insert(statements.begin(), statement);
            }else
            {
                statement += currentChar;
            }
        }
    }

    for (int i = 0; i < statements.size(); i++)
    {
        cout << "Statement " << i << " in statements is: " << statements[i] << endl;
    }
    
    return 0;
}