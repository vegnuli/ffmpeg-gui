<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.0" language="ru">
<context>
    <name>QObject</name>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="484"/>
        <location filename="../src/ffmpegfrontend.cpp" line="553"/>
        <location filename="../src/ffmpegfrontend.cpp" line="689"/>
        <location filename="../src/ffmpegfrontend.cpp" line="1028"/>
        <location filename="../src/ffmpegfrontend.cpp" line="1052"/>
        <source>error</source>
        <translation>ошибка</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="484"/>
        <location filename="../src/ffmpegfrontend.cpp" line="553"/>
        <source>ffmpeg could not starts or some error occurred</source>
        <translation>не запустился ffmpeg или произошка какая-то ошибка</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="689"/>
        <source>codec is not in the list</source>
        <translation>кодек не из списка</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="1028"/>
        <source>cannot read ffmped output</source>
        <translation>не могу прочесть вывод ffmpeg</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="1052"/>
        <source>ffmped could not get video information</source>
        <translation>ffmpeg не может получить видео-инфо</translation>
    </message>
</context>
<context>
    <name>ffmpegFrontend</name>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="20"/>
        <source>ffmpeg parameters</source>
        <translation>параметры ffmpeg</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="42"/>
        <source>Preset</source>
        <translation>Предустановки</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="88"/>
        <source>save current preset</source>
        <translation>сохранить текущие предустановки</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="105"/>
        <source>Items with a red circle are those commonly used</source>
        <translation>Часто используемые элементы - с красным кружком</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="126"/>
        <source>Audio codec</source>
        <translation>Кодек звука</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="161"/>
        <source>Disable audio stream</source>
        <translation>Отключить звуковой поток</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="176"/>
        <location filename="../src/ffmpegfrontend.ui" line="363"/>
        <source>bit rate</source>
        <translation>битрейт</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="215"/>
        <source>frequency</source>
        <translation>частота</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="254"/>
        <source>channels</source>
        <translation>каналы</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="314"/>
        <source>Video codec</source>
        <translation>Кодек видео</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="348"/>
        <source>Disable video stream</source>
        <translation>Отключить видео поток</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="402"/>
        <source>frame rate</source>
        <translation>частота кадров</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="462"/>
        <source>Container format</source>
        <translation>Формат контейнера</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="513"/>
        <source>As original</source>
        <translation>Как оригинал</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="529"/>
        <source>Resolution</source>
        <translation>Разрешение</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="624"/>
        <source>log to html file</source>
        <translation>лог в html-файл</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="643"/>
        <source>Clear log</source>
        <translation>Очистить лог</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="680"/>
        <source>-1 = no thread parameter
0 = let ffmpeg decide
&gt;0 number of threads to use
This parameter is not stored in presets</source>
        <translation>-1 = без параметров потока
0 = на усмотрение ffmpeg
&gt;0 использовать число потоков
Эти параметры не сохранены в предустановках</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="788"/>
        <source>Exit</source>
        <translation>Выход</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="807"/>
        <source>choose video file(s)</source>
        <translation>конвертировать видео</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="814"/>
        <source>delete original video
after the conversion</source>
        <translation>удалить оригинальное\nвидео после конвертации</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="723"/>
        <source>ffmpeg command line parameters. You can add your own here and press enter key to update the view.
When executing will be added:
&lt;-i INPUT_FILE&gt; at the begin
&lt;OUTPUT_FILE&gt; at the end
-vf scale=W:H,pad=W:H:X:Y:#000000
-threads n (if n&gt;=0).
WARNING: if a file with the same name exists, will be replaced (-y option added by default).</source>
        <translation>Параметры командной строки ffmpeg. Вы можете здесь добавить свои собственные и нажать Enter.
При выполнении будут добавлены:
&lt;-i INPUT_FILE&gt; в начало
&lt;OUTPUT_FILE&gt; в конец
-vf scale=W:H,pad=W:H:X:Y:#000000
-threads n (if n&gt;=0).
ВНИМАНИЕ: если файл с таким именем уже существует - он будет заменен (опция -y добавлена по умолчанию).</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="395"/>
        <source>file name</source>
        <translation>имя файла</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="395"/>
        <source>input a short file name description</source>
        <translation>введите краткое описание файла</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="396"/>
        <source>description</source>
        <translation>описание</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="396"/>
        <source>if you like input also a description</source>
        <translation>если Вам нравится также введите описание</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="501"/>
        <location filename="../src/ffmpegfrontend.cpp" line="570"/>
        <location filename="../src/ffmpegfrontend.cpp" line="572"/>
        <source>don&apos;t care</source>
        <translation>безразлично</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="575"/>
        <source>copy video stream</source>
        <translation>копировать видео поток</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="577"/>
        <source>copy audio stream</source>
        <translation>копировать звуковой поток</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="1170"/>
        <location filename="../src/ffmpegfrontend.cpp" line="1208"/>
        <source>ffmpeg error
</source>
        <translation>ошибка ffmpeg</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="1171"/>
        <location filename="../src/ffmpegfrontend.cpp" line="1209"/>
        <source>The original video file still be in </source>
        <translation>Файл-оригинал видео все еще находится в</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="1222"/>
        <source>Convert video</source>
        <translation>Конвертировать видео</translation>
    </message>
</context>
<context>
    <name>ffmpegOutput</name>
    <message>
        <location filename="../src/ffmpegoutput.ui" line="14"/>
        <location filename="../src/ffmpegoutput.ui" line="20"/>
        <source>ffmpeg output</source>
        <translation>вывод ffmpeg</translation>
    </message>
    <message>
        <location filename="../src/ffmpegoutput.ui" line="46"/>
        <source>stop</source>
        <translation>стоп</translation>
    </message>
    <message>
        <location filename="../src/ffmpegoutput.ui" line="53"/>
        <source>ffmpeg executed command</source>
        <translation>ffmpeg выполнил команду</translation>
    </message>
    <message>
        <location filename="../src/ffmpegoutput.ui" line="114"/>
        <source>Close</source>
        <translation>Закрыть</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="91"/>
        <source>error</source>
        <translation>ошибка</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="92"/>
        <source>Log file couldn&apos;t be opened</source>
        <translation>Не могу открыть лог-файл</translation>
    </message>
</context>
</TS>
