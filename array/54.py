# https://leetcode.com/problems/spiral-matrix/

from typing import List

class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        m = len(matrix)
        n = len(matrix[0])

        di = 0
        dj = 1

        i = 0
        j = 0
        out = []
        min_row = 0
        min_col = 0
        max_row = m
        max_col = n
        for _ in range(m * n):
            out.append(matrix[i][j])

            if not (min_row <= i + di < max_row \
                and min_col <= j + dj < max_col):
                di,dj = dj, -di
                min_row += max(di, 0)
                max_row += min(di, 0)
                min_col += max(dj, 0)
                max_col += min(dj, 0)
            
            i += di
            j += dj
        return out

import unittest

class Test54(unittest.TestCase):
    cases = [
        (
            [
                [1,2,3],
                [4,5,6],
                [7,8,9],
            ],
            [1,2,3,6,9,8,7,4,5],
        ),
        (
            [
                [1,2,3,4],
                [5,6,7,8],
                [9,10,11,12],
            ],
            [1,2,3,4,8,12,11,10,9,5,6,7],
        ),
    ]

    def test_cases(self):
        s = Solution()
        for matrix, expected in self.cases:
            self.assertEqual(s.spiralOrder(matrix), expected)

if __name__ == "__main__":
    unittest.main()
