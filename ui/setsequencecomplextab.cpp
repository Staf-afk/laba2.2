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

Complex parseComplex(const QString& str) {
    QString s = str.trimmed();
    s.remove(' ');
    if (s.contains('+') || s.contains('-')) {
        int plusPos = s.indexOf('+', 1);
        int minusPos = s.indexOf('-', 1);
        int splitPos = -1;
        if (plusPos != -1) splitPos = plusPos;
        if (minusPos != -1 && (splitPos == -1 || minusPos < splitPos)) splitPos = minusPos;
        
        if (splitPos != -1) {
            double real = s.left(splitPos).toDouble();
            double imag = s.mid(splitPos).toDouble();
            return Complex(real, imag);
        }
    }
    double real = s.toDouble();
    return Complex(real, 0);
}

QString complexToString(const Complex& c) {
    return QString::number(c.real()) + (c.imag() >= 0 ? "+" : "") + QString::number(c.imag()) + "i";
}

QWidget* MainWindow::createSetSequenceComplexTab()
{
    QWidget* tab = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(tab);

    QGroupBox* viewGroup = new QGroupBox("Текущее SetSequence<Complex> (множество комплексных чисел)");
    QVBoxLayout* viewLayout = new QVBoxLayout(viewGroup);
    setDisplayComplex = new QTextEdit();
    setDisplayComplex->setReadOnly(true);
    setDisplayComplex->setMaximumHeight(100);
    viewLayout->addWidget(setDisplayComplex);
    layout->addWidget(viewGroup);
    
    QGroupBox* opsGroup = new QGroupBox("Операции");
    QGridLayout* opsLayout = new QGridLayout(opsGroup);
    
    QLineEdit* valueInput = new QLineEdit();
    valueInput->setPlaceholderText("Значение (например: 3+4i или 5)");
    QLineEdit* indexInput = new QLineEdit();
    indexInput->setPlaceholderText("Индекс (для Get)");
    QLineEdit* startInput = new QLineEdit();
    startInput->setPlaceholderText("Начало");
    QLineEdit* endInput = new QLineEdit();
    endInput->setPlaceholderText("Конец");
    QLineEdit* createItemsInput = new QLineEdit();
    createItemsInput->setPlaceholderText("Элементы через запятую (1+1i,2+2i,3+3i)");
    
    QPushButton* appendBtn = new QPushButton("Append (добавить)");
    QPushButton* getBtn = new QPushButton("Get (по индексу)");
    QPushButton* subseqBtn = new QPushButton("GetSubsequence");
    QPushButton* concatBtn = new QPushButton("Concat (с копией)");
    QPushButton* mapBtn = new QPushButton("Map (+1 ко всем)");
    QPushButton* whereBtn = new QPushButton("Where (Re > 0)");
    QPushButton* reduceBtn = new QPushButton("Reduce (сумма)");
    QPushButton* findBtn = new QPushButton("Find (значение == 3+3i)");
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
                Complex val = parseComplex(valueInput->text());
                SetSequence<Complex>* newSet = currentSetSeqComplex->Append(val);
                delete currentSetSeqComplex;
                currentSetSeqComplex = newSet;
                displaySetSequenceComplex();
                updateOutput("Set<Complex> Append(" + valueInput->text() + ")");
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
                Complex val = currentSetSeqComplex->Get(index);
                updateOutput("Set<Complex> Get(" + QString::number(index) + ") = " + complexToString(val));
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
                SetSequence<Complex>* subseq = currentSetSeqComplex->GetSubsequence(start, end);
                QString result = "Подмножество [" + QString::number(start) + "-" + QString::number(end) + "]: {";
                for (size_t i = 0; i < subseq->GetLength(); i++) {
                    result += complexToString(subseq->Get(i));
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
            SetSequence<Complex>* copy = new SetSequence<Complex>();
            for (size_t i = 0; i < currentSetSeqComplex->GetLength(); i++) {
                SetSequence<Complex>* temp = copy->Append(currentSetSeqComplex->Get(i));
                delete copy;
                copy = temp;
            }
            SetSequence<Complex>* result = currentSetSeqComplex->Concat(copy);
            updateOutput("Set<Complex> Concat: создана новая последовательность");
            delete copy;
            delete result;
        } catch (const std::exception& e) {
            updateOutput("Ошибка: " + QString(e.what()));
        }
    });
    
    connect(mapBtn, &QPushButton::clicked, [this]() {
        if (currentSetSeqComplex->GetLength() > 0) {
            try {
                SetSequence<Complex>* result = currentSetSeqComplex->Map([](Complex x) { 
                    return Complex(x.real() + 1, x.imag()); 
                });
                QString res = "Map (+1 к реальной части): {";
                for (size_t i = 0; i < result->GetLength(); i++) {
                    res += complexToString(result->Get(i));
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
        if (currentSetSeqComplex->GetLength() > 0) {
            try {
                SetSequence<Complex>* result = currentSetSeqComplex->Where([](Complex x) { return x.real() > 0; });
                QString res = "Комплексные с Re > 0: {";
                for (size_t i = 0; i < result->GetLength(); i++) {
                    res += complexToString(result->Get(i));
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
        if (currentSetSeqComplex->GetLength() > 0) {
            try {
                Complex sum = currentSetSeqComplex->Reduce([](Complex a, Complex b) { return a + b; }, Complex(0, 0));
                updateOutput("Сумма всех элементов = " + complexToString(sum));
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
        }
    });
    
    connect(findBtn, &QPushButton::clicked, [this]() {
        Complex target(3, 3);
        Option<Complex> found = currentSetSeqComplex->Find([target](Complex x) { 
            return x.real() == target.real() && x.imag() == target.imag(); 
        });
        if (found.IsSome()) {
            updateOutput("Найдено значение 3+3i");
        } else {
            updateOutput("Значение 3+3i не найдено");
        }
    });
    
    connect(createBtn, &QPushButton::clicked, [this, createItemsInput]() {
        if (!createItemsInput->text().isEmpty()) {
            try {
                QStringList parts = createItemsInput->text().split(',');
                std::vector<Complex> items;
                for (const QString& part : parts) {
                    items.push_back(parseComplex(part.trimmed()));
                }
                delete currentSetSeqComplex;
                currentSetSeqComplex = new SetSequence<Complex>(items.data(), items.size());
                displaySetSequenceComplex();
                updateOutput("Создано новое множество из: {" + createItemsInput->text() + "}");
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            createItemsInput->clear();
        } else {
            delete currentSetSeqComplex;
            currentSetSeqComplex = new SetSequence<Complex>();
            displaySetSequenceComplex();
            updateOutput("Создано пустое множество");
        }
    });
    
    connect(removeAtBtn, &QPushButton::clicked, [this, indexInput]() {
        if (!indexInput->text().isEmpty()) {
            try {
                size_t index = indexInput->text().toInt();
                if (index < currentSetSeqComplex->GetLength()) {
                    SetSequence<Complex>* newSet = new SetSequence<Complex>();
                    for (size_t i = 0; i < currentSetSeqComplex->GetLength(); i++) {
                        if (i != index) {
                            SetSequence<Complex>* temp = newSet->Append(currentSetSeqComplex->Get(i));
                            delete newSet;
                            newSet = temp;
                        }
                    }
                    delete currentSetSeqComplex;
                    currentSetSeqComplex = newSet;
                    displaySetSequenceComplex();
                    updateOutput("Удалён элемент с индексом " + QString::number(index));
                }
            } catch (const std::exception& e) {
                updateOutput("Ошибка: " + QString(e.what()));
            }
            indexInput->clear();
        }
    });
    
    connect(clearBtn, &QPushButton::clicked, [this]() {
        delete currentSetSeqComplex;
        currentSetSeqComplex = new SetSequence<Complex>();
        displaySetSequenceComplex();
        updateOutput("Множество очищено");
    });
    
    return tab;
}

