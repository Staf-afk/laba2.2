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
    QGroupBox* viewGroup = new QGroupBox("Текущий BitSequence");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    bitDisplay = new QTextEdit();
    bitDisplay->setReadOnly(true);
    bitDisplay->setMaximumHeight(100);
    viewLayout->addWidget(bitDisplay);
    layout->addWidget(viewGroup);
    QGroupBox* opsGroup = new QGroupBox("Битовые операции");
    QGridLayout* opsLayout = new QGridLayout(opsGroup);
    QLineEdit* indexInput = new QLineEdit();
    indexInput->setPlaceholderText("Индекс бита");
    QCheckBox* valueCheck = new QCheckBox("Значение бита");
    QLineEdit* startInput = new QLineEdit();
    startInput->setPlaceholderText("Начало");
    QLineEdit* endInput = new QLineEdit();
    endInput->setPlaceholderText("Конец");
    QLineEdit* sizeInput = new QLineEdit();
    sizeInput->setPlaceholderText("Размер");
    QPushButton* setBtn = new QPushButton("SetBit");
    QPushButton* getBtn = new QPushButton("GetBit");
    QPushButton* andBtn = new QPushButton("AND (с копией)");
    QPushButton* orBtn = new QPushButton("OR (с копией)");
    QPushButton* xorBtn = new QPushButton("XOR (с копией)");
    QPushButton* notBtn = new QPushButton("NOT");
    QPushButton* subseqBtn = new QPushButton("GetSubsequence");
    QPushButton* appendBtn = new QPushButton("Append");
    QPushButton* insertBtn = new QPushButton("InsertAt");
    QPushButton* createBtn = new QPushButton("Создать новый");
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
                currentBitSeq->SetBit(static_cast<size_t>(indexInput->text().toInt()), valueCheck->isChecked());
                displayBitSequence();
                updateOutput("Bit SetBit(" + indexInput->text() + ", " + (valueCheck->isChecked() ? "1" : "0") + ")");
            } catch (const std::exception& e) { updateOutput("Ошибка: " + QString(e.what())); }
            indexInput->clear();
        }
    });
    connect(getBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                bool val = currentBitSeq->GetBit(static_cast<size_t>(indexInput->text().toInt()));
                updateOutput("Bit GetBit(" + indexInput->text() + ") = " + QString::number(val));
            } catch (const std::exception& e) { updateOutput("Ошибка: " + QString(e.what())); }
            indexInput->clear();
        }
    });
    connect(removeAtBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t index = static_cast<size_t>(indexInput->text().toInt());
                if (index < static_cast<size_t>(currentBitSeq->GetLength())) {
                    BitSequence* newSeq = new BitSequence(currentBitSeq->GetLength() - 1);
                    size_t newIndex = 0;
                    for (size_t i = 0; i < static_cast<size_t>(currentBitSeq->GetLength()); i++) {
                        if (i != index) newSeq->SetBit(newIndex++, currentBitSeq->GetBit(i));
                    }
                    delete currentBitSeq; currentBitSeq = newSeq;
                    displayBitSequence(); updateOutput("Bit RemoveBitAt(" + QString::number(index) + ")");
                } else { updateOutput("Ошибка: Индекс вне диапазона"); }
            } catch (const std::exception& e) { updateOutput("Ошибка: " + QString(e.what())); }
            indexInput->clear();
        }
    });
    connect(removeFirstBtn, &QPushButton::clicked, [this]() {
        if (currentBitSeq->GetLength() > 0) {
            try {
                BitSequence* newSeq = new BitSequence(currentBitSeq->GetLength() - 1);
                for (size_t i = 1; i < static_cast<size_t>(currentBitSeq->GetLength()); i++) newSeq->SetBit(i - 1, currentBitSeq->GetBit(i));
                delete currentBitSeq; currentBitSeq = newSeq;
                displayBitSequence(); updateOutput("Bit RemoveFirstBit()");
            } catch (const std::exception& e) { updateOutput("Ошибка: " + QString(e.what())); }
        } else { updateOutput("RemoveFirstBit: последовательность пуста"); }
    });
    connect(removeLastBtn, &QPushButton::clicked, [this]() {
        if (currentBitSeq->GetLength() > 0) {
            try {
                BitSequence* newSeq = new BitSequence(currentBitSeq->GetLength() - 1);
                for (size_t i = 0; i < static_cast<size_t>(currentBitSeq->GetLength()) - 1; i++) newSeq->SetBit(i, currentBitSeq->GetBit(i));
                delete currentBitSeq; currentBitSeq = newSeq;
                displayBitSequence(); updateOutput("Bit RemoveLastBit()");
            } catch (const std::exception& e) { updateOutput("Ошибка: " + QString(e.what())); }
        } else { updateOutput("RemoveLastBit: последовательность пуста"); }
    });
    connect(andBtn, &QPushButton::clicked, [this]() {
        BitSequence copy(*currentBitSeq);
        auto* result = currentBitSeq->And(copy);
        QString res = "Bit AND результат: ";
        for (size_t i = 0; i < static_cast<size_t>(result->GetLength()); i++) res += QString::number(result->GetBit(i));
        updateOutput(res); delete result;
    });
    connect(orBtn, &QPushButton::clicked, [this]() {
        BitSequence copy(*currentBitSeq);
        auto* result = currentBitSeq->Or(copy);
        QString res = "Bit OR результат: ";
        for (size_t i = 0; i < static_cast<size_t>(result->GetLength()); i++) res += QString::number(result->GetBit(i));
        updateOutput(res); delete result;
    });
    connect(xorBtn, &QPushButton::clicked, [this]() {
        BitSequence copy(*currentBitSeq);
        auto* result = currentBitSeq->Xor(copy);
        QString res = "Bit XOR результат: ";
        for (size_t i = 0; i < static_cast<size_t>(result->GetLength()); i++) res += QString::number(result->GetBit(i));
        updateOutput(res); delete result;
    });
    connect(notBtn, &QPushButton::clicked, [this]() {
        auto* result = currentBitSeq->Not();
        QString res = "Bit NOT результат: ";
        for (size_t i = 0; i < static_cast<size_t>(result->GetLength()); i++) res += QString::number(result->GetBit(i));
        updateOutput(res); delete result;
    });
    connect(subseqBtn, &QPushButton::clicked, [this, startInput, endInput]() {
        if (!startInput->text().isEmpty() && !endInput->text().isEmpty()) {
            try {
                auto* subseq = currentBitSeq->GetSubsequence(static_cast<size_t>(startInput->text().toInt()), static_cast<size_t>(endInput->text().toInt()));
                QString res = "Bit подпоследовательность: ";
                for (size_t i = 0; i < static_cast<size_t>(subseq->GetLength()); i++) res += QString::number(subseq->GetBit(i));
                updateOutput(res); delete subseq;
            } catch (const std::exception& e) { updateOutput("Ошибка: " + QString(e.what())); }
            startInput->clear(); endInput->clear();
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
                currentBitSeq->InsertAt(Bit(valueCheck->isChecked()), static_cast<size_t>(indexInput->text().toInt()));
                displayBitSequence();
                updateOutput("Bit InsertAt(" + QString::number(valueCheck->isChecked()) + ", " + indexInput->text() + ")");
            } catch (const std::exception& e) { updateOutput("Ошибка: " + QString(e.what())); }
            indexInput->clear();
        }
    });
    connect(createBtn, &QPushButton::clicked, [this, sizeInput]() {
        size_t size = sizeInput->text().isEmpty() ? 8 : static_cast<size_t>(sizeInput->text().toInt());
        delete currentBitSeq;
        currentBitSeq = new BitSequence(size);
        displayBitSequence();
        updateOutput("Создана новая BitSequence размера " + QString::number(size));
        sizeInput->clear();
    });
    return tab;
}