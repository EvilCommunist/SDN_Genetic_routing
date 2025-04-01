#ifndef CONTROLLERDIALOG_H
#define CONTROLLERDIALOG_H

#include <QDialog>

namespace Ui {
class ControllerDialog;
}

class ControllerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ControllerDialog(QWidget *parent = nullptr);
    ~ControllerDialog();

private:
    Ui::ControllerDialog *ui;
};

#endif // CONTROLLERDIALOG_H
