// ***********************************************************************************************
// *                                                                                             *
// * SetXAxisOptionsFloatDialog.cpp - X axis options dialog, float                               *
// *                                                                                             *
// * Dr. Rainer Sieger - 2012-06-08                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include <QtGui>
#include <QtDebug>

#include "Application.h"
#include "SetXAxisOptionsFloatDialog.h"

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void MainWindow::doSetXAxisOptionsFloatDialog()
{
    int XAxisParameterID = gv_PP.at( 0 );

    saveGraphicOptions();
    saveParameterOptions();

    this->setUpdatesEnabled( false );

    SetXAxisOptionsFloatDialog dialog( this );

// ***********************************************************************************************************************

    dialog.Precision_spinBox->setRange( 0, 10 );
    dialog.ReflineWidth_spinBox->setRange( 0, 10 );

    dialog.setAutoNiceLabel( gv_PS.at( XAxisParameterID ).AutoYnFrac(), gv_PS.at( XAxisParameterID ).AutoYTickmarkSpacing(),
                             gv_PS.at( XAxisParameterID ).AutoYGraphMin(), gv_PS.at( XAxisParameterID ).AutoYGraphMax() );

    dialog.setManualNiceLabel( gv_PS.at( XAxisParameterID ).ManualYnFrac(), gv_PS.at( XAxisParameterID ).ManualYTickmarkSpacing(),
                               gv_PS.at( XAxisParameterID ).ManualYGraphMin(), gv_PS.at( XAxisParameterID ).ManualYGraphMax() );

    if ( gb_manuallyXScale == false )
        dialog.setDialogItems( Qt::Unchecked );
    else
        dialog.useManualScaleSettings_checkBox->setChecked( gb_manuallyXScale );

    dialog.DrawRefline_checkBox->setChecked( gv_PS.at( XAxisParameterID ).drawXRefline() );
    dialog.ReflineWidth_spinBox->setValue( gv_PS.at( XAxisParameterID ).XReflineWidth() );
    dialog.ReflineValue_lineEdit->setText( QString( "%1" ).arg( gv_PS.at( XAxisParameterID ).XRefline() ) );
    dialog.setReflineColor( gv_PS.at( XAxisParameterID ).XReflineColor() );

    dialog.OK_pushButton->setWhatsThis( "Set new options" );
    dialog.Cancel_pushButton->setWhatsThis( "Cancel dialog" );

    dialog.move( posDialog );
    dialog.resize( dialog.sizeHint() );
    dialog.show();

// ******************************************************************************************************

    switch ( dialog.exec() )
    {
    case QDialog::Accepted:
        gb_manuallyXScale = dialog.useManualScaleSettings_checkBox->isChecked();

        gv_PS[XAxisParameterID].setXReflineOptions( dialog.DrawRefline_checkBox->isChecked(), dialog.ReflineWidth_spinBox->value(), dialog.ReflineColor(), dialog.ReflineValue_lineEdit->text().toDouble() );

        if ( gb_manuallyXScale == true )
            gv_PS[XAxisParameterID].setManualYNiceLabel( dialog.Precision_spinBox->value(), dialog.TickmarkSpacing_lineEdit->text().toDouble(),
                                                         dialog.GraphicMinimum_lineEdit->text().toDouble(), dialog.GraphicMaximum_lineEdit->text().toDouble() );
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

SetXAxisOptionsFloatDialog::SetXAxisOptionsFloatDialog( QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    connect(OK_pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel_pushButton, SIGNAL(clicked()), this, SLOT(reject()));

    connect(useManualScaleSettings_checkBox, SIGNAL(stateChanged(int)), this, SLOT(setDialogItems(int)));

    connect(Precision_spinBox, SIGNAL(valueChanged(int)), this, SLOT(setManuallyPrecision(int)));

    connect(GraphicMinimum_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(setManuallyScale(QString)));
    connect(GraphicMaximum_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(setManuallyScale(QString)));
    connect(TickmarkSpacing_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(setManuallyScale(QString)));

    connect(GraphicMinimum_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableOK()));
    connect(GraphicMaximum_lineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableOK()));

    connect(ReflineColor_pushButton, SIGNAL(clicked()), this, SLOT(chosseReflineColor()));
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetXAxisOptionsFloatDialog::setDialogItems( int i_State )
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

void SetXAxisOptionsFloatDialog::setManuallyScale( QString s_Value )
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

void SetXAxisOptionsFloatDialog::setManuallyPrecision( int i_Precision )
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

bool SetXAxisOptionsFloatDialog::DialogItemsNotEmpty()
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

void SetXAxisOptionsFloatDialog::enableOK()
{
    if ( this->GraphicMinimum_lineEdit->text().toDouble() >= this->GraphicMaximum_lineEdit->text().toDouble() )
        this->OK_pushButton->setEnabled( false );
    else
        this->OK_pushButton->setEnabled( true );
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetXAxisOptionsFloatDialog::paintEvent( QPaintEvent * /* event */ )
{
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    QPainter painter( this );

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

void SetXAxisOptionsFloatDialog::chosseReflineColor()
{
    setReflineColor( QColorDialog::getColor( this->ReflineColor(), this, tr( "Select color of reference line"), QColorDialog::DontUseNativeDialog ) );

    update();
}

