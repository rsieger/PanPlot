#include <QtGui>

#include "Application.h"
#include "Globals.h"
#include "../Forms/SetTickOptionsDialog/SetTickOptionsDialog.h"

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void MainWindow::doSetTickOptionsDialog()
{
    int i_DialogResult = QDialog::Rejected;

    SetTickOptionsDialog *dialog	= new SetTickOptionsDialog();

// ***********************************************************************************************************************

    dialog->OKPushButton->setWhatsThis( "Set new tick options" );
    dialog->CancelPushButton->setWhatsThis( "Cancel dialog" );

// ***********************************************************************************************************************
// Options

    dialog->tickmarkWidth_lineEdit->setValidator( new QIntValidator( 0, 30, this ) );
    dialog->numMinorXTicks_lineEdit->setValidator( new QIntValidator( 0, 30, this ) );
    dialog->numMinorYTicks_lineEdit->setValidator( new QIntValidator( 0, 30, this ) );

    dialog->tickmarkWidth_lineEdit->setText( QString( "%1" ).arg( gi_tickmarkWidth ) );
    dialog->numMinorXTicks_lineEdit->setText( QString( "%1" ).arg( gi_numMinorXTicks ) );
    dialog->numMinorYTicks_lineEdit->setText( QString( "%1" ).arg( gi_numMinorYTicks ) );

    dialog->drawMajorXTicklines_checkBox->setChecked( gb_drawMajorXTicklines );
    dialog->drawMajorXTicksLeft_checkBox->setChecked( gb_drawMajorXTicksLeft );
    dialog->drawMajorXTicksRight_checkBox->setChecked( gb_drawMajorXTicksRight );
    dialog->drawMajorXTicksInside_checkBox->setChecked( gb_drawMajorXTicksInside );
    dialog->drawMajorXTicksOutside_checkBox->setChecked( gb_drawMajorXTicksOutside );

    dialog->drawMajorYTicklines_checkBox->setChecked( gb_drawMajorYTicklines );
    dialog->drawMajorYTicksTop_checkBox->setChecked( gb_drawMajorYTicksTop );
    dialog->drawMajorYTicksBottom_checkBox->setChecked( gb_drawMajorYTicksBottom );
    dialog->drawMajorYTicksInside_checkBox->setChecked( gb_drawMajorYTicksInside );
    dialog->drawMajorYTicksOutside_checkBox->setChecked( gb_drawMajorYTicksOutside );

    dialog->drawMinorXTicklines_checkBox->setChecked( gb_drawMinorXTicklines );
    dialog->drawMinorXTicksLeft_checkBox->setChecked( gb_drawMinorXTicksLeft );
    dialog->drawMinorXTicksRight_checkBox->setChecked( gb_drawMinorXTicksRight );
    dialog->drawMinorXTicksInside_checkBox->setChecked( gb_drawMinorXTicksInside );
    dialog->drawMinorXTicksOutside_checkBox->setChecked( gb_drawMinorXTicksOutside );

    dialog->drawMinorYTicklines_checkBox->setChecked( gb_drawMinorYTicklines );
    dialog->drawMinorYTicksTop_checkBox->setChecked( gb_drawMinorYTicksTop );
    dialog->drawMinorYTicksBottom_checkBox->setChecked( gb_drawMinorYTicksBottom );
    dialog->drawMinorYTicksInside_checkBox->setChecked( gb_drawMinorYTicksInside );
    dialog->drawMinorYTicksOutside_checkBox->setChecked( gb_drawMinorYTicksOutside );

    dialog->tickmarkWidth_lineEdit->setFocus();
    dialog->tickmarkWidth_lineEdit->selectAll();

    dialog->adjustSize();
    dialog->move( posDialog );

// ******************************************************************************************************

    i_DialogResult = dialog->exec();

    posDialog = dialog->pos();

    switch ( i_DialogResult )
    {
    case QDialog::Accepted:
        gi_tickmarkWidth  = dialog->tickmarkWidth_lineEdit->text().toInt();
        gi_numMinorXTicks = dialog->numMinorXTicks_lineEdit->text().toInt();
        gi_numMinorYTicks = dialog->numMinorYTicks_lineEdit->text().toInt();

        gb_drawMajorXTicklines    = dialog->drawMajorXTicklines_checkBox->isChecked();
        gb_drawMajorXTicksLeft    = dialog->drawMajorXTicksLeft_checkBox->isChecked();
        gb_drawMajorXTicksRight   = dialog->drawMajorXTicksRight_checkBox->isChecked();
        gb_drawMajorXTicksInside  = dialog->drawMajorXTicksInside_checkBox->isChecked();
        gb_drawMajorXTicksOutside = dialog->drawMajorXTicksOutside_checkBox->isChecked();

        gb_drawMajorYTicklines    = dialog->drawMajorYTicklines_checkBox->isChecked();
        gb_drawMajorYTicksTop     = dialog->drawMajorYTicksTop_checkBox->isChecked();
        gb_drawMajorYTicksBottom  = dialog->drawMajorYTicksBottom_checkBox->isChecked();
        gb_drawMajorYTicksInside  = dialog->drawMajorYTicksInside_checkBox->isChecked();
        gb_drawMajorYTicksOutside = dialog->drawMajorYTicksOutside_checkBox->isChecked();

        gb_drawMinorXTicklines    = dialog->drawMinorXTicklines_checkBox->isChecked();
        gb_drawMinorXTicksLeft    = dialog->drawMinorXTicksLeft_checkBox->isChecked();
        gb_drawMinorXTicksRight   = dialog->drawMinorXTicksRight_checkBox->isChecked();
        gb_drawMinorXTicksInside  = dialog->drawMinorXTicksInside_checkBox->isChecked();
        gb_drawMinorXTicksOutside = dialog->drawMinorXTicksOutside_checkBox->isChecked();

        gb_drawMinorYTicklines    = dialog->drawMinorYTicklines_checkBox->isChecked();
        gb_drawMinorYTicksTop     = dialog->drawMinorYTicksTop_checkBox->isChecked();
        gb_drawMinorYTicksBottom  = dialog->drawMinorYTicksBottom_checkBox->isChecked();
        gb_drawMinorYTicksInside  = dialog->drawMinorYTicksInside_checkBox->isChecked();
        gb_drawMinorYTicksOutside = dialog->drawMinorYTicksOutside_checkBox->isChecked();

        doShowPlot();
        break;

    case QDialog::Rejected:
        break;

    default:
        break;
    }

    delete dialog;
}
