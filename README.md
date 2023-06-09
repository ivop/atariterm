### Atari 800 Emulator in a terminal or console

Uses standard vt100/ANSI to fake a GTIA/ANTIC image.  

Needs a terminal window or console of at least 48x31 characters. Modern
terminal emulators like gnome-terminal, konsole, lxterminal, but also the
Linux console and good 'ol xterm work fine. It needs to handle vt100/ANSI
codes and unicode characters. A proper unicode font for all the control
character glyphs is required.

##### Precompiled Binaries

You can download precompiled binaries on the [release page](https://github.com/ivop/atariterm/releases/tag/v1.0).

##### Compilation Instructions

* download the atari800 sources from https://github.com/atari800/atari800

* run ./autogen.sh and configure it with CFLAGS=-O3 ./configure --disable-sdltest --disable-cursesbasic --disable-crashmenu --disable-eventrecording --disable-audiorecording --disable-videorecording --disable-screenshots --disable-pngcodec --disable-zmbvcodec  --disable-opengl-by-default --disable-bufferdlog --disable-newcycleexact --target=libatari800

* make it so

* copy src/libatari800.a to the atariterm directory

* make

* ./atariterm -config config.cfg [atari800 command line options]

If you use your default $HOME/.atari800.cfg configuration you might see
some error messages flash by that complain about SDL related stuff. You
can safely ignore them. The supplied sample config file does not include
any ROM paths. You have to setup these yourself.  

Limitted color support by the fake GTIA and ANTIC implementation. Only two shades per color and a lot of colors map to the same base color. You do get
a different text color than the background though, just like a Sophia upgrade
on real hardware. You get used to yellow on blue pretty quickly.  

Instead of the unreadable unicode character for escape (␛) I have to chosen
to display the lunate epsilon symbol (ϵ).  

Non-text modes are displayed as empty scanlines in groups of eight. Rendering
graphics 3, 4, and 5 should be possible with unicode characters, but I
doubt its usefulness.  

The emulator runs at the approximately normal speed of 20ms per frame.  

##### Keybindings

* F1 Pause emulation; you can now select and copy text from the window.
* F2 Option
* F3 Select
* F4 Start
* F5 Warmstart (+shift is coldstart)
* F6 Help
* F7 Break
* F8 Caps
* F9 Exit emulator
* Alt-, Alt-. and Alt-; map to Control-, Control-. and Control-; respectively, becuase the control combinations cannot be detected.
* Alt-h, Alt-i, and Alt-m map to Control-h, Control-i, and Control-m, because they cannot be distinguished from the ASCII controls for BS, TAB and CR. In case they clash with the keyboard shortcuts of your terminal emulator, you can also use Alt-[, Alt-], and Alt-\ respectively.
* Home Clear
* Arrows are cursor keys without needing to press Control.

##### Platforms

* Linux and your favorite terminal emulator that supports vt100/ANSI.

* Windows. It compiles with cygwin (not MSYS2 because it lacks termios). Run it
in cygwin's mintty. The windows terminal window is way too slow. You need to
hack the atari800
sources to use strcasecmp as Util_stricmp (util.h) or it won't compile.

* macOS. atari800 does not compile cleanly with XCode's clang. I used brew install gcc. After that, it runs fine and the terminal is fast enough.

##### Screenshots

* gnome-terminal, running the supplied sample disk

![screenshot1](img/screenshot1.png)
![screenshot3](img/screenshot3.png)

* lxterminal, different and smaller font, mixed modes

![screenshot4](img/screenshot4.png)
![screenshot5](img/screenshot5.png)

* xterm, even smaller font, running syncalc

![screenshot6](img/screenshot6.png)

The code in this repository is Copyright © 2023 by Ivo van Poorten  

See LICENSE for details.  
