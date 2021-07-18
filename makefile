OBJS = main.o steam_library.o log.o
CXX = g++
CPPFLAGS = -g -c -Wall -std=c++20
LDFLAGS = -g -Wall -std=c++20
EXE = main

$(EXE): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(EXE)

log.o: log.h log.cpp
	$(CXX) $(CPPFLAGS) log.cpp

steam_library.o: steam_library.h steam_library.cpp library.h log.h
	$(CXX) $(CPPFLAGS) steam_library.cpp

main.o: main.cpp steam_library.h log.h
	$(CXX) $(CPPFLAGS) main.cpp

clean:
	rm *.o $(EXE) -v
