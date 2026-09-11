#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int charIndex(char c)
{
    if (c >= 'a' && c <= 'z') 
    {
        return c - 'a';
    }
    if (c >= 'A' && c <= 'Z')
    {
        return c - 'A';
    }
    return 26; 
}

int main()
{
    int l;
    cin >> l; cin.ignore();
    int h;
    cin >> h; cin.ignore();
    string t;
    getline(cin, t);

    vector<string> font(h);
    for (int i = 0; i < h; i++)
    {
        getline(cin, font[i]);
    }

    for (int i = 0; i < h; i++)
    {
        string line = "";
        for (char c : t) 
        {
            int idx = charIndex(c);
            line += font[i].substr(idx * l, l);
        }
        cout << line << endl;
    }
}