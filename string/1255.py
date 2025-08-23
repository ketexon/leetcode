# https://leetcode.com/problems/maximum-score-words-formed-by-letters/
from typing import List

class Solution:
    def maxScoreWords(self, words: List[str], letters: List[str], scores: List[int]) -> int:
        letter_counts = defaultdict(int)
        for letter in letters:
            letter_counts[letter] += 1

        print(letter_counts)

        word_scores = []
        for word in words:
            score = 0
            for ch in word:
                score += scores[ord(ch) - ord('a')]
            word_scores.append(score)
        
        def impl(words, word_scores, word_idx, letter_counts):
            if word_idx >= len(words):
                return 0


            score_without = impl(words, word_scores, word_idx + 1, letter_counts)
            word = words[word_idx]
            can_use = True
            for ch in word:
                letter_counts[ch] -= 1
                if letter_counts[ch] < 0:
                    can_use = False
            score_with = 0
            if can_use:
                score_with = word_scores[word_idx]
                score_with += impl(words, word_scores, word_idx + 1, letter_counts)
            
            for ch in word:
                letter_counts[ch] += 1
            
            return max(score_with, score_without)
                
        return impl(words, word_scores, 0, letter_counts)
