/* DataFile.cpp               */
/* 2011-01-21                 */
/* Dr. Rainer Sieger          */

#include <QApplication>
#include <QtGui>

#include "Application.h"
#include "DataItem.h"
#include "PlotSettings.h"


int MainWindow::writeDataFile( const QString &s_FilenameOut, const int i_NumOfFiles )
{
    if ( ( gv_PP.count() < 1 ) || ( i_NumOfFiles < 0 ) )
        return( NOERROR );

    QFile fout( s_FilenameOut );

    if ( fout.open( QIODevice::WriteOnly ) == FALSE )
        return( -10 );

// **********************************************************************************************

    QTextStream ts( &fout );

    ts << "PanPlot data file. Version: " << DATAFORMATVERSION << endl;
    ts << "Created: " << QDateTime::currentDateTime().toString( Qt::ISODate ) << endl;
    ts << "Number of parameters:\t" << gv_PS.count() << endl;
    ts << "Number of data items:\t" << gv_Data.count() << endl;

    ts << "[Data description]" << endl;
    for ( int i=0; i<gsl_DataDescription.count(); i++ )
        ts << gsl_DataDescription.at( i ) << endl;

    ts << "[Position and size of window]" << endl;                                                                                            // 1
    ts << x() << ", " << y() << ", " << height() << ", " << width() << endl;                                                                  // 2

    ts << "[Plot positions]" << endl;
    ts << "Diagram number:\tAbscissa";
    for ( int i=1; i<gv_PP.count(); i++ )
        ts << "\t" << i;
    ts << endl;

    ts << "Data column:";
    for ( int i=0; i<gv_PP.count(); i++ )
    {
        if ( gv_PP.at( i ) > -1 )
            ts << "\t" << gv_PP.at( i ) + 1;
        else
            ts << "\tdisabled";
    }
    ts << endl;

    ts << "[Global settings]" << endl;
    ts << gi_Codec << ", " << gi_ParameterOrientation << ", " << gb_XReverseGraphRange << ", " << gb_YReverseGraphRange << ", " << gb_Antialiasing << ", " << gb_drawBackground << endl;
    ts << gi_marginLeft << ", " << gi_marginRight << ", " << gi_marginTop << ", " << gi_marginBottom << ", " << gi_marginScale << endl;
    ts << gb_fixedDiagramSize << ", " << gi_diagramWidth << ", " << gi_diagramHeight << ", " << gi_diagramDistance << ", " << gi_diagramFrameWidth << endl;
    ts << gi_TickmarkLength << ", " << gi_numMinorXTicks << ", " << gi_numMinorYTicks << endl;    
    ts << gi_TickmarkWidth << ", " << gi_TicklineWidth << ", " << gi_MinorTickmarkWidth << ", " << gi_MinorTicklineWidth << endl;
    ts << gb_drawMajorXTicklines << ", " << gb_drawMajorXTicksLeft << ", " << gb_drawMajorXTicksRight << ", " << gb_drawMajorXTicksInside << ", " << gb_drawMajorXTicksOutside << endl;
    ts << gb_drawMajorYTicklines << ", " << gb_drawMajorYTicksTop << ", " << gb_drawMajorYTicksBottom << ", " << gb_drawMajorYTicksInside << ", " << gb_drawMajorYTicksOutside << endl;
    ts << gb_drawMinorXTicklines << ", " << gb_drawMinorXTicksLeft << ", " << gb_drawMinorXTicksRight << ", " << gb_drawMinorXTicksInside << ", " << gb_drawMinorXTicksOutside << endl;
    ts << gb_drawMinorYTicklines << ", " << gb_drawMinorYTicksTop << ", " << gb_drawMinorYTicksBottom << ", " << gb_drawMinorYTicksInside << ", " << gb_drawMinorYTicksOutside << endl;
    ts << gb_drawMarkers << ", " << gb_drawLines << ", " << gb_drawColorized << ", " << gb_drawDataText << ", " << gb_drawDiagramBackground << endl;
    ts << gi_MarkerSize << ", " << gi_LineWidth << ", " << gi_ColorizedPattern << endl;
    ts << ColorStr( gc_MarkerColor ) << ", " << ColorStr( gc_LineColor ) << ", " << ColorStr( gc_ColorizedColor ) << ", " << ColorStr( gc_DiagramBackgroundColor ) << ", " << ColorStr( gc_DataTextColor ) << endl;
    ts << ColorStr( gc_DiagramFrameColor ) << ", " << ColorStr( gc_BackgroundColor ) << ", " << ColorStr( gc_HeaderTextColor ) << ", " << ColorStr( gc_TickmarkColor ) << ", " << ColorStr( gc_TicklineColor ) << ", " << ColorStr( gc_MinorTicklineColor ) << endl;
    ts << FontStr( g_DataTextFont ) << endl;
    ts << FontStr( g_HeaderTextFont ) << endl;

    ts << "[Parameter settings]" << endl;
    for ( int j=0; j<gv_PS.count(); j++ )
    {
        ts << j+1 << "\t";
        ts << gv_PS.at( j ).ParameterName() << "\t";                                        // 1
        ts << gv_PS.at( j ).ParameterUnit() << "\t";                                        // 2
        ts << gv_PS.at( j ).Parameter() << "\t";                                            // 3

        ts << gv_PS.at( j ).StartPos() << "\t";                                             // 4
        ts << gv_PS.at( j ).DataCount() << "\t";                                            // 5
        ts << gv_PS.at( j ).Type() << "\t";                                                 // 6
        ts << gv_PS.at( j ).Quality() << "\t";                                              // 7

        ts << gv_PS.at( j ).NumOfPointsNumeric() << "\t";                                   // 8
        ts << gv_PS.at( j ).NumOfPointsDataText() << "\t";                                  // 9

        ts << gv_PS.at( j ).NumOfXMinorTicks() << "\t";                                     // 10
        ts << gv_PS.at( j ).NumOfYMinorTicks() << "\t";                                     // 11

        ts << gv_PS.at( j ).drawDiagramBackground() << "\t";                                // 12
        ts << ColorStr( gv_PS.at( j ).DiagramBackgroundColor() ) << "\t";                   // 13

        ts << gv_PS.at( j ).drawMarker() << "\t";                                           // 14
        ts << gv_PS.at( j ).MarkerSize() << "\t";                                           // 15
        ts << ColorStr( gv_PS.at( j ).MarkerColor() ) << "\t";                              // 16

        ts << gv_PS.at( j ).drawDataText() << "\t";                                         // 17
        ts << FontStr( gv_PS.at( j ).DataTextFont() ) << "\t";                              // 18
        ts << ColorStr( gv_PS.at( j ).DataTextColor() ) << "\t";                            // 19

        ts << gv_PS.at( j ).drawLine() << "\t";                                             // 20
        ts << gv_PS.at( j ).LineWidth() << "\t";                                            // 21
        ts << ColorStr( gv_PS.at( j ).LineColor() ) << "\t";                                // 22

        ts << gv_PS.at( j ).drawColorized() << "\t";                                        // 23
        ts << gv_PS.at( j ).Pattern() << "\t";                                              // 24
        ts << ColorStr( gv_PS.at( j ).ColorizedColor() ) << "\t";                           // 25

        ts << gv_PS.at( j ).YReverseGraphRange() << "\t";                                   // 26

        ts << gv_PS.at( j ).drawXRefline() << "\t";                                         // 27
        ts << QString( "%1" ).arg( gv_PS.at( j ).XRefline(), 0, 'g', 16 ) << "\t";          // 28

        ts << gv_PS.at( j ).drawYRefline() << "\t";                                         // 29
        ts << QString( "%1" ).arg( gv_PS.at( j ).YRefline(), 0, 'g', 16 ) << "\t";          // 30

        ts << QString( "%1" ).arg( gv_PS.at( j ).XMinimum(), 0, 'g', 16 ) << "\t";          // 31
        ts << QString( "%1" ).arg( gv_PS.at( j ).XMaximum(), 0, 'g', 16 ) << "\t";          // 32

        ts << gv_PS.at( j ).XnFrac() << "\t";                                               // 33
        ts << gv_PS.at( j ).XTickmarkSpacing() << "\t";                                     // 34
        ts << QString( "%1" ).arg( gv_PS.at( j ).XGraphMin(), 0, 'g', 16 ) << "\t";         // 35
        ts << QString( "%1" ).arg( gv_PS.at( j ).XGraphMax(), 0, 'g', 16 ) << "\t";         // 36
        ts << QString( "%1" ).arg( gv_PS.at( j ).XGraphRange(), 0, 'g', 16 ) << "\t";       // 37

        ts << QString( "%1" ).arg( gv_PS.at( j ).YMinimum(), 0, 'g', 16 ) << "\t";          // 38
        ts << QString( "%1" ).arg( gv_PS.at( j ).YMaximum(), 0, 'g', 16 ) << "\t";          // 39

        ts << gv_PS.at( j ).YnFrac() << "\t";                                               // 40
        ts << gv_PS.at( j ).YTickmarkSpacing() << "\t";                                     // 41
        ts << QString( "%1" ).arg( gv_PS.at( j ).YGraphMin(), 0, 'g', 16 ) << "\t";         // 42
        ts << QString( "%1" ).arg( gv_PS.at( j ).YGraphMax(), 0, 'g', 16 ) << "\t";         // 43
        ts << QString( "%1" ).arg( gv_PS.at( j ).YGraphRange(), 0, 'g', 16 ) << "\t";       // 44

        ts << QString( "%1" ).arg( gv_PS.at( j ).Median(), 0, 'g', 16 ) << "\t";            // 45
        ts << QString( "%1" ).arg( gv_PS.at( j ).Mean(), 0, 'g', 16 ) << "\t";              // 46
        ts << QString( "%1" ).arg( gv_PS.at( j ).StandardDeviation(), 0, 'g', 16 ) << "\t"; // 47

        ts << gv_PS.at( j ).isGeocode() << endl;                                            // 48
    }

    ts << "[Data]" << endl;
    ts << "Column\tRow\tText\tValue\tQualityFlag + Type\tStatus" << endl;
    for ( int i=0; i<gv_Data.count(); i++ )
        ts << gv_Data.at( i ).Column() << "\t" << gv_Data.at( i ).Row() << "\t" << gv_Data.at( i ).Text() << "\t" << QString( "%1" ).arg( gv_Data.at( i ).Value(), 0, 'g', 16 ) << "\t" << gv_Data.at( i ).QualityFlag() << "\t" << gv_Data.at( i ).Status() << endl;


    fout.close();

    return( NOERROR );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-01-21

int MainWindow::readDataFile( const QStringList &sl_Input )
{
    QString     s_DataFormatVersion = "PanPlot data file. Version: " + DATAFORMATVERSION;

    int         i                 = 0;
    int         n                 = 0;
    int         i_NumOfParameters = 0;
    int         i_NumOfDataItems  = 0;

// **********************************************************************************************

    if ( sl_Input.at( 0 ).section( "\t", 0, 0 ) != s_DataFormatVersion )
        return( -40 ); // wrong format

// **********************************************************************************************

    n                 = sl_Input.count();
    i_NumOfParameters = sl_Input.at( 2 ).section( "\t", 1, 1 ).toInt();
    i_NumOfDataItems  = sl_Input.at( 3 ).section( "\t", 1, 1 ).toInt();

// **********************************************************************************************

    i = 5;
    while ( ( sl_Input.at( i ).section( "\t", 0, 0 ) != "[Position and size of window]" ) && ( i < sl_Input.count() ) )
        gsl_DataDescription.append( sl_Input.at( i++ ) );

// **********************************************************************************************
// Position and size of program window

    if ( ++i < n )
    {
        posWindow.setX( sl_Input.at( i ).section( ",", 0, 0 ).toInt() );
        posWindow.setY( sl_Input.at( i ).section( ",", 1, 1 ).toInt() );

        sizeWindow.setHeight( sl_Input.at( i ).section( ",", 2, 2 ).toInt() );
        sizeWindow.setWidth( sl_Input.at( i ).section( ",", 3, 3 ).toInt() );

        this->resize( sizeWindow );
        this->move( posWindow );
    }

// **********************************************************************************************
// read plot position

    i += 2;
    if ( ++i < sl_Input.count() )
    {
        QString s_PlotPosition = sl_Input.at( i );

        for ( int j=1; j<=i_NumOfParameters; j++ )
        {
            if ( s_PlotPosition.section( "\t", j, j ).isEmpty() == FALSE )
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
        gi_Codec                = sl_Input.at( i ).section( ",", 0, 0 ).toInt();
        gi_ParameterOrientation = sl_Input.at( i ).section( ",", 1, 1 ).toInt();
        gb_XReverseGraphRange   = (bool) sl_Input.at( i ).section( ",", 2, 2 ).toInt();
        gb_YReverseGraphRange   = (bool) sl_Input.at( i ).section( ",", 3, 3 ).toInt();
        gb_Antialiasing         = (bool) sl_Input.at( i ).section( ",", 4, 4 ).toInt();
        gb_drawBackground       = (bool) sl_Input.at( i ).section( ",", 5, 5 ).toInt();
    }

// Margins
    if ( ++i < n ) // 9
    {
        gi_marginLeft   = sl_Input.at( i ).section( ",", 0, 0 ).toInt();
        gi_marginRight  = sl_Input.at( i ).section( ",", 1, 1 ).toInt();
        gi_marginTop    = sl_Input.at( i ).section( ",", 2, 2 ).toInt();
        gi_marginBottom = sl_Input.at( i ).section( ",", 3, 3 ).toInt();
        gi_marginScale  = sl_Input.at( i ).section( ",", 4, 4 ).toInt();
    }

// Diagram size
    if ( ++i < n ) // 10
    {
        gb_fixedDiagramSize  = (bool) sl_Input.at( i ).section( ",", 0, 0 ).toInt();
        gi_diagramWidth      = sl_Input.at( i ).section( ",", 1, 1 ).toInt();
        gi_diagramHeight     = sl_Input.at( i ).section( ",", 2, 2 ).toInt();
        gi_diagramDistance   = sl_Input.at( i ).section( ",", 3, 3 ).toInt();
        gi_diagramFrameWidth = sl_Input.at( i ).section( ",", 4, 4 ).toInt();
    }

// Ticks
    if ( ++i < n ) // 11
    {
        gi_TickmarkLength = sl_Input.at( i ).section( ",", 0, 0 ).toInt();
        gi_numMinorXTicks = sl_Input.at( i ).section( ",", 1, 1 ).toInt();
        gi_numMinorYTicks = sl_Input.at( i ).section( ",", 2, 2 ).toInt();
    }

    if ( ++i < n ) // 12
    {
        gi_TickmarkWidth      = sl_Input.at( i ).section( ",", 0, 0 ).toInt();
        gi_TicklineWidth      = sl_Input.at( i ).section( ",", 1, 1 ).toInt();
        gi_MinorTickmarkWidth = sl_Input.at( i ).section( ",", 2, 2 ).toInt();
        gi_MinorTicklineWidth = sl_Input.at( i ).section( ",", 3, 3 ).toInt();
    }

    if ( ++i < n ) // 13
    {
        gb_drawMajorXTicklines    = (bool) sl_Input.at( i ).section( ",", 0, 0 ).toInt();
        gb_drawMajorXTicksLeft    = (bool) sl_Input.at( i ).section( ",", 1, 1 ).toInt();
        gb_drawMajorXTicksRight   = (bool) sl_Input.at( i ).section( ",", 2, 2 ).toInt();
        gb_drawMajorXTicksInside  = (bool) sl_Input.at( i ).section( ",", 3, 3 ).toInt();
        gb_drawMajorXTicksOutside = (bool) sl_Input.at( i ).section( ",", 4, 4 ).toInt();
    }

    if ( ++i < n ) // 14
    {
        gb_drawMajorYTicklines    = (bool) sl_Input.at( i ).section( ",", 0, 0 ).toInt();
        gb_drawMajorYTicksTop     = (bool) sl_Input.at( i ).section( ",", 1, 1 ).toInt();
        gb_drawMajorYTicksBottom  = (bool) sl_Input.at( i ).section( ",", 2, 2 ).toInt();
        gb_drawMajorYTicksInside  = (bool) sl_Input.at( i ).section( ",", 3, 3 ).toInt();
        gb_drawMajorYTicksOutside = (bool) sl_Input.at( i ).section( ",", 4, 4 ).toInt();
    }

    if ( ++i < n ) // 15
    {
        gb_drawMinorXTicklines    = (bool) sl_Input.at( i ).section( ",", 0, 0 ).toInt();
        gb_drawMinorXTicksLeft    = (bool) sl_Input.at( i ).section( ",", 1, 1 ).toInt();
        gb_drawMinorXTicksRight   = (bool) sl_Input.at( i ).section( ",", 2, 2 ).toInt();
        gb_drawMinorXTicksInside  = (bool) sl_Input.at( i ).section( ",", 3, 3 ).toInt();
        gb_drawMinorXTicksOutside = (bool) sl_Input.at( i ).section( ",", 4, 4 ).toInt();
    }

    if ( ++i < n ) // 16
    {
        gb_drawMinorYTicklines    = (bool) sl_Input.at( i ).section( ",", 0, 0 ).toInt();
        gb_drawMinorYTicksTop     = (bool) sl_Input.at( i ).section( ",", 1, 1 ).toInt();
        gb_drawMinorYTicksBottom  = (bool) sl_Input.at( i ).section( ",", 2, 2 ).toInt();
        gb_drawMinorYTicksInside  = (bool) sl_Input.at( i ).section( ",", 3, 3 ).toInt();
        gb_drawMinorYTicksOutside = (bool) sl_Input.at( i ).section( ",", 4, 4 ).toInt();
    }

    if ( ++i < n ) // 17
    {
        gb_drawMarkers           = (bool) sl_Input.at( i ).section( ",", 0, 0 ).toInt();
        gb_drawLines             = (bool) sl_Input.at( i ).section( ",", 1, 1 ).toInt();
        gb_drawColorized         = (bool) sl_Input.at( i ).section( ",", 2, 2 ).toInt();
        gb_drawDataText          = (bool) sl_Input.at( i ).section( ",", 3, 3 ).toInt();
        gb_drawDiagramBackground = (bool) sl_Input.at( i ).section( ",", 4, 4 ).toInt();
    }

    if ( ++i < n ) // 18
    {
        gi_MarkerSize            = sl_Input.at( i ).section( ",", 0, 0 ).toInt();
        gi_LineWidth             = sl_Input.at( i ).section( ",", 1, 1 ).toInt();
        gi_ColorizedPattern      = sl_Input.at( i ).section( ",", 2, 2 ).toInt();
    }

    if ( ++i < n ) // 19
    {
        gc_MarkerColor              = setColor( sl_Input.at( i ).section( ",", 0, 0 ) );
        gc_LineColor                = setColor( sl_Input.at( i ).section( ",", 1, 1 ) );
        gc_ColorizedColor           = setColor( sl_Input.at( i ).section( ",", 2, 2 ) );
        gc_DiagramBackgroundColor   = setColor( sl_Input.at( i ).section( ",", 3, 3 ) );
        gc_DataTextColor            = setColor( sl_Input.at( i ).section( ",", 4, 4 ) );
    }

    if ( ++i < n ) // 20
    {
        gc_DiagramFrameColor    = setColor( sl_Input.at( i ).section( ",", 0, 0 ) );
        gc_BackgroundColor      = setColor( sl_Input.at( i ).section( ",", 1, 1 ) );
        gc_HeaderTextColor      = setColor( sl_Input.at( i ).section( ",", 2, 2 ) );
        gc_TickmarkColor        = setColor( sl_Input.at( i ).section( ",", 3, 3 ) );
        gc_TicklineColor        = setColor( sl_Input.at( i ).section( ",", 4, 4 ) );
        gc_MinorTicklineColor   = setColor( sl_Input.at( i ).section( ",", 5, 5 ) );
    }

    if ( ++i < n ) // 21
        g_DataTextFont = setFont( sl_Input.at( i ) );

    if ( ++i < n ) // 22
        g_HeaderTextFont = setFont( sl_Input.at( i ) );

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

// **********************************************************************************************
// read parameter settings

    ++i;
    for ( int j=0; j<i_NumOfParameters; j++ )
    {
        QString s_Input = sl_Input.at( ++i );

        gv_PS.append( PlotSettings( FALSE, j ) );

        gv_PS[j].setParameterNameUnit( s_Input.section( "\t", 1, 1 ), s_Input.section( "\t", 2, 2 ), s_Input.section( "\t", 3, 3 ) );   // ParameterName(), ParameterUnit(), Parameter()

        gv_PS[j].setStartPos( s_Input.section( "\t", 4, 4 ).toInt() );                                                                  // StartPos()
        gv_PS[j].setDataCount( s_Input.section( "\t", 5, 5 ).toInt() );                                                                 // DataCount()
        gv_PS[j].setType( s_Input.section( "\t", 6, 6 ).toInt() );                                                                      // Type()
        gv_PS[j].setQuality( s_Input.section( "\t", 7, 7 ).toInt() );                                                                   // Quality()

        gv_PS[j].setNumOfPointsNumeric( s_Input.section( "\t", 8, 8 ).toInt() );                                                        // NumOfPointsNumeric()
        gv_PS[j].setNumOfPointsDataText( s_Input.section( "\t", 9, 9 ).toInt() );                                                       // NumOfPointsData()

        gv_PS[j].setXMinorTicksOptions( s_Input.section( "\t", 10, 10 ).toInt(), b_drawMinorXTickmarksLeftOutside, b_drawMinorXTickmarksLeftInside, b_drawMinorXTickmarksRightOutside, b_drawMinorXTickmarksRightInside, gb_drawMinorXTicklines );
        gv_PS[j].setYMinorTicksOptions( s_Input.section( "\t", 11, 11 ).toInt(), b_drawMinorYTickmarksTopOutside, b_drawMinorYTickmarksTopInside, b_drawMinorYTickmarksBottomOutside, b_drawMinorYTickmarksBottomInside, gb_drawMinorYTicklines );

        // Diagram background options
        gv_PS[j].setDiagramBackgroundOptions( (bool) s_Input.section( "\t", 12, 12 ).toInt(), setColor( s_Input.section( "\t", 13, 13 ) ) );  // drawDiagramBackground(), DiagramBackgroundColor()

        // Marker options
        gv_PS[j].setMarkerOptions( (bool) s_Input.section( "\t", 14, 14 ).toInt(), s_Input.section( "\t", 15, 15 ).toInt(), setColor( s_Input.section( "\t", 16, 16 ) ) ); // drawMarker(), MarkerSize(), MarkerColor()

        // Data text options
        gv_PS[j].setDataTextOptions( (bool) s_Input.section( "\t", 17, 17 ).toInt(), setFont( s_Input.section( "\t", 18, 18 ) ), setColor( s_Input.section( "\t", 19, 19 ) ) ); // drawDataText(), DataTextFont(), DataTextColor

        // Line options
        gv_PS[j].setLineOptions( (bool) s_Input.section( "\t", 20, 20 ).toInt(), s_Input.section( "\t", 21, 21 ).toInt(), setColor( s_Input.section( "\t", 22, 22 ) ) ); // drawLine(), LineWidth(), LineColor()

        // Colorized options
        gv_PS[j].setColorizedOptions( (bool) s_Input.section( "\t", 23, 23 ).toInt(), s_Input.section( "\t", 24, 24 ).toInt(), setColor( s_Input.section( "\t", 25, 25 ) ) ); // drawColorized(), Pattern(), ColorizedColor()

        // Y reverse graph range
        gv_PS[j].setYReverseGraphRange( (bool) s_Input.section( "\t", 26, 26 ).toInt() ); // YReverseGraphRange()

        // X refline options
        gv_PS[j].setXReflineOptions( (bool) s_Input.section( "\t", 27, 27 ).toInt(), s_Input.section( "\t", 28, 28 ).toDouble() ); // drawXRefline(), XRefline()

        // Y refline options
        gv_PS[j].setYReflineOptions( (bool) s_Input.section( "\t", 29, 29 ).toInt(), s_Input.section( "\t", 30, 30 ).toDouble() ); // drawYRefline(), YRefline()

        // X minimum, X maximum
        gv_PS[j].setXMinMax( s_Input.section( "\t", 31, 31 ).toDouble(), s_Input.section( "\t", 32, 32 ).toDouble() ); // XMinimum(), XMaximum()

        // X nfrac, X tickmark spacing, X graph min, X graph max
        gv_PS[j].setXNiceLabel( s_Input.section( "\t", 33, 33 ).toInt(), s_Input.section( "\t", 34, 34 ).toDouble(), s_Input.section( "\t", 35, 35 ).toDouble(), s_Input.section( "\t", 36, 36 ).toDouble(), s_Input.section( "\t", 37, 37 ).toDouble() ); // XnFrac(), XTickmarkSpacing(), XGraphMin(), XGraphMax(), XGraphRange()

        // Y minimum, Y maximum
        gv_PS[j].setYMinMax( s_Input.section( "\t", 38, 38 ).toDouble(), s_Input.section( "\t", 39, 39 ).toDouble() ); // YMinimum(), YMaximum()

        // Y nfrac, Y tickmark spacing, Y graph min, Y graph max
        gv_PS[j].setYNiceLabel( s_Input.section( "\t", 40, 40 ).toInt(), s_Input.section( "\t", 41, 41 ).toDouble(), s_Input.section( "\t", 42, 42 ).toDouble(), s_Input.section( "\t", 43, 43 ).toDouble(), s_Input.section( "\t", 44, 44 ).toDouble() ); // YnFrac(), YTickmarkSpacing(), YGraphMin(), YGraphMax(), YGraphRange()

        // Median
        gv_PS[j].setMedian( s_Input.section( "\t", 45, 45 ).toDouble() ); // Median()

        // Mean
        gv_PS[j].setMean( s_Input.section( "\t", 46, 46 ).toDouble() ); // Mean()

        // Standard deviation
        gv_PS[j].setStandardDeviation( s_Input.section( "\t", 47, 47 ).toDouble() ); // StandardDeviation()

        // isGeocode
        gv_PS[j].setGeocode( (bool) s_Input.section( "\t", 48, 48 ).toInt() ); // isGeocode

        // X tick options
        gv_PS[j].setXTicksOptions( gi_TickmarkLength, b_drawMajorXTickmarksLeftOutside, b_drawMajorXTickmarksLeftInside, b_drawMajorXTickmarksRightOutside, b_drawMajorXTickmarksRightInside, gb_drawMajorXTicklines, gb_drawXTickmarkLabels );

        // Y tick options
        gv_PS[j].setYTicksOptions( gi_TickmarkLength, b_drawMajorYTickmarksTopOutside, b_drawMajorYTickmarksTopInside, b_drawMajorYTickmarksBottomOutside, b_drawMajorYTickmarksBottomInside, gb_drawMajorYTicklines, gb_drawYTickmarkLabels );
    }

    i += 2;
    for ( int j=0; j<i_NumOfDataItems; j++ )
    {
        QString s_Input = sl_Input.at( ++i );

        // Column(), Row(), Text(), Value(), QualityFlag(), Status()
        gv_Data.append( DataItem( s_Input.section( "\t", 0, 0 ).toInt(), s_Input.section( "\t", 1, 1 ).toInt(), s_Input.section( "\t", 2, 2 ), s_Input.section( "\t", 3, 3 ).toDouble(), s_Input.section( "\t", 4, 4 ).toInt(), s_Input.section( "\t", 5, 5 ).toInt() ) );
    }

    return( NOERROR );
}

