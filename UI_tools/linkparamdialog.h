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
    explicit linkParamDialog(NetLink* link, QWidget *parent = 0);
    ~linkParamDialog();
    NetLink* getLink();
    void setLinkData();

private slots:
    virtual void accept();

private:
    Ui::linkParamDialog *ui;
    NetLink* link;
};

#endif // LINKPARAMDIALOG_H
