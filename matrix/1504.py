# https://leetcode.com/problems/count-submatrices-with-all-ones/
# solution: https://leetcode.com/problems/count-submatrices-with-all-ones/solutions/7107976/human-readable-intuition-with-detailed-examples-monotonic-stack-dp
from typing import List

class Solution:
    """
    Logic:
        We will count the number of rects with bottom right corner
        at i,j.

        First, fix a i, then iterate j.

        Example:
        0 1 0 1
        0 1 1 0
        1 1 1 1
        1 1 1 0
            ^
            j

        Consider the rectangle with the largest height (in this case, 3),
        and extend it leftwards to the largest width.

        Example
        0 1 0 1
        0 x x 0
        1 x x 1
        1 x x 0
        ^   ^
        p   j

        Note that every rectangle ending at i,j is either in this region,
        or an extension of a recangle ending at p.

        # Case 1: rectangles starting after p

        Count the number of rectangles formable in this area ending at the bottom
        right. This involves choosing 1 column and 1 row in this region, so
        there are w * h choices.

        # Case 2: rectangles at or before p
        For every rectangle ending at i,p,
        we can extend it to j

        Example
        0 1 0 1
        0 1 1 0
        x x x 1
        x x x 0
        ^   ^
        p   j

        Thus, the total number of rectangles ending at i,j
        is w * h + the total number of rectangles ending at i,p

    Optimizations:
        We store the heights at the current row
        in an array of length n.
        For each column in a row, we add 1 if the value
        is 1, otherwise we reset the heights.

        To optimize finding p, we use a monotonic stack
        whose top element is the last index
        whose height is smaller than the current height.

    Complexity:
        O(n) to make the histogram
        + O(m) row iteration * (
            O(n) to make num_rects
            + O(n) to update histogram
            + O(n) to update num_rects
            + O(n) to pop elements from stack (inside update for num rects)
        )
        = O(mn)
    """

    def numSubmat(self, matrix: List[List[int]]) -> int:
        m = len(matrix)
        n = len(matrix[0])
        total_num_rects = 0

        # monotonic increasing stack
        # hist[i-1] is last idx of element
        # smaller than hist[i]
        hist = [0] * n
        for i in range(m):
            stack = [-1]
            num_rects = [0] * n
            # update hist
            for j in range(n):
                hist[j] = (hist[j] + 1) * matrix[i][j]

            for j, h in enumerate(hist):
                # keep stack monotonic
                while stack[-1] >= 0 and hist[stack[-1]] >= h:
                    stack.pop()

                # previous rect smaller
                prev_j = stack[-1]
                prev_n_rects = 0 if prev_j < 0 else num_rects[prev_j]
                num_rects[j] = prev_n_rects + h * (j - prev_j)

                total_num_rects += num_rects[j]
                stack.append(j)

        return total_num_rects

import unittest

class Test1504(unittest.TestCase):
    cases = [
        ([[1,0,1],
          [1,1,0],
          [1,1,0]],
         13,
        ),
        ([[0,1,1,0],
          [0,1,1,1],
          [1,1,1,0]],
         24,
        ),
        ([[1,1,1,1,1]],
         15,
        ),
        ([[1,0,1],
          [0,1,0],
          [1,0,1]],
         5,
        ),
    ]

    def test_cases(self):
        s = Solution()
        for matrix, expected in self.cases:
            self.assertEqual(s.numSubmat(matrix), expected)

if __name__ == "__main__":
    unittest.main()
