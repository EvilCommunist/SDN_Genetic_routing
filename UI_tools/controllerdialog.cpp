#include "controllerdialog.h"
#include "ui_controllerdialog.h"

ControllerDialog::ControllerDialog(Controller* controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControllerDialog),
    controller(controller){
    ui->setupUi(this);
    setControllerData();
}

Controller* ControllerDialog::getController(){return controller;}

void ControllerDialog::setControllerData(){
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setWindowTitle(QString("Controller %0").arg(controller->getName()));
    ui->lineEdit->setText(controller->getIp());
    ui->lineEdit_2->setText(controller->getPort());
}

ControllerDialog::~ControllerDialog(){delete ui;}

void ControllerDialog::accept()
{
    controller->setIp(ui->lineEdit->text());
    controller->setPort(ui->lineEdit_2->text());
    done(QDialog::Accepted);
}
