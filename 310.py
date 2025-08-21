# https://leetcode.com/problems/minimum-height-trees/
from typing import List

class Solution:
    def findMinHeightTrees(self, n: int, edges: List[List[int]]) -> List[int]:
        if len(edges) == 0: return [0]

        # adjacency matrix
        # mat[i][j] <=> i -> j
        adj_lists = [[] for _ in range(n)]
        degrees = [0 for _ in range(n)]
        for [a,b] in edges:
            adj_lists[b].append(a)
            adj_lists[a].append(b)
            degrees[a] += 1
            degrees[b] += 1
        
        leafs = [i for i,c in enumerate(degrees) if c == 1]
        nodes_remaining = n
        while nodes_remaining > 2:
            new_leafs = []
            for node in leafs:
                for adj in adj_lists[node]:
                    degrees[adj] -= 1
                    if degrees[adj] == 1:
                        new_leafs.append(adj)
            nodes_remaining -= len(leafs)
            leafs = new_leafs
        
        return leafs

import unittest
class Test310(unittest.TestCase):
    cases = [
        (4, [[1,0],[1,2],[1,3]], [1]),
        (6, [[0,3],[1,3],[2,3],[4,3],[5,4]], [3,4]),
        (1, [], [0]),
        (2, [[0,1]], [0,1]),
    ]

    def test(self):
        s = Solution()
        for n, edges, expected in self.cases:
            result = s.findMinHeightTrees(n, edges)
            result.sort()
            expected.sort()
            self.assertEqual(result, expected)

if __name__ == "__main__":
    unittest.main()
