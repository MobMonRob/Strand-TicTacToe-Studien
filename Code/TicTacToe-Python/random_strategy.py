import random

def generate_random_value(sent_values, human_clicks):
    """
    Generate a random value between 1 and 9 (excluding already sent and human-clicked values).
    """
    available_values = set(range(1, 10)) - sent_values - human_clicks
    if available_values:
        return str(random.choice(list(available_values)))
    return None

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
