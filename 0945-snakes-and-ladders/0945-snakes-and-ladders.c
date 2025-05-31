#define min(a, b) (a < b ? a : b)

int get_board_position(int** board, int boardSize, int current_index) {
    const int y = boardSize - ceil(((float)(current_index + 1) / boardSize));
    int x;
    if ((boardSize - y) % 2) {
        x = (current_index % boardSize);
    } else {
        x = (boardSize - 1) - (current_index % boardSize);
    }
    return board[y][x];
}

int snakesAndLadders(int** board, int boardSize, int* boardColSize) {
    int min_steps[boardSize * boardSize];
    for (int i = 0; i < boardSize * boardSize; i++) {
        min_steps[i] = INT_MAX;
    }
    min_steps[0] = 0;
    
    for (int move_number = 0; move_number < INT_MAX; move_number++) {
        int skipped_tiles = 0;  
        for (int tile = 0; tile < boardSize * boardSize; tile++) {
            if (min_steps[tile] != move_number) {
                skipped_tiles++;
                continue;
            }
            for (int dice_roll = 1; dice_roll <= 6; dice_roll++) {
                const int position_tile = tile + dice_roll;
                if (boardSize * boardSize <= position_tile) {
                    break;
                }
                const int destination_tile = get_board_position(board, boardSize, position_tile) - 1;
                if (destination_tile != -2) {
                    min_steps[destination_tile] = min(min_steps[destination_tile], move_number + 1);
                } else {
                    min_steps[position_tile] = min(min_steps[position_tile], move_number + 1);

                }
            }
        }
        if (min_steps[boardSize * boardSize - 1] != INT_MAX) {
            return min_steps[boardSize * boardSize - 1];
        }
        if (boardSize * boardSize == skipped_tiles) {
            return -1;
        }
    }
    return (int) 1;
}