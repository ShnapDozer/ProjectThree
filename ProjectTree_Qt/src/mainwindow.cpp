#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "GameApplication.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_gameApp(new pt::GameApplication())
{
    ui->setupUi(this);

    assert(NULL != m_gameApp && "main() Can't create Application");

    int exitCode = m_gameApp->run();

    delete m_gameApp;
}

MainWindow::~MainWindow()
{
    delete ui;
}

