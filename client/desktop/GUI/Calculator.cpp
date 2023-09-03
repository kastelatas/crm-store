#include "Calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent) : QWidget(parent),
                                          mUi(new Ui::calculator)
{
    mUi->setupUi(this);
    this->setWindowTitle("Калькулятор");
    this->hide();

    if (mUi != NULL)
    {
        mUi->calcTableWidget->setRowCount(1);
        mUi->calcTableWidget->setColumnCount(4);

        mUi->calcTableWidget->setHorizontalHeaderLabels({"Название", "Кол-во", "Един. измерения", "Цена за кг."});

        QHeaderView *header = mUi->calcTableWidget->horizontalHeader();

        // Устанавливаем режим растяжения для каждой колонки
        for (int col = 0; col < mUi->calcTableWidget->columnCount(); ++col)
        {
            header->setSectionResizeMode(col, QHeaderView::Stretch);
        }

        QComboBox *comboBox = createComboBoxWithUnity();

        mUi->calcTableWidget->setCellWidget(0, 2, comboBox);

        mUi->calcTableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);

        connect(mUi->addIngridient, SIGNAL(clicked()), this, SLOT(addNewIngridient()));
        connect(mUi->calcCost, SIGNAL(clicked()), this, SLOT(calcCost()));
        connect(mUi->calcTableWidget, SIGNAL(clicked(const QModelIndex &index)), this, SLOT(removeIngridient(const QModelIndex &index)));
    }
}

Calculator::~Calculator()
{
    delete mUi;
}

void Calculator::addNewIngridient()
{
    int rowCount = mUi->calcTableWidget->rowCount(); // Получаем текущее количество строк

    QComboBox *comboBox = createComboBoxWithUnity();

    mUi->calcTableWidget->insertRow(rowCount); // Добавляем новую строку
    mUi->calcTableWidget->setCellWidget(rowCount, 2, comboBox);
}

void Calculator::copyLayout(QLayout *sourceLayout, QLayout *targetLayout)
{
    for (int i = 0; i < sourceLayout->count(); ++i)
    {
        QLayoutItem *item = sourceLayout->itemAt(i);
        if (item)
        {
            QWidget *widget = item->widget();
            if (widget)
            {
                targetLayout->addWidget(widget);
            }
        }
    }
}

void Calculator::calcCost()
{
    int rowCount = mUi->calcTableWidget->rowCount();
    int colCount = mUi->calcTableWidget->columnCount();
    double productCost = 0;

    QVector<Ingredient> tableData; // Вектор для хранения данных

    for (int row = 0; row < rowCount; ++row)
    {
        Ingredient rowData; // Вектор для хранения данных строки
        for (int col = 0; col < colCount; ++col)
        {
            QTableWidgetItem *item = mUi->calcTableWidget->item(row, col);
            if (item)
            {
                QString cellData = "";

                QComboBox *comboBox = qobject_cast<QComboBox *>(mUi->calcTableWidget->cellWidget(row, col));
                if (comboBox)
                {
                    cellData = comboBox->currentText();
                }
                else
                {
                    cellData = item->text();
                }

                switch (col)
                {
                case 0:
                    rowData.name = cellData;
                    break;
                case 1:
                    rowData.quantity = cellData;

                    break;
                case 1:
                    rowData.unity = cellData;

                    break;
                case 1:
                    rowData.price = cellData;

                    break;
                default:
                    break;
                }
            }
        }
        tableData.push_back(rowData);
    }

    for (int i = 0; i < tableData.size(); i++)
    {
        productCost += (tableData[i][1].toInt() * (tableData[i][3].toInt()) / 1000);
    }

    mUi->productCost->setText(QString::number(productCost) + " грн.");
}

void Calculator::removeIngridient(const QModelIndex &index)
{
    if (index.column() == 0)
    {
        mUi->calcTableWidget->removeRow(index.row());
    }
}

QComboBox *Calculator::createComboBoxWithUnity()
{
    QComboBox *comboBox = new QComboBox;
    comboBox->addItem("кг");
    comboBox->addItem("г");
    comboBox->addItem("л");
    comboBox->addItem("мл");

    return comboBox;
}
