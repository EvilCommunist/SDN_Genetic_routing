#ifndef HOSTDIALOG_H
#define HOSTDIALOG_H

#include <QDialog>
#include "../Netw_elems/host.h"

namespace Ui {
class HostDialog;
}

class HostDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HostDialog(Host*, QWidget *parent = 0);
    ~HostDialog();
    Host* getHost();

private:
    Ui::HostDialog *ui;
    Host* host;
};

#endif // HOSTDIALOG_H
