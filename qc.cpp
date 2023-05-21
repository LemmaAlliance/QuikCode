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
    vector<vector<string>> foundKeywords;
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
        cursor = end;

        while(stateEnd == false)
        {
            cursor++;
            currentChar = contents[cursor-1];
            if(currentChar == ";")
            {
                statement += currentChar;
                end = cursor;
                stateEnd = true;
                statements.insert(statements.begin(), statement);
            }else
            {
                statement += currentChar;
            }
        }
    }
    int substateCursor = 0;
    char current;
    for(int i=0; i<=(statements.size()-1);)
    {
        //Repeates every statement
        substateCursor = stoi(foundKeywords[i][2]);
        while(substateCursor < statements[i].length()-1)
        {
            current = statements[i][substateCursor];
            cout << "Current char: " << current << " @ char " << substateCursor << endl;
            //Check if a statement is being opened
            if(current == '(')
            {
                cout << "Statment opened @: " << substateCursor << endl;
            }else if(current == ')')
            {
                cout << "Statement closed @: " << substateCursor << endl;
            }else
            {
                cout << "Nothing of intrest @: " << substateCursor << endl;
            }
            substateCursor++;
        }
        cout << "Cursor is at: " << substateCursor << endl;
        i++;
    }

    for (int i = 0; i < statements.size(); i++)
    {
        cout << "Statement " << i << " in statements is: " << statements[i] << endl;
        cout << "Keyword " << i << " in foundkeywords is: " << foundKeywords[i][0] << endl;
    }
    
    return 0;
}