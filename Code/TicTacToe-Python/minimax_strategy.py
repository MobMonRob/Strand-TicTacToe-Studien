
def check_win(board, player):
    """
    Check if the player has won the game.
    """
    # Define winning combinations
    win_combinations = [
        [0, 1, 2], [3, 4, 5], [6, 7, 8],  # Rows
        [0, 3, 6], [1, 4, 7], [2, 5, 8],  # Columns
        [0, 4, 8], [2, 4, 6]              # Diagonals
    ]

    for combo in win_combinations:
        if all(board[i] == player for i in combo):
            return True
    return False

def minimax(board, depth, maximizing_player):
    # Base cases: Check if the game is over or if the depth limit is reached
    if check_win(board, 'X'):
        return -10 + depth  # AI player wins
    elif check_win(board, 'O'):
        return 10 - depth   # Human player wins
    elif not any([c == '' for c in board]):  # Check if the board is full
        return 0  # Tie game

    if maximizing_player:
        max_eval = float('-inf')
        for i, cell in enumerate(board):
            if cell == '':
                board[i] = 'O'
                eval = minimax(board, depth + 1, False)
                board[i] = ''
                max_eval = max(max_eval, eval)
        return max_eval
    else:
        min_eval = float('inf')
        for i, cell in enumerate(board):
            if cell == '':
                board[i] = 'X'
                eval = minimax(board, depth + 1, True)
                board[i] = ''
                min_eval = min(min_eval, eval)
        return min_eval

def best_move(board):
    best_score = float('-inf')
    best_move_index = None
    for i, cell in enumerate(board):
        if cell == '':
            board[i] = 'O'
            score = minimax(board, 0, False)
            board[i] = ''
            if score > best_score:
                best_score = score
                best_move_index = i
    return best_move_index