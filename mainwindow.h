#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include "UI_tools/networkview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionController_triggered();
    void on_actionHost_triggered();
    void on_actionSwitch_triggered();
    void on_actionLink_triggered();
    void on_actionEdit_triggered();

private:
    Ui::MainWindow *ui;
    NetworkView *networkView;
    QActionGroup *metricGroupInMenu;
    QActionGroup *toolsGroupInMenu;
    QActionGroup *instrumentGroupInMenu;
    QActionGroup *toolsGroup;
    QAction *actionController;
    QAction *actionHost;
    QAction *actionSwitch;
    QAction *actionLink;
    QAction *actionEdit;
    QString openedFilePath;

    QToolBar *toolBar;

    void topologyTools();

signals:
    void signalPrepareController();
    void signalPrepareHost();
    void signalPrepareSwitch();
    void signalPrepareLink();
    void signalChangeStateToEdit();
};
#endif // MAINWINDOW_H
