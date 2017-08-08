# Building C++ Dynamic Linked Library (DLL) for Unity
A simple demonstration of using C++ library (DLL) in Unity. This repo describes how to build a C++ library in the form of dynamic linked library (DLL), encapsulate C++ classes and export functions. On the other hand, this repo also shows how to import and use the library (DLL) in Unity via c# script.

## How to Use Repo
This repo contains two folders:
1. SampleCppDll - A Visual Studio Community 2017 project and C++ files.

2. UnitySampleDll - An Unity project that make uses of the DLL built by SampleCppDll. Unity version 5.6.2f1 is used here.

### Quick Start
1. Use Visual Studio Community 2017 to open the SampleCppDll solution file `SampleCppDll/SampleCppDll.sln`

2. Use the menu `Build > Build Solution` to build (Remember to set the architecture x64 and it's assumed 64bits environment here)

3. Copy the output file `SampleCppDll.dll` under `SampleCppDll/x64/Debug/` to `UnitySampleDll/Assets/Plugins/` (If release build is used then it's under `SampleCppDll/x64/Release/`)

4. Use Unity 5.6+ to open folder `UnitySampleDll`

5. Open `UnitySampleDll/Assets/Scene/Main.unity`

6. Run it in the editor. Output from DLL will be printed in the Unity console tab.

7. More functions can be added to the C++ projects or even linking other library (Note that all linked dynamic linking library has to be copied to the `UnitySampleDll/Assets/Plugins` folder). Enjoy the boilerplate ~
