//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 06 - Homework 03
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to preprocess the pattern and create the LPS array
vector<int> computeLPSArray(const string &pattern)
{
    int m = pattern.length();
    vector<int> lps(m, 0);
    int len = 0;
    int i = 1;

    while (i < m)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

// Function to perform KMP pattern matching
vector<int> KMPSearch(const string &text, const string &pattern)
{
    int n = text.length();
    int m = pattern.length();
    vector<int> lps = computeLPSArray(pattern);
    vector<int> result;

    int i = 0; // index for text
    int j = 0; // index for pattern

    while (i < n)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }

        if (j == m)
        {
            result.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i])
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }
    return result;
}

int main()
{
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";

    vector<int> result = KMPSearch(text, pattern);

    cout << "Pattern found at indices: ";
    for (int index : result)
    {
        cout << index << " ";
    }
    cout << endl;

    return 0;
}
