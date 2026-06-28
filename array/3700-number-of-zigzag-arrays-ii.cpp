// https://leetcode.com/problems/number-of-zigzag-arrays-ii/

#include <vector>

using namespace std;

constexpr int mod = 1000000007;

struct SquareMatrix {
    int n;
    vector<int> data;

    SquareMatrix(int n) : n(n), data(n * n, 0) {}
    SquareMatrix(const SquareMatrix& other) : n(other.n), data(other.data) {}

    constexpr int& at(int i, int j) {
        return data[i * n + j];
    }

    static SquareMatrix mult(SquareMatrix& l, SquareMatrix& r) {
        int n = l.n;
        SquareMatrix out(n);
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < n; ++k) {
                for (int j = 0; j < n; ++j) {
                    out.at(i, j) = (
                        out.at(i, j) 
                        + (static_cast<long long>(l.at(i, k)) * r.at(k, j)) % mod
                    ) % mod;
                }
            }
        }
        return out;
    }

    static vector<int> apply(SquareMatrix& matrix, vector<int>& data) {
        int n = matrix.n;
        vector<int> out(n, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                out[i] = (out[i] + matrix.at(i, j) * data[j]) % mod;
            }
        }
        return out;
    }

    static SquareMatrix pow(SquareMatrix& matrix, int power) {
        if (power == 1) {
            return matrix;
        }
        SquareMatrix out = pow(matrix, power/2);
        out = mult(out, out);
        if (power % 2 == 1) {
            out = mult(matrix, out);
        }
        return out;
    }
};


class Solution {
public:
    // to simplify: we will consider all zigZags starting up and multiply by 2
    int zigZagArrays(int n, int l, int r) {
        n -= 1; // transition count = length - 1
        int m = (r - l) + 1;

        SquareMatrix up(m);
        SquareMatrix down(m);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == j) continue;
                if (i < j) { up.at(i, j) = 1; }
                else { down.at(i, j) = 1; }
            }
        }
        SquareMatrix combined = SquareMatrix::mult(down, up);
        SquareMatrix result = SquareMatrix::pow(combined, n / 2);
        if (n % 2 == 1) {
            result = SquareMatrix::mult(up, result);
        }
        vector<int> v(m, 1);
        v = SquareMatrix::apply(result, v);

        int sum = 0;
        for (int x : v) {
            sum = (sum + x) % mod;
        }
        return (sum * 2) % mod;
    }
};

#include "../test.hpp"

KET_TEST_MAIN(
    &Solution::zigZagArrays, 
    (vector<tuple<tuple<vector<int>, int>, int>> {
        { { 3, 4, 5 }, 2 },
        { { 3, 1, 3 }, 10 },
        { { 8, 34, 67 }, 2633967 },
        { { 8, 4, 33 }, 417511445 },
        { { 9, 38, 86 }, 138519916 },
    })
);