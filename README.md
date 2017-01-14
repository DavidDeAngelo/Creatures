# Creatures
Make sure you have Visual Studio

download bullet 2.85

unzip

go to build3 folder

in command prompt use premake to generate visual studio project files

use command premake4 --targetdir="../bin" vs2010

go to bullet3-2.85.1\build3\vs2010

open up 0_Bullet3Solution.sln

make sure Solution is set to 64x if you want to run it as a 64 bit application  

build Solution

download Creatures zip

place in Folder with bullet directory(if you don't rename it from the zip file, just the folder bullet3-2.85.1)
open up Creatures.vcxproj

make sure project is set to 64x (or whatever you build bullet in)

run local windows debugger to test if everything was set up correctly

???

profit

Idea:Maintain internal genetic historical markers not only for species, but for each node (and each nested node) of a creature
Cross similar parts with each other.
Could be important for nested neural network structure

div 2080

format-number(number(Employment_Traversal/Employment/Assignments_Traversal/Assignments/Assignment_Record/Assignment_Salary_Annual_Amount) div number($Pay_Period_Count),'#######.00')