import serial
import time
import tkinter as tk
from tkinter import messagebox
from random_strategy import generate_random_value, check_win
from minimax_strategy import best_move

# Set the COM port and baud rate according to your Arduino configuration
COM_PORT = 'COM4'  # Change this to your Arduino's COM port
BAUD_RATE = 9600   # Change this to match your Arduino sketch

# Open a serial connection to the Arduino
arduino = serial.Serial(COM_PORT, BAUD_RATE, timeout=1)

def write_to_arduino(data):
    """
    Writes data to the Arduino.
    """
    arduino.write(data.encode())
    print(f"Sent to Arduino: {data}")

def read_from_arduino():
    """
    Reads data from the Arduino.
    """
    data = arduino.readline().decode().strip()
    if data:
        print(data)
    return data

def update_gui(board):
    """
    Update the Tic Tac Toe GUI based on the board state.
    """
    for i, value in enumerate(board):
        labels[i].config(text=value)

def on_closing():
    """
    Function to handle cleanup tasks and close the serial connection when the GUI is closed.
    """
    print("Serial connection closed.")
    arduino.close()
    root.destroy()

def play_game():
    """
    Function to play the game using the selected game mode.
    """
    game_mode = mode_picker.get()
    sent_values = set()
    human_clicks = set()
    board = [""] * 9

    while True:
        received_data = read_from_arduino()

        if received_data == "All 9 positions have been visited. Stopping the program.":
            print("Received stopping message from Arduino. Stopping the program.")
            break

        if received_data.startswith("The human clicked on:"):
            human_click = int(received_data.split(":")[-1].strip())
            human_clicks.add(human_click)
            board[human_click - 1] = "O"
            update_gui(board)
            if check_win(board, "O"):
                messagebox.showinfo("Game Over", "Player O wins!")
                break  # End the game

        if received_data and "Enter the position you want to visit (1-9):" in received_data:
            # Use the selected game mode to generate a move
            if game_mode == "Random":
                value = generate_random_value(sent_values, human_clicks)
            elif game_mode == "Minimax":
                # Get the best move index from the minimax algorithm
                best_index = best_move(board)
                # Convert the index to a string before sending it to Arduino
                value = str(best_index + 1)  # Add 1 to match the Arduino's indexing

            # Add the value to the set of sent values
            sent_values.add(int(value))

            # Send the value to the Arduino
            write_to_arduino(value)
            print(f"Sent value to Arduino: {value}")

            board[int(value) - 1] = "X"
            update_gui(board)
            if check_win(board, "X"):
                messagebox.showinfo("Game Over", "Player X wins!")
                break  # End the game

        root.update()
        time.sleep(0.1)  # Add a small delay to avoid busy-waiting and reduce CPU usage

    else:
        messagebox.showinfo("Game Over", "It's a tie!")  # If no one wins and the game ends due to all positions filled

# Create the main window
root = tk.Tk()
root.title("Tic Tac Toe")
root.geometry("500x600")
root.resizable(False, False)

# Create labels for the Tic Tac Toe grid starting from 9 to 1
labels = []
for i in reversed(range(1, 10)):
    label = tk.Label(root, text="", font=("Helvetica", 16), relief="solid", borderwidth=1, width=10, height=5)
    label.grid(row=(9-i)//3, column=(9-i)%3, sticky="nsew")
    labels.append(label)

# Configure row and column weights to make the labels fill the entire width and height
for i in range(3):
    root.grid_rowconfigure(i, weight=1)
    root.grid_columnconfigure(i, weight=1)

# Picklist to choose game mode
mode_picker = tk.StringVar(root)
mode_picker.set("Random")  # Default mode
mode_menu = tk.OptionMenu(root, mode_picker, "Random", "Minimax")
mode_menu.grid(row=3, columnspan=3)

# Button to play the game
play_button = tk.Button(root, text="Play", command=play_game)
play_button.grid(row=4, columnspan=3)

# Bind the on_closing function to the window close event
root.protocol("WM_DELETE_WINDOW", on_closing)

# Start the GUI main loop
root.mainloop()
