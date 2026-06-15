CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -fPIC
QT_PATH = C:/Qt/6.11.1/mingw_64
QT_INCLUDES = -I$(QT_PATH)/include/QtCore -I$(QT_PATH)/include/QtGui -I$(QT_PATH)/include/QtWidgets -I$(QT_PATH)/include
QT_LIBS = -L$(QT_PATH)/lib -lQt6Core -lQt6Gui -lQt6Widgets
WIN_OPTIONS = -DUNICODE -DWIN32 -DWIN64

UI_DIR = ui
INCLUDE_DIR = include

OBJECTS = $(UI_DIR)/main.o $(UI_DIR)/mainwindow.o $(UI_DIR)/arraysequencetab.o $(UI_DIR)/listsequencetab.o \
          $(UI_DIR)/bitsequencetab.o $(UI_DIR)/linkedlisttab.o $(UI_DIR)/moc_mainwindow.o bitSequence.o
TARGET = laba2_2.exe

CXXFLAGS_ALL = $(CXXFLAGS) $(QT_INCLUDES) $(WIN_OPTIONS)

all: $(TARGET)

bitSequence.o: bitSequence.cpp $(INCLUDE_DIR)/bitSequence.hpp
	$(CXX) $(CXXFLAGS) -Iinclude -c $< -o $@

$(UI_DIR)/moc_mainwindow.cpp: $(UI_DIR)/mainwindow.hpp
	$(QT_PATH)/bin/moc.exe $< -o $@

$(UI_DIR)/main.o: $(UI_DIR)/main.cpp $(UI_DIR)/mainwindow.hpp
	$(CXX) $(CXXFLAGS_ALL) -c $< -o $@

$(UI_DIR)/mainwindow.o: $(UI_DIR)/mainwindow.cpp $(UI_DIR)/mainwindow.hpp $(UI_DIR)/moc_mainwindow.cpp
	$(CXX) $(CXXFLAGS_ALL) -c $< -o $@

$(UI_DIR)/arraysequencetab.o: $(UI_DIR)/arraysequencetab.cpp $(UI_DIR)/mainwindow.hpp
	$(CXX) $(CXXFLAGS_ALL) -c $< -o $@

$(UI_DIR)/listsequencetab.o: $(UI_DIR)/listsequencetab.cpp $(UI_DIR)/mainwindow.hpp
	$(CXX) $(CXXFLAGS_ALL) -c $< -o $@

$(UI_DIR)/bitsequencetab.o: $(UI_DIR)/bitsequencetab.cpp $(UI_DIR)/mainwindow.hpp
	$(CXX) $(CXXFLAGS_ALL) -c $< -o $@

$(UI_DIR)/linkedlisttab.o: $(UI_DIR)/linkedlisttab.cpp $(UI_DIR)/mainwindow.hpp
	$(CXX) $(CXXFLAGS_ALL) -c $< -o $@

$(UI_DIR)/moc_mainwindow.o: $(UI_DIR)/moc_mainwindow.cpp
	$(CXX) $(CXXFLAGS) $(QT_INCLUDES) $(WIN_OPTIONS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(QT_LIBS) -static-libgcc -static-libstdc++


test: bitSequence.o
	$(CXX) $(CXXFLAGS) -Iinclude -static-libgcc -static-libstdc++ tests/test_dynamic_array.cpp -o tests/test_dynamic_array.exe
	$(CXX) $(CXXFLAGS) -Iinclude -static-libgcc -static-libstdc++ tests/test_linked_list.cpp -o tests/test_linked_list.exe
	$(CXX) $(CXXFLAGS) -Iinclude -static-libgcc -static-libstdc++ tests/test_bit_sequence.cpp bitSequence.o -o tests/test_bit_sequence.exe
	$(CXX) $(CXXFLAGS) -Iinclude -static-libgcc -static-libstdc++ tests/test_sequences.cpp -o tests/test_sequences.exe
	cd tests && test_dynamic_array.exe
	cd tests && test_linked_list.exe
	cd tests && test_bit_sequence.exe
	cd tests && test_sequences.exe

clean:
	del /f /q $(UI_DIR)\\*.o 2>nul
	del /f /q $(UI_DIR)\\moc_*.cpp 2>nul
	del /f /q bitSequence.o 2>nul
	del /f /q $(TARGET) 2>nul

run: $(TARGET)
	$(TARGET)

.PHONY: all clean run