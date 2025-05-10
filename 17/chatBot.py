# python3 -m pip install --upgrade --extra-index-url https://PySimpleGUI.net/install PySimpleGUI

import PySimpleGUI as sg
from nltk.chat.util import Chat, reflections

# Movie data
movies = {
    'Interstellar': ['10:00 AM', '2:00 PM', '6:00 PM'],
    'The Dark Knight': ['11:00 AM', '3:00 PM', '7:00 PM'],
    'Dune': ['9:30 AM', '1:30 PM', '5:30 PM']
}

# Chat patterns
patterns = [
    (r'hi|hello|hey', ['Hello! How can I assist you today?']),
    (r'how are you', ['I am just a bot, but always ready to help!']),
    (r'(.*) movie', [f"Available movies: {', '.join(movies)}"]),
    (r'(.*) ticket', ['How many tickets would you like to book?']),
    (r'(.*) showtime|timing', ["Showtimes:\n" + '\n'.join(f"{m}: {', '.join(t)}" for m, t in movies.items())]),
    (r'(.*) book tickets', ["Great! Let's proceed with booking."]),
    (r'(.*)(bye|goodbye)', ['Thanks for visiting! Enjoy your movie.']),
]

chatbot = Chat(patterns, reflections)

# Booking state
booking_mode = False
step = 0
temp_data = {}

# Ticket booking logic
def book_tickets(movie, tickets, showtime):
    try:
        total = int(tickets) * 100
        return f"🎟 Booking confirmed!\n{tickets} tickets for '{movie}' at {showtime}.\nTotal: ₹{total}"
    except:
        return "❌ Please enter a valid ticket number."

# Layout
layout = [
    [sg.Multiline(size=(60, 20), key='-CHAT-', disabled=True, autoscroll=True)],
    [sg.Input(key='-INPUT-', do_not_clear=False), sg.Button("Send", bind_return_key=True)]
]

window = sg.Window("🎬 Movie Ticket ChatBot", layout, finalize=True)

# Initial message
window['-CHAT-'].print("Bot: Hello! How can I assist you today?")

while True:
    event, values = window.read()
    if event == sg.WINDOW_CLOSED:
        break

    msg = values['-INPUT-'].strip()
    if not msg:
        continue

    window['-CHAT-'].print(f"You: {msg}")

    if booking_mode:
        if step == 1:
            if msg not in movies:
                window['-CHAT-'].print("Bot: Choose from: " + ', '.join(movies))
                continue
            temp_data['movie'], step = msg, 2
            window['-CHAT-'].print("Bot: How many tickets?")
        elif step == 2:
            temp_data['tickets'], step = msg, 3
            times = '\n'.join(movies[temp_data['movie']])
            window['-CHAT-'].print(f"Bot: What showtime for '{temp_data['movie']}'?\nOptions:\n{times}")
        elif step == 3:
            temp_data['showtime'] = msg
            result = book_tickets(**temp_data)
            window['-CHAT-'].print(f"Bot: {result}")
            booking_mode, step, temp_data = False, 0, {}    
    elif "book tickets" in msg.lower():
        booking_mode, step = True, 1
        window['-CHAT-'].print("Bot: Which movie would you like to watch?")
    else:
        response = chatbot.respond(msg) or "Sorry, I didn't understand that."
        window['-CHAT-'].print(f"Bot: {response}")

window.close()
