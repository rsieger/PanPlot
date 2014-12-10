#include <QtGui>

#include "Globals.h"
#include "SetParameterOrientationDialog.h"

SetParameterOrientationDialog::SetParameterOrientationDialog( QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    connect(OKPushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(CancelPushButton, SIGNAL(clicked()), this, SLOT(reject()));
}

