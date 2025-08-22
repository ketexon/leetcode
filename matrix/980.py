# https://leetcode.com/problems/unique-paths-iii/
from typing import List

class Solution:
    '''
    Backtracking
    Keep track of path length to make sure
    all cells are walked over
    '''
    def uniquePathsIII(self, grid: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])
        # find start idx
        start_idx = None
        total_empties = 0
        for i, row in enumerate(grid):
            for j, col in enumerate(row):
                if col == 1:
                    start_idx = (i,j)
                if col == 1 or col == 0:
                    total_empties += 1
        assert(start_idx is not None)

        def impl(grid, i, j, visited, cache, empties_left):
            if not (0 <= i < m and 0 <= j < n):
                return 0
            if grid[i][j] == 2:
                if empties_left == 0:
                    return 1
                else:
                    return 0
            elif grid[i][j] == -1:
                return 0
            
            count = 0
            visited.add((i,j))
            for di,dj in ((1,0),(0,1),(-1,0),(0,-1)):
                if (i+di,j+dj) in visited:
                    continue
                count += impl(grid, i + di, j + dj, visited, cache, empties_left - 1)
            visited.remove((i,j))

            cache[i,j] = count
            return count
            

        return impl(grid, start_idx[0], start_idx[1], set(), dict(), total_empties)

import unittest

class Test980(unittest.TestCase):
    cases = [
        ([[1,0,0,0],
          [0,0,0,0],
          [0,0,2,-1]],
         2,
        ),
        ([[1,0,0,0],
          [0,0,0,0],
          [0,0,0,2]],
         4,
        ),
        ([[0,1],
          [2,0]],
         0,
        ),
    ]

    def test_cases(self):
        s = Solution()
        for grid, expected in self.cases:
            self.assertEqual(s.uniquePathsIII(grid), expected)

if __name__ == "__main__":
    unittest.main()
