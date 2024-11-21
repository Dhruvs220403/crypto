#include <bits/stdc++.h>
using namespace std;

string caesar_cipher(const string &text, int shift)
{
    string result;
    for (char c : text)
    {
        if (isalpha(c))
        {
            char base = isupper(c) ? 'A' : 'a';
            result += char((c - base + shift) % 26 + base);
        }
        else
        {
            result += c;
        }
    }
    return result;
}

map<char, int> get_frequency(const string &text)
{
    map<char, int> frequency;
    for (char c : text)
    {
        if (isalpha(c))
        {
            c = tolower(c);
            frequency[c]++;
        }
    }
    return frequency;
}

vector<pair<char, int>> sort_frequency(const map<char, int> &freq_map)
{
    vector<pair<char, int>> freq_vector(freq_map.begin(), freq_map.end());
    sort(freq_vector.begin(), freq_vector.end(), [](const pair<char, int> &a, const pair<char, int> &b)
         { return a.second > b.second; });
    return freq_vector;
}

int main()
{
    string text;

    cout << "Enter the ciphertext: ";
    getline(cin, text);

    cout << "Brute force analysis results:" << endl;
    for (int shift = 1; shift < 26; ++shift)
    {
        string decrypted_text = caesar_cipher(text, -shift);
        cout << "Shift " << shift << ": " << decrypted_text << endl;
    }

    cout << "Enter the ciphertext: ";
    getline(cin, text);

    auto frequency = get_frequency(text);
    auto sorted_frequency = sort_frequency(frequency);

    cout << "Letter frequency in ciphertext:" << endl;
    for (const auto &pair : sorted_frequency)
    {
        cout << pair.first << ": " << pair.second << endl;
    }

    cout << "Analyzing possible shifts based on frequency:" << endl;
    for (int shift = 0; shift < 26; ++shift)
    {
        string decrypted_text = caesar_cipher(text, -shift);
        auto freq = get_frequency(decrypted_text);
        auto sorted_decrypted_frequency = sort_frequency(freq);

        cout << "Shift " << shift << ":" << endl;
        for (const auto &pair : sorted_decrypted_frequency)
        {
            cout << pair.first << ": " << pair.second << endl;
        }
        cout << endl;
    }
}