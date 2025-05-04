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
    explicit ControllerDialog(Controller* ,QWidget *parent = 0);
    ~ControllerDialog();
    Controller* getController();

private:
    Ui::ControllerDialog *ui;
    Controller* controller;
};

#endif // CONTROLLERDIALOG_H
