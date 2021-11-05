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

## Creating a new project in Visual Studio (New)
#### 1. Create an empty project in Visual Studio
#### 2. Download the new source with the download button above
#### 3. In the Visual Studio files explorer click "show all files"
#### 4. (Recommended) Create a "Source" folder for yourself in the Visual Studio files explorer
#### 5. Right-Click your project and click "open in file explorer"
#### 6. Now you should see your "Source" folder from 4. with some Visual Studio files. Copy the "Hgine" folder next to the Source folder. Make sure you don't copy the main.cpp file
#### 7. Go back to Visual Studio and click the refresh button in the files explorer. Now you should see the "Hgine" folder
#### 8. Right-Click the Hgine folder and click "add to project"
#### 9. Now press the build button. You should get a lot of errors.
#### 10. Go to Properties. Make sure plattforms and configurations are set to: "All". -> C/C++ -> Language -> C++20
#### 11. (Optional) Go to Properties. Make sure plattforms are set to: "All" and configurations are set to: "Release". -> C/C++ -> Codegeneration: RuntimeLibrary = /MT
#### 12. (Recommended) Go to Properties. Make sure plattforms are set to: "All" and configurations are set to: "Release". -> C/C++ -> Optimization: Optimization = /O2 Inline functions = /Ob2 Intrinsic functions = /Oi Preferred = /Ot | C/C++ -> Codegeneration -> floating point = /fp:fast
#### 13. Press the build button again and it should compile with some linker errors
#### 14. Go to Hgine -> C++ -> Classes -> Audio -> Audio.h and change the #pragma comment stuff to the correct path where the lib is located at
#### 15. Go to Hgine -> C++ -> Classes -> LuaScript -> LuaScrip.h and chage the #pragma comment stuff to the correct path where the lib is located at
#### 16. Go and copy the x86 bass.dll into your release and debug folder. Go anc copy the x64 bass.dll into your x64/release and x64/debug folder. Simply where your exe is at.
### Done

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



