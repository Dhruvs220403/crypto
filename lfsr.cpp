#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> lfsr(const vector<int>& feedback_poly, vector<int> seed, int length) {
    int n = seed.size();
    vector<int> output;

    for (int i = 0; i < length; i++) {
        output.push_back(seed[0]);
        int feedback = 0;
        for (int j = 0; j < n; j++) {
            if (feedback_poly[j]) {
                feedback ^= seed[j];
            }
        }
        for (int j = 0; j < n - 1; j++) {
            seed[j] = seed[j + 1];
        }
        seed[n - 1] = feedback;
    }
    return output;
}

vector<int> deduce_feedback_poly(const vector<int>& sequence, int n) {
    vector<vector<int>> matrix(n, vector<int>(n + 1, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = sequence[i + j];
        }
        matrix[i][n] = sequence[i + n];
    }

    for (int i = 0; i < n; i++) {
        if (matrix[i][i] == 0) {
            for (int j = i + 1; j < n; j++) {
                if (matrix[j][i] == 1) {
                    swap(matrix[i], matrix[j]);
                    break;
                }
            }
        }
        for (int j = i + 1; j < n; j++) {
            if (matrix[j][i] == 1) {
                for (int k = 0; k <= n; k++) {
                    matrix[j][k] ^= matrix[i][k];
                }
            }
        }
    }

    vector<int> feedback_poly(n, 0);
    for (int i = n - 1; i >= 0; i--) {
        feedback_poly[i] = matrix[i][n];
        for (int j = i + 1; j < n; j++) {
            feedback_poly[i] ^= (matrix[i][j] * feedback_poly[j]);
        }
    }

    return feedback_poly;
}

int main() {
    vector<int> feedback_poly = {1, 0, 1, 1}; // x^3 + x + 1
    vector<int> seed = {1, 0, 0, 1};
    int n = seed.size();
    int sequence_length = 2 * n;

    vector<int> sequence = lfsr(feedback_poly, seed, sequence_length);

    cout << "Generated Sequence: ";
    for (int bit : sequence) {
        cout << bit << " ";
    }
    cout << endl;

    vector<int> deduced_poly = deduce_feedback_poly(sequence, n);

    cout << "Deduced Feedback Polynomial: ";
    for (int coeff : deduced_poly) {
        cout << coeff << " ";
    }
    cout << endl;

    return 0;
}
