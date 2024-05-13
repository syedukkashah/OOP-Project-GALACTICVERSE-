# PROJECT FINAL REPORT
### OBJECT ORIENTED PROGRAMMING
#### Instructor: Talha Shahid
#### Section: BAI-2A

###### Prepared by:

| Name             | Roll No       |
| ---------------- | ------------- |
| Ukkashah Ahmed   | 23k-0055      |
| Ibrahim Johar    | 23k-0074      |
| Muhammad Abbas   | 23k-0068      |

# ABSTRACT

The project aims to design and implement a 2-D Space Shooter [GALACTICVERSE] where the player controlles spacecraft is supposed to shoot through enemy space craft and collect points while avoiding collision with enemy space craft
and keeping the health intact. 

# PROJECT OVERVIEW

The project uses SFML concepts and OOP concepts to make the game have attributes like:
1. Sprites and textures to add a 2-D graphical interface to the project
2. Randomly generated enemy sprites that get destroyed when player bullets come into contact with them.
3. Sound effects and UI interfaces which includes text and a space background
4. Keeping track of attributes like player score, enemy health, player health as well as timers and clocks etc.
   
The codes implementation and working is described in the ppt

# DESIGN METHODOLOGY

The process began with learning how to implement SFML in a C++ code and then dividing the work among the group member. The work was divided into four parts:
1. Implementing the Animations & the sound effects
2. Creating the Enemy, Player & Ship classes.
3. Creating the PowerBlast and Bullet classes
4. Implementing all methods in a Game class to modularise code

The next step was to compile the code and then work out all the errors and issues that the code presented. 

The project functions in a simple yet efficient way. The SFML library has been dynamically linked to the project so that the dll files have been included in all
files of the project and repeated library linking is not neccessary. The game has a player controlled space-craft which can move anywhere along the y-axis and the 
x-axis. The player controlled spacecraft can shoot bullets that destroy enemy spacecraft. In addition on gaining 50 points, the spacecraft can shoot a power blast
that destroys all enemy spacecraft in it's path. There is a music track running on the background to add ambiance and sounds played when the bullets are fired to replicate
realism. This is a game with 2-levels.

# MEMBER CONTRIBUTIONS
Since this was a collaborative project, each member contributed to the entire project in one way or another but their specific contributions are as follows:

Syed Ukkashah [23K-0055] 
- Implemented and designed the Ship, Player & Enemy classes.
- Used inheritance to increase code productivity.
- Ship movement and collision checks were handled in the Game class.
- Implemented spawn timers to avoid infinite spawns and program crashes
- Enemies were deleted once they are out of window bounds for a more efficient program.
  
Ibrahim Johar [23K-0074]  
- Created the PowerBlast & Bullet classes. 
- Manipulated bullet vectors to handle collision and ensured deletion of bullets once they are out of window bounds to ensure proper cleanup. 
- Implemented Shoot timers to avoid spraying bullets & created the "canBlast" logic for the power blast.
- Designed the cover art for the game
  
Muhammad Abbas [23K-0068]
- Created the Animation class to handle the jet thruster spritesheet
- Implemented Sound effects for a more immersive experience.
- UI was also implemented (HP bars, timers, texts, logos, etc.)
  
# RESULTS AND ANALYSIS
The project was thoroughly analyzed using different testing methods, and the results were as expected.

# CONCLUSION
In conclusion, the project successfully demonstrates the application of Object Oriented Programming in developing a GUI based 2-D game. It fulfills its objectives of efficient game implementation and paves the way for further enhancements in future iterations.

# FUTURE IMPROVEMENTS
1. Future versions or software patches could include multiple more levels with harder enemy spacecrafts
2. A boss level can be added 
3. floating power-ups could be added with different attributes like health recovery or multiple bullets being fired at once.
4. Bonus XP after a certain score threshold is achieved

# REFERENCES
Youtube and other sites were used to understand SFML and Visual Studio was used as an IDE.

# VIDEO DEMO
https://github.com/muhammad1234-max/OOP-SEMPROJECT-24/assets/115150510/0b120b85-e692-4174-8af2-a83e016e51ea
