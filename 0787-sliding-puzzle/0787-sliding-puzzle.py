class Solution:
    def slidingPuzzle(self, board: List[List[int]]) -> int:

        best = [[-1 for _ in range (3)] for _ in range (2)]
        best [0] [0], best [0] [1], best [0] [2] = 1, 2, 3
        best [1] [0], best [1] [1], best [1] [2] = 4, 5, 0
        
        def check (mat):
            for i in range (2):
                for j in range (3):
                    if mat [i] [j] != best [i] [j]:
                        return False
            return True
        
        def inBounds (x, y):
            return 0 <= x < 2 and 0 <= y < 3
        memo = {}
        
        def helper (x, y, moves):
            if check (board):
                return moves
            state_key = tuple (tuple (row) for row in board)
            if (state_key, moves) in memo:
                return memo [(state_key, moves)]
            if moves >= 20:
                return float ('inf')
            min_moves = float ('inf')
            # Move left
            if inBounds (x, y + 1):
                board [x] [y], board [x] [y + 1] = board [x] [y + 1], board [x] [y]
                min_moves = min (min_moves, helper (x, y + 1, moves + 1))
                board [x] [y], board [x] [y + 1] = board [x] [y + 1], board [x] [y]
            # Move down
            if inBounds (x + 1, y):
                board [x] [y], board [x + 1] [y] = board [x + 1] [y], board [x] [y]
                min_moves = min (min_moves, helper (x + 1, y, moves + 1))
                board [x] [y], board [x + 1] [y] = board [x + 1] [y], board [x] [y]
            # Move right
            if inBounds (x, y - 1):
                board [x] [y], board [x] [y - 1] = board [x] [y - 1], board [x] [y]
                min_moves = min (min_moves, helper (x, y - 1, moves + 1))
                board [x] [y], board [x] [y - 1] = board [x] [y - 1], board [x] [y]
            # Move up
            if inBounds (x - 1, y):
                board [x] [y], board [x - 1] [y] = board [x - 1] [y], board [x] [y]
                min_moves = min (min_moves, helper (x - 1, y, moves + 1))
                board [x] [y], board [x - 1] [y] = board [x - 1] [y], board [x] [y]
            memo [(state_key, moves)] = min_moves
            return min_moves
        start_x, start_y = -1, -1
        for i in range (2):
            for j in range (3):
                if board [i] [j] == 0:
                    start_x, start_y = i, j
                    break
        result = helper (start_x, start_y, 0)
        return result if result != float ('inf') else -1