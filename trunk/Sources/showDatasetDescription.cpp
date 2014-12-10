/* showDatasetDescription.cpp */
/* 2009-12-07                 */
/* Dr. Rainer Sieger          */

#include <QPrinter>
#include <QPrintDialog>

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2009-12-04

void MainWindow::showDatasetDescription( const QStringList &sl_DataDescription )
{
    int n              = 1;
    int k              = 0;
    int i_TextWidth    = 0;
    int i_TextHeight   = 0;

    int i_firstColumnWidth  = 150;
    int i_secondColumnWidth = 850;

    int i_RowHeight         = 0;

// **********************************************************************************************

    setMainWindowWidget( _SHOWDATADESCRIPTIONTABLE_ );

    DataDescriptionTable->setColumnCount( 2 );
    DataDescriptionTable->setRowCount( sl_DataDescription.count() );

    DataDescriptionTable->setSortingEnabled( false );
    DataDescriptionTable->setWordWrap( true );
    DataDescriptionTable->setCornerButtonEnabled( false );
    DataDescriptionTable->verticalHeader()->hide();
    DataDescriptionTable->horizontalHeader()->hide();

    i_secondColumnWidth = DataDescriptionTable->window()->width() - i_firstColumnWidth;

    DataDescriptionTable->setColumnWidth( 0, i_firstColumnWidth );
    DataDescriptionTable->setColumnWidth( 1, i_secondColumnWidth );

    QFontMetrics FontMetrics( font() );

    i_TextHeight = FontMetrics.boundingRect( "gG" ).height();

    for( int i=0; i<sl_DataDescription.count(); i++ )
    {
        if ( ( sl_DataDescription.at( i ).startsWith( "/*" ) == false ) && ( sl_DataDescription.at( i ).startsWith( "*/" ) == false ) && ( sl_DataDescription.at( i ).startsWith( "//" ) == false ) )
        {
            QTableWidgetItem *Item = new QTableWidgetItem( sl_DataDescription.at( i ).section( "\t", 0, 0 ) );
            DataDescriptionTable->setItem( k, 0, Item );
            DataDescriptionTable->item( k, 0 )->setTextAlignment( Qt::AlignTop );

            QTableWidgetItem *Content = new QTableWidgetItem( sl_DataDescription.at( i ).section( "\t", 1, 1 ) );
            DataDescriptionTable->setItem( k, 1, Content );

            i_TextWidth = FontMetrics.boundingRect( DataDescriptionTable->item( k, 1 )->text() ).width();

            n = 0;
            while ( n*i_secondColumnWidth < i_TextWidth+10 )
                ++n;

            i_RowHeight = n * ( i_TextHeight + 5 );
            DataDescriptionTable->setRowHeight( k, i_RowHeight );

            k++;
        }
    }

    DataDescriptionTable->setRowCount( k-1 );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2009-12-07

void MainWindow::doShowDatasetDescription()
{
    if ( gsl_DataDescription.count() > 0 )
        showDatasetDescription( gsl_DataDescription );

    setStatusBar( tr( "Ready" ), 2 );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-03-07

void MainWindow::doPrintDatasetDescription()
{
    if ( gsl_DataDescription.count() > 0 )
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
            textDocu.setHtml( createDataDescriptionOutputText( fi.fileName(), gsl_DataDescription ) );
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

void MainWindow::doSaveDatasetDescriptionText()
{
    if ( gsl_DataDescription.count() > 0 )
        saveDatasetDescription( gsl_FilenameList.at( 0 ), gsl_DataDescription, _FORMATTEXT_ );

    setStatusBar( tr( "Done" ), 2 );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-03-07

void MainWindow::doSaveDatasetDescriptionPDF()
{
    if ( gsl_DataDescription.count() > 0 )
        saveDatasetDescription( gsl_FilenameList.at( 0 ), gsl_DataDescription, _FORMATPDF_ );

    setStatusBar( tr( "Done" ), 2 );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-03-07

void MainWindow::saveDatasetDescription( const QString &s_FilenameIn, const QStringList &sl_DataDescription, const int i_Format )
{
    QPrinter        printer;
    QTextDocument   textDocu;
    QFont           textFont        = QFont( gf_HeaderTextFont.family(), 10, 0, false );

    QFileInfo fi( s_FilenameIn );

    QString         s_FilenameDescr = fi.absolutePath() + "/" + fi.baseName() + "_data_descr.";
    QString         s_FileDescr     = "";

// **********************************************************************************************

    switch ( i_Format )
    {
    case _FORMATPDF_:
        s_FilenameDescr.append( "pdf" );
        s_FileDescr = tr( "Portable document format (*.pdf)" );
        break;
    default:
        s_FilenameDescr.append( "txt" );
        s_FileDescr = tr( "Text (*.txt)" );
        break;
    }

    #if defined(Q_OS_LINUX)
        s_FilenameDescr = QFileDialog::getSaveFileName(this, tr( "Save data description to file" ), s_FilenameDescr, s_FileDescr, 0, QFileDialog::DontUseNativeDialog );
    #endif

    #if defined(Q_OS_WIN)
        s_FilenameDescr = QFileDialog::getSaveFileName(this, tr( "Save data description to file" ), s_FilenameDescr, s_FileDescr, 0, QFileDialog::DontUseNativeDialog );
    #endif

    #if defined(Q_OS_MAC)
        s_FilenameDescr = QFileDialog::getSaveFileName(this, tr( "Save data description to file" ), s_FilenameDescr, s_FileDescr, 0, QFileDialog::DontUseNativeDialog );
    #endif

    switch ( i_Format )
    {
    case _FORMATPDF_:
        printer.setOrientation( QPrinter::Landscape );
        printer.setOutputFileName( s_FilenameDescr );

        textDocu.setHtml( createDataDescriptionOutputText( fi.fileName(), sl_DataDescription ) );
        textDocu.setDefaultFont( textFont );
        textDocu.print( &printer );
        break;

    default:
        QFile fout( s_FilenameDescr );

        if ( fout.open( QIODevice::WriteOnly | QIODevice::Text ) == true )
        {
            QTextStream tout( &fout );

            tout << "Data description of:\t" << fi.fileName() << endl;

            for ( int i=1; i<sl_DataDescription.count()-1; i++ )
                tout << sl_DataDescription.at( i ) << endl;

            fout.close();
        }
        break;
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-03-06

QString MainWindow::createDataDescriptionOutputText( const QString &s_FilenameIn, const QStringList &sl_DataDescription )
{
    QString         s_Text          = "";

    s_Text = "<table>";

    s_Text.append( "<tr><td>Data description of:</td><td>" + s_FilenameIn + "</td></tr>" );

    for ( int i=1; i<sl_DataDescription.count()-1; i++ )
        s_Text.append( "<tr><td>" + sl_DataDescription.at( i ).section( "\t", 0, 0 ) + "</td><td>" + sl_DataDescription.at( i ).section( "\t", 1, 1 ) + "</td></tr>" );

    s_Text.append( "</table>" );

    return( s_Text );
}
