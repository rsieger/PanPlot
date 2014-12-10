#include <QtGui>

#include "Application.h"
#include "Globals.h"
#include "../Forms/SetParameterOrientationDialog/SetParameterOrientationDialog.h"

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void MainWindow::doSetParameterOrientationDialog()
{
    int i_DialogResult = QDialog::Rejected;

    SetParameterOrientationDialog *dialog	= new SetParameterOrientationDialog();

// ***********************************************************************************************************************

    dialog->OKPushButton->setWhatsThis( "Set new parameter title orientation" );
    dialog->CancelPushButton->setWhatsThis( "Cancel dialog" );

// ***********************************************************************************************************************
// Options

    switch ( gi_ParameterOrientation )
    {
    case 90:
        dialog->ParameterOrientation90RadioButton->setChecked( TRUE );
        break;
    case 45:
        dialog->ParameterOrientation45RadioButton->setChecked( TRUE );
        break;
    default:
        dialog->ParameterOrientation0RadioButton->setChecked( TRUE );
        break;
    }

    dialog->adjustSize();

    dialog->move( posDialog );

// ******************************************************************************************************

    i_DialogResult = dialog->exec();

    posDialog = dialog->pos();

    switch ( i_DialogResult )
    {
    case QDialog::Accepted:
        if ( dialog->ParameterOrientation0RadioButton->isChecked() )
            gi_ParameterOrientation = 0;
        if ( dialog->ParameterOrientation45RadioButton->isChecked() )
            gi_ParameterOrientation = 45;
        if ( dialog->ParameterOrientation90RadioButton->isChecked() )
            gi_ParameterOrientation = 90;
        renderArea->setParameterNameOrientation( gi_ParameterOrientation );
        break;

    case QDialog::Rejected:
        break;

    default:
        break;
    }

    delete dialog;
}
