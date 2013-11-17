/***************************************************************************
*  FFMPEG-GUI main frontend source for wrapper gui rexpress usage ffmpeg   *
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

#include <QRegExp>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>
#include <QDesktopServices>
#include <QFileDialog>
#include <QFile>
#include <QUrl>
#include <QDateTime>

#include "about.h"
#include "settings.h"
#include "ffmpegfrontend.h"
#include "ui_ffmpegfrontend.h"
#include "ui_ffmpegoutput.h"

////////////////////////////////////////////////////////////////////
////  OUTPUT  //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
ffmpegOutput::ffmpegOutput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ffmpegOutput)
{
    ui->setupUi(this);
    logging=false;

    QDir path;
#ifdef DEBUGGING
    logLocation.setPath(QString(QUOTEME(PWD_PRO))); // for debug mode read preset in path
#else
    #ifdef Q_WS_X11
        logLocation.setPath(QDir::homePath()+"/.ffmpeg-gui");
    #endif

    // directory not exist, create
    if (!logLocation.exists()) logLocation.mkdir(logLocation.absolutePath());

    // dont copy files to home, only put here the modified/created by users
    #ifdef Q_WS_X11
        QDir systemPath;
        QFileInfoList entries;
        QFile file;			// TODO: macro for shared dir install
        systemPath.setPath("/usr/share/ffmpeg/"); // was /etc/ffmpeg-gui/
        entries= systemPath.entryInfoList(QStringList("MD*.ffpreset"),QDir::Files,QDir::Name);
        foreach (QFileInfo f, entries) {
            file.setFileName(f.absoluteFilePath());
            file.copy(QDir::homePath()+"/.ffmpeg-gui/"+f.fileName());
        }
    #endif

#endif

    html_log = new QFile(logLocation.absolutePath()+"/ffmpegLog.html");

    ui->PTE_ffmpeg_error->hide();
}

ffmpegOutput::~ffmpegOutput()
{
    delete html_log;
    delete ui;
}

void ffmpegOutput::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ffmpegOutput::setStopButtonDisabled(bool b)
{
    ui->PB_stop_ffmpeg->setDisabled(b);
}

void ffmpegOutput::clearLogFile()
{
    html_log->remove();
}

void ffmpegOutput::setLogging(bool b)
{
    logging=b;
    if (!logging) return;
    if (!html_log->open(QIODevice::Append | QIODevice::Text) ) {
        QMessageBox::warning(this,
                             tr("error"),
                             tr("Log file couldn't be opened"),
                             QMessageBox::Ok);
        logging=false;
    }
}

void ffmpegOutput::closeLoggingFile()
{
    if (logging) {
        html_log->write("<hr style=\"width: 100%; height: 25px; background-color: rgb(0, 0, 255);\"> <br>");
        html_log->close();
    }
}

void ffmpegOutput::on_PB_close_clicked()
{
    // if close, sure for stop any process
    emit PB_stop_ffmpeg_clicked();
    // now we cand close
    setStopButtonDisabled(true);
    closeLoggingFile();
    ui->PTE_ffmpeg_command->setPlainText("");
    ui->PTE_standard_output->setPlainText("");
    ui->PTE_ffmpeg_error->setPlainText("");
    ui->PTE_ffmpeg_error->hide();
    this->hide();
}

void ffmpegOutput::setCommandText(QString s)
{
    if (logging) {
        QString html;
        html=QString(
                "<table style=\"background-color: rgb(238, 238, 238); width: 100%;\""
                "border=\"2\" cellpadding=\"2\" cellspacing=\"0\">"
                "<caption style=\"background-color: rgb(187, 187, 187);\">"
                "   <strong>ffmpeg command</strong>( %2 )"
                "</caption>"
                "<tbody>"
                "<tr>"
                "  <td>"
                "    <strong>%1</strong>"
                "  </td>"
                "</tr>"
                "</tbody>"
                "</table>"
                ).arg(s).arg(QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss"));
        html_log->write(html.toAscii());
    }

    ui->PTE_ffmpeg_command->setPlainText(s);
}

void ffmpegOutput::setOutputText(QString s)
{
    if (logging) {
        QString html=s;
        html.replace("\n","<br />")+"<br />";
        html_log->write(html.toAscii());
    }
    ui->PTE_standard_output->setPlainText(s);
}

void ffmpegOutput::appendOutputText(QString s)
{
    if (logging) {
        QString html=s;
        html.replace("\n","<br />")+"<br />";
        html_log->write(html.toAscii());
    }
    s=ui->PTE_standard_output->toPlainText()+s;
    ui->PTE_standard_output->setPlainText(s);
    ui->PTE_standard_output->moveCursor(QTextCursor::End,QTextCursor::MoveAnchor);
}

void ffmpegOutput::setErrorText(QString s)
{
    if (s.isEmpty())
        ui->PTE_ffmpeg_error->hide();
    ui->PTE_ffmpeg_error->setPlainText(s);
}

void ffmpegOutput::appendErrorText(QString s)
{
    if (logging) {
        QString html=s;
        html=QString(
                "<table style=\"background-color: rgb(255, 180, 180); color: rgb(0, 0, 0); width: 100%;\""
                "border=\"2\" cellpadding=\"2\" cellspacing=\"0\">"
                "<caption style=\"background-color: rgb(180, 71, 71); color: rgb(255, 255, 255);\">"
                "   <strong>ffmpeg error</strong>"
                "</caption>"
                "<tbody>"
                "<tr>"
                "  <td>"
                "    <strong>%1</strong>"
                "  </td>"
                "</tr>"
                "</tbody>"
                "</table>"
                ).arg(html.replace("\n","<br />"));
        html_log->write(html.toAscii());
    }

    s=ui->PTE_ffmpeg_error->toPlainText()+s;
    ui->PTE_ffmpeg_error->setPlainText(s);
    ui->PTE_ffmpeg_error->moveCursor(QTextCursor::End,QTextCursor::MoveAnchor);
}


void ffmpegOutput::hideErrorWidget()
{
    ui->PTE_ffmpeg_error->hide();
}

void ffmpegOutput::showErrorWidget()
{
    ui->PTE_ffmpeg_error->show();
}


void ffmpegOutput::on_PB_stop_ffmpeg_clicked()
{
    emit PB_stop_ffmpeg_clicked();
}


////////////////////////////////////////////////////////////////////
////  FRONTEND  ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
ffmpegFrontend::ffmpegFrontend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ffmpegFrontend)
{
    ui->setupUi(this);
    ui->CB_audio_codec->setStyleSheet("font: 75 9pt \"Nimbus Mono L\";");
    ui->CB_video_codec->setStyleSheet("font: 75 9pt \"Nimbus Mono L\";");
    ui->CB_ffmpeg_preset->setStyleSheet("font: 75 9pt \"Nimbus Mono L\";");
    ui->CB_container->setStyleSheet("font: 75 9pt \"Nimbus Mono L\";");

    output = new ffmpegOutput(this);

    ui->CB_log_to_html->setToolTip(output->logLocation.absolutePath()+"/ffmpegLog.html");


    // If the process cannot be started, -2 is returned.
    // If the process crashes, -1 is returned. Otherwise,
    // the process' exit code is returned.
    int i = QProcess::execute ( "ffmpeg");
    if (i!=-2)
    {
        setupCB_formats();
        setupCB_codecs();
        setupCB_presets();

        setDefaults();

        connect(ui->CB_ffmpeg_preset, SIGNAL(currentIndexChanged(int)), this, SLOT(onCB_ffmpeg_preset_changed(int)) );
        // update command line preview in live if some thing clicked/changed
        connect(ui->TE_preview_args, SIGNAL(textChanged()), this, SLOT(onTE_preview_args_textChanged()) );

        on_CB_as_original_clicked(ui->CB_as_original->isChecked());
        // update command line preview
        update_ffmpeg_args();
    }

    connect(output, SIGNAL(PB_stop_ffmpeg_clicked()), this, SLOT(onStop_ffmpeg_clicked()) );
    connect(&ffmpeg, SIGNAL(readyReadStandardError()), this, SLOT(ffmpegStderr()) );
    connect(&ffmpeg, SIGNAL(readyReadStandardOutput()), this, SLOT(ffmpegStdout()) );
    connect(&ffmpeg, SIGNAL(finished(int)), this, SLOT(ffmpegFinished(int)) );
    connect(&ffmpeg, SIGNAL(started()), this, SLOT(ffmpegStarted()) );
    connect(&ffmpeg, SIGNAL(error(QProcess::ProcessError)), this , SLOT(ffmpegError(QProcess::ProcessError)) );

    output->setStopButtonDisabled(true);

    delete_original_video=ui->CB_delete_original_video->isChecked();

    settings conf;
    ui->LE_ffmpeg_dir->setText(conf.conf->value("ffmpeg/executable","").toString());

    update_ffmpeg_GUI_args();
}

ffmpegFrontend::~ffmpegFrontend()
{
    delete output;
    delete ui;
}

void ffmpegFrontend::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ffmpegFrontend::onCB_delete_original_video_clicked(bool b)
{
    delete_original_video=b;
}

void ffmpegFrontend::connectSlots()
{
    connect(ui->CB_delete_original_video, SIGNAL(clicked(bool)), this, SLOT(onCB_delete_original_video_clicked(bool)) );
    connect(ui->CB_as_original, SIGNAL(clicked(bool)), this, SLOT(on_CB_as_original_clicked(bool)) );
    connect(ui->CB_as_original, SIGNAL(clicked()), this, SLOT(update_ffmpeg_args()) );
    connect(ui->SB_x_resolution, SIGNAL(valueChanged(int)), this, SLOT(update_ffmpeg_args()) );
    connect(ui->SB_y_resolution, SIGNAL(valueChanged(int)), this, SLOT(update_ffmpeg_args()) );
    connect(ui->CB_video_codec, SIGNAL(currentIndexChanged(int)), this, SLOT(update_ffmpeg_args()) );
    connect(ui->CB_audio_codec, SIGNAL(currentIndexChanged(int)), this, SLOT(update_ffmpeg_args()) );
    connect(ui->CB_container, SIGNAL(currentIndexChanged(int)), this, SLOT(on_CB_container_currentIndexChanged(int)) );

    connect(ui->CB_disable_video, SIGNAL(clicked()), this, SLOT(update_ffmpeg_args()) );
    connect(ui->CB_disable_audio, SIGNAL(clicked()), this, SLOT(update_ffmpeg_args()) );
    connect(ui->SB_audio_bitrate, SIGNAL(valueChanged(int)), this, SLOT(update_ffmpeg_args()) );
    connect(ui->SB_audio_frequency, SIGNAL(valueChanged(int)), this, SLOT(update_ffmpeg_args()) );
    connect(ui->SB_audio_channels, SIGNAL(valueChanged(int)), this, SLOT(update_ffmpeg_args()) );
    connect(ui->SB_video_bitrate, SIGNAL(valueChanged(int)), this, SLOT(update_ffmpeg_args()) );
    connect(ui->SB_video_framerate, SIGNAL(valueChanged(int)), this, SLOT(update_ffmpeg_args()) );

    connect(ui->TE_preview_args, SIGNAL(textChanged()), this, SLOT(onTE_preview_args_textChanged()) );
}

void ffmpegFrontend::disconnectSlots()
{
    bool b;
    b=disconnect(ui->CB_delete_original_video, SIGNAL(clicked(bool)) ,0 ,0);

    b=disconnect(ui->CB_as_original, SIGNAL(clicked(bool)) ,0 ,0);
    b=disconnect(ui->CB_as_original, SIGNAL(clicked()) ,0 ,0);
    b=disconnect(ui->SB_x_resolution, SIGNAL(valueChanged(int)) ,0 ,0 );
    b=disconnect(ui->SB_y_resolution, SIGNAL(valueChanged(int)) ,0 ,0 );
    b=disconnect(ui->CB_video_codec, SIGNAL(currentIndexChanged(int)) ,0 ,0 );
    b=disconnect(ui->CB_audio_codec, SIGNAL(currentIndexChanged(int)) ,0 ,0 );
    b=disconnect(ui->CB_container, SIGNAL(currentIndexChanged(int)) ,0 ,0 );

    b=disconnect(ui->CB_disable_video, SIGNAL(clicked()) ,0 ,0 );
    b=disconnect(ui->CB_disable_audio, SIGNAL(clicked()) ,0 ,0 );
    b=disconnect(ui->SB_audio_bitrate, SIGNAL(valueChanged(int)) ,0 ,0 );
    b=disconnect(ui->SB_audio_frequency, SIGNAL(valueChanged(int)) ,0 ,0 );
    b=disconnect(ui->SB_audio_channels, SIGNAL(valueChanged(int)) ,0 ,0 );
    b=disconnect(ui->SB_video_bitrate, SIGNAL(valueChanged(int)) ,0 ,0 );
    b=disconnect(ui->SB_video_framerate, SIGNAL(valueChanged(int)) ,0 ,0 );

    b=disconnect(ui->TE_preview_args, SIGNAL(textChanged()), 0, 0 );
}

void ffmpegFrontend::setDefaults()
{
    disconnectSlots();
    ui->CB_video_codec->setCurrentIndex(0);
    ui->CB_disable_video->setChecked(false);
    ui->CB_audio_codec->setCurrentIndex(0);
    ui->CB_container->setCurrentIndex(0);
    ui->CB_disable_audio->setChecked(false);
    ui->CB_as_original->setChecked(true);
    ui->SB_x_resolution->setValue(640);
    ui->SB_y_resolution->setValue(480);
    ui->SB_audio_bitrate->setValue(96);
    ui->SB_audio_frequency->setValue(44100);
    ui->SB_audio_channels->setValue(1);
    ui->SB_video_bitrate->setValue(160);
    ui->SB_video_framerate->setValue(30);
    ui->SB_x_resolution->setDisabled(true);
    ui->SB_y_resolution->setDisabled(true);
    connectSlots();
}
////////////////////////////////////////////////////////////////////////////////
void ffmpegFrontend::onStop_ffmpeg_clicked()
{
    if (ffmpeg.isWritable()) ffmpeg.write("q");
}

void ffmpegFrontend::on_PB_clear_log_file_clicked()
{
    output->clearLogFile();
}

////////////////////////////////////////////////////////////////////////////////
// Checks ffmpeg scale and pad filters
bool ffmpegFrontend::check_ffmpeg_filters_availability()
{
    // Check if ffmpeg has scale and pad filters
    QProcess ffmpeg;
    bool b=true;
    ffmpeg.start( "ffmpeg -filters" );
    if (ffmpeg.waitForReadyRead()) {
        QString result;
        //           result = tmp_ffmpeg.readAllStandardError();
        result = ffmpeg.readAll();

        QRegExp rx;
        rx.setPattern("Filters:.*scale");
        rx.setMinimal(true);
        if (rx.indexIn(result, 0) == -1)
            return b=false;

        rx.setPattern("Filters:.*pad");
        rx.setMinimal(true);
        if (rx.indexIn(result, 0) == -1)
            return b=false;
    }
    return b;
}

////////////////////////////////////////////////////////////////////////////////
// Save current parameters to a <new_file>.ffpreset into HOME/.mediadownloader
void ffmpegFrontend::on_PB_save_current_preset_clicked()
{
    QString fileName = QInputDialog::getText(this, tr("file name"), tr("input a short file name description"),QLineEdit::Normal);
    QString description = QInputDialog::getText(this, tr("description"), tr("if you like input also a description"),QLineEdit::Normal);
    qDebug() << QDir::toNativeSeparators(local_preset_directory.absolutePath()+"/")+fileName+".ffpreset";
    QFile file( QDir::toNativeSeparators(local_preset_directory.absolutePath()+"/")+fileName+".ffpreset" );

    // TODO: check file char and if file exists
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
             return;

    QTextStream out(&file);
    QString command;
    int i;
    out << "# " << description << "\n";
    parseArgs(ui->TE_preview_args->toPlainText());
    for (i=0; i< commands.size(); i++) {
        command=commands[i];
        command.remove(0,1);
        if ( commands_string[i].isEmpty() )
            out << command << "\n";
        else
            out << command << "=" << commands_string.at(i) << "\n";
    }
    file.close();
    ui->CB_ffmpeg_preset->clear();
    setupCB_presets();
}
////////////////////////////////////////////////////////////////////////////////////////
// Get *.ffpreset file list
// first version at first start files are copied by MainWindow::copy_application_files()
// do not copy now, due only put modified in user dir
QFileInfoList ffmpegFrontend::getPresetFileList()
{
    QDir ffpresetDir;
    QFileInfoList ret;

#ifdef Q_WS_X11
    // search in default ffmpeg preset directory
    ffpresetDir.setPath("/usr/share/ffmpeg/");
    ffpresetDir=ffpresetDir.toNativeSeparators(ffpresetDir.absolutePath());
    ret += ffpresetDir.entryInfoList(QStringList("*.ffpreset"),QDir::Files,QDir::Name);
    if (ffpresetDir.exists()) qDebug() << "ffmpeg default presets dir: " << ffpresetDir.absolutePath();
#endif

    // search ffmpeg-gui directory
#ifdef DEBUGGING
        ffpresetDir.setPath(QString(QUOTEME(PWD_PRO))+"/ffmpeg-presets");
        local_preset_directory = ffpresetDir;
#else
    #ifdef Q_WS_X11
        // search in custom home directory
        ffpresetDir.setPath(QDir::homePath()+"/.ffmpeg-gui");
        ffpresetDir=ffpresetDir.toNativeSeparators(ffpresetDir.absolutePath());
        local_preset_directory = ffpresetDir;
    #else
        ffpresetDir.setPath(QDir::currentPath());
        local_preset_directory = ffpresetDir;
    #endif
#endif
    //ffpresetDir=ffpresetDir.toNativeSeparators(ffpresetDir.absolutePath());
    ret += ffpresetDir.entryInfoList(QStringList("*.ffpreset"),QDir::Files,QDir::Name);
    if (ffpresetDir.exists()) qDebug() << "ffmpeg home presets dir: " << ffpresetDir.absolutePath();

    return ret;
}

/** setupCB_presets ; load preset list combo list */
void ffmpegFrontend::setupCB_presets()
{
    QFileInfoList presetList=getPresetFileList();
    ui->CB_ffmpeg_preset->addItem("none");
    foreach (QFileInfo f, presetList) {
        ui->CB_ffmpeg_preset->addItem(f.baseName(), f.absoluteFilePath());
    //    qDebug () << "found " << f.absoluteFilePath() << " ffmpeg preset";
    }
}

