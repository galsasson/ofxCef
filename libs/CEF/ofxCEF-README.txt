###########################################################
# WINDOWS
###########################################################

Tested with openframeworks version 0.9.3 and CEF version 11/19/2016 - CEF 3.2840.1518.gffd843c / Chromium 54.0.2840.99 (downloaded from http://opensource.spotify.com/cefbuilds/index.html)

If you want to compile for both 32 and 64 bit you have to download both CEF Windows builds!



Move the contents of the 32bit version of CEF to ofxCef\libs\CEF\win32 and the content of the 64bit version to ofxCef\libs\CEF\win64
Build the CEF Visual Studio Projects AFTER copying CEF to the addon (some generated paths are absolute and not relative to the project location)
Note if you are using CMake to perform a Windows build of CEF and are following the instructions in CEF's CMakeLists.txt you have to exclude the sandbox if you are using Visual Studio 2015 Update 3 with the argument -DUSE_SANDBOX=Off like so (else you will get build errors, though this might be fixed in newer versions of CEF):
cmake -DUSE_SANDBOX=Off -G "Visual Studio 14" ..
cmake -DUSE_SANDBOX=Off -G "Visual Studio 14 Win64" ..



It will be easiest to work off of the provided example solution.
If you want add ofxCEF to your existing project, the following steps have to be done:

Add libcef_dll_wrapper.vcxproj and the ZERO_CHECK.vcxproj to your existing Visaul Studio solution.
If you want to setup both 32bit and 64bit support for your project, you have to add both versions to your solution. This can be a bit tricky, because Visual Studio only accepts one project of the same name. You can however add the projects to different solution folders. It might be easier to add the projects by editing the sln file in a text editor. If in doubt check the example_ofxCef solution.

Add additional include directories
Go to your project's Configuration Properties/C/C++/General/Additional Include Directories, add:
..\..\..\addons\ofxCef\libs\CEF\win32\include
..\..\..\addons\ofxCef\libs\CEF\win32
..\..\..\addons\ofxCef\src

Add library directories
Go to your project's Configuration Properties/Linker/General/Additional Library Directories, add:
..\..\..\addons\ofxCef\libs\CEF\win32\$(Configuration)
(for 64bit configuration replace win32 with win64)

Link against libcef.lib and libcef_dll_wrapper.lib
Go to your project's Configuration Properties/Linker/Input/Additional Dependencies, add:
..\..\..\addons\ofxCef\libs\CEF\win32\build\libcef_dll_wrapper\$(Configuration)\libcef_dll_wrapper.lib
..\..\..\addons\ofxCef\libs\CEF\win32\$(Configuration)\libcef.lib
(for 64bit configuration replace win32 with win64)

Add a post build event to copy the relevant dll, bin and pak files to the executable
Go to your project's Configuration Properties/Build Events/Post-Build Event/Command Line, replace the openframeworks stuff with:
echo on
        dir
        robocopy "$(ProjectDir)../../../addons/ofxCef/libs/CEF/win32/$(Configuration)/" "$(ProjectDir)bin/" "*.dll" "*.bin" /njs /njh /np /fp /bytes
        robocopy "$(ProjectDir)../../../addons/ofxCef/libs/CEF/win32/Resources/" "$(ProjectDir)bin/" "*.pak" /njs /njh /np /fp /bytes
        robocopy "$(OF_ROOT)/export/vs/$(Platform_Actual)/" "$(ProjectDir)bin/" "*.dll" /njs /njh /np /fp /bytes
if errorlevel 1 exit 0 else exit %errorlevel%

(for 64bit configuration replace win32 with win64)
If you want to skip this step you can also just copy the relevant files yourself to the executable. Your project should build independently of this step, you might just get an error when the application starts running (because of missing files).

Ensure libcef_dll_wrapper is a dependency of your own project (Project Name > Project Dependencies).
Ensure libcef_dll_wrapper is referenced by your project (Project Name > References > Add New Reference).
You may have to change the Runtime Library of the libcef_dll_wrapper.vcxproj to Multi-threaded DLL (Configuration Properties/C/C++/Code Generation/Runtime Library).


###########################################################