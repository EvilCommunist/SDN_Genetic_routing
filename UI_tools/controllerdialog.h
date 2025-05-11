#ifndef CONTROLLERDIALOG_H
#define CONTROLLERDIALOG_H

#include <QDialog>
#include "../Netw_elems/controller.h"

namespace Ui {
class ControllerDialog;
}

class ControllerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ControllerDialog(Controller* controller, QWidget *parent = 0);
    ~ControllerDialog();
    Controller* getController();

private:
    Ui::ControllerDialog *ui;
    Controller* controller;

    void setControllerData();

private slots:
    virtual void accept();
};

#endif // CONTROLLERDIALOG_H
