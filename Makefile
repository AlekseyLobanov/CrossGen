all:
	mkdir -p Build
	g++-4.8  -c  src/crossexport.cpp -std=c++11 -O3 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) -DNDEBUG -o ./Build/crossexport.cpp.o -I. -Isrc -IwxCrossGen/fbgui -IwxCrossGen
	g++-4.8  -c  src/crossgen.cpp -std=c++11 -O3 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) -DNDEBUG -o ./Build/crossgen.cpp.o -I. -Isrc -IwxCrossGen/fbgui -IwxCrossGen
	g++-4.8  -c  wxCrossGen/fmain.cpp -std=c++11 -O3 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) -DNDEBUG -o ./Build/fmain.cpp.o -I. -Isrc -IwxCrossGen/fbgui -IwxCrossGen
	g++-4.8  -c  wxCrossGen/fsettings.cpp -std=c++11 -O3 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) -DNDEBUG -o ./Build/fsettings.cpp.o -I. -Isrc -IwxCrossGen/fbgui -IwxCrossGen
	g++-4.8  -c  wxCrossGen/fsettings.cpp -std=c++11 -O3 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) -DNDEBUG -o ./Build/fsettings.cpp.o -I. -Isrc -IwxCrossGen/fbgui -IwxCrossGen
	g++-4.8  -c  wxCrossGen/main.cpp -std=c++11 -O3 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) -DNDEBUG -o ./Build/main.cpp.o -I. -Isrc -IwxCrossGen/fbgui -IwxCrossGen
	g++-4.8  -c  wxCrossGen/fbgui/fbgui.cpp -std=c++11 -O3 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=no) -DNDEBUG -o ./Build/fbgui.cpp.cpp.o -I. -Isrc -IwxCrossGen/fbgui -IwxCrossGen
	g++-4.8 -o ./Build/CrossGen ./Build/crossexport.cpp.o ./Build/crossgen.cpp.o ./Build/fbgui.cpp.cpp.o ./Build/fmain.cpp.o ./Build/fsettings.cpp.o ./Build/main.cpp.o -L. $(shell wx-config --debug=no  --unicode=yes --libs all)