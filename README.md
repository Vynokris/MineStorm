# **MineStorm**

## **General information**

This project is a student project done for ISART Digital by Rémi SERRA and Alexandre PERCHÉ.

The goal was to recreate the "MineStorm" game released on Vectrex in 1982. <br>
This game can be played with a keyboard or a gamepad, by 1 or 2 players.

Try it <a href="https://vynokris.itch.io/modern-minestorm" target="_blank">here</a>!

The game object assets were provided by the school. <br>
All keybinding assets come from itch.io free assets packs :

- <a href="https://gerald-burke.itch.io/geralds-keys" target="_blank">Gerald's keys</a>

- <a href="https://kenney-assets.itch.io/input-prompts-pixel-16" target="_blank">Kenney's input prompts</a>

<br>

## Preview

<img src="./data/screenshots/minestorm.gif"/> <img src="./data/screenshots/screenshot0.png" style="width:260px;"/>
<img src="./data/screenshots/screenshot4.png" style="width:260px;"/>
<img src="./data/screenshots/screenshot1.png" style="width:260px;"/>
<img src="./data/screenshots/screenshot2.png" style="width:260px;"/>
<img src="./data/screenshots/screenshot3.png" style="width:260px;"/>

<br>

## **Game information**

When starting a game, a spaceship (the minelayer) lays mines on the playing field. <br>
These mines then spawn gradually when the player destroys them. <br>
When all the mines have spawned, the minelayer comes back and lays 3 more mines. <br>
Finally, when all  the mines have been destroyed and the minelayer is destroyed or gone, the round ends and a new, more difficult one starts.

<br>

## **Technical details**

The game runs on the simple and easy-to-use <a href="https://www.raylib.com/" target="_blank">raylib 4.0</a> library made for game programming. <br>
A custom mathematics library was created for this project. It is mainly used to detect collisions between the game objects' hitboxes. <br>
Game rendering is done on a render texture, to enable post processing effects, such as scanlines and screen shake.

Upon valgrind inspection, the project leaks and has a few errors. These are all caused by OpenGL and raylib.

<br>

## **Sound design**

The original soundtrack was composed by Alexandre PERCHÉ. <br>
<a href="https://soundcloud.com/user-131837480-851531639" target="_blank">vegasword's soundcloud</a> · <a href="https://soundcloud.com/user-131837480-851531639/minestorm-mind" target="_blank">MineStorm Mind</a> <br>

All sound effects come from the <a href="https://freesound.org/" target="_blank">Freesound</a> website, and are licensed under the Creative Commons Attribution license. Sound effects were also remixed by Alexandre PERCHÉ. <br>
