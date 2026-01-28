CXX := g++
CXXFLAGS := -Iinclude -std=c++17 -Wall
LDFLAGS := -Llib -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -lsfml-audio

SRCS := $(wildcard src/*.cpp)
OBJS := $(patsubst src/%.cpp, obj/%.o, $(SRCS))

.PHONY: all clean

all: main

# rule to make obj directory if needed
obj:
	mkdir -p obj

# compile each source into obj/*.o
obj/%.o: src/%.cpp | obj
	$(CXX)	$(CXXFLAGS) -c $< -o $@

# link
main: $(OBJS)
	$(CXX)	$(OBJS) -o $@	$(LDFLAGS)

clean:
	if exist obj rmdir /s /q obj
	if exist main.exe del /q main.exe
	if exist main del /q main
	del /q *.o 2>nul