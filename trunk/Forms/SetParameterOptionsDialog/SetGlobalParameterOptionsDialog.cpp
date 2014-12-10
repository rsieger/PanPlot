// ***********************************************************************************************
// *                                                                                             *
// * SetGlobalParameterOptionsDialog.cpp - Parameter options dialog, global                      *
// *                                                                                             *
// * Dr. Rainer Sieger - 2011-07-17                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include <QtGui>

#include "Application.h"
#include "SetGlobalParameterOptionsDialog.h"

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void MainWindow::doSetGlobalParameterOptionsDialog()
{
    saveGraphicOptions();
    saveParameterOptions();

    this->setUpdatesEnabled( false );

    SetGlobalParameterOptionsDialog dialog( this );

    if ( ( gi_PlotOrientation == _SHOWPLOTH_ ) && ( gi_ParameterOrientation == 45 ) )
        gi_ParameterOrientation = 0;

    dialog.setParameterOrientationRadioButton( gi_ParameterOrientation );

    if ( gi_PlotOrientation == _SHOWPLOTH_ )
        dialog.ParameterOrientation45RadioButton->hide();

    dialog.setPatternComboBox( gi_ColorizedPattern );

    dialog.DrawDiagramBackground_checkBox->setChecked( gb_drawDiagramBackground );
    dialog.DrawMarkers_checkBox->setChecked( gb_drawMarkers );
    dialog.DrawLines_checkBox->setChecked( gb_drawLines );
    dialog.DrawColorized_checkBox->setChecked( gb_drawColorized );
    dialog.DrawDataText_checkBox->setChecked( gb_drawDataText );

    dialog.MarkerSize_spinBox->setValue( gi_MarkerSize );
    dialog.LineWidth_spinBox->setValue( gi_LineWidth );

    dialog.setDiagramBackgroundColor( gc_DiagramBackgroundColor );
    dialog.setMarkerColor( gc_MarkerColor );
    dialog.setLineColor( gc_LineColor );
    dialog.setColorizedColor( gc_ColorizedGreaterRefColor );
    dialog.setDataTextColor( gc_DataTextColor );

    dialog.setDataTextFont( gf_DataTextFont );

    dialog.OK_pushButton->setWhatsThis( "Close dialog" );
    dialog.Cancel_pushButton->setWhatsThis( "Cancel dialog" );

    dialog.move( posDialog );
    dialog.resize( dialog.sizeHint() );
    dialog.show();

// ******************************************************************************************************

    switch ( dialog.exec() )
    {
    case QDialog::Accepted:
        setUpdateGlobalParameterOptions( true );

        gb_drawDiagramBackground    = dialog.DrawDiagramBackground_checkBox->isChecked();
        gb_drawMarkers              = dialog.DrawMarkers_checkBox->isChecked();
        gb_drawLines                = dialog.DrawLines_checkBox->isChecked();
        gb_drawColorized            = dialog.DrawColorized_checkBox->isChecked();
        gb_drawDataText             = dialog.DrawDataText_checkBox->isChecked();

        gi_MarkerSize               = dialog.MarkerSize_spinBox->value();
        gi_LineWidth                = dialog.LineWidth_spinBox->value();
        gi_ColorizedPattern         = dialog.PatternComboBox();
        gi_ParameterOrientation     = dialog.ParameterOrientationRadioButton();

        gc_DiagramBackgroundColor   = dialog.DiagramBackgroundColor();
        gc_MarkerColor              = dialog.MarkerColor();
        gc_LineColor                = dialog.LineColor();
        gc_ColorizedGreaterRefColor = dialog.ColorizedColor();
        gc_DataTextColor            = dialog.DataTextColor();

        gf_DataTextFont             = dialog.DataTextFont();
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

SetGlobalParameterOptionsDialog::SetGlobalParameterOptionsDialog( QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    connect(OK_pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel_pushButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(DiagramBackgroundColor_pushButton, SIGNAL(clicked()), this, SLOT(chosseDiagramBackgroundColor()));
    connect(MarkerColor_pushButton, SIGNAL(clicked()), this, SLOT(chosseMarkerColor()));
    connect(LineColor_pushButton, SIGNAL(clicked()), this, SLOT(chosseLineColor()));
    connect(ColorizedColor_pushButton, SIGNAL(clicked()), this, SLOT(chosseColorizedColor()));
    connect(DataTextColor_pushButton, SIGNAL(clicked()), this, SLOT(chosseDataTextColor()));
    connect(DataTextFont_pushButton, SIGNAL(clicked()), this, SLOT(chosseDataTextFont()));
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetGlobalParameterOptionsDialog::setParameterOrientationRadioButton( int i_ParameterOrientation )
{
    switch ( i_ParameterOrientation )
    {
    case 90:
        this->ParameterOrientation90RadioButton->setChecked( true );
        break;
    case 45:
        this->ParameterOrientation45RadioButton->setChecked( true );
        break;
    default:
        this->ParameterOrientation0RadioButton->setChecked( true );
        break;
    }
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

int SetGlobalParameterOptionsDialog::ParameterOrientationRadioButton()
{
    if ( this->ParameterOrientation45RadioButton->isChecked() )
        return( 45 );

    if ( this->ParameterOrientation90RadioButton->isChecked() )
        return( 90 );

    return( 0 ); // dialog.ParameterOrientation0RadioButton->isChecked()
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetGlobalParameterOptionsDialog::setPatternComboBox( int i_Pattern )
{
// Pattern number -> list number
    this->Pattern_comboBox->addItem( tr( "No brush pattern" ) );                          // 0  -> 0
    this->Pattern_comboBox->addItem( tr( "Uniform color" ) );                             // 1  -> 1
//  this->Pattern_comboBox->addItem( tr( "Extremely dense brush pattern" ) );             // 2  ->
//  this->Pattern_comboBox->addItem( tr( "Very dense brush pattern" ) );                  // 3  ->
//  this->Pattern_comboBox->addItem( tr( "Somewhat dense brush pattern" ) );              // 4  ->
    this->Pattern_comboBox->addItem( tr( "Half dense brush pattern" ) );                  // 5  -> 2
//  this->Pattern_comboBox->addItem( tr( "Somewhat sparse brush pattern" ) );             // 6  ->
//  this->Pattern_comboBox->addItem( tr( "Very sparse brush pattern" ) );                 // 7  ->
//  this->Pattern_comboBox->addItem( tr( "Extremely sparse brush pattern" ) );            // 8  ->
    this->Pattern_comboBox->addItem( tr( "Horizontal lines" ) );                          // 9  -> 3
    this->Pattern_comboBox->addItem( tr( "Vertical lines" ) );                            // 10 -> 4
    this->Pattern_comboBox->addItem( tr( "Crossing horizontal and vertical lines" ) );    // 11 -> 5
    this->Pattern_comboBox->addItem( tr( "Backward diagonal lines." ) );                  // 12 -> 6
    this->Pattern_comboBox->addItem( tr( "Forward diagonal lines" ) );                    // 13 -> 7
    this->Pattern_comboBox->addItem( tr( "Crossing diagonal lines" ) );                   // 14 -> 8

    switch ( i_Pattern )
    {
    case 0:
    case 1:
        this->Pattern_comboBox->setCurrentIndex( i_Pattern );
        break;
    case 5:
        this->Pattern_comboBox->setCurrentIndex( i_Pattern - 3 );
        break;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        this->Pattern_comboBox->setCurrentIndex( i_Pattern - 6 );
        break;
    default:
        this->Pattern_comboBox->setCurrentIndex( 0 );
        break;
    }
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

int SetGlobalParameterOptionsDialog::PatternComboBox()
{
    int i_Pattern = this->Pattern_comboBox->currentIndex();

    switch ( i_Pattern )
    {
    case 0:
    case 1:
        return( i_Pattern );
        break;
    case 2:
        return( i_Pattern + 3 );
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        return( i_Pattern + 6 );
        break;
    default:
        return( 0 );
        break;
    }

    return( 0 );
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetGlobalParameterOptionsDialog::chosseDataTextFont()
{
    bool OK;

    QFont newFont = QFontDialog::getFont( &OK, DataTextFont(), this, tr( "Choose font" ), QFontDialog::DontUseNativeDialog );

    if( OK == true )
        setDataTextFont( newFont );
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetGlobalParameterOptionsDialog::chosseDataTextColor()
{
    setDataTextColor( QColorDialog::getColor( this->DataTextColor(), this, tr( "Select color of header"), QColorDialog::DontUseNativeDialog ) );

    update();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetGlobalParameterOptionsDialog::chosseDiagramBackgroundColor()
{
    setDiagramBackgroundColor( QColorDialog::getColor ( this->DiagramBackgroundColor(), this, tr( "Select color of diagram background"), QColorDialog::DontUseNativeDialog ) );

    update();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetGlobalParameterOptionsDialog::chosseMarkerColor()
{
    setMarkerColor( QColorDialog::getColor( this->MarkerColor(), this, tr( "Select color of markers"), QColorDialog::DontUseNativeDialog ) );

    update();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetGlobalParameterOptionsDialog::chosseLineColor()
{
    setLineColor( QColorDialog::getColor( this->LineColor(), this, tr( "Select color of lines"), QColorDialog::DontUseNativeDialog ) );

    update();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetGlobalParameterOptionsDialog::chosseColorizedColor()
{
    setColorizedColor( QColorDialog::getColor( this->ColorizedColor(), this, tr( "Select color"), QColorDialog::DontUseNativeDialog ) );

    update();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetGlobalParameterOptionsDialog::paintEvent( QPaintEvent * /* event */ )
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

    painter.setBrush( QBrush( DataTextColor(), Qt::SolidPattern ) );
    painter.drawRect( x, y, w, h );

    x = this->DiagramBackground_groupBox->pos().x() + this->DiagramBackgroundColor_frame->pos().x();
    y = this->DiagramBackground_groupBox->pos().y() + this->DiagramBackgroundColor_frame->pos().y();
    w = this->DiagramBackgroundColor_frame->width();
    h = this->DiagramBackgroundColor_frame->height();

    painter.setBrush( QBrush( DiagramBackgroundColor(), Qt::SolidPattern ) );
    painter.drawRect( x, y, w, h );

    x = this->Marker_groupBox->pos().x() + this->MarkerColor_frame->pos().x();
    y = this->Marker_groupBox->pos().y() + this->MarkerColor_frame->pos().y();
    w = this->MarkerColor_frame->width();
    h = this->MarkerColor_frame->height();

    painter.setBrush( QBrush( MarkerColor(), Qt::SolidPattern ) );
    painter.drawRect( x, y, w, h );

    x = this->Lines_groupBox->pos().x() + this->LinesColor_frame->pos().x();
    y = this->Lines_groupBox->pos().y() + this->LinesColor_frame->pos().y();
    w = this->LinesColor_frame->width();
    h = this->LinesColor_frame->height();

    painter.setBrush( QBrush( LineColor(), Qt::SolidPattern ) );
    painter.drawRect( x, y, w, h );

    x = this->Colorized_groupBox->pos().x() + this->ColorizedColor_frame->pos().x();
    y = this->Colorized_groupBox->pos().y() + this->ColorizedColor_frame->pos().y();
    w = this->ColorizedColor_frame->width();
    h = this->ColorizedColor_frame->height();

    painter.setBrush( QBrush( ColorizedColor(), Qt::SolidPattern ) );
    painter.drawRect( x, y, w, h );
}