/////////////////////////////////////////////////////////////////////////////////
// Fill container comboBoxe
// Get "ffmpeg -foramts" stdoutput to retrieve audio and video codecs availability
void ffmpegFrontend::setupCB_formats()
{
    ffmpeg.start("ffmpeg -formats");
    if (!ffmpeg.waitForFinished()) {
        QMessageBox::critical(0,QObject::tr("error"),QObject::tr("ffmpeg could not starts or some error occurred") );
        return;
    }

    QByteArray result;

    result = ffmpeg.readAllStandardOutput();

    // Retrieve video supported codecs
    QRegExp rx;
    QString format;
    QString format_description;
    QStringList description_words;
    QString item_text;
    int i;
    int pos;

    ui->CB_container->addItem(tr("don't care"), "don't care");

    rx.setPattern("( +[DE]{1,2} +)(\\w.+)\\n");
    rx.setMinimal(true);
    pos=0;
    while ((pos = rx.indexIn(result, pos)) != -1)
    {
        format=rx.cap(1).trimmed();
        format_description=rx.cap(2).trimmed();
        // Remove first word of description
        description_words=format_description.split(" ", QString::SkipEmptyParts);
        format_description.clear();
        for (i=1; i<description_words.size(); i++) {
            format_description+=description_words.at(i)+" ";
        }
        pos += rx.matchedLength();

        // Fill the formats comboBox
        if (format.contains("E"))
        {
            item_text=description_words.at(0);
            for (i=0; i<12-description_words.at(0).length(); i++)
                item_text+=" ";
            item_text+=" "+format_description;
            ui->CB_container->addItem(item_text, description_words.at(0));
            // add a red circle icon to mark of common codec
            if (description_words.at(0).contains("ogg", Qt::CaseInsensitive) ||
                description_words.at(0).contains("dvd", Qt::CaseInsensitive) ||
                description_words.at(0).contains("mp4", Qt::CaseInsensitive) ||
                description_words.at(0).contains("mpg", Qt::CaseInsensitive) ||
                description_words.at(0).contains("263", Qt::CaseInsensitive) ||
                description_words.at(0).contains("m4", Qt::CaseInsensitive) ||
                description_words.at(0).contains("mp3", Qt::CaseInsensitive) ||
                description_words.at(0).contains("264", Qt::CaseInsensitive) ||
                description_words.at(0).contains("matroska", Qt::CaseInsensitive) ||
                description_words.at(0).contains("3gp", Qt::CaseInsensitive) )
                ui->CB_container->setItemIcon(ui->CB_container->count()-1, QIcon(":/icons/icons/circle.png"));
            else
                ui->CB_container->setItemIcon(ui->CB_container->count()-1, QIcon(":/icons/icons/transparent.png"));
        }

    }

}
/////////////////////////////////////////////////////////////////////////////////
// Fill audio and video comboBoxes
// Get "ffmpeg -codecs" stdoutput to retrieve audio and video codecs availability
void ffmpegFrontend::setupCB_codecs()
{
    ffmpeg.start("ffmpeg -codecs");
    if (!ffmpeg.waitForFinished()) {
        QMessageBox::critical(0,QObject::tr("error"),QObject::tr("ffmpeg could not starts or some error occurred, please revise output and remove or chosse compatible options") );
        return;
    }

    QByteArray result;

    result = ffmpeg.readAllStandardOutput();

    // Retrieve video supported codecs
    QRegExp rx;
    QString codec_properties;
    QString codec_description;
    QStringList description_words;
    QString item_text;
    int i;
    int pos;

    ui->CB_video_codec->addItem(tr("don't care"), "don't care");
    ui->CB_video_codec->setItemIcon(ui->CB_video_codec->count()-1, QIcon(":/icons/icons/transparent.png"));
    ui->CB_audio_codec->addItem(tr("don't care"), "don't care");
    ui->CB_audio_codec->setItemIcon(ui->CB_audio_codec->count()-1, QIcon(":/icons/icons/transparent.png"));

    ui->CB_video_codec->addItem(tr("copy video stream"), "copy");
    ui->CB_video_codec->setItemIcon(ui->CB_video_codec->count()-1, QIcon(":/icons/icons/transparent.png"));
    ui->CB_audio_codec->addItem(tr("copy audio stream"), "copy");
    ui->CB_audio_codec->setItemIcon(ui->CB_audio_codec->count()-1, QIcon(":/icons/icons/transparent.png"));

    // ffmpeg 0.X and v1 the first 7 chars identify decoding, encodig, video, audio ... ffmpeg v2 are diffrent
    rx.setPattern("([DEVASDT ]{7,7})(.*)\\n");
    // TODO ffmpeg v2 the more to left 7 chars with space (6) identify decoding, encodig, video, audio ... ffmpeg v2 are diffrent
    //rx.setPattern("([\\.DEVIASDTL]{6,6}) (.*)\\n");
    rx.setMinimal(true);
    pos=0;
    while ((pos = rx.indexIn(result, pos)) != -1)
    {
        codec_properties=rx.cap(1).trimmed();
        codec_description=rx.cap(2).trimmed();
        // Remove first word of description
        description_words=codec_description.split(" ", QString::SkipEmptyParts);
        codec_description.clear();
        for (i=1; i<description_words.size(); i++) {
            codec_description+=description_words.at(i)+" ";
        }
        pos += rx.matchedLength();

        // Fill the video comboBox
        if (codec_properties.contains("E") && codec_properties.contains("V"))
        {
            item_text=description_words.at(0);
            for (i=0; i<12-description_words.at(0).length(); i++)
                item_text+=" ";
            item_text+=" "+codec_description;
            ui->CB_video_codec->addItem(item_text, description_words.at(0));
            // add a red circle icon to mark common codecs
            if (description_words.at(0).contains("mpeg", Qt::CaseInsensitive) ||
                description_words.at(0).contains("ogv", Qt::CaseInsensitive) ||
                description_words.at(0).contains("mp4", Qt::CaseInsensitive) ||
                description_words.at(0).contains("dvd", Qt::CaseInsensitive) ||
                description_words.at(0).contains("263", Qt::CaseInsensitive) ||
                description_words.at(0).contains("264", Qt::CaseInsensitive) ||
                description_words.at(0).contains("xvid", Qt::CaseInsensitive) ||
                description_words.at(0).contains("quicktime", Qt::CaseInsensitive) )
                ui->CB_video_codec->setItemIcon(ui->CB_video_codec->count()-1, QIcon(":/icons/icons/circle.png"));
            else
                ui->CB_video_codec->setItemIcon(ui->CB_video_codec->count()-1, QIcon(":/icons/icons/transparent.png"));
        }
        // Fill the audio comboBox
        if (codec_properties.contains("E") && codec_properties.contains("A"))
        {
            item_text=description_words.at(0);
            for (i=0; i<16-description_words.at(0).length(); i++)
                item_text+=" ";
            item_text+=" "+codec_description;
            ui->CB_audio_codec->addItem(item_text, description_words.at(0));
            // add a red circle icon to mark common codecs
            if (description_words.at(0).contains("mpeg", Qt::CaseInsensitive) ||
                description_words.at(0).contains("ogg", Qt::CaseInsensitive) ||
                description_words.at(0).contains("mp3", Qt::CaseInsensitive) ||
                description_words.at(0).contains("aac", Qt::CaseInsensitive) )
                ui->CB_audio_codec->setItemIcon(ui->CB_audio_codec->count()-1, QIcon(":/icons/icons/circle.png"));
            else
                ui->CB_audio_codec->setItemIcon(ui->CB_audio_codec->count()-1, QIcon(":/icons/icons/transparent.png"));
        }
    }
}

