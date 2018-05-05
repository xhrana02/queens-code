# Queens Regicide

Bachelor's thesis (zadání bakalářské práce): **Hra v OpenGL**  
Author: **Pavel Hranáč (xhrana02)**


## Prebuilt Windows 64x Release

https://drive.google.com/open?id=1FflLXqP8NIciPeTzc2IEI4n9J8Ogn9pO


## Prerequisites:

* **C++11**

* **CMake 3.8**  
	https://cmake.org/

* **GPUEngine (tested on version from 25.03.2018)**  
	https://github.com/Rendering-FIT/GPUEngine

* **Qt 5.7**  
	https://www.qt.io/

* **assimp 3.3**  
	http://www.assimp.org/


## Instructions:

directory \libs\ needs following files in the following structure  
\libs\Debug\assimpd.dll  
\libs\Debug\geCored.dll  
\libs\Debug\geGLd.dll  
\libs\Debug\geSGd.dll  
\libs\Debug\Qt5Cored.dll  
\libs\Debug\Qt5Guid.dll  
\libs\Debug\Qt5Networkd.dll  
\libs\Debug\Qt5Qmld.dll  
\libs\Debug\Qt5Quickd.dll  
\libs\Debug\Qt5QuickWidgetsd.dll  
\libs\Debug\Qt5Widgetsd.dll  
\libs\Release\assimp.dll  
\libs\Release\geCore.dll  
\libs\Release\geGL.dll  
\libs\Release\geSG.dll  
\libs\Release\Qt5Core.dll  
\libs\Release\Qt5Gui.dll  
\libs\Release\Qt5Network.dll  
\libs\Release\Qt5Qml.dll  
\libs\Release\Qt5Quick.dll  
\libs\Release\Qt5QuickWidgets.dll  
\libs\Release\Qt5Widgets.dll

These files are then copied to the output directory after build depending on the chosen build type. If this method doesn't work, copy the same files to the output directory manually.


## Used software:

CMake (solution builder)  
Microsoft Visual Studio 2017 (C++ code)  
Microsoft Visulo Studio Code (QML code)  
Blender (modeling)  
GitHub (source control)


## Resources:

https://texture.ninja/ (grass texture, wall texture)  
http://spiralgraphics.biz (ice, wizard's balls)  
http://game-icons.net/ (all ability icons)


## KNOWN BUGS:

#### QApplicationCore unexpected null

BUG: run in debug -> during game -> game menu -> to title -> error in the console for every ice block  
REASON: If I don't delete the ice blocks at the end of the game (causing memory leak) the warnings don't show. No idea why.  
PRIORITY: 4/10 (Mild annoyance but could be a symptom of a more serious problem)

#### Accidental game end in options menu

BUG: during game -> game menu -> options -> fullscreen to windowed -> click in empty space -> jumps to main menu  
REASON: Unknown  
PRIORITY: 3/10 (Game-breaking but rare and avoidable)

#### Macro redefinitions

BUG: compile solution in MSVC -> macro redefinitions  
REASON: Multiple sources (GPUEngine and Microsoft) set the same OpenGL macros  
PRIORITY: 1/10 (Mild annoyance)
