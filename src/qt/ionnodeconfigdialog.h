#ifndef ADRENALINENODECONFIGDIALOG_H
#define ADRENALINENODECONFIGDIALOG_H

#include <QDialog>

namespace Ui {
    class ionNodeConfigDialog;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Dialog showing transaction details. */
class ionNodeConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ionNodeConfigDialog(QWidget *parent = 0, QString nodeAddress = "YOURIPADDRESS:REPLACEMEWITHYOURPORT", QString privkey="MASTERNODEPRIVKEY");
    ~ionNodeConfigDialog();

private:
    Ui::ionNodeConfigDialog *ui;
};

#endif // ADRENALINENODECONFIGDIALOG_H