void ffmpegFrontend::onCB_ffmpeg_preset_changed(int i)
{
    // remove -vpre
    if (i==0) {
        remove_command("-vpre");
    }
    else {
        // Check if the preset is in mediadownloader dir
        // if not, it is a ffmpeg preset and use -vpre parameter and set the right codec
        // If is a mediadownloader preset, compose it into text box
        if (ui->CB_ffmpeg_preset->itemData(i).toString().contains("/.ffmpeg-gui/") || // This if we are in release mode
            ui->CB_ffmpeg_preset->itemData(i).toString().contains("/ffmpeg-presets/"))   // This if we are in debug mode
        {
            // TODO loading of MD files from systems preset paths
            QFile file(ui->CB_ffmpeg_preset->itemData(i).toString());
            // TODO: check file char and existance
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                     return;
            QString s;
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                if (!line.startsWith("#")) {
                    line = "-"+line.replace("=", " ");
                    s+=line+" ";
                }
            }
            parseArgs(s);
            update_ffmpeg_GUI_args();
        }
        else {
            // in the default ffmpeg presets, codec is written in file name: <codec>-<description>.ffprest
            // so find codec in CB_video_codec and set it
            QString codec=ui->CB_ffmpeg_preset->itemText(i);
            QString vpre=ui->CB_ffmpeg_preset->itemData(i).toString();
            codec = codec.left(codec.indexOf("-"));
            vpre = vpre.right(vpre.length()-vpre.indexOf("-")-1);
            vpre = vpre.remove(".ffpreset", Qt::CaseInsensitive);
            bool b=false;
            for (int n=0; n<ui->CB_video_codec->count(); n++)
                if ( ui->CB_video_codec->itemText(n).startsWith(codec,Qt::CaseInsensitive) ) {
                ui->CB_disable_video->setChecked(false);
                ui->CB_video_codec->setCurrentIndex(n);
                ui->CB_video_codec->setDisabled(false);
                check_command("-vpre",vpre);
                // For simplicity, if the codec is libx264, set the container to mp4
                if (codec=="libx264") {
                    ui->CB_container->setCurrentIndex(ui->CB_container->findText("mp4",Qt::MatchStartsWith));
                    check_command("-f","mp4");

                }
                // TODO olders ffmpeg do not support format loading from presets
                if (codec=="mpeg4") {
                    ui->CB_container->setCurrentIndex(ui->CB_container->findText("mp4",Qt::MatchStartsWith));
                    check_command("-f","mp4");
                }
                // TODO olders ffmpeg do not support format loading from presets
                if (codec=="h263") {
                    ui->CB_container->setCurrentIndex(ui->CB_container->findText("mp4",Qt::MatchStartsWith));
                    check_command("-f","3gp");
                }
                // TODO loading of MD files from systems preset paths
                update_ffmpeg_args();
                b=true;
                break;
            }
            if (!b)
                QMessageBox::critical(0,QObject::tr("error"),codec+" "+QObject::tr("codec is not in the list") );
        }
    }
    emit preset_or_args_changed();
}

