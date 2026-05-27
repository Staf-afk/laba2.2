#include "mainwindow.h"
#include <QDebug>
#include <QScrollBar>
#include <QPushButton>
#include <QLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
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
    currentBitSeq = new BitSequence(0);
    currentLinkedList = new LinkedList<int>();


    displayArraySequence();
    displayListSequence();
    displayBitSequence();
    displayLinkedList();
    
    updateOutput("Application started. Use tabs to work with different data structures.\n");
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
    setWindowTitle("Laboratory Work 2.2 - Data Structures");
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
    QGroupBox* outputGroup = new QGroupBox("Output");
    QVBoxLayout* outputLayout = new QVBoxLayout(outputGroup);
    outputTextEdit = new QTextEdit();
    outputTextEdit->setReadOnly(true);
    outputTextEdit->setFontFamily("Consolas");
    outputLayout->addWidget(outputTextEdit);
    rightLayout->addWidget(outputGroup);
    
    QPushButton* clearOutputBtn = new QPushButton("Clear Output");
    rightLayout->addWidget(clearOutputBtn);
    mainLayout->addWidget(rightPanel, 1);
    
    connect(clearOutputBtn, &QPushButton::clicked, this, &MainWindow::clearOutput);
}

QWidget* MainWindow::createArraySequenceTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);
    
    QGroupBox* viewGroup = new QGroupBox("Current ArraySequence");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    arrayDisplay = new QTextEdit();
    arrayDisplay->setReadOnly(true);
    arrayDisplay->setMaximumHeight(100);
    viewLayout->addWidget(arrayDisplay);
    layout->addWidget(viewGroup);
    
    QGroupBox* opsGroup = new QGroupBox("Operations");
    QGridLayout* opsLayout = new QGridLayout(opsGroup);
    QLineEdit* valueInput = new QLineEdit(); 
    valueInput->setPlaceholderText("Value");
    QLineEdit* indexInput = new QLineEdit(); 
    indexInput->setPlaceholderText("Index");
    QLineEdit* startInput = new QLineEdit(); 
    startInput->setPlaceholderText("Start");
    QLineEdit* endInput = new QLineEdit(); 
    endInput->setPlaceholderText("End");
    
    QPushButton* appendBtn = new QPushButton("Append");
    QPushButton* prependBtn = new QPushButton("Prepend");
    QPushButton* insertBtn = new QPushButton("InsertAt");
    QPushButton* getBtn = new QPushButton("Get");
    QPushButton* subseqBtn = new QPushButton("GetSubsequence");
    QPushButton* concatBtn = new QPushButton("Concat (with copy)");
    QPushButton* mapBtn = new QPushButton("Map (+1 to all)");
    QPushButton* whereBtn = new QPushButton("Where (even numbers)");
    QPushButton* reduceBtn = new QPushButton("Reduce (sum)");
    QPushButton* findBtn = new QPushButton("Find (value == 3)");
    
    QPushButton* removeAtBtn = new QPushButton("RemoveAt");
    QPushButton* removeFirstBtn = new QPushButton("RemoveFirst");
    QPushButton* removeLastBtn = new QPushButton("RemoveLast");
    
    opsLayout->addWidget(valueInput, 0, 0); 
    opsLayout->addWidget(appendBtn, 0, 1); 
    opsLayout->addWidget(prependBtn, 0, 2);
    opsLayout->addWidget(indexInput, 1, 0); 
    opsLayout->addWidget(insertBtn, 1, 1); 
    opsLayout->addWidget(getBtn, 1, 2);
    opsLayout->addWidget(removeAtBtn, 1, 3);
    opsLayout->addWidget(startInput, 2, 0); 
    opsLayout->addWidget(endInput, 2, 1); 
    opsLayout->addWidget(subseqBtn, 2, 2);
    opsLayout->addWidget(removeFirstBtn, 2, 3);
    opsLayout->addWidget(concatBtn, 3, 0); 
    opsLayout->addWidget(mapBtn, 3, 1);
    opsLayout->addWidget(removeLastBtn, 3, 2);
    opsLayout->addWidget(whereBtn, 4, 0);
    opsLayout->addWidget(reduceBtn, 4, 1);
    opsLayout->addWidget(findBtn, 5, 0, 1, 3);
    layout->addWidget(opsGroup);
    
    layout->addStretch();
    
    connect(appendBtn, &QPushButton::clicked, [this, valueInput]() {
        if (!valueInput->text().isEmpty()) {
            currentArraySeq->Append(valueInput->text().toInt());
            displayArraySequence();
            updateOutput("Append(" + valueInput->text() + ")");
            valueInput->clear();
        }
    });
    
    connect(prependBtn, &QPushButton::clicked, [this, valueInput]() {
        if (!valueInput->text().isEmpty()) {
            currentArraySeq->Prepend(valueInput->text().toInt());
            displayArraySequence();
            updateOutput("Prepend(" + valueInput->text() + ")");
            valueInput->clear();
        }
    });
    
    connect(insertBtn, &QPushButton::clicked, [this, valueInput, indexInput]() {
        if (!valueInput->text().isEmpty() && !indexInput->text().isEmpty()) {
            try {
                currentArraySeq->InsertAt(valueInput->text().toInt(), indexInput->text().toInt());
                displayArraySequence();
                updateOutput("InsertAt(" + valueInput->text() + ", " + indexInput->text() + ")");
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
            valueInput->clear(); 
            indexInput->clear();
        }
    });
    
    connect(getBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                int val = currentArraySeq->Get(indexInput->text().toInt());
                updateOutput("Get(" + indexInput->text() + ") = " + QString::number(val));
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
            indexInput->clear();
        }
    });
    
    connect(removeAtBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                int index = indexInput->text().toInt();
                ArraySequence<int>* newSeq = new ArraySequence<int>();
                for (int i = 0; i < currentArraySeq->GetLength(); i++) {
                    if (i != index) {
                        newSeq->Append(currentArraySeq->Get(i));
                    }
                }
                delete currentArraySeq;
                currentArraySeq = newSeq;
                displayArraySequence();
                updateOutput("RemoveAt(" + QString::number(index) + ")");
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
            indexInput->clear();
        }
    });
    
    connect(removeFirstBtn, &QPushButton::clicked, [this]() {
        if (currentArraySeq->GetLength() > 0) {
            try {
                ArraySequence<int>* newSeq = new ArraySequence<int>();
                for (int i = 1; i < currentArraySeq->GetLength(); i++) {
                    newSeq->Append(currentArraySeq->Get(i));
                }
                delete currentArraySeq;
                currentArraySeq = newSeq;
                displayArraySequence();
                updateOutput("RemoveFirst()");
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
        } else {
            updateOutput("RemoveFirst: sequence is empty");
        }
    });
    
    connect(removeLastBtn, &QPushButton::clicked, [this]() {
        if (currentArraySeq->GetLength() > 0) {
            try {
                ArraySequence<int>* newSeq = new ArraySequence<int>();
                for (int i = 0; i < currentArraySeq->GetLength() - 1; i++) {
                    newSeq->Append(currentArraySeq->Get(i));
                }
                delete currentArraySeq;
                currentArraySeq = newSeq;
                displayArraySequence();
                updateOutput("RemoveLast()");
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
        } 
        else {
            updateOutput("RemoveLast: sequence is empty");
        }
    });
    
    connect(subseqBtn, &QPushButton::clicked, [this, startInput, endInput]() {
        if (!startInput->text().isEmpty() && !endInput->text().isEmpty()) {
            try {
                auto* subseq = currentArraySeq->GetSubsequence(startInput->text().toInt(), endInput->text().toInt());
                QString result = "Subsequence [";
                for (int i = 0; i < subseq->GetLength(); i++) { 
                    result += QString::number(subseq->Get(i)); 
                    if (i < subseq->GetLength() - 1) result += ", "; 
                }
                result += "]";
                updateOutput(result); 
                delete subseq;
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
            startInput->clear(); 
            endInput->clear();
        }
    });
    
    connect(concatBtn, &QPushButton::clicked, [this]() {
        auto* copy = new ArraySequence<int>();
        for (int i = 0; i < currentArraySeq->GetLength(); i++) {
            copy->Append(currentArraySeq->Get(i));
        }
        auto* result = currentArraySeq->Concat(copy);
        updateOutput("Concat: created new sequence with duplicate");
        delete copy; 
        delete result;
    });
    
    connect(mapBtn, &QPushButton::clicked, [this]() {
        if (currentArraySeq->GetLength() > 0) {
            auto* result = currentArraySeq->Map();
            QString res = "Map (+1): [";
            for (int i = 0; i < result->GetLength(); i++) {
                res += QString::number(result->Get(i));
                if (i < result->GetLength() - 1) res += ", ";
            }
            res += "]";
            updateOutput(res);
            delete result;
        } else {
            updateOutput("Map: sequence is empty");
        }
    });
    
    connect(whereBtn, &QPushButton::clicked, [this]() {
        if (currentArraySeq->GetLength() > 0) {
            auto* result = currentArraySeq->Where();
            QString res = "Where (even numbers): [";
            for (int i = 0; i < result->GetLength(); i++) {
                res += QString::number(result->Get(i));
                if (i < result->GetLength() - 1) res += ", ";
            }
            res += "]";
            updateOutput(res);
            delete result;
        } else {
            updateOutput("Where: sequence is empty");
        }
    });
    
    connect(reduceBtn, &QPushButton::clicked, [this]() {
        if (currentArraySeq->GetLength() > 0) {
            int result = currentArraySeq->Reduce();
            updateOutput("Reduce (sum) = " + QString::number(result));
        } else {
            updateOutput("Reduce: sequence is empty, sum = 0");
        }
    });
    
    connect(findBtn, &QPushButton::clicked, [this]() {
        Option<int> found = currentArraySeq->Find([](int x) { return x == 3; });
        if (found.IsSome()) {
            updateOutput("Find(value == 3): found value " + QString::number(found.GetValue()));
        } else {
            updateOutput("Find(value == 3): value not found");
        }
    });
    
    return tab;
}

QWidget* MainWindow::createListSequenceTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);
    QGroupBox* viewGroup = new QGroupBox("Current ListSequence");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    listDisplay = new QTextEdit();
    listDisplay->setReadOnly(true);
    listDisplay->setMaximumHeight(100);
    viewLayout->addWidget(listDisplay);
    layout->addWidget(viewGroup);
    
    QGroupBox* opsGroup = new QGroupBox("Operations");
    QGridLayout* opsLayout = new QGridLayout(opsGroup);
    QLineEdit* valueInput = new QLineEdit(); 
    valueInput->setPlaceholderText("Value");
    QLineEdit* indexInput = new QLineEdit(); 
    indexInput->setPlaceholderText("Index");
    QLineEdit* startInput = new QLineEdit(); 
    startInput->setPlaceholderText("Start");
    QLineEdit* endInput = new QLineEdit(); 
    endInput->setPlaceholderText("End");
    
    QPushButton* appendBtn = new QPushButton("Append");
    QPushButton* prependBtn = new QPushButton("Prepend");
    QPushButton* insertBtn = new QPushButton("InsertAt");
    QPushButton* getBtn = new QPushButton("Get");
    QPushButton* subseqBtn = new QPushButton("GetSubsequence");
    QPushButton* concatBtn = new QPushButton("Concat");
    QPushButton* mapBtn = new QPushButton("Map (+1 to all)");
    QPushButton* whereBtn = new QPushButton("Where (even numbers)");
    QPushButton* reduceBtn = new QPushButton("Reduce (sum)");
    QPushButton* findBtn = new QPushButton("Find (value == 3)");
    
    QPushButton* removeAtBtn = new QPushButton("RemoveAt");
    QPushButton* removeFirstBtn = new QPushButton("RemoveFirst");
    QPushButton* removeLastBtn = new QPushButton("RemoveLast");
    
    opsLayout->addWidget(valueInput, 0, 0); 
    opsLayout->addWidget(appendBtn, 0, 1); 
    opsLayout->addWidget(prependBtn, 0, 2);
    opsLayout->addWidget(indexInput, 1, 0); 
    opsLayout->addWidget(insertBtn, 1, 1); 
    opsLayout->addWidget(getBtn, 1, 2);
    opsLayout->addWidget(removeAtBtn, 1, 3);
    opsLayout->addWidget(startInput, 2, 0); 
    opsLayout->addWidget(endInput, 2, 1); 
    opsLayout->addWidget(subseqBtn, 2, 2);
    opsLayout->addWidget(removeFirstBtn, 2, 3);
    opsLayout->addWidget(concatBtn, 3, 0); 
    opsLayout->addWidget(mapBtn, 3, 1);
    opsLayout->addWidget(removeLastBtn, 3, 2);
    opsLayout->addWidget(whereBtn, 4, 0);
    opsLayout->addWidget(reduceBtn, 4, 1);
    opsLayout->addWidget(findBtn, 5, 0, 1, 3);
    layout->addWidget(opsGroup);
    
    layout->addStretch();
    
    connect(appendBtn, &QPushButton::clicked, [this, valueInput]() {
        if (!valueInput->text().isEmpty()) { 
            currentListSeq->Append(valueInput->text().toInt()); 
            displayListSequence(); 
            updateOutput("List Append(" + valueInput->text() + ")"); 
            valueInput->clear(); 
        }
    });
    
    connect(prependBtn, &QPushButton::clicked, [this, valueInput]() {
        if (!valueInput->text().isEmpty()) { 
            currentListSeq->Prepend(valueInput->text().toInt()); 
            displayListSequence(); 
            updateOutput("List Prepend(" + valueInput->text() + ")"); 
            valueInput->clear(); 
        }
    });
    
    connect(insertBtn, &QPushButton::clicked, [this, valueInput, indexInput]() {
        if (!valueInput->text().isEmpty() && !indexInput->text().isEmpty()) {
            try { 
                currentListSeq->InsertAt(valueInput->text().toInt(), indexInput->text().toInt()); 
                displayListSequence(); 
                updateOutput("List InsertAt(" + valueInput->text() + ", " + indexInput->text() + ")"); 
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
            valueInput->clear(); 
            indexInput->clear();
        }
    });
    
    connect(getBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try { 
                int val = currentListSeq->Get(indexInput->text().toInt()); 
                updateOutput("List Get(" + indexInput->text() + ") = " + QString::number(val)); 
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
            indexInput->clear();
        }
    });
    
    connect(removeAtBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                int index = indexInput->text().toInt();
                ListSequence<int>* newSeq = new ListSequence<int>();
                for (int i = 0; i < currentListSeq->GetLength(); i++) {
                    if (i != index) {
                        newSeq->Append(currentListSeq->Get(i));
                    }
                }
                delete currentListSeq;
                currentListSeq = newSeq;
                displayListSequence();
                updateOutput("List RemoveAt(" + QString::number(index) + ")");
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
            indexInput->clear();
        }
    });
    
    connect(removeFirstBtn, &QPushButton::clicked, [this]() {
        if (currentListSeq->GetLength() > 0) {
            try {
                ListSequence<int>* newSeq = new ListSequence<int>();
                for (int i = 1; i < currentListSeq->GetLength(); i++) {
                    newSeq->Append(currentListSeq->Get(i));
                }
                delete currentListSeq;
                currentListSeq = newSeq;
                displayListSequence();
                updateOutput("List RemoveFirst()");
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
        } 
        else {
            updateOutput("List RemoveFirst: sequence is empty");
        }
    });
    
    connect(removeLastBtn, &QPushButton::clicked, [this]() {
        if (currentListSeq->GetLength() > 0) {
            try {
                ListSequence<int>* newSeq = new ListSequence<int>();
                for (int i = 0; i < currentListSeq->GetLength() - 1; i++) {
                    newSeq->Append(currentListSeq->Get(i));
                }
                delete currentListSeq;
                currentListSeq = newSeq;
                displayListSequence();
                updateOutput("List RemoveLast()");
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
        } else {
            updateOutput("List RemoveLast: sequence is empty");
        }
    });
    
    connect(subseqBtn, &QPushButton::clicked, [this, startInput, endInput]() {
        if (!startInput->text().isEmpty() && !endInput->text().isEmpty()) {
            try {
                auto* subseq = currentListSeq->GetSubsequence(startInput->text().toInt(), endInput->text().toInt());
                QString result = "List subsequence [";
                for (int i = 0; i < subseq->GetLength(); i++) { 
                    result += QString::number(subseq->Get(i)); 
                    if (i < subseq->GetLength() - 1) result += ", "; 
                }
                result += "]"; 
                updateOutput(result); 
                delete subseq;
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
            startInput->clear(); 
            endInput->clear();
        }
    });
    
    connect(concatBtn, &QPushButton::clicked, [this]() {
        auto* copy = new ListSequence<int>();
        for (int i = 0; i < currentListSeq->GetLength(); i++) {
            copy->Append(currentListSeq->Get(i));
        }
        auto* result = currentListSeq->Concat(copy);
        updateOutput("List Concat: created new sequence"); 
        delete copy; 
        delete result;
    });
    
    connect(mapBtn, &QPushButton::clicked, [this]() {
        if (currentListSeq->GetLength() > 0) {
            auto* result = currentListSeq->Map();
            QString res = "List Map (+1): [";
            for (int i = 0; i < result->GetLength(); i++) {
                res += QString::number(result->Get(i));
                if (i < result->GetLength() - 1) res += ", ";
            }
            res += "]";
            updateOutput(res);
            delete result;
        } else {
            updateOutput("List Map: sequence is empty");
        }
    });
    
    connect(whereBtn, &QPushButton::clicked, [this]() {
        if (currentListSeq->GetLength() > 0) {
            auto* result = currentListSeq->Where();
            QString res = "List Where (even numbers): [";
            for (int i = 0; i < result->GetLength(); i++) {
                res += QString::number(result->Get(i));
                if (i < result->GetLength() - 1) res += ", ";
            }
            res += "]";
            updateOutput(res);
            delete result;
        } else {
            updateOutput("List Where: sequence is empty");
        }
    });
    
    connect(reduceBtn, &QPushButton::clicked, [this]() {
        if (currentListSeq->GetLength() > 0) {
            int result = currentListSeq->Reduce();
            updateOutput("List Reduce (sum) = " + QString::number(result));
        } else {
            updateOutput("List Reduce: sequence is empty, sum = 0");
        }
    });
    
    connect(findBtn, &QPushButton::clicked, [this]() {
        Option<int> found = currentListSeq->Find([](int x) { return x == 3; });
        if (found.IsSome()) {
            updateOutput("List Find(value == 3): found value " + QString::number(found.GetValue()));
        } else {
            updateOutput("List Find(value == 3): value not found");
        }
    });
    
    return tab;
}

QWidget* MainWindow::createBitSequenceTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);
    QGroupBox* viewGroup = new QGroupBox("Current BitSequence");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    bitDisplay = new QTextEdit();
    bitDisplay->setReadOnly(true);
    bitDisplay->setMaximumHeight(100);
    viewLayout->addWidget(bitDisplay);
    layout->addWidget(viewGroup);
    
    QGroupBox* opsGroup = new QGroupBox("Bit Operations");
    QGridLayout* opsLayout = new QGridLayout(opsGroup);
    QLineEdit* indexInput = new QLineEdit(); 
    indexInput->setPlaceholderText("Bit index");
    QCheckBox* valueCheck = new QCheckBox("Bit value");
    QLineEdit* startInput = new QLineEdit(); 
    startInput->setPlaceholderText("Start");
    QLineEdit* endInput = new QLineEdit(); 
    endInput->setPlaceholderText("End");
    QLineEdit* sizeInput = new QLineEdit(); 
    sizeInput->setPlaceholderText("Size");
    QPushButton* setBtn = new QPushButton("SetBit");
    QPushButton* getBtn = new QPushButton("GetBit");
    QPushButton* andBtn = new QPushButton("AND (with copy)");
    QPushButton* orBtn = new QPushButton("OR (with copy)");
    QPushButton* xorBtn = new QPushButton("XOR (with copy)");
    QPushButton* notBtn = new QPushButton("NOT");
    QPushButton* subseqBtn = new QPushButton("GetSubsequence");
    QPushButton* appendBtn = new QPushButton("Append");
    QPushButton* insertBtn = new QPushButton("InsertAt");
    QPushButton* createBtn = new QPushButton("Create New");
    
    QPushButton* removeAtBtn = new QPushButton("RemoveBitAt");
    QPushButton* removeFirstBtn = new QPushButton("RemoveFirstBit");
    QPushButton* removeLastBtn = new QPushButton("RemoveLastBit");
    
    opsLayout->addWidget(indexInput, 0, 0); 
    opsLayout->addWidget(valueCheck, 0, 1); 
    opsLayout->addWidget(setBtn, 0, 2); 
    opsLayout->addWidget(getBtn, 0, 3);
    opsLayout->addWidget(andBtn, 1, 0); 
    opsLayout->addWidget(orBtn, 1, 1); 
    opsLayout->addWidget(xorBtn, 1, 2); 
    opsLayout->addWidget(notBtn, 1, 3);
    opsLayout->addWidget(startInput, 2, 0); 
    opsLayout->addWidget(endInput, 2, 1); 
    opsLayout->addWidget(subseqBtn, 2, 2); 
    opsLayout->addWidget(appendBtn, 2, 3);
    opsLayout->addWidget(sizeInput, 3, 0); 
    opsLayout->addWidget(createBtn, 3, 1); 
    opsLayout->addWidget(insertBtn, 3, 2);
    opsLayout->addWidget(removeAtBtn, 4, 0);
    opsLayout->addWidget(removeFirstBtn, 4, 1);
    opsLayout->addWidget(removeLastBtn, 4, 2);
    layout->addWidget(opsGroup);
    
    layout->addStretch();
    
    connect(setBtn, &QPushButton::clicked, [this, indexInput, valueCheck]() {
        if (!indexInput->text().isEmpty()) {
            try { 
                currentBitSeq->SetBit(indexInput->text().toInt(), valueCheck->isChecked()); 
                displayBitSequence(); 
                updateOutput("Bit SetBit(" + indexInput->text() + ", " + (valueCheck->isChecked() ? "1" : "0") + ")"); 
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
            indexInput->clear();
        }
    });
    
    connect(getBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try { 
                bool val = currentBitSeq->GetBit(indexInput->text().toInt()); 
                updateOutput("Bit GetBit(" + indexInput->text() + ") = " + QString::number(val)); 
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
            indexInput->clear();
        }
    });
    
    connect(removeAtBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                int index = indexInput->text().toInt();
                BitSequence* newSeq = new BitSequence(currentBitSeq->GetLength() - 1);
                int newIndex = 0;
                for (int i = 0; i < currentBitSeq->GetLength(); i++) {
                    if (i != index) {
                        newSeq->SetBit(newIndex++, currentBitSeq->GetBit(i));
                    }
                }
                delete currentBitSeq;
                currentBitSeq = newSeq;
                displayBitSequence();
                updateOutput("Bit RemoveBitAt(" + QString::number(index) + ")");
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
            indexInput->clear();
        }
    });
    
    connect(removeFirstBtn, &QPushButton::clicked, [this]() {
        if (currentBitSeq->GetLength() > 0) {
            try {
                BitSequence* newSeq = new BitSequence(currentBitSeq->GetLength() - 1);
                for (int i = 1; i < currentBitSeq->GetLength(); i++) {
                    newSeq->SetBit(i - 1, currentBitSeq->GetBit(i));
                }
                delete currentBitSeq;
                currentBitSeq = newSeq;
                displayBitSequence();
                updateOutput("Bit RemoveFirstBit()");
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
        } else {
            updateOutput("RemoveFirstBit: sequence is empty");
        }
    });
    
    connect(removeLastBtn, &QPushButton::clicked, [this]() {
        if (currentBitSeq->GetLength() > 0) {
            try {
                BitSequence* newSeq = new BitSequence(currentBitSeq->GetLength() - 1);
                for (int i = 0; i < currentBitSeq->GetLength() - 1; i++) {
                    newSeq->SetBit(i, currentBitSeq->GetBit(i));
                }
                delete currentBitSeq;
                currentBitSeq = newSeq;
                displayBitSequence();
                updateOutput("Bit RemoveLastBit()");
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
        } else {
            updateOutput("RemoveLastBit: sequence is empty");
        }
    });
    
    connect(andBtn, &QPushButton::clicked, [this]() {
        BitSequence copy(*currentBitSeq);
        auto* result = currentBitSeq->And(copy);
        QString res = "Bit AND result: ";
        for (int i = 0; i < result->GetLength(); i++) {
            res += QString::number(result->GetBit(i));
        }
        updateOutput(res); 
        delete result;
    });
    
    connect(orBtn, &QPushButton::clicked, [this]() {
        BitSequence copy(*currentBitSeq);
        auto* result = currentBitSeq->Or(copy);
        QString res = "Bit OR result: ";
        for (int i = 0; i < result->GetLength(); i++) {
            res += QString::number(result->GetBit(i));
        }
        updateOutput(res); 
        delete result;
    });
    
    connect(xorBtn, &QPushButton::clicked, [this]() {
        BitSequence copy(*currentBitSeq);
        auto* result = currentBitSeq->Xor(copy);
        QString res = "Bit XOR result: ";
        for (int i = 0; i < result->GetLength(); i++) {
            res += QString::number(result->GetBit(i));
        }
        updateOutput(res); 
        delete result;
    });
    
    connect(notBtn, &QPushButton::clicked, [this]() {
        auto* result = currentBitSeq->Not();
        QString res = "Bit NOT result: ";
        for (int i = 0; i < result->GetLength(); i++) {
            res += QString::number(result->GetBit(i));
        }
        updateOutput(res); 
        delete result;
    });
    
    connect(subseqBtn, &QPushButton::clicked, [this, startInput, endInput]() {
        if (!startInput->text().isEmpty() && !endInput->text().isEmpty()) {
            try {
                auto* subseq = currentBitSeq->GetSubsequence(startInput->text().toInt(), endInput->text().toInt());
                QString res = "Bit subsequence: ";
                for (int i = 0; i < subseq->GetLength(); i++) {
                    res += QString::number(subseq->GetBit(i));
                }
                updateOutput(res); 
                delete subseq;
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
            startInput->clear(); 
            endInput->clear();
        }
    });
    
    connect(appendBtn, &QPushButton::clicked, [this, valueCheck]() {
        currentBitSeq->Append(Bit(valueCheck->isChecked()));
        displayBitSequence(); 
        updateOutput("Bit Append(" + QString::number(valueCheck->isChecked()) + ")");
    });
    
    connect(insertBtn, &QPushButton::clicked, [this, indexInput, valueCheck]() {
        if (!indexInput->text().isEmpty()) {
            try { 
                currentBitSeq->InsertAt(Bit(valueCheck->isChecked()), indexInput->text().toInt()); 
                displayBitSequence(); 
                updateOutput("Bit InsertAt(" + QString::number(valueCheck->isChecked()) + ", " + indexInput->text() + ")"); 
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
            indexInput->clear();
        }
    });
    
    connect(createBtn, &QPushButton::clicked, [this, sizeInput]() {
        int size = sizeInput->text().isEmpty() ? 8 : sizeInput->text().toInt();
        delete currentBitSeq;
        currentBitSeq = new BitSequence(size);
        displayBitSequence(); 
        updateOutput("Created new BitSequence of size " + QString::number(size));
        sizeInput->clear();
    });
    
    return tab;
}

QWidget* MainWindow::createLinkedListTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);
    QGroupBox* viewGroup = new QGroupBox("Current LinkedList");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    linkedDisplay = new QTextEdit();
    linkedDisplay->setReadOnly(true);
    linkedDisplay->setMaximumHeight(100);
    viewLayout->addWidget(linkedDisplay);
    layout->addWidget(viewGroup);
    
    QGroupBox* opsGroup = new QGroupBox("Operations");
    QGridLayout* opsLayout = new QGridLayout(opsGroup);
    QLineEdit* valueInput = new QLineEdit(); 
    valueInput->setPlaceholderText("Value");
    QLineEdit* indexInput = new QLineEdit(); 
    indexInput->setPlaceholderText("Index");
    QLineEdit* startInput = new QLineEdit(); 
    startInput->setPlaceholderText("Start");
    QLineEdit* endInput = new QLineEdit(); 
    endInput->setPlaceholderText("End");
    QPushButton* appendBtn = new QPushButton("Append");
    QPushButton* prependBtn = new QPushButton("Prepend");
    QPushButton* insertBtn = new QPushButton("InsertAt");
    QPushButton* getBtn = new QPushButton("Get");
    QPushButton* sublistBtn = new QPushButton("GetSubList");
    
    QPushButton* removeAtBtn = new QPushButton("RemoveAt");
    QPushButton* removeFirstBtn = new QPushButton("RemoveFirst");
    QPushButton* removeLastBtn = new QPushButton("RemoveLast");
    
    opsLayout->addWidget(valueInput, 0, 0); 
    opsLayout->addWidget(appendBtn, 0, 1); 
    opsLayout->addWidget(prependBtn, 0, 2);
    opsLayout->addWidget(indexInput, 1, 0); 
    opsLayout->addWidget(insertBtn, 1, 1); 
    opsLayout->addWidget(getBtn, 1, 2);
    opsLayout->addWidget(removeAtBtn, 1, 3);
    opsLayout->addWidget(startInput, 2, 0); 
    opsLayout->addWidget(endInput, 2, 1); 
    opsLayout->addWidget(sublistBtn, 2, 2);
    opsLayout->addWidget(removeFirstBtn, 2, 3);
    opsLayout->addWidget(removeLastBtn, 3, 0);
    layout->addWidget(opsGroup);
    layout->addStretch();
    
    connect(appendBtn, &QPushButton::clicked, [this, valueInput]() {
        if (!valueInput->text().isEmpty()) { 
            currentLinkedList->Append(valueInput->text().toInt()); 
            displayLinkedList(); 
            updateOutput("LinkedList Append(" + valueInput->text() + ")"); 
            valueInput->clear(); 
        }
    });
    
    connect(prependBtn, &QPushButton::clicked, [this, valueInput]() {
        if (!valueInput->text().isEmpty()) { 
            currentLinkedList->Prepend(valueInput->text().toInt()); 
            displayLinkedList(); 
            updateOutput("LinkedList Prepend(" + valueInput->text() + ")"); 
            valueInput->clear(); 
        }
    });
    
    connect(insertBtn, &QPushButton::clicked, [this, valueInput, indexInput]() {
        if (!valueInput->text().isEmpty() && !indexInput->text().isEmpty()) {
            try { 
                currentLinkedList->InsertAt(valueInput->text().toInt(), indexInput->text().toInt()); 
                displayLinkedList(); 
                updateOutput("LinkedList InsertAt(" + valueInput->text() + ", " + indexInput->text() + ")"); 
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
            valueInput->clear(); 
            indexInput->clear();
        }
    });
    
    connect(getBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try { 
                int val = currentLinkedList->Get(indexInput->text().toInt()); 
                updateOutput("LinkedList Get(" + indexInput->text() + ") = " + QString::number(val)); 
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
            indexInput->clear();
        }
    });
    
    connect(removeAtBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                int index = indexInput->text().toInt();
                LinkedList<int>* newList = new LinkedList<int>();
                for (int i = 0; i < currentLinkedList->GetLength(); i++) {
                    if (i != index) {
                        newList->Append(currentLinkedList->Get(i));
                    }
                }
                delete currentLinkedList;
                currentLinkedList = newList;
                displayLinkedList();
                updateOutput("LinkedList RemoveAt(" + QString::number(index) + ")");
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
            indexInput->clear();
        }
    });
    
    connect(removeFirstBtn, &QPushButton::clicked, [this]() {
        if (currentLinkedList->GetLength() > 0) {
            try {
                LinkedList<int>* newList = new LinkedList<int>();
                for (int i = 1; i < currentLinkedList->GetLength(); i++) {
                    newList->Append(currentLinkedList->Get(i));
                }
                delete currentLinkedList;
                currentLinkedList = newList;
                displayLinkedList();
                updateOutput("LinkedList RemoveFirst()");
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
        } else {
            updateOutput("LinkedList RemoveFirst: list is empty");
        }
    });
    
    connect(removeLastBtn, &QPushButton::clicked, [this]() {
        if (currentLinkedList->GetLength() > 0) {
            try {
                LinkedList<int>* newList = new LinkedList<int>();
                for (int i = 0; i < currentLinkedList->GetLength() - 1; i++) {
                    newList->Append(currentLinkedList->Get(i));
                }
                delete currentLinkedList;
                currentLinkedList = newList;
                displayLinkedList();
                updateOutput("LinkedList RemoveLast()");
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
        } 
        else {
            updateOutput("LinkedList RemoveLast: list is empty");
        }
    });
    
    connect(sublistBtn, &QPushButton::clicked, [this, startInput, endInput]() {
        if (!startInput->text().isEmpty() && !endInput->text().isEmpty()) {
            try {
                auto* sublist = currentLinkedList->GetSubList(startInput->text().toInt(), endInput->text().toInt());
                QString result = "LinkedList sublist [";
                for (int i = 0; i < sublist->GetLength(); i++) { 
                    result += QString::number(sublist->Get(i)); 
                    if (i < sublist->GetLength() - 1) result += ", "; 
                }
                result += "]"; 
                updateOutput(result); 
                delete sublist;
            } catch (const std::exception& e) { 
                updateOutput("Error: " + QString(e.what())); 
            }
            startInput->clear(); 
            endInput->clear();
        }
    });
    
    return tab;
}

void MainWindow::updateOutput(const QString& text)
{
    if (outputTextEdit) {
        outputTextEdit->append("> " + text);
        outputTextEdit->verticalScrollBar()->setValue(outputTextEdit->verticalScrollBar()->maximum());
    }
}

void MainWindow::displayArraySequence()
{
    if (arrayDisplay && currentArraySeq) {
        QString text = "[";
        for (int i = 0; i < currentArraySeq->GetLength(); i++) {
            text += QString::number(currentArraySeq->Get(i));
            if (i < currentArraySeq->GetLength() - 1) text += ", ";
        }
        text += "] (length: " + QString::number(currentArraySeq->GetLength()) + ")";
        arrayDisplay->setText(text);
    }
}

void MainWindow::displayListSequence()
{
    if (listDisplay && currentListSeq) {
        QString text = "[";
        for (int i = 0; i < currentListSeq->GetLength(); i++) {
            text += QString::number(currentListSeq->Get(i));
            if (i < currentListSeq->GetLength() - 1) text += ", ";
        }
        text += "] (length: " + QString::number(currentListSeq->GetLength()) + ")";
        listDisplay->setText(text);
    }
}

void MainWindow::displayBitSequence()
{
    if (bitDisplay && currentBitSeq) {
        QString text = "";
        for (int i = 0; i < currentBitSeq->GetLength(); i++) {
            text += QString::number(currentBitSeq->GetBit(i));
            if ((i + 1) % 8 == 0 && i < currentBitSeq->GetLength() - 1) text += " ";
        }
        text += " (length: " + QString::number(currentBitSeq->GetLength()) + " bits)";
        bitDisplay->setText(text);
    }
}

void MainWindow::displayLinkedList()
{
    if (linkedDisplay && currentLinkedList) {
        QString text = "[";
        for (int i = 0; i < currentLinkedList->GetLength(); i++) {
            text += QString::number(currentLinkedList->Get(i));
            if (i < currentLinkedList->GetLength() - 1) text += ", ";
        }
        text += "] (length: " + QString::number(currentLinkedList->GetLength()) + ")";
        linkedDisplay->setText(text);
    }
}

void MainWindow::runArraySequenceDemo() {}
void MainWindow::runListSequenceDemo() {}
void MainWindow::runBitSequenceDemo() {}

void MainWindow::clearOutput()
{
    if (outputTextEdit) outputTextEdit->clear();
}