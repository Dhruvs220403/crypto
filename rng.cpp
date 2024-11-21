#include <bits/stdc++.h>

using namespace std;

void generateKey(const string &device, vector<unsigned char> &key, size_t keySize) {
    ifstream dev(device, ios::in | ios::binary);
    if (!dev) {
        cerr << "Error: Cannot open device " << device << endl;
        exit(1);
    }

    key.resize(keySize);
    dev.read(reinterpret_cast<char *>(key.data()), keySize);
    dev.close();
}

void printKey(const vector<unsigned char> &key) {
    for (const auto &byte : key) {
        cout << hex << setw(2) << setfill('0') << static_cast<int>(byte);
    }
    cout << endl;
}

vector<unsigned char> generateRandomKey(size_t keySize) {
    vector<unsigned char> key(keySize);
    random_device rd;
    for (size_t i = 0; i < keySize; ++i) {
        key[i] = rd() % 256; 
    }
    return key;
}

vector<unsigned char> applyOTP(const vector<unsigned char>& message, const vector<unsigned char>& key) {
    vector<unsigned char> result(message.size());
    for (size_t i = 0; i < message.size(); ++i) {
        result[i] = message[i] ^ key[i];
    }
    return result;
}

void printBinary(const vector<unsigned char>& data) {
    for (unsigned char byte : data) {
        cout << bitset<8>(byte) << " ";
    }
    cout << endl;
}

int main() {
    size_t keySize = 16;  // 128-bit key (16 bytes)
    vector<unsigned char> randomKey, urandomKey;

    cout << "Generating 128-bit cryptographic key from /dev/random..." << endl;
    generateKey("/dev/random", randomKey, keySize);
    cout << "Key from /dev/random: ";
    printKey(randomKey);

    cout << "Generating 128-bit cryptographic key from /dev/urandom..." << endl;
    generateKey("/dev/urandom", urandomKey, keySize);
    cout << "Key from /dev/urandom: ";
    printKey(urandomKey);

    string message = "This is a secret message!!";
    vector<unsigned char> plaintext(message.begin(), message.end());

    vector<unsigned char> key = generateRandomKey(plaintext.size());

    cout << "Original message in binary: ";
    printBinary(plaintext);

    cout << "Random key in binary: ";
    printBinary(key);

    vector<unsigned char> ciphertext = applyOTP(plaintext, key);

    cout << "Ciphertext in binary: ";
    printBinary(ciphertext);

    vector<unsigned char> decryptedMessage = applyOTP(ciphertext, key);

    cout << "Decrypted message in binary: ";
    printBinary(decryptedMessage);

    string decryptedString(decryptedMessage.begin(), decryptedMessage.end());
    cout << "Decrypted message: " << decryptedString << endl;

    return 0;
}