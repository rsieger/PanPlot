// ***********************************************************************************************
// *                                                                                             *
// * SetXAxisOptionsDateTimeDialog.cpp - X axis options dialog, date/time                        *
// *                                                                                             *
// * Dr. Rainer Sieger - 2012-06-08                                                              *
// *                                                                                             *
// ***********************************************************************************************

#include <QtGui>

#include "Application.h"
#include "SetXAxisOptionsDateTimeDialog.h"

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void MainWindow::doSetXAxisOptionsDateTimeDialog()
{
    int XAxisParameterID = gv_PP.at( 0 );

    saveGraphicOptions();
    saveParameterOptions();

    this->setUpdatesEnabled( false );

    SetXAxisOptionsDateTimeDialog dialog( this );

// ***********************************************************************************************************************

    dialog.setAutoNiceLabel( gv_PS.at( XAxisParameterID ).AutoYTickmarkSpacing(), gv_PS.at( XAxisParameterID ).AutoYGraphMin(),
                             gv_PS.at( XAxisParameterID ).AutoYGraphMax() );

    dialog.setManualNiceLabel( gv_PS.at( XAxisParameterID ).ManualYTickmarkSpacing(), gv_PS.at( XAxisParameterID ).ManualYGraphMin(),
                               gv_PS.at( XAxisParameterID ).ManualYGraphMax() );

    if ( gb_manuallyXScale == false )
        dialog.setDialogItems( Qt::Unchecked );
    else
        dialog.useManualScaleSettings_checkBox->setChecked( gb_manuallyXScale );

    switch ( gi_DateTimeFormat )
    {
    case _FORMATYEAR_ :
        dialog.Year_radioButton->setChecked( true );
        break;

    case _FORMATYEARMONTH_ :
        dialog.YearMonth_radioButton->setChecked( true );
        break;

    case _FORMATISODATE_ :
        dialog.IsoDate_radioButton->setChecked( true );
        break;

    case _FORMATISODATETIMESECS_ :
        dialog.IsoDateTimeSecs_radioButton->setChecked( true );
        break;

    default:
        dialog.IsoDateTime_radioButton->setChecked( true );
        break;
    }

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

        if ( gb_manuallyXScale == true )
        {
            QDate d_min = QDate::fromString( dialog.GraphicMinimum_DateTimeEdit->text().left( 10 ), "yyyy-MM-dd" );
            QDate d_max = QDate::fromString( dialog.GraphicMaximum_DateTimeEdit->text().left( 10 ), "yyyy-MM-dd" );

            QTime t_min = QTime::fromString( dialog.GraphicMinimum_DateTimeEdit->text().right( 8 ), "hh:mm:ss" );
            QTime t_max = QTime::fromString( dialog.GraphicMaximum_DateTimeEdit->text().right( 8 ), "hh:mm:ss" );

            gv_PS[XAxisParameterID].setManualYNiceLabel( 0, dialog.TickmarkSpacing_lineEdit->text().toDouble(),
                                                         (double) d_min.toJulianDay() - (double) t_min.secsTo( QTime( 0, 0, 0 ) )/86400. + 0.00001,
                                                         (double) d_max.toJulianDay() - (double) t_max.secsTo( QTime( 0, 0, 0 ) )/86400. + 0.00001 );
        }

        if ( dialog.Year_radioButton->isChecked() )
            gi_DateTimeFormat = _FORMATYEAR_;
        if ( dialog.YearMonth_radioButton->isChecked() )
            gi_DateTimeFormat = _FORMATYEARMONTH_;
        if ( dialog.IsoDate_radioButton->isChecked() )
            gi_DateTimeFormat = _FORMATISODATE_;
        if ( dialog.IsoDateTime_radioButton->isChecked() )
            gi_DateTimeFormat = _FORMATISODATETIME_;
        if ( dialog.IsoDateTimeSecs_radioButton->isChecked() )
            gi_DateTimeFormat = _FORMATISODATETIMESECS_;

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

SetXAxisOptionsDateTimeDialog::SetXAxisOptionsDateTimeDialog( QWidget *parent ) : QDialog( parent )
{
    setupUi( this );

    connect(OK_pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel_pushButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(useManualScaleSettings_checkBox, SIGNAL(stateChanged(int)), this, SLOT(setDialogItems(int)));
}

// ****************************************************************************
// ****************************************************************************
// ****************************************************************************

void SetXAxisOptionsDateTimeDialog::setDialogItems( int state )
{
    if ( state == Qt::Checked )
    {
        QDate d_min = QDate::fromJulianDay( (qint64) this->ManualGraphMin() );
        QDate d_max = QDate::fromJulianDay( (qint64) this->ManualGraphMax() );

        QTime t_min = QTime( 0, 0, 0 ).addSecs( ( this->ManualGraphMin() - (qint64) this->ManualGraphMin() ) * 86400 );
        QTime t_max = QTime( 0, 0, 0 ).addSecs( ( this->ManualGraphMax() - (qint64) this->ManualGraphMax() ) * 86400 );

        this->GraphicMinimum_label->setEnabled( true );
        this->GraphicMaximum_label->setEnabled( true );
        this->TickmarkSpacing_label->setEnabled( true );

        this->GraphicMinimum_DateTimeEdit->setEnabled( true );
        this->GraphicMaximum_DateTimeEdit->setEnabled( true );
        this->TickmarkSpacing_lineEdit->setEnabled( true );

        this->GraphicMinimum_DateTimeEdit->setDisplayFormat( "yyyy-MM-dd hh:mm:ss" );
        this->GraphicMaximum_DateTimeEdit->setDisplayFormat( "yyyy-MM-dd hh:mm:ss" );

        this->GraphicMinimum_DateTimeEdit->setDate( d_min );
        this->GraphicMinimum_DateTimeEdit->setTime( t_min );
        this->GraphicMaximum_DateTimeEdit->setDate( d_max );
        this->GraphicMaximum_DateTimeEdit->setTime( t_max );

        this->TickmarkSpacing_lineEdit->setText( QString( "%1" ).arg( this->ManualTickmarkSpacing(), 0, 'f', 2 ) );
    }
    else
    {
        QDate d_min = QDate::fromJulianDay( (qint64) this->AutoGraphMin() );
        QDate d_max = QDate::fromJulianDay( (qint64) this->AutoGraphMax() );

        QTime t_min = QTime( 0, 0, 0 ).addSecs( ( this->AutoGraphMin() - (qint64) this->AutoGraphMin() ) * 86400 );
        QTime t_max = QTime( 0, 0, 0 ).addSecs( ( this->AutoGraphMax() - (qint64) this->AutoGraphMax() ) * 86400 );

        this->GraphicMinimum_label->setEnabled( false );
        this->GraphicMaximum_label->setEnabled( false );
        this->TickmarkSpacing_label->setEnabled( false );

        this->GraphicMinimum_DateTimeEdit->setEnabled( false );
        this->GraphicMaximum_DateTimeEdit->setEnabled( false );
        this->TickmarkSpacing_lineEdit->setEnabled( false );

        this->GraphicMinimum_DateTimeEdit->setDisplayFormat( "yyyy-MM-dd hh:mm:ss" );
        this->GraphicMaximum_DateTimeEdit->setDisplayFormat( "yyyy-MM-dd hh:mm:ss" );

        this->GraphicMinimum_DateTimeEdit->setDate( d_min );
        this->GraphicMinimum_DateTimeEdit->setTime( t_min );
        this->GraphicMaximum_DateTimeEdit->setDate( d_max );
        this->GraphicMaximum_DateTimeEdit->setTime( t_max );

        this->TickmarkSpacing_lineEdit->setText( QString( "%1" ).arg( this->AutoTickmarkSpacing(), 0, 'f', 2 ) );
    }
}
