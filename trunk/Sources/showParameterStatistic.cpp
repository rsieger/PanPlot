/* showParameterStatistic.cpp */
/* 2009-12-07                 */
/* Dr. Rainer Sieger          */

#include <QPrinter>
#include <QPrintDialog>

#include "Application.h"

const bool b_showGraphicMinMax = false;

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2009-12-04

void MainWindow::showParameterStatistic( const QVector<PlotSettings> &v_PS )
{
    setMainWindowWidget( _SHOWPARAMETERTABLE_ );

    if ( b_showGraphicMinMax == true )
        ParameterTable->setColumnCount( 10 );
    else
        ParameterTable->setColumnCount( 7 );

    ParameterTable->setRowCount( v_PS.count() + 1 );
    ParameterTable->setSortingEnabled( false );
    ParameterTable->setWordWrap( false );
    ParameterTable->setCornerButtonEnabled( false );
    ParameterTable->verticalHeader()->hide();
    ParameterTable->horizontalHeader()->hide();

    QTableWidgetItem *ParameterNameHeader = new QTableWidgetItem( tr( "Parameter name" ) );
    ParameterNameHeader->setBackground( QBrush( Qt::lightGray ) );
    ParameterTable->setItem( 0, 0, ParameterNameHeader );

    QTableWidgetItem *DataMinimumHeader = new QTableWidgetItem( tr( "Minimum" ) );
    DataMinimumHeader->setBackground( QBrush( Qt::lightGray ) );
    ParameterTable->setItem( 0, 1, DataMinimumHeader );

    QTableWidgetItem *DataMaximumHeader = new QTableWidgetItem( tr( "Maximum" ) );
    DataMaximumHeader->setBackground( QBrush( Qt::lightGray ) );
    ParameterTable->setItem( 0, 2, DataMaximumHeader );

    QTableWidgetItem *DataMedianHeader = new QTableWidgetItem( tr( "Median" ) );
    DataMedianHeader->setBackground( QBrush( Qt::lightGray ) );
    ParameterTable->setItem( 0, 3, DataMedianHeader );

    QTableWidgetItem *DataMeanHeader = new QTableWidgetItem( tr( "Mean" ) );
    DataMeanHeader->setBackground( QBrush( Qt::lightGray ) );
    ParameterTable->setItem( 0, 4, DataMeanHeader );

    QTableWidgetItem *DataStdDevHeader = new QTableWidgetItem( tr( "Std dev" ) );
    DataStdDevHeader->setBackground( QBrush( Qt::lightGray ) );
    ParameterTable->setItem( 0, 5, DataStdDevHeader );

    QTableWidgetItem *DataTypeHeader = new QTableWidgetItem( tr( "Type" ) );
    DataTypeHeader->setBackground( QBrush( Qt::lightGray ) );
    ParameterTable->setItem( 0, 6, DataTypeHeader );

    QTableWidgetItem *GraphMinimumHeader = new QTableWidgetItem( tr( "Minimum, graph" ) );
    GraphMinimumHeader->setBackground( QBrush( Qt::lightGray ) );
    ParameterTable->setItem( 0, 7, GraphMinimumHeader );

    QTableWidgetItem *GraphMaximumHeader = new QTableWidgetItem( tr( "Maximum, graph" ) );
    GraphMaximumHeader->setBackground( QBrush( Qt::lightGray ) );
    ParameterTable->setItem( 0, 8, GraphMaximumHeader );

    QTableWidgetItem *TickMarkSpacingHeader = new QTableWidgetItem( tr( "Tick mark spacing" ) );
    TickMarkSpacingHeader->setBackground( QBrush( Qt::lightGray ) );
    ParameterTable->setItem( 0, 9, TickMarkSpacingHeader );

    ParameterTable->setColumnWidth( 0, 300 );
    ParameterTable->setColumnWidth( 1, 110 );
    ParameterTable->setColumnWidth( 2, 110 );
    ParameterTable->setRowHeight( 0, 20 );

    for( int i=0; i<v_PS.count(); i++ )
    {
        QTableWidgetItem *Parameter = new QTableWidgetItem( v_PS.at( i ).Parameter() );
        ParameterTable->setItem( i+1, 0, Parameter );

        if ( v_PS.at( i ).Type() == isDateTime )
        {
            QTableWidgetItem *Minimum = new QTableWidgetItem( QString( "%1" ).arg( QDate::fromJulianDay( (int) v_PS.at( i ).YMinimum() ).toString( Qt::ISODate ) ) );
            ParameterTable->setItem( i+1, 1, Minimum );

            QTableWidgetItem *Maximum = new QTableWidgetItem( QString( "%1" ).arg( QDate::fromJulianDay( (int) v_PS.at( i ).YMaximum() ).toString( Qt::ISODate ) ) );
            ParameterTable->setItem( i+1, 2, Maximum );

            QTableWidgetItem *Type = new QTableWidgetItem( "Date/Time" );
            ParameterTable->setItem( i+1, 6, Type );
        }
        else
        {
            if ( v_PS.at( i ).Type() != isText )
            {
                if ( v_PS.at( i ).YMinimum() < 10E99 )
                {
                    QTableWidgetItem *Minimum = new QTableWidgetItem( QString( "%1" ).arg( v_PS.at( i ).YMinimum() ) );
                    ParameterTable->setItem( i+1, 1, Minimum );
                }

                if ( v_PS.at( i ).YMaximum() > -10E99 )
                {
                    QTableWidgetItem *Maximum = new QTableWidgetItem( QString( "%1" ).arg( v_PS.at( i ).YMaximum() ) );
                    ParameterTable->setItem( i+1, 2, Maximum );
                }

                if ( v_PS.at( i ).isGeocode() == false )
                {
                    if ( v_PS.at( i ).Median() != -999. )
                    {
                        QTableWidgetItem *Median = new QTableWidgetItem( QString( "%1" ).arg( v_PS.at( i ).Median() ) );
                        ParameterTable->setItem( i+1, 3, Median );
                    }

                    if ( v_PS.at( i ).Mean() != -999. )
                    {
                        QTableWidgetItem *Mean = new QTableWidgetItem( QString( "%1" ).arg( v_PS.at( i ).Mean() ) );
                        ParameterTable->setItem( i+1, 4, Mean );
                    }

                    if ( v_PS.at( i ).StandardDeviation() != -999. )
                    {
                        QTableWidgetItem *StdDev = new QTableWidgetItem( QString( "%1" ).arg( v_PS.at( i ).StandardDeviation() ) );
                        ParameterTable->setItem( i+1, 5, StdDev );
                    }
                }
            }

            if ( v_PS.at( i ).Type() == isNumeric )
            {
                QTableWidgetItem *TypeNumeric = new QTableWidgetItem( "Numeric" );
                ParameterTable->setItem( i+1, 6, TypeNumeric );
            }

            if ( v_PS.at( i ).Type() == isText )
            {
                QTableWidgetItem *TypeText = new QTableWidgetItem( "Text" );
                ParameterTable->setItem( i+1, 6, TypeText );
            }

            if ( b_showGraphicMinMax == true )
            {
                QTableWidgetItem *GraphMinimum = new QTableWidgetItem( QString( "%1" ).arg( v_PS.at( i ).YGraphMin() ) );
                ParameterTable->setItem( i+1, 7, GraphMinimum );

                QTableWidgetItem *GraphMaximum = new QTableWidgetItem( QString( "%1" ).arg( v_PS.at( i ).YGraphMax() ) );
                ParameterTable->setItem( i+1, 8, GraphMaximum );

                QTableWidgetItem *TickMarkSpacing = new QTableWidgetItem( QString( "%1" ).arg( v_PS.at( i ).YTickmarkSpacing() ) );
                ParameterTable->setItem( i+1, 9, TickMarkSpacing );
            }
        }

        if ( v_PS.at( i ).isGeocode() == true )
            Parameter->setForeground( QBrush( Qt::red ) );

        ParameterTable->setRowHeight( i+1, 20 );
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2009-12-07

void MainWindow::doShowParameterStatistic()
{
    if ( gv_PS.count() > 0 )
        showParameterStatistic( gv_PS );

    setStatusBar( tr( "Ready" ), 2 );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-03-07

void MainWindow::doPrintParameterStatistic()
{
    if ( gv_PS.count() > 0 )
    {
        QTextDocument   textDocu;

        QPrinter        printer;
        QPrintDialog    printDialog( &printer, this );

        printer.setOrientation( QPrinter::Landscape );

        if ( printDialog.exec() == QDialog::Accepted )
        {
            QFileInfo   fi( gsl_FilenameList.at( 0 ) );
            QFont       textFont = QFont( gf_HeaderTextFont.family(), 10, 0, false );

            printer.setOutputFileName( tr( "" ) );
            textDocu.setHtml( createParameterStatisticOutputText( fi.fileName(), gv_PS ) );
            textDocu.setDefaultFont( textFont );
            textDocu.print( &printer );
        }

        update();
    }

    setStatusBar( tr( "Done" ), 2 );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-03-07

void MainWindow::doSaveParameterStatisticText()
{
    if ( gv_PS.count() > 0 )
        saveParameterStatistic( gsl_FilenameList.at( 0 ), gv_PS, _FORMATTEXT_ );

    setStatusBar( tr( "Done" ), 2 );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-03-07

void MainWindow::doSaveParameterStatisticPDF()
{
    if ( gv_PS.count() > 0 )
        saveParameterStatistic( gsl_FilenameList.at( 0 ), gv_PS, _FORMATPDF_ );

    setStatusBar( tr( "Done" ), 2 );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-03-07

void MainWindow::saveParameterStatistic( const QString &s_FilenameIn, const QVector<PlotSettings> &v_PS, const int i_Format )
{
    QPrinter        printer;
    QTextDocument   textDocu;
    QFont           textFont            = QFont( gf_HeaderTextFont.family(), 10, 0, false );

    QFileInfo fi( s_FilenameIn );

    QString         s_FilenameParamStat = fi.absolutePath() + "/" + fi.baseName() + "_param_stat.";
    QString         s_FileDescr         = "";

// **********************************************************************************************

    switch ( i_Format )
    {
    case _FORMATPDF_:
        s_FilenameParamStat.append( "pdf" );
        s_FileDescr = tr( "Portable document format (*.pdf)" );
        break;
    default:
        s_FilenameParamStat.append( "txt" );
        s_FileDescr = tr( "Text (*.txt)" );
        break;
    }

    #if defined(Q_OS_LINUX)
        s_FilenameParamStat = QFileDialog::getSaveFileName(this, tr( "Save parameter statistic to file" ), s_FilenameParamStat, s_FileDescr, 0, QFileDialog::DontUseNativeDialog );
    #endif

    #if defined(Q_OS_WIN)
        s_FilenameParamStat = QFileDialog::getSaveFileName(this, tr( "Save parameter statistic to file" ), s_FilenameParamStat, s_FileDescr, 0, QFileDialog::DontUseNativeDialog );
    #endif

    #if defined(Q_OS_MAC)
        s_FilenameParamStat = QFileDialog::getSaveFileName(this, tr( "Save parameter statistic to file" ), s_FilenameParamStat, s_FileDescr, 0, QFileDialog::DontUseNativeDialog );
    #endif

    switch ( i_Format )
    {
    case _FORMATPDF_:
        printer.setOrientation( QPrinter::Landscape );
        printer.setOutputFileName( s_FilenameParamStat );

        textDocu.setHtml( createParameterStatisticOutputText( fi.fileName(), v_PS ) );
        textDocu.setDefaultFont( textFont );
        textDocu.print( &printer );
        break;

    default:
        QFile fout( s_FilenameParamStat );

        if ( fout.open( QIODevice::WriteOnly | QIODevice::Text ) == true )
        {
            QTextStream tout( &fout );

            tout << "Parameter settings of:\t" << fi.fileName() << endl << endl;

            tout << "Parameter name" << "\t" << "Minimum" << "\t" << "Maximum" << "\t" << "Median" << "\t" << "Mean" << "\t" << "Std dev" << "\t" << "Type" << endl;

            for ( int i=0; i<v_PS.count(); i++ )
            {
                tout << v_PS.at( i ).Parameter() << "\t";

                if ( v_PS.at( i ).Type() == isDateTime )
                {
                    tout << QString( "%1" ).arg( QDate::fromJulianDay( (int) v_PS.at( i ).YMinimum() ).toString( Qt::ISODate ) ) << "\t";
                    tout << QString( "%1" ).arg( QDate::fromJulianDay( (int) v_PS.at( i ).YMaximum() ).toString( Qt::ISODate ) ) << "\t";
                    tout << "\t" << "\t" << "\t";
                    tout << "Date/Time" << endl;
                }
                else
                {
                    if ( v_PS.at( i ).Type() != isText )
                    {
                        if ( v_PS.at( i ).YMinimum() < 10E99 )
                            tout << QString( "%1" ).arg( v_PS.at( i ).YMinimum() ) << "\t";
                        else
                            tout << "\t";

                        if ( v_PS.at( i ).YMaximum() > -10E99 )
                            tout << QString( "%1" ).arg( v_PS.at( i ).YMaximum() ) << "\t";
                        else
                            tout << "\t";

                        if ( v_PS.at( i ).isGeocode() == false )
                        {
                            if ( v_PS.at( i ).Median() != -999. )
                                tout  << QString( "%1" ).arg( v_PS.at( i ).Median() ) << "\t";
                            else
                                tout << "\t";

                            if ( v_PS.at( i ).Mean() != -999. )
                                tout  << QString( "%1" ).arg( v_PS.at( i ).Mean() ) << "\t";
                            else
                                tout << "\t";

                            if ( v_PS.at( i ).StandardDeviation() != -999. )
                                tout << QString( "%1" ).arg( v_PS.at( i ).StandardDeviation() ) << "\t";
                            else
                                tout << "\t";
                        }
                    }

                    if ( v_PS.at( i ).Type() == isNumeric )
                        tout << "Numeric";

                    if ( v_PS.at( i ).Type() == isText )
                        tout << "\t" << "\t" << "\t" << "\t" << "\t" << "Text";

                    tout << endl;
                }
            }

            fout.close();
        }
        break;
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-03-06

QString MainWindow::createParameterStatisticOutputText( const QString &s_FilenameIn, const QVector<PlotSettings> &v_PS )
{
    QString         s_Text          = "";

    s_Text.append( "<p>Parameter settings of: " + s_FilenameIn + "</p><p></p>" );

    s_Text.append( "<table border=\"1\" cellpadding=\"5\">" );

    s_Text.append( "<tr><td>Parameter name</td><td>Minimum</td><td>Maximum</td><td>Median</td><td>Mean</td><td>Std dev</td><td>Type</td></tr>" );

    for ( int i=0; i<v_PS.count(); i++ )
    {
        s_Text.append( "<tr><td>" + v_PS.at( i ).Parameter() + "</td>" );

        if ( v_PS.at( i ).Type() == isDateTime )
        {
            s_Text.append( QString( "<td>%1</td>" ).arg( QDate::fromJulianDay( (int) v_PS.at( i ).YMinimum() ).toString( Qt::ISODate ) ) );
            s_Text.append( QString( "<td>%1</td>" ).arg( QDate::fromJulianDay( (int) v_PS.at( i ).YMaximum() ).toString( Qt::ISODate ) ) );
            s_Text.append( "<td></td>" );
            s_Text.append( "<td></td>" );
            s_Text.append( "<td></td>" );
            s_Text.append( "<td>Date/Time</td></tr>" );
        }
        else
        {
            if ( v_PS.at( i ).Type() != isText )
            {
                if ( v_PS.at( i ).YMinimum() < 10E99 )
                    s_Text.append( QString( "<td>%1</td>" ).arg( v_PS.at( i ).YMinimum() ) );
                else
                    s_Text.append( "<td></td>" );

                if ( v_PS.at( i ).YMaximum() > -10E99 )
                    s_Text.append( QString( "<td>%1</td>" ).arg( v_PS.at( i ).YMaximum() ) );
                else
                    s_Text.append( "<td></td>" );

                if ( v_PS.at( i ).isGeocode() == false )
                {
                    if ( v_PS.at( i ).Median() != -999. )
                        s_Text.append( QString( "<td>%1</td>" ).arg( v_PS.at( i ).Median() ) );
                    else
                        s_Text.append( "<td></td>" );

                    if ( v_PS.at( i ).Mean() != -999. )
                        s_Text.append( QString( "<td>%1</td>" ).arg( v_PS.at( i ).Mean() ) );
                    else
                        s_Text.append( "<td></td>" );

                    if ( v_PS.at( i ).StandardDeviation() != -999. )
                        s_Text.append( QString( "<td>%1</td>" ).arg( v_PS.at( i ).StandardDeviation() ) );
                    else
                        s_Text.append( "<td></td>" );
                }
                else
                {
                    s_Text.append( "<td></td>" );
                    s_Text.append( "<td></td>" );
                    s_Text.append( "<td></td>" );
                }
            }

            if ( v_PS.at( i ).Type() == isNumeric )
                s_Text.append( "<td>Numeric</td>" );

            if ( v_PS.at( i ).Type() == isText )
                s_Text.append( "<td></td><td></td><td></td><td></td><td></td><td>Text</td>" );

            s_Text.append( "</tr>" );
        }
    }

    s_Text.append( "</table>" );

    return( s_Text );
}
