// ***********************************************************************************************
// *                                                                                             *
// * SetParameterOptionsDialog.cpp - Parameter options dialog                                    *
// *                                                                                             *
// * Dr. Rainer Sieger - 2013-08-20                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include <QtGui>

#include "Application.h"
#include "SetParameterOptionsDialog.h"

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void MainWindow::doSetParameterOptionsDialog()
{
    QAction *action    = qobject_cast<QAction *>( sender() );

    int i              = action->data().toInt();

    this->setUpdatesEnabled( false );

    SetParameterOptionsDialog dialog( this );

// ***********************************************************************************************************************

    dialog.setWindowTitle( gv_PS.at( i ).Parameter() );

    dialog.setPatternComboBox( gv_PS.at( i ).Pattern() );
    dialog.setYReverseRangeRadioButton( gv_PS.at( i ).YReverseGraphRange() );

    dialog.DrawDiagramBackground_checkBox->setChecked( gv_PS.at( i ).drawDiagramBackground() );
    dialog.DrawMarkers_checkBox->setChecked( gv_PS.at( i ).drawMarker() );
    dialog.DrawLines_checkBox->setChecked( gv_PS.at( i ).drawLine() );
    dialog.DrawColorized_checkBox->setChecked( gv_PS.at( i ).drawColorized() );
    dialog.DrawDataText_checkBox->setChecked( gv_PS.at( i ).drawDataText() );
    dialog.DrawRefline_checkBox->setChecked( gv_PS.at( i ).drawYRefline() );

    dialog.setDiagramBackgroundColor( gv_PS.at( i ).DiagramBackgroundColor() );
    dialog.setMarkerColor( gv_PS.at( i ).MarkerColor() );
    dialog.setLineColor( gv_PS.at( i ).LineColor() );
    dialog.setColorizedGreaterRefColor( gv_PS.at( i ).ColorizedGreaterRefColor() );
    dialog.setColorizedLessRefColor( gv_PS.at( i ).ColorizedLessRefColor() );
    dialog.setDataTextColor( gv_PS.at( i ).DataTextColor() );
    dialog.setReflineColor( gv_PS.at( i ).YReflineColor() );

    dialog.MarkerSize_spinBox->setValue( gv_PS.at( i ).MarkerSize() );
    dialog.LineWidth_spinBox->setValue( gv_PS.at( i ).LineWidth() );
    dialog.ReflineWidth_spinBox->setValue( gv_PS.at( i ).YReflineWidth() );

    dialog.setDataTextFont( gv_PS.at( i ).DataTextFont() );

    dialog.Precision_spinBox->setRange( 0, 10 );
    dialog.ReflineWidth_spinBox->setRange( 0, 10 );

    dialog.setAutoNiceLabel( gv_PS.at( i ).AutoYnFrac(), gv_PS.at( i ).AutoYTickmarkSpacing(),
                             gv_PS.at( i ).AutoYGraphMin(), gv_PS.at( i ).AutoYGraphMax() );

    dialog.setManualNiceLabel( gv_PS.at( i ).ManualYnFrac(), gv_PS.at( i ).ManualYTickmarkSpacing(),
                               gv_PS.at( i ).ManualYGraphMin(), gv_PS.at( i ).ManualYGraphMax() );

    if ( gv_PS.at( i ).useManualScaleSettings() == false )
        dialog.setDialogItems( Qt::Unchecked );
    else
        dialog.useManualScaleSettings_checkBox->setChecked( gv_PS.at( i ).useManualScaleSettings() );

    dialog.ReflineValue_lineEdit->setText( QString( "%1" ).arg( gv_PS.at( i ).YRefline() ) );

    dialog.OK_pushButton->setWhatsThis( "Close dialog" );
    dialog.Cancel_pushButton->setWhatsThis( "Cancel dialog" );

    dialog.adjustSize();
    dialog.move( posDialog );
    dialog.show();

// ******************************************************************************************************

    switch ( dialog.exec() )
    {
    case QDialog::Accepted:
        setUpdateGlobalParameterOptions( false );

        gv_PS[i].setYReverseGraphRange( dialog.YReverseGraphRangeOn_radioButton->isChecked() );
        gv_PS[i].setDiagramBackgroundOptions( dialog.DrawDiagramBackground_checkBox->isChecked(), dialog.DiagramBackgroundColor() );
        gv_PS[i].setMarkerOptions( dialog.DrawMarkers_checkBox->isChecked(), dialog.MarkerSize_spinBox->value(), dialog.MarkerColor() );
        gv_PS[i].setLineOptions( dialog.DrawLines_checkBox->isChecked(), dialog.LineWidth_spinBox->value(), dialog.LineColor() );
        gv_PS[i].setColorizedOptions( dialog.DrawColorized_checkBox->isChecked(), dialog.PatternComboBox(), dialog.ColorizedGreaterRefColor(), dialog.ColorizedLessRefColor() );
        gv_PS[i].setDataTextOptions( dialog.DrawDataText_checkBox->isChecked(), dialog.DataTextFont(), dialog.DataTextColor() );
        gv_PS[i].setYReflineOptions( dialog.DrawRefline_checkBox->isChecked(), dialog.ReflineWidth_spinBox->value(), dialog.ReflineColor(), dialog.ReflineValue_lineEdit->text().toDouble() );
        gv_PS[i].setUseManualScaleSettings( dialog.useManualScaleSettings_checkBox->isChecked() );

        if ( gv_PS.at( i ).useManualScaleSettings() == true )
            gv_PS[i].setManualYNiceLabel( dialog.Precision_spinBox->value(), dialog.TickmarkSpacing_lineEdit->text().toDouble(),
                                          dialog.GraphicMinimum_lineEdit->text().toDouble(), dialog.GraphicMaximum_lineEdit->text().toDouble() );

        gc_ColorizedGreaterRefColor = dialog.ColorizedGreaterRefColor();
        gc_ColorizedLessRefColor    = dialog.ColorizedLessRefColor();
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

SetParameterOptionsDialog::SetParameterOptionsDialog( QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    connect(OK_pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel_pushButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(DiagramBackgroundColor_pushButton, SIGNAL(clicked()), this, SLOT(chosseDiagramBackgroundColor()));
    connect(MarkerColor_pushButton, SIGNAL(clicked()), this, SLOT(chosseMarkerColor()));
    connect(LineColor_pushButton, SIGNAL(clicked()), this, SLOT(chosseLineColor()));
    connect(ColorizedGreaterRefColor_pushButton, SIGNAL(clicked()), this, SLOT(chosseColorizedGreaterRefColor()));
    connect(ColorizedLessRefColor_pushButton, SIGNAL(clicked()), this, SLOT(chosseColorizedLessRefColor()));
    connect(ReflineColor_pushButton, SIGNAL(clicked()), this, SLOT(chosseReflineColor()));
    connect(DataTextColor_pushButton, SIGNAL(clicked()), this, SLOT(chosseDataTextColor()));
    connect(DataTextFont_pushButton, SIGNAL(clicked()), this, SLOT(chosseDataTextFont()));

    connect(useManualScaleSettings_checkBox, SIGNAL(stateChanged(int)), this, SLOT(setDialogItems(int)));

    connect(Precision_spinBox, SIGNAL(valueChanged(int)), this, SLOT(setManuallyPrecision(int)));

    connect(GraphicMinimum_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(setManuallyScale(QString)));
    connect(GraphicMaximum_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(setManuallyScale(QString)));
    connect(TickmarkSpacing_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(setManuallyScale(QString)));

    connect(GraphicMinimum_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableOK()));
    connect(GraphicMaximum_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableOK()));
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetParameterOptionsDialog::setYReverseRangeRadioButton( bool b_YReverseGraphRange )
{
    if ( b_YReverseGraphRange == true )
        this->YReverseGraphRangeOn_radioButton->setChecked( true );
    else
        this->YReverseGraphRangeOff_radioButton->setChecked( true);
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetParameterOptionsDialog::setPatternComboBox( int i_Pattern )
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

int SetParameterOptionsDialog::PatternComboBox()
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

void SetParameterOptionsDialog::chosseDataTextFont()
{
    bool OK;

    QFont newFont = QFontDialog::getFont( &OK, DataTextFont(), this, tr( "Choose font" ), QFontDialog::DontUseNativeDialog );

    if( OK == true )
        setDataTextFont( newFont );
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetParameterOptionsDialog::chosseDataTextColor()
{
    setDataTextColor( QColorDialog::getColor( this->DataTextColor(), this, tr( "Select color of header"), QColorDialog::DontUseNativeDialog ) );

    update();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetParameterOptionsDialog::chosseReflineColor()
{
    setReflineColor( QColorDialog::getColor( this->ReflineColor(), this, tr( "Select color of reference line"), QColorDialog::DontUseNativeDialog ) );

    update();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetParameterOptionsDialog::chosseDiagramBackgroundColor()
{
    setDiagramBackgroundColor( QColorDialog::getColor ( this->DiagramBackgroundColor(), this, tr( "Select color diagram background"), QColorDialog::DontUseNativeDialog ) );

    update();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetParameterOptionsDialog::chosseMarkerColor()
{
    setMarkerColor( QColorDialog::getColor( this->MarkerColor(), this, tr( "Select color of markers"), QColorDialog::DontUseNativeDialog ) );

    update();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetParameterOptionsDialog::chosseLineColor()
{
    setLineColor( QColorDialog::getColor( this->LineColor(), this, tr( "Select color of lines"), QColorDialog::DontUseNativeDialog ) );

    update();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetParameterOptionsDialog::chosseColorizedGreaterRefColor()
{
    setColorizedGreaterRefColor( QColorDialog::getColor( this->ColorizedGreaterRefColor(), this, tr( "Select color"), QColorDialog::DontUseNativeDialog ) );

    update();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetParameterOptionsDialog::chosseColorizedLessRefColor()
{
    setColorizedLessRefColor( QColorDialog::getColor( this->ColorizedLessRefColor(), this, tr( "Select color"), QColorDialog::DontUseNativeDialog ) );

    update();
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetParameterOptionsDialog::paintEvent( QPaintEvent * /* event */ )
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

    x = this->Colorized_groupBox->pos().x() + this->ColorizedGreaterRefColor_frame->pos().x();
    y = this->Colorized_groupBox->pos().y() + this->ColorizedGreaterRefColor_frame->pos().y();
    w = this->ColorizedGreaterRefColor_frame->width();
    h = this->ColorizedGreaterRefColor_frame->height();

    painter.setBrush( QBrush( ColorizedGreaterRefColor(), Qt::SolidPattern ) );
    painter.drawRect( x, y, w, h );

    x = this->Colorized_groupBox->pos().x() + this->ColorizedLessRefColor_frame->pos().x();
    y = this->Colorized_groupBox->pos().y() + this->ColorizedLessRefColor_frame->pos().y();
    w = this->ColorizedLessRefColor_frame->width();
    h = this->ColorizedLessRefColor_frame->height();

    painter.setBrush( QBrush( ColorizedLessRefColor(), Qt::SolidPattern ) );
    painter.drawRect( x, y, w, h );

    x = this->Refline_groupBox->pos().x() + this->ReflineColor_frame->pos().x();
    y = this->Refline_groupBox->pos().y() + this->ReflineColor_frame->pos().y();
    w = this->ReflineColor_frame->width();
    h = this->ReflineColor_frame->height();

    painter.setBrush( QBrush( ReflineColor(), Qt::SolidPattern ) );
    painter.drawRect( x, y, w, h );
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetParameterOptionsDialog::setDialogItems( int i_State )
{
    if ( i_State == Qt::Checked )
    {
        this->Precision_label->setEnabled( true );
        this->GraphicMinimum_label->setEnabled( true );
        this->GraphicMaximum_label->setEnabled( true );
        this->TickmarkSpacing_label->setEnabled( true );

        this->Precision_spinBox->setEnabled( true );
        this->GraphicMinimum_lineEdit->setEnabled( true );
        this->GraphicMaximum_lineEdit->setEnabled( true );
        this->TickmarkSpacing_lineEdit->setEnabled( true );

        this->Precision_spinBox->setValue( this->ManualPrecision() );
        this->GraphicMinimum_lineEdit->setText( QString( "%1" ).arg( this->ManualGraphMin(), 0, 'f', this->ManualPrecision() ) );
        this->GraphicMaximum_lineEdit->setText( QString( "%1" ).arg( this->ManualGraphMax(), 0, 'f', this->ManualPrecision() ) );
        this->TickmarkSpacing_lineEdit->setText( QString( "%1" ).arg( this->ManualTickmarkSpacing(), 0, 'f', this->ManualPrecision() ) );
    }
    else
    {
        if ( DialogItemsNotEmpty() == true )
            this->setManualNiceLabel( this->Precision_spinBox->value(), this->TickmarkSpacing_lineEdit->text().toDouble(),
                                      this->GraphicMinimum_lineEdit->text().toDouble(), this->GraphicMaximum_lineEdit->text().toDouble() );

        this->Precision_label->setEnabled( false );
        this->GraphicMinimum_label->setEnabled( false );
        this->GraphicMaximum_label->setEnabled( false );
        this->TickmarkSpacing_label->setEnabled( false );

        this->Precision_spinBox->setEnabled( false );
        this->GraphicMinimum_lineEdit->setEnabled( false );
        this->GraphicMaximum_lineEdit->setEnabled( false );
        this->TickmarkSpacing_lineEdit->setEnabled( false );

        this->Precision_spinBox->setValue( this->AutoPrecision() );
        this->GraphicMinimum_lineEdit->setText( QString( "%1" ).arg( this->AutoGraphMin(), 0, 'f', this->AutoPrecision() ) );
        this->GraphicMaximum_lineEdit->setText( QString( "%1" ).arg( this->AutoGraphMax(), 0, 'f', this->AutoPrecision() ) );
        this->TickmarkSpacing_lineEdit->setText( QString( "%1" ).arg( this->AutoTickmarkSpacing(), 0, 'f', this->AutoPrecision() ) );
    }
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetParameterOptionsDialog::setManuallyScale( QString s_Value )
{
    if ( this->useManualScaleSettings_checkBox->isChecked() == true )
    {
        if ( s_Value.section( ".", 1, 1 ).size() > this->Precision_spinBox->value() )
        {
            this->Precision_spinBox->setValue( s_Value.section( ".", 1, 1 ).size() );
            this->setManualNiceLabel( this->Precision_spinBox->value(), this->TickmarkSpacing_lineEdit->text().toDouble(),
                                      this->GraphicMinimum_lineEdit->text().toDouble(), this->GraphicMaximum_lineEdit->text().toDouble() );
        }
    }
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetParameterOptionsDialog::setManuallyPrecision( int i_Precision )
{
    if ( this->useManualScaleSettings_checkBox->isChecked() == true )
    {
        if ( ( i_Precision > this->ManualPrecision() ) && ( DialogItemsNotEmpty() == true ) )
        {
            this->GraphicMinimum_lineEdit->setText( QString( "%1" ).arg( this->GraphicMinimum_lineEdit->text().toDouble(), 0, 'f', i_Precision ) );
            this->GraphicMaximum_lineEdit->setText( QString( "%1" ).arg( this->GraphicMaximum_lineEdit->text().toDouble(), 0, 'f', i_Precision ) );
            this->TickmarkSpacing_lineEdit->setText( QString( "%1" ).arg( this->TickmarkSpacing_lineEdit->text().toDouble(), 0, 'f', i_Precision ) );

            this->setManualNiceLabel( this->Precision_spinBox->value(), this->TickmarkSpacing_lineEdit->text().toDouble(),
                                      this->GraphicMinimum_lineEdit->text().toDouble(), this->GraphicMaximum_lineEdit->text().toDouble() );
        }
        else
        {
            this->GraphicMinimum_lineEdit->setText( QString( "%1" ).arg( this->ManualGraphMin(), 0, 'f', i_Precision ) );
            this->GraphicMaximum_lineEdit->setText( QString( "%1" ).arg( this->ManualGraphMax(), 0, 'f', i_Precision ) );
            this->TickmarkSpacing_lineEdit->setText( QString( "%1" ).arg( this->ManualTickmarkSpacing(), 0, 'f', i_Precision ) );
        }
    }
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

bool SetParameterOptionsDialog::DialogItemsNotEmpty()
{
    if ( this->GraphicMinimum_lineEdit->text().isEmpty() == true )
        return( false );

    if ( this->GraphicMaximum_lineEdit->text().isEmpty() == true )
        return( false );

    if ( this->TickmarkSpacing_lineEdit->text().isEmpty() == true )
        return( false );

    return( true );
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetParameterOptionsDialog::enableOK()
{
    if ( this->GraphicMinimum_lineEdit->text().toDouble() >= this->GraphicMaximum_lineEdit->text().toDouble() )
        this->OK_pushButton->setEnabled( false );
    else
        this->OK_pushButton->setEnabled( true );
}
