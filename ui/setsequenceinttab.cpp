#include "mainwindow.hpp"
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <exception>

QWidget* MainWindow::createSetSequenceIntTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);

    QGroupBox* viewGroup = new QGroupBox("Текущее SetSequence<int> (множество целых чисел)");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    setDisplayInt = new QTextEdit();
    setDisplayInt->setReadOnly(true);
    setDisplayInt->setMaximumHeight(100);
    viewLayout->addWidget(setDisplayInt);
    layout->addWidget(viewGroup);
    
    QGroupBox* opsGroup = new QGroupBox("Операции");
    QGridLayout* opsLayout = new QGridLayout(opsGroup);
    
    QLineEdit* valueInput = new QLineEdit();
    valueInput->setPlaceholderText("Значение (целое число)");
    QLineEdit* indexInput = new QLineEdit();
    indexInput->setPlaceholderText("Индекс (для Get)");
    QLineEdit* startInput = new QLineEdit();
    startInput->setPlaceholderText("Начало");
    QLineEdit* endInput = new QLineEdit();
    endInput->setPlaceholderText("Конец");
    QLineEdit* createItemsInput = new QLineEdit();
    createItemsInput->setPlaceholderText("Элементы через запятую (1,2,3)");
    
    QPushButton* appendBtn = new QPushButton("Append (добавить)");
    QPushButton* getBtn = new QPushButton("Get (по индексу)");
    QPushButton* subseqBtn = new QPushButton("GetSubsequence");
    QPushButton* concatBtn = new QPushButton("Concat (с копией)");
    QPushButton* mapBtn = new QPushButton("Map (+1 ко всем)");
    QPushButton* whereBtn = new QPushButton("Where (чётные числа)");
    QPushButton* reduceBtn = new QPushButton("Reduce (сумма)");
    QPushButton* findBtn = new QPushButton("Find (значение == 3)");
    QPushButton* createBtn = new QPushButton("Создать новое множество");
    QPushButton* removeAtBtn = new QPushButton("RemoveAt (удалить по индексу)");
    QPushButton* clearBtn = new QPushButton("Очистить множество");
    
    opsLayout->addWidget(valueInput, 0, 0);
    opsLayout->addWidget(appendBtn, 0, 1);
    opsLayout->addWidget(createBtn, 0, 2);
    
    opsLayout->addWidget(indexInput, 1, 0);
    opsLayout->addWidget(getBtn, 1, 1);
    opsLayout->addWidget(removeAtBtn, 1, 2);
    
    opsLayout->addWidget(startInput, 2, 0);
    opsLayout->addWidget(endInput, 2, 1);
    opsLayout->addWidget(subseqBtn, 2, 2);
    
    opsLayout->addWidget(concatBtn, 3, 0);
    opsLayout->addWidget(mapBtn, 3, 1);
    opsLayout->addWidget(whereBtn, 3, 2);
    
    opsLayout->addWidget(reduceBtn, 4, 0);
    opsLayout->addWidget(findBtn, 4, 1);
    opsLayout->addWidget(clearBtn, 4, 2);
    
    opsLayout->addWidget(createItemsInput, 5, 0, 1, 3);
    
    layout->addWidget(opsGroup);
    layout->addStretch();

    connect(appendBtn, &QPushButton::clicked, [this, valueInput]() {
        if (!valueInput->text().isEmpty()) {
            try {
                int val = valueInput->text().toInt();
                SetSequence<int>* newSet = currentSetSeqInt->Append(val);
                delete currentSetSeqInt;
                currentSetSeqInt = newSet;
                displaySetSequenceInt();
                updateOutput("Set<int> Append(" + QString::number(val) + ")");
                valueInput->clear();
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
        }
    });
    
    connect(getBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t index = indexInput->text().toInt();
                int val = currentSetSeqInt->Get(index);
                updateOutput("Set<int> Get(" + QString::number(index) + ") = " + QString::number(val));
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
                SetSequence<int>* subseq = currentSetSeqInt->GetSubsequence(start, end);
                QString result = "Подмножество [" + QString::number(start) + "-" + QString::number(end) + "]: {";
                for (size_t i = 0; i < subseq->GetLength(); i++) {
                    result += QString::number(subseq->Get(i));
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
            SetSequence<int>* copy = new SetSequence<int>();
            for (size_t i = 0; i < currentSetSeqInt->GetLength(); i++) {
                SetSequence<int>* temp = copy->Append(currentSetSeqInt->Get(i));
                delete copy;
                copy = temp;
            }
            SetSequence<int>* result = currentSetSeqInt->Concat(copy);
            updateOutput("Set<int> Concat: создана новая последовательность");
            delete copy;
            delete result;
        } catch (const std::exception& e) {
            updateOutput("Ошибка: " + QString(e.what()));
        }
    });
    
    connect(mapBtn, &QPushButton::clicked, [this]() {
        if (currentSetSeqInt->GetLength() > 0) {
            try {
                SetSequence<int>* result = currentSetSeqInt->Map([](int x) { return x + 1; });
                QString res = "Map (+1): {";
                for (size_t i = 0; i < result->GetLength(); i++) {
                    res += QString::number(result->Get(i));
                    if (i < result->GetLength() - 1) res += ", ";
                }
                res += "}";
                updateOutput(res);
                delete result;
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
        }
    });
    
    connect(whereBtn, &QPushButton::clicked, [this]() {
        if (currentSetSeqInt->GetLength() > 0) {
            try {
                SetSequence<int>* result = currentSetSeqInt->Where([](int x) { return x % 2 == 0; });
                QString res = "Чётные числа: {";
                for (size_t i = 0; i < result->GetLength(); i++) {
                    res += QString::number(result->Get(i));
                    if (i < result->GetLength() - 1) res += ", ";
                }
                res += "}";
                updateOutput(res);
                delete result;
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
        }
    });
    
    connect(reduceBtn, &QPushButton::clicked, [this]() {
        if (currentSetSeqInt->GetLength() > 0) {
            try {
                int sum = currentSetSeqInt->Reduce([](int a, int b) { return a + b; }, 0);
                updateOutput("Сумма всех элементов = " + QString::number(sum));
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
        }
    });
    
    connect(findBtn, &QPushButton::clicked, [this]() {
        Option<int> found = currentSetSeqInt->Find([](int x) { return x == 3; });
        if (found.IsSome()) {
            updateOutput("Найдено значение 3");
        } else {
            updateOutput("Значение 3 не найдено");
        }
    });
    
    connect(createBtn, &QPushButton::clicked, [this, createItemsInput]() {
        if (!createItemsInput->text().isEmpty()) {
            try {
                QStringList parts = createItemsInput->text().split(',');
                std::vector<int> items;
                for (const QString& part : parts) {
                    items.push_back(part.trimmed().toInt());
                }
                delete currentSetSeqInt;
                currentSetSeqInt = new SetSequence<int>(items.data(), items.size());
                displaySetSequenceInt();
                updateOutput("Создано новое множество из: {" + createItemsInput->text() + "}");
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            createItemsInput->clear();
        } else {
            delete currentSetSeqInt;
            currentSetSeqInt = new SetSequence<int>();
            displaySetSequenceInt();
            updateOutput("Создано пустое множество");
        }
    });
    
    connect(removeAtBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t index = indexInput->text().toInt();
                if (index < currentSetSeqInt->GetLength()) {
                    SetSequence<int>* newSet = new SetSequence<int>();
                    for (size_t i = 0; i < currentSetSeqInt->GetLength(); i++) {
                        if (i != index) {
                            SetSequence<int>* temp = newSet->Append(currentSetSeqInt->Get(i));
                            delete newSet;
                            newSet = temp;
                        }
                    }
                    delete currentSetSeqInt;
                    currentSetSeqInt = newSet;
                    displaySetSequenceInt();
                    updateOutput("Удалён элемент с индексом " + QString::number(index));
                }
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            indexInput->clear();
        }
    });
    
    connect(clearBtn, &QPushButton::clicked, [this]() {
        delete currentSetSeqInt;
        currentSetSeqInt = new SetSequence<int>();
        displaySetSequenceInt();
        updateOutput("Множество очищено");
    });
    
    return tab;
}

