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
#include "../include/setTypes.hpp"

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
    
    SetSequence<int>* currentSetSeqInt;
    SetSequence<double>* currentSetSeqDouble;
    SetSequence<Complex>* currentSetSeqComplex;
    SetSequence<QString>* currentSetSeqString;
    SetSequence<FunctionWrapper<int>>* currentSetSeqFunction;
    SetSequence<Person>* currentSetSeqPerson;
    SetSequence<Pair<int, QString>>* currentSetSeqPair;

    QTextEdit* outputTextEdit;
    QTextEdit* arrayDisplay;
    QTextEdit* listDisplay;
    QTextEdit* bitDisplay;
    QTextEdit* linkedDisplay;
    
    QTextEdit* setDisplayInt;
    QTextEdit* setDisplayDouble;
    QTextEdit* setDisplayComplex;
    QTextEdit* setDisplayString;
    QTextEdit* setDisplayFunction;
    QTextEdit* setDisplayPerson;
    QTextEdit* setDisplayPair;

    void updateOutput(const QString& text);
    
    void displayArraySequence();
    void displayListSequence();
    void displayBitSequence();
    void displayLinkedList();
    
    void displaySetSequenceInt();
    void displaySetSequenceDouble();
    void displaySetSequenceComplex();
    void displaySetSequenceString();
    void displaySetSequenceFunction();
    void displaySetSequencePerson();
    void displaySetSequencePair();
    
    void setupUI();
    
    QWidget* createArraySequenceTab();
    QWidget* createListSequenceTab();
    QWidget* createBitSequenceTab();
    QWidget* createLinkedListTab();
    
    QWidget* createSetSequenceIntTab();
    QWidget* createSetSequenceDoubleTab();
    QWidget* createSetSequenceComplexTab();
    QWidget* createSetSequenceStringTab();
    QWidget* createSetSequenceFunctionTab();
    QWidget* createSetSequencePersonTab();
    QWidget* createSetSequencePairTab();
};

#endif