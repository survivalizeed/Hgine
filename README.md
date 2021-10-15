![nope](https://github.com/survivalizeed/Hgine/blob/master/Res/HgineSplashGithub.png?raw=true)
# Hgine
### Download:  
#### New: 
<a href="https://minhaskamal.github.io/DownGit/#/home?url=https://github.com/survivalizeed/Hgine/tree/master/New%20Source">Here</a> 
#### Old: 
<a href="https://minhaskamal.github.io/DownGit/#/home?url=https://github.com/survivalizeed/Hgine/tree/master/Source">Here</a> 
## About:

Just an Engine which uses the gdiplus.h to display an array of pixels.  
It is not the fastest Engine out there but it is really hardcoded and enough for some cool 2D games and some retro 3D games aswell.
Make sure you are using C++ 20. For the best results compile it in x86/x64 release, MSVC and -O2 optimization level!  I am calling it Hgine:)  

#### If you want to change something or just found a bug please send me a pullrequest or contact me via discord.

## Note:   
The Engine is still under development and I am only one developer.  
Please don't wonder if I don't commit weekly.
Most of the time Im collecting new code to then publish it.  
Discord: survivalizeed#7659  
Server: https://discord.gg/ymVn8ZsbeT


## Make it work (Old)
To make the Engine work you just need to download the source folder and import it into a visual studio project.  
After you have done that go into the SurLua.h and change the #pragma comment paths to the destination where your .a files are placed.  
They are included in the Extern folder in the Source folder 
##### Be aware of x64 and x86.  
Now go into the Audio.h and do the same with the bass.lib.  
##### Again be aware of x64 and x86
Next make sure that all x64 build folders (debug/release) include the lua54.dll and the bass.dll.  
Pick the ones from the Extern folder in the Source folder. Make sure you picked the x64 dlls.  
  
Then do the same with the x86 build folders (debug/release) include the lua54.dll and bass.dll.
Pick the ones from the Extern folder in the Source folder. Make sure you picked the x86 dlls.  

Now open the initialize.cpp and change the lua::LoadFile("To the path where the config.lua file is located at")  

Next download the Hgine resource generator.exe to be able to create some Hgineres files.  

### The final build
If you want to do the final build make sure you changed all lua::LoadFile() calls to 
##### lua::LoadFile(sur::GetExeDirectory() + "xyz.lua")  
so the application will search in the exe's directory.  
Now copy your config.lua into the release folder where your exe will be generated.  
#### This process applies to every other .lua file you will use in your project.



