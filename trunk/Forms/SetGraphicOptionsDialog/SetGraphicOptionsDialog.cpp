// ***********************************************************************************************
// *                                                                                             *
// * SetGraphicOptionsDialog.cpp - Graphic options dialog                                        *
// *                                                                                             *
// * Dr. Rainer Sieger - 2011-07-17                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include <QtGui>

#include "Application.h"
#include "SetGraphicOptionsDialog.h"

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void MainWindow::doSetGraphicOptionsDialog()
{
    saveGraphicOptions();
    saveParameterOptions();

    this->setUpdatesEnabled( false );

    SetGraphicOptionsDialog dialog( this );

    if ( gi_PlotOrientation == _SHOWPLOTV_ )
        dialog.PlotOrientationV_radioButton->setChecked( true );
    else
        dialog.PlotOrientationH_radioButton->setChecked( true );

    if ( gb_Antialiasing == true )
        dialog.AntialiasingOn_radioButton->setChecked( true );
    else
        dialog.AntialiasingOff_radioButton->setChecked( true);

    if ( gb_XReverseGraphRange == true )
        dialog.XReverseGraphRangeOn_radioButton->setChecked( true );
    else
        dialog.XReverseGraphRangeOff_radioButton->setChecked( true);

    dialog.setHeaderTextFont( gf_HeaderTextFont );
    dialog.setHeaderTextColor( gc_HeaderTextColor );
    dialog.setBackgroundColor( gc_BackgroundColor );
    dialog.DrawBackground_checkBox->setChecked( gb_drawBackground );
    dialog.marginLeft_spinBox->setValue( gi_marginLeft );
    dialog.marginRight_spinBox->setValue( gi_marginRight );
    dialog.marginTop_spinBox->setValue( gi_marginTop );
    dialog.marginBottom_spinBox->setValue( gi_marginBottom );

    dialog.marginScale_spinBox->setValue( gi_marginScale );

    dialog.diagramWidth_spinBox->setValue( gi_diagramWidth );
    dialog.diagramHeight_spinBox->setValue( gi_diagramHeight );
    dialog.diagramDistance_spinBox->setValue( gi_diagramDistance );
    dialog.diagramFrameWidth_spinBox->setValue( gi_diagramFrameWidth );
    dialog.setDiagramFrameColor( gc_DiagramFrameColor );

    dialog.fixedDiagramSize_checkBox->setChecked( gb_fixedDiagramSize );

    dialog.marginRight_spinBox->setFocus();
    dialog.marginRight_spinBox->selectAll();

    dialog.OK_pushButton->setWhatsThis( "Close dialog" );
    dialog.Cancel_pushButton->setWhatsThis( "Cancel dialog" );

    dialog.move( posDialog );
    dialog.resize( dialog.sizeHint() );
    dialog.show();

// ******************************************************************************************************

    switch ( dialog.exec() )
    {
    case QDialog::Accepted:
        if ( dialog.PlotOrientationV_radioButton->isChecked() )
            gi_PlotOrientation = _SHOWPLOTV_;
        else
            gi_PlotOrientation = _SHOWPLOTH_;

        gb_Antialiasing         = dialog.AntialiasingOn_radioButton->isChecked();
        gb_XReverseGraphRange   = dialog.XReverseGraphRangeOn_radioButton->isChecked();
        gb_drawBackground       = dialog.DrawBackground_checkBox->isChecked();
        gb_fixedDiagramSize     = dialog.fixedDiagramSize_checkBox->isChecked();

        gi_diagramHeight        = dialog.diagramHeight_spinBox->value();
        gi_diagramWidth         = dialog.diagramWidth_spinBox->value();
        gi_diagramDistance      = dialog.diagramDistance_spinBox->value();
        gi_diagramFrameWidth    = dialog.diagramFrameWidth_spinBox->value();

        gi_marginLeft           = dialog.marginLeft_spinBox->value();
        gi_marginRight          = dialog.marginRight_spinBox->value();
        gi_marginTop            = dialog.marginTop_spinBox->value();
        gi_marginBottom         = dialog.marginBottom_spinBox->value();
        gi_marginScale          = dialog.marginScale_spinBox->value();

        gf_HeaderTextFont       = dialog.HeaderTextFont();
        gc_HeaderTextColor      = dialog.HeaderTextColor();
        gc_BackgroundColor      = dialog.BackgroundColor();
        gc_DiagramFrameColor    = dialog.DiagramFrameColor();
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

SetGraphicOptionsDialog::SetGraphicOptionsDialog( QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    connect(OK_pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel_pushButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(fixedDiagramSize_checkBox, SIGNAL(stateChanged(int)), this, SLOT(setFixedDiagramSizeOptionsEnabled(int)));
    connect(BackgroundColor_pushButton, SIGNAL(clicked()), this, SLOT(chosseBackgroundColor()));
    connect(DiagramFrameColor_pushButton, SIGNAL(clicked()), this, SLOT(chosseDiagramFrameColor()));
    connect(HeaderTextColor_pushButton, SIGNAL(clicked()), this, SLOT(chosseHeaderTextColor()));
    connect(HeaderTextFont_pushButton, SIGNAL(clicked()), this, SLOT(chosseHeaderTextFont()));

    this->setFixedDiagramSizeOptionsEnabled( Qt::Unchecked );
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetGraphicOptionsDialog::setFixedDiagramSizeOptionsEnabled( int state )
{
    if ( state == Qt::Checked )
    {
        this->diagramWidth_spinBox->setEnabled( true );
        this->diagramHeight_spinBox->setEnabled( true );
    }
    else
    {
        this->diagramWidth_spinBox->setEnabled( false );
        this->diagramHeight_spinBox->setEnabled( false );
    }
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetGraphicOptionsDialog::chosseBackgroundColor()
{
    setBackgroundColor( QColorDialog::getColor( this->BackgroundColor(), this, tr( "Select color of background"), QColorDialog::DontUseNativeDialog ) );

    update();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetGraphicOptionsDialog::chosseDiagramFrameColor()
{
    setDiagramFrameColor( QColorDialog::getColor( this->DiagramFrameColor(), this, tr( "Select color of diagram frame"), QColorDialog::DontUseNativeDialog ) );

    update();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetGraphicOptionsDialog::chosseHeaderTextColor()
{
    setHeaderTextColor( QColorDialog::getColor( this->HeaderTextColor(), this, tr( "Select color of header"), QColorDialog::DontUseNativeDialog ) );

    update();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetGraphicOptionsDialog::chosseHeaderTextFont()
{
    bool OK;

    QFont newFont = QFontDialog::getFont( &OK, HeaderTextFont(), this, tr( "Choose font" ), QFontDialog::DontUseNativeDialog );

    if( OK == true )
        setHeaderTextFont( newFont );
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetGraphicOptionsDialog::paintEvent( QPaintEvent * /* event */ )
{
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    QPainter painter( this );

    x = this->TextOptions_groupBox->pos().x() + this->TextColor_frame->pos().x();
    y = this->TextOptions_groupBox->pos().y() + this->TextColor_frame->pos().y();
    w = this->TextColor_frame->width();
    h = this->TextColor_frame->height();

    painter.setBrush( QBrush( HeaderTextColor(), Qt::SolidPattern ) );
    painter.drawRect( x, y, w, h );

    x = this->GraphicBackground_groupBox->pos().x() + this->BackgroundColor_frame->pos().x();
    y = this->GraphicBackground_groupBox->pos().y() + this->BackgroundColor_frame->pos().y();
    w = this->BackgroundColor_frame->width();
    h = this->BackgroundColor_frame->height();

    painter.setBrush( QBrush( BackgroundColor(), Qt::SolidPattern ) );
    painter.drawRect( x, y, w, h );

    x = this->DiagramFrame_groupBox->pos().x() + this->DiagramFrameColor_frame->pos().x();
    y = this->DiagramFrame_groupBox->pos().y() + this->DiagramFrameColor_frame->pos().y();
    w = this->DiagramFrameColor_frame->width();
    h = this->DiagramFrameColor_frame->height();

    painter.setBrush( QBrush( DiagramFrameColor(), Qt::SolidPattern ) );
    painter.drawRect( x, y, w, h );
}
