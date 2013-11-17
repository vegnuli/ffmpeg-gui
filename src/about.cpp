/***************************************************************************
*  FFMPEG-GUI about source file                                            *
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

#include <QDesktopServices>
#include <QUrl>

#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::about)
{
    m_ui->setupUi(this);
}

about::~about()
{
    delete m_ui;
}

void about::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

