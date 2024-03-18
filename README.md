This is a simulator of the card game Euchre, written by Shahed Al Massri

♠️♦️♣️♥️

Currently the game can play a round of 5 tricks and determine the winner of a trick, and the winner of a round.
There is a function to draw the trick at its current state as well as the player's hand when player is making a card selection

Update March 18th 2024:
- Added second round trump prompt and decision-making for both player and computer
- Currently doesn't force dealer to choose trump if everyone passes, if everyone passes on the second round the game exits
- Next round is to set up continous playing of the game until one team reaches a score of 10
- After that computer logic has to be added so computer isn't just making random decisions on passing/trump/cards to play

Update March 12th 2024:
- Added first round trump decision-making round (where a specific card is flipped up)
- Next step to finish trump decision round is to add the second round where players can make trump any suit

Next steps:
- Trump decision making round (in progress)
- Computer player's logic for trump selection
- Computer player's logic for card selection
- Input validation for user's card selection, card chosen must adhere to game rules
- Add the ability for players to go alone 
- Clean up and comments
