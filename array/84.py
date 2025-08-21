# https://leetcode.com/problems/largest-rectangle-in-histogram/
from typing import List

class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        # each elem represents
        # the last idx smaller than
        # the current
        stack = [-1]
        max_area = 0
        for i,h in enumerate(heights):
            # keep stack monotonic
            while stack[-1] >= 0 and heights[stack[-1]] >= h:
                idx = stack.pop()
                prev = stack[-1]
                area = (i - prev - 1) * heights[idx]
                max_area = max(max_area, area)
            stack.append(i)
        
        # now each element in the stack represents rectangles
        while stack[-1] >= 0:
            idx = stack.pop()
            prev = stack[-1]
            area = (len(heights) - prev - 1) * heights[idx]
            max_area = max(max_area, area)
        return max_area
        
import unittest

class Test84(unittest.TestCase):
    cases = [
        ([2,1,5,6,2,3], 10),
        ([2,4], 4),
        ([1,1], 2),
        ([4,2,0,3,2,5], 6),
    ]

    def test_cases(self):
        s = Solution()
        for heights, expected in self.cases:
            self.assertEqual(s.largestRectangleArea(heights), expected)

if __name__ == "__main__":
    unittest.main()
