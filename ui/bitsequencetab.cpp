#include "mainwindow.hpp"
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <exception>

QWidget* MainWindow::createBitSequenceTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);
    
    QGroupBox* viewGroup = new QGroupBox("Текущий BitSequence (упакованный, 1 бит на элемент)");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    bitDisplay = new QTextEdit();
    bitDisplay->setReadOnly(true);
    bitDisplay->setMaximumHeight(120);
    viewLayout->addWidget(bitDisplay);
    layout->addWidget(viewGroup);
    
    QGroupBox* opsGroup = new QGroupBox("Битовые операции");
    QGridLayout* opsLayout = new QGridLayout(opsGroup);
    
    QLineEdit* indexInput = new QLineEdit();
    indexInput->setPlaceholderText("Индекс бита");
    QCheckBox* valueCheck = new QCheckBox("Значение бита (1/0)");
    QLineEdit* startInput = new QLineEdit();
    startInput->setPlaceholderText("Начало");
    QLineEdit* endInput = new QLineEdit();
    endInput->setPlaceholderText("Конец");
    QLineEdit* sizeInput = new QLineEdit();
    sizeInput->setPlaceholderText("Размер");
    QLineEdit* bitsInput = new QLineEdit();
    bitsInput->setPlaceholderText("Биты для установки (например: 10101010)");
    
    QPushButton* setBtn = new QPushButton("SetBit");
    QPushButton* getBtn = new QPushButton("GetBit");
    QPushButton* andBtn = new QPushButton("AND (с копией)");
    QPushButton* orBtn = new QPushButton("OR (с копией)");
    QPushButton* xorBtn = new QPushButton("XOR (с копией)");
    QPushButton* notBtn = new QPushButton("NOT");
    QPushButton* subseqBtn = new QPushButton("GetSubsequence");
    QPushButton* appendBtn = new QPushButton("Append (добавить бит)");
    QPushButton* insertBtn = new QPushButton("InsertAt");
    QPushButton* createBtn = new QPushButton("Создать новый");
    QPushButton* removeAtBtn = new QPushButton("RemoveBitAt");
    QPushButton* removeFirstBtn = new QPushButton("RemoveFirstBit");
    QPushButton* removeLastBtn = new QPushButton("RemoveLastBit");
    QPushButton* setBitsFromStringBtn = new QPushButton("Установить биты из строки");
    
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
    
    opsLayout->addWidget(bitsInput, 5, 0, 1, 2);
    opsLayout->addWidget(setBitsFromStringBtn, 5, 2, 1, 2);
    
    layout->addWidget(opsGroup);
    layout->addStretch();
    
    connect(setBtn, &QPushButton::clicked, [this, indexInput, valueCheck]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t idx = indexInput->text().toInt();
                currentBitSeq->SetBit(idx, valueCheck->isChecked());
                displayBitSequence();
                updateOutput("SetBit(" + QString::number(idx) + ", " + 
                    (valueCheck->isChecked() ? "1" : "0") + ")");
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            indexInput->clear();
        }
    });
    
    connect(getBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t idx = indexInput->text().toInt();
                bool val = currentBitSeq->GetBit(idx);
                updateOutput("GetBit(" + QString::number(idx) + ") = " + QString::number(val));
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            indexInput->clear();
        }
    });
    
    connect(andBtn, &QPushButton::clicked, [this]() {
        try {
            BitSequence copy(*currentBitSeq);
            auto* result = currentBitSeq->And(copy);
            QString res = "AND результат: ";
            for (size_t i = 0; i < result->GetLength(); ++i) {
                res += QString::number(result->GetBit(i));
            }
            updateOutput(res);
            delete result;
        } catch (const std::exception& e) {
            updateOutput("Ошибка: " + QString(e.what()));
        }
    });
    
    connect(orBtn, &QPushButton::clicked, [this]() {
        try {
            BitSequence copy(*currentBitSeq);
            auto* result = currentBitSeq->Or(copy);
            QString res = "OR результат: ";
            for (size_t i = 0; i < result->GetLength(); ++i) {
                res += QString::number(result->GetBit(i));
            }
            updateOutput(res);
            delete result;
        } catch (const std::exception& e) {
            updateOutput("Ошибка: " + QString(e.what()));
        }
    });
    
    connect(xorBtn, &QPushButton::clicked, [this]() {
        try {
            BitSequence copy(*currentBitSeq);
            auto* result = currentBitSeq->Xor(copy);
            QString res = "XOR результат: ";
            for (size_t i = 0; i < result->GetLength(); ++i) {
                res += QString::number(result->GetBit(i));
            }
            updateOutput(res);
            delete result;
        } catch (const std::exception& e) {
            updateOutput("Ошибка: " + QString(e.what()));
        }
    });
    
    connect(notBtn, &QPushButton::clicked, [this]() {
        try {
            auto* result = currentBitSeq->Not();
            QString res = "NOT результат: ";
            for (size_t i = 0; i < result->GetLength(); ++i) {
                res += QString::number(result->GetBit(i));
            }
            updateOutput(res);
            delete result;
        } catch (const std::exception& e) {
            updateOutput("Ошибка: " + QString(e.what()));
        }
    });
    
    connect(subseqBtn, &QPushButton::clicked, [this, startInput, endInput]() {
        if (!startInput->text().isEmpty() && !endInput->text().isEmpty()) {
            try {
                size_t start = startInput->text().toInt();
                size_t end = endInput->text().toInt();
                auto* subseq = currentBitSeq->GetSubsequence(start, end);
                QString res = "Подпоследовательность [" + QString::number(start) + "-" + 
                    QString::number(end) + "]: ";
                for (size_t i = 0; i < subseq->GetLength(); ++i) {
                    res += QString::number(subseq->Get(i));
                }
                updateOutput(res);
                delete subseq;
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            startInput->clear();
            endInput->clear();
        }
    });
    
    connect(appendBtn, &QPushButton::clicked, [this, valueCheck]() {
        try {
            currentBitSeq->Append(valueCheck->isChecked());
            displayBitSequence();
            updateOutput("Append(" + QString::number(valueCheck->isChecked()) + ")");
        } catch (const std::exception& e) {
            updateOutput("Ошибка: " + QString(e.what()));
        }
    });
    
    connect(insertBtn, &QPushButton::clicked, [this, indexInput, valueCheck]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t idx = indexInput->text().toInt();
                currentBitSeq->InsertAt(valueCheck->isChecked(), idx);
                displayBitSequence();
                updateOutput("InsertAt(" + QString::number(valueCheck->isChecked()) + 
                    ", " + indexInput->text() + ")");
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            indexInput->clear();
        }
    });
    
    connect(removeAtBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t idx = indexInput->text().toInt();
                currentBitSeq->RemoveBitAt(idx);
                displayBitSequence();
                updateOutput("RemoveBitAt(" + QString::number(idx) + ")");
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            indexInput->clear();
        }
    });
    
    connect(removeFirstBtn, &QPushButton::clicked, [this]() {
        try {
            if (currentBitSeq->GetLength() > 0) {
                currentBitSeq->RemoveFirstBit();
                displayBitSequence();
                updateOutput("RemoveFirstBit()");
            } else {
                updateOutput("RemoveFirstBit: последовательность пуста");
            }
        } catch (const std::exception& e) {
            updateOutput("Ошибка: " + QString(e.what()));
        }
    });
    
    connect(removeLastBtn, &QPushButton::clicked, [this]() {
        try {
            if (currentBitSeq->GetLength() > 0) {
                currentBitSeq->RemoveLastBit();
                displayBitSequence();
                updateOutput("RemoveLastBit()");
            } else {
                updateOutput("RemoveLastBit: последовательность пуста");
            }
        } catch (const std::exception& e) {
            updateOutput("Ошибка: " + QString(e.what()));
        }
    });
    
    connect(createBtn, &QPushButton::clicked, [this, sizeInput]() {
        size_t size = sizeInput->text().isEmpty() ? 8 : sizeInput->text().toInt();
        delete currentBitSeq;
        currentBitSeq = new BitSequence(size);
        displayBitSequence();
        updateOutput("Создана новая BitSequence размера " + QString::number(size));
        sizeInput->clear();
    });
    
    connect(setBitsFromStringBtn, &QPushButton::clicked, [this, bitsInput]() {
        if (!bitsInput->text().isEmpty()) {
            QString bitsStr = bitsInput->text().trimmed();
            size_t len = bitsStr.length();
            delete currentBitSeq;
            currentBitSeq = new BitSequence(len);
            for (size_t i = 0; i < len; ++i) {
                QChar ch = bitsStr.at(i);
                if (ch == '1') {
                    currentBitSeq->SetBit(i, true);
                } else if (ch == '0') {
                    currentBitSeq->SetBit(i, false);
                }
            }
            displayBitSequence();
            updateOutput("Установлены биты из строки: " + bitsStr);
            bitsInput->clear();
        }
    });
    
    return tab;
}

