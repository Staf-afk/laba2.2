#include "mainwindow.hpp"
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QLabel>
#include <exception>

QString personToString(const Person& p) {
    return QString::fromStdString(p.GetFullName()) + " (ID: " + QString::number(p.GetID().GetNumber()) + ")";
}

QWidget* MainWindow::createSetSequencePersonTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);

    QGroupBox* viewGroup = new QGroupBox("Текущее SetSequence<Person> (множество студентов/преподавателей)");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    setDisplayPerson = new QTextEdit();
    setDisplayPerson->setReadOnly(true);
    setDisplayPerson->setMaximumHeight(100);
    viewLayout->addWidget(setDisplayPerson);
    layout->addWidget(viewGroup);
    
    QGroupBox* inputGroup = new QGroupBox("Добавление персоны");
    QGridLayout* inputLayout = new QGridLayout(inputGroup);
    
    QLineEdit* firstNameInput = new QLineEdit();
    firstNameInput->setPlaceholderText("Имя");
    QLineEdit* lastNameInput = new QLineEdit();
    lastNameInput->setPlaceholderText("Фамилия");
    QLineEdit* idSeriesInput = new QLineEdit();
    idSeriesInput->setPlaceholderText("Серия ID");
    QLineEdit* idNumberInput = new QLineEdit();
    idNumberInput->setPlaceholderText("Номер ID");
    QComboBox* personTypeSelector = new QComboBox();
    personTypeSelector->addItems({"Студент", "Преподаватель"});
    
    QPushButton* appendPersonBtn = new QPushButton("Добавить персону");
    
    inputLayout->addWidget(firstNameInput, 0, 0);
    inputLayout->addWidget(lastNameInput, 0, 1);
    inputLayout->addWidget(idSeriesInput, 1, 0);
    inputLayout->addWidget(idNumberInput, 1, 1);
    inputLayout->addWidget(personTypeSelector, 2, 0);
    inputLayout->addWidget(appendPersonBtn, 2, 1);
    
    layout->addWidget(inputGroup);
    
    QGroupBox* opsGroup = new QGroupBox("Операции");
    QGridLayout* opsLayout = new QGridLayout(opsGroup);
    
    QLineEdit* indexInput = new QLineEdit();
    indexInput->setPlaceholderText("Индекс (для Get)");
    QLineEdit* startInput = new QLineEdit();
    startInput->setPlaceholderText("Начало");
    QLineEdit* endInput = new QLineEdit();
    endInput->setPlaceholderText("Конец");
    
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
    
    layout->addWidget(opsGroup);
    layout->addStretch();

    connect(appendPersonBtn, &QPushButton::clicked, [this, firstNameInput, lastNameInput, idSeriesInput, idNumberInput, personTypeSelector]() {
        if (!firstNameInput->text().isEmpty() && !lastNameInput->text().isEmpty()) {
            try {
                int series = idSeriesInput->text().isEmpty() ? 1234 : idSeriesInput->text().toInt();
                int number = idNumberInput->text().isEmpty() ? rand() % 1000 : idNumberInput->text().toInt();
                PersonID id(series, number);
                Person newPerson(id, firstNameInput->text().toStdString(), lastNameInput->text().toStdString());
                
                SetSequence<Person>* newSet = currentSetSeqPerson->Append(newPerson);
                delete currentSetSeqPerson;
                currentSetSeqPerson = newSet;
                displaySetSequencePerson();
                updateOutput("Добавлена персона: " + personToString(newPerson));
                
                firstNameInput->clear();
                lastNameInput->clear();
                idSeriesInput->clear();
                idNumberInput->clear();
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
        }
    });
    
    connect(getBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t index = indexInput->text().toInt();
                Person val = currentSetSeqPerson->Get(index);
                updateOutput("Get(" + QString::number(index) + ") = " + personToString(val));
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
                SetSequence<Person>* subseq = currentSetSeqPerson->GetSubsequence(start, end);
                QString result = "Подмножество [" + QString::number(start) + "-" + QString::number(end) + "]: {";
                for (size_t i = 0; i < subseq->GetLength(); i++) {
                    result += personToString(subseq->Get(i));
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
            SetSequence<Person>* copy = new SetSequence<Person>();
            for (size_t i = 0; i < currentSetSeqPerson->GetLength(); i++) {
                SetSequence<Person>* temp = copy->Append(currentSetSeqPerson->Get(i));
                delete copy;
                copy = temp;
            }
            SetSequence<Person>* result = currentSetSeqPerson->Concat(copy);
            updateOutput("Set<Person> Concat: создана новая последовательность");
            delete copy;
            delete result;
        } catch (const std::exception& e) {
            updateOutput("Ошибка: " + QString(e.what()));
        }
    });
    
    connect(createBtn, &QPushButton::clicked, [this]() {
        delete currentSetSeqPerson;
        currentSetSeqPerson = new SetSequence<Person>();
        displaySetSequencePerson();
        updateOutput("Создано пустое множество персон");
    });
    
    connect(removeAtBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t index = indexInput->text().toInt();
                if (index < currentSetSeqPerson->GetLength()) {
                    SetSequence<Person>* newSet = new SetSequence<Person>();
                    for (size_t i = 0; i < currentSetSeqPerson->GetLength(); i++) {
                        if (i != index) {
                            SetSequence<Person>* temp = newSet->Append(currentSetSeqPerson->Get(i));
                            delete newSet;
                            newSet = temp;
                        }
                    }
                    delete currentSetSeqPerson;
                    currentSetSeqPerson = newSet;
                    displaySetSequencePerson();
                    updateOutput("Удалён элемент с индексом " + QString::number(index));
                }
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            indexInput->clear();
        }
    });
    
    connect(clearBtn, &QPushButton::clicked, [this]() {
        delete currentSetSeqPerson;
        currentSetSeqPerson = new SetSequence<Person>();
        displaySetSequencePerson();
        updateOutput("Множество очищено");
    });
    
    return tab;
}


