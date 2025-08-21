# https://leetcode.com/problems/course-schedule/
from typing import List

class Solution:
    def canFinish(self, n: int, prerequisites: List[List[int]]) -> bool:
        adj_lists = [[] for _ in range(n)]
        incoming_counts = [0 for _ in range(n)]
        for [a,b] in prerequisites:
            if a == b:
                return False
            adj_lists[b].append(a)
            incoming_counts[a] += 1
        
        no_incoming = [i for i,c in enumerate(incoming_counts) if c == 0]
        num_visited = 0
        while len(no_incoming) > 0:
            new_no_incoming = []
            for course in no_incoming:
                for adj in adj_lists[course]:
                    incoming_counts[adj] -= 1
                    if incoming_counts[adj] == 0:
                        new_no_incoming.append(adj)
                num_visited += 1
            no_incoming = new_no_incoming
        
        return num_visited == n
        
import unittest
class Test207(unittest.TestCase):
    cases = [
        (2, [[1,0]], True),
        (2, [[1,0],[0,1]], False),
        (3, [[1,0],[2,1],[0,2]], False),
        (3, [[1,0],[2,1]], True),
        (5, [[1,4],[2,4],[3,1],[3,2]], True),
    ]

    def test_cases(self):
        s = Solution()
        for n, prerequisites, expected in self.cases:
            self.assertEqual(s.canFinish(n, prerequisites), expected)

if __name__ == "__main__":
    unittest.main()
