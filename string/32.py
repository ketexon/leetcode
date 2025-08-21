class Solution:
    def longestValidParentheses(self, s: str) -> int:
        # top of stack is the last unmatched open paren
        stack = [-1]
        max_len = 0
        for i, ch in enumerate(s):
            if ch == '(':
                stack.append(i)
            else:
                stack.pop()
                if len(stack) == 0:
                    stack.append(i)
                else:
                    max_len = max(max_len, i - stack[-1])
        return max_len

import unittest

class Test32(unittest.TestCase):
    cases = [
        ("(()", 2),
        (")()())", 4),
        ("", 0),
        ("()(()", 2),
        ("()(())", 6),
        (")()())()()(", 4),
    ]

    def test_cases(self):
        s = Solution()
        for string, expected in self.cases:
            result = s.longestValidParentheses(string)
            self.assertEqual(result, expected)

if __name__ == "__main__":
    unittest.main()
