# https://leetcode.com/problems/word-ladder/
from typing import List
import string
import collections

class Solution:
    '''
    Intution: we are trying to find the shortest path betwee
    begin and end, so we can use a shortest path algorithm for graphs.
    Edges in the graph correspond to words that differ by a letter
    '''
    def ladderLength(self, begin: str, end: str, words: List[str]) -> int:
        word_set = set()
        for word in words:
            word_set.add(word)

        letters = string.ascii_lowercase
        queue = collections.deque([begin])
        visited = { begin }
        depth = 1
        while len(queue) > 0:
            depth += 1
            for _ in range(len(queue)):
                word = queue.popleft()
                for i, ch in enumerate(word):
                    for subs_ch in letters:
                        subs_word = word[:i] + subs_ch + word[i+1:]
                        if subs_word not in word_set: continue
                        if subs_word in visited: continue
                        if subs_word == end:
                            return depth
                        visited.add(subs_word)
                        queue.append(subs_word)
            
        return 0
                
import unittest

class Test127(unittest.TestCase):
    cases = [
        ("hit", "cog", ["hot","dot","dog","lot","log","cog"], 5),
        ("hit", "cog", ["hot","dot","dog","lot","log"], 0),
        ("a", "c", ["a","b","c"], 2),
        ("red", "tax", ["ted","tex","red","tax","tad","den","rex","pee"], 4),
    ]

    def test_cases(self):
        s = Solution()
        for begin, end, words, expected in self.cases:
            self.assertEqual(s.ladderLength(begin, end, words), expected)

if __name__ == "__main__":
    unittest.main()

