#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <duckview.h>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void urlEntered();
    void urlChanged();

    void navigateNext();
    void navigatePrevious();

    void newTab();

    void titleChanged(QString title);
    void closeTab(int idx);

private:
    Ui::MainWindow *ui;

    void addTab(QString url);
    DuckView* currentTab();
    void navigate(QString url);
};

#endif // MAINWINDOW_H
