#include "ionnodeconfigdialog.h"
#include "ui_ionnodeconfigdialog.h"

#include <QModelIndex>

ionNodeConfigDialog::ionNodeConfigDialog(QWidget *parent, QString nodeAddress, QString privkey) :
    QDialog(parent),
    ui(new Ui::ionNodeConfigDialog)
{
    ui->setupUi(this);
    QString desc = "rpcallowip=127.0.0.1<br>rpcuser=REPLACEME<br>rpcpassword=REPLACEME<br>server=1<br>listen=1<br>port=REPLACEMEWITHYOURPORT<br>staking=0<br>enableaccounts=1<br>masternode=1<br>masternodeaddr=" + nodeAddress + "<br>masternodeprivkey=" + privkey + "<br>";
    ui->detailText->setHtml(desc);
}

ionNodeConfigDialog::~ionNodeConfigDialog()
{
    delete ui;
}
