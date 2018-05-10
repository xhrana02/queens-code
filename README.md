# Queens Regicide

Bachelor's thesis (zadání bakalářské práce): **Hra v OpenGL**  
Author: **Pavel Hranáč (xhrana02)**


## Prebuilt Windows 64x Release with windeployqt

https://drive.google.com/open?id=1gl10WCPCNWVyFDwmtwtpFoeEp0muKSsV


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


## Resources:

Natanael Gama (Cinzel Decorative Font) www.fontsquirrel.com/license/cinzel-decorative  
https://texture.ninja (grass texture, wall texture)  
http://spiralgraphics.biz (ice texture, wizard's balls texture)  
http://game-icons.net (all ability icons)  
Individual creators from Game-icons:
21 icon bases by Lorc, 3 by Delapouite, 1 by Carl Olsen, 1 by sbed, 1 by Skoll

## Known bugs:

#### Picture freezing when not looking at any units

Bug: during game -> zoom and pan so that no units are in your view -> picture freezes (but not the application)  
Reason: Signal QQuickWindow::beforeRendering() is not getting emitted
Priority: 4/10 (weird but not game-breaking)

#### Accidental game end in options menu

Bug: during game -> game menu -> options -> fullscreen to windowed -> click in empty space -> jumps to main menu  
Reason: Unknown  
Priority: 3/10 (game-breaking but avoidable)

#### Macro redefinitions

Bug: compile solution in MSVC -> macro redefinitions  
Reason: Multiple sources (GPUEngine and Microsoft) set the same OpenGL macros  
Priority: 1/10 (annoying)
