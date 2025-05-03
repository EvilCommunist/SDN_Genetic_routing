#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QActionGroup *metricGroupInMenu;
    QActionGroup *toolsGroupInMenu;
    QActionGroup *instrumentGroupInMenu;
    QActionGroup *toolsGroup;
    QAction *actionController;
    QAction *actionHost;
    QAction *actionSwitch;
    QAction *actionLink;
    QAction *actionEdit;
    QAction *actionText;
    QString openedFilePath;

    QToolBar *toolBar;
    QToolBar *utilitiesToolBar;

    void topologyTools();
};
#endif // MAINWINDOW_H