void ffmpegFrontend::on_CB_container_currentIndexChanged(int index)
{
    // remove -f (format) ?? TODO conflicting updates when selection of presets
    if (index==0) {
        remove_command("-f");
    }
    else {
        check_command("-f",ui->CB_container->itemData(index).toString());
        update_ffmpeg_args();
    }
}

void ffmpegFrontend::on_CB_as_original_clicked(bool checked)
{
    ui->SB_x_resolution->setDisabled(checked);
    ui->SB_y_resolution->setDisabled(checked);
}

void ffmpegFrontend::on_CB_disable_video_clicked(bool checked)
{
    ui->CB_video_codec->setDisabled(checked);
}

void ffmpegFrontend::on_CB_disable_audio_clicked(bool checked)
{
    ui->CB_audio_codec->setDisabled(checked);
}

void ffmpegFrontend::onTE_preview_args_textChanged()
{
    // if return pressed inside textBox (since the CLI arguments should not contain \n)
    if (ui->TE_preview_args->toPlainText().contains("\n") ) {

        ui->TE_preview_args->setText( ui->TE_preview_args->toPlainText().remove("\n") );

        // save current cursor position
        QTextCursor c=ui->TE_preview_args->textCursor();
        int p=c.position();
        parseArgs(ui->TE_preview_args->toPlainText());
        update_ffmpeg_GUI_args();
        // restore current cursor position
        c.setPosition(p);
        ui->TE_preview_args->setTextCursor(c);
    }
}

//////////////////////////////////////////////////////////////////////////////
// parse args string to fill commands and commands_string list
void ffmpegFrontend::parseArgs(QString args)
{
    QRegExp rx;
    int pos;

    commands.clear();
    commands_string.clear();
    if (args.right(2)!=" -") args+=" -";
    rx.setPattern("(-\\w{0,}) ([\\w|\\d|:|=|+]{0,})([ ]{0,}-)");
    rx.setMinimal(true);
    pos=0;
    while ((pos = rx.indexIn(args, pos)) != -1)
    {
        commands << rx.cap(1);
        commands_string << rx.cap(2);
        pos += rx.matchedLength()-rx.cap(3).length();
    }
}
////////////////////////////////////////////////////////////
// get current args
QStringList ffmpegFrontend::getArgs()
{
    QStringList ret;
    for (int i=0; i<commands.size(); i++)
        ret << commands.at(i) + " " + commands_string.at(i);
    return ret;
}
////////////////////////////////////////////////////////////
// update args in textedit
void ffmpegFrontend::remove_command(QString command)
{
    int i=commands.lastIndexOf(command);
    if (i!=-1) {
        commands.removeAt(i);
        commands_string.removeAt(i);
    }
}

void ffmpegFrontend::check_command(QString command, QString arg)
{
    int i=commands.lastIndexOf(command);
    if (i==-1) {
        commands << command;
        commands_string << arg;
    }
    else commands_string[i] = arg;
}

void ffmpegFrontend::replace_command(QString command,
                                     QString command_replace_with,
                                     QString arg_replace_with)
{
    int i=commands.lastIndexOf(command);
    if (i==-1) check_command(command_replace_with, arg_replace_with);
    else {
        remove_command(command);
        check_command(command_replace_with, arg_replace_with);
    }
}

// Update GUI according to commands and commands_string list
void ffmpegFrontend::update_ffmpeg_GUI_args()
{
    int i,n;
    QString command;
    QRegExp rx;
    int width, height;

    // set default values
    setDefaults();
    disconnectSlots();

    for (i=0; i<commands.size(); i++)
    {
        command=commands.at(i);
        command=command.right(command.length()-1);

        /////////////
        // Check for "-vcodec" to set into CB_video_codec
        if (command=="vcodec") {
            n=ui->CB_video_codec->findData(commands_string.at(i), Qt::UserRole, Qt::MatchStartsWith);
            if (n!=-1) {
                ui->CB_video_codec->setCurrentIndex(n);
            }
            else ui->CB_video_codec->setCurrentIndex(0);
        }

        /////////////
        // Check for "-vn" to set CB_disable_video
        if (command=="vn")
            ui->CB_disable_video->setChecked(true);

        /////////////
        // Check for "-acodec" to set into CB_audio_codec
        if (command=="acodec") {
            n=ui->CB_audio_codec->findData(commands_string.at(i), Qt::UserRole, Qt::MatchStartsWith);
            if (n!=-1) {
                ui->CB_audio_codec->setCurrentIndex(n);
            }
            else ui->CB_audio_codec->setCurrentIndex(0);
        }

        /////////////
        // Check for "-an" to set CB_disable_audio
        if (command=="an")
            ui->CB_disable_audio->setChecked(true);

        /////////////
        // Check for "-f" to set into CB_audio_codec
        if (command=="f") {
            n=ui->CB_container->findData(commands_string.at(i), Qt::UserRole, Qt::MatchStartsWith);
            if (n!=-1) {
                ui->CB_container->setCurrentIndex(n);
            }
            else ui->CB_container->setCurrentIndex(0);
        }

        /////////////
        // Check for "-ab" audio bit rate
        if (command=="ab") {
            ui->SB_audio_bitrate->setValue( commands_string[i].replace("kb","").toInt() );
            ui->SB_audio_bitrate->setValue( commands_string[i].replace("k","").toInt() );
        }

        /////////////
        // Check for "-ar" audio frequency
        if (command=="ar")
            ui->SB_audio_frequency->setValue( commands_string.at(i).toInt() );

        /////////////
        // Check for "-ac" audio channels
        if (command=="ac")
            ui->SB_audio_channels->setValue( commands_string.at(i).toInt() );

        /////////////
        // Check for "-s" video size
        if (command=="s")
        {
            ui->CB_as_original->setChecked(false);
            ui->SB_x_resolution->setDisabled(false);
            ui->SB_y_resolution->setDisabled(false);
            rx.setPattern("(\\d{2,})x(\\d{2,})");
            rx.setMinimal(false);
            if (rx.indexIn(commands_string.at(i),0) != -1) {
                width  = rx.cap(1).toInt();
                height = rx.cap(2).toInt();
                ui->SB_x_resolution->setValue(width);
                ui->SB_y_resolution->setValue(height);
            }
        }

        /////////////
        // Check for "-b" video bit rate
        if (command=="b") {
            ui->SB_video_bitrate->setValue( commands_string[i].replace("kb","").toInt() );
            ui->SB_video_bitrate->setValue( commands_string[i].replace("k","").toInt() );
        }

        /////////////
        // Check for "-r" video frame rate
        if (command=="r")
            ui->SB_video_framerate->setValue( commands_string.at(i).toInt() );

        /////////////
        // Check for "-vf" video frame rate
        if (command=="vf")
        {
            // find width and height resolution from a value like:
            // scale=320:240,pad=640:240:160:0:0xFF0000
            rx.setPattern("pad=(\\d{2,}):(\\d{2,}):");
            rx.setMinimal(true);
            if (rx.indexIn(commands_string.at(i),0) != -1) {
                width  = rx.cap(1).toInt();
                height = rx.cap(2).toInt();
                ui->SB_x_resolution->setValue(width);
                ui->SB_y_resolution->setValue(height);
            }
        }

    }
    update_ffmpeg_args();
    connectSlots();
    emit preset_or_args_changed();
}

// Update commands and commands_string list according to GUI
void ffmpegFrontend::update_ffmpeg_args()
{
    QString s;
    //////////////////////////////
    // Check -vcodec (video codec)
    if (ui->CB_video_codec->currentIndex()==0) { // if "don't care" is choosen
        remove_command("-vcodec");
        if (ui->CB_disable_video->isChecked())
            check_command("-vn", " ");
    }
    else {
        if (ui->CB_disable_video->isChecked())
            replace_command("-vcodec", "-vn", " ");
        else {
            if (ui->CB_video_codec->currentIndex() == 0)
                s="copy";
            else
                s=ui->CB_video_codec->itemData( ui->CB_video_codec->currentIndex() ).toString();
            replace_command("-vn", "-vcodec", s);
        }
    }
    //////////////////////////////
    // Check -acodec (audio codec)
    if (ui->CB_audio_codec->currentIndex()==0) { // if "don't care" is choosen
        remove_command("-acodec");
        if (ui->CB_disable_audio->isChecked())
            check_command("-an", " ");
    }
    else {
        if (ui->CB_disable_audio->isChecked())
            replace_command("-acodec", "-an", " ");
        else {
            if (ui->CB_audio_codec->currentIndex() == 0)
                s="copy";
            else
                s=ui->CB_audio_codec->itemData( ui->CB_audio_codec->currentIndex() ).toString();
            replace_command("-an", "-acodec", s);
        }
    }

    ///////////////////////////////((((((((////////////////
    // Check -ab audio bit rate the default ffmpeg is 64
    if (ui->SB_audio_bitrate->value()!=64)
        check_command("-ab", QString::number(ui->SB_audio_bitrate->value())+"k" );
    else
        remove_command("-ab");

    ///////////////////////////////((((((((////////////////
    // Check -ar audio frequency the default ffmpeg is 44100
    if (ui->SB_audio_frequency->value()!=44100)
        check_command("-ar", QString::number(ui->SB_audio_frequency->value()) );
    else
        remove_command("-ar");

    ///////////////////////////////((((((((////////////////
    // Check -ac audio channels the default ffmpeg is 1
    if (ui->SB_audio_channels->value()!=1)
        check_command("-ac", QString::number(ui->SB_audio_channels->value()) );
    else
        remove_command("-ac");

    ///////////////////////////////((((((((////////////////
    // Check -b video bit rate the default ffmpeg is 200
    if (ui->SB_video_bitrate->value()!=200)
        check_command("-b", QString::number(ui->SB_video_bitrate->value())+"k" );
    else
        remove_command("-b");

    ///////////////////////////////((((((((////////////////
    // Check -r video frame rate the default ffmpeg is 25
    if (ui->SB_video_framerate->value()!=25)
        check_command("-r", QString::number(ui->SB_video_framerate->value()) );
    else
        remove_command("-r");


    // write commands parameter to TextEdit
    s.clear();
    for (int i=0; i<commands.size(); i++)
        s += commands.at(i) + " " + commands_string.at(i) + " ";
    ui->TE_preview_args->setText(s);
    emit preset_or_args_changed();
}

//////////////////////////////////////////////
// Find the resolution of given video and adjust
// padding if necessary
// I found throubles with libavfilter and ffmpeg 5:0.6-0.1 but not with 5:0.6~svn20100726-0.1
QString ffmpegFrontend::getSizeAndPaddingParameters(QFileInfo input_file)
{
    if (ui->CB_as_original->isChecked()) return "";
    // Parse output of "ffmpeg -i input_file and catch resolution.
    // for catch resolution see example when set patter for catch
    QProcess tmp_ffmpeg;
    // TODO FIXME: start a process here, get care of others if hancle, get segfaults
    tmp_ffmpeg.start("ffmpeg -i " + input_file.absoluteFilePath());
    qDebug() << "ffmpeg -i " + input_file.absoluteFilePath();
    if (tmp_ffmpeg.waitForReadyRead()) {
        output->setCommandText("ffmpeg -i " + input_file.absoluteFilePath());
        QMessageBox::critical(0,QObject::tr("error"),QObject::tr("cannot read ffmped output") );
        return "";
    }

    QString ret="";
    QByteArray result;
    QRegExp rx;
    int old_width, GUI_width;
    int old_height, GUI_height;

//    result = tmp_ffmpeg.readAll();
//    result = tmp_ffmpeg.readAllStandardOutput();
    result = tmp_ffmpeg.readAllStandardError();
    qDebug() << result;

    // round width and height to the lower multiple of 8, umm for what? padding with high values?
    GUI_width=ui->SB_x_resolution->value()/8*8;
    GUI_height=ui->SB_y_resolution->value()/8*8;

    // Example of output to parse v0.6 and above
    // Stream #0.1(und): Video: h264, yuv420p, 352x262 [PAR 1:1 DAR 176:131], 301 kb/s, 29.96 fps, 29.96 tbr, 29964 tbn, 59928 tbc
    // Example of output from 0.7 and up releases
    // Stream #0.1(und): Video: h264 (Constrained Baseline), yuv420p, 352x262, 301 kb/s, 29.96 fps, 29.96 tbr, 29964 tbn, 59928 tbc
    rx.setPattern("Stream.*Video:.*(\\d{2,})x(\\d{2,})[ |,|.]"); // TODO FIXME fixed but still return bad number
    qDebug() << "sized extracted " + rx.cap(1) + "x" + rx.cap(2);
    rx.setMinimal(true);
    if (rx.indexIn(result, 0) == -1)
    {
        output->setCommandText("ffmpeg -i " + input_file.absoluteFilePath());
        QMessageBox::critical(0,QObject::tr("error"),QObject::tr("ffmped could not get video information, conversion will keep original resolution") );
        return "";
    }
    // WxH original detected values
    old_width = rx.cap(1).toInt();
    old_height = (rx.cap(2)).toInt(); //  + "0" TODO work around for stupid thing rexpr 
    qDebug() << "sized detected " + QString::number(old_width) + "x" + QString::number(old_height);

    qreal dx,dy;
    int new_width;
    int new_height;

    // scaling factor calculated, convert all value or separated?
    dx = (qreal)ui->SB_x_resolution->value() / (qreal)old_width;
    dy = (qreal)ui->SB_y_resolution->value() / (qreal)old_height;
    qDebug() << "scaled factors " + QString::number(dx) + "x" + QString::number(dy);

    if (dx<=dy) {
        new_width = old_width * dx;
        new_height= old_height * dx;
    }
    else {
        new_width = old_width * dx;
        new_height= old_height * dy;
    }
    qDebug() << "resize calculated " + QString::number(new_width) + "x" + QString::number(new_height);

    // round width and height to the lower multiple of 8
    new_width = new_width/8*8;
    new_height= new_height/8*8; // : ?? maybe 4

    int H_padding;
    int V_padding;

    // coordinates , set position of new video in center of calculed size
    H_padding = ( (qreal)GUI_width-new_width ) / 2;
    V_padding = ( (qreal)GUI_height-new_height ) / 2;    // some fixed need here

    // TODO FIXME: due the calculate of scaling factor this assig wrong number to Y so then swaping values
    ret="-vf scale="+QString::number(new_width)+":"+QString::number(new_height)+","
        "pad="+QString::number(GUI_width)+":"+QString::number(GUI_height)+
        ":"+QString::number(H_padding)+":"+QString::number(V_padding)+":0x000000";

    return ret;
}


//////////////////////////////////////////////
// Run ffmpeg command for video conversion
void ffmpegFrontend::runFfmpeg(QStringList args, QFileInfo input_file, QFileInfo output_file)
{
    if (ffmpeg.state()!=QProcess::NotRunning) {
        // add to queue
        queue q;
        q.args = args;
        q.input_file = input_file;
        q.output_file = output_file;
        queue_obj << q;
        return;
    }

    QStringList args_twins;
    int i;

    // if output_file is not given, set it
    QString ext = ui->CB_container->itemData(ui->CB_container->currentIndex()).toString();
    if (ui->CB_container->currentIndex() == 0) // If "don't care" is set in CB_container
        ext="";
    if (output_file.fileName() == "")
        output_file.setFile(input_file.absoluteDir(),
                            input_file.completeBaseName() + "-converted." +
                            ext);

    // Remove -s WxH argument since it is made by -vf scale=...,pad=...
    i=args.indexOf(QRegExp("-s[ ]{1,}\\d{2,}x\\d{2,}"));
    if (i!=-1) {
        args.removeAt(i);
    }

    // -thread n parameter if >=0
    QString thread_param="";
    if (ui->SB_threads->value()>=0)
        thread_param = " -threads " + QString::number(ui->SB_threads->value());

    // add to output_file the extension format from the one choosen in CB_container
    if (ui->CB_container->currentIndex() > 0)
    {
        // Check if it has the right ext
        if (!output_file.completeSuffix().contains(ui->CB_container->itemData(ui->CB_container->currentIndex()).toString() ) )
            output_file.setFile(output_file.absolutePath(), output_file.baseName()+"."+
                                ui->CB_container->itemData(ui->CB_container->currentIndex()).toString());
    }
    last_input_file = input_file;
    last_output_file = output_file;

    // build command line args
    args_twins << "-i "
            // Add input file,
            << " \"" + input_file.absoluteFilePath() + "\" "
            // displayed args,
            << args
            // size and video related
            << " " + getSizeAndPaddingParameters(input_file)
            // thread numbers if defined by users or ffmpeg auto
            << thread_param
            // if defined a experimental codec use it and dont care
            << " -strict experimental"
            // -y to force overwrite and output file
            << " -y"
            // output file
            << " \"" + output_file.absoluteFilePath()+ "\"";
    QString all_args;
    for (int i=0; i<args_twins.size(); i++)
        all_args += args_twins.at(i)+" ";

    output->show();
    output->closeLoggingFile();
    output->setLogging(ui->CB_log_to_html->isChecked());
    output->setCommandText("ffmpeg "+all_args);
    output->setOutputText( "" );
//    output->setErrorText( "" );
    ffmpeg.start("ffmpeg "+all_args);

}

void ffmpegFrontend::ffmpegStdout()
{
    output->appendOutputText( QString(ffmpeg.readAllStandardOutput()) );
}

void ffmpegFrontend::ffmpegStderr()
{
    output->appendOutputText( QString(ffmpeg.readAllStandardError()) );
}

void ffmpegFrontend::ffmpegFinished( int exitCode )
{
    if (exitCode!=0) {
        output->appendErrorText( tr("ffmpeg error, please see output below and fix options choosed\n") +
                                 tr("The original video file still be in ") +
                                 last_input_file.absoluteFilePath() + "\n");
        output->showErrorWidget();
    }
    else {
        // delete original file and rename the converted
        if (delete_original_video) {
            QString new_ext;
            new_ext=last_output_file.suffix();
            if (QFile::remove(last_input_file.absoluteFilePath()))
                QFile::rename(last_output_file.absoluteFilePath(),
                              last_input_file.completeBaseName()+"."+new_ext);
        }
    }
    output->closeLoggingFile();
    output->setStopButtonDisabled(true);

    // If there are some other video to convert proced with the queue
    if ( queue_obj.size()>0 ) {
        queue tmp;
        tmp.args = queue_obj.at(0).args;
        tmp.input_file = queue_obj.at(0).input_file;
        tmp.output_file = queue_obj.at(0).output_file;
        queue_obj.removeFirst();
        runFfmpeg(tmp.args, tmp.input_file, tmp.output_file);
    }
}

void ffmpegFrontend::ffmpegStarted()
{
    output->show();
    output->setStopButtonDisabled(false);
}

void ffmpegFrontend::ffmpegError(QProcess::ProcessError err)
{
    Q_UNUSED(err)
    output->appendErrorText( tr("ffmpeg error, please see output below and fix options choosed\n") +
                             tr("The original video file still be in ") +
                             last_input_file.absoluteFilePath() );
    output->showErrorWidget();
    output->closeLoggingFile();
    output->setStopButtonDisabled(true);
}

void ffmpegFrontend::on_PB_convert_video_file_clicked()
{
    QFile file;
    QStringList fileList;
    QString s;

    fileList = QFileDialog::getOpenFileNames(this, tr("Convert video"), "");

    foreach (s, fileList) {
        file.setFileName(s);
        if (file.exists()) {
            getSizeAndPaddingParameters(QFileInfo(file));
            runFfmpeg(getArgs(), QFileInfo(file) );
        }
    }
}

void ffmpegFrontend::on_PB_view_log_clicked()
{
    if (output->html_log->exists())
        QDesktopServices::openUrl(QUrl(output->html_log->fileName(), QUrl::TolerantMode));
}

void ffmpegFrontend::on_PB_set_ffmpeg_dir_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setViewMode(QFileDialog::List);
    dialog.setDirectory(ui->LE_ffmpeg_dir->text());
    QString s=dialog.getOpenFileName(this);
    if (!s.isEmpty()) {
        settings conf;
        ui->LE_ffmpeg_dir->setText(s);
        conf.store_settings("ffmpeg/executable", s );
    }
}

void ffmpegFrontend::on_LE_ffmpeg_dir_returnPressed()
{
    settings conf;
    conf.store_settings("ffmpeg/executable", ui->LE_ffmpeg_dir->text() );
}

void ffmpegFrontend::on_pushButton_clicked()
{
    about *a = new about(this);
    a->show();
}
