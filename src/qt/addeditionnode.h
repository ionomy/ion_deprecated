#ifndef ADDEDITADRENALINENODE_H
#define ADDEDITADRENALINENODE_H

#include <QDialog>

namespace Ui {
class AddEditionNode;
}


class AddEditionNode : public QDialog
{
    Q_OBJECT

public:
    explicit AddEditionNode(QWidget *parent = 0);
    ~AddEditionNode();

protected:

private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();

signals:

private:
    Ui::AddEditionNode *ui;
};

#endif // ADDEDITADRENALINENODE_H
