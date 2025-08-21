# https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
from collections import defaultdict
from typing import List

class Solution:
    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        # treat the matrix as a graph
        # where each edge represents the greater than relation
        # note that this is a DAG since > is antisymmetric
        # every path must start with a local minimum and therefore
        # have no incoming edges, so we can do a topo sort

        m = len(matrix)
        n = len(matrix[0])
        adj_lists = [[] for _ in range(m * n)]
        incoming_counts = [0 for _ in range(m * n)]
        for i in range(m):
            for j in range(n):
                for di,dj in [(-1,0),(1,0),(0,-1),(0,1)]:
                    ni,nj = i+di,j+dj
                    if 0 <= ni < m and 0 <= nj < n and matrix[ni][nj] > matrix[i][j]:
                        adj_lists[i*n + j].append(ni*n + nj)
                        incoming_counts[ni*n + nj] += 1
        
        no_incoming = [i for i,c in enumerate(incoming_counts) if c == 0]
        length = 0
        while len(no_incoming) > 0:
            new_no_incoming = []
            for course in no_incoming:
                for adj in adj_lists[course]:
                    incoming_counts[adj] -= 1
                    if incoming_counts[adj] == 0:
                        new_no_incoming.append(adj)
            no_incoming = new_no_incoming
            length += 1
        
        return length

import unittest
class Test329(unittest.TestCase):
    cases = [
        (
            [
                [9,9,4],
                [6,6,8],
                [2,1,1],
            ],
            4,
        ),
        (
            [
                [3,4,5],
                [3,2,6],
                [2,2,1],
            ],
            4,
        ),
        (
            [
                [1],
            ],
            1,
        ),
    ]

    def test_cases(self):
        s = Solution()
        for matrix, expected in self.cases:
            result =  s.longestIncreasingPath(matrix)
            self.assertEqual(result, expected)

if __name__ == "__main__":
    unittest.main()
        
