#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QTabWidget>
#include <QTableWidget>
#include <QSpinBox>
#include <QCheckBox>
#include <QMessageBox>

#include "../include/arraySequence.hpp"
#include "../include/listSequence.hpp"
#include "../include/bitSequence.hpp"
#include "../include/linkedList.hpp"
#include "../include/dynamicArray.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void runArraySequenceDemo();
    void runListSequenceDemo();
    void runBitSequenceDemo();
    void clearOutput();

private:
    // Текущие экземпляры для демонстрации
    ArraySequence<int>* currentArraySeq;
    ListSequence<int>* currentListSeq;
    BitSequence* currentBitSeq;
    DynamicArray<int>* currentDynamicArray;
    LinkedList<int>* currentLinkedList;
    
    QTextEdit* outputTextEdit;
    
    // QTextEdit для отображения
    QTextEdit* arrayDisplay;
    QTextEdit* listDisplay;
    QTextEdit* bitDisplay;
    QTextEdit* dynamicDisplay;
    QTextEdit* linkedDisplay;
    
    void updateOutput(const QString& text);
    void displayArraySequence();
    void displayListSequence();
    void displayBitSequence();
    void displayDynamicArray();
    void displayLinkedList();
    void setupUI();
    
    // Методы для создания вкладок
    QWidget* createArraySequenceTab();
    QWidget* createListSequenceTab();
    QWidget* createBitSequenceTab();
    QWidget* createDynamicArrayTab();
    QWidget* createLinkedListTab();
};

#endif // MAINWINDOW_H