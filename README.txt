ffmpegGUI. Frontend for ffmpeg
Copyright (C) 2010-2012  Marco Bavagnoli - lil.deimos@gmail.com

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



ABOUT
ffmpegGUI is a frontend to ffmpeg that allow you to set most important
conversion parameters. You can choose your preferred installed preset
or make and save your own. You can batch convert multiple videos and have
a log file in html format, if destination size ratio differ, ffmpegGUI
will automatically add a padding.
Written using Qt framework.


Building
In Linux/X11, Mac OS/X or Windows, install the latest Qt development packages that
you will find on http://qt.nokia.com/ then on dos prompt(windows) or terminal, go inside the
source tree and run:
qmake (or qmake-qt4, usually in Debian)
make (or nmake, if you're on windows)




Hope you enjoy this app and if you have any comment, suggestions or bug report,
leave me an email <lil.deimos@gmail.com>, I will be happy for your support.

http://mediadownloader.cz.cc



CHANGELOG
v1.1 (10 Jan 2012)
	fixed unandled spaces in paths
	added about button
	added path chosing for ffmpeg executable
