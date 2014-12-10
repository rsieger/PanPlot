// ***********************************************************************************************
// *                                                                                             *
// * AboutDialog.cpp - About dialog of program                                                   *
// *                                                                                             *
// * Dr. Rainer Sieger - 2011-07-17                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include <QtGui>

#include "AboutDialog.h"

AboutDialog::AboutDialog( QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    connect(OK_pushButton, SIGNAL(clicked()), this, SLOT(accept()));
}
