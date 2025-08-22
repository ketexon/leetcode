# https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
from typing import List

class Solution:
    '''
    M[i][j] is the best time to buy and sell i stocks in prices[:j]
    M[i][j] = max(
        M[i][j],  # don't trade on this day
        prices[j] - prices[k] # do one trasaction including the current value
        + M[i-1][k-1] # and one before
        for k in range(0,j)
    )
    From the DP for this, we can transform it to below
    '''
    def maxProfit(self, prices: List[int]) -> int:
        m = len(prices)
        
        # best time to buy and sell one stocks at current index
        max_1 = 0
        # best time to buy and sell two stocks at current index
        max_2 = 0
        # smallest loss for one buy
        loss_1 = prices[0]
        # smallest loss for two buys
        loss_2 = prices[0]
        
        for i in range(1,m):
            price = prices[i]
            max_1 = max(max_1, price - loss_1)
            max_2 = max(max_2, price - loss_2)
            loss_1 = min(loss_1, price)
            loss_2 = min(loss_2, price - max_1)

        return max_2

import unittest

class Test123(unittest.TestCase):
    cases = [
        ([3,3,5,0,0,3,1,4], 6),
        ([1,2,3,4,5], 4),
        ([7,6,4,3,1], 0),
        ([1], 0),
        ([1,2], 1),
        ([2,1], 0),
        ([1,2,3], 2),
        ([3,2,1], 0),
        ([1,2,3,4,5,1,2,3,4,5], 8),
    ]

    def test_cases(self):
        s = Solution()
        for prices, expected in self.cases:
            result = s.maxProfit(prices)
            self.assertEqual(result, expected)

if __name__ == "__main__":
    unittest.main()
