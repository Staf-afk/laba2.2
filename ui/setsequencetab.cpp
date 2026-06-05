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

QWidget* MainWindow::createSetSequenceTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);

    QGroupBox* viewGroup = new QGroupBox("Текущее SetSequence (множество)");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    setDisplay = new QTextEdit();
    setDisplay->setReadOnly(true);
    setDisplay->setMaximumHeight(100);
    viewLayout->addWidget(setDisplay);
    layout->addWidget(viewGroup);
    
    QGroupBox* opsGroup = new QGroupBox("Операции");
    QGridLayout* opsLayout = new QGridLayout(opsGroup);
    
    QLineEdit* valueInput = new QLineEdit();
    valueInput->setPlaceholderText("Значение");
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
                SetSequence<int>* newSet = currentSetSeq->Append(val);
                delete currentSetSeq;
                currentSetSeq = newSet;
                displaySetSequence();
                updateOutput("Set Append(" + QString::number(val) + ")");
                valueInput->clear();
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
        } else {
            updateOutput("Ошибка: введите значение");
        }
    });
    
    connect(getBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t index = indexInput->text().toInt();
                int val = currentSetSeq->Get(index);
                updateOutput("Set Get(" + QString::number(index) + ") = " + QString::number(val));
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            indexInput->clear();
        } else {
            updateOutput("Ошибка: введите индекс");
        }
    });
    
    connect(subseqBtn, &QPushButton::clicked, [this, startInput, endInput]() {
        if (!startInput->text().isEmpty() && !endInput->text().isEmpty()) {
            try {
                size_t start = startInput->text().toInt();
                size_t end = endInput->text().toInt();
                SetSequence<int>* subseq = currentSetSeq->GetSubsequence(start, end);
                QString result = "Set подмножество [" + QString::number(start) + "-" + QString::number(end) + "]: {";
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
        } else {
            updateOutput("Ошибка: введите начало и конец");
        }
    });

    connect(concatBtn, &QPushButton::clicked, [this]() {
        try {
            SetSequence<int>* copy = new SetSequence<int>();
            for (size_t i = 0; i < currentSetSeq->GetLength(); i++) {
                SetSequence<int>* temp = copy->Append(currentSetSeq->Get(i));
                delete copy;
                copy = temp;
            }
            SetSequence<int>* result = currentSetSeq->Concat(copy);
            updateOutput("Set Concat: создана новая последовательность (дубликаты удалены)");
            delete copy;
            delete result;
        } catch (const std::exception& e) {
            updateOutput("Ошибка: " + QString(e.what()));
        }
    });
    
    connect(mapBtn, &QPushButton::clicked, [this]() {
        if (currentSetSeq->GetLength() > 0) {
            try {
                SetSequence<int>* result = currentSetSeq->Map();
                QString res = "Set Map (+1 к каждому элементу): {";
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
        } else {
            updateOutput("Set Map: множество пусто");
        }
    });
    
    connect(whereBtn, &QPushButton::clicked, [this]() {
        if (currentSetSeq->GetLength() > 0) {
            try {
                SetSequence<int>* result = currentSetSeq->Where();
                QString res = "Set Where (чётные числа): {";
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
        } else {
            updateOutput("Set Where: множество пусто");
        }
    });
    
    connect(reduceBtn, &QPushButton::clicked, [this]() {
        if (currentSetSeq->GetLength() > 0) {
            try {
                int result = currentSetSeq->Reduce();
                updateOutput("Set Reduce (сумма всех элементов) = " + QString::number(result));
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
        } else {
            updateOutput("Set Reduce: множество пусто, сумма = 0");
        }
    });
    
    connect(findBtn, &QPushButton::clicked, [this]() {
        Option<int> found = currentSetSeq->Find();
        if (found.IsSome()) {
            updateOutput("Set Find(значение == 3): найдено значение " + QString::number(found.GetValue()));
        } else {
            updateOutput("Set Find(значение == 3): значение не найдено");
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
                delete currentSetSeq;
                currentSetSeq = new SetSequence<int>(items.data(), items.size());
                displaySetSequence();
                updateOutput("Создано новое множество из элементов: {" + createItemsInput->text() + "}");
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            createItemsInput->clear();
        } else {
            delete currentSetSeq;
            currentSetSeq = new SetSequence<int>();
            displaySetSequence();
            updateOutput("Создано пустое множество");
        }
    });
    
    connect(removeAtBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t index = indexInput->text().toInt();
                if (index < currentSetSeq->GetLength()) {
                    SetSequence<int>* newSet = new SetSequence<int>();
                    for (size_t i = 0; i < currentSetSeq->GetLength(); i++) {
                        if (i != index) {
                            SetSequence<int>* temp = newSet->Append(currentSetSeq->Get(i));
                            delete newSet;
                            newSet = temp;
                        }
                    }
                    delete currentSetSeq;
                    currentSetSeq = newSet;
                    displaySetSequence();
                    updateOutput("Set RemoveAt(" + QString::number(index) + ")");
                } else {
                    updateOutput("Ошибка: индекс вне диапазона");
                }
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            indexInput->clear();
        } else {
            updateOutput("Ошибка: введите индекс");
        }
    });
    
    connect(clearBtn, &QPushButton::clicked, [this]() {
        delete currentSetSeq;
        currentSetSeq = new SetSequence<int>();
        displaySetSequence();
        updateOutput("Множество очищено");
    });
    
    return tab;
}

