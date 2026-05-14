CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -g
LDFLAGS = -static
TARGET = lab2.exe
SRCS = src/main.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(wildcard include/*.hpp) $(wildcard src/*.tpp)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

src/%.o: src/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)