#include <QtGui>

#include "Application.h"
#include "Globals.h"
#include "../Forms/SetGraphicOptionsDialog/SetGraphicOptionsDialog.h"

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void MainWindow::doSetGraphicOptionsDialog()
{
    int i_DialogResult = QDialog::Rejected;

    SetGraphicOptionsDialog *dialog	= new SetGraphicOptionsDialog();

// ***********************************************************************************************************************

    dialog->OKPushButton->setWhatsThis( "Set new parameter title orientation" );
    dialog->CancelPushButton->setWhatsThis( "Cancel dialog" );

// ***********************************************************************************************************************
// Options

    dialog->marginLeft_lineEdit->setValidator( new QIntValidator( 0, 50, this ) );
    dialog->marginRight_lineEdit->setValidator( new QIntValidator( 0, 300, this ) );
    dialog->marginTop_lineEdit->setValidator( new QIntValidator( 0, 50, this ) );
    dialog->marginBottom_lineEdit->setValidator( new QIntValidator( 0, 50, this ) );
    dialog->marginScale_lineEdit->setValidator( new QIntValidator( 0, 30, this ) );
    dialog->diagramWidth_lineEdit->setValidator( new QIntValidator( 30, 5000, this ) );
    dialog->diagramHeight_lineEdit->setValidator( new QIntValidator( 50, 5000, this ) );
    dialog->diagramDistance_lineEdit->setValidator( new QIntValidator( 0, 100, this ) );

    dialog->marginLeft_lineEdit->setText( QString( "%1" ).arg( gi_marginLeft ) );
    dialog->marginRight_lineEdit->setText( QString( "%1" ).arg( gi_marginRight ) );
    dialog->marginTop_lineEdit->setText( QString( "%1" ).arg( gi_marginTop ) );
    dialog->marginBottom_lineEdit->setText( QString( "%1" ).arg( gi_marginBottom ) );
    dialog->marginScale_lineEdit->setText( QString( "%1" ).arg( gi_marginScale ) );
    dialog->diagramWidth_lineEdit->setText( QString( "%1" ).arg( gi_diagramWidth ) );
    dialog->diagramHeight_lineEdit->setText( QString( "%1" ).arg( gi_diagramHeight ) );
    dialog->diagramDistance_lineEdit->setText( QString( "%1" ).arg( gi_diagramDistance ) );
    dialog->fixedDiagramSize_checkBox->setChecked( gb_fixedDiagramSize );

    if ( gb_Antialiasing == TRUE )
        dialog->AntialiasingOn_radioButton->setChecked( TRUE );
    else
        dialog->AntialiasingOff_radioButton->setChecked( TRUE);

    dialog->marginRight_lineEdit->setFocus();
    dialog->marginRight_lineEdit->selectAll();
    dialog->adjustSize();
    dialog->move( posDialog );

// ******************************************************************************************************

    i_DialogResult = dialog->exec();

    posDialog = dialog->pos();

    switch ( i_DialogResult )
    {
    case QDialog::Accepted:
        gi_marginLeft       = dialog->marginLeft_lineEdit->text().toInt();
        gi_marginRight      = dialog->marginRight_lineEdit->text().toInt();
        gi_marginTop        = dialog->marginTop_lineEdit->text().toInt();
        gi_marginBottom     = dialog->marginBottom_lineEdit->text().toInt();
        gi_marginScale      = dialog->marginScale_lineEdit->text().toInt();
        gi_diagramWidth     = dialog->diagramWidth_lineEdit->text().toInt();
        gi_diagramHeight    = dialog->diagramHeight_lineEdit->text().toInt();
        gi_diagramDistance  = dialog->diagramDistance_lineEdit->text().toInt();
        gb_fixedDiagramSize = dialog->fixedDiagramSize_checkBox->isChecked();

        if ( dialog->AntialiasingOn_radioButton->isChecked() )
            gb_Antialiasing = TRUE;
        else
            gb_Antialiasing = FALSE;

        doShowPlot();
        break;

    case QDialog::Rejected:
        break;

    default:
        break;
    }

    delete dialog;
}
