#include <QtGui>

#include "Application.h"
#include "Globals.h"
#include "../Forms/SetParameterOptionsDialog/SetParameterOptionsDialog.h"

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void MainWindow::doSetParameterOptionsDialog()
{
    int i_DialogResult = QDialog::Rejected;

    SetParameterOptionsDialog *dialog	= new SetParameterOptionsDialog();

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

    dialog->DrawMarkers_checkBox->setChecked( gb_drawMarkers );
    dialog->DrawLines_checkBox->setChecked( gb_drawLines );

    dialog->MarkerSize_spinBox->setRange( 1, 20 );
    dialog->MarkerSize_spinBox->setSingleStep( 1 );
    dialog->MarkerSize_spinBox->setValue( gi_MarkerSize );

    dialog->LineWidth_spinBox->setRange( 1, 20 );
    dialog->LineWidth_spinBox->setSingleStep( 1 );
    dialog->LineWidth_spinBox->setValue( gi_LineWidth );

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

        gb_drawMarkers = dialog->DrawMarkers_checkBox->isChecked();
        gb_drawLines   = dialog->DrawLines_checkBox->isChecked();

        gi_MarkerSize  = dialog->MarkerSize_spinBox->value();
        gi_LineWidth   = dialog->LineWidth_spinBox->value();

        doShowPlot();

        break;

    case QDialog::Rejected:
        break;

    default:
        break;
    }

    delete dialog;
}
