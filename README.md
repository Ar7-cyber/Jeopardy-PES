Jeopardy-PES (Terminal-Based Game)

A terminal-based interactive Jeopardy-style quiz game written in C.
This project uses queues for player management, timed questions, category-based gameplay, and supports multiple players.

Features

    Multi-player Support

Players enter their names and join a queue system.

    Categories

Players select categories (General, Science, Tech, Movies, Sports).

    Timed Questions

Each player must answer within a time limit using alarm() and signals.

    Score Tracking

Correct answers add points, wrong answers deduct points.

    Winner Announcement

After all questions are completed, the player with the highest score is announced.

    Modular Code Structure
	     •	main.c → Game flow and UI
	     •	jeopardy.c → Core logic (questions, player queue, scoring)
	     •	jeopardy.h → Structs, macros, and function declarations



Project Structure
    Jeopardy-PES/
    │
    ├── main.c          # Main game loop, player input, menus
    ├── jeopardy.c      # Question handling, queue logic, scoring
    ├── jeopardy.h      # Struct definitions & function prototypes
    └── README.md



How to Compile

Use GCC:
     gcc main.c jeopardy.c -o jeopardy

Run the game:
     ./jeopardy



How to Play
	1.	Enter number of players
	2.	Enter their names
	3.	Each player selects a category
	4.	Answer questions within the time limit
	5.	Scores are updated automatically
	6.	After all rounds, the winner is displayed


Dependencies

This game uses only standard C libraries:
	•	stdio.h
	•	stdlib.h
	•	string.h
	•	unistd.h
	•	signal.h

No external libraries required.
  
