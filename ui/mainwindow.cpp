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
, outputTextEdit(nullptr)
, arrayDisplay(nullptr)
, listDisplay(nullptr)
, bitDisplay(nullptr)
, linkedDisplay(nullptr)
{
    setupUI();
    currentArraySeq = new ArraySequence<int>();
    currentListSeq = new ListSequence<int>();
    currentBitSeq = new BitSequence(static_cast<size_t>(0));
    currentLinkedList = new LinkedList<int>();
    displayArraySequence();
    displayListSequence();
    displayBitSequence();
    displayLinkedList();
    updateOutput("Приложение запущено. Используйте вкладки для работы со структурами данных.\n");
}

MainWindow::~MainWindow()
{
    delete currentArraySeq;
    delete currentListSeq;
    delete currentBitSeq;
    delete currentLinkedList;
}

void MainWindow::setupUI()
{
    setWindowTitle("Лабораторная работа 2.2 - Структуры данных");
    setMinimumSize(1200, 800);
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    QTabWidget* operationsTabs = new QTabWidget();
    operationsTabs->setMinimumWidth(500);
    operationsTabs->addTab(createArraySequenceTab(), "ArraySequence");
    operationsTabs->addTab(createListSequenceTab(), "ListSequence");
    operationsTabs->addTab(createBitSequenceTab(), "BitSequence");
    operationsTabs->addTab(createLinkedListTab(), "LinkedList");
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

void MainWindow::displayArraySequence()
{
    if (arrayDisplay && currentArraySeq) {
        QString text = "[";
        for (size_t i = 0; i < static_cast<size_t>(currentArraySeq->GetLength()); i++) {
            text += QString::number(currentArraySeq->Get(i));
            if (i < currentArraySeq->GetLength() - 1) text += ", ";
        }
        text += "] (длина: " + QString::number(currentArraySeq->GetLength()) + ")";
        arrayDisplay->setText(text);
    }
}

void MainWindow::displayListSequence()
{
    if (listDisplay && currentListSeq) {
        QString text = "[";
        for (size_t i = 0; i < static_cast<size_t>(currentListSeq->GetLength()); i++) {
            text += QString::number(currentListSeq->Get(i));
            if (i < currentListSeq->GetLength() - 1) text += ", ";
        }
        text += "] (длина: " + QString::number(currentListSeq->GetLength()) + ")";
        listDisplay->setText(text);
    }
}

void MainWindow::displayBitSequence()
{
    if (bitDisplay && currentBitSeq) {
        QString text = "";
        for (size_t i = 0; i < static_cast<size_t>(currentBitSeq->GetLength()); i++) {
            text += QString::number(currentBitSeq->GetBit(i));
            if ((i + 1) % 8 == 0 && i < currentBitSeq->GetLength() - 1) text += " ";
        }
        text += " (длина: " + QString::number(currentBitSeq->GetLength()) + " бит)";
        bitDisplay->setText(text);
    }
}

void MainWindow::displayLinkedList()
{
    if (linkedDisplay && currentLinkedList) {
        QString text = "[";
        for (size_t i = 0; i < static_cast<size_t>(currentLinkedList->GetLength()); i++) {
            text += QString::number(currentLinkedList->Get(i));
            if (i < currentLinkedList->GetLength() - 1) text += ", ";
        }
        text += "] (длина: " + QString::number(currentLinkedList->GetLength()) + ")";
        linkedDisplay->setText(text);
    }
}

void MainWindow::runArraySequenceDemo() {}
void MainWindow::runListSequenceDemo() {}
void MainWindow::runBitSequenceDemo() {}