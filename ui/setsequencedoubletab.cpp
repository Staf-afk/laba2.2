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

QWidget* MainWindow::createSetSequenceDoubleTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);

    QGroupBox* viewGroup = new QGroupBox("Текущее SetSequence<double> (множество вещественных чисел)");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    setDisplayDouble = new QTextEdit();
    setDisplayDouble->setReadOnly(true);
    setDisplayDouble->setMaximumHeight(100);
    viewLayout->addWidget(setDisplayDouble);
    layout->addWidget(viewGroup);
    
    QGroupBox* opsGroup = new QGroupBox("Операции");
    QGridLayout* opsLayout = new QGridLayout(opsGroup);
    
    QLineEdit* valueInput = new QLineEdit();
    valueInput->setPlaceholderText("Значение (вещественное число)");
    QLineEdit* indexInput = new QLineEdit();
    indexInput->setPlaceholderText("Индекс (для Get)");
    QLineEdit* startInput = new QLineEdit();
    startInput->setPlaceholderText("Начало");
    QLineEdit* endInput = new QLineEdit();
    endInput->setPlaceholderText("Конец");
    QLineEdit* createItemsInput = new QLineEdit();
    createItemsInput->setPlaceholderText("Элементы через запятую (1.5,2.7,3.14)");
    
    QPushButton* appendBtn = new QPushButton("Append (добавить)");
    QPushButton* getBtn = new QPushButton("Get (по индексу)");
    QPushButton* subseqBtn = new QPushButton("GetSubsequence");
    QPushButton* concatBtn = new QPushButton("Concat (с копией)");
    QPushButton* mapBtn = new QPushButton("Map (+1 ко всем)");
    QPushButton* whereBtn = new QPushButton("Where (> 0)");
    QPushButton* reduceBtn = new QPushButton("Reduce (сумма)");
    QPushButton* findBtn = new QPushButton("Find (значение == 3.14)");
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
                double val = valueInput->text().toDouble();
                SetSequence<double>* newSet = currentSetSeqDouble->Append(val);
                delete currentSetSeqDouble;
                currentSetSeqDouble = newSet;
                displaySetSequenceDouble();
                updateOutput("Set<double> Append(" + valueInput->text() + ")");
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
                double val = currentSetSeqDouble->Get(index);
                updateOutput("Set<double> Get(" + QString::number(index) + ") = " + QString::number(val));
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
                SetSequence<double>* subseq = currentSetSeqDouble->GetSubsequence(start, end);
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
            SetSequence<double>* copy = new SetSequence<double>();
            for (size_t i = 0; i < currentSetSeqDouble->GetLength(); i++) {
                SetSequence<double>* temp = copy->Append(currentSetSeqDouble->Get(i));
                delete copy;
                copy = temp;
            }
            SetSequence<double>* result = currentSetSeqDouble->Concat(copy);
            updateOutput("Set<double> Concat: создана новая последовательность");
            delete copy;
            delete result;
        } catch (const std::exception& e) {
            updateOutput("Ошибка: " + QString(e.what()));
        }
    });
    
    connect(mapBtn, &QPushButton::clicked, [this]() {
        if (currentSetSeqDouble->GetLength() > 0) {
            try {
                SetSequence<double>* result = currentSetSeqDouble->Map([](double x) { return x + 1.0; });
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
        if (currentSetSeqDouble->GetLength() > 0) {
            try {
                SetSequence<double>* result = currentSetSeqDouble->Where([](double x) { return x > 0; });
                QString res = "Положительные числа: {";
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
        if (currentSetSeqDouble->GetLength() > 0) {
            try {
                double sum = currentSetSeqDouble->Reduce([](double a, double b) { return a + b; }, 0.0);
                updateOutput("Сумма всех элементов = " + QString::number(sum));
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
        }
    });
    
    connect(findBtn, &QPushButton::clicked, [this]() {
        Option<double> found = currentSetSeqDouble->Find([](double x) { return std::abs(x - 3.14) < 0.001; });
        if (found.IsSome()) {
            updateOutput("Найдено значение 3.14");
        } else {
            updateOutput("Значение 3.14 не найдено");
        }
    });
    
    connect(createBtn, &QPushButton::clicked, [this, createItemsInput]() {
        if (!createItemsInput->text().isEmpty()) {
            try {
                QStringList parts = createItemsInput->text().split(',');
                std::vector<double> items;
                for (const QString& part : parts) {
                    items.push_back(part.trimmed().toDouble());
                }
                delete currentSetSeqDouble;
                currentSetSeqDouble = new SetSequence<double>(items.data(), items.size());
                displaySetSequenceDouble();
                updateOutput("Создано новое множество из: {" + createItemsInput->text() + "}");
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            createItemsInput->clear();
        } else {
            delete currentSetSeqDouble;
            currentSetSeqDouble = new SetSequence<double>();
            displaySetSequenceDouble();
            updateOutput("Создано пустое множество");
        }
    });
    
    connect(removeAtBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t index = indexInput->text().toInt();
                if (index < currentSetSeqDouble->GetLength()) {
                    SetSequence<double>* newSet = new SetSequence<double>();
                    for (size_t i = 0; i < currentSetSeqDouble->GetLength(); i++) {
                        if (i != index) {
                            SetSequence<double>* temp = newSet->Append(currentSetSeqDouble->Get(i));
                            delete newSet;
                            newSet = temp;
                        }
                    }
                    delete currentSetSeqDouble;
                    currentSetSeqDouble = newSet;
                    displaySetSequenceDouble();
                    updateOutput("Удалён элемент с индексом " + QString::number(index));
                }
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            indexInput->clear();
        }
    });
    
    connect(clearBtn, &QPushButton::clicked, [this]() {
        delete currentSetSeqDouble;
        currentSetSeqDouble = new SetSequence<double>();
        displaySetSequenceDouble();
        updateOutput("Множество очищено");
    });
    
    return tab;
}

