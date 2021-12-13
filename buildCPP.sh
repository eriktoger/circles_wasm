em++ -c lib/CPP/constants.cpp
em++ -c lib/CPP/classes.cpp
em++ -c lib/CPP/globals.cpp
em++ -c lib/CPP/helpers.cpp
em++ -c lib/CPP/circleFunctions.cpp
em++ -c lib/CPP/export.cpp
em++  --bind constants.o helpers.o globals.o export.o circleFunctions.o classes.o -o public/CPP/canvas.js -s ALLOW_MEMORY_GROWTH=1 
rm *.o