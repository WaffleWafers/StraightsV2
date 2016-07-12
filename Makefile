EXEC = straights
CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -MMD -O -g `pkg-config gtkmm-2.4 --cflags`
LIBFLAG = `pkg-config gtkmm-2.4 --libs`
OBJECTS = Subject.o Model.o Controller.o DeckGUI.o View.o Straights.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${LIBFLAG}

clean:
	rm -rf ${OBJECTS} ${EXEC} ${DEPENDS}

zip:
	zip straights.zip *.h *.cpp Makefile

#DeckGUI.o: DeckGUI.h DeckGUI.cc
#Model.o: Subject.h Model.h Model.cc
#Subject.o: Subject.h Subject.cc
#Controller.o: Controller.h Model.h Controller.cc
#View.o: View.h Observer.h Controller.h Model.h Subject.h DeckGUI.h View.cc
#Straights.o: View.h Controller.h Model.h Straights.cc

-include ${DEPENDS} 