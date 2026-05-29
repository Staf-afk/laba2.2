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

QWidget* MainWindow::createLinkedListTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);
    QGroupBox* viewGroup = new QGroupBox("Текущий LinkedList");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    linkedDisplay = new QTextEdit();
    linkedDisplay->setReadOnly(true);
    linkedDisplay->setMaximumHeight(100);
    viewLayout->addWidget(linkedDisplay);
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
    QPushButton* sublistBtn = new QPushButton("GetSubList");
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
    opsLayout->addWidget(sublistBtn, 2, 2);
    opsLayout->addWidget(removeFirstBtn, 2, 3);
    opsLayout->addWidget(removeLastBtn, 3, 0);
    layout->addWidget(opsGroup);
    layout->addStretch();
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
                currentLinkedList->InsertAt(valueInput->text().toInt(), static_cast<size_t>(indexInput->text().toInt()));
                displayLinkedList();
                updateOutput("LinkedList InsertAt(" + valueInput->text() + ", " + indexInput->text() + ")");
            } catch (const std::exception& e) { updateOutput("Ошибка: " + QString(e.what())); }
            valueInput->clear(); indexInput->clear();
        }
    });
    connect(getBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                int val = currentLinkedList->Get(static_cast<size_t>(indexInput->text().toInt()));
                updateOutput("LinkedList Get(" + indexInput->text() + ") = " + QString::number(val));
            } catch (const std::exception& e) { updateOutput("Ошибка: " + QString(e.what())); }
            indexInput->clear();
        }
    });
    connect(removeAtBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t index = static_cast<size_t>(indexInput->text().toInt());
                LinkedList<int>* newList = new LinkedList<int>();
                for (size_t i = 0; i < static_cast<size_t>(currentLinkedList->GetLength()); i++) {
                    if (i != index) newList->Append(currentLinkedList->Get(i));
                }
                delete currentLinkedList; currentLinkedList = newList;
                displayLinkedList(); updateOutput("LinkedList RemoveAt(" + QString::number(index) + ")");
            } catch (const std::exception& e) { updateOutput("Ошибка: " + QString(e.what())); }
            indexInput->clear();
        }
    });
    connect(removeFirstBtn, &QPushButton::clicked, [this]() {
        if (currentLinkedList->GetLength() > 0) {
            try {
                LinkedList<int>* newList = new LinkedList<int>();
                for (size_t i = 1; i < static_cast<size_t>(currentLinkedList->GetLength()); i++) newList->Append(currentLinkedList->Get(i));
                delete currentLinkedList; currentLinkedList = newList;
                displayLinkedList(); updateOutput("LinkedList RemoveFirst()");
            } catch (const std::exception& e) { updateOutput("Ошибка: " + QString(e.what())); }
        } else { updateOutput("LinkedList RemoveFirst: список пуст"); }
    });
    connect(removeLastBtn, &QPushButton::clicked, [this]() {
        if (currentLinkedList->GetLength() > 0) {
            try {
                LinkedList<int>* newList = new LinkedList<int>();
                for (size_t i = 0; i < static_cast<size_t>(currentLinkedList->GetLength()) - 1; i++) newList->Append(currentLinkedList->Get(i));
                delete currentLinkedList; currentLinkedList = newList;
                displayLinkedList(); updateOutput("LinkedList RemoveLast()");
            } catch (const std::exception& e) { updateOutput("Ошибка: " + QString(e.what())); }
        } else { updateOutput("LinkedList RemoveLast: список пуст"); }
    });
    connect(sublistBtn, &QPushButton::clicked, [this, startInput, endInput]() {
        if (!startInput->text().isEmpty() && !endInput->text().isEmpty()) {
            try {
                auto* sublist = currentLinkedList->GetSubList(static_cast<size_t>(startInput->text().toInt()), static_cast<size_t>(endInput->text().toInt()));
                QString result = "LinkedList подсписок [";
                for (size_t i = 0; i < static_cast<size_t>(sublist->GetLength()); i++) {
                    result += QString::number(sublist->Get(i));
                    if (i < sublist->GetLength() - 1) result += ", ";
                }
                result += "]"; updateOutput(result); delete sublist;
            } catch (const std::exception& e) { updateOutput("Ошибка: " + QString(e.what())); }
            startInput->clear(); endInput->clear();
        }
    });
    return tab;
}