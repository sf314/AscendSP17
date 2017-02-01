# AscendSP17
Code for ASCEND, Spring 2017

*** EXPLANATION OF FOLDERS *** 

ascendMain
- folder containing flight code for main arduino.
- subsequent arduinos shall have their code in ascendMain2, etc

SparkFun...-master
- Library and examples for SparkFun 6DOF IMU

*** HOW TO USE *** 
All code for use in flight must exist in the
same directory as the .ino file where it is 
going to be used. Thus, your #include state-
ments will use "" instead of <>. This will 
encapsulate all flight code for an Arduino
into a single folder rather than referencing 
files in ../libraries/, which may not be the
same for every person. 

When creating a library, create a folder in
the main directory, something like 
../testReadThing and create your .ino file
 and test files there. Note that your .ino 
file must have the same name as the enclosing 
folder. Once your library is complete, you can
copy those files over to /ascendMain for 
integration with the flight code.

If downloading a library from the internet, 
be sure to include that download in your test
folder for reference. This will keep things
neat and organized. See testIMU for example 
of all of this.


