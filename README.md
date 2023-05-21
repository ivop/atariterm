### Atari 800 Emulator in a terminal or console

Uses standard vt100/ANSI to fake a GTIA/ANTIC image.  

Needs a terminal window or console of at least 48x31 characters. Modern
terminal emulators like gnome-terminal, konsole, lxterminal, but also the
Linux console and good 'ol xterm work fine. It needs to handle vt100/ANSI
codes and unicode characters. A proper unicode font for all the control
character glyphs is required.

##### Instructions:

* download the atari800 sources from https://github.com/atari800/atari800

* configure it with ./configure --target=libatari800

* make it so

* copy src/libatari800.a to the atariterm directory

* make

* ./atariterm [atari800 command line options]

If you use the default $HOME/.atari800.cfg configuration you might see
some error messages flash by that complain about SDL related stuff. You
can safely ignore them.  

##### Keybindings:

* F2 Option
* F3 Select
* F4 Start
* F5 Warmstart (+shift is coldstart)
* F6 Help
* F7 Break
* F8 Caps
* F9 Exit emulator
* Alt-, Alt-. and Alt-; map to Control-, Control-. and Control-; respectively.

The code in this repository is Copyright © 2023 by Ivo van Poorten  

See LICENSE for details.  
