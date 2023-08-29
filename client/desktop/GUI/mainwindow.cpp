#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), mUi(new Ui::MainWindow)
{
    mUi->setupUi(this);

    if (mUi != NULL)
    {
    }
}

MainWindow::~MainWindow()
{
    delete mUi;
}