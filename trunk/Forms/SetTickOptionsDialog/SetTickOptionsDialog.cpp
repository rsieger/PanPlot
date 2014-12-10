// ***********************************************************************************************
// *                                                                                             *
// * SetTickOptionsDialog.cpp - Tick options dailog                                              *
// *                                                                                             *
// * Dr. Rainer Sieger - 2012-06-08                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include <QtGui>

#include "Application.h"
#include "SetTickOptionsDialog.h"

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void MainWindow::doSetTickOptionsDialog()
{
    saveGraphicOptions();
    saveParameterOptions();

    this->setUpdatesEnabled( false );

    SetTickOptionsDialog dialog( this );

    dialog.numMinorXTicks_spinBox->setValue( gi_numMinorXTicks );
    dialog.numMinorYTicks_spinBox->setValue( gi_numMinorYTicks );
    dialog.TickmarkLength_spinBox->setValue( gi_TickmarkLength );
    dialog.TickmarkWidth_spinBox->setValue( gi_TickmarkWidth );
    dialog.TicklineWidth_spinBox->setValue( gi_TicklineWidth );
    dialog.MinorTicklineWidth_spinBox->setValue( gi_MinorTicklineWidth );
    dialog.MinorTickmarkWidth_spinBox->setValue( gi_MinorTickmarkWidth );

    dialog.drawMajorXTicklines_checkBox->setChecked( gb_drawMajorXTicklines );
    dialog.drawMajorXTicksLeft_checkBox->setChecked( gb_drawMajorXTicksLeft );
    dialog.drawMajorXTicksRight_checkBox->setChecked( gb_drawMajorXTicksRight );
    dialog.drawMajorXTicksInside_checkBox->setChecked( gb_drawMajorXTicksInside );
    dialog.drawMajorXTicksOutside_checkBox->setChecked( gb_drawMajorXTicksOutside );

    dialog.drawMajorYTicklines_checkBox->setChecked( gb_drawMajorYTicklines );
    dialog.drawMajorYTicksTop_checkBox->setChecked( gb_drawMajorYTicksTop );
    dialog.drawMajorYTicksBottom_checkBox->setChecked( gb_drawMajorYTicksBottom );
    dialog.drawMajorYTicksInside_checkBox->setChecked( gb_drawMajorYTicksInside );
    dialog.drawMajorYTicksOutside_checkBox->setChecked( gb_drawMajorYTicksOutside );

    dialog.drawMinorXTicklines_checkBox->setChecked( gb_drawMinorXTicklines );
    dialog.drawMinorXTicksLeft_checkBox->setChecked( gb_drawMinorXTicksLeft );
    dialog.drawMinorXTicksRight_checkBox->setChecked( gb_drawMinorXTicksRight );
    dialog.drawMinorXTicksInside_checkBox->setChecked( gb_drawMinorXTicksInside );
    dialog.drawMinorXTicksOutside_checkBox->setChecked( gb_drawMinorXTicksOutside );

    dialog.drawMinorYTicklines_checkBox->setChecked( gb_drawMinorYTicklines );
    dialog.drawMinorYTicksTop_checkBox->setChecked( gb_drawMinorYTicksTop );
    dialog.drawMinorYTicksBottom_checkBox->setChecked( gb_drawMinorYTicksBottom );
    dialog.drawMinorYTicksInside_checkBox->setChecked( gb_drawMinorYTicksInside );
    dialog.drawMinorYTicksOutside_checkBox->setChecked( gb_drawMinorYTicksOutside );

    if ( gi_PlotOrientation == _SHOWPLOTH_ )
    {
        dialog.drawMajorXTicksLeft_checkBox->setText( tr( "Ticks top" ) );
        dialog.drawMajorXTicksRight_checkBox->setText( tr( "Ticks bottom" ) );
        dialog.drawMajorYTicksTop_checkBox->setText( tr( "Ticks left" ) );
        dialog.drawMajorYTicksBottom_checkBox->setText( tr( "Ticks right" ) );

        dialog.drawMinorXTicksLeft_checkBox->setText( tr( "Ticks top" ) );
        dialog.drawMinorXTicksRight_checkBox->setText( tr( "Ticks bottom" ) );
        dialog.drawMinorYTicksTop_checkBox->setText( tr( "Ticks left" ) );
        dialog.drawMinorYTicksBottom_checkBox->setText( tr( "Ticks right" ) );
    }

    dialog.setTickmarkColor( gc_TickmarkColor );
    dialog.setTicklineColor( gc_TicklineColor );
    dialog.setMinorTicklineColor( gc_MinorTicklineColor );

    dialog.TickmarkLength_spinBox->setFocus();
    dialog.TickmarkLength_spinBox->selectAll();

    dialog.OK_pushButton->setWhatsThis( "Set new tick options" );
    dialog.Cancel_pushButton->setWhatsThis( "Cancel dialog" );

    dialog.move( posDialog );
    dialog.resize( dialog.sizeHint() );
    dialog.show();

// ******************************************************************************************************

    switch ( dialog.exec() )
    {
    case QDialog::Accepted:
        gi_numMinorXTicks = dialog.numMinorXTicks_spinBox->value();
        gi_numMinorYTicks = dialog.numMinorYTicks_spinBox->value();
        gi_TickmarkLength = dialog.TickmarkLength_spinBox->value();
        gi_TickmarkWidth = dialog.TickmarkWidth_spinBox->value();
        gi_TicklineWidth = dialog.TicklineWidth_spinBox->value();
        gi_MinorTickmarkWidth = dialog.MinorTickmarkWidth_spinBox->value();
        gi_MinorTicklineWidth = dialog.MinorTicklineWidth_spinBox->value();

        gb_drawMajorXTicklines    = dialog.drawMajorXTicklines_checkBox->isChecked();
        gb_drawMajorXTicksLeft    = dialog.drawMajorXTicksLeft_checkBox->isChecked();
        gb_drawMajorXTicksRight   = dialog.drawMajorXTicksRight_checkBox->isChecked();
        gb_drawMajorXTicksInside  = dialog.drawMajorXTicksInside_checkBox->isChecked();
        gb_drawMajorXTicksOutside = dialog.drawMajorXTicksOutside_checkBox->isChecked();

        gb_drawMajorYTicklines    = dialog.drawMajorYTicklines_checkBox->isChecked();
        gb_drawMajorYTicksTop     = dialog.drawMajorYTicksTop_checkBox->isChecked();
        gb_drawMajorYTicksBottom  = dialog.drawMajorYTicksBottom_checkBox->isChecked();
        gb_drawMajorYTicksInside  = dialog.drawMajorYTicksInside_checkBox->isChecked();
        gb_drawMajorYTicksOutside = dialog.drawMajorYTicksOutside_checkBox->isChecked();

        gb_drawMinorXTicklines    = dialog.drawMinorXTicklines_checkBox->isChecked();
        gb_drawMinorXTicksLeft    = dialog.drawMinorXTicksLeft_checkBox->isChecked();
        gb_drawMinorXTicksRight   = dialog.drawMinorXTicksRight_checkBox->isChecked();
        gb_drawMinorXTicksInside  = dialog.drawMinorXTicksInside_checkBox->isChecked();
        gb_drawMinorXTicksOutside = dialog.drawMinorXTicksOutside_checkBox->isChecked();

        gb_drawMinorYTicklines    = dialog.drawMinorYTicklines_checkBox->isChecked();
        gb_drawMinorYTicksTop     = dialog.drawMinorYTicksTop_checkBox->isChecked();
        gb_drawMinorYTicksBottom  = dialog.drawMinorYTicksBottom_checkBox->isChecked();
        gb_drawMinorYTicksInside  = dialog.drawMinorYTicksInside_checkBox->isChecked();
        gb_drawMinorYTicksOutside = dialog.drawMinorYTicksOutside_checkBox->isChecked();

        gc_TickmarkColor          = dialog.TickmarkColor();
        gc_TicklineColor          = dialog.TicklineColor();
        gc_MinorTicklineColor     = dialog.MinorTicklineColor();
        break;

    case QDialog::Rejected:
        break;

    default:
        break;
    }

    posDialog = dialog.pos();

    this->setUpdatesEnabled( true );

    doShowPlot();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

SetTickOptionsDialog::SetTickOptionsDialog( QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    connect(OK_pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel_pushButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(TickmarkColor_pushButton, SIGNAL(clicked()), this, SLOT(chosseTickmarkColor()));
    connect(TicklineColor_pushButton, SIGNAL(clicked()), this, SLOT(chosseTicklineColor()));
    connect(MinorTicklineColor_pushButton, SIGNAL(clicked()), this, SLOT(chosseMinorTicklineColor()));
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetTickOptionsDialog::chosseTickmarkColor()
{
    setTickmarkColor( QColorDialog::getColor( this->TickmarkColor(), this, tr( "Select color of tickmarks"), QColorDialog::DontUseNativeDialog ) );

    update();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetTickOptionsDialog::chosseTicklineColor()
{
    setTicklineColor( QColorDialog::getColor( this->TicklineColor(), this, tr( "Select color of ticklines"), QColorDialog::DontUseNativeDialog ) );

    update();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetTickOptionsDialog::chosseMinorTicklineColor()
{
    setMinorTicklineColor( QColorDialog::getColor( this->MinorTicklineColor(), this, tr( "Select color of minor ticklines"), QColorDialog::DontUseNativeDialog ) );

    update();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetTickOptionsDialog::paintEvent( QPaintEvent * /* event */ )
{
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    QPainter painter( this );

    x = this->TickColors_groupBox->pos().x() + this->TickmarkColor_frame->pos().x();
    y = this->TickColors_groupBox->pos().y() + this->TickmarkColor_frame->pos().y();
    w = this->TickmarkColor_frame->width();
    h = this->TickmarkColor_frame->height();

    painter.setBrush( QBrush( TickmarkColor(), Qt::SolidPattern ) );
    painter.drawRect( x, y, w, h );

    x = this->TickColors_groupBox->pos().x() + this->TicklineColor_frame->pos().x();
    y = this->TickColors_groupBox->pos().y() + this->TicklineColor_frame->pos().y();
    w = this->TicklineColor_frame->width();
    h = this->TicklineColor_frame->height();

    painter.setBrush( QBrush( TicklineColor(), Qt::SolidPattern ) );
    painter.drawRect( x, y, w, h );

    x = this->TickColors_groupBox->pos().x() + this->MinorTicklineColor_frame->pos().x();
    y = this->TickColors_groupBox->pos().y() + this->MinorTicklineColor_frame->pos().y();
    w = this->MinorTicklineColor_frame->width();
    h = this->MinorTicklineColor_frame->height();

    painter.setBrush( QBrush( MinorTicklineColor(), Qt::SolidPattern ) );
    painter.drawRect( x, y, w, h );
}
