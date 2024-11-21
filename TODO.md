# Techtree

- Add a techtree to the GUI (in the top right corner)
- Add more type of buildings and resources unlockables and finish connections

# Buildings

- Add visual representation of buildings (Cookie clicker style)
- Manage the memory pool of visuals buildings (e.g. 1 visual building for 10 buildings when exceeding a number of building)
- Add a way to unlock building (Implementation but should be in the GUI)

# Resources

- Move the resources to the top of the screen (Civilization style)

# Energy

- Add an energy resource
- Add an energy building (Wind turbine, solar panel, etc.)
- Add a way to convert energy to other resources (e.g. energy to gold)
- Add a way to convert other resources to energy (e.g. wood to energy) if the building made for this is built

# Save

- Add a save button to save the game state (refeer to a user id)
- Add a load button to load the game state

- Make a file format to store the useful data of the player
- Make a parser for this custom file format (have to be optimized)
- Make a loader to set the fetched value as in-game value
- Make a checker to not allow the player to custom the save file to beat the game faster
- 

# Prestige

- Add a prestige system
	- Prestige is meant to be a late-game feature aiming at restarting a new game with particular multiplier to ease the progression of the next saves.
	- The number of prestige bonuses that can be choose is determined by the number of "Prestige point".
- Add a prestige resource
	- Prestige resources is a set of bonus post-prestige late-game useful resources to be converted to prestige points or additional gold.
- Add a prestige building
	- Prestige building is a set of bonus post-prestige late-game useful buildings to yield prestige resources
	- Prestige buildings can be bought for gold as normal building does. 
- Add prestige points
	- Prestige points is an in-game currency that can be use to buy prestige bonuses in order to generate more prestige point, therefore have even more bonuses once the next prestige is reached.
- Add prestige bonuses
	- Prestige bonuses is a set of bonuses useful to generate more resources faster, it can be a global variable multiplier, flat base to click then variable mutliplier, a bonus explosion at certain stage of gold reached, new reasearches and many more.
