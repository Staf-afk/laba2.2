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
#include "../include/setSequence.hpp"

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
    ArraySequence<int>* currentArraySeq;
    ListSequence<int>* currentListSeq;
    BitSequence* currentBitSeq;
    LinkedList<int>* currentLinkedList;
    SetSequence<int>* currentSetSeq;

    QTextEdit* outputTextEdit;
    QTextEdit* arrayDisplay;
    QTextEdit* listDisplay;
    QTextEdit* bitDisplay;
    QTextEdit* linkedDisplay;
    QTextEdit* setDisplay;

    void updateOutput(const QString& text);
    void displayArraySequence();
    void displayListSequence();
    void displayBitSequence();
    void displayLinkedList();
    void displaySetSequence();
    
    void setupUI();
    QWidget* createArraySequenceTab();
    QWidget* createListSequenceTab();
    QWidget* createBitSequenceTab();
    QWidget* createLinkedListTab();
    QWidget* createSetSequenceTab();
};

#endif 