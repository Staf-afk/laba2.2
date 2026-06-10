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

QWidget* MainWindow::createSetSequenceStringTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);

    QGroupBox* viewGroup = new QGroupBox("Текущее SetSequence<QString> (множество строк)");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    setDisplayString = new QTextEdit();
    setDisplayString->setReadOnly(true);
    setDisplayString->setMaximumHeight(100);
    viewLayout->addWidget(setDisplayString);
    layout->addWidget(viewGroup);
    
    QGroupBox* opsGroup = new QGroupBox("Операции");
    QGridLayout* opsLayout = new QGridLayout(opsGroup);
    
    QLineEdit* valueInput = new QLineEdit();
    valueInput->setPlaceholderText("Значение (строка)");
    QLineEdit* indexInput = new QLineEdit();
    indexInput->setPlaceholderText("Индекс (для Get)");
    QLineEdit* startInput = new QLineEdit();
    startInput->setPlaceholderText("Начало");
    QLineEdit* endInput = new QLineEdit();
    endInput->setPlaceholderText("Конец");
    QLineEdit* createItemsInput = new QLineEdit();
    createItemsInput->setPlaceholderText("Элементы через запятую (hello,world,cpp)");
    
    QPushButton* appendBtn = new QPushButton("Append (добавить)");
    QPushButton* getBtn = new QPushButton("Get (по индексу)");
    QPushButton* subseqBtn = new QPushButton("GetSubsequence");
    QPushButton* concatBtn = new QPushButton("Concat (с копией)");
    QPushButton* mapBtn = new QPushButton("Map (toUpper)");
    QPushButton* whereBtn = new QPushButton("Where (длина > 3)");
    QPushButton* reduceBtn = new QPushButton("Reduce (конкатенация)");
    QPushButton* findBtn = new QPushButton("Find (значение == \"hello\")");
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
                QString val = valueInput->text();
                SetSequence<QString>* newSet = currentSetSeqString->Append(val);
                delete currentSetSeqString;
                currentSetSeqString = newSet;
                displaySetSequenceString();
                updateOutput("Set<QString> Append(" + val + ")");
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
                QString val = currentSetSeqString->Get(index);
                updateOutput("Set<QString> Get(" + QString::number(index) + ") = " + val);
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
                SetSequence<QString>* subseq = currentSetSeqString->GetSubsequence(start, end);
                QString result = "Подмножество [" + QString::number(start) + "-" + QString::number(end) + "]: {";
                for (size_t i = 0; i < subseq->GetLength(); i++) {
                    result += subseq->Get(i);
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
            SetSequence<QString>* copy = new SetSequence<QString>();
            for (size_t i = 0; i < currentSetSeqString->GetLength(); i++) {
                SetSequence<QString>* temp = copy->Append(currentSetSeqString->Get(i));
                delete copy;
                copy = temp;
            }
            SetSequence<QString>* result = currentSetSeqString->Concat(copy);
            updateOutput("Set<QString> Concat: создана новая последовательность");
            delete copy;
            delete result;
        } catch (const std::exception& e) {
            updateOutput("Ошибка: " + QString(e.what()));
        }
    });
    
    connect(mapBtn, &QPushButton::clicked, [this]() {
        if (currentSetSeqString->GetLength() > 0) {
            try {
                SetSequence<QString>* result = currentSetSeqString->Map([](QString x) { return x.toUpper(); });
                QString res = "Map (toUpper): {";
                for (size_t i = 0; i < result->GetLength(); i++) {
                    res += result->Get(i);
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
        if (currentSetSeqString->GetLength() > 0) {
            try {
                SetSequence<QString>* result = currentSetSeqString->Where([](QString x) { return x.length() > 3; });
                QString res = "Строки длиннее 3 символов: {";
                for (size_t i = 0; i < result->GetLength(); i++) {
                    res += result->Get(i);
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
        if (currentSetSeqString->GetLength() > 0) {
            try {
                QString result = currentSetSeqString->Reduce([](QString a, QString b) { return a + b; }, QString(""));
                updateOutput("Конкатенация всех строк = " + result);
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
        }
    });
    
    connect(findBtn, &QPushButton::clicked, [this]() {
        Option<QString> found = currentSetSeqString->Find([](QString x) { return x == "hello"; });
        if (found.IsSome()) {
            updateOutput("Найдена строка \"hello\"");
        } else {
            updateOutput("Строка \"hello\" не найдена");
        }
    });
    
    connect(createBtn, &QPushButton::clicked, [this, createItemsInput]() {
        if (!createItemsInput->text().isEmpty()) {
            try {
                QStringList parts = createItemsInput->text().split(',');
                std::vector<QString> items;
                for (const QString& part : parts) {
                    items.push_back(part.trimmed());
                }
                delete currentSetSeqString;
                currentSetSeqString = new SetSequence<QString>(items.data(), items.size());
                displaySetSequenceString();
                updateOutput("Создано новое множество из: {" + createItemsInput->text() + "}");
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            createItemsInput->clear();
        } else {
            delete currentSetSeqString;
            currentSetSeqString = new SetSequence<QString>();
            displaySetSequenceString();
            updateOutput("Создано пустое множество");
        }
    });
    
    connect(removeAtBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t index = indexInput->text().toInt();
                if (index < currentSetSeqString->GetLength()) {
                    SetSequence<QString>* newSet = new SetSequence<QString>();
                    for (size_t i = 0; i < currentSetSeqString->GetLength(); i++) {
                        if (i != index) {
                            SetSequence<QString>* temp = newSet->Append(currentSetSeqString->Get(i));
                            delete newSet;
                            newSet = temp;
                        }
                    }
                    delete currentSetSeqString;
                    currentSetSeqString = newSet;
                    displaySetSequenceString();
                    updateOutput("Удалён элемент с индексом " + QString::number(index));
                }
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            indexInput->clear();
        }
    });
    
    connect(clearBtn, &QPushButton::clicked, [this]() {
        delete currentSetSeqString;
        currentSetSeqString = new SetSequence<QString>();
        displaySetSequenceString();
        updateOutput("Множество очищено");
    });
    
    return tab;
}

