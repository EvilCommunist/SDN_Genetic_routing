#include "linkparamdialog.h"
#include "ui_linkparamdialog.h"

linkParamDialog::linkParamDialog(NetLink*, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::linkParamDialog),
    link(link)
{
    ui->setupUi(this);
}

NetLink* linkParamDialog::getLink(){return link;}

linkParamDialog::~linkParamDialog(){delete ui;}
