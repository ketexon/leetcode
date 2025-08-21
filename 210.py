# https://leetcode.com/problems/course-schedule-ii/
from typing import List

class Solution:
    def findOrder(self, n: int, prerequisites: List[List[int]]) -> List[int]:
        adj_lists = [[] for _ in range(n)]
        incoming_counts = [0 for _ in range(n)]
        for [a,b] in prerequisites:
            adj_lists[b].append(a)
            incoming_counts[a] += 1
        
        no_incoming = [i for i,c in enumerate(incoming_counts) if c == 0]
        out = []
        while len(no_incoming) > 0:
            new_no_incoming = []
            for course in no_incoming:
                for adj in adj_lists[course]:
                    incoming_counts[adj] -= 1
                    if incoming_counts[adj] == 0:
                        new_no_incoming.append(adj)
                out.append(course)
            no_incoming = new_no_incoming
        
        return out if len(out) == n else []
        
import unittest
class Test210(unittest.TestCase):
    cases = [
        (2, [[1,0]], [0,1]),
        (2, [[1,0],[0,1]], []),
        (3, [[1,0],[2,1],[0,2]], []),
        (3, [[1,0],[2,1]], [0,1,2]),
        (5, [[1,4],[2,4],[3,1],[3,2]], [4,0,1,2,3]),
    ]

    def test_cases(self):
        s = Solution()
        for n, prerequisites, expected in self.cases:
            courses = s.findOrder(n, prerequisites)
            courses.sort()
            expected.sort()
            self.assertEqual(courses, expected)

if __name__ == "__main__":
    unittest.main()
