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

QWidget* MainWindow::createArraySequenceTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);
    QGroupBox* viewGroup = new QGroupBox("Текущий ArraySequence");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    arrayDisplay = new QTextEdit();
    arrayDisplay->setReadOnly(true);
    arrayDisplay->setMaximumHeight(100);
    viewLayout->addWidget(arrayDisplay);
    layout->addWidget(viewGroup);
    QGroupBox* opsGroup = new QGroupBox("Операции");
    QGridLayout* opsLayout = new QGridLayout(opsGroup);
    QLineEdit* valueInput = new QLineEdit();
    valueInput->setPlaceholderText("Значение");
    QLineEdit* indexInput = new QLineEdit();
    indexInput->setPlaceholderText("Индекс");
    QLineEdit* startInput = new QLineEdit();
    startInput->setPlaceholderText("Начало");
    QLineEdit* endInput = new QLineEdit();
    endInput->setPlaceholderText("Конец");
    QPushButton* appendBtn = new QPushButton("Append");
    QPushButton* prependBtn = new QPushButton("Prepend");
    QPushButton* insertBtn = new QPushButton("InsertAt");
    QPushButton* getBtn = new QPushButton("Get");
    QPushButton* subseqBtn = new QPushButton("GetSubsequence");
    QPushButton* concatBtn = new QPushButton("Concat (с копией)");
    QPushButton* mapBtn = new QPushButton("Map (+1 ко всем)");
    QPushButton* whereBtn = new QPushButton("Where (чётные числа)");
    QPushButton* reduceBtn = new QPushButton("Reduce (сумма)");
    QPushButton* findBtn = new QPushButton("Find (значение == 3)");
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
                currentArraySeq->InsertAt(valueInput->text().toInt(), static_cast<size_t>(indexInput->text().toInt()));
                displayArraySequence();
                updateOutput("InsertAt(" + valueInput->text() + ", " + indexInput->text() + ")");
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            valueInput->clear();
            indexInput->clear();
        }
    });
    connect(getBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                int val = currentArraySeq->Get(static_cast<size_t>(indexInput->text().toInt()));
                updateOutput("Get(" + indexInput->text() + ") = " + QString::number(val));
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            indexInput->clear();
        }
    });
    connect(removeAtBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t index = static_cast<size_t>(indexInput->text().toInt());
                ArraySequence<int>* newSeq = new ArraySequence<int>();
                for (size_t i = 0; i < static_cast<size_t>(currentArraySeq->GetLength()); i++) {
                    if (i != index) newSeq->Append(currentArraySeq->Get(i));
                }
                delete currentArraySeq;
                currentArraySeq = newSeq;
                displayArraySequence();
                updateOutput("RemoveAt(" + QString::number(index) + ")");
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            indexInput->clear();
        }
    });
    connect(removeFirstBtn, &QPushButton::clicked, [this]() {
        if (currentArraySeq->GetLength() > 0) {
            try {
                ArraySequence<int>* newSeq = new ArraySequence<int>();
                for (size_t i = 1; i < static_cast<size_t>(currentArraySeq->GetLength()); i++) {
                    newSeq->Append(currentArraySeq->Get(i));
                }
                delete currentArraySeq;
                currentArraySeq = newSeq;
                displayArraySequence();
                updateOutput("RemoveFirst()");
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
        } else {
            updateOutput("RemoveFirst: последовательность пуста");
        }
    });
    connect(removeLastBtn, &QPushButton::clicked, [this]() {
        if (currentArraySeq->GetLength() > 0) {
            try {
                ArraySequence<int>* newSeq = new ArraySequence<int>();
                for (size_t i = 0; i < static_cast<size_t>(currentArraySeq->GetLength()) - 1; i++) {
                    newSeq->Append(currentArraySeq->Get(i));
                }
                delete currentArraySeq;
                currentArraySeq = newSeq;
                displayArraySequence();
                updateOutput("RemoveLast()");
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
        } else {
            updateOutput("RemoveLast: последовательность пуста");
        }
    });
    connect(subseqBtn, &QPushButton::clicked, [this, startInput, endInput]() {
        if (!startInput->text().isEmpty() && !endInput->text().isEmpty()) {
            try {
                auto* subseq = currentArraySeq->GetSubsequence(static_cast<size_t>(startInput->text().toInt()), static_cast<size_t>(endInput->text().toInt()));
                QString result = "Подпоследовательность [";
                for (size_t i = 0; i < static_cast<size_t>(subseq->GetLength()); i++) {
                    result += QString::number(subseq->Get(i));
                    if (i < subseq->GetLength() - 1) result += ", ";
                }
                result += "]";
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
        auto* copy = new ArraySequence<int>();
        for (size_t i = 0; i < static_cast<size_t>(currentArraySeq->GetLength()); i++) copy->Append(currentArraySeq->Get(i));
        auto* result = currentArraySeq->Concat(copy);
        updateOutput("Concat: создана новая последовательность с дубликатом");
        delete copy; delete result;
    });
    connect(mapBtn, &QPushButton::clicked, [this]() {
        if (currentArraySeq->GetLength() > 0) {
            auto* result = currentArraySeq->Map();
            QString res = "Map (+1): [";
            for (size_t i = 0; i < static_cast<size_t>(result->GetLength()); i++) {
                res += QString::number(result->Get(i));
                if (i < result->GetLength() - 1) res += ", ";
            }
            res += "]"; updateOutput(res); delete result;
        } else { updateOutput("Map: последовательность пуста"); }
    });
    connect(whereBtn, &QPushButton::clicked, [this]() {
        if (currentArraySeq->GetLength() > 0) {
            auto* result = currentArraySeq->Where();
            QString res = "Where (чётные числа): [";
            for (size_t i = 0; i < static_cast<size_t>(result->GetLength()); i++) {
                res += QString::number(result->Get(i));
                if (i < result->GetLength() - 1) res += ", ";
            }
            res += "]"; updateOutput(res); delete result;
        } else { updateOutput("Where: последовательность пуста"); }
    });
    connect(reduceBtn, &QPushButton::clicked, [this]() {
        if (currentArraySeq->GetLength() > 0) {
            int result = currentArraySeq->Reduce();
            updateOutput("Reduce (сумма) = " + QString::number(result));
        } else { updateOutput("Reduce: последовательность пуста, сумма = 0"); }
    });
    connect(findBtn, &QPushButton::clicked, [this]() {
        Option<int> found = currentArraySeq->Find();
        if (found.IsSome()) updateOutput("Find: найдено значение " + QString::number(found.GetValue()));
        else updateOutput("Find: значение 3 не найдено");
    });
    return tab;
}