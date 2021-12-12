em++ -c lib/CPP/constants.cpp
em++ -c lib/CPP/functions.cpp
em++ -c lib/CPP/classes.cpp
em++ -c lib/CPP/canvas.cpp
em++  --bind constants.o canvas.o functions.o classes.o -o public/CPP/canvas.js
rm *.o