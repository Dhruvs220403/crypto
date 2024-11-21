#include <iostream>
#include <string>

using namespace std;

string caesar_cipher(const string& text, int shift) {
    string result;
    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += char((c - base + shift) % 26 + base);
        } else {
            result += c;
        }
    }
    return result;
}

int main() {
    char action;
    string text;
    int shift;

    while (true) {
        cout << "Would you like to (E)ncrypt or (D)ecrypt? (E/D): ";
        cin >> action;
        if (action != 'E' && action != 'D') {
            cout << "Invalid choice. Please enter 'E' for encryption or 'D' for decryption." << endl;
            continue;
        }
        
        cout << "Enter the text: ";
        cin.ignore();
        getline(cin, text);

        cout << "Enter the shift number: ";
        cin >> shift;

        if (action == 'D') {
            shift = -shift;
        }

        string result = caesar_cipher(text, shift);
        cout << "The result is: " << result << endl;

        cout << "Would you like to perform another operation? (Y/N): ";
        cin >> action;
        if (action != 'Y' && action != 'y') {
            break;
        }
    }

    return 0;
}