# chapter 0(env prepare):
关于环境，有很多选项，光是编译器就可以使用MinGW、MSVC、GNU等gcc编译器来编译(gnu和mingw编译不通过去看RAEDME的Q&A)，调试的话同理根据选择的编译器有不同的调试方式，MSVC就是vs ide来debug，我目前用的是mingw所以我打算使用gdb来进行debug，编译时注意一下流程：
```sh
yix@GWSHAPCCP35 MINGW64 ~/Desktop/Graphics/proj/OPG/build/mingw64 (main)
$ make debug
-- Using Win32 for window creation
Copying resources directory to build directory
-- Configuring done
-- Generating done
-- Build files have been written to: C:/Users/yix/Desktop/Graphics/proj/OPG/build/mingw64
-- Using Win32 for window creation
Copying resources directory to build directory
-- Configuring done
-- Generating done
-- Build files have been written to: C:/Users/yix/Desktop/Graphics/proj/OPG/build/mingw64
Built target debug
yix@GWSHAPCCP35 MINGW64 ~/Desktop/Graphics/proj/OPG/build/mingw64 (main)
$ make
[  3%] Building C object external/glfw/src/CMakeFiles/glfw.dir/context.c.obj
[  7%] Building C object external/glfw/src/CMakeFiles/glfw.dir/init.c.obj
[ 10%] Building C object external/glfw/src/CMakeFiles/glfw.dir/input.c.obj
[ 14%] Building C object external/glfw/src/CMakeFiles/glfw.dir/monitor.c.obj
[ 17%] Building C object external/glfw/src/CMakeFiles/glfw.dir/vulkan.c.obj
[ 21%] Building C object external/glfw/src/CMakeFiles/glfw.dir/window.c.obj
[ 25%] Building C object external/glfw/src/CMakeFiles/glfw.dir/win32_init.c.obj
[ 28%] Building C object external/glfw/src/CMakeFiles/glfw.dir/win32_joystick.c.obj
[ 32%] Building C object external/glfw/src/CMakeFiles/glfw.dir/win32_monitor.c.obj
[ 35%] Building C object external/glfw/src/CMakeFiles/glfw.dir/win32_time.c.obj
[ 39%] Building C object external/glfw/src/CMakeFiles/glfw.dir/win32_thread.c.obj
[ 42%] Building C object external/glfw/src/CMakeFiles/glfw.dir/win32_window.c.obj
[ 46%] Building C object external/glfw/src/CMakeFiles/glfw.dir/wgl_context.c.obj
[ 50%] Building C object external/glfw/src/CMakeFiles/glfw.dir/egl_context.c.obj
[ 53%] Building C object external/glfw/src/CMakeFiles/glfw.dir/osmesa_context.c.obj
[ 57%] Linking C static library ..\..\..\lib\libglfw3_d.a
[ 57%] Built target glfw
Scanning dependencies of target vermilion
[ 60%] Building C object CMakeFiles/vermilion.dir/vermilion/lib/gl3w.c.obj
[ 64%] Building CXX object CMakeFiles/vermilion.dir/vermilion/lib/LoadShaders.cpp.obj
[ 67%] Building CXX object CMakeFiles/vermilion.dir/vermilion/lib/targa.cpp.obj
[ 71%] Building CXX object CMakeFiles/vermilion.dir/vermilion/lib/vdds.cpp.obj
[ 75%] Building CXX object CMakeFiles/vermilion.dir/vermilion/lib/loadtexture.cpp.obj
[ 78%] Building CXX object CMakeFiles/vermilion.dir/vermilion/lib/vermilion.cpp.obj
[ 82%] Building CXX object CMakeFiles/vermilion.dir/vermilion/lib/vbm.cpp.obj
[ 85%] Linking CXX static library lib\libvermilion_d.a
[ 85%] Built target vermilion
[ 89%] Building CXX object CMakeFiles/1-1-triangles.dir/src/1-1-triangles/1-1-triangles.cpp.obj
[ 92%] Linking CXX executable bin\1-1-triangles_d.exe
[ 92%] Built target 1-1-triangles
Scanning dependencies of target 1-1-keypress
[ 96%] Building CXX object CMakeFiles/1-1-keypress.dir/src/1-1-keypress/1-1-keypress.cpp.obj
[100%] Linking CXX executable bin\1-1-keypress_d.exe
[100%] Built target 1-1-keypress
```
然后理论上你的bin目录应该是这样的：

```txt
bin
    |-/media
    |1-1-keypress_d.exe
    |...
```
"_d"说明生成的程序集是以"-g"编译选项编译得到的，所以接着可以调用gdb(用mingw内部自带的那个就行了)进行古法调参：
```sh
yix@GWSHAPCCP35 MINGW64 ~/Desktop/Graphics/proj/OPG/build/mingw64 (main)
$ gdb ./bin/1-1-triangles_d
GNU gdb (GDB) 11.2
Copyright (C) 2022 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-w64-mingw32".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./bin/1-1-triangles_d...
(gdb) b main
Breakpoint 1 at 0x1400016e5: file C:\Users\yix\Desktop\Graphics\proj\OPG\src\1-1-triangles\1-1-triangles.cpp, line 90.
(gdb) r
Starting program: C:\Users\yix\Desktop\Graphics\proj\OPG\build\mingw64\bin\1-1-triangles_d.exe 
[New Thread 36520.0x8dbc]
[New Thread 36520.0x7208]
[New Thread 36520.0x525c]

Thread 1 hit Breakpoint 1, main (argc=1, argv=0x1a673ee5f60) at C:\Users\yix\Desktop\Graphics\proj\OPG\src\1-1-triangles\1-1-triangles.cpp:90
90          glfwInit();
(gdb)
```

试着在vscode里配置一下gdb在vscode中debug...