/***************************************************************************
*  ffmpegGUI. Frontend for ffmpeg                                          *
*  Copyright (C) 2009-2012  Marco Bavagnoli - lil.deimos@gmail.com         *
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

#ifndef FFMPEGFRONTEND_H
#define FFMPEGFRONTEND_H

#include <QProcess>
#include <QDialog>
#include <QFile>
#include <QFileInfoList>
#include <QDir>

#define QUOTEME_(x) #x
#define QUOTEME(x) QUOTEME_(x)

namespace Ui {
    class ffmpegFrontend;
    class ffmpegOutput;
}


typedef struct {
    QStringList args;
    QFileInfo input_file;
    QFileInfo output_file;
} queue;

////////////////////////////////////////////////////////////////////
////  OUTPUT  //////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
class ffmpegOutput : public QDialog
{
    Q_OBJECT

public:
    explicit ffmpegOutput(QWidget *parent = 0);
    ~ffmpegOutput();
    void setStopButtonDisabled(bool b);
    void setCommandText(QString s);
    void setOutputText(QString s);
    void appendOutputText(QString s);
    void setErrorText(QString s);
    void appendErrorText(QString s);
    void showErrorWidget();
    void hideErrorWidget();
    void clearLogFile();
    void setLogging(bool b);
    void closeLoggingFile();
    QDir logLocation;
    QFile *html_log;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ffmpegOutput *ui;
    bool logging;

private slots:
    void on_PB_stop_ffmpeg_clicked();
    void on_PB_close_clicked();

signals:
    void PB_stop_ffmpeg_clicked();
};

////////////////////////////////////////////////////////////////////
////  FRONTEND  ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
class ffmpegFrontend : public QDialog
{
    Q_OBJECT

public:
    explicit ffmpegFrontend(QWidget *parent = 0);
    ~ffmpegFrontend();
    Ui::ffmpegFrontend *ui;
    bool check_ffmpeg_filters_availability();
    QFileInfoList getPresetFileList();
    void parseArgs(QString args);
    QStringList getArgs();
    QString getSizeAndPaddingParameters(QFileInfo input_file);
    void runFfmpeg(QStringList args, QFileInfo input_file, QFileInfo output_file=QFileInfo());

    QStringList commands;
    QStringList commands_string;
    bool delete_original_video;
    QList<queue> queue_obj;

protected:
    void changeEvent(QEvent *e);

private:
    QProcess ffmpeg;
    QFileInfo last_output_file;
    QFileInfo last_input_file;
    QDir local_preset_directory;
    ffmpegOutput *output;
    void connectSlots();
    void setDefaults();
    void disconnectSlots();
    void setupCB_formats();
    void setupCB_codecs();
    void setupCB_presets();
    void remove_command(QString command);
    void check_command(QString command, QString arg);
    void replace_command(QString command,
                         QString command_replace_with,
                         QString arg_replace_with);


public slots:
    void ffmpegStdout();
    void ffmpegStderr();
    void ffmpegFinished( int exitCode);
    void ffmpegStarted();
    void ffmpegError(QProcess::ProcessError err);
    void onStop_ffmpeg_clicked();

private slots:
    void onCB_delete_original_video_clicked(bool b);
    void on_PB_clear_log_file_clicked();
    void on_PB_convert_video_file_clicked();
    void on_PB_save_current_preset_clicked();
    void on_CB_container_currentIndexChanged(int index);
    void onTE_preview_args_textChanged();
    void onCB_ffmpeg_preset_changed(int i);
    void on_CB_disable_audio_clicked(bool checked);
    void on_CB_disable_video_clicked(bool checked);
    void on_CB_as_original_clicked(bool checked);
    void update_ffmpeg_args();
    void update_ffmpeg_GUI_args();

    void on_PB_view_log_clicked();

    void on_PB_set_ffmpeg_dir_clicked();

    void on_LE_ffmpeg_dir_returnPressed();

    void on_pushButton_clicked();

signals:
    void preset_or_args_changed();
};

#endif // FFMPEGFRONTEND_H
