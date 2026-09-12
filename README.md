# ♟️ Chess in C++
 
A chess game written in C++, built primarily as a project to learn and practice
the language.

## :dart: Purpose

The project was created as a way to lean C++ by building something from scratch while getting more comfortable with C++ features like classes,
structs, enums, pointers, references and much more. 

## :construction: Project status

Almost finished!

This project has not been prioritized in newer times because of other projects
and school subjects. The main chess mechanics have been implemented, with some
missing details. 

### Whats missing
- En passant 
- All stalemate scenarios

## :arrow_forward: Builing & Running

```bash 
git clone https://github.com/BrouZie/chess.git
cd chess

g++ main.cpp game.cpp board.cpp pieces.cpp -o chess
./chess
```


## :rocket: Further improvenments 

These are the further improvenments we would make if we were to come back to
this project.

### En passant
This feature would be added to the pawns to complete movenment for all
pieces.

### All stalemate scenarios
Most stalemate scenarios are in place, like no legal moves and insufficient
material. The missing scenarios are 50-Move rule, Draw by repition and when it
is impossible for either side to capture another piece.

### Timer
Implementing a timer would be a great addition to the game to play the game in
different formats.

### GUI
At the moment the game is visualized in the terminal by a small grid and the
user is recieved some prompts for the next move, or an error message if the user tries to
do something illegal. Upgrading to a GUI would largely enhance the player
experience.

### Data oriented programming
To keep pushing our skills and learn new skillsets, rewriting the code from
classes to a more data oriented design would pose new challanges and fun
obstacles.
