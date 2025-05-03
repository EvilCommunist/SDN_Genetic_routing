#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    topologyTools();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::topologyTools(){
    toolsGroup = new QActionGroup(this);
    toolBar = new QToolBar("toolBar");
    toolBar->setIconSize(QSize(64,64));
    actionController = toolBar->addAction(QPixmap(":imgs/controller.png"), "Controller (C)", this, SLOT(on_actionController_triggered()));
    actionController->setCheckable(true);
    toolsGroup->addAction(actionController);
    actionSwitch = toolBar->addAction(QPixmap(":imgs/switch.png"), "Switch (S)", this, SLOT(on_actionSwitch_triggered()));
    actionSwitch->setCheckable(true);
    toolsGroup->addAction(actionSwitch);
    actionHost = toolBar->addAction(QPixmap(":imgs/host.png"), "Host (H)", this, SLOT(on_actionHost_triggered()));
    actionHost->setCheckable(true);
    toolsGroup->addAction(actionHost);
    actionLink = toolBar->addAction(QPixmap(":imgs/link.png"), "Link (L)", this, SLOT(on_actionLink_triggered()));
    actionLink->setCheckable(true);
    toolsGroup->addAction(actionLink);
    toolBar->addSeparator();
    actionEdit = toolBar->addAction(QPixmap(":imgs/edit.png"), "Edit (E)", this, SLOT(on_actionEdit_triggered()));
    actionEdit->setCheckable(true);
    actionEdit->setChecked(true);
    toolsGroup->addAction(actionEdit);
    addToolBar(Qt::LeftToolBarArea, toolBar);
}
