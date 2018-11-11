# LinBound2

[![Build Status](https://travis-ci.org/gbaudic/linbound2.svg?branch=master)](https://travis-ci.org/gbaudic/linbound2)
[![Appveyor Build status](https://ci.appveyor.com/api/projects/status/l7s64j4n2iv2cf2j?svg=true)](https://ci.appveyor.com/project/gbaudic/linbound2)

LinBound aims to be an open-source clone of the game [GunBound](http://gunbound.softnyx.net), a multiplayer turn-based arcade game with a gameplay very close to Worms, Hedgewars or WarMUX. It is primarily targeted to Linux but it aims to be as cross-platform as possible.  
This repository is an attempt to start again implementation from a clean state, using more state-of-the-art software engineering and coding practices. 

## Documentation

Please see the wiki for more information about the goals of this project, implementation details and roadmaps. Many of these can date back to 2012 or earlier, so be careful. 

## Dependencies

Linbound uses SDL2, SDL2_image, SDL2_ttf, SDL2_mixer, SDL2_net and SDL2_gfx.  
It also relies on TinyXML2 for XML processing.  
GUI subsystem will be handled by guisan (https://github.com/gbaudic/guisan).  
For the server part, SQLite will be used. 

## Credits

Unless otherwise stated, the code is covered by the Mozilla Public License.  
Some of the artwork (test maps) comes from the WarMUX project. 
The SDL2 libraries, TinyXML2 and Box2D use a zlib license. Guisan is under a BSD license. 
