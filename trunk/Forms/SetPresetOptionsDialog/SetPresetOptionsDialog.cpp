// ***********************************************************************************************
// *                                                                                             *
// * SetPresetOptionsDialog.cpp - Presets dialog                                                 *
// *                                                                                             *
// * Dr. Rainer Sieger - 2014-06-08                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include <QtGui>

#include "Application.h"
#include "SetPresetOptionsDialog.h"

void MainWindow::doSetPresetOptionsDialog()
{
    SetPresetOptionsDialog dialog( this );

    if ( ( gi_PlotOrientation == _SHOWPLOTH_ ) && ( gb_XReverseGraphRange == false ) )
        dialog.Horizontal_radioButton->setChecked( true );

    if ( ( gi_PlotOrientation == _SHOWPLOTH_ ) && ( gb_XReverseGraphRange == true ) )
        dialog.Horizontal_reverse_radioButton->setChecked( true );

    if ( ( gi_PlotOrientation == _SHOWPLOTV_ ) && ( gb_XReverseGraphRange == false ) )
        dialog.Vertical_radioButton->setChecked( true );

    if ( ( gi_PlotOrientation == _SHOWPLOTV_ ) && ( gb_XReverseGraphRange == true ) )
        dialog.Vertical_reverse_radioButton->setChecked( true );

    if ( ( gi_PlotOrientation == _SHOWDATADESCRIPTIONTABLE_ ) && ( gsl_DataDescription.count() > 0 ) )
        dialog.Dataset_description_radioButton->setChecked( true );

    if ( gi_PlotOrientation == _SHOWPARAMETERTABLE_ )
        dialog.Parameter_statistic_radioButton->setChecked( true );

    if ( gsl_DataDescription.count() == 0 )
        dialog.Dataset_description_radioButton->setEnabled( false );

    dialog.OK_pushButton->setWhatsThis( "Close dialog" );
    dialog.Cancel_pushButton->setWhatsThis( "Cancel dialog" );

    dialog.adjustSize();
    dialog.move( posDialog );
    dialog.show();

// ******************************************************************************************************

    switch ( dialog.exec() )
    {
    case QDialog::Accepted:
        if ( dialog.Horizontal_radioButton->isChecked() == true )
        {
            gi_ParameterOrientation = 90;
            gi_PlotOrientation      = _SHOWPLOTH_;
            gb_XReverseGraphRange   = false;
            gb_YReverseGraphRange   = false;
        }

        if ( dialog.Horizontal_reverse_radioButton->isChecked() == true )
        {
            gi_ParameterOrientation = 90;
            gi_PlotOrientation      = _SHOWPLOTH_;
            gb_XReverseGraphRange   = true;
            gb_YReverseGraphRange   = false;
        }

        if ( dialog.Vertical_radioButton->isChecked() == true )
        {
            gi_ParameterOrientation = 0;
            gi_PlotOrientation      = _SHOWPLOTV_;
            gb_XReverseGraphRange   = false;
            gb_YReverseGraphRange   = false;
        }

        if ( dialog.Vertical_reverse_radioButton->isChecked() == true )
        {
            gi_ParameterOrientation = 0;
            gi_PlotOrientation      = _SHOWPLOTV_;
            gb_XReverseGraphRange   = true;
            gb_YReverseGraphRange   = false;
        }

        if ( ( dialog.Dataset_description_radioButton->isChecked() == true ) && ( gsl_DataDescription.count() > 0 ) )
            gi_PlotOrientation = _SHOWDATADESCRIPTIONTABLE_;

        if ( dialog.Parameter_statistic_radioButton->isChecked() == true )
            gi_PlotOrientation = _SHOWPARAMETERTABLE_;

        break;

    case QDialog::Rejected:
        break;

    default:
        break;
    }

    posDialog = dialog.pos();
}

// ******************************************************************************************************
// ******************************************************************************************************
// ******************************************************************************************************

SetPresetOptionsDialog::SetPresetOptionsDialog( QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    connect(OK_pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel_pushButton, SIGNAL(clicked()), this, SLOT(reject()));
}

