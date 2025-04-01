#include "hostdialog.h"
#include "ui_hostdialog.h"

HostDialog::HostDialog(Host* host, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HostDialog),
    host(host)
{ui->setupUi(this);}

Host* HostDialog::getHost(){return host;}

HostDialog::~HostDialog(){delete ui;}
