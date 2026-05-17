# Makefile для Windows с Qt 6.11.1
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -fPIC

# Путь к Qt
QT_PATH = C:/Qt/6.11.1/mingw_64

# Qt include пути
QT_INCLUDES = -I$(QT_PATH)/include/QtCore \
              -I$(QT_PATH)/include/QtGui \
              -I$(QT_PATH)/include/QtWidgets \
              -I$(QT_PATH)/include

# Qt библиотеки
QT_LIBS = -L$(QT_PATH)/lib \
          -lQt6Core \
          -lQt6Gui \
          -lQt6Widgets

# Опции для Windows
WIN_OPTIONS = -DUNICODE -DWIN32 -DWIN64

UI_DIR = ui
INCLUDE_DIR = include

# Исходные файлы
OBJECTS = $(UI_DIR)/main.o $(UI_DIR)/mainwindow.o $(UI_DIR)/moc_mainwindow.o bitSequence.o

TARGET = laba2_2.exe

CXXFLAGS_ALL = $(CXXFLAGS) $(QT_INCLUDES) $(WIN_OPTIONS)

all: $(TARGET)

# Генерация MOC файла
$(UI_DIR)/moc_mainwindow.cpp: $(UI_DIR)/mainwindow.h
	$(QT_PATH)/bin/moc.exe $< -o $@

# Компиляция bitSequence.cpp
bitSequence.o: bitSequence.cpp $(INCLUDE_DIR)/bitSequence.hpp
	$(CXX) $(CXXFLAGS_ALL) -c bitSequence.cpp -o bitSequence.o

# Компиляция main.cpp
$(UI_DIR)/main.o: $(UI_DIR)/main.cpp $(UI_DIR)/mainwindow.h
	$(CXX) $(CXXFLAGS_ALL) -c $< -o $@

# Компиляция mainwindow.cpp
$(UI_DIR)/mainwindow.o: $(UI_DIR)/mainwindow.cpp $(UI_DIR)/mainwindow.h $(UI_DIR)/moc_mainwindow.cpp
	$(CXX) $(CXXFLAGS_ALL) -c $< -o $@

# Компиляция MOC файла
$(UI_DIR)/moc_mainwindow.o: $(UI_DIR)/moc_mainwindow.cpp
	$(CXX) $(CXXFLAGS_ALL) -c $< -o $@

# Линковка
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(QT_LIBS) -static-libgcc -static-libstdc++

clean:
	del /f $(UI_DIR)\\*.o $(UI_DIR)\\moc_*.cpp bitSequence.o $(TARGET) 2>nul || rm -f $(UI_DIR)/*.o $(UI_DIR)/moc_*.cpp bitSequence.o $(TARGET)

run: $(TARGET)
	$(TARGET)

.PHONY: all clean run