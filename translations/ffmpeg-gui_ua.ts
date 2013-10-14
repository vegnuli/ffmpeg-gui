<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.0" language="uk">
<context>
    <name>QObject</name>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="484"/>
        <location filename="../src/ffmpegfrontend.cpp" line="553"/>
        <location filename="../src/ffmpegfrontend.cpp" line="689"/>
        <location filename="../src/ffmpegfrontend.cpp" line="1028"/>
        <location filename="../src/ffmpegfrontend.cpp" line="1052"/>
        <source>error</source>
        <translation>помилка</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="484"/>
        <location filename="../src/ffmpegfrontend.cpp" line="553"/>
        <source>ffmpeg could not starts or some error occurred</source>
        <translation>не запустився ffmpeg чи виникла якась помилка</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="689"/>
        <source>codec is not in the list</source>
        <translation>кодек не із переліку</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="1028"/>
        <source>cannot read ffmped output</source>
        <translation>не можу прочитати вивід ffmpeg</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="1052"/>
        <source>ffmped could not get video information</source>
        <translation>ffmpeg не може отримати відео-інфо</translation>
    </message>
</context>
<context>
    <name>ffmpegFrontend</name>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="20"/>
        <source>ffmpeg parameters</source>
        <translation>параметри ffmpeg</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="42"/>
        <source>Preset</source>
        <translation>Передустановки</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="88"/>
        <source>save current preset</source>
        <translation>зберегти поточні передустановки</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="105"/>
        <source>Items with a red circle are those commonly used</source>
        <translation>Популярні елементи - з червоним кружечком</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="126"/>
        <source>Audio codec</source>
        <translation>Кодек аудіо</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="161"/>
        <source>Disable audio stream</source>
        <translation>Вимкнути звуковий потік</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="176"/>
        <location filename="../src/ffmpegfrontend.ui" line="363"/>
        <source>bit rate</source>
        <translation>бітрейт</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="215"/>
        <source>frequency</source>
        <translation>частота</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="254"/>
        <source>channels</source>
        <translation>канали</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="314"/>
        <source>Video codec</source>
        <translation>Кодек відео</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="348"/>
        <source>Disable video stream</source>
        <translation>Вимкнути відео потік</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="402"/>
        <source>frame rate</source>
        <translation>частота кадрів</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="462"/>
        <source>Container format</source>
        <translation>Формат контейнера</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="513"/>
        <source>As original</source>
        <translation>Как оригінал</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="529"/>
        <source>Resolution</source>
        <translation>Роздільна здатність</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="624"/>
        <source>log to html file</source>
        <translation>звіт у html-файл</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="643"/>
        <source>Clear log</source>
        <translation>Очистити звіт</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="680"/>
        <source>-1 = no thread parameter
0 = let ffmpeg decide
&gt;0 number of threads to use
This parameter is not stored in presets</source>
        <translation>-1 = без параметрів потоку
0 = на вибір ffmpeg
&gt;0 використовувати число потоків
Ці параметри не збережено в передвстановленнях</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="788"/>
        <source>Exit</source>
        <translation>Вихід</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="807"/>
        <source>choose video file(s)</source>
        <translation>конвертувати видео</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.ui" line="814"/>
        <source>delete original video
after the conversion</source>
        <translation>видалити оригінальне\nвідео після конвертації</translation>
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
        <translation>Параметри командного рядка ffmpeg. Ви можете тут додати свої власні та натиснути Enter.
При виконанні будуть додані:
&lt;-i INPUT_FILE&gt; в початок
&lt;OUTPUT_FILE&gt; в кінець
-vf scale=W:H,pad=W:H:X:Y:#000000
-threads n (if n&gt;=0).
УВАГА: якщо файл з таким іменем вже існує - його буде замінено (опція -y додана за умовчанням).</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="395"/>
        <source>file name</source>
        <translation>ім&apos;я файла</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="395"/>
        <source>input a short file name description</source>
        <translation>введіть короткий опис файла</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="396"/>
        <source>description</source>
        <translation>опис</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="396"/>
        <source>if you like input also a description</source>
        <translation>якщо Вам подобається також уведіть опис</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="501"/>
        <location filename="../src/ffmpegfrontend.cpp" line="570"/>
        <location filename="../src/ffmpegfrontend.cpp" line="572"/>
        <source>don&apos;t care</source>
        <translation>байдуже</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="575"/>
        <source>copy video stream</source>
        <translation>копіювати відео потік</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="577"/>
        <source>copy audio stream</source>
        <translation>копіювати аудіо потік</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="1170"/>
        <location filename="../src/ffmpegfrontend.cpp" line="1208"/>
        <source>ffmpeg error
</source>
        <translation>помилка ffmpeg</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="1171"/>
        <location filename="../src/ffmpegfrontend.cpp" line="1209"/>
        <source>The original video file still be in </source>
        <translation>Файл-оригінал відео все ще знаходиться в</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="1222"/>
        <source>Convert video</source>
        <translation>Конвертувати видео</translation>
    </message>
</context>
<context>
    <name>ffmpegOutput</name>
    <message>
        <location filename="../src/ffmpegoutput.ui" line="14"/>
        <location filename="../src/ffmpegoutput.ui" line="20"/>
        <source>ffmpeg output</source>
        <translation>вивід ffmpeg</translation>
    </message>
    <message>
        <location filename="../src/ffmpegoutput.ui" line="46"/>
        <source>stop</source>
        <translation>стоп</translation>
    </message>
    <message>
        <location filename="../src/ffmpegoutput.ui" line="53"/>
        <source>ffmpeg executed command</source>
        <translation>ffmpeg виконав команду</translation>
    </message>
    <message>
        <location filename="../src/ffmpegoutput.ui" line="114"/>
        <source>Close</source>
        <translation>Закрити</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="91"/>
        <source>error</source>
        <translation>помилка</translation>
    </message>
    <message>
        <location filename="../src/ffmpegfrontend.cpp" line="92"/>
        <source>Log file couldn&apos;t be opened</source>
        <translation>Не можут відкрити файл звіту</translation>
    </message>
</context>
</TS>
