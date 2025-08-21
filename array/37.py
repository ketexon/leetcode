# https://leetcode.com/problems/sudoku-solver/
from typing import List

class Solution:
    def solve_recursive(self) -> bool:
        min_cell = None
        min_cell_options = None

        for i in range(9):
            for j in range(9):
                if self.board[i][j] != '.':
                    continue
                options = (
                    self.row_sets[i]
                    & self.col_sets[j]
                    & self.get_square_set(i,j)
                )

                if len(options) == 0:
                    return False

                if min_cell_options is None or len(min_cell_options) > len(options):
                    min_cell = (i,j)
                    min_cell_options = options
        if min_cell_options is None or min_cell is None:
            return True

        i, j = min_cell
        options = list(min_cell_options)
        for option in options:
            self.set_cell(i, j, option)
            if self.solve_recursive():
                return True
            self.unset_cell(i, j)
        return False

    def get_square_set(self, i, j) -> set:
        idx = (i // 3) * 3 + (j // 3)
        return self.square_sets[idx]

    def set_cell(self, i, j, v):
        self.row_sets[i].remove(v)
        self.col_sets[j].remove(v)
        self.get_square_set(i,j).remove(v)
        self.board[i][j] = v

    def unset_cell(self, i, j):
        old_val = self.board[i][j]
        self.row_sets[i].add(old_val)
        self.col_sets[j].add(old_val)
        self.get_square_set(i,j).add(old_val)
        self.board[i][j] = '.'

    def solveSudoku(self, board: List[List[str]]) -> None:
        self.board = board
        self.row_sets = [set(map(str, range(1, 10))) for _ in range(9)]
        self.col_sets = [set(map(str, range(1, 10))) for _ in range(9)]
        self.square_sets = [set(map(str, range(1, 10))) for _ in range(9)]

        # populate initial sets
        for i, row in enumerate(self.board):
            for j, cell in enumerate(row):
                if cell == '.': continue
                self.set_cell(i, j, self.board[i][j])
        
        self.solve_recursive()

import unittest

class Test37(unittest.TestCase):
    cases = [
        (
            [["5","3",".",".","7",".",".",".","."],
             ["6",".",".","1","9","5",".",".","."],
             [".","9","8",".",".",".",".","6","."],
             ["8",".",".",".","6",".",".",".","3"],
             ["4",".",".","8",".","3",".",".","1"],
             ["7",".",".",".","2",".",".",".","6"],
             [".","6",".",".",".",".","2","8","."],
             [".",".",".","4","1","9",".",".","5"],
             [".",".",".",".","8",".",".","7","9"]],

            [["5","3","4","6","7","8","9","1","2"],
             ["6","7","2","1","9","5","3","4","8"],
             ["1","9","8","3","4","2","5","6","7"],
             ["8","5","9","7","6","1","4","2","3"],
             ["4","2","6","8","5","3","7","9","1"],
             ["7","1","3","9","2","4","8","5","6"],
             ["9","6","1","5","3","7","2","8","4"],
             ["2","8","7","4","1","9","6","3","5"],
             ["3","4","5","2","8","6","1","7","9"]]
        ),
    ]

    def test_cases(self):
        s = Solution()
        for board, expected in self.cases:
            s.solveSudoku(board)
            self.assertEqual(board, expected)

if __name__ == "__main__":
    unittest.main()

