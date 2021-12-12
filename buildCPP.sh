em++ -c lib/CPP/globals.cpp
em++ -c lib/CPP/functions.cpp
em++ -c lib/CPP/classes.cpp
em++ -c lib/CPP/export.cpp
em++  --bind globals.o export.o functions.o classes.o -o public/CPP/canvas.js
rm *.o