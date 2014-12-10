/* DataFile.cpp               */
/* 2011-01-21                 */
/* Dr. Rainer Sieger          */

#include "Application.h"

int MainWindow::writeDataFile( const QString &s_FilenameOut )
{
    if ( s_FilenameOut.isEmpty() == true )
        return( _CHOOSEABORTED_ );

    if ( ( gv_PP.count() < 1 ) || ( gv_Data.count() < 2 ) )
        return( _NOERROR_ );

    QFile fout( s_FilenameOut );

    if ( fout.open( QIODevice::WriteOnly ) == false )
        return( -10 );

// **********************************************************************************************

    saveGraphicOptions();
    saveParameterOptions();

    QByteArray ba( "PanPlot data file\n" );                                                                 // 0

    ba.append( QString( "Version:\t%1\n" ).arg( _DATAFORMATVERSION_ ) );                                    // 1
    ba.append( QString( "Created:\t%1\n" ).arg( QDateTime::currentDateTime().toString( Qt::ISODate ) ) );   // 2
    ba.append( QString( "Number of parameters:\t%1\n" ).arg( gv_PS.count() ) );                             // 3
    ba.append( QString( "Number of data items:\t%1\n" ).arg( gv_Data.count() ) );                           // 4

    ba.append( "[Data description]\n" );                                                                    // 5
    for ( int i=0; i<gsl_DataDescription.count(); i++ )
        ba.append( QString( "%1\n" ).arg( gsl_DataDescription.at( i ) ) );

    ba.append( "[Position and size of window]\n" );
    ba.append( QString( "%1\t%2\t%3\t%4\n" ).arg( x() ).arg( y() ).arg( height() ).arg( width() ) );

    ba.append( "[Plot positions]\n" );
    ba.append( "Diagram number:\tAbscissa" );
    for ( int i=1; i<gv_PP.count(); i++ )
        ba.append( QString( "\t%1" ).arg( i ) );
    ba.append( "\n" );

    ba.append( "Data column:" );
    for ( int i=0; i<gv_PP.count(); i++ )
    {
        if ( gv_PP.at( i ) > -1 )
            ba.append( QString( "\t%1" ).arg( gv_PP.at( i ) + 1 ) );
        else
            ba.append( "\tdisabled" );
    }
    ba.append( "\n" );

    ba.append( "[Global settings]\n" );
    ba.append( QString( "%1\t%2\t%3\t%4\t%5\t%6\t%7\n" ).arg( gi_Codec ).arg( gi_PlotOrientation ).arg( gi_ParameterOrientation ).arg( gb_XReverseGraphRange ).arg( gb_YReverseGraphRange ).arg( gb_Antialiasing ).arg( gb_drawBackground ) );    // 7
    ba.append( QString( "%1\t%2\t%3\t%4\t%5\n" ).arg( gi_marginLeft ).arg( gi_marginRight ).arg( gi_marginTop ).arg( gi_marginBottom ).arg( gi_marginScale ) );
    ba.append( QString( "%1\t%2\t%3\t%4\t%5\n" ).arg( gb_fixedDiagramSize ).arg( gi_diagramWidth ).arg( gi_diagramHeight ).arg( gi_diagramDistance ).arg( gi_diagramFrameWidth ) );
    ba.append( QString( "%1\t%2\t%3\t%4\n" ).arg( gb_manuallyXScale ).arg( gi_TickmarkLength ).arg( gi_numMinorXTicks ).arg( gi_numMinorYTicks ) );
    ba.append( QString( "%1\t%2\t%3\t%4\n" ).arg( gi_TickmarkWidth ).arg( gi_TicklineWidth ).arg( gi_MinorTickmarkWidth ).arg( gi_MinorTicklineWidth ) );
    ba.append( QString( "%1\t%2\t%3\t%4\t%5\n" ).arg( gb_drawMajorXTicklines ).arg( gb_drawMajorXTicksLeft ).arg( gb_drawMajorXTicksRight ).arg( gb_drawMajorXTicksInside ).arg( gb_drawMajorXTicksOutside ) );
    ba.append( QString( "%1\t%2\t%3\t%4\t%5\n" ).arg( gb_drawMajorYTicklines ).arg( gb_drawMajorYTicksTop ).arg( gb_drawMajorYTicksBottom ).arg( gb_drawMajorYTicksInside ).arg( gb_drawMajorYTicksOutside ) );
    ba.append( QString( "%1\t%2\t%3\t%4\t%5\n" ).arg( gb_drawMinorXTicklines ).arg( gb_drawMinorXTicksLeft ).arg( gb_drawMinorXTicksRight ).arg( gb_drawMinorXTicksInside ).arg( gb_drawMinorXTicksOutside ) );
    ba.append( QString( "%1\t%2\t%3\t%4\t%5\n" ).arg( gb_drawMinorYTicklines ).arg( gb_drawMinorYTicksTop ).arg( gb_drawMinorYTicksBottom ).arg( gb_drawMinorYTicksInside ).arg( gb_drawMinorYTicksOutside ) );
    ba.append( QString( "%1\t%2\t%3\t%4\t%5\n" ).arg( gb_drawMarkers ).arg( gb_drawLines ).arg( gb_drawColorized ).arg( gb_drawDataText ).arg( gb_drawDiagramBackground ) );
    ba.append( QString( "%1\t%2\t%3\t%4\n" ).arg( gi_MarkerSize ).arg( gi_LineWidth ).arg( gi_ColorizedPattern ).arg( gi_DateTimeFormat ) );
    ba.append( QString( "%1\t%2\t%3\t%4\t%5\t%6\n" ).arg( ColorStr( gc_MarkerColor ) ).arg( ColorStr( gc_LineColor ) ).arg( ColorStr( gc_ColorizedGreaterRefColor ) ).arg( ColorStr( gc_ColorizedLessRefColor ) ).arg( ColorStr( gc_DiagramBackgroundColor ) ).arg( ColorStr( gc_DataTextColor ) ) );
    ba.append( QString( "%1\t%2\t%3\t%4\t%5\t%6\n" ).arg( ColorStr( gc_DiagramFrameColor ) ).arg( ColorStr( gc_BackgroundColor ) ).arg( ColorStr( gc_HeaderTextColor ) ).arg( ColorStr( gc_TickmarkColor ) ).arg( ColorStr( gc_TicklineColor ) ).arg( ColorStr( gc_MinorTicklineColor ) ) );
    ba.append( QString( "%1\n" ).arg( FontStr( gf_DataTextFont ) ) );
    ba.append( QString( "%1\n" ).arg( FontStr( gf_HeaderTextFont ) ) );

    ba.append( "[Parameter settings]\n" );
    for ( int j=0; j<gv_PS.count(); j++ )
    {
        ba.append( QString( "%1\t" ).arg( j+1 ) );
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).ParameterName() ) );                                        // 1
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).ParameterUnit() ) );                                        // 2
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).Parameter() ) );                                            // 3

        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).StartPos() ) );                                             // 4
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).DataCount() ) );                                            // 5
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).Type() ) );                                                 // 6
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).Quality() ) );                                              // 7

        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).NumOfPointsNumeric() ) );                                   // 8
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).NumOfPointsDataText() ) );                                  // 9

        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).NumOfXMinorTicks() ) );                                     // 10
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).NumOfYMinorTicks() ) );                                     // 11

        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).drawDiagramBackground() ) );                                // 12
        ba.append( QString( "%1\t" ).arg( ColorStr( gv_PS.at( j ).DiagramBackgroundColor() ) ) );                   // 13

        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).drawMarker() ) );                                           // 14
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).MarkerSize() ) );                                           // 15
        ba.append( QString( "%1\t" ).arg( ColorStr( gv_PS.at( j ).MarkerColor() ) ) );                              // 16

        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).drawDataText() ) );                                         // 17
        ba.append( QString( "%1\t" ).arg( FontStr( gv_PS.at( j ).DataTextFont() ) ) );                              // 18
        ba.append( QString( "%1\t" ).arg( ColorStr( gv_PS.at( j ).DataTextColor() ) ) );                            // 19

        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).drawLine() ) );                                             // 20
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).LineWidth() ) );                                            // 21
        ba.append( QString( "%1\t" ).arg( ColorStr( gv_PS.at( j ).LineColor() ) ) );                                // 22

        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).drawColorized() ) );                                        // 23
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).Pattern() ) );                                              // 24
        ba.append( QString( "%1\t" ).arg( ColorStr( gv_PS.at( j ).ColorizedGreaterRefColor() ) ) );                 // 25
        ba.append( QString( "%1\t" ).arg( ColorStr( gv_PS.at( j ).ColorizedLessRefColor() ) ) );                    // 26

        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).YReverseGraphRange() ) );                                   // 27

        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).drawXRefline() ) );                                         // 28
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).XReflineWidth() ) );                                        // 29
        ba.append( QString( "%1\t" ).arg( ColorStr( gv_PS.at( j ).XReflineColor() ) ) );                            // 30
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).XRefline(), 0, 'g', 16 ) );                                 // 31

        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).drawYRefline() ) );                                         // 32
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).YReflineWidth() ) );                                        // 33
        ba.append( QString( "%1\t" ).arg( ColorStr( gv_PS.at( j ).YReflineColor() ) ) );                            // 34
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).YRefline(), 0, 'g', 16 ) );                                 // 35

        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).XMinimum(), 0, 'g', 16 ) );                                 // 36
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).XMaximum(), 0, 'g', 16 ) );                                 // 37

        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).AutoXnFrac() ) );                                           // 38
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).AutoXTickmarkSpacing() ) );                                 // 39
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).AutoXGraphMin(), 0, 'g', 16 ) );                            // 40
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).AutoXGraphMax(), 0, 'g', 16 ) );                            // 41

        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).ManualXnFrac() ) );                                         // 42
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).ManualXTickmarkSpacing() ) );                               // 43
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).ManualXGraphMin(), 0, 'g', 16 ) );                          // 44
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).ManualXGraphMax(), 0, 'g', 16 ) );                          // 45

        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).YMinimum(), 0, 'g', 16 ) );                                 // 46
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).YMaximum(), 0, 'g', 16 ) );                                 // 47

        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).AutoYnFrac() ) );                                           // 48
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).AutoYTickmarkSpacing() ) );                                 // 49
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).AutoYGraphMin(), 0, 'g', 16 ) );                            // 50
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).AutoYGraphMax(), 0, 'g', 16 ) );                            // 51

        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).ManualYnFrac() ) );                                         // 52
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).ManualYTickmarkSpacing() ) );                               // 53
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).ManualYGraphMin(), 0, 'g', 16 ) );                          // 54
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).ManualYGraphMax(), 0, 'g', 16 ) );                          // 55

        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).Median(), 0, 'g', 16 ) );                                   // 56
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).Mean(), 0, 'g', 16 ) );                                     // 57
        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).StandardDeviation(), 0, 'g', 16 ) );                        // 58

        ba.append( QString( "%1\t" ).arg( gv_PS.at( j ).isGeocode() ) );                                            // 59
        ba.append( QString( "%1\n" ).arg( gv_PS.at( j ).useManualScaleSettings() ) );                               // 60
    }

    ba.append( "[Data]\n" );
    ba.append( "Column\tRow\tValue\tText\tQualityFlag + Type\tStatus\n" );
    for ( int i=0; i<gv_Data.count(); i++ )
        ba.append( QString( "%1\t%2\t%3\t%4\t%5\t%6\n" ).arg( gv_Data.at( i ).Column() ).arg( gv_Data.at( i ).Row() ).arg( gv_Data.at( i ).Value(), 0, 'g', 16 ).arg( gv_Data.at( i ).Text() ).arg( gv_Data.at( i ).QualityFlag() ).arg( gv_Data.at( i ).Status() ) );

    fout.write( qCompress( ba, 9 ) );

    fout.close();

    return( _NOERROR_ );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-01-21

