/* readData.cpp               */
/* 2009-12-01                 */
/* Dr. Rainer Sieger          */

#include <qmath.h>

#include "Application.h"

int MainWindow::readData( const QString &s_FilenameIn, const int i_Codec )
{
    int         stopProgress  = _NOERROR_;

    QStringList sl_Input;
    QStringList sl_Data;

// **********************************************************************************************

    gsl_DataDescription.clear();

    gv_Data.clear();
    gv_PS.clear();
    gv_PP.clear();

// **********************************************************************************************

    initProgress( 1, s_FilenameIn, tr( "Read data" ), 4 );

    if ( readFile( s_FilenameIn, sl_Input, i_Codec ) < 1 )
    {
        resetProgress( 1 );
        return( _NODATAFOUND_ );
    }

    stopProgress = incProgress( 1, 1 );

// **********************************************************************************************

    if ( sl_Input.at( 0 ).startsWith( "PanPlot data file" ) == true )
    {
        stopProgress = readDataFile( s_FilenameIn );
    }
    else
    {
        if ( stopProgress == _NOERROR_ )
            stopProgress = splitInput( sl_Input, gsl_DataDescription, sl_Data );

        stopProgress = incProgress( 1, 2 );

        if ( stopProgress == _NOERROR_ )
            stopProgress = buildDataVector( sl_Data, gv_Data, gv_PS, gv_PP );

        stopProgress = incProgress( 1, 3 );

        if ( stopProgress == _NOERROR_ )
            setRange( gv_Data, gv_PS );

        if ( stopProgress == _NOERROR_ )
            sortParameter( gv_PS, gv_PP);
    }

// **********************************************************************************************

    resetProgress( 1 );

    if ( stopProgress != _NOERROR_ )
        return( stopProgress );

    return( _NOERROR_ );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-01-13

int MainWindow::buildDataVector( const QStringList &sl_Data, QVector<DataItem> &v_Data, QVector<PlotSettings> &v_PS, QVector<int> &v_PP )
{
    int         i              = 0;
    int         j              = 0;

    int         NumOfColumns   = 0;
    int         NumOfLines     = 0;

// **********************************************************************************************

    if ( sl_Data.isEmpty() == true )
        return( _NODATAFOUND_ );

// **********************************************************************************************

    NumOfLines   = sl_Data.count();
    NumOfColumns = NumOfSections( sl_Data.at( 0 ) );

// **********************************************************************************************

    while ( i < NumOfColumns )
    {
        v_PS.append( PlotSettings( true, i, NumOfLines, sl_Data.at( 0 ) ) );
        v_PP.append( i );

        j = 0;
        while ( ++j < NumOfLines )
            v_Data.append( DataItem( i, j, sl_Data.at( j ).section( "\t", i, i ), v_PS.last().Type() ) );

        ++i;
    }

    return( _NOERROR_ );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2009-12-03

int MainWindow::setRange( const QVector<DataItem> &v_Data, QVector<PlotSettings> &v_PS )
{
    int j = 0;

// **********************************************************************************************

    while ( j < v_PS.count() )
    {
        int     i_qualityMin        =  999;
        int     i_qualityMax        = -999;

        int     i_statusMin         =  999;
        int     i_statusMax         = -999;

        int     s                   = v_PS.at( j ).StartPos();
        int     e                   = v_PS.at( j ).StartPos() + v_PS.at( j ).DataCount();

        double  d_Minimum           =  10E99;
        double  d_Maximum           = -10E99;

        int     i_nfrac             = 0;
        double  d_TickmarkSpacing   = 1.;
        double  d_graphMin          = 0.;
        double  d_graphMax          = 0.;

        QList<double> v_Stat;

        // **********************************************************************************************

        if ( v_PS.at( j ).Type() == isDOI )
        {
            for ( int i=s; i<e; i++ )
            {
                if ( ( v_Data.at( i ).Status() != _EMPTY_ ) && ( v_Data.at( i ).Value() != -999. ) )
                {
                    d_Minimum    = qMin( d_Minimum, v_Data.at( i ).Value() );
                    d_Maximum    = qMax( d_Maximum, v_Data.at( i ).Value() );
                    i_qualityMin = qMin( i_qualityMin, v_Data.at( i ).QualityFlag() );
                    i_qualityMax = qMax( i_qualityMax, v_Data.at( i ).QualityFlag() );
                }

                i_statusMin = qMin( i_statusMin, v_Data.at( i ).Status() );
                i_statusMax = qMax( i_statusMax, v_Data.at( i ).Status() );
            }
        }

        if ( ( v_PS.at( j ).Type() == isNumeric ) || ( v_PS.at( j ).Type() == isDateTime ) )
        {
            for ( int i=s; i<e; i++ )
            {
                if ( ( v_Data.at( i ).Status() != _EMPTY_ ) && ( v_Data.at( i ).QualityFlag() < _TEXT_ ) )
                {
                    d_Minimum    = qMin( d_Minimum, v_Data.at( i ).Value() );
                    d_Maximum    = qMax( d_Maximum, v_Data.at( i ).Value() );
                    i_qualityMin = qMin( i_qualityMin, v_Data.at( i ).QualityFlag() );
                    i_qualityMax = qMax( i_qualityMax, v_Data.at( i ).QualityFlag() );

                    v_Stat.append( v_Data.at( i ).Value() );
                }

                i_statusMin = qMin( i_statusMin, v_Data.at( i ).Status() );
                i_statusMax = qMax( i_statusMax, v_Data.at( i ).Status() );
            }
        }

        // **********************************************************************************************
        /* Types and quality flags for data items

            // Status
            const int EMPTY            = -1;

            // Quality flag and type
            const int GOOD             = 0;  // OK
            const int UNKNOWN          = 1;  // *
            const int NOTVALID         = 2;  // /
            const int INDDEF           = 3;  // #
            const int QUESTIONABLE     = 4;  // ?
            const int LESSTHAN         = 5;  // <
            const int GREATERTHAN      = 6;  // >
            const int MEAN             = 7;  // mean
            const int DATETIME         = 10;
            const int NUMERIC          = 20;
            const int STRING           = 40;
            const int DOI              = 80;
            const int URL              = 160;
        */

        if ( i_qualityMin > i_qualityMax )
        {
            v_PS[j].setType( isText );
        }
        else
        {
            if ( i_qualityMin >= _NUMERIC_ )
                v_PS[j].setType( isNumeric + isText );

            if ( i_qualityMin >= _TEXT_ )
                v_PS[j].setType( isText );

            if ( ( i_qualityMin == _DOI_ ) && ( d_Minimum >= 50000 ) ) // 50.000 is the first PANGAEA dataset ID
                v_PS[j].setType( isDOI );

            if ( ( i_qualityMin >= _NUMERIC_ ) && ( i_qualityMax < _TEXT_ ) )
                v_PS[j].setType( isNumeric );

            if ( ( i_qualityMin >= _DATETIME_ ) && ( i_qualityMax < _NUMERIC_ ) )
                v_PS[j].setType( isDateTime );

            if ( i_qualityMin != i_qualityMax )
                v_PS[j].setQuality( v_PS[j].Quality() + hasQualityFlags );
        }

        if ( ( i_statusMin == _EMPTY_ ) && ( i_statusMax != _EMPTY_ ) )
            v_PS[j].setQuality( v_PS[j].Quality() + hasEmptyEntries );

        // **********************************************************************************************

        if ( d_Minimum > d_Maximum )
        {
            d_Minimum = -1.;
            d_Maximum =  1.;
        }

        if ( d_Maximum == d_Minimum )
        {
            d_Minimum -= 1.;
            d_Maximum += 1.;
        }

        // **********************************************************************************************

        calcLooseLabel( d_Minimum, d_Maximum, i_nfrac, d_TickmarkSpacing, d_graphMin, d_graphMax );

        if ( ( v_PS.at( j ).Type() == isDateTime ) && ( ( d_Maximum - d_Minimum ) > 2 ) )
        {
            d_graphMin = floor( d_Minimum );
            d_graphMax = ceil( d_Maximum );

            gi_DateTimeFormat = _FORMATISODATE_;
        }

        v_PS[j].setYMinMax( d_Minimum, d_Maximum );

        v_PS[j].setYNiceLabel( i_nfrac, d_TickmarkSpacing, d_graphMin, d_graphMax );
        v_PS[j].setAutoYNiceLabel( i_nfrac, d_TickmarkSpacing, d_graphMin, d_graphMax );
        v_PS[j].setManualYNiceLabel( i_nfrac, d_TickmarkSpacing, d_graphMin, d_graphMax );

        v_PS[j].setXReflineOptions( false, 1, Qt::black, d_graphMin );
        v_PS[j].setYReflineOptions( false, 1, Qt::black, d_graphMin );

        // **********************************************************************************************

        calcStatistics( j, v_PS, v_Stat );

        ++j;
    }

    return( _NOERROR_ );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-01-20

void MainWindow::calcStatistics( const int j, QVector<PlotSettings> &v_PS, QList<double> &v_Stat )
{
    int     n       = v_Stat.count();

    double  d_Mean  = 0.;
    double  d_Sum   = 0.;
    double  d       = 0.;

// **********************************************************************************************

    if ( n < 1 )
    {
        v_PS[j].setMedian( -999. );
        v_PS[j].setMean( -999. );
        v_PS[j].setStandardDeviation( -999. );
        return;
    }

// **********************************************************************************************
// calculate mean and standard deviation

    for ( int i=0; i<n; i++ )
        d_Mean += v_Stat.at( i );

    if ( n != 0 )
    {
        d_Mean = d_Mean/(double) n;

        for ( int i=0; i<n; i++ )
        {
           d = d_Mean - v_Stat.at( i );
           d_Sum = d_Sum + d*d;
        }

        v_PS[j].setMean( d_Mean );
        v_PS[j].setStandardDeviation( qSqrt( d_Sum/(double) n ) );
    }

// **********************************************************************************************
// calculate median

    qSort( v_Stat.begin(), v_Stat.end() );

    int m = n/2;

    if ( n%2 == 1 ) // odd value
        v_PS[j].setMedian( v_Stat.at( m ) );
    else
        v_PS[j].setMedian( ( v_Stat.at( m-1 ) + v_Stat.at( m ) )/2. );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-01-03

int MainWindow::sortParameter( const QVector<PlotSettings> &v_PS, QVector<int> &v_PP )
{
    if ( v_PS.at( 0 ).Type() == isText )
    {
        int i          = 0;
        int i_validPos = -1;

        while( ++i < v_PS.count() )  // searching the first geocode
        {
            if ( v_PS.at( i ).isGeocode() == true )
            {
                i_validPos = i;
                break;
            }
        }

        if ( i_validPos < 0 )  // searching first numeric parameter if no geocode found
        {
            i = 0;

            while( ++i < v_PS.count() )
            {
                if ( v_PS.at( i ).Type() == isNumeric )
                {
                    i_validPos = i;
                    break;
                }
            }
        }

        if ( i_validPos > 0 )
        {
            v_PP.remove( i_validPos );
            v_PP.prepend( i_validPos );
        }
    }

    return( _NOERROR_ );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2009-12-03

int MainWindow::splitInput( QStringList &sl_Input, QStringList &sl_DataDescription, QStringList &sl_Data )
{
    int i               = 0;
    int i_NumOfLines    = sl_Input.count();

// **********************************************************************************************

    if ( ( sl_Input.filter( "/*" ).isEmpty() == false ) || ( sl_Input.filter( "//" ).isEmpty() == false ) )
    {
        while ( i < i_NumOfLines )
        {
            if ( sl_Input.at( i ).startsWith( "/*" ) == true )
            {
                while ( sl_Input.at( i ).startsWith( "*/" ) == false )
                    sl_DataDescription.append( sl_Input.at( i++ ) );

                sl_DataDescription.append( sl_Input.at( i++ ) );
            }

            while ( sl_Input.at( i ).startsWith( "//" ) == true )
                sl_DataDescription.append( sl_Input.at( i++ ) );

            sl_Data.append( sl_Input.at( i++ ) );
        }
    }
    else
    {
        sl_Data = sl_Input;
    }

    sl_Input.clear();

    return( _NOERROR_ );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::doReloadFile()
{
    doReadData( true );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::doReadData( bool b_reloadFile )
{
    int         err               = _NOERROR_;
    int         stopProgress      = 0;
    bool        b_pp2             = false;

// **********************************************************************************************
// Init

    initPointer();

    if ( b_reloadFile == false )
        gsl_FilenameList.clear();

// **********************************************************************************************

    setUpdatesEnabled( false );

    if ( existsFirstFile( gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList ) == true )
    {
        showPlotVAction->setEnabled( false );
        showPlotHAction->setEnabled( false );
        presetMenu->setEnabled( false );
        savePlotBMPAction->setEnabled( false );
        savePlotPDFAction->setEnabled( false );
        savePlotPNGAction->setEnabled( false );
        savePlotSVGAction->setEnabled( false );
        printPlotAction->setEnabled( true );
        showDatasetDescriptionAction->setEnabled( false );
        printDatasetDescriptionAction->setEnabled( false );
        saveDatasetDescriptionTextAction->setEnabled( false );
        saveDatasetDescriptionPDFAction->setEnabled( false );
        showParameterStatisticAction->setEnabled( false );
        printParameterStatisticAction->setEnabled( false );
        saveParameterStatisticTextAction->setEnabled( false );
        saveParameterStatisticPDFAction->setEnabled( false );
        setGraphicOptionsDialogAction->setEnabled( false );
        setTickOptionsDialogAction->setEnabled( false );
        setGlobalParameterOptionsDialogAction->setEnabled( false );
        selectParametersDialogAction->setEnabled( false );

        if ( gsl_FilenameList.count() > 0 )
        {
            QFileInfo fi( gsl_FilenameList.at( 0 ) );

            if ( fi.suffix().toLower() == "pp2" )
            {
                b_pp2 = true;

                err = readDataFile( gsl_FilenameList.at( 0 ) );
            }

            if ( ( fi.suffix().toLower() == "txt" ) || ( fi.suffix().toLower() == "csv" ) || ( fi.suffix().toLower() == "tab" ) || ( fi.suffix().toLower() == "dat" ) || ( fi.suffix().toLower() == "tsv" ) )
            {
                b_pp2 = false;

                err = readData( gsl_FilenameList.at( 0 ), gi_Codec );
            }
        }
    }
    else
    {
        err = _CHOOSEABORTED_;
    }

// **********************************************************************************************

    endTool( err, stopProgress, gi_ActionNumber, gs_FilenameFormat, gi_Extension, gsl_FilenameList, tr( "Done" ), tr( "Read data was canceled" ), false, false );

// **********************************************************************************************

    if ( err != _CHOOSEABORTED_ )
    {
        if ( b_pp2 == true )
            setUpdateGlobalParameterOptions( false );
        else
            setUpdateGlobalParameterOptions( true );

        if ( gsl_DataDescription.count() > 0 )
        {
            showDatasetDescriptionAction->setEnabled( true );
            printDatasetDescriptionAction->setEnabled( true );
            saveDatasetDescriptionTextAction->setEnabled( true );
            saveDatasetDescriptionPDFAction->setEnabled( true );
        }

        if ( ( gv_Data.count() > 0 ) && ( gv_PS.count() > 0 ) )
        {
            for ( int i=0; i < _MAX_NUM_OF_PARAMETERS_ ; i++ )
                setParameterOptionsDialogAction[i]->setVisible( false );

            saveAction->setEnabled( true );
            saveAsAction->setEnabled( true );
            showParameterStatisticAction->setEnabled( true );
            printParameterStatisticAction->setEnabled( true );
            saveParameterStatisticTextAction->setEnabled( true );
            saveParameterStatisticPDFAction->setEnabled( true );

            if ( b_pp2 == false )
            {
                for ( int i=0; i<gv_PS.count(); i++ )
                {
                    gv_PS[i].setMarkerOptions( gb_drawMarkers, gi_MarkerSize, gc_MarkerColor );
                    gv_PS[i].setLineOptions( gb_drawLines, gi_LineWidth, gc_LineColor );
                    gv_PS[i].setColorizedOptions( gb_drawColorized, gi_ColorizedPattern, gc_ColorizedGreaterRefColor, gc_ColorizedLessRefColor );
                    gv_PS[i].setDataTextOptions( gb_drawDataText, gf_DataTextFont, gc_DataTextColor );
                    gv_PS[i].setDiagramBackgroundOptions( gb_drawDiagramBackground, gc_DiagramBackgroundColor );
                    gv_PS[i].setUseManualScaleSettings( true );
                }

                gb_manuallyXScale = true;

                if ( b_reloadFile == false )
                    doSetPresetOptionsDialog();
            }
        }
    }
    else
    {
        setUpdateGlobalParameterOptions( false );
    }

    setUpdatesEnabled( true );

    switch ( gi_PlotOrientation)
    {
    case _SHOWDATADESCRIPTIONTABLE_:
        doShowDatasetDescription();
        break;

    case _SHOWPARAMETERTABLE_:
        doShowParameterStatistic();
        break;

    case _SHOWPLOTH_:
    case _SHOWPLOTV_:
        doShowPlot();
        break;

    default:
        doShowPlot();
        break;
    }

// **********************************************************************************************

    onError( err );
}
