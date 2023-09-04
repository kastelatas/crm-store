#include "Calculator.h"
#include "ui_calculator.h"
#include <QDebug>
#include "QFile"
#include <QPdfWriter>
#include <QPainter>

Calculator::Calculator(QWidget *parent) : QWidget(parent),
                                          mUi(new Ui::calculator)
{
    mUi->setupUi(this);
    this->setWindowTitle("Калькулятор");
    this->hide();

    if (mUi != NULL)
    {
        // configuration calc table
        mUi->calcTableWidget->setRowCount(0);
        mUi->calcTableWidget->setColumnCount(6);

        mUi->calcTableWidget->setHorizontalHeaderLabels({"Название",
                                                         "Кол-во в", "Един. измерения",
                                                         "Цена за", "Един. измерения", "  "});

        QHeaderView *calcTableHeader = mUi->calcTableWidget->horizontalHeader();

        for (int col = 0, count = mUi->calcTableWidget->columnCount(); col < count; ++col)
        {
            calcTableHeader->setSectionResizeMode(col, QHeaderView::Stretch);
        }

        // mUi->calcTableWidget->setCellWidget(0, 0, createIngridientsComboBox());
        // mUi->calcTableWidget->setCellWidget(0, 2, createQuantityUnitsComboBox());
        // mUi->calcTableWidget->setCellWidget(0, 4, createPriceUnitsComboBox());
        // mUi->calcTableWidget->setCellWidget(0, 5, createDeleteButton(0));
        mUi->calcTableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);

        // configuration ingridients table
        mUi->ingridientTableWidget->setRowCount(0);
        mUi->ingridientTableWidget->setColumnCount(1);
        mUi->ingridientTableWidget->setHorizontalHeaderLabels({"Название"});

        QHeaderView *ingridientTableHeader = mUi->ingridientTableWidget->horizontalHeader();

        for (int col = 0, count = mUi->ingridientTableWidget->columnCount(); col < count; ++col)
        {
            ingridientTableHeader->setSectionResizeMode(col, QHeaderView::Stretch);
        }

        readFromFile();
        updateDataInIngridientsComboBox();

        // deleteButtonMapper = new QSignalMapper(this);

        connect(mUi->addIngridient, SIGNAL(clicked()), this, SLOT(addNewIngridient()));
        connect(mUi->calcCost, SIGNAL(clicked()), this, SLOT(calcCost()));
        connect(mUi->calcTabs, SIGNAL(currentChanged(int)), this, SLOT(changeTab(int)));
        connect(mUi->addIngridientToTable, SIGNAL(clicked()), this, SLOT(addIngridient()));
        connect(mUi->clearCalcTable, SIGNAL(clicked()), this, SLOT(clearCalcTable()));
        connect(mUi->saveDish, SIGNAL(clicked()), this, SLOT(writeToPDF()));

        // connect(deleteButtonMapper, SIGNAL(mapped(int)), this, SLOT(onDeleteButtonClicked(int)));
    }
}

Calculator::~Calculator()
{
    delete mUi;
}

void Calculator::addNewIngridient()
{
    const int rowCount = mUi->calcTableWidget->rowCount();

    mUi->calcTableWidget->insertRow(rowCount);
    mUi->calcTableWidget->setCellWidget(rowCount, 0, createIngridientsComboBox());
    mUi->calcTableWidget->setCellWidget(rowCount, 4, createPriceUnitsComboBox());
    mUi->calcTableWidget->setCellWidget(rowCount, 2, createQuantityUnitsComboBox());
    mUi->calcTableWidget->setCellWidget(rowCount, 5, createDeleteButton(rowCount));
}

void Calculator::calcCost()
{
    const int rowCount = mUi->calcTableWidget->rowCount();
    const int colCount = mUi->calcTableWidget->columnCount();

    for (int row = 0; row < rowCount; ++row)
    {
        Ingredient rowData;
        for (int col = 0; col < colCount; ++col)
        {
            const auto *item = mUi->calcTableWidget->item(row, col);
            const auto *comboBox = qobject_cast<QComboBox *>(mUi->calcTableWidget->cellWidget(row, col));
            if (item || comboBox)
            {
                switch (col)
                {
                case 0:
                    rowData.name = comboBox->currentText();
                    break;
                case 1:
                    rowData.quantity = item->text().toFloat();
                    break;
                case 2:
                    rowData.quantityUnit = comboBox->itemData(comboBox->currentIndex()).value<QuantityUnit>();
                    break;
                case 3:
                    rowData.price = item->text().toFloat();
                    break;
                case 4:
                    rowData.priceUnit = comboBox->itemData(comboBox->currentIndex()).value<PriceUnit>();
                    break;
                default:
                    break;
                }
            }
        }
        mDish.push_back(rowData);
    }

    double productCost = 0;

    for (int i = 0; i < mDish.size(); i++)
    {
        const auto &item = mDish[i];
        float quantity = item.quantity;
        float price = item.price;

        double rowCost = (quantity * price) / coefficient(item.priceUnit, item.quantityUnit);

        productCost += rowCost;
    }

    mUi->productCost->setText(QString::number(productCost) + " грн.");
}

QComboBox *Calculator::createQuantityUnitsComboBox()
{
    auto comboBox = new QComboBox(mUi->calcTableWidget);
    comboBox->addItem("кг", QVariant::fromValue(QuantityUnit::KILOGRAMM));
    comboBox->addItem("г", QVariant::fromValue(QuantityUnit::GRAMM));
    comboBox->addItem("л", QVariant::fromValue(QuantityUnit::LITER));
    comboBox->addItem("мл", QVariant::fromValue(QuantityUnit::MILLILITER));
    comboBox->addItem("шт", QVariant::fromValue(QuantityUnit::UNIT));

    return comboBox;
}

QComboBox *Calculator::createPriceUnitsComboBox()
{
    auto comboBox = new QComboBox(mUi->calcTableWidget);
    comboBox->addItem("грн/кг", QVariant::fromValue(PriceUnit::UAH_PER_KG));
    comboBox->addItem("грн/л", QVariant::fromValue(PriceUnit::UAH_PER_LITER));
    comboBox->addItem("грн/шт", QVariant::fromValue(PriceUnit::UAH_PER_UNIT));

    return comboBox;
}

QComboBox *Calculator::createIngridientsComboBox()
{
    auto comboBox = new QComboBox();
    for (const auto &item : mIngredients)
    {
        comboBox->addItem(item);
    }

    return comboBox;
}

QPushButton *Calculator::createDeleteButton(int rowId)
{
    auto deleteButton = new QPushButton();
    // TODO update path to icon
    deleteButton->setIcon(QIcon(":/icons/remove.png"));
    deleteButton->setIconSize(QSize(24, 24));

    // deleteButtonMapper->setMapping(deleteButton, rowId);
    // connect(deleteButton, SIGNAL(clicked()), deleteButtonMapper, SLOT(map()));

    return deleteButton;
}

void Calculator::onDeleteButtonClicked(int rowId)
{
    mUi->calcTableWidget->removeRow(rowId);
}

/*
            | UAH_PER_KG	UAH_PER_LITER	UAH_PER_UNIT
KILOGRAMM	| 1             PO              N/A
GRAMM	    | 1000          PO              N/A
LITER	    | PO            1               N/A
MILLILITER	| PO            1000            N/A
UNIT	    | N/A           N/A             1

*/

float Calculator::coefficient(PriceUnit priceUnit, QuantityUnit quantityUnit) const
{
    float result = 1.0;

    if (priceUnit == PriceUnit::UAH_PER_KG)
    {
        if (quantityUnit == QuantityUnit::KILOGRAMM)
            result = 1.0;
        else if (quantityUnit == QuantityUnit::GRAMM)
            result = 1000.0;
        // TODO
    }
    else if (priceUnit == PriceUnit::UAH_PER_LITER)
    {
        if (quantityUnit == QuantityUnit::LITER)
            result = 1.0;
        else if (quantityUnit == QuantityUnit::MILLILITER)
            result = 1000.0;
        // TODO
    }
    else if (priceUnit == PriceUnit::UAH_PER_UNIT)
    {
        if (quantityUnit == QuantityUnit::UNIT)
            result = 1.0;
        // TODO
    }

    return result;
}

void Calculator::changeTab(int index)
{
    if (index == 0)
    {
        updateDataInIngridientsComboBox();
    }
}

void Calculator::updateDataInIngridientsComboBox()
{
    const int rowCount = mUi->calcTableWidget->rowCount();
    const int colCount = mUi->calcTableWidget->columnCount();

    for (int row = 0; row < rowCount; ++row)
    {
        for (int col = 0; col < colCount; ++col)
        {
            auto *comboBox = qobject_cast<QComboBox *>(mUi->calcTableWidget->cellWidget(row, col));
            if (comboBox && col == 0)
            {
                comboBox->clear();
                for (const auto &item : mIngredients)
                {
                    comboBox->addItem(item);
                }
            }
        }
    }
}

void Calculator::addIngridient()
{
    if (!mUi->ingridientInput->toPlainText().isEmpty())
    {
        const int rowCount = mUi->ingridientTableWidget->rowCount();
        mUi->ingridientTableWidget->insertRow(rowCount);

        QTableWidgetItem *newItem = new QTableWidgetItem(mUi->ingridientInput->toPlainText());

        mUi->ingridientTableWidget->setItem(rowCount, 0, newItem);

        mIngredients.push_back(mUi->ingridientInput->toPlainText());

        writeToFile();

        mUi->ingridientInput->clear();
    }
}

void Calculator::writeToFile()
{
    QFile file("ingredients.txt");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        for (const auto &ingredient : mIngredients)
        {
            out << ingredient << "\n";
        }
        file.close();
    }
}

void Calculator::readFromFile()
{
    QFile file("ingredients.txt");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);

        while (!in.atEnd())
        {
            QString line = in.readLine();
            mIngredients.push_back(line);
        }
        file.close();

        updateIngridientTable();
    }
}

void Calculator::updateIngridientTable()
{
    for (const auto &item : mIngredients)
    {
        const int rowCount = mUi->ingridientTableWidget->rowCount();
        mUi->ingridientTableWidget->insertRow(rowCount);
        mUi->ingridientTableWidget->setItem(rowCount, 0, new QTableWidgetItem(item));
    }
}

void Calculator::clearCalcTable()
{
    int rowCount = mUi->calcTableWidget->rowCount();

    if (rowCount > 0)
    {
        for (int i = 0; i < rowCount; i++)
        {
            mUi->calcTableWidget->removeRow(0); // Удаляем всегда первую строку, пока таблица не будет пустой
        }
    }
}

void Calculator::writeToPDF()
{
    QPdfWriter pdfWriter("example.pdf");
    pdfWriter.setPageSize(QPagedPaintDevice::A4);
    QPainter painter(&pdfWriter);

    painter.drawText(100, 100, "Список ингредиентов:");
    painter.drawText(100, 300, "");

    QTableWidget table;
    table.setColumnCount(5); // Количество столбцов
    table.setHorizontalHeaderLabels({"Ингредиент", "Количество", "Един. изм", "Цена", "Един. изм"});
    table.setRowCount(mDish.size());

    const int rowHeight = 450; // Установите желаемую высоту строки
    const int colWidth = 1700; // Установите желаемую ширину столбца
    table.verticalHeader()->setDefaultSectionSize(rowHeight);
    for (int col = 0; col < table.columnCount(); ++col)
    {
        table.setColumnWidth(col, colWidth);
    }

    table.setContentsMargins(150, 500, 0, 0);

    QFont font = table.font();
    font.setPointSize(120); // Установите желаемый размер шрифта
    table.setFont(font);

    for (int row = 0; row < mDish.size(); ++row)
    {
        const Ingredient &ingredient = mDish[row];

        QTableWidgetItem *item = new QTableWidgetItem(ingredient.name);

        // Устанавливаем выравнивание текста в ячейке слева
        item->setTextAlignment(Qt::AlignVCenter);
        table.setItem(row, 0, item);
        table.setItem(row, 1, new QTableWidgetItem(QString::number(ingredient.quantity)));
        table.setItem(row, 2, new QTableWidgetItem(QString::number(static_cast<int>(ingredient.quantityUnit))));
        table.setItem(row, 3, new QTableWidgetItem(QString::number(ingredient.price)));
        table.setItem(row, 4, new QTableWidgetItem(QString::number(static_cast<int>(ingredient.priceUnit))));
    }

    // Устанавливаем размер таблицы
    const qreal scale = 20.5; // Увеличьте масштаб, чтобы увеличить размер таблицы
    table.resize(table.size() * scale);

    // Рисуем таблицу на PDF-странице
    table.render(&painter);

    painter.end();
}
