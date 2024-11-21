#include<bits/stdc++.h>
using namespace std;

string stringToBinary(const string& text) {
    string binary;
    for (char c : text) {
        binary += bitset<8>(static_cast<unsigned char>(c)).to_string();
    }
    return binary;
}

string generateRandomBinaryKey(int length) {
    string key;
    for (int i = 0; i < length; ++i) {
        key += (rand() % 2) ? '1' : '0';
    }
    return key;
}

string xorBinaryStrings(const string& a, const string& b) {
    string result;
    for (int i = 0; i < a.size(); ++i) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

string binaryToString(const string& binary) {
    string text;
    for (int i = 0; i < binary.size(); i += 8) {
        bitset<8> byte(binary.substr(i, 8));
        text += static_cast<char>(byte.to_ulong());
    }
    return text;
}

int main() {
    string plaintext;
    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    string binaryText = stringToBinary(plaintext);
    int length = binaryText.size();

    srand(static_cast<unsigned>(time(0)));

    string key1 = generateRandomBinaryKey(length);
    string key2 = generateRandomBinaryKey(length);

    string encryptedWithKey1 = xorBinaryStrings(binaryText, key1);
    string encryptedWithKey2 = xorBinaryStrings(encryptedWithKey1, key2);

    cout << "Encrypted text (binary): " << encryptedWithKey2 << endl;

    string encryptedText = binaryToString(encryptedWithKey2);
    cout << "Encrypted text (string): " << encryptedText << endl;

    string knownPlaintext, correspondingCiphertext;

    cout << "Enter known plaintext (binary): ";
    getline(cin, knownPlaintext);
    cout << "Enter corresponding ciphertext (binary): ";
    getline(cin, correspondingCiphertext);

    string intermediate = xorBinaryStrings(correspondingCiphertext, knownPlaintext);

    cout << "Intermediate result (binary): " << intermediate << endl;

    string additionalPlaintext, additionalCiphertext;
    cout << "Enter additional known plaintext (binary): ";
    getline(cin, additionalPlaintext);
    cout << "Enter additional corresponding ciphertext (binary): ";
    getline(cin, additionalCiphertext);

    string secondKey = xorBinaryStrings(additionalCiphertext, intermediate);

    cout << "Second key (binary): " << secondKey << endl;
}