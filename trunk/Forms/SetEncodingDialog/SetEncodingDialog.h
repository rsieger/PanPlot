#ifndef SETENCODINGDIALOG_H
#define SETENCODINGDIALOG_H

#include <QDialog>

#include "ui_setencodingdialog.h"

class SetEncodingDialog : public QDialog, public Ui::SetEncodingDialog
{
Q_OBJECT

public:
    SetEncodingDialog( QWidget *parent = 0 );
};

#endif
