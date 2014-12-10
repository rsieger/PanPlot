#include <QtGui>

#include "Globals.h"
#include "SetGlobalOptionsDialog.h"

SetGlobalOptionsDialog::SetGlobalOptionsDialog( QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    connect(OKPushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(CancelPushButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(fixedDiagramSize_checkBox, SIGNAL(stateChanged(int)), this, SLOT(setFixedDiagramSizeOptionsEnabled(int)));

    this->setFixedDiagramSizeOptionsEnabled( Qt::Unchecked );
}

void SetGlobalOptionsDialog::setFixedDiagramSizeOptionsEnabled( int state )
{
    if ( state == Qt::Checked )
    {
        this->diagramWidth_lineEdit->setEnabled( TRUE );
        this->diagramHeight_lineEdit->setEnabled( TRUE );
    }
    else
    {
        this->diagramWidth_lineEdit->setEnabled( FALSE );
        this->diagramHeight_lineEdit->setEnabled( FALSE );
    }
}
