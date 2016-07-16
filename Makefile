EXEC = straights
CXX = g++
CXXFLAGS = -std=c++11 -g -Wall -MMD -O -g `pkg-config gtkmm-2.4 --cflags`
LIBFLAG = `pkg-config gtkmm-2.4 --libs`
OBJECTS = Subject.o Card.o Model.o Controller.o DeckGUI.o View.o PlayerFrame.o CardButton.o NewGameDialog.o RoundEndDialog.o Straights.o Player.o ComputerPlayer.o HumanPlayer.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${LIBFLAG}

clean:
	rm -rf ${OBJECTS} ${EXEC} ${DEPENDS}

zip:
	zip straights.zip *.h *.cpp Makefile

-include ${DEPENDS} 
