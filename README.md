ffmpeg-gui: mirror repo of Ffmpeg frontend of VenenuX
==========

ffmpegGUI. Frontend for ffmpeg


ABOUT
------

ffmpegGUI is a frontend to ffmpeg that allow you to set most important
conversion parameters. You can choose your preferred installed preset
or make and save your own. You can batch convert multiple videos and have
a log file in html format, if destination size ratio differ, ffmpegGUI
will automatically add a padding.

Written using Qt framework.


INSTALL & USAGE
----------------

In Linux/X11 or Mac OS/X, install the latest Qt development packages that
you will find on http://qt.nokia.com/ on terminal, go inside the source 
tree and run:

qmake (or qmake-qt4, usually in Debian)
make (or gmake, if use older GNU command)

and thenrun from the current dir as: "./ffmpeg-gui".

For install u can made "make install" but this target are experimental, 
there's no process to uninstall, files are under DESTDIR variable.


PLANS & ISSUES:
---------------

translations and preset are not right handle by instalation, the 
program only manage the ffmpeg frontend, the ffplay and ffprobe still not.

* this only acts as command line wrapper for the ffmpeg command transcoder.
* ffprobe its the media detector, there are plans for implementing.
* ffplay are a command line player directly using the ffmpeg libs.



LICENCE:
--------

Copyright (C) 2010-2012  Marco Bavagnoli - lil.deimos@gmail.com
Copyright (C) 2013  PICCORO Lenz McKAY - mckaygerhard@gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


CONTACT:
--------

Hope you enjoy this app and if you have any comment, suggestions or bug report,
leave me an email <lil.deimos@gmail.com>, I will be happy for your support.



