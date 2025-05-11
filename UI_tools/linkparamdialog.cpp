#include "linkparamdialog.h"
#include "ui_linkparamdialog.h"

linkParamDialog::linkParamDialog(NetLink* link, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::linkParamDialog),
    link(link)
{
    ui->setupUi(this);
    setLinkData();
}

NetLink* linkParamDialog::getLink(){return link;}

void linkParamDialog::setLinkData(){
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setWindowTitle(QString("Link %0 - %1")
                         .arg(link->getNode1()->getName())
                         .arg(link->getNode2()->getName()));
    ui->lineEdit->setText(QString::number(link->getBandwidth()));
    ui->lineEdit_2->setText(QString::number(link->getDelay()));
    ui->lineEdit_3->setText(QString::number(link->getPacketLoss()*100));
}

linkParamDialog::~linkParamDialog(){delete ui;}

void linkParamDialog::accept(){
    link->setBandwidth(ui->lineEdit->text().toFloat());
    link->setDelay(ui->lineEdit_2->text().toFloat());
    link->setPacketLoss(ui->lineEdit_3->text().toFloat()/100);
    done(QDialog::Accepted);
}
