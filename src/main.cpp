/***************************************************************************
*  FFMPEG-GUI main  source file, frontend for ffmpeg                       *
*  Copyright (C) 2009-2012  Marco Bavagnoli - lil.deimos@gmail.com         *
*  Copyright (C) 2013  PICCORO Lenz McKAY - mckaygerhard@gmail.com         *
*                                                                          *
*  This program is free software: you can redistribute it and/or modify    *
*  it under the terms of the GNU General Public License as published by    *
*  the Free Software Foundation, either version 3 of the License, or       *
*  (at your option) any later version.                                     *
*                                                                          *
*  This program is distributed in the hope that it will be useful,         *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of          *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
*  GNU General Public License for more details.                            *
*                                                                          *
*  You should have received a copy of the GNU General Public License       *
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
***************************************************************************/

#include <QtGui/QApplication>
#include <QTranslator>
#include <QLocale>
#include "ffmpegfrontend.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ffmpegFrontend w;

    QLocale l;
    QString localeName=l.name();
    QTranslator translator;

    if (localeName.contains("de")) translator.load(":/usr/share/ffmpeg-gui/ffmpeg-gui_de");
    if (localeName.contains("es")) translator.load(":/usr/share/ffmpeg-gui/ffmpeg-gui_es");
    if (localeName.contains("es_ES")) translator.load(":/usr/share/ffmpeg-gui/ffmpeg-gui_es");
    if (localeName.contains("es_VE")) translator.load(":/usr/share/ffmpeg-gui/ffmpeg-gui_es_VE");
    if (localeName.contains("ru")) translator.load(":/usr/share/ffmpeg-gui/ffmpeg-gui_ru");
    if (localeName.contains("ua")) translator.load(":/usr/share/ffmpeg-gui/ffmpeg-gui_ua");
    if (localeName.contains("it")) translator.load(":/usr/share/ffmpeg-gui/ffmpeg-gui_it");

    a.installTranslator(&translator);


    w.show();

    return a.exec();
}
