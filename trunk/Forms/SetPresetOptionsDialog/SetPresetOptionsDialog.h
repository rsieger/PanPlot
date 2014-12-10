#ifndef SETPRESETOPTIONSDIALOG_H
#define SETPRESETOPTIONSDIALOG_H

#include <QDialog>

#include "ui_setpresetoptionsdialog.h"

class SetPresetOptionsDialog : public QDialog, public Ui::SetPresetOptionsDialog
{
    Q_OBJECT

public:
    SetPresetOptionsDialog( QWidget *parent = 0 );
};

#endif
