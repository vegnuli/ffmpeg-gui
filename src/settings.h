/***************************************************************************
*  ffmpegGUI. Frontend for ffmpeg                                          *
*  Copyright (C) 2010-2012  Marco Bavagnoli - lil.deimos@gmail.com         *
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
#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class settings
{
public:
    explicit settings();
    virtual ~settings();

    void store_settings( QString name, int value);
    void store_settings( QString name, QString value);
    void store_settings( QString name, QByteArray value);
    void store_settings( QString name, bool value);

    QSettings *conf;
};

#endif // SETTINGS_H
