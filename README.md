![nope](https://github.com/survivalizeed/Hgine/blob/master/Res/HgineSplashGithub.png?raw=true)
# Hgine
Just an Engine that uses the gdiplus.h to display an array of pixels.  
The average FPS are around 65 with 30 sprites. I know it is not the fastest Engine out there but it is really hardcoded and enough for some cool 2D games (probably 3D too).
Make sure you are using C++ 20. For the best results compile it in x64 release, MSVC and -O2 optimization level!  I am trying to re-create some algorithms from the graphics card and calling it Hgine:)  

#### If you want to change something or just found a bug please send me a pullrequest or contact me via discord.

## Note:  
Im 15 years old and still learning C++ so please understand if this is not the best code you have ever seen ;)  
The Engine is still under development and I am only one developer.  
Please don't wonder if I don't commit weekly.
Most of the time Im collecting new code to then publish it.  
Discord: survivalizeed#7659  
Server: https://discord.gg/ymVn8ZsbeT


## Make it work
To make the Engine work you just need to download the source folder and import it into a visual studio project.  
After you have done that go into the SurLua.h and change the #pragma comment paths to the destination where your .a files are placed.  
##### Be aware of x64 and x86.  
Now go into the Audio.h and do the same with the bass.lib.  
##### Again be aware of x64 and x86
Next make sure that all x64 build folders (debug/release) include the lua54.dll and the bass.dll.  
Pick the ones from the Extern folder in the source folder. Make sure you picked the x64 dlls.  
  
Then do the same with the x86 build folders (debug/release) include the lua54.dll and bass.dll.
Pick the ones from the Extern folder in the source folder. Make sure you picked the x86 dlls.  

Now open the initialize.cpp and change the lua::LoadFile("To the path where the config.lua file is located at")  

Next download the Hgine resource generator.exe to be able to create some Hgineres files.

