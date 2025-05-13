#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QDebug>
#include <QFileDialog>

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

void MainWindow::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    "Сохранить файл",
                                                    QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/untitled.sdn",
                                                    "Файлы топологии (*.sdn);;Файлы формата JSON (*.json)");
    if (filename.isEmpty()) {
        return;
    }
    if (!filename.endsWith(".sdn", Qt::CaseInsensitive)) {
        filename += ".sdn";
    }

    bool ok = JSONProcessor::saveJSONFile(networkView, filename);

    if(!ok){
        QMessageBox::warning(this, "Ошибка",
                                     "Произошло непредвиденное повреждение данных при сохранении файла!");
    }
    openedProjectPath = filename;
    QFileInfo fileInfo(filename);
    QString fileName = fileInfo.fileName();
    setWindowTitle(windowTitle() + " ["+fileName+"]");
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    "Открыть файл",
                                                    QStandardPaths::writableLocation(QStandardPaths::HomeLocation),
                                                    "Файлы топологии (*.sdn);;Файлы формата JSON (*.json)");
    if (filename.isEmpty()) {
        return;
    }

    bool ok = JSONProcessor::loadJSONFile(networkView, filename);

    if(!ok){
        QMessageBox::warning(this, "Ошибка",
                                     "Произошло непредвиденное повреждение данных при загрузке файла!");
    }
    openedProjectPath = filename;
    QFileInfo fileInfo(filename);
    QString fileName = fileInfo.fileName();
    setWindowTitle(windowTitle() + " ["+fileName+"]");
}

void MainWindow::on_actionSave_triggered()
{
    if(openedProjectPath.isEmpty()){
        on_actionSave_as_triggered();
        return;
    }

    bool ok = JSONProcessor::saveJSONFile(networkView, openedProjectPath);

    if(!ok){
        QMessageBox::warning(this, "Ошибка",
                                     "Произошло непредвиденное повреждение данных при сохранении файла!");
    }
}

void MainWindow::on_actionExport_as_mininet_script_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    "Сохранить файл",
                                                    QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/untitled.sdn.py",
                                                    "Скрипты mininet (*.sdn.py);;Скрипты Python (*.py)");
    if (filename.isEmpty()) {
        return;
    }
    if (!filename.endsWith(".sdn.py", Qt::CaseInsensitive)) {
        filename += ".sdn.py";
    }

    auto topology = networkView->getScene();
    int controllerPort = 0;
    QString controllerIP = "";
    QList<NetNode*> nodes{};

    for (QGraphicsItem* item : topology->items()) {
        if (auto node = dynamic_cast<NetNode*>(item)) {
            if(auto controller = dynamic_cast<Controller*>(node)){
                controllerPort = controller->getPort().toInt();
                controllerIP = controller->getIp();
            }else{
                nodes.append(node);
            }
        }
    }

    QList<NetLink*> links{};
    for (QGraphicsItem* item : topology->items()) {
        if (auto link = dynamic_cast<NetLink*>(item)) {
            if(link->getNode1()->getName()[0]=="c" || link->getNode2()->getName()[0]=="c")
                continue;
            links.append(link);
        }
    }

    QString script = mininetBuilder::generateMininetScript(nodes, links, controllerIP, controllerPort);

    bool ok = mininetBuilder::saveMNScript(script, filename);

    if(!ok){
        QMessageBox::warning(this, "Ошибка",
                                     "Произошло непредвиденное повреждение данных при сохранении файла!");
    }
}
