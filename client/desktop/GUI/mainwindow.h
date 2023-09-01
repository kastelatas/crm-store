#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Menu.h"
#include "orders.h"
#include "ingredients.h"
#include "calculator.h"
#include "clients.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onMenuClicked(const QModelIndex &index);

private:
    Ui::MainWindow *mUi;
    std::map<int, QWidget *> mMenuWidgets;
};
#endif // MAINWINDOW_H
