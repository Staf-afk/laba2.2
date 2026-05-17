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
    , currentDynamicArray(nullptr)
    , currentLinkedList(nullptr)
    , outputTextEdit(nullptr)
    , arrayDisplay(nullptr)
    , listDisplay(nullptr)
    , bitDisplay(nullptr)
    , dynamicDisplay(nullptr)
    , linkedDisplay(nullptr)
{
    setupUI();
    
    // Initialize examples
    currentArraySeq = new ArraySequence<int>();
    currentListSeq = new ListSequence<int>();
    currentBitSeq = new BitSequence(8);
    currentDynamicArray = new DynamicArray<int>();
    currentLinkedList = new LinkedList<int>();
    
    // Add demo data
    for (int i = 1; i <= 5; i++) {
        currentArraySeq->Append(i);
        currentListSeq->Append(i);
        currentLinkedList->Append(i);
    }
    
    for (int i = 0; i < currentBitSeq->GetLength(); i++) {
        currentBitSeq->SetBit(i, i % 2 == 0);
    }
    
    for (int i = 0; i < 5; i++) {
        currentDynamicArray->Resize(i + 1);
        currentDynamicArray->Set(i, (i + 1) * 10);
    }
    
    displayArraySequence();
    displayListSequence();
    displayBitSequence();
    displayDynamicArray();
    displayLinkedList();
    
    updateOutput("Application started. Use tabs to work with different data structures.\n");
}

MainWindow::~MainWindow()
{
    delete currentArraySeq;
    delete currentListSeq;
    delete currentBitSeq;
    delete currentDynamicArray;
    delete currentLinkedList;
}

void MainWindow::setupUI()
{
    setWindowTitle("Laboratory Work 2.2 - Data Structures");
    setMinimumSize(1200, 800);
    
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    
    // Left panel with operation tabs
    QTabWidget* operationsTabs = new QTabWidget();
    operationsTabs->setMinimumWidth(500);
    
    operationsTabs->addTab(createArraySequenceTab(), "ArraySequence");
    operationsTabs->addTab(createListSequenceTab(), "ListSequence");
    operationsTabs->addTab(createBitSequenceTab(), "BitSequence");
    operationsTabs->addTab(createDynamicArrayTab(), "DynamicArray");
    operationsTabs->addTab(createLinkedListTab(), "LinkedList");
    
    mainLayout->addWidget(operationsTabs, 2);
    
    // Right panel with output
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
    
    // Current state view
    QGroupBox* viewGroup = new QGroupBox("Current ArraySequence");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    arrayDisplay = new QTextEdit();
    arrayDisplay->setReadOnly(true);
    arrayDisplay->setMaximumHeight(100);
    viewLayout->addWidget(arrayDisplay);
    layout->addWidget(viewGroup);
    
    // Operations
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
    QLineEdit* mapFuncInput = new QLineEdit();
    mapFuncInput->setPlaceholderText("Function (x*2, x+1, x*x)");
    QLineEdit* predicateInput = new QLineEdit();
    predicateInput->setPlaceholderText("Predicate (x>2, x%2==0)");
    QLineEdit* initialInput = new QLineEdit();
    initialInput->setPlaceholderText("Initial value");
    
    QPushButton* appendBtn = new QPushButton("Append");
    QPushButton* prependBtn = new QPushButton("Prepend");
    QPushButton* insertBtn = new QPushButton("InsertAt");
    QPushButton* getBtn = new QPushButton("Get");
    QPushButton* subseqBtn = new QPushButton("GetSubsequence");
    QPushButton* concatBtn = new QPushButton("Concat (with copy)");
    QPushButton* mapBtn = new QPushButton("Map");
    QPushButton* whereBtn = new QPushButton("Where");
    QPushButton* reduceBtn = new QPushButton("Reduce");
    QPushButton* findBtn = new QPushButton("Find");
    
    opsLayout->addWidget(valueInput, 0, 0);
    opsLayout->addWidget(appendBtn, 0, 1);
    opsLayout->addWidget(prependBtn, 0, 2);
    opsLayout->addWidget(indexInput, 1, 0);
    opsLayout->addWidget(insertBtn, 1, 1);
    opsLayout->addWidget(getBtn, 1, 2);
    opsLayout->addWidget(startInput, 2, 0);
    opsLayout->addWidget(endInput, 2, 1);
    opsLayout->addWidget(subseqBtn, 2, 2);
    opsLayout->addWidget(concatBtn, 3, 0);
    opsLayout->addWidget(mapFuncInput, 4, 0, 1, 2);
    opsLayout->addWidget(mapBtn, 4, 2);
    opsLayout->addWidget(predicateInput, 5, 0, 1, 2);
    opsLayout->addWidget(whereBtn, 5, 2);
    opsLayout->addWidget(initialInput, 6, 0, 1, 2);
    opsLayout->addWidget(reduceBtn, 6, 2);
    opsLayout->addWidget(findBtn, 7, 0, 1, 3);
    
    layout->addWidget(opsGroup);
    
    QPushButton* demoBtn = new QPushButton("Run ArraySequence Demo");
    layout->addWidget(demoBtn);
    layout->addStretch();
    
    // Signal connections
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
    
    connect(subseqBtn, &QPushButton::clicked, [this, startInput, endInput]() {
        if (!startInput->text().isEmpty() && !endInput->text().isEmpty()) {
            try {
                auto* subseq = currentArraySeq->GetSubsequence(
                    startInput->text().toInt(), 
                    endInput->text().toInt()
                );
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
    
    connect(mapBtn, &QPushButton::clicked, [this, mapFuncInput]() {
        if (!mapFuncInput->text().isEmpty()) {
            QString funcStr = mapFuncInput->text();
            auto* result = currentArraySeq->Map<int>([funcStr](int x) -> int {
                if (funcStr == "x*2") return x * 2;
                if (funcStr == "x+1") return x + 1;
                if (funcStr == "x*x") return x * x;
                return x;
            });
            QString res = "Map([";
            for (int i = 0; i < result->GetLength(); i++) {
                res += QString::number(result->Get(i));
                if (i < result->GetLength() - 1) res += ", ";
            }
            res += "])";
            updateOutput(res);
            delete result;
            mapFuncInput->clear();
        }
    });
    
    connect(whereBtn, &QPushButton::clicked, [this, predicateInput]() {
        if (!predicateInput->text().isEmpty()) {
            QString predStr = predicateInput->text();
            auto* result = currentArraySeq->Where([predStr](int x) -> bool {
                if (predStr == "x>2") return x > 2;
                if (predStr == "x%2==0") return x % 2 == 0;
                return true;
            });
            QString res = "Where([";
            for (int i = 0; i < result->GetLength(); i++) {
                res += QString::number(result->Get(i));
                if (i < result->GetLength() - 1) res += ", ";
            }
            res += "])";
            updateOutput(res);
            delete result;
            predicateInput->clear();
        }
    });
    
    connect(reduceBtn, &QPushButton::clicked, [this, initialInput]() {
        int initial = initialInput->text().isEmpty() ? 0 : initialInput->text().toInt();
        int result = currentArraySeq->Reduce<int>([](int acc, int x) { return acc + x; }, initial);
        updateOutput("Reduce(sum, initial=" + QString::number(initial) + ") = " + QString::number(result));
    });
    
    connect(findBtn, &QPushButton::clicked, [this]() {
        Option<int> found = currentArraySeq->Find([](int x) { return x == 3; });
        if (found.IsSome()) {
            updateOutput("Find(value == 3): found value " + QString::number(found.GetValue()));
        } else {
            updateOutput("Find(value == 3): value not found");
        }
    });
    
    connect(demoBtn, &QPushButton::clicked, this, &MainWindow::runArraySequenceDemo);
    
    return tab;
}

QWidget* MainWindow::createListSequenceTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);
    
    // Current state view
    QGroupBox* viewGroup = new QGroupBox("Current ListSequence");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    listDisplay = new QTextEdit();
    listDisplay->setReadOnly(true);
    listDisplay->setMaximumHeight(100);
    viewLayout->addWidget(listDisplay);
    layout->addWidget(viewGroup);
    
    // Operations
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
    QLineEdit* mapFuncInput = new QLineEdit();
    mapFuncInput->setPlaceholderText("Function (x*2, x+1)");
    QLineEdit* predicateInput = new QLineEdit();
    predicateInput->setPlaceholderText("Predicate (x>2, x%2==0)");
    
    QPushButton* appendBtn = new QPushButton("Append");
    QPushButton* prependBtn = new QPushButton("Prepend");
    QPushButton* insertBtn = new QPushButton("InsertAt");
    QPushButton* getBtn = new QPushButton("Get");
    QPushButton* subseqBtn = new QPushButton("GetSubsequence");
    QPushButton* concatBtn = new QPushButton("Concat");
    QPushButton* mapBtn = new QPushButton("Map");
    QPushButton* whereBtn = new QPushButton("Where");
    
    opsLayout->addWidget(valueInput, 0, 0);
    opsLayout->addWidget(appendBtn, 0, 1);
    opsLayout->addWidget(prependBtn, 0, 2);
    opsLayout->addWidget(indexInput, 1, 0);
    opsLayout->addWidget(insertBtn, 1, 1);
    opsLayout->addWidget(getBtn, 1, 2);
    opsLayout->addWidget(startInput, 2, 0);
    opsLayout->addWidget(endInput, 2, 1);
    opsLayout->addWidget(subseqBtn, 2, 2);
    opsLayout->addWidget(concatBtn, 3, 0);
    opsLayout->addWidget(mapFuncInput, 4, 0, 1, 2);
    opsLayout->addWidget(mapBtn, 4, 2);
    opsLayout->addWidget(predicateInput, 5, 0, 1, 2);
    opsLayout->addWidget(whereBtn, 5, 2);
    
    layout->addWidget(opsGroup);
    
    QPushButton* demoBtn = new QPushButton("Run ListSequence Demo");
    layout->addWidget(demoBtn);
    layout->addStretch();
    
    // Signal connections
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
    
    connect(subseqBtn, &QPushButton::clicked, [this, startInput, endInput]() {
        if (!startInput->text().isEmpty() && !endInput->text().isEmpty()) {
            try {
                auto* subseq = currentListSeq->GetSubsequence(
                    startInput->text().toInt(), 
                    endInput->text().toInt()
                );
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
    
    connect(mapBtn, &QPushButton::clicked, [this, mapFuncInput]() {
        if (!mapFuncInput->text().isEmpty()) {
            QString funcStr = mapFuncInput->text();
            auto* result = currentListSeq->Map<int>([funcStr](int x) -> int {
                if (funcStr == "x*2") return x * 2;
                if (funcStr == "x+1") return x + 1;
                return x;
            });
            QString res = "List Map([";
            for (int i = 0; i < result->GetLength(); i++) {
                res += QString::number(result->Get(i));
                if (i < result->GetLength() - 1) res += ", ";
            }
            res += "])";
            updateOutput(res);
            delete result;
            mapFuncInput->clear();
        }
    });
    
    connect(whereBtn, &QPushButton::clicked, [this, predicateInput]() {
        if (!predicateInput->text().isEmpty()) {
            QString predStr = predicateInput->text();
            auto* result = currentListSeq->Where([predStr](int x) -> bool {
                if (predStr == "x>2") return x > 2;
                if (predStr == "x%2==0") return x % 2 == 0;
                return true;
            });
            QString res = "List Where([";
            for (int i = 0; i < result->GetLength(); i++) {
                res += QString::number(result->Get(i));
                if (i < result->GetLength() - 1) res += ", ";
            }
            res += "])";
            updateOutput(res);
            delete result;
            predicateInput->clear();
        }
    });
    
    connect(demoBtn, &QPushButton::clicked, this, &MainWindow::runListSequenceDemo);
    
    return tab;
}

QWidget* MainWindow::createBitSequenceTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);
    
    // Current state view
    QGroupBox* viewGroup = new QGroupBox("Current BitSequence");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    bitDisplay = new QTextEdit();
    bitDisplay->setReadOnly(true);
    bitDisplay->setMaximumHeight(100);
    viewLayout->addWidget(bitDisplay);
    layout->addWidget(viewGroup);
    
    // Operations
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
    
    layout->addWidget(opsGroup);
    
    QPushButton* demoBtn = new QPushButton("Run BitSequence Demo");
    layout->addWidget(demoBtn);
    layout->addStretch();
    
    // Signal connections
    connect(setBtn, &QPushButton::clicked, [this, indexInput, valueCheck]() {
        if (!indexInput->text().isEmpty()) {
            try {
                currentBitSeq->SetBit(indexInput->text().toInt(), valueCheck->isChecked());
                displayBitSequence();
                updateOutput("Bit SetBit(" + indexInput->text() + ", " + 
                           (valueCheck->isChecked() ? "1" : "0") + ")");
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
                auto* subseq = currentBitSeq->GetSubsequence(
                    startInput->text().toInt(), 
                    endInput->text().toInt()
                );
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
                updateOutput("Bit InsertAt(" + QString::number(valueCheck->isChecked()) + 
                           ", " + indexInput->text() + ")");
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
        for (int i = 0; i < size && i < 8; i++) {
            currentBitSeq->SetBit(i, i % 2 == 0);
        }
        displayBitSequence();
        updateOutput("Created new BitSequence of size " + QString::number(size));
        sizeInput->clear();
    });
    
    connect(demoBtn, &QPushButton::clicked, this, &MainWindow::runBitSequenceDemo);
    
    return tab;
}

QWidget* MainWindow::createDynamicArrayTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);
    
    // Current state view
    QGroupBox* viewGroup = new QGroupBox("Current DynamicArray");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    dynamicDisplay = new QTextEdit();
    dynamicDisplay->setReadOnly(true);
    dynamicDisplay->setMaximumHeight(100);
    viewLayout->addWidget(dynamicDisplay);
    layout->addWidget(viewGroup);
    
    // Operations
    QGroupBox* opsGroup = new QGroupBox("Operations");
    QGridLayout* opsLayout = new QGridLayout(opsGroup);
    
    QLineEdit* indexInput = new QLineEdit();
    indexInput->setPlaceholderText("Index");
    QLineEdit* valueInput = new QLineEdit();
    valueInput->setPlaceholderText("Value");
    QLineEdit* sizeInput = new QLineEdit();
    sizeInput->setPlaceholderText("New size");
    
    QPushButton* setBtn = new QPushButton("Set");
    QPushButton* getBtn = new QPushButton("Get");
    QPushButton* resizeBtn = new QPushButton("Resize");
    QPushButton* createBtn = new QPushButton("Create New");
    
    opsLayout->addWidget(indexInput, 0, 0);
    opsLayout->addWidget(valueInput, 0, 1);
    opsLayout->addWidget(setBtn, 0, 2);
    opsLayout->addWidget(getBtn, 0, 3);
    opsLayout->addWidget(sizeInput, 1, 0);
    opsLayout->addWidget(resizeBtn, 1, 1);
    opsLayout->addWidget(createBtn, 1, 2);
    
    layout->addWidget(opsGroup);
    layout->addStretch();
    
    // Signal connections
    connect(setBtn, &QPushButton::clicked, [this, indexInput, valueInput]() {
        if (!indexInput->text().isEmpty() && !valueInput->text().isEmpty()) {
            try {
                currentDynamicArray->Set(indexInput->text().toInt(), valueInput->text().toInt());
                displayDynamicArray();
                updateOutput("DynamicArray Set(" + indexInput->text() + ", " + 
                           valueInput->text() + ")");
            } catch (const std::exception& e) {
                updateOutput("Error: " + QString(e.what()));
            }
            indexInput->clear();
            valueInput->clear();
        }
    });
    
    connect(getBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                int val = currentDynamicArray->Get(indexInput->text().toInt());
                updateOutput("DynamicArray Get(" + indexInput->text() + ") = " + QString::number(val));
            } catch (const std::exception& e) {
                updateOutput("Error: " + QString(e.what()));
            }
            indexInput->clear();
        }
    });
    
    connect(resizeBtn, &QPushButton::clicked, [this, sizeInput]() {
        if (!sizeInput->text().isEmpty()) {
            try {
                currentDynamicArray->Resize(sizeInput->text().toInt());
                displayDynamicArray();
                updateOutput("DynamicArray Resize(" + sizeInput->text() + ")");
            } catch (const std::exception& e) {
                updateOutput("Error: " + QString(e.what()));
            }
            sizeInput->clear();
        }
    });
    
    connect(createBtn, &QPushButton::clicked, [this, sizeInput]() {
        int size = sizeInput->text().isEmpty() ? 5 : sizeInput->text().toInt();
        delete currentDynamicArray;
        currentDynamicArray = new DynamicArray<int>(size);
        for (int i = 0; i < size; i++) {
            currentDynamicArray->Set(i, (i + 1) * 10);
        }
        displayDynamicArray();
        updateOutput("Created new DynamicArray of size " + QString::number(size));
        sizeInput->clear();
    });
    
    return tab;
}

QWidget* MainWindow::createLinkedListTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);
    
    // Current state view
    QGroupBox* viewGroup = new QGroupBox("Current LinkedList");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    linkedDisplay = new QTextEdit();
    linkedDisplay->setReadOnly(true);
    linkedDisplay->setMaximumHeight(100);
    viewLayout->addWidget(linkedDisplay);
    layout->addWidget(viewGroup);
    
    // Operations
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
    
    opsLayout->addWidget(valueInput, 0, 0);
    opsLayout->addWidget(appendBtn, 0, 1);
    opsLayout->addWidget(prependBtn, 0, 2);
    opsLayout->addWidget(indexInput, 1, 0);
    opsLayout->addWidget(insertBtn, 1, 1);
    opsLayout->addWidget(getBtn, 1, 2);
    opsLayout->addWidget(startInput, 2, 0);
    opsLayout->addWidget(endInput, 2, 1);
    opsLayout->addWidget(sublistBtn, 2, 2);
    
    layout->addWidget(opsGroup);
    layout->addStretch();
    
    // Signal connections
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
                updateOutput("LinkedList InsertAt(" + valueInput->text() + ", " + 
                           indexInput->text() + ")");
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
    
    connect(sublistBtn, &QPushButton::clicked, [this, startInput, endInput]() {
        if (!startInput->text().isEmpty() && !endInput->text().isEmpty()) {
            try {
                auto* sublist = currentLinkedList->GetSubList(
                    startInput->text().toInt(), 
                    endInput->text().toInt()
                );
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

void MainWindow::displayDynamicArray()
{
    if (dynamicDisplay && currentDynamicArray) {
        QString text = "[";
        for (int i = 0; i < currentDynamicArray->GetSize(); i++) {
            text += QString::number(currentDynamicArray->Get(i));
            if (i < currentDynamicArray->GetSize() - 1) text += ", ";
        }
        text += "] (size: " + QString::number(currentDynamicArray->GetSize()) + ")";
        dynamicDisplay->setText(text);
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

void MainWindow::runArraySequenceDemo()
{
    updateOutput("\n=== ArraySequence Demo ===");
    
    ArraySequence<int> seq;
    updateOutput("Created empty ArraySequence");
    
    for (int i = 1; i <= 5; i++) {
        seq.Append(i * 10);
    }
    updateOutput("After Append(10,20,30,40,50):");
    QString items = "";
    for (int i = 0; i < seq.GetLength(); i++) {
        items += QString::number(seq.Get(i)) + " ";
    }
    updateOutput("  " + items);
    
    seq.Prepend(5);
    updateOutput("After Prepend(5):");
    items = "";
    for (int i = 0; i < seq.GetLength(); i++) {
        items += QString::number(seq.Get(i)) + " ";
    }
    updateOutput("  " + items);
    
    seq.InsertAt(99, 3);
    updateOutput("After InsertAt(99, 3):");
    items = "";
    for (int i = 0; i < seq.GetLength(); i++) {
        items += QString::number(seq.Get(i)) + " ";
    }
    updateOutput("  " + items);
    
    updateOutput("GetFirst() = " + QString::number(seq.GetFirst()));
    updateOutput("GetLast() = " + QString::number(seq.GetLast()));
    updateOutput("Get(2) = " + QString::number(seq.Get(2)));
    
    auto* sub = seq.GetSubsequence(2, 5);
    items = "";
    for (int i = 0; i < sub->GetLength(); i++) {
        items += QString::number(sub->Get(i)) + " ";
    }
    updateOutput("GetSubsequence(2,5): " + items);
    delete sub;
    
    auto* mapped = seq.Map<int>([](int x) { return x * 2; });
    items = "";
    for (int i = 0; i < mapped->GetLength(); i++) {
        items += QString::number(mapped->Get(i)) + " ";
    }
    updateOutput("Map(x*2): " + items);
    delete mapped;
    
    auto* filtered = seq.Where([](int x) { return x > 20; });
    items = "";
    for (int i = 0; i < filtered->GetLength(); i++) {
        items += QString::number(filtered->Get(i)) + " ";
    }
    updateOutput("Where(x>20): " + items);
    delete filtered;
    
    int sum = seq.Reduce<int>([](int acc, int x) { return acc + x; }, 0);
    updateOutput("Reduce(sum) = " + QString::number(sum));
    
    Option<int> found = seq.Find([](int x) { return x == 30; });
    if (found.IsSome()) {
        updateOutput("Find(value == 30): found");
    } else {
        updateOutput("Find(value == 30): not found");
    }
    
    updateOutput("=== End of ArraySequence Demo ===\n");
}

void MainWindow::runListSequenceDemo()
{
    updateOutput("\n=== ListSequence Demo ===");
    
    ListSequence<int> seq;
    updateOutput("Created empty ListSequence");
    
    for (int i = 1; i <= 5; i++) {
        seq.Append(i * 5);
    }
    QString items = "";
    for (int i = 0; i < seq.GetLength(); i++) {
        items += QString::number(seq.Get(i)) + " ";
    }
    updateOutput("After Append(5,10,15,20,25): " + items);
    
    seq.Prepend(1);
    items = "";
    for (int i = 0; i < seq.GetLength(); i++) {
        items += QString::number(seq.Get(i)) + " ";
    }
    updateOutput("After Prepend(1): " + items);
    
    seq.InsertAt(100, 3);
    items = "";
    for (int i = 0; i < seq.GetLength(); i++) {
        items += QString::number(seq.Get(i)) + " ";
    }
    updateOutput("After InsertAt(100, 3): " + items);
    
    updateOutput("GetFirst() = " + QString::number(seq.GetFirst()));
    updateOutput("GetLast() = " + QString::number(seq.GetLast()));
    
    updateOutput("=== End of ListSequence Demo ===\n");
}

void MainWindow::runBitSequenceDemo()
{
    updateOutput("\n=== BitSequence Demo ===");
    
    BitSequence bits(16);
    updateOutput("Created BitSequence of size 16 bits");
    
    for (int i = 0; i < 16; i++) {
        bits.SetBit(i, i % 3 == 0);
    }
    
    QString bitsStr = "";
    for (int i = 0; i < bits.GetLength(); i++) {
        bitsStr += QString::number(bits.GetBit(i));
        if ((i + 1) % 8 == 0) bitsStr += " ";
    }
    updateOutput("Bits set: " + bitsStr);
    
    updateOutput("GetBit(0) = " + QString::number(bits.GetBit(0)));
    updateOutput("GetBit(5) = " + QString::number(bits.GetBit(5)));
    
    auto* notBits = bits.Not();
    bitsStr = "";
    for (int i = 0; i < notBits->GetLength(); i++) {
        bitsStr += QString::number(notBits->GetBit(i));
        if ((i + 1) % 8 == 0) bitsStr += " ";
    }
    updateOutput("NOT operation: " + bitsStr);
    delete notBits;
    
    updateOutput("=== End of BitSequence Demo ===\n");
}

void MainWindow::clearOutput()
{
    if (outputTextEdit) {
        outputTextEdit->clear();
    }
}