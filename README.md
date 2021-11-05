# **MineStorm**

## **General information**

This project is a student project done for ISART Digital by Rémi SERRA and Alexandre PERCHÉ.

The goal was to recreate the "MineStorm" game released on Vectrex in 1982. <br>
This game can be played with a keyboard or a gamepad, by 1 or 2 players.

The game object assets were provided by the school. <br>
All keybinding assets come from itch.io free assets packs :

- [Gerald's keys](https://gerald-burke.itch.io/geralds-keys)

- [Kenney's input prompts](https://kenney-assets.itch.io/input-prompts-pixel-16)

<br>

## **Game information**

When starting a game, a spaceship (the minelayer) lays mines on the playing field. <br>
These mines then spawn gradually when the player destroys them. <br>
When all the mines have spawned, the minelayer comes back and lays 3 more mines. <br>
Finally, when all  the mines have been destroyed and the minelayer is destroyed or gone, the round ends and a new, more difficult one starts.

<br>

## **Technical details**

The game runs on the simple and easy-to-use [raylib 4.0](https://www.raylib.com/) library made for game programming. <br>
A custom mathematics library was created for this project. It is mainly used to detect collisions between the game objects' hitboxes. <br>
Game rendering is done on a render texture, to enable post processing effects, such as scanlines and screen shake.

Upon valgrind inspection, the project leaks and has a few errors. These are all caused by OpenGL and raylib.

<br>

## **Sound design**

The original soundtrack was composed by Alexandre PERCHÉ. <br>
<iframe width="350px" height="300" scrolling="no" frameborder="no" allow="autoplay" src="https://w.soundcloud.com/player/?url=https%3A//api.soundcloud.com/tracks/1148721193&color=%23ff5500&auto_play=false&hide_related=false&show_comments=true&show_user=true&show_reposts=false&show_teaser=true&visual=true"></iframe><div style="font-size: 10px; color: #cccccc;line-break: anywhere;word-break: normal;overflow: hidden;white-space: nowrap;text-overflow: ellipsis; font-family: Interstate,Lucida Grande,Lucida Sans Unicode,Lucida Sans,Garuda,Verdana,Tahoma,sans-serif;font-weight: 100;"><a href="https://soundcloud.com/user-131837480-851531639" title="vegasword" target="_blank" style="color: #cccccc; text-decoration: none;">vegasword</a> · <a href="https://soundcloud.com/user-131837480-851531639/minestorm-mind" title="MineStorm Mind" target="_blank" style="color: #cccccc; text-decoration: none;">MineStorm Mind</a></div> <br>

All sound effects come from the [Freesound](https://freesound.org/) website, and are licensed under the Creative Commons Attribution license. Sound effects were also remixed by Alexandre PERCHÉ. <br>

<br>

## **Screenshots**

<img src="./data/screenshots/screenshot0.png" style="width:400px;"/>
<img src="./data/screenshots/screenshot1.png" style="width:400px;"/>
<img src="./data/screenshots/screenshot2.png" style="width:400px;"/>
<img src="./data/screenshots/screenshot3.png" style="width:400px;"/>
