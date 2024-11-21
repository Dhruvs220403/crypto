#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> generateMatrix(const string& key) {
    unordered_set<char> seen;
    queue<char> characters;
    for (char ch : key) {
        char lowerCh = tolower(ch);
        if (seen.find(lowerCh) == seen.end()) {
            seen.insert(lowerCh);
            characters.push(lowerCh);
        }
    }
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        if (ch != 'j' && seen.find(ch) == seen.end()) {
            seen.insert(ch);
            characters.push(ch);
        }
    }
    vector<vector<char>> matrix(5, vector<char>(5));
    int index = 0;
    while (!characters.empty()) {
        matrix[index / 5][index % 5] = characters.front();
        characters.pop();
        ++index;
    }
    return matrix;
}

string encryptPlayfair(const string& text, const string& key) {
    auto matrix = generateMatrix(key);
    unordered_map<char, pair<int, int>> positionMap;

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            positionMap[matrix[row][col]] = {row, col};
        }
    }

    string adjustedText = text;
    for (char& ch : adjustedText) {
        ch = tolower(ch);
    }
    if (adjustedText.length() % 2 != 0) {
        adjustedText += 'x';
    }

    string ciphertext;
    for (int i = 0; i < adjustedText.length(); i += 2) {
        char a = adjustedText[i];
        char b = adjustedText[i + 1];
        auto pos1 = positionMap[a];
        auto pos2 = positionMap[b];

        if (pos1.first == pos2.first) {
            ciphertext += matrix[pos1.first][(pos1.second + 1) % 5];
            ciphertext += matrix[pos2.first][(pos2.second + 1) % 5];
        } else if (pos1.second == pos2.second) {
            ciphertext += matrix[(pos1.first + 1) % 5][pos1.second];
            ciphertext += matrix[(pos2.first + 1) % 5][pos2.second];
        } else {
            ciphertext += matrix[pos1.first][pos2.second];
            ciphertext += matrix[pos2.first][pos1.second];
        }
    }

    return ciphertext;
}

string decryptPlayfair(const string& text, const string& key) {
    auto matrix = generateMatrix(key);
    unordered_map<char, pair<int, int>> positionMap;

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            positionMap[matrix[row][col]] = {row, col};
        }
    }

    string plaintext;
    for (int i = 0; i < text.length(); i += 2) {
        char a = text[i];
        char b = text[i + 1];
        auto pos1 = positionMap[a];
        auto pos2 = positionMap[b];

        if (pos1.first == pos2.first) {
            plaintext += matrix[pos1.first][(pos1.second - 1 + 5) % 5];
            plaintext += matrix[pos2.first][(pos2.second - 1 + 5) % 5];
        } else if (pos1.second == pos2.second) {
            plaintext += matrix[(pos1.first - 1 + 5) % 5][pos1.second];
            plaintext += matrix[(pos2.first - 1 + 5) % 5][pos2.second];
        } else {
            plaintext += matrix[pos1.first][pos2.second];
            plaintext += matrix[pos2.first][pos1.second];
        }
    }

    return plaintext;
}

pair<int, int> findPosition(const vector<vector<char>>& matrix, char ch) {
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (matrix[row][col] == ch) {
                return {row, col};
            }
        }
    }
    return {-1, -1};
}

vector<vector<char>> deriveMatrix(const string& plaintext, const string& ciphertext) {
    vector<vector<char>> matrix = generateMatrix("abcdefghiklmnopqrstuvwxyz");
    
    for (int i = 0; i < plaintext.length(); i += 2) {
        char pt1 = plaintext[i];
        char pt2 = plaintext[i + 1];
        char ct1 = ciphertext[i];
        char ct2 = ciphertext[i + 1];

        auto posPt1 = findPosition(matrix, pt1);
        auto posPt2 = findPosition(matrix, pt2);
        auto posCt1 = findPosition(matrix, ct1);
        auto posCt2 = findPosition(matrix, ct2);

        if (posPt1.first == posPt2.first) {
            swap(matrix[posPt1.first][(posPt1.second + 1) % 5], matrix[posCt1.first][(posCt2.second + 1) % 5]);
            swap(matrix[posPt2.first][(posPt2.second + 1) % 5], matrix[posCt2.first][(posCt1.second + 1) % 5]);
        } else if (posPt1.second == posPt2.second) {
            swap(matrix[(posPt1.first + 1) % 5][posPt1.second], matrix[(posCt1.first + 1) % 5][posCt1.second]);
            swap(matrix[(posPt2.first + 1) % 5][posPt2.second], matrix[(posCt2.first + 1) % 5][posCt2.second]);
        } else {
            swap(matrix[posPt1.first][posPt2.second], matrix[posCt1.first][posCt2.second]);
            swap(matrix[posPt2.first][posPt1.second], matrix[posCt2.first][posCt1.second]);
        }
    }
    
    return matrix;
}

int main() {
    string key = "MONARCHY";
    string plaintext = "GETTHEGOLD";
    string encryptedText = encryptPlayfair(plaintext, key);
    cout << "Encrypted Text: " << encryptedText << endl;

    string partialPlaintext = "GETH";
    vector<vector<char>> derivedMatrix = deriveMatrix(partialPlaintext, encryptedText);

    string reconstructedKey;
    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            reconstructedKey += derivedMatrix[row][col];
        }
    }

    cout << "Original Plaintext: " << plaintext << endl;
    cout << "Provided Key: " << key << endl;
    cout << "Derived Key: " << reconstructedKey << endl;

    cout << "Encrypted with Derived Key: " << encryptPlayfair(plaintext, reconstructedKey) << endl;
    cout << "Decrypted with Derived Key: " << decryptPlayfair(encryptedText, reconstructedKey) << endl;

    return 0;
}