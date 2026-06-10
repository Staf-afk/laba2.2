#include "mainwindow.hpp"
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QString>
#include <exception>

// Примеры функций для демонстрации
int square(int x) { return x * x; }
int doubleVal(int x) { return x * 2; }
int increment(int x) { return x + 1; }
int decrement(int x) { return x - 1; }

QString functionToString(const FunctionWrapper<int>& f) {
    return QString::fromStdString(f.GetName());
}

QWidget* MainWindow::createSetSequenceFunctionTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);

    QGroupBox* viewGroup = new QGroupBox("Текущее SetSequence<FunctionWrapper<int>> (множество функций)");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    setDisplayFunction = new QTextEdit();
    setDisplayFunction->setReadOnly(true);
    setDisplayFunction->setMaximumHeight(100);
    viewLayout->addWidget(setDisplayFunction);
    layout->addWidget(viewGroup);
    
    QGroupBox* opsGroup = new QGroupBox("Операции");
    QGridLayout* opsLayout = new QGridLayout(opsGroup);
    
    QComboBox* functionSelector = new QComboBox();
    functionSelector->addItems({"square", "double", "increment", "decrement"});
    QLineEdit* indexInput = new QLineEdit();
    indexInput->setPlaceholderText("Индекс (для Get)");
    QLineEdit* startInput = new QLineEdit();
    startInput->setPlaceholderText("Начало");
    QLineEdit* endInput = new QLineEdit();
    endInput->setPlaceholderText("Конец");
    
    QPushButton* appendBtn = new QPushButton("Append (добавить функцию)");
    QPushButton* getBtn = new QPushButton("Get (по индексу)");
    QPushButton* subseqBtn = new QPushButton("GetSubsequence");
    QPushButton* concatBtn = new QPushButton("Concat (с копией)");
    QPushButton* createBtn = new QPushButton("Создать новое множество");
    QPushButton* removeAtBtn = new QPushButton("RemoveAt (удалить по индексу)");
    QPushButton* clearBtn = new QPushButton("Очистить множество");
    QPushButton* testFuncBtn = new QPushButton("Протестировать функцию (вызвать с x=5)");
    
    opsLayout->addWidget(functionSelector, 0, 0);
    opsLayout->addWidget(appendBtn, 0, 1);
    opsLayout->addWidget(createBtn, 0, 2);
    
    opsLayout->addWidget(indexInput, 1, 0);
    opsLayout->addWidget(getBtn, 1, 1);
    opsLayout->addWidget(removeAtBtn, 1, 2);
    
    opsLayout->addWidget(startInput, 2, 0);
    opsLayout->addWidget(endInput, 2, 1);
    opsLayout->addWidget(subseqBtn, 2, 2);
    
    opsLayout->addWidget(concatBtn, 3, 0);
    opsLayout->addWidget(testFuncBtn, 3, 1);
    opsLayout->addWidget(clearBtn, 3, 2);
    
    layout->addWidget(opsGroup);
    layout->addStretch();

    connect(appendBtn, &QPushButton::clicked, [this, functionSelector]() {
        try {
            FunctionWrapper<int> newFunc;
            QString funcName = functionSelector->currentText();
            if (funcName == "square") {
                newFunc = FunctionWrapper<int>(square, "square");
            } else if (funcName == "double") {
                newFunc = FunctionWrapper<int>(doubleVal, "double");
            } else if (funcName == "increment") {
                newFunc = FunctionWrapper<int>(increment, "increment");
            } else {
                newFunc = FunctionWrapper<int>(decrement, "decrement");
            }
            
            SetSequence<FunctionWrapper<int>>* newSet = currentSetSeqFunction->Append(newFunc);
            delete currentSetSeqFunction;
            currentSetSeqFunction = newSet;
            displaySetSequenceFunction();
            updateOutput("Set<Function> Append(" + funcName + ")");
        } catch (const std::exception& e) {
            updateOutput("Ошибка: " + QString(e.what()));
        }
    });
    
    connect(getBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t index = indexInput->text().toInt();
                FunctionWrapper<int> val = currentSetSeqFunction->Get(index);
                updateOutput("Set<Function> Get(" + QString::number(index) + ") = " + functionToString(val));
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            indexInput->clear();
        }
    });
    
    connect(subseqBtn, &QPushButton::clicked, [this, startInput, endInput]() {
        if (!startInput->text().isEmpty() && !endInput->text().isEmpty()) {
            try {
                size_t start = startInput->text().toInt();
                size_t end = endInput->text().toInt();
                SetSequence<FunctionWrapper<int>>* subseq = currentSetSeqFunction->GetSubsequence(start, end);
                QString result = "Подмножество [" + QString::number(start) + "-" + QString::number(end) + "]: {";
                for (size_t i = 0; i < subseq->GetLength(); i++) {
                    result += functionToString(subseq->Get(i));
                    if (i < subseq->GetLength() - 1) result += ", ";
                }
                result += "}";
                updateOutput(result);
                delete subseq;
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            startInput->clear();
            endInput->clear();
        }
    });
    
    connect(concatBtn, &QPushButton::clicked, [this]() {
        try {
            SetSequence<FunctionWrapper<int>>* copy = new SetSequence<FunctionWrapper<int>>();
            for (size_t i = 0; i < currentSetSeqFunction->GetLength(); i++) {
                SetSequence<FunctionWrapper<int>>* temp = copy->Append(currentSetSeqFunction->Get(i));
                delete copy;
                copy = temp;
            }
            SetSequence<FunctionWrapper<int>>* result = currentSetSeqFunction->Concat(copy);
            updateOutput("Set<Function> Concat: создана новая последовательность");
            delete copy;
            delete result;
        } catch (const std::exception& e) {
            updateOutput("Ошибка: " + QString(e.what()));
        }
    });
    
    connect(testFuncBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t index = indexInput->text().toInt();
                FunctionWrapper<int> func = currentSetSeqFunction->Get(index);
                int result = func(5);
                updateOutput("Вызов функции " + functionToString(func) + "(5) = " + QString::number(result));
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
        } else {
            updateOutput("Введите индекс функции");
        }
    });
    
    connect(createBtn, &QPushButton::clicked, [this]() {
        delete currentSetSeqFunction;
        currentSetSeqFunction = new SetSequence<FunctionWrapper<int>>();
        displaySetSequenceFunction();
        updateOutput("Создано пустое множество функций");
    });
    
    connect(removeAtBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t index = indexInput->text().toInt();
                if (index < currentSetSeqFunction->GetLength()) {
                    SetSequence<FunctionWrapper<int>>* newSet = new SetSequence<FunctionWrapper<int>>();
                    for (size_t i = 0; i < currentSetSeqFunction->GetLength(); i++) {
                        if (i != index) {
                            SetSequence<FunctionWrapper<int>>* temp = newSet->Append(currentSetSeqFunction->Get(i));
                            delete newSet;
                            newSet = temp;
                        }
                    }
                    delete currentSetSeqFunction;
                    currentSetSeqFunction = newSet;
                    displaySetSequenceFunction();
                    updateOutput("Удалён элемент с индексом " + QString::number(index));
                }
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            indexInput->clear();
        }
    });
    
    connect(clearBtn, &QPushButton::clicked, [this]() {
        delete currentSetSeqFunction;
        currentSetSeqFunction = new SetSequence<FunctionWrapper<int>>();
        displaySetSequenceFunction();
        updateOutput("Множество очищено");
    });
    
    return tab;
}

