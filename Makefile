CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -fPIC

QT_PATH = C:/Qt/6.11.1/mingw_64

QT_INCLUDES = -I$(QT_PATH)/include/QtCore \
              -I$(QT_PATH)/include/QtGui \
              -I$(QT_PATH)/include/QtWidgets \
              -I$(QT_PATH)/include

QT_LIBS = -L$(QT_PATH)/lib \
          -lQt6Core \
          -lQt6Gui \
          -lQt6Widgets

WIN_OPTIONS = -DUNICODE -DWIN32 -DWIN64

UI_DIR = ui
INCLUDE_DIR = include
TESTS_DIR = tests

OBJECTS = $(UI_DIR)/main.o $(UI_DIR)/mainwindow.o $(UI_DIR)/moc_mainwindow.o bitSequence.o

TARGET = laba2_2.exe

CXXFLAGS_ALL = $(CXXFLAGS) $(QT_INCLUDES) $(WIN_OPTIONS)

all: $(TARGET)

bitSequence.o: bitSequence.cpp $(INCLUDE_DIR)/bitSequence.hpp
	$(CXX) $(CXXFLAGS_ALL) -c bitSequence.cpp -o bitSequence.o

$(UI_DIR)/moc_mainwindow.cpp: $(UI_DIR)/mainwindow.h
	$(QT_PATH)/bin/moc.exe $< -o $@

$(UI_DIR)/main.o: $(UI_DIR)/main.cpp $(UI_DIR)/mainwindow.h
	$(CXX) $(CXXFLAGS_ALL) -c $< -o $@

$(UI_DIR)/mainwindow.o: $(UI_DIR)/mainwindow.cpp $(UI_DIR)/mainwindow.h $(UI_DIR)/moc_mainwindow.cpp
	$(CXX) $(CXXFLAGS_ALL) -c $< -o $@

$(UI_DIR)/moc_mainwindow.o: $(UI_DIR)/moc_mainwindow.cpp
	$(CXX) $(CXXFLAGS_ALL) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(QT_LIBS) -static-libgcc -static-libstdc++

test:
	$(CXX) $(CXXFLAGS) -Iinclude $(TESTS_DIR)/test_dynamic_array.cpp -o $(TESTS_DIR)/test_dynamic_array.exe
	$(CXX) $(CXXFLAGS) -Iinclude $(TESTS_DIR)/test_linked_list.cpp -o $(TESTS_DIR)/test_linked_list.exe
	$(CXX) $(CXXFLAGS) -Iinclude $(TESTS_DIR)/test_bit_sequence.cpp bitSequence.o -o $(TESTS_DIR)/test_bit_sequence.exe
	$(CXX) $(CXXFLAGS) -Iinclude $(TESTS_DIR)/test_sequences.cpp -o $(TESTS_DIR)/test_sequences.exe
	$(TESTS_DIR)/test_dynamic_array.exe
	$(TESTS_DIR)/test_linked_list.exe
	$(TESTS_DIR)/test_bit_sequence.exe
	$(TESTS_DIR)/test_sequences.exe

clean:
	if exist $(UI_DIR)\\*.o del /f $(UI_DIR)\\*.o
	if exist $(UI_DIR)\\moc_*.cpp del /f $(UI_DIR)\\moc_*.cpp
	if exist bitSequence.o del /f bitSequence.o
	if exist $(TARGET) del /f $(TARGET)
	if exist $(TESTS_DIR)\\*.exe del /f $(TESTS_DIR)\\*.exe

run: $(TARGET)
	$(TARGET)

.PHONY: all clean run test