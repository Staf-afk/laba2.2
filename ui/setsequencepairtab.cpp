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

QString pairToString(const Pair<int, QString>& p) {
    return "(" + QString::number(p.GetFirst()) + ", " + p.GetSecond() + ")";
}

QWidget* MainWindow::createSetSequencePairTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);

    QGroupBox* viewGroup = new QGroupBox("Текущее SetSequence<Pair<int, QString>> (множество пар)");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    setDisplayPair = new QTextEdit();
    setDisplayPair->setReadOnly(true);
    setDisplayPair->setMaximumHeight(100);
    viewLayout->addWidget(setDisplayPair);
    layout->addWidget(viewGroup);
    
    QGroupBox* inputGroup = new QGroupBox("Добавление пары");
    QGridLayout* inputLayout = new QGridLayout(inputGroup);
    
    QLineEdit* firstInput = new QLineEdit();
    firstInput->setPlaceholderText("Первое значение (целое число)");
    QLineEdit* secondInput = new QLineEdit();
    secondInput->setPlaceholderText("Второе значение (строка)");
    
    QPushButton* appendPairBtn = new QPushButton("Добавить пару");
    
    inputLayout->addWidget(firstInput, 0, 0);
    inputLayout->addWidget(secondInput, 0, 1);
    inputLayout->addWidget(appendPairBtn, 1, 0, 1, 2);
    
    layout->addWidget(inputGroup);
    
    QGroupBox* opsGroup = new QGroupBox("Операции");
    QGridLayout* opsLayout = new QGridLayout(opsGroup);
    
    QLineEdit* indexInput = new QLineEdit();
    indexInput->setPlaceholderText("Индекс (для Get)");
    QLineEdit* startInput = new QLineEdit();
    startInput->setPlaceholderText("Начало");
    QLineEdit* endInput = new QLineEdit();
    endInput->setPlaceholderText("Конец");
    QLineEdit* createItemsInput = new QLineEdit();
    createItemsInput->setPlaceholderText("Пары через запятую (1:one,2:two,3:three)");
    
    QPushButton* getBtn = new QPushButton("Get (по индексу)");
    QPushButton* subseqBtn = new QPushButton("GetSubsequence");
    QPushButton* concatBtn = new QPushButton("Concat (с копией)");
    QPushButton* createBtn = new QPushButton("Создать новое множество");
    QPushButton* removeAtBtn = new QPushButton("RemoveAt (удалить по индексу)");
    QPushButton* clearBtn = new QPushButton("Очистить множество");
    
    opsLayout->addWidget(indexInput, 0, 0);
    opsLayout->addWidget(getBtn, 0, 1);
    opsLayout->addWidget(removeAtBtn, 0, 2);
    
    opsLayout->addWidget(startInput, 1, 0);
    opsLayout->addWidget(endInput, 1, 1);
    opsLayout->addWidget(subseqBtn, 1, 2);
    
    opsLayout->addWidget(concatBtn, 2, 0);
    opsLayout->addWidget(createBtn, 2, 1);
    opsLayout->addWidget(clearBtn, 2, 2);
    
    opsLayout->addWidget(createItemsInput, 3, 0, 1, 3);
    
    layout->addWidget(opsGroup);
    layout->addStretch();

    connect(appendPairBtn, &QPushButton::clicked, [this, firstInput, secondInput]() {
        if (!firstInput->text().isEmpty() && !secondInput->text().isEmpty()) {
            try {
                int first = firstInput->text().toInt();
                QString second = secondInput->text();
                Pair<int, QString> newPair(first, second);
                
                SetSequence<Pair<int, QString>>* newSet = currentSetSeqPair->Append(newPair);
                delete currentSetSeqPair;
                currentSetSeqPair = newSet;
                displaySetSequencePair();
                updateOutput("Добавлена пара: " + pairToString(newPair));
                
                firstInput->clear();
                secondInput->clear();
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
        }
    });
    
    connect(getBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t index = indexInput->text().toInt();
                Pair<int, QString> val = currentSetSeqPair->Get(index);
                updateOutput("Get(" + QString::number(index) + ") = " + pairToString(val));
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
                SetSequence<Pair<int, QString>>* subseq = currentSetSeqPair->GetSubsequence(start, end);
                QString result = "Подмножество [" + QString::number(start) + "-" + QString::number(end) + "]: {";
                for (size_t i = 0; i < subseq->GetLength(); i++) {
                    result += pairToString(subseq->Get(i));
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
            SetSequence<Pair<int, QString>>* copy = new SetSequence<Pair<int, QString>>();
            for (size_t i = 0; i < currentSetSeqPair->GetLength(); i++) {
                SetSequence<Pair<int, QString>>* temp = copy->Append(currentSetSeqPair->Get(i));
                delete copy;
                copy = temp;
            }
            SetSequence<Pair<int, QString>>* result = currentSetSeqPair->Concat(copy);
            updateOutput("Set<Pair> Concat: создана новая последовательность");
            delete copy;
            delete result;
        } catch (const std::exception& e) {
            updateOutput("Ошибка: " + QString(e.what()));
        }
    });
    
    connect(createBtn, &QPushButton::clicked, [this, createItemsInput]() {
        if (!createItemsInput->text().isEmpty()) {
            try {
                QStringList parts = createItemsInput->text().split(',');
                std::vector<Pair<int, QString>> items;
                for (const QString& part : parts) {
                    QStringList pairParts = part.trimmed().split(':');
                    if (pairParts.size() == 2) {
                        int first = pairParts[0].toInt();
                        QString second = pairParts[1];
                        items.push_back(Pair<int, QString>(first, second));
                    }
                }
                delete currentSetSeqPair;
                currentSetSeqPair = new SetSequence<Pair<int, QString>>(items.data(), items.size());
                displaySetSequencePair();
                updateOutput("Создано новое множество из: {" + createItemsInput->text() + "}");
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            createItemsInput->clear();
        } else {
            delete currentSetSeqPair;
            currentSetSeqPair = new SetSequence<Pair<int, QString>>();
            displaySetSequencePair();
            updateOutput("Создано пустое множество пар");
        }
    });
    
    connect(removeAtBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t index = indexInput->text().toInt();
                if (index < currentSetSeqPair->GetLength()) {
                    SetSequence<Pair<int, QString>>* newSet = new SetSequence<Pair<int, QString>>();
                    for (size_t i = 0; i < currentSetSeqPair->GetLength(); i++) {
                        if (i != index) {
                            SetSequence<Pair<int, QString>>* temp = newSet->Append(currentSetSeqPair->Get(i));
                            delete newSet;
                            newSet = temp;
                        }
                    }
                    delete currentSetSeqPair;
                    currentSetSeqPair = newSet;
                    displaySetSequencePair();
                    updateOutput("Удалён элемент с индексом " + QString::number(index));
                }
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            indexInput->clear();
        }
    });
    
    connect(clearBtn, &QPushButton::clicked, [this]() {
        delete currentSetSeqPair;
        currentSetSeqPair = new SetSequence<Pair<int, QString>>();
        displaySetSequencePair();
        updateOutput("Множество очищено");
    });
    
    return tab;
}


