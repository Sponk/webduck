#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "duckview.h"
#include <QWebHistory>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    addTab("google.de");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTab(QString url)
{
    DuckView* view = new DuckView;

    view->setUrl(QUrl::fromUserInput(url));
    view->settings()->setAttribute(QWebSettings::PluginsEnabled, true);

    connect(view,SIGNAL(urlChanged(QUrl)),this,SLOT(urlChanged()));
    connect(view,SIGNAL(titleChanged(QString)),this,SLOT(titleChanged(QString)));

    ui->browserTabs->addTab(view, "Unbekannt");
}

DuckView* MainWindow::currentTab()
{
    return (DuckView*) ui->browserTabs->currentWidget();
}

void MainWindow::navigate(QString url)
{
    QUrl qurl = QUrl::fromUserInput(url);
    currentTab()->setUrl(qurl);
    ui->urlEdit->setText(qurl.toString());
}

void MainWindow::urlEntered()
{
    navigate(ui->urlEdit->displayText());
}

void MainWindow::urlChanged()
{
    ui->urlEdit->setText(currentTab()->url().toString());
    ui->urlEdit->setCursorPosition(0);
}

void MainWindow::navigateNext()
{
    currentTab()->page()->history()->forward();
}

void MainWindow::navigatePrevious()
{
    currentTab()->page()->history()->back();
}

void MainWindow::newTab()
{
    // TODO: Startseite!
    addTab("www.google.de");
}

void MainWindow::titleChanged(QString title)
{
    if(title == "")
        return;

    for(int i = 0; i < ui->browserTabs->count(); i++)
    {
            DuckView* view = (DuckView*) ui->browserTabs->widget(i);

            if(view->title() == title)
            {
                if(title.size() > 13)
                {
                    ui->browserTabs->setTabText(ui->browserTabs->indexOf(view), title.left(13)+"...");
                }
                else
                {
                    ui->browserTabs->setTabText(ui->browserTabs->indexOf(view), title);
                }
            }
    }
}

void MainWindow::closeTab(int idx)
{
    ui->browserTabs->removeTab(idx);

    if(ui->browserTabs->count() <= 0)
        addTab("google.de");
}
