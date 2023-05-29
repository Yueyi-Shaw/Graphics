Write this lab according to OpenGL Programming Guide, you can find the book in OPG/book. I also add the offcial source code as a submodule to this repo.

Q:How to build it?
A:In the root path, run :
$mkdir build
$cd build
$cmake -G <your compiler> ..

Q1:How about opengl lib?
A:My display card is RTX3060 and my driver verison is 531.79, which support opengl 4.6, you can check this info by using GPU-Z in the /Tools path.

Q2:Why the directory structure got a big difference with the official example?
A:I don't understand why the OpenGL Red Book's example project provided on GitHub was designed in that way, so I made some adjustments. However, some weird questions still exist, such as why not simply make the whole Vermilion project into a library.
(Actually, well, the vermilion/LoadShaders.cpp and vermilion/vdds.cpp didn't take part in the compilation process of cmake, you can directly remove them)

Q3:"LNK2019	unresolved external symbol WinMain referenced in function "int __cdecl invoke_main(void)" (?invoke_main@@YAHXZ)"
A:Check you application's "subsystem" is "CONSOLE" if you are using entry func "main()", there are different crt entry func for concole and windows application. You can get more infomation in Windows via C/Cpp.

Q4:compile failed on linux or mingw32.
A: https://github.com/openglredbook/examples/commit/1a3e0fa25aaff29befc79bc16634abe9e8034a40#diff-f9b9c4ac5561892dd6de1c285d20ad4063b0a2474fda52bbd27244355240cf4e

Q5:Some examples are totally different from official ones or unmentioned in offical repo, why?
A: I don't want to "copy", but to follow the book(OPG) and to turn my own ideas to code with APIs introduced in OPG, maybe I would read the official code and try to analyze its architecture, but that doesn't mean I will coding in the same way.