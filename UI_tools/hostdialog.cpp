#include "hostdialog.h"
#include "ui_hostdialog.h"

HostDialog::HostDialog(Host* host, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HostDialog),
    host(host){
    ui->setupUi(this);
    setHostData();
}

Host* HostDialog::getHost(){return host;}

void HostDialog::setHostData(){
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setWindowTitle(QString("Host %0").arg(host->getName()));
    ui->lineEdit->setText(host->getIpAddr());
    ui->lineEdit_2->setText(host->getMacAddr());
}

HostDialog::~HostDialog(){delete ui;}

void HostDialog::accept()
{
    host->setIpAddr(ui->lineEdit->text());
    host->setMacAddr(ui->lineEdit_2->text());
    done(QDialog::Accepted);
}
