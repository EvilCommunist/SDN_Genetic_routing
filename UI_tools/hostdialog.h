#ifndef HOSTDIALOG_H
#define HOSTDIALOG_H

#include <QDialog>

namespace Ui {
class HostDialog;
}

class HostDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HostDialog(QWidget *parent = nullptr);
    ~HostDialog();

private:
    Ui::HostDialog *ui;
};

#endif // HOSTDIALOG_H
