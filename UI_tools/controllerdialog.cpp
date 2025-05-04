#include "controllerdialog.h"
#include "ui_controllerdialog.h"

ControllerDialog::ControllerDialog(Controller*, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControllerDialog),
    controller(controller)
{ui->setupUi(this);}

Controller* ControllerDialog::getController(){return controller;}

ControllerDialog::~ControllerDialog(){delete ui;}
