/***************************************************************************
*  FFMPEG-GUI settings source file, frontend for ffmpeg                    *
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


#include <QDir>
#include <QDebug>
#include <QDesktopServices>
#include "settings.h"

settings::settings()
{
    QString homePath;

//    Q_WS_PM  Does this still works on OS/2 ?
//    these should
//    Q_OS_OS2     Defined on OS/2.
//    Q_OS_OS2EMX  Defined on XFree86 on OS/2 (not PM).
#if defined(Q_OS_OS2) || defined(Q_OS_OS2EMX)  || defined(Q_WS_PM)

    homePath = QDir::toNativeSeparators( QDesktopServices::storageLocation(QDesktopServices::DataLocation)+"/ffmpeg-gui.conf");
#else
    homePath=QDir::toNativeSeparators( QDir::homePath()+"/.config/ffmpeg-gui.conf" );
#endif

    conf = new QSettings(homePath,QSettings::IniFormat);
//    qDebug() << "File path to store settings file:" << homePath;
}

settings::~settings()
{
    delete conf;
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void settings::store_settings( QString name, int value)
{
    conf->setValue(name, value);
}

void settings::store_settings( QString name, QString value)
{
    conf->setValue(name, value);
}

void settings::store_settings( QString name, QByteArray value)
{
    conf->setValue(name, value);
}

void settings::store_settings( QString name, bool value)
{
    conf->setValue(name, value);
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
