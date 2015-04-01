Project 1.07

Dice.cpp is what stores the information for dice objects (speed, HP, and Damage), and Monster.cpp has the main function, which reads the definitions from the ~/.rlg229/monsterdefs.txt file.

I initially did this project in Visual Studio without any problems, but when I moved it to Pyrite, I found out GNU doesn't have a full implementation of regex, so I had to use boost.

Apparently, in a newer version of GCC, regex actually works.
