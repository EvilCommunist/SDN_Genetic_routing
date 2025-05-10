#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    networkView = ui->networkView;

    connect(ui->actionHost, &QAction::triggered,
            networkView, &NetworkView::setHostMode);
    connect(ui->actionController, &QAction::triggered,
            networkView, &NetworkView::setControllerMode);
    connect(ui->actionSwitch, &QAction::triggered,
            networkView, &NetworkView::setSwitchMode);
    connect(ui->actionLink, &QAction::triggered,
            networkView, &NetworkView::setLinkMode);
    connect(ui->actionEdit, &QAction::triggered,
            networkView, &NetworkView::setEditMode);
    connect(ui->actionDelete, &QAction::triggered,
            networkView, &NetworkView::deleteSelectedItems);

    topologyTools();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::topologyTools(){
    ui->actionHost->setIcon(QIcon(":/imgs/host.png"));
    ui->actionSwitch->setIcon(QIcon(":/imgs/switch.png"));
    ui->actionController->setIcon(QIcon(":/imgs/controller.png"));
    ui->actionLink->setIcon(QIcon(":/imgs/link.png"));
    ui->actionEdit->setIcon(QIcon(":/imgs/edit.png"));

    QToolBar *topologyToolBar = new QToolBar("Topology Builder");
    topologyToolBar->setIconSize(QSize(64, 64));
    topologyToolBar->addAction(ui->actionController);
    topologyToolBar->addAction(ui->actionSwitch);
    topologyToolBar->addAction(ui->actionHost);
    topologyToolBar->addAction(ui->actionLink);
    topologyToolBar->addSeparator();
    topologyToolBar->addAction(ui->actionEdit);
    addToolBar(Qt::LeftToolBarArea,topologyToolBar);;
}

void MainWindow::on_actionController_triggered()
{
    emit signalPrepareController();
}

void MainWindow::on_actionHost_triggered()
{
    emit signalPrepareHost();
}

void MainWindow::on_actionSwitch_triggered()
{
    emit signalPrepareSwitch();
}

void MainWindow::on_actionLink_triggered()
{
    emit signalPrepareLink();
}

void MainWindow::on_actionEdit_triggered()
{
    emit signalChangeStateToEdit();
}
