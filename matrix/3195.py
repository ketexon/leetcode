# https://leetcode.com/problems/minimum-area-rectangle-covering-all-ones/
from typing import List

class Solution:
    def minimumArea(self, grid: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])
        
        min_i = m
        max_i = 0
        min_j = n
        max_j = 0

        for i, row in enumerate(grid):
            should_break = False
            for j, v in enumerate(row):
                if v != 1: continue

                min_j = min(min_j, j)
                max_j = max(max_j, j)
                min_i = i
                max_i = max(max_i, i)
                should_break = True
                break
            if should_break: break
        
        for i in range(m-1, max_i, -1):
            should_break = False
            for j, v in enumerate(grid[i]):
                if v != 1: continue
                min_j = min(min_j, j)
                max_j = max(max_j, j)
                max_i = i
                should_break = True
                break
            if should_break: break
        
        for j in range(0, min_j):
            should_break = False
            for i in range(m):
                v = grid[i][j]
                if v == 0: continue
                min_j = j
                should_break = True
                break
            if should_break: break
        
        for j in range(n-1, max_j, -1):
            should_break = False
            for i in range(m):
                v = grid[i][j]
                if v == 0: continue
                max_j = j
                should_break = True
                break
            if should_break: break
        
        return (max_i - min_i + 1) * (max_j - min_j + 1)

import unittest

class Test3195(unittest.TestCase):
    cases = [
        ([[0,0,0,0,0,0,0,0],
          [0,0,1,1,1,0,0,0],
          [0,0,1,1,1,0,0,0],
          [0,0,1,1,1,0,0,0],
          [0,0,0,0,0,0,0,0]],
         9,
        ),
        ([[1,0,0,0,0,0,0,1],
          [0,0,0,0,0,0,0,0],
          [0,0,0,1,0,0,0,0],
          [0,0,0,0,0,0,0,1],
          [0,0,0,0,0,0,0,0]],
         32,
        ),
        ([[1,1,1],
          [1,1,1],
          [1,1,1]],
         9,
        ),
        ([[1,1,1],
          [1,0,1],
          [1,1,1]],
         9,
        ),
        ([[0,0,1],
          [0,1,1],
          [1,1,1]],
         9,
        ),
        ([[1]],
         1,
        ),
        ([[1,1],
          [1,1]],
         4,
        ),
        ([[1,0],
          [0,1]],
         4,
        ),
        ([[0]],
         0,
        ),
    ]

    def test_cases(self):
        s = Solution()
        for grid, expected in self.cases:
            self.assertEqual(s.minimumArea(grid), expected)

if __name__ == "__main__":
    unittest.main()
