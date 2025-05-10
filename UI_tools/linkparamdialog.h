#ifndef LINKPARAMDIALOG_H
#define LINKPARAMDIALOG_H

#include <QDialog>
#include "../Netw_elems/base/netlink.h"

namespace Ui {
class linkParamDialog;
}

class linkParamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit linkParamDialog(NetLink*, QWidget *parent = 0);
    ~linkParamDialog();
    NetLink* getLink();

private:
    Ui::linkParamDialog *ui;
    NetLink* link;
};

#endif // LINKPARAMDIALOG_H
