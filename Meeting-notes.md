# Meeting Notes
In this file, you are required to take notes for your weekly meetings. 
In each meeting, you are required to discuss:

1. What each member has done during the week?
2. Are there challenges or problems? Discuss the possible solutions
3. Plan for the next week for everyone
4. Deviations and changes to the project plan, if any


# Week 1 Meeting 1 07.11.2022 18:00

**Participants**: 
1. Elias Peltokangas
2. Kabir Bissessar
3. Juho Poteri
4. Antti Pekkanen

## Summary of the meeting
- Introductions, discussed backgrounds in programming.  
This is the first or one of the first group programming projects for all of us.

- Agreed on "the secretary".  
Elias will be responsible for meeting notes, and possible other documentations / text submissions.

- Agreed on communication.  
Created a Telegram channel which will be used for internal communication.

- Sketched the contents for the project plan (game structure, initial feature list, work division etc.).  
Agreed on Elias finishing it.

## Project status
The project has officially been started and a sketch for the plan has been made.

## Next meeting
Next meeting will be on Wednesday. The project plan will be discussed and finalized as well as next steps and next meeting determined.

## TODOs for the next meeting
* Create a draft of the full project plan (Elias)
* Create/acquire an initial idea of your part and the whole project. (Everyone)


# Week 1 Meeting 2 09.11.2022 17:00

**Participants**: 
1. Elias Peltokangas
2. Kabir Bissessar
3. Juho Poteri
4. Antti Pekkanen

## Summary of works
1. **Elias**: Project plan draft completed.

2. **Kabir**: Initial preparations.

3. **Juho**: High-level draft of enemy and tower classes done.

4. **Antti**: Initial preparations.



## Challenges

1. How to have enough time to build all features.

## Actions
This week:
1. **Elias**: finalize and commit the project plan and meeting notes.

Before next meeting:
1. **Elias**: Build first version of the Map class and the map system.

2. **Kabir**: Look into GUIs and the SFML, add SFML to project, make a base/prototype window to build on.

3. **Juho**: Build first versions of Enemy and Tower classes and some subclasses, build class that generates waves of enemies.

4. **Antti**: Create first working Cmake and a basic hello world main.c, create first versions of the game class and gametime loop.



## Project status 
High level project plan is done. Some of the interfaces between software modules were preliminarily planned during this meeting.



# Week 2 Meeting 18.11.2022 15:00

**Participants**: 
1. Elias Peltokangas
2. Kabir Bissessar
3. Juho Poteri
4. Antti Pekkanen

## Summary of works
1. **Elias**: First version of map class, initialization from textfile and validation complete. Path building complete.
2. **Kabir**: Figuring out the SFML, how to run it etc.
3. **Juho**: Enemy_Factory nearly complete, enemies in progress
4. **Antti**: Gametime loop under design, cmake done, hello world done

## Challenges

1. Running the SFML GUI has problems depending on the system
2. How the game core works (we discussed this)

## Actions
1. **Elias**: Draw graphics for a resolution of about 1200x800, finish Map class (GetStart() method etc.).
2. **Kabir**: Get SFML working, create the drawing methods. Start working on the GUI class.
3. **Juho**: Tower Act takes the map of (x, y) -> Enemy as a parameter and enemy advance returns true or false depending.
4. **Antti**: Game class: variables, map, towerlist, enemypos and methods AdvanceEnemies and TowersAction. Work on GUI loop with Kabir.

## Project status
Map and enemies are roughly complete.
Goal of the next week: Get the wave part of the game running


# Week 3 Meeting 1 25.11.2022 15:00

**Participants**: 
1. Kabir Bissessar
2. Juho Poteri
3. Antti Pekkanen

## Summary of works
1. **Elias**: Images done for tiles, enemies, towers and a basic background.
2. **Kabir**: GUI can now draw general shapes.
3. **Juho**: Towers have a basic logic to attack enemies etc. (towers and enemies communicate together)
4. **Antti**: Game core has functions that advance enemies and make towers attack. (Game communicates with towers and enemies)

## Actions
1. **Elias**: Building the shop part of the game (with Kabir).
2. **Kabir**: Figuring out sprites and creating a map from maptiles (then enemies and towers).
3. **Juho**: Tower upgrade logic.
4. **Antti**: Tower building logic for the game core.

## Project status 
GUI still a work in progress. Basic structures for core and classes done. Communication between classes is partly done.  
Next focusing on piecing the puzzle together and adding the rest of the features to complete the game.

# Example Meeting xx.xx.2022 xx:xx

**Participants**: 
1. Elias Peltokangas
2. Kabir Bissessar
3. Juho Poteri
4. Antti Pekkanen

## Summary of works
1. **Elias**:
2. **Kabir**:
3. **Juho**:
4. **Antti**:

## Challenges

1. 

## Actions
1. **Elias**:
2. **Kabir**:
3. **Juho**:
4. **Antti**:


## Project status 