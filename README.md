# graphics-coursework-yr2
This is my project for Computer Graphics. In my solution I have made a scene that is based upon Minecraft with a human character that runs around being chased by a bee. Both the Human and Bee are complex objects. You may find hand-drawn documentation of the Bee as images in the root directory of the project.

Some main features of my coursework project include animated textures, plain text files to load levels and basic interaction.

Embarking on this project I decided that an opportunity was presented for me to transition from old C++ to modern C++. Therefore, all the code written by myself in the project is in C++. There are some dependencies in the form of __libraries__ in the project, these include: OpenGL, GLFW, SOIL and winmm (if on windows). For the project to compile successfully you may need to compile and link these libraries yourself, unless using Visual Studio, in which case the project file should be sufficient.

NB: Just as in the Java lab this project runs with OpenGL 1.1 as the context target and utilises functions from that version specifically.

## Documentation
All classes have thorough documentation in their header files with minimal comments in the actual implementation. You can find the scene graph in basic_scene.h in the comment block on the class itself.

## Controls
| Action  | Description                                                |
|---------|------------------------------------------------------------|
| Hold N  | Player swats at bee (and bee moves away)                   |
| Press M | Player will enter idling mode and will stop following path |
| Press X | Switch to axis perspective along X-Axis                    |
| Press Y | Switch to axis perspective along Y-Axis                    |
| Press Z | Switch to axis perspective along Z-Axis                    |

## Footnote
Please make sure to compile and run the program in 32-bit if compiling from Visual Studio project files as the project is not setup for 64-bit.

## Attribution References
Any resources found and used in the project from 3rd parties can be found in attributions_texture.txt and attributions_misc.txt
