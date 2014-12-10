#ifndef SETPARAMETERORIENTATIONDIALOG_H
#define SETPARAMETERORIENTATIONDIALOG_H

#include <QDialog>

#include "ui_setparameterorientationdialog.h"

class SetParameterOrientationDialog : public QDialog, public Ui::SetParameterOrientationDialog
{
    Q_OBJECT

public:
    SetParameterOrientationDialog( QWidget *parent = 0 );
};

#endif
