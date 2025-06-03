#ifndef RYUDIALOG_H
#define RYUDIALOG_H

#include <QWidget>

namespace Ui {
class RyuDialog;
}

class RyuDialog : public QWidget
{
    Q_OBJECT

public:
    explicit RyuDialog(QWidget *parent = nullptr);
    ~RyuDialog();

private:
    Ui::RyuDialog *ui;
};

#endif // RYUDIALOG_H
