# https://leetcode.com/problems/maximal-rectangle/
from typing import List

class Solution:
    # from 84
    def largest_histogram_area(self, hist: List[int]) -> int:
        # each elem represents
        # the last idx smaller than
        # the current
        stack = [-1]
        max_area = 0
        for i,h in enumerate(hist):
            # keep stack monotonic
            while stack[-1] >= 0 and hist[stack[-1]] >= h:
                idx = stack.pop()
                prev = stack[-1]
                area = (i - prev - 1) * hist[idx]
                max_area = max(max_area, area)
            stack.append(i)
        
        # now each element in the stack represents rectangles
        while stack[-1] >= 0:
            idx = stack.pop()
            prev = stack[-1]
            area = (len(hist) - prev - 1) * hist[idx]
            max_area = max(max_area, area)
        return max_area

    def maximalRectangle(self, matrix: List[List[str]]) -> int:
        m = len(matrix)
        n = len(matrix[0])
        hists = [[0 for _ in range(n)] for _ in range(m)]
        for i, row in enumerate(matrix):
            for j, cell in enumerate(row):
                if cell == "0": continue
                hists[i][j] = 1
                if i > 0:
                    hists[i][j] += hists[i-1][j]
        
        return max(
            self.largest_histogram_area(hist)
            for hist
            in hists
        )
            
import unittest

class Test85(unittest.TestCase):
    cases = [
        (
            [
                ["1","0","1","0","0"],
                ["1","0","1","1","1"],
                ["1","1","1","1","1"],
                ["1","0","0","1","0"],
            ],
            6,
        ),
        (
            [
                ["0"]
            ],
            0,
        ),
        (
            [
                ["1"]
            ],
            1,
        ),
        (
            [
                ["0","0"]
            ],
            0,
        ),
        (
            [
                ["1","1"]
            ],
            2,
        ),
        (
            [
                ["0","1"]
            ],
            1,
        ),
    ]

    def test_cases(self):
        s = Solution()
        for matrix, expected in self.cases:
            self.assertEqual(s.maximalRectangle(matrix), expected)

if __name__ == "__main__":
    unittest.main()