int MainWindow::readDataFile( const QString &s_FilenameIn )

{
    int         stopProgress    = _NOERROR_;

    int         i                 = 0;
    int         n                 = 0;
    int         i_NumOfParameters = 0;
    int         i_NumOfDataItems  = 0;

    QStringList sl_Input;

    QRect       ScreenGeometry;

// **********************************************************************************************

    gsl_DataDescription.clear();

    gv_Data.clear();
    gv_PS.clear();
    gv_PP.clear();

// **********************************************************************************************

    initProgress( 1, s_FilenameIn, tr( "Read data" ), 5 );

    if ( ( n = readFile( s_FilenameIn, sl_Input, -1, 0, -1 ) ) < 1 )  // read compressed file
    {
        resetProgress( 1 );
        return( _NODATAFOUND_ );
    }

    stopProgress = incProgress( 1, 1 );

// **********************************************************************************************

    if ( sl_Input.at( 0 ) != "PanPlot data file" )
    {
        resetProgress( 1 );
        return( -40 ); // wrong format
    }

    if ( sl_Input.at( 1 ).section( "\t", 1, 1 ) != _DATAFORMATVERSION_ )
    {
        resetProgress( 1 );
        return( -40 ); // wrong format
    }

// **********************************************************************************************

    n                 = sl_Input.count();
    i_NumOfParameters = sl_Input.at( 3 ).section( "\t", 1, 1 ).toInt();
    i_NumOfDataItems  = sl_Input.at( 4 ).section( "\t", 1, 1 ).toInt();

// **********************************************************************************************

    i = 6;
    while ( ( sl_Input.at( i ).section( "\t", 0, 0 ) != "[Position and size of window]" ) && ( i < n ) )
        gsl_DataDescription.append( sl_Input.at( i++ ) );

    stopProgress = incProgress( 1, 2 );

// **********************************************************************************************
// Position and size of program window

    if ( ++i < n )
    {
        QString s_Input = sl_Input.at( i );

        posWindow.setX( s_Input.section( "\t", 0, 0 ).toInt() );
        posWindow.setY( s_Input.section( "\t", 1, 1 ).toInt() );

        if ( posWindow.x() < 1 ) posWindow.setX( 1 );
        if ( posWindow.y() < 1 ) posWindow.setY( 1 );

        sizeWindow.setHeight( s_Input.section( "\t", 2, 2 ).toInt() );
        sizeWindow.setWidth( s_Input.section( "\t", 3, 3 ).toInt() );
    }

// **********************************************************************************************
// read plot position

    i += 2;
    if ( ++i < n )
    {
        QString s_PlotPosition = sl_Input.at( i );

        for ( int j=1; j<=i_NumOfParameters; j++ )
        {
            if ( s_PlotPosition.section( "\t", j, j ).isEmpty() == false )
            {
                if ( s_PlotPosition.section( "\t", j, j ) != "disabled" )
                    gv_PP.append( s_PlotPosition.section( "\t", j, j ).toInt() - 1 );
                else
                    gv_PP.append( -1 );
            }
        }
    }

// **********************************************************************************************
// read global options

    ++i;
    if ( ++i < n ) // 8
    {
        gi_Codec                = sl_Input.at( i ).section( "\t", 0, 0 ).toInt();
        gi_PlotOrientation      = sl_Input.at( i ).section( "\t", 1, 1 ).toInt();
        gi_ParameterOrientation = sl_Input.at( i ).section( "\t", 2, 2 ).toInt();
        gb_XReverseGraphRange   = (bool) sl_Input.at( i ).section( "\t", 3, 3 ).toInt();
        gb_YReverseGraphRange   = (bool) sl_Input.at( i ).section( "\t", 4, 4 ).toInt();
        gb_Antialiasing         = (bool) sl_Input.at( i ).section( "\t", 5, 5 ).toInt();
        gb_drawBackground       = (bool) sl_Input.at( i ).section( "\t", 6, 6 ).toInt();
    }

// Margins
    if ( ++i < n ) // 9
    {
        gi_marginLeft   = sl_Input.at( i ).section( "\t", 0, 0 ).toInt();
        gi_marginRight  = sl_Input.at( i ).section( "\t", 1, 1 ).toInt();
        gi_marginTop    = sl_Input.at( i ).section( "\t", 2, 2 ).toInt();
        gi_marginBottom = sl_Input.at( i ).section( "\t", 3, 3 ).toInt();
        gi_marginScale  = sl_Input.at( i ).section( "\t", 4, 4 ).toInt();
    }

// Diagram size
    if ( ++i < n ) // 10
    {
        gb_fixedDiagramSize  = (bool) sl_Input.at( i ).section( "\t", 0, 0 ).toInt();
        gi_diagramWidth      = sl_Input.at( i ).section( "\t", 1, 1 ).toInt();
        gi_diagramHeight     = sl_Input.at( i ).section( "\t", 2, 2 ).toInt();
        gi_diagramDistance   = sl_Input.at( i ).section( "\t", 3, 3 ).toInt();
        gi_diagramFrameWidth = sl_Input.at( i ).section( "\t", 4, 4 ).toInt();
    }

// Ticks
    if ( ++i < n ) // 11
    {
        gb_manuallyXScale = (bool) sl_Input.at( i ).section( "\t", 0, 0 ).toInt();
        gi_TickmarkLength = sl_Input.at( i ).section( "\t", 1, 1 ).toInt();
        gi_numMinorXTicks = sl_Input.at( i ).section( "\t", 2, 2 ).toInt();
        gi_numMinorYTicks = sl_Input.at( i ).section( "\t", 3, 3 ).toInt();
    }

    if ( ++i < n ) // 12
    {
        gi_TickmarkWidth      = sl_Input.at( i ).section( "\t", 0, 0 ).toInt();
        gi_TicklineWidth      = sl_Input.at( i ).section( "\t", 1, 1 ).toInt();
        gi_MinorTickmarkWidth = sl_Input.at( i ).section( "\t", 2, 2 ).toInt();
        gi_MinorTicklineWidth = sl_Input.at( i ).section( "\t", 3, 3 ).toInt();
    }

    if ( ++i < n ) // 13
    {
        gb_drawMajorXTicklines    = (bool) sl_Input.at( i ).section( "\t", 0, 0 ).toInt();
        gb_drawMajorXTicksLeft    = (bool) sl_Input.at( i ).section( "\t", 1, 1 ).toInt();
        gb_drawMajorXTicksRight   = (bool) sl_Input.at( i ).section( "\t", 2, 2 ).toInt();
        gb_drawMajorXTicksInside  = (bool) sl_Input.at( i ).section( "\t", 3, 3 ).toInt();
        gb_drawMajorXTicksOutside = (bool) sl_Input.at( i ).section( "\t", 4, 4 ).toInt();
    }

    if ( ++i < n ) // 14
    {
        gb_drawMajorYTicklines    = (bool) sl_Input.at( i ).section( "\t", 0, 0 ).toInt();
        gb_drawMajorYTicksTop     = (bool) sl_Input.at( i ).section( "\t", 1, 1 ).toInt();
        gb_drawMajorYTicksBottom  = (bool) sl_Input.at( i ).section( "\t", 2, 2 ).toInt();
        gb_drawMajorYTicksInside  = (bool) sl_Input.at( i ).section( "\t", 3, 3 ).toInt();
        gb_drawMajorYTicksOutside = (bool) sl_Input.at( i ).section( "\t", 4, 4 ).toInt();
    }

    if ( ++i < n ) // 15
    {
        gb_drawMinorXTicklines    = (bool) sl_Input.at( i ).section( "\t", 0, 0 ).toInt();
        gb_drawMinorXTicksLeft    = (bool) sl_Input.at( i ).section( "\t", 1, 1 ).toInt();
        gb_drawMinorXTicksRight   = (bool) sl_Input.at( i ).section( "\t", 2, 2 ).toInt();
        gb_drawMinorXTicksInside  = (bool) sl_Input.at( i ).section( "\t", 3, 3 ).toInt();
        gb_drawMinorXTicksOutside = (bool) sl_Input.at( i ).section( "\t", 4, 4 ).toInt();
    }

    if ( ++i < n ) // 16
    {
        gb_drawMinorYTicklines    = (bool) sl_Input.at( i ).section( "\t", 0, 0 ).toInt();
        gb_drawMinorYTicksTop     = (bool) sl_Input.at( i ).section( "\t", 1, 1 ).toInt();
        gb_drawMinorYTicksBottom  = (bool) sl_Input.at( i ).section( "\t", 2, 2 ).toInt();
        gb_drawMinorYTicksInside  = (bool) sl_Input.at( i ).section( "\t", 3, 3 ).toInt();
        gb_drawMinorYTicksOutside = (bool) sl_Input.at( i ).section( "\t", 4, 4 ).toInt();
    }

    if ( ++i < n ) // 17
    {
        gb_drawMarkers           = (bool) sl_Input.at( i ).section( "\t", 0, 0 ).toInt();
        gb_drawLines             = (bool) sl_Input.at( i ).section( "\t", 1, 1 ).toInt();
        gb_drawColorized         = (bool) sl_Input.at( i ).section( "\t", 2, 2 ).toInt();
        gb_drawDataText          = (bool) sl_Input.at( i ).section( "\t", 3, 3 ).toInt();
        gb_drawDiagramBackground = (bool) sl_Input.at( i ).section( "\t", 4, 4 ).toInt();
    }

    if ( ++i < n ) // 18
    {
        gi_MarkerSize            = sl_Input.at( i ).section( "\t", 0, 0 ).toInt();
        gi_LineWidth             = sl_Input.at( i ).section( "\t", 1, 1 ).toInt();
        gi_ColorizedPattern      = sl_Input.at( i ).section( "\t", 2, 2 ).toInt();
        gi_DateTimeFormat        = sl_Input.at( i ).section( "\t", 3, 3 ).toInt();
    }

    if ( ++i < n ) // 19
    {
        gc_MarkerColor              = setColor( sl_Input.at( i ).section( "\t", 0, 0 ) );
        gc_LineColor                = setColor( sl_Input.at( i ).section( "\t", 1, 1 ) );
        gc_ColorizedGreaterRefColor = setColor( sl_Input.at( i ).section( "\t", 2, 2 ) );
        gc_ColorizedLessRefColor    = setColor( sl_Input.at( i ).section( "\t", 3, 3 ) );
        gc_DiagramBackgroundColor   = setColor( sl_Input.at( i ).section( "\t", 4, 4 ) );
        gc_DataTextColor            = setColor( sl_Input.at( i ).section( "\t", 5, 5 ) );
    }

    if ( ++i < n ) // 20
    {
        gc_DiagramFrameColor    = setColor( sl_Input.at( i ).section( "\t", 0, 0 ) );
        gc_BackgroundColor      = setColor( sl_Input.at( i ).section( "\t", 1, 1 ) );
        gc_HeaderTextColor      = setColor( sl_Input.at( i ).section( "\t", 2, 2 ) );
        gc_TickmarkColor        = setColor( sl_Input.at( i ).section( "\t", 3, 3 ) );
        gc_TicklineColor        = setColor( sl_Input.at( i ).section( "\t", 4, 4 ) );
        gc_MinorTicklineColor   = setColor( sl_Input.at( i ).section( "\t", 5, 5 ) );
    }

    if ( ++i < n ) // 21
        gf_DataTextFont = setFont( sl_Input.at( i ) );

    if ( ++i < n ) // 22
        gf_HeaderTextFont = setFont( sl_Input.at( i ) );

// **********************************************************************************************
// calculate global tick options

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

    stopProgress = incProgress( 1, 3 );

// **********************************************************************************************
// read parameter settings

    ++i;
    for ( int j=0; j<i_NumOfParameters; j++ )
    {
        QString s_Input = sl_Input.at( ++i );

        gv_PS.append( PlotSettings( false, j ) );

        int k = 1;
        gv_PS[j].setParameterNameUnit( s_Input.section( "\t", k, k ), s_Input.section( "\t", k+1, k+1 ) );   // ParameterName(), ParameterUnit()

        k += 3; // k = 4;
        gv_PS[j].setStartPos( s_Input.section( "\t", k, k ).toInt() );                                       // StartPos()
        gv_PS[j].setDataCount( s_Input.section( "\t", k+1, k+1 ).toInt() );                                  // DataCount()
        gv_PS[j].setType( s_Input.section( "\t", k+2, k+2 ).toInt() );                                       // Type()
        gv_PS[j].setQuality( s_Input.section( "\t", k+3, k+3 ).toInt() );                                    // Quality()

        k += 4; // k = 8;
        gv_PS[j].setNumOfPointsNumeric( s_Input.section( "\t", k, k ).toInt() );                             // NumOfPointsNumeric()
        gv_PS[j].setNumOfPointsDataText( s_Input.section( "\t", k+1, k+1 ).toInt() );                        // NumOfPointsData()

        k += 2; // k = 10;
        gv_PS[j].setXMinorTicksOptions( s_Input.section( "\t", k, k ).toInt(), b_drawMinorXTickmarksLeftOutside, b_drawMinorXTickmarksLeftInside, b_drawMinorXTickmarksRightOutside, b_drawMinorXTickmarksRightInside, gb_drawMinorXTicklines );
        gv_PS[j].setYMinorTicksOptions( s_Input.section( "\t", k+1, k+1 ).toInt(), b_drawMinorYTickmarksTopOutside, b_drawMinorYTickmarksTopInside, b_drawMinorYTickmarksBottomOutside, b_drawMinorYTickmarksBottomInside, gb_drawMinorYTicklines );

        // Diagram background options
        k += 2; // k = 12;
        gv_PS[j].setDiagramBackgroundOptions( (bool) s_Input.section( "\t", k, k ).toInt(), setColor( s_Input.section( "\t", k+1, k+1 ) ) );  // drawDiagramBackground(), DiagramBackgroundColor()

        // Marker options
        k += 2; // k = 14;
        gv_PS[j].setMarkerOptions( (bool) s_Input.section( "\t", k, k ).toInt(), s_Input.section( "\t", k+1, k+1 ).toInt(), setColor( s_Input.section( "\t", k+2, k+2 ) ) ); // drawMarker(), MarkerSize(), MarkerColor()

        // Data text options
        k += 3; // k = 17;
        gv_PS[j].setDataTextOptions( (bool) s_Input.section( "\t", k, k ).toInt(), setFont( s_Input.section( "\t", k+1, k+1 ) ), setColor( s_Input.section( "\t", k+2, k+2 ) ) ); // drawDataText(), DataTextFont(), DataTextColor

        // Line options
        k += 3; // k = 20;
        gv_PS[j].setLineOptions( (bool) s_Input.section( "\t", k, k ).toInt(), s_Input.section( "\t", k+1, k+1 ).toInt(), setColor( s_Input.section( "\t", k+2, k+2 ) ) ); // drawLine(), LineWidth(), LineColor()

        // Colorized options
        k += 3; // k = 23;
        gv_PS[j].setColorizedOptions( (bool) s_Input.section( "\t", k, k ).toInt(), s_Input.section( "\t", k+1, k+1 ).toInt(), setColor( s_Input.section( "\t", k+2, k+2 ) ), setColor( s_Input.section( "\t", k+3, k+3 ) ) ); // drawColorized(), Pattern(), ColorizedGreaterRefColor(), ColorizedLessRefColor()

        // Y reverse graph range
        k += 4; // k = 27;
        gv_PS[j].setYReverseGraphRange( (bool) s_Input.section( "\t", k, k ).toInt() ); // YReverseGraphRange()

        // X refline options
        k += 1; // k = 28;
        gv_PS[j].setXReflineOptions( (bool) s_Input.section( "\t", k, k ).toInt(), s_Input.section( "\t", k+1, k+1 ).toInt(), setColor( s_Input.section( "\t", k+2, k+2 ) ), s_Input.section( "\t", k+3, k+3 ).toDouble() ); // drawXRefline(), XReflineWidth, XReflineColor, XRefline()

        // Y refline options
        k += 4; // k = 32;
        gv_PS[j].setYReflineOptions( (bool) s_Input.section( "\t", k, k ).toInt(), s_Input.section( "\t", k+1, k+1 ).toInt(), setColor( s_Input.section( "\t", k+2, k+2 ) ), s_Input.section( "\t", k+3, k+3 ).toDouble() ); // drawYRefline(), YReflineWidth, YReflineColor, YRefline()

        // X minimum, X maximum
        k += 4; // k = 36;
        gv_PS[j].setXMinMax( s_Input.section( "\t", k, k ).toDouble(), s_Input.section( "\t", k+1, k+1 ).toDouble() ); // XMinimum(), XMaximum()

        // X nfrac, X tickmark spacing, X graph min, X graph max
        k += 2; // k = 38;
        gv_PS[j].setXNiceLabel( s_Input.section( "\t", k, k ).toInt(), s_Input.section( "\t", k+1, k+1 ).toDouble(), s_Input.section( "\t", k+2, k+2 ).toDouble(), s_Input.section( "\t", k+3, k+3 ).toDouble() ); // XnFrac(), XTickmarkSpacing(), XGraphMin(), XGraphMax()
        gv_PS[j].setAutoXNiceLabel( s_Input.section( "\t", k, k ).toInt(), s_Input.section( "\t", k+1, k+1 ).toDouble(), s_Input.section( "\t", k+2, k+2 ).toDouble(), s_Input.section( "\t", k+3, k+3 ).toDouble() ); // AutoXnFrac(), AutoXTickmarkSpacing(), AutoXGraphMin(), AutoXGraphMax()

        k += 4; // k = 42;
        gv_PS[j].setManualXNiceLabel( s_Input.section( "\t", k, k ).toInt(), s_Input.section( "\t", k+1, k+1 ).toDouble(), s_Input.section( "\t", k+2, k+2 ).toDouble(), s_Input.section( "\t", k+3, k+3 ).toDouble() ); // ManualXnFrac(), ManualXTickmarkSpacing(), ManualXGraphMin(), ManualXGraphMax()

        // Y minimum, Y maximum
        k += 4; // k = 46;
        gv_PS[j].setYMinMax( s_Input.section( "\t", k, k ).toDouble(), s_Input.section( "\t", k+1, k+1 ).toDouble() ); // YMinimum(), YMaximum()

        // Y nfrac, Y tickmark spacing, Y graph min, Y graph max
        k += 2; // k = 48;
        gv_PS[j].setYNiceLabel( s_Input.section( "\t", k, k ).toInt(), s_Input.section( "\t", k+1, k+1 ).toDouble(), s_Input.section( "\t", k+2, k+2 ).toDouble(), s_Input.section( "\t", k+3, k+3 ).toDouble() ); // YnFrac(), YTickmarkSpacing(), YGraphMin(), YGraphMax()
        gv_PS[j].setAutoYNiceLabel( s_Input.section( "\t", k, k ).toInt(), s_Input.section( "\t", k+1, k+1 ).toDouble(), s_Input.section( "\t", k+2, k+2 ).toDouble(), s_Input.section( "\t", k+3, k+3 ).toDouble() ); // AutoYnFrac(), AutoYTickmarkSpacing(), AutoYGraphMin(), AutoYGraphMax()

        k += 4; // k = 52;
        gv_PS[j].setManualYNiceLabel( s_Input.section( "\t", k, k ).toInt(), s_Input.section( "\t", k+1, k+1 ).toDouble(), s_Input.section( "\t", k+2, k+2 ).toDouble(), s_Input.section( "\t", k+3, k+3 ).toDouble() ); // ManualYnFrac(), ManualYTickmarkSpacing(), ManualYGraphMin(), ManualYGraphMax()

        // Median
        k += 4; // k = 56;
        gv_PS[j].setMedian( s_Input.section( "\t", k, k ).toDouble() ); // Median()

        // Mean
        k += 1; // k = 57;
        gv_PS[j].setMean( s_Input.section( "\t", k, k ).toDouble() ); // Mean()

        // Standard deviation
        k += 1; // k = 58;
        gv_PS[j].setStandardDeviation( s_Input.section( "\t", k, k ).toDouble() ); // StandardDeviation()

        // isGeocode
        k += 1; // k = 59;
        gv_PS[j].setGeocode( (bool) s_Input.section( "\t", k, k ).toInt() ); // isGeocode

        // useManualScaleSettings
        k += 1; // k = 60;
        gv_PS[j].setUseManualScaleSettings( (bool) s_Input.section( "\t", k, k ).toInt() ); // useManualScaleSettings

        // X tick options
        gv_PS[j].setXTicksOptions( gi_TickmarkLength, b_drawMajorXTickmarksLeftOutside, b_drawMajorXTickmarksLeftInside, b_drawMajorXTickmarksRightOutside, b_drawMajorXTickmarksRightInside, gb_drawMajorXTicklines, gb_drawXTickmarkLabels );

        // Y tick options
        gv_PS[j].setYTicksOptions( gi_TickmarkLength, b_drawMajorYTickmarksTopOutside, b_drawMajorYTickmarksTopInside, b_drawMajorYTickmarksBottomOutside, b_drawMajorYTickmarksBottomInside, gb_drawMajorYTicklines, gb_drawYTickmarkLabels );
    }

    stopProgress = incProgress( 1, 4 );

    i += 2; gv_Data.clear();

    for ( int j=0; j<i_NumOfDataItems; j++ )
    {
        QString s_Input = sl_Input.at( ++i );

        // Column(), Row(), Text(), Value(), QualityFlag(), Status()
        gv_Data.append( DataItem( s_Input.section( "\t", 0, 0 ).toInt(), s_Input.section( "\t", 1, 1 ).toInt(), s_Input.section( "\t", 3, 3 ), s_Input.section( "\t", 2, 2 ).toDouble(), s_Input.section( "\t", 4, 4 ).toInt(), s_Input.section( "\t", 5, 5 ).toInt() ) );
    }

// ***************************************************************************************

    resetProgress( 1 );

    if ( stopProgress != _NOERROR_ )
        return( stopProgress );

    ScreenGeometry = QApplication::desktop()->availableGeometry();

    if ( ( ScreenGeometry.width() > sizeWindow.width() ) && ( ScreenGeometry.height() > sizeWindow.height() ) )
        this->resize( sizeWindow );

    if ( ( ScreenGeometry.width() > posWindow.x() ) && ( ScreenGeometry.height() > posWindow.y() ) )
        this->move( posWindow );

    return( _NOERROR_ );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

/*! @brief Datei sichern.
    Sichert Einstellungen und Daten in PP2-Datei.
*/

int MainWindow::saveDataFile()
{
    int       err = _NOERROR_;

    QFileInfo fi( gsl_FilenameList.at( 0 ) );

    err = writeDataFile( fi.absolutePath() + "/" + fi.completeBaseName() + ".pp2" );

    return( err );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

/*! @brief Datei sichern als.
    Sichert Einstellungen und Daten in PP2-Datei. Dialog erfragt neuen Dateinamen.
*/

int MainWindow::saveDataFileAs()
{
    int       err           = _NOERROR_;
    QString   s_FilenameOut = "";

// **********************************************************************************************

    QFileInfo fi( gsl_FilenameList.at( 0 ) );

#if defined(Q_OS_LINUX)
    s_FilenameOut = QFileDialog::getSaveFileName(this, tr( "Save data to file" ), fi.absolutePath() + "/" + fi.completeBaseName() + ".pp2", tr( "PanPlot2 file (*.pp2)" ), 0, QFileDialog::DontUseNativeDialog );
#endif

#if defined(Q_OS_WIN)
    s_FilenameOut = QFileDialog::getSaveFileName(this, tr( "Save data to file" ), fi.absolutePath() + "/" + fi.completeBaseName() + ".pp2", tr( "PanPlot2 file (*.pp2)" ), 0, QFileDialog::DontUseNativeDialog );
#endif

#if defined(Q_OS_MAC)
    s_FilenameOut = QFileDialog::getSaveFileName(this, tr( "Save data to file" ), fi.absolutePath() + "/" + fi.completeBaseName() + ".pp2", tr( "PanPlot2 file (*.pp2)" ), 0, QFileDialog::DontUseNativeDialog );
#endif

    err = writeDataFile( s_FilenameOut );

    return( err );
}
