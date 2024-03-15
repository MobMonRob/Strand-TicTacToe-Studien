import serial
import serial.tools.list_ports
import time
import tkinter as tk
from tkinter import messagebox
from tkinter import ttk
from random_strategy import generate_random_value, check_win
from minimax_strategy import best_move
import pygame
import os
import random

BAUD_RATE = 9600  # Change this to match your Arduino sketch
AUDIO_FOLDER = "Audio"  # Folder containing the MP3 files


def play_sound(sound_file):
    pygame.mixer.music.load(sound_file)
    pygame.mixer.music.play()


def init_sound():
    pygame.mixer.init()


class TicTacToeApp:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("DHBW: Tic Tac Toe")
        self.root.iconbitmap('images/tic-tac-toe.ico')
        self.root.geometry("600x600")
        self.root.resizable(False, False)
        self.root.configure(background='#f0f0f0')

        self.labels = []
        self.arduino = None

        self.game_mode = tk.StringVar(self.root, "Random")
        self.last_played_sound = None

        self.setup_ui()
        init_sound()

    def setup_ui(self):
        for i in range(3):
            for j in range(3):
                label = tk.Label(self.root, text='', font=('Arial', 50), relief="solid", borderwidth=1, width=8,
                                 height=3, bg='white')
                label.grid(row=i, column=j, sticky="nsew", padx=5, pady=5)
                self.labels.append(label)

        for i in range(3):
            self.root.grid_rowconfigure(i, weight=1)
            self.root.grid_columnconfigure(i, weight=1)

        mode_menu_frame = ttk.Frame(self.root)
        mode_menu_frame.grid(row=3, columnspan=3, pady=10)

        mode_label = ttk.Label(mode_menu_frame, text="Game Mode:", font=("Arial", 12))
        mode_label.grid(row=0, column=0, padx=(0, 5))

        random_radio = ttk.Radiobutton(mode_menu_frame, text="Random", variable=self.game_mode, value="Random")
        random_radio.grid(row=0, column=1)

        minimax_radio = ttk.Radiobutton(mode_menu_frame, text="Minimax", variable=self.game_mode, value="Minimax")
        minimax_radio.grid(row=0, column=2)

        play_button = tk.Button(self.root, text="Play", command=self.play_game, font=("Arial", 14), bg='#4CAF50',
                                fg='white', width=50)
        play_button.grid(row=4, column=0, columnspan=3, pady=10)

        self.root.protocol("WM_DELETE_WINDOW", self.on_closing)

    @staticmethod
    def find_arduino_port():
        ports = serial.tools.list_ports.comports()
        for port, desc, hwid in sorted(ports):
            if 'arduino' in desc.lower():
                return port
        return None

    def connect_to_arduino(self):
        port = self.find_arduino_port()
        if port:
            self.arduino = serial.Serial(port, BAUD_RATE, timeout=1)
            print(f"Connected to Arduino on port {port}")
        else:
            print("Arduino not found.")

    def write_to_arduino(self, data):
        if self.arduino:
            self.arduino.write(data.encode())
            print(f"Sent to Arduino: {data}")

    def read_from_arduino(self):
        if self.arduino:
            data = self.arduino.readline().decode().strip()
            if data:
                print(data)
            return data
        return None

    def update_gui(self, board):
        for i, value in enumerate(board):
            if value == "X":
                self.labels[i].config(text=value, fg="red")
            elif value == "O":
                self.labels[i].config(text=value, fg="blue")
            else:
                self.labels[i].config(text=value, fg="black")

    def on_closing(self):
        print("Serial connection closed.")
        if self.arduino:
            self.arduino.close()
        pygame.mixer.quit()
        self.root.destroy()

    def get_random_sound(self):
        sound_files = [f for f in os.listdir(AUDIO_FOLDER) if f.endswith(".mp3")]
        if sound_files:
            sound_file = random.choice(sound_files)
            while sound_file == self.last_played_sound:
                sound_file = random.choice(sound_files)
            self.last_played_sound = sound_file
            return os.path.join(AUDIO_FOLDER, sound_file)
        else:
            return None

    def play_game(self):
        game_mode = self.game_mode.get()
        sent_values = set()
        human_clicks = set()
        board = [""] * 9

        if not self.arduino:
            self.connect_to_arduino()

        while True:
            value = None
            received_data = self.read_from_arduino()

            if received_data == "All 9 positions have been visited. Stopping the program.":
                print("Received stopping message from Arduino. Stopping the program.")
                break

            if received_data.startswith("The human clicked on:"):
                human_click = int(received_data.split(":")[-1].strip())
                human_clicks.add(human_click)
                board[human_click - 1] = "O"
                self.update_gui(board)
                if check_win(board, "O"):
                    messagebox.showinfo("Game Over", "Player O wins!")
                    break
                sound_file = self.get_random_sound()
                if sound_file:
                    play_sound(sound_file)

            if received_data and "Enter the position you want to visit (1-9):" in received_data:
                if game_mode == "Random":
                    value = generate_random_value(sent_values, human_clicks)
                elif game_mode == "Minimax":
                    best_index = best_move(board)
                    value = str(best_index + 1)

                sent_values.add(int(value))
                self.write_to_arduino(value)
                print(f"Sent value to Arduino: {value}")

                board[int(value) - 1] = "X"
                self.update_gui(board)
                if check_win(board, "X"):
                    messagebox.showinfo("Game Over", "Player X wins!")
                    break
                elif len(sent_values) == 9:  # Check for draw
                    messagebox.showinfo("Game Over", "It's a draw!")
                    break
            self.root.update()
            time.sleep(0.1)


if __name__ == "__main__":
    app = TicTacToeApp()
    app.root.mainloop()
