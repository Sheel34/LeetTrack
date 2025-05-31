class Solution:
    def snakesAndLadders(self, board: List[List[int]]) -> int:
        boardSize = len(board)
        visited = [False] * (boardSize * boardSize + 1)
        queue = deque([(1, 0)])  # (cellNumber, moveCount)
        visited[1] = True

        while queue:
            cellNumber, moveCount = queue.popleft()
            if cellNumber == boardSize * boardSize:
                return moveCount

            for diceRoll in range(1, 7):
                nextCell = cellNumber + diceRoll
                if nextCell > boardSize * boardSize:
                    break

                row, col = self.getCoordinates(nextCell, boardSize)
                destination = board[row][col] if board[row][col] != -1 else nextCell

                if not visited[destination]:
                    visited[destination] = True
                    queue.append((destination, moveCount + 1))

        return -1
    def getCoordinates(self, cellNumber, boardSize):
        colIndex = (cellNumber - 1) % boardSize
        rowIndex = (cellNumber - 1) // boardSize
        if rowIndex % 2 == 0:
            actualCol = colIndex
        else:
            actualCol = boardSize - colIndex - 1
        return boardSize - rowIndex - 1, actualCol
