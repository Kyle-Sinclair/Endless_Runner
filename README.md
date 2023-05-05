# Endless_Runner


A 2-player coop Endless Runner prototype build designed to learn basic OOP principles in Unreal Engine. 

# Controls

PLayer 1 (Left Side) 
WD - Move Left and Right
Spacebar - jump

PLayer 2 (Right Side) 
Arrow keys - Move Left and Right
Spacebar - Enter

F10 - Quit game
# Controls




Track Manager as a class manages both the track pieces the players stand on
and has now taken over obstacle management as well. This allows me to
satisfy the despawn spec requirement by having a queryable collection.

The 2 Player mode is done through a custom Playercontroller class that is linked at 
run time by Game mode. 

As a twist, when an obstacle is 'despawned' off the track, it will be teleported to
the other track. The chance of this teleportation occuring increases with obstacle
successfully dodged and resets upon being hit.

This teleportation does move obstacles between collections. In order to avoid 
access competition, all obstacle management occurs in discrete phases of each tick.

The creation and  destruction of obstacles is still done in a programatically naive way.
I ran out of time to move to an object factory for reuse of existing elements, so garbage 
collection occurs wastefully often. 

At start time the program access a customisable file path to load up an existing
* best time *. Upon either player taking three points of damage, the game will reset and 
the current time will be compared to the best time and stored if it is longer. It would be better 
to move to a JSON file for storing this data but I ran out of time to debug it appropriately, so 
currently only one high score is saved. 



 