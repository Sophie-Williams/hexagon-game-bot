# Hexagon game bot
This part of game "Hexagon" implementing game of bot.

More precisely, it is the tcp-server which listens to a certain port.
When he accepts data of the game card, he looks for the best step for the player and sends back the card.
## Fast start
 For Linux
```
cd <hexagon-game-bot/>
mkdir out/
cd out/
cmake ../
make
./hexagon-game-bot
```
 For Win32
```
cd <hexagon-game-bot>
mkdir out\
cd out\
cmake ..\
MSBuild hexagon-game-bot.vcxproj
start Debug\hexagon-game-bot.exe
```
