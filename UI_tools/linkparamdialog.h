#ifndef LINKPARAMDIALOG_H
#define LINKPARAMDIALOG_H

#include <QDialog>
#include "../Netw_elems/sslink.h"

namespace Ui {
class linkParamDialog;
}

class linkParamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit linkParamDialog(SSLink*, QWidget *parent = 0);
    ~linkParamDialog();
    SSLink* getLink();

private:
    Ui::linkParamDialog *ui;
    SSLink* link;
};

#endif // LINKPARAMDIALOG_H
