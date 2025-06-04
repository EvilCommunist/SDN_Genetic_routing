#ifndef RYUDIALOG_H
#define RYUDIALOG_H

#include <QWidget>
#include <qtermwidget5/qtermwidget.h>

namespace Ui {
class RyuDialog;
}

class RyuDialog : public QWidget
{
    Q_OBJECT

public:
    explicit RyuDialog(const QString& controllerPath, QWidget *parent = nullptr);

    ~RyuDialog();

private slots:
    void on_restart_clicked();

    void on_start_clicked();

    void on_stop_clicked();

private:
    Ui::RyuDialog *ui;
    QTermWidget *terminal;
    QString currentControllerPath;

    bool initTerminal();
    void startRyuManager();
    void stopRyuManager();
    void setupTerminal();
    void updateButtons(bool isRunning);
};

#endif // RYUDIALOG_H
