all:
	mkdir -p Build
	g++  -c  src/crossexport.cpp -std=c++11 -O3 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) -DNDEBUG -o ./Build/crossexport.cpp.o -I. -Isrc -IwxCrossGen/fbgui -IwxCrossGen
	g++  -c  src/crossgen.cpp -std=c++11 -O3 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) -DNDEBUG -o ./Build/crossgen.cpp.o -I. -Isrc -IwxCrossGen/fbgui -IwxCrossGen
	g++  -c  wxCrossGen/fmain.cpp -std=c++11 -O3 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) -DNDEBUG -o ./Build/fmain.cpp.o -I. -Isrc -IwxCrossGen/fbgui -IwxCrossGen
	g++  -c  wxCrossGen/fsettings.cpp -std=c++11 -O3 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) -DNDEBUG -o ./Build/fsettings.cpp.o -I. -Isrc -IwxCrossGen/fbgui -IwxCrossGen
	g++  -c  wxCrossGen/fsettings.cpp -std=c++11 -O3 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) -DNDEBUG -o ./Build/fsettings.cpp.o -I. -Isrc -IwxCrossGen/fbgui -IwxCrossGen
	g++  -c  wxCrossGen/main.cpp -std=c++11 -O3 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) -DNDEBUG -o ./Build/main.cpp.o -I. -Isrc -IwxCrossGen/fbgui -IwxCrossGen
	g++  -c  wxCrossGen/fbgui/fbgui.cpp -std=c++11 -O3 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) -DNDEBUG -o ./Build/fbgui.cpp.cpp.o -I. -Isrc -IwxCrossGen/fbgui -IwxCrossGen
	g++ -o ./Build/CrossGen ./Build/crossexport.cpp.o ./Build/crossgen.cpp.o ./Build/fbgui.cpp.cpp.o ./Build/fmain.cpp.o ./Build/fsettings.cpp.o ./Build/main.cpp.o -L. $(shell wx-config --debug=no  --unicode=yes --libs all)