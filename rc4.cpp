#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <random>

using namespace std;
using namespace chrono;

vector<int> KSA(const vector<int>& key, duration<double>& ksa_time) {
    vector<int> S(256);
    auto start_ksa = high_resolution_clock::now();
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }
    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key.size()]) % 256;
        swap(S[i], S[j]);
    }
    auto stop_ksa = high_resolution_clock::now();
    ksa_time = duration_cast<microseconds>(stop_ksa - start_ksa);
    return S;
}

vector<int> PRGA(vector<int>& S, size_t length, duration<double>& prga_time) {
    int i = 0, j = 0;
    vector<int> keystream;
    auto start_prga = high_resolution_clock::now();
    for (size_t k = 0; k < length; k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        keystream.push_back(S[(S[i] + S[j]) % 256]);
    }
    auto stop_prga = high_resolution_clock::now();
    prga_time = duration_cast<microseconds>(stop_prga - start_prga);
    return keystream;
}

vector<int> rc4(const string& key, const string& text, duration<double>& ksa_time, duration<double>& prga_time) {
    vector<int> keyBytes(key.begin(), key.end());
    vector<int> S = KSA(keyBytes, ksa_time);
    vector<int> keystream = PRGA(S, text.size(), prga_time);
    vector<int> ciphertext;
    for (size_t i = 0; i < text.size(); i++) {
        ciphertext.push_back(text[i] ^ keystream[i]);
    }
    return ciphertext;
}

string generate_random_message(size_t length) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 255);
    string message(length, '\0');
    for (size_t i = 0; i < length; i++) {
        message[i] = dist(gen);
    }
    return message;
}

void test_rc4_with_key_and_message_lengths() {
    vector<int> key_lengths = {5, 16, 32};  // 40-bit, 128-bit, 256-bit keys (in bytes)
    vector<size_t> message_lengths = {1024, 10240, 102400, 1048576}; // 1 KB, 10 KB, 100 KB, 1 MB
    const int runs = 5;

    for (int key_len : key_lengths) {
        string key(key_len, 'K');
        for (size_t msg_len : message_lengths) {
            double total_ksa_time = 0, total_prga_time = 0;
            
            for (int run = 0; run < runs; run++) {
                string message = generate_random_message(msg_len);

                duration<double> ksa_time(0), prga_time(0);

                rc4(key, message, ksa_time, prga_time);

                total_ksa_time += ksa_time.count();
                total_prga_time += prga_time.count();
            }

            cout << "Key Length: " << key_len * 8 << " bits, Message Length: " << msg_len / 1024 << " KB, "
                 << "Average KSA Time: " << total_ksa_time / runs * 1000 << " ms, "
                 << "Average PRGA Time: " << total_prga_time / runs * 1000 << " ms" << endl;
        }
    }
}

int main() {
    test_rc4_with_key_and_message_lengths();
    return 0;
}