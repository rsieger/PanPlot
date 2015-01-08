/* ApplicationTools.cpp       */
/* 2009-12-04                 */
/* Dr. Rainer Sieger          */

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2009-12-04

void MainWindow::setMainWindowWidget( const int i_widget, bool b_saveOptions )
{
    if ( b_saveOptions == true )
    {
        saveGraphicOptions( true );
        saveParameterOptions( true );

        initPointer();
    }

    switch ( i_widget )
    {
    case _SHOWLIST_:
        Model	 = new QStringListModel( this );
        ListView = new QListView;
        ListView->setModel( Model );
        ListView->setEditTriggers( QAbstractItemView::NoEditTriggers );
        setCentralWidget( ListView );
        break;

    case _SHOWDATADESCRIPTIONTABLE_:
        DataDescriptionTable = new QTableWidget( 0, 0, this );
        setCentralWidget( DataDescriptionTable );

        setGraphicOptionsDialogAction->setEnabled( false );
        setTickOptionsDialogAction->setEnabled( false );
        setGlobalParameterOptionsDialogAction->setEnabled( false );
        showDatasetDescriptionAction->setEnabled( false );
        selectParametersDialogAction->setEnabled( false );
        reloadFileAction->setEnabled( true );

        if ( ( gv_Data.count() > 0 ) && ( gv_PS.count() > 0 ) )
        {
            showParameterStatisticAction->setEnabled( true );
            printParameterStatisticAction->setEnabled( true );
            saveParameterStatisticTextAction->setEnabled( true );
            saveParameterStatisticPDFAction->setEnabled( true );
            showPlotVAction->setEnabled( true );
            showPlotHAction->setEnabled( true );
            presetMenu->setEnabled( true );
        }
        break;

    case _SHOWPARAMETERTABLE_:
        ParameterTable = new QTableWidget( 0, 0, this );
        setCentralWidget( ParameterTable );

        setGraphicOptionsDialogAction->setEnabled( false );
        setTickOptionsDialogAction->setEnabled( false );
        setGlobalParameterOptionsDialogAction->setEnabled( false );
        showParameterStatisticAction->setEnabled( false );
        selectParametersDialogAction->setEnabled( false );
        reloadFileAction->setEnabled( true );

        if ( gsl_DataDescription.count() > 0 )
        {
            showDatasetDescriptionAction->setEnabled( true );
            printDatasetDescriptionAction->setEnabled( true );
            saveDatasetDescriptionTextAction->setEnabled( true );
            saveDatasetDescriptionPDFAction->setEnabled( true );
        }

        if ( ( gv_Data.count() > 0 ) && ( gv_PS.count() > 0 ) )
        {
            showPlotVAction->setEnabled( true );
            showPlotHAction->setEnabled( true );
            presetMenu->setEnabled( true );
        }

        break;

    case _SHOWPLOTV_:
    case _SHOWPLOTH_:
        if ( gb_fixedDiagramSize == true )
        {
            scrollArea = new QScrollArea();
            renderArea = new RenderArea();
            scrollArea->setWidget( renderArea );
            scrollArea->setWidgetResizable( true );
            scrollArea->viewport()->setAutoFillBackground( true );
            setCentralWidget( scrollArea );
        }
        else
        {
            renderArea = new RenderArea();
            setCentralWidget( renderArea );
        }

        // **********************************************************************************************

        reloadFileAction->setEnabled( true );

        savePlotBMPAction->setEnabled( true );
        savePlotPDFAction->setEnabled( true );
        savePlotPNGAction->setEnabled( true );
        savePlotSVGAction->setEnabled( true );
        printPlotAction->setEnabled( true );

        setGraphicOptionsDialogAction->setEnabled( true );
        setTickOptionsDialogAction->setEnabled( true );
        setGlobalParameterOptionsDialogAction->setEnabled( true );
        selectParametersDialogAction->setEnabled( true );
        setXAxisOptionsDialogAction->setEnabled( true );

        setXAxisOptionsDialogAction->setText( gv_PS.at( gv_PP.at( 0 ) ).Parameter() );

        for ( int i=0; i < _MAX_NUM_OF_PARAMETERS_ ; i++ )
        {
            setParameterOptionsDialogAction[i]->setText( QString( "Parameter %1" ).arg( i+1 ) );
            setParameterOptionsDialogAction[i]->setVisible( false );
        }

        for ( int i=1; i<gv_PS.count(); i++ )
        {
            if ( gv_PP.at( i ) >= 0 )
            {
                setParameterOptionsDialogAction[i-1]->setText( gv_PS.at( gv_PP.at( i ) ).Parameter() );
                setParameterOptionsDialogAction[i-1]->setData( gv_PP.at( i ) );
                setParameterOptionsDialogAction[i-1]->setVisible( true );
            }
            else
            {
                setParameterOptionsDialogAction[i-1]->setVisible( false );
            }
        }

        switch ( gi_PlotOrientation )
        {
        case _SHOWPLOTV_:
            showPlotVAction->setEnabled( false );
            showPlotHAction->setEnabled( true );
            presetMenu->setEnabled( true );
            break;
        case _SHOWPLOTH_:
            showPlotVAction->setEnabled( true );
            showPlotHAction->setEnabled( false );
            presetMenu->setEnabled( true );
            break;
        default:
            showPlotVAction->setEnabled( true );
            showPlotHAction->setEnabled( true );
            presetMenu->setEnabled( true );
            break;
        }

        if ( gsl_DataDescription.count() > 0 )
        {
            showDatasetDescriptionAction->setEnabled( true );
            printDatasetDescriptionAction->setEnabled( true );
            saveDatasetDescriptionTextAction->setEnabled( true );
            saveDatasetDescriptionPDFAction->setEnabled( true );
        }

        if ( gv_PS.count() > 0 )
        {
            showParameterStatisticAction->setEnabled( true );
            printParameterStatisticAction->setEnabled( true );
            saveParameterStatisticTextAction->setEnabled( true );
            saveParameterStatisticPDFAction->setEnabled( true );
        }

        // **********************************************************************************************

        bool b_drawMajorXTickmarksLeftOutside     = setBool( gb_drawMajorXTicksLeft, gb_drawMajorXTicksOutside );
        bool b_drawMajorXTickmarksLeftInside      = setBool( gb_drawMajorXTicksLeft, gb_drawMajorXTicksInside );
        bool b_drawMajorXTickmarksRightOutside    = setBool( gb_drawMajorXTicksRight, gb_drawMajorXTicksOutside );
        bool b_drawMajorXTickmarksRightInside     = setBool( gb_drawMajorXTicksRight, gb_drawMajorXTicksInside );

        bool b_drawMinorXTickmarksLeftOutside     = setBool( gb_drawMinorXTicksLeft, gb_drawMinorXTicksOutside );
        bool b_drawMinorXTickmarksLeftInside      = setBool( gb_drawMinorXTicksLeft, gb_drawMinorXTicksInside );
        bool b_drawMinorXTickmarksRightOutside    = setBool( gb_drawMinorXTicksRight, gb_drawMinorXTicksOutside );
        bool b_drawMinorXTickmarksRightInside     = setBool( gb_drawMinorXTicksRight, gb_drawMinorXTicksInside );

        bool b_drawMajorYTickmarksTopOutside      = setBool( gb_drawMajorYTicksTop, gb_drawMajorYTicksOutside );
        bool b_drawMajorYTickmarksTopInside       = setBool( gb_drawMajorYTicksTop, gb_drawMajorYTicksInside );
        bool b_drawMajorYTickmarksBottomOutside   = setBool( gb_drawMajorYTicksBottom, gb_drawMajorYTicksOutside );
        bool b_drawMajorYTickmarksBottomInside    = setBool( gb_drawMajorYTicksBottom, gb_drawMajorYTicksInside );

        bool b_drawMinorYTickmarksTopOutside      = setBool( gb_drawMinorYTicksTop, gb_drawMinorYTicksOutside );
        bool b_drawMinorYTickmarksTopInside       = setBool( gb_drawMinorYTicksTop, gb_drawMinorYTicksInside );
        bool b_drawMinorYTickmarksBottomOutside   = setBool( gb_drawMinorYTicksBottom, gb_drawMinorYTicksOutside );
        bool b_drawMinorYTickmarksBottomInside    = setBool( gb_drawMinorYTicksBottom, gb_drawMinorYTicksInside );

        for ( int i=0; i<gv_PS.count(); i++ )
        {
            gv_PS[i].setXTicksOptions( gi_TickmarkLength, b_drawMajorXTickmarksLeftOutside, b_drawMajorXTickmarksLeftInside, b_drawMajorXTickmarksRightOutside, b_drawMajorXTickmarksRightInside, gb_drawMajorXTicklines, gb_drawXTickmarkLabels );
            gv_PS[i].setXMinorTicksOptions( gi_numMinorXTicks, b_drawMinorXTickmarksLeftOutside, b_drawMinorXTickmarksLeftInside, b_drawMinorXTickmarksRightOutside, b_drawMinorXTickmarksRightInside, gb_drawMinorXTicklines );
            gv_PS[i].setYTicksOptions( gi_TickmarkLength, b_drawMajorYTickmarksTopOutside, b_drawMajorYTickmarksTopInside, b_drawMajorYTickmarksBottomOutside, b_drawMajorYTickmarksBottomInside, gb_drawMajorYTicklines, gb_drawYTickmarkLabels );
            gv_PS[i].setYMinorTicksOptions( gi_numMinorYTicks, b_drawMinorYTickmarksTopOutside, b_drawMinorYTickmarksTopInside, b_drawMinorYTickmarksBottomOutside, b_drawMinorYTickmarksBottomInside, gb_drawMinorYTicklines );
        }

        // **********************************************************************************************

        int XAxisParameterID = gv_PP.at( 0 );

        for ( int i=0; i<gv_PS.count(); i++ )
        {
            gv_PS[i].setXMinMax( gv_PS.at( XAxisParameterID ).YMinimum(), gv_PS.at( XAxisParameterID ).YMaximum() );
            gv_PS[i].setYMinMax( gv_PS.at( i ).YMinimum(), gv_PS.at( i ).YMaximum() );

            if ( gb_manuallyXScale == false )
                gv_PS[i].setXNiceLabel( gv_PS.at( XAxisParameterID ).AutoYnFrac(), gv_PS.at( XAxisParameterID ).AutoYTickmarkSpacing(), gv_PS.at( XAxisParameterID ).AutoYGraphMin(), gv_PS.at( XAxisParameterID ).AutoYGraphMax() );
            else
                gv_PS[i].setXNiceLabel( gv_PS.at( XAxisParameterID ).ManualYnFrac(), gv_PS.at( XAxisParameterID ).ManualYTickmarkSpacing(), gv_PS.at( XAxisParameterID ).ManualYGraphMin(), gv_PS.at( XAxisParameterID ).ManualYGraphMax() );

            gv_PS[i].setXReflineOptions( gv_PS.at( XAxisParameterID ).drawXRefline(), gv_PS.at( XAxisParameterID ).XReflineWidth(), gv_PS.at( XAxisParameterID ).XReflineColor(), gv_PS.at( XAxisParameterID ).XRefline() );

            if ( gv_PS.at( i ).useManualScaleSettings() == false )
                gv_PS[i].setYNiceLabel( gv_PS.at( i ).AutoYnFrac(), gv_PS.at( i ).AutoYTickmarkSpacing(), gv_PS.at( i ).AutoYGraphMin(), gv_PS.at( i ).AutoYGraphMax() );
            else
                gv_PS[i].setYNiceLabel( gv_PS.at( i ).ManualYnFrac(), gv_PS.at( i ).ManualYTickmarkSpacing(), gv_PS.at( i ).ManualYGraphMin(), gv_PS.at( i ).ManualYGraphMax() );

            gv_PS[i].setYReflineOptions( gv_PS.at( i ).drawYRefline(), gv_PS.at( i ).YReflineWidth(), gv_PS.at( i ).YReflineColor(), gv_PS.at( i ).YRefline() );
        }

        // **********************************************************************************************

        if ( UpdateGlobalParameterOptions() == true )
        {
            setUpdateGlobalParameterOptions( false );

            for ( int i=0; i<gv_PS.count(); i++ )
            {
                gv_PS[i].setMarkerOptions( gb_drawMarkers, gi_MarkerSize, gc_MarkerColor );
                gv_PS[i].setLineOptions( gb_drawLines, gi_LineWidth, gc_LineColor );
                gv_PS[i].setColorizedOptions( gb_drawColorized, gi_ColorizedPattern, gc_ColorizedGreaterRefColor, gc_ColorizedLessRefColor );
                gv_PS[i].setDataTextOptions( gb_drawDataText, gf_DataTextFont, gc_DataTextColor );
                gv_PS[i].setDiagramBackgroundOptions( gb_drawDiagramBackground, gc_DiagramBackgroundColor );
                gv_PS[i].setYReverseGraphRange( gb_YReverseGraphRange );
            }
        }

        // **********************************************************************************************

        renderArea->setSavePlotFormat( gi_SavePlotFormat );
        renderArea->setFilenamePlot( gs_FilenamePlot );

        if ( gb_drawBackground == true )
            renderArea->setBackgroundBrush( QBrush( gc_BackgroundColor, Qt::SolidPattern ) );
        else
            renderArea->setBackgroundBrush( QBrush( QColor( Qt::white ), Qt::SolidPattern ) );

        if ( gv_Data.count() < 100000 )
            renderArea->setAntialiasing( gb_Antialiasing );
        else
            renderArea->setAntialiasing( false );

        renderArea->setPosDialog( posDialog );

        renderArea->setXReverseGraphRange( gb_XReverseGraphRange );

        renderArea->setDrawBackground( gb_drawBackground );
        renderArea->setBackgroundColor( gc_BackgroundColor );

        renderArea->setStatusBarHeight( statusBar()->height() );

        renderArea->setDiagramSize( gb_fixedDiagramSize, gi_diagramHeight, gi_diagramWidth, gi_diagramDistance );
        renderArea->setDiagramFrameWidth( gi_diagramFrameWidth );
        renderArea->setDiagramFrameColor( gc_DiagramFrameColor );

        renderArea->setHeaderTextColor( gc_HeaderTextColor );
        renderArea->setHeaderTextFont( gf_HeaderTextFont );

        renderArea->setMargin( gi_marginLeft, gi_marginRight, gi_marginTop, gi_marginBottom, gi_marginScale );

        renderArea->setParameterNameOrientation( gi_ParameterOrientation );
        renderArea->setPlotOrientation( gi_PlotOrientation );
        renderArea->setDateTimeFormat( gi_DateTimeFormat );
        renderArea->setTickWidth( gi_TickmarkWidth, gi_MinorTickmarkWidth, gi_TicklineWidth, gi_MinorTicklineWidth );
        renderArea->setTickColor( gc_TickmarkColor, gc_TicklineColor, gc_MinorTicklineColor );

        renderArea->setMinimumSizeHint( 450, 450 );

        renderArea->setMouseLeftButton( false );
        renderArea->setMouseRightButton( false );
        renderArea->setMouseMidButton( false );
        renderArea->setResizeState( false );

        renderArea->setData( gv_Data );
        renderArea->setPrameterSettings( gv_PS );
        renderArea->setParameterPosition( gv_PP );

        renderArea->resetCount();
        break;
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-01-10

void MainWindow::saveGraphicOptions( const bool b_updateGraphicOptions )
{
    if ( !renderArea )
        return;

    if ( b_updateGraphicOptions == true )
    {
        posDialog               = renderArea->posDialog();

        gs_FilenamePlot         = renderArea->FilenamePlot();

        gi_PlotOrientation      = renderArea->PlotOrientation();
        gi_SavePlotFormat       = renderArea->SavePlotFormat();

        gb_Antialiasing         = renderArea->Antialiasing();
        gb_XReverseGraphRange   = renderArea->XReverseGraphRange();
        gb_drawBackground       = renderArea->drawBackground();
        gb_fixedDiagramSize     = renderArea->fixedDiagramSize();

        gi_diagramHeight        = renderArea->DiagramHeight();
        gi_diagramWidth         = renderArea->DiagramWidth();
        gi_diagramDistance      = renderArea->DiagramDistance();
        gi_diagramFrameWidth    = renderArea->DiagramFrameWidth();

        gi_marginLeft           = renderArea->MarginLeft();
        gi_marginRight          = renderArea->MarginRight();
        gi_marginTop            = renderArea->MarginTop();
        gi_marginBottom         = renderArea->MarginBottom();
        gi_marginScale          = renderArea->MarginScale();

        gf_HeaderTextFont       = renderArea->HeaderTextFont();
        gc_HeaderTextColor      = renderArea->HeaderTextColor();
        gc_BackgroundColor      = renderArea->BackgroundColor();
        gc_DiagramFrameColor    = renderArea->DiagramFrameColor();
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-01-10

void MainWindow::saveParameterOptions( const bool b_updateGraphicOptions )
{
    if ( !renderArea )
        return;

    if ( b_updateGraphicOptions == true )
    {
        posDialog = renderArea->posDialog();

        gv_PS     = renderArea->ParameterSettings();
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2014-06-01

void MainWindow::savePlot( const int i_PlotFormat, const QString &s_FilenamePlot )
{
    renderArea->setSavePlotFormat( i_PlotFormat );
    renderArea->setFilenamePlot( s_FilenamePlot );

    saveGraphicOptions( true );
    saveParameterOptions( true );

    doShowPlot();

    wait( 100 );

    setUpdatesEnabled( false );
    if ( s_FilenamePlot.isEmpty() == false )
        QMessageBox::information( this, getApplicationName(),  QString ( tr( "Plot has been saved to:\n%1" ).arg( s_FilenamePlot ) ) );
    else
        QMessageBox::information( this, getApplicationName(),  QString ( tr( "Plot has been send to printer." ) ) );
    setUpdatesEnabled( true );

    gi_SavePlotFormat = _FORMATNULL_;
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2013-06-17

void MainWindow::doSavePlotBMP()
{
    QFileInfo fi( gsl_FilenameList.at( 0 ) );
    QString   s_FilenamePlot  = fi.absolutePath() + "/" + fi.baseName() + ".bmp";

// **********************************************************************************************

    setUpdatesEnabled( false );

    #if defined(Q_OS_LINUX)
        s_FilenamePlot = QFileDialog::getSaveFileName(this, tr( "Save plot to file" ), s_FilenamePlot, tr( "Windows Bitmap (*.bmp)" ), 0, QFileDialog::DontUseNativeDialog );
    #endif

    #if defined(Q_OS_WIN)
        s_FilenamePlot = QFileDialog::getSaveFileName(this, tr( "Save plot to file" ), s_FilenamePlot, tr( "Windows Bitmap (*.bmp)" ), 0, QFileDialog::DontUseNativeDialog );
    #endif

    #if defined(Q_OS_MAC)
        s_FilenamePlot = QFileDialog::getSaveFileName(this, tr( "Save plot to file" ), s_FilenamePlot, tr( "Windows Bitmap (*.bmp)" ), 0, QFileDialog::DontUseNativeDialog );
    #endif

    setUpdatesEnabled( true );

    if ( s_FilenamePlot.isEmpty() == false )
    {
        savePlot( _FORMATBMP_, s_FilenamePlot );
        doShowPlot();
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2013-06-17

void MainWindow::doSavePlotPNG()
{
    QFileInfo fi( gsl_FilenameList.at( 0 ) );
    QString   s_FilenamePlot  = fi.absolutePath() + "/" + fi.baseName() + ".png";

// **********************************************************************************************

    setUpdatesEnabled( false );

    #if defined(Q_OS_LINUX)
        s_FilenamePlot = QFileDialog::getSaveFileName(this, tr( "Save plot to file" ), s_FilenamePlot, tr( "Portable Network Graphic (*.png)" ), 0, QFileDialog::DontUseNativeDialog );
    #endif

    #if defined(Q_OS_WIN)
        s_FilenamePlot = QFileDialog::getSaveFileName(this, tr( "Save plot to file" ), s_FilenamePlot, tr( "Portable Network Graphic (*.png)" ), 0, QFileDialog::DontUseNativeDialog );
    #endif

    #if defined(Q_OS_MAC)
        s_FilenamePlot = QFileDialog::getSaveFileName(this, tr( "Save plot to file" ), s_FilenamePlot, tr( "Portable Network Graphic (*.png)" ), 0, QFileDialog::DontUseNativeDialog );
    #endif

    setUpdatesEnabled( true );

    if ( s_FilenamePlot.isEmpty() == false )
    {
        savePlot( _FORMATPNG_, s_FilenamePlot );
        doShowPlot();
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2013-06-17

void MainWindow::doSavePlotPDF()
{
    QFileInfo fi( gsl_FilenameList.at( 0 ) );
    QString   s_FilenamePlot  = fi.absolutePath() + "/" + fi.baseName() + ".pdf";

// **********************************************************************************************

    setUpdatesEnabled( false );

    #if defined(Q_OS_LINUX)
        s_FilenamePlot = QFileDialog::getSaveFileName(this, tr( "Save plot to file" ), s_FilenamePlot, tr( "Portable Document Format (*.pdf)" ), 0, QFileDialog::DontUseNativeDialog );
    #endif

    #if defined(Q_OS_WIN)
        s_FilenamePlot = QFileDialog::getSaveFileName(this, tr( "Save plot to file" ), s_FilenamePlot, tr( "Portable Document Format (*.pdf)" ), 0, QFileDialog::DontUseNativeDialog );
    #endif

    #if defined(Q_OS_MAC)
        s_FilenamePlot = QFileDialog::getSaveFileName(this, tr( "Save plot to file" ), s_FilenamePlot, tr( "Portable Document Format (*.pdf)" ), 0, QFileDialog::DontUseNativeDialog );
    #endif

    setUpdatesEnabled( true );

    if ( s_FilenamePlot.isEmpty() == false )
    {
        savePlot( _FORMATPDF_, s_FilenamePlot );
        doShowPlot();
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2013-06-17

void MainWindow::doSavePlotSVG()
{
    QFileInfo fi( gsl_FilenameList.at( 0 ) );
    QString   s_FilenamePlot  = fi.absolutePath() + "/" + fi.baseName() + ".svg";

// **********************************************************************************************

    setUpdatesEnabled( false );

    #if defined(Q_OS_LINUX)
        s_FilenamePlot = QFileDialog::getSaveFileName(this, tr( "Save plot to file" ), s_FilenamePlot, tr( "Scalable Vector Graphics (*.svg)" ), 0, QFileDialog::DontUseNativeDialog );
    #endif

    setUpdatesEnabled( false );

    #if defined(Q_OS_WIN)
        s_FilenamePlot = QFileDialog::getSaveFileName(this, tr( "Save plot to file" ), s_FilenamePlot, tr( "Scalable Vector Graphics (*.svg)" ), 0, QFileDialog::DontUseNativeDialog );
    #endif

    #if defined(Q_OS_MAC)
        s_FilenamePlot = QFileDialog::getSaveFileName(this, tr( "Save plot to file" ), s_FilenamePlot, tr( "Scalable Vector Graphics (*.svg)" ), 0, QFileDialog::DontUseNativeDialog );
    #endif

    setUpdatesEnabled( true );

    if ( s_FilenamePlot.isEmpty() == false )
    {
        savePlot( _FORMATSVG_, s_FilenamePlot );
        doShowPlot();
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2013-06-17

void MainWindow::doPrintPlot()
{
    savePlot( _FORMATPRINT_, "" );
    doShowPlot();
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-01-05

bool MainWindow::setBool( const bool b1, const bool b2, const bool b3 )
{
    if ( ( b1 == true ) && ( b2 == true ) && ( b3 == true ) )
        return( true );

    return( false );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-01-12

void MainWindow::initPointer()
{
    renderArea           = NULL;
    scrollArea           = NULL;
    ParameterTable       = NULL;
    DataDescriptionTable = NULL;
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-01-24

QColor MainWindow::setColor( const QString &s_Color )
{
    QColor Color;

    Color.setRed( s_Color.section( "-", 0, 0 ).toInt() );
    Color.setGreen( s_Color.section( "-", 1, 1 ).toInt() );
    Color.setBlue( s_Color.section( "-", 2, 2 ).toInt() );

    return( Color );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-01-24

QString MainWindow::ColorStr( const QColor &Color )
{
    return( QString( "%1-%2-%3" ).arg( Color.red() ).arg( Color.green() ).arg( Color.blue() ) );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-01-24

QFont MainWindow::setFont( const QString &s_Font )
{
    QFont Font;

    Font.setFamily( s_Font.section( ",", 0, 0 ) );
    Font.setPointSize( s_Font.section( ",", 1, 1 ).toInt() );
    Font.setWeight( s_Font.section( ",", 2, 2 ).toInt() );
    Font.setItalic( (bool) s_Font.section( ",", 3, 3 ).toInt() );
    Font.setStrikeOut( (bool) s_Font.section( ",", 4, 4 ).toInt() );
    Font.setUnderline( (bool) s_Font.section( ",", 5, 5 ).toInt() );

    return( Font );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-01-24

QString MainWindow::FontStr( const QFont &Font )
{
    return( QString( "%1, %2, %3, %4, %5, %6" ).arg( Font.family() ).arg( Font.pointSize() ).arg( Font.weight() ).arg( Font.italic() ).arg( Font.strikeOut() ).arg( Font.underline() ) );
}
