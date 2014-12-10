#ifndef SETGLOBALOPTIONSDIALOG_H
#define SETGLOBALOPTIONSDIALOG_H

#include <QDialog>

#include "ui_setglobaloptionsdialog.h"

class SetGlobalOptionsDialog : public QDialog, public Ui::SetGlobalOptionsDialog
{
    Q_OBJECT

public:
    SetGlobalOptionsDialog( QWidget *parent = 0 );

private slots:
    void setFixedDiagramSizeOptionsEnabled( int state );
};

#endif
