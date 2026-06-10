#include "mainwindow.hpp"
#include <QDebug>
#include <QScrollBar>
#include <QPushButton>
#include <QLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QScreen>
#include <QRect>
#include <QGuiApplication>

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, currentArraySeq(nullptr)
, currentListSeq(nullptr)
, currentBitSeq(nullptr)
, currentLinkedList(nullptr)
, currentSetSeqInt(nullptr)
, currentSetSeqDouble(nullptr)
, currentSetSeqComplex(nullptr)
, currentSetSeqString(nullptr)
, currentSetSeqFunction(nullptr)
, currentSetSeqPerson(nullptr)
, currentSetSeqPair(nullptr)
, outputTextEdit(nullptr)
, arrayDisplay(nullptr)
, listDisplay(nullptr)
, bitDisplay(nullptr)
, linkedDisplay(nullptr)
, setDisplayInt(nullptr)
, setDisplayDouble(nullptr)
, setDisplayComplex(nullptr)
, setDisplayString(nullptr)
, setDisplayFunction(nullptr)
, setDisplayPerson(nullptr)
, setDisplayPair(nullptr)
{
    setupUI();
    
    currentArraySeq = new ArraySequence<int>();
    currentListSeq = new ListSequence<int>();
    currentBitSeq = new BitSequence(0);
    currentLinkedList = new LinkedList<int>();
    
    currentSetSeqInt = new SetSequence<int>();
    currentSetSeqDouble = new SetSequence<double>();
    currentSetSeqComplex = new SetSequence<Complex>();
    currentSetSeqString = new SetSequence<QString>();
    currentSetSeqFunction = new SetSequence<FunctionWrapper<int>>();
    currentSetSeqPerson = new SetSequence<Person>();
    currentSetSeqPair = new SetSequence<Pair<int, QString>>();
    
    displayArraySequence();
    displayListSequence();
    displayBitSequence();
    displayLinkedList();
    
    displaySetSequenceInt();
    displaySetSequenceDouble();
    displaySetSequenceComplex();
    displaySetSequenceString();
    displaySetSequenceFunction();
    displaySetSequencePerson();
    displaySetSequencePair();
    
    updateOutput("Приложение запущено. Используйте вкладки для работы со структурами данных.\n");
}

MainWindow::~MainWindow()
{
    delete currentArraySeq;
    delete currentListSeq;
    delete currentBitSeq;
    delete currentLinkedList;
    
    delete currentSetSeqInt;
    delete currentSetSeqDouble;
    delete currentSetSeqComplex;
    delete currentSetSeqString;
    delete currentSetSeqFunction;
    delete currentSetSeqPerson;
    delete currentSetSeqPair;
}

void MainWindow::setupUI()
{
    setWindowTitle("Лабораторная работа 2.2 - Структуры данных");
    setMinimumSize(1400, 800);
    
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    
    QTabWidget* operationsTabs = new QTabWidget();
    operationsTabs->setMinimumWidth(600);
    
    operationsTabs->addTab(createArraySequenceTab(), "ArraySequence");
    operationsTabs->addTab(createListSequenceTab(), "ListSequence");
    operationsTabs->addTab(createBitSequenceTab(), "BitSequence");
    operationsTabs->addTab(createLinkedListTab(), "LinkedList");
    
    operationsTabs->addTab(createSetSequenceIntTab(), "Set<int>");
    operationsTabs->addTab(createSetSequenceDoubleTab(), "Set<double>");
    operationsTabs->addTab(createSetSequenceComplexTab(), "Set<Complex>");
    operationsTabs->addTab(createSetSequenceStringTab(), "Set<QString>");
    operationsTabs->addTab(createSetSequenceFunctionTab(), "Set<Function>");
    operationsTabs->addTab(createSetSequencePersonTab(), "Set<Person>");
    operationsTabs->addTab(createSetSequencePairTab(), "Set<Pair>");
    
    mainLayout->addWidget(operationsTabs, 2);
    
    QWidget* rightPanel = new QWidget();
    QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);
    
    QGroupBox* outputGroup = new QGroupBox("Вывод");
    QVBoxLayout* outputLayout = new QVBoxLayout(outputGroup);
    outputTextEdit = new QTextEdit();
    outputTextEdit->setReadOnly(true);
    outputTextEdit->setFontFamily("Consolas");
    outputLayout->addWidget(outputTextEdit);
    rightLayout->addWidget(outputGroup);
    
    QPushButton* clearOutputBtn = new QPushButton("Очистить вывод");
    rightLayout->addWidget(clearOutputBtn);
    
    mainLayout->addWidget(rightPanel, 1);
    
    connect(clearOutputBtn, &QPushButton::clicked, this, &MainWindow::clearOutput);
}

void MainWindow::updateOutput(const QString& text)
{
    if (outputTextEdit) {
        outputTextEdit->append("> " + text);
        outputTextEdit->verticalScrollBar()->setValue(outputTextEdit->verticalScrollBar()->maximum());
    }
}

void MainWindow::clearOutput()
{
    if (outputTextEdit) outputTextEdit->clear();
}

void MainWindow::displayArraySequence() {
    if (arrayDisplay && currentArraySeq) {
        QString text = "[";
        for (size_t i = 0; i < currentArraySeq->GetLength(); i++) {
            text += QString::number(currentArraySeq->Get(i));
            if (i < currentArraySeq->GetLength() - 1) text += ", ";
        }
        text += "] (длина: " + QString::number(currentArraySeq->GetLength()) + ")";
        arrayDisplay->setText(text);
    }
}

void MainWindow::displayListSequence() {
    if (listDisplay && currentListSeq) {
        QString text = "[";
        for (size_t i = 0; i < currentListSeq->GetLength(); i++) {
            text += QString::number(currentListSeq->Get(i));
            if (i < currentListSeq->GetLength() - 1) text += ", ";
        }
        text += "] (длина: " + QString::number(currentListSeq->GetLength()) + ")";
        listDisplay->setText(text);
    }
}

void MainWindow::displayBitSequence() {
    if (bitDisplay && currentBitSeq) {
        QString text = "";
        for (size_t i = 0; i < currentBitSeq->GetLength(); i++) {
            text += QString::number(currentBitSeq->GetBit(i));
            if ((i + 1) % 8 == 0 && i < currentBitSeq->GetLength() - 1) text += " ";
        }
        text += " (длина: " + QString::number(currentBitSeq->GetLength()) + " бит)";
        bitDisplay->setText(text);
    }
}

void MainWindow::displayLinkedList() {
    if (linkedDisplay && currentLinkedList) {
        QString text = "[";
        for (size_t i = 0; i < currentLinkedList->GetLength(); i++) {
            text += QString::number(currentLinkedList->Get(i));
            if (i < currentLinkedList->GetLength() - 1) text += ", ";
        }
        text += "] (длина: " + QString::number(currentLinkedList->GetLength()) + ")";
        linkedDisplay->setText(text);
    }
}

void MainWindow::displaySetSequenceInt() {
    if (setDisplayInt && currentSetSeqInt) {
        QString text = "{";
        for (size_t i = 0; i < currentSetSeqInt->GetLength(); i++) {
            text += QString::number(currentSetSeqInt->Get(i));
            if (i < currentSetSeqInt->GetLength() - 1) text += ", ";
        }
        text += "} (размер: " + QString::number(currentSetSeqInt->GetLength()) + ")";
        setDisplayInt->setText(text);
    }
}

void MainWindow::displaySetSequenceDouble() {
    if (setDisplayDouble && currentSetSeqDouble) {
        QString text = "{";
        for (size_t i = 0; i < currentSetSeqDouble->GetLength(); i++) {
            text += QString::number(currentSetSeqDouble->Get(i));
            if (i < currentSetSeqDouble->GetLength() - 1) text += ", ";
        }
        text += "} (размер: " + QString::number(currentSetSeqDouble->GetLength()) + ")";
        setDisplayDouble->setText(text);
    }
}

void MainWindow::displaySetSequenceComplex() {
    if (setDisplayComplex && currentSetSeqComplex) {
        QString text = "{";
        for (size_t i = 0; i < currentSetSeqComplex->GetLength(); i++) {
            Complex c = currentSetSeqComplex->Get(i);
            text += QString::number(c.real()) + (c.imag() >= 0 ? "+" : "") + QString::number(c.imag()) + "i";
            if (i < currentSetSeqComplex->GetLength() - 1) text += ", ";
        }
        text += "} (размер: " + QString::number(currentSetSeqComplex->GetLength()) + ")";
        setDisplayComplex->setText(text);
    }
}

void MainWindow::displaySetSequenceString() {
    if (setDisplayString && currentSetSeqString) {
        QString text = "{";
        for (size_t i = 0; i < currentSetSeqString->GetLength(); i++) {
            text += "\"" + currentSetSeqString->Get(i) + "\"";
            if (i < currentSetSeqString->GetLength() - 1) text += ", ";
        }
        text += "} (размер: " + QString::number(currentSetSeqString->GetLength()) + ")";
        setDisplayString->setText(text);
    }
}

void MainWindow::displaySetSequenceFunction() {
    if (setDisplayFunction && currentSetSeqFunction) {
        QString text = "{";
        for (size_t i = 0; i < currentSetSeqFunction->GetLength(); i++) {
            text += QString::fromStdString(currentSetSeqFunction->Get(i).GetName());
            if (i < currentSetSeqFunction->GetLength() - 1) text += ", ";
        }
        text += "} (размер: " + QString::number(currentSetSeqFunction->GetLength()) + ")";
        setDisplayFunction->setText(text);
    }
}

void MainWindow::displaySetSequencePerson() {
    if (setDisplayPerson && currentSetSeqPerson) {
        QString text = "{";
        for (size_t i = 0; i < currentSetSeqPerson->GetLength(); i++) {
            Person p = currentSetSeqPerson->Get(i);
            text += QString::fromStdString(p.GetFullName()) + "(" + QString::number(p.GetID().GetNumber()) + ")";
            if (i < currentSetSeqPerson->GetLength() - 1) text += ", ";
        }
        text += "} (размер: " + QString::number(currentSetSeqPerson->GetLength()) + ")";
        setDisplayPerson->setText(text);
    }
}

void MainWindow::displaySetSequencePair() {
    if (setDisplayPair && currentSetSeqPair) {
        QString text = "{";
        for (size_t i = 0; i < currentSetSeqPair->GetLength(); i++) {
            Pair<int, QString> p = currentSetSeqPair->Get(i);
            text += "(" + QString::number(p.GetFirst()) + ", \"" + p.GetSecond() + "\")";
            if (i < currentSetSeqPair->GetLength() - 1) text += ", ";
        }
        text += "} (размер: " + QString::number(currentSetSeqPair->GetLength()) + ")";
        setDisplayPair->setText(text);
    }
}

void MainWindow::runArraySequenceDemo() {}
void MainWindow::runListSequenceDemo() {}
void MainWindow::runBitSequenceDemo() {}