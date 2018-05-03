# queens-code

SOURCES

software:
CMake (solution builder)
Microsoft Visual Studio 2017 (C++ code)
Microsoft Visulo Studio Code (QML code)
Blender (modeling)
GitHub (source control)

Resources:
https://texture.ninja/ (grass, wall)
http://spiralgraphics.biz (ice, wizard's balls)
http://game-icons.net/ (all ability icons)

KNOWN BUGS

BUG: during game -> game menu -> options -> fullscreen to windowed -> click in empty space -> jumps to main menu
REASON: Unknown
PRIORITY: 3/10 (Game-breaking but rare and avoidable)

BUG: compile solution in MSVC -> macro redefinitions
REASON: Multiple sources (GPUEngine and Microsoft) set the same OpenGL macros
PRIORITY: 1/10 (Mild annoyance)
