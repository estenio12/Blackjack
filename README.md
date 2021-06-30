# Blackjack Cards Game

This project was developed to study and practice my game development skills;

Extra: Game executable for windows;

# Dependency

<h3> SFML 2 </h3>
Link main page: https://www.sfml-dev.org

Download Library: https://www.sfml-dev.org/download/sfml/2.5.1/

<h3> C++ Compiler </h3>
This project was compiler with G++. But you don't need to use the same.

GCC link: https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-posix/seh/x86_64-7.3.0-release-posix-seh-rt_v5-rev0.7z/download

<ul>
  <h4> Rules for compiler with G++: </h4>
  
  <li><h3> Linux Compiler: </h3> g++ *.cpp ./src/*.cpp -std==c++17 -o main -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system && ./main</li>
   <li>
    <h3> Windows Compiler with G++ </h3>
    <ul>
      <li><h5> Step 1: </h5> Download and install SFML Library: sudo apt-get install libsfml-dev</li>
      <li><h5> Step 2: </h5> Linux Compiler: </h3> g++ *.cpp ./src/*.cpp -std==c++17 -o main -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system</li>
      <li><h5> Step 3: </h5> Execute program: ./main</h2></li>
    </ul>
    </li>
  <li>
    <h3> Windows Compiler with G++ </h3>
    <ul>
      <li><h5> Step 1: </h5> Download SFML Library;</li>
      <li><h5> Step 2: </h5> inside DLL folder from SFML, Copy .DLL files and paste inside G++ .DLL folder.</li>
      <li><h5> Step 3: </h5> g++ *.cpp ./src/*.cpp -std==c++17 -o main -I \" Here past the path at sfml include folder\" -L \" Here past the path at sfml lib folder\" -D \"SFML_STATIC\" -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system</li>
      <li><h5> Step 4: </h5> Execute program: main.exe</h2></li>
    </ul>
    </li>
</ul>

<h3> Other ways to compiler </h3>
<ul>
  <li>Visual Studio 2019 link: https://visualstudio.microsoft.com/pt-br/downloads/</li>
  <li>Visual Studio Code link: https://code.visualstudio.com/download</li>
</ul>
