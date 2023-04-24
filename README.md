# Endless_Runner

# Design Principles

An Endless Runner prototype build designed to learn basic OOP principles in Unreal Engine. 

The program is divided into discrete classes which perform different roles

The Meshes which provide the ground for our character all extend one class called Track Segment
These pieces can have their mesh component altered in the blueprint editor but are currently 
all one kind for prototyping purposes.

The movement and management of these track segments are handled by a Track manager class, which is responsible
for shifting them on the x-axis a certain amount per frame. In order to avoid creating and destroying actors
repeatedly, this track manager moves the position of the final track piece back to the front of the track
at appropriate times. 

Pointers to these track segments are currently stored in a Tarray inside Track Manager. In order to facilitate
swapping out and swapping back in track pieces, Track Manager holds two weak pointers to the furthest forward
and furthest behind pieces of track, called HeadTrackPiece and TailTrackPiece respectively. These allow the
manager to track the outermost segments of the track. 

In order to keep these pointers pointing to the outermost segments of track despite swapping the rearmost for the foremost
intermittently, each track segment has a weak pointer to the track segments either side of it. Track manager can update its
head and tail track pieces to the subsequent pieces easier this way. 

Currently, obstacles are spawned by track Manager when it switches the rear Track Segment to the fore. 
These new actors are then attached to that track piece so that their relative positions are maintained
as the track shifts. These actors are then destroyed 


# Features
 
# To Do

# # Needs

- Dynamic difficulty influencing speed
- Dynamic difficulty influencing how common obstacles are
- Lives lost upon obstacle collision
- Widget reporting on lives
- Save lives to file

# # Nice to have 

- Moving Obstacles such as projectiles
- Dynamic allocation of static mesh components
- Subsystem for obstacle creation

