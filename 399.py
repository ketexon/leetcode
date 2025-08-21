# https://leetcode.com/problems/evaluate-division/
from collections import defaultdict
from typing import List

class Solution:
    '''
    Build a graph where there is an edge with weight v between a and b if a/b = v
    Thus, you can calculate a/c = (a/b) * (b/c) by multiplying the weights along the path from a to c
    Every edge has an inverse, and when we calculate a query, we cache it onto
    the graph (just in case)
    '''
    def calcEquation(self, equations: List[List[str]], values: List[float], queries: List[List[str]]) -> List[float]:
        variables = set()
        adj_lists = defaultdict(list)
        edge_values = dict()
        for [a,b], v in zip(equations, values):
            adj_lists[a].append(b)
            adj_lists[b].append(a)
            edge_values[a,b] = v
            edge_values[b,a] = 1/v
            variables.add(a)
            variables.add(b)
        
        out = []
        for [a,b] in queries:
            v = None
            if a not in variables or b not in variables:
                v = -1
            elif a == b:
                v = 1
            elif (a,b) in edge_values:
                v = edge_values[a,b]
            
            if v is not None:
                out.append(v)
                continue

            def dfs(node, visited = set()):
                nonlocal adj_lists, edge_values, b
                if node == b:
                    return 1
                for adj in adj_lists[node]:
                    if adj in visited:
                        continue
                    visited.add(adj)
                    res = dfs(adj, visited)
                    if res is not None:
                        return res * edge_values[node,adj]
                return None

            v = dfs(a)
            if v is None:
                out.append(-1)
                continue
            
            # cache
            edge_values[a,b] = v
            edge_values[b,a] = 1/v

            adj_lists[a].append(b)
            adj_lists[b].append(a)

            out.append(v)
        return out

import unittest

class Test399(unittest.TestCase):
    cases = [
        (
            [["a","b"],["b","c"]],
            [2.0,3.0],
            [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]],
            [6.0,0.5,-1.0,1.0,-1.0]
        ),
        (
            [["a","b"],["b","c"],["bc","cd"]],
            [1.5,2.5,5.0],
            [["a","c"],["c","b"],["bc","cd"],["cd","bc"]],
            [3.75,0.4,5.0,0.2]
        ),
    ]

    def test_cases(self):
        s = Solution()
        for equations, values, queries, expected in self.cases:
            result = s.calcEquation(equations, values, queries)
            self.assertEqual(result, expected)

if __name__ == "__main__":
    unittest.main()
