# https://leetcode.com/problems/distinct-subsequences/description/

class Solution:
    # note:
    # numDistinct(s, t) =
    #   | s[-1] == t[-1] -> numDistinct(s[:-1], t) +  umDistinct(s[:-1], t[:-1])
    #   | otherwise numDistinct(s[:-1], t)
    def numDistinct(self, s: str, t: str) -> int:
        m = len(s)
        n = len(t)
        M = [[0 for _ in range(n)] for _ in range(m)]
        
        # for the first row, the number of ways to
        # output the first letter is the number 
        # of that letter before or at the current
        # index
        acc = 0
        for i in range(m):
            if s[i] == t[0]:
                acc += 1
            M[i][0] = acc
        
        for i in range(1,m):
            for j in range(1,n):
                M[i][j] = M[i-1][j]
                if s[i] == t[j] and j > 0:
                    M[i][j] += M[i-1][j-1]

        return M[-1][-1]

import unittest

class Test115(unittest.TestCase):
    cases = [
        ("rabbbit", "rabbit", 3),
        ("babgbag", "bag", 5),
        ("a", "a", 1),
        ("a", "b", 0),
        ("aaa", "aa", 3),
    ]

    def test_cases(self):
        s = Solution()
        for s_str, t_str, expected in self.cases:
            result = s.numDistinct(s_str, t_str)
            self.assertEqual(result, expected)

if __name__ == "__main__":
    unittest.main()
