// ***********************************************************************************************
// *                                                                                             *
// * SetEncodingDialog.cpp - Sets encoding of datasets                                           *
// *                                                                                             *
// * Dr. Rainer Sieger - 2011-01-03                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include <QtGui>

#include "Application.h"
#include "SetEncodingDialog.h"

SetEncodingDialog::SetEncodingDialog( QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    connect(OK_pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel_pushButton, SIGNAL(clicked()), this, SLOT(reject()));
}

// ***********************************************************************************************************************
// ***********************************************************************************************************************
// ***********************************************************************************************************************

void MainWindow::doSetEncodingDialog()
{
    SetEncodingDialog dialog( this );

    dialog.setCodecComboBox->setCurrentIndex( gi_Codec );

    dialog.OK_pushButton->setWhatsThis( "Close dialog" );
    dialog.Cancel_pushButton->setWhatsThis( "Cancel dialog" );

    dialog.move( posDialog );
    dialog.resize( dialog.sizeHint() );
    dialog.show();

// ******************************************************************************************************

    switch ( dialog.exec() )
    {
    case QDialog::Accepted:
        gi_Codec = dialog.setCodecComboBox->currentIndex();
        break;

    case QDialog::Rejected:
        break;

    default:
        break;
    }

    posDialog = dialog.pos();
}
