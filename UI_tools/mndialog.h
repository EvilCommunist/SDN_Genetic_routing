#ifndef MNDIALOG_H
#define MNDIALOG_H

#include <QWidget>
#include <qtermwidget5/qtermwidget.h>

namespace Ui {
class MNDialog;
}

class MNDialog : public QWidget
{
    Q_OBJECT

public:
    explicit MNDialog(const QString& scriptPath, QWidget *parent = nullptr);
    ~MNDialog();

private slots:
    void on_stop_clicked();

    void on_start_clicked();

private:
    Ui::MNDialog *ui;
    QTermWidget *terminal;
    QString currentScriptPath;
    bool isRunning;

    bool initTerminal();
    void startMininet();
    void stopMininet();
    void setupTerminal();
};

#endif // MNDIALOG_H
