/* PlotSettings.cpp   */
/* 2009-12-03         */
/* Dr. Rainer Sieger  */

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2009-12-31

PlotSettings::PlotSettings( const bool b_allSettings, const int i_ParameterID, const int i_Count, const QString &s_Header )
{
    setID( i_ParameterID );

    if ( b_allSettings == false )
        return;

    setType();
    setQuality();
    setGeocode( false );
    setDataCount( i_Count-1 );
    setStartPos( ID() * DataCount() );

    setMedian( -999. );
    setMean( -999. );
    setStandardDeviation( -999. );

    setXMinMax( -9999., 9999. );
    setYMinMax( -9999., 9999. );

    setXGraphMinMax( 0., 0. );
    setYGraphMinMax( 0., 0. );

    setXGraphRange( -9999. );
    setYGraphRange( -9999. );

    setXTicksOptions();
    setYTicksOptions();

    setXMinorTicksOptions();
    setYMinorTicksOptions();

    setXNiceLabel( 0, 0., 0., 0. );
    setYNiceLabel( 0, 0., 0., 0. );

    setXReflineOptions( false );
    setYReflineOptions( false );

    setXReverseGraphRange( true );
    setYReverseGraphRange( false );

    setColorizedOptions( false );
    setLineOptions( true );
    setMarkerOptions( false );
    setDataTextOptions( false );

    setDiagramBackgroundOptions( false );

// **********************************************************************************************

    setParameterNameUnit( s_Header.section( "\t", i_ParameterID, i_ParameterID ) );

    if ( isGeocode( Parameter() ) == true )
        setGeocode( true );

    if ( ( ParameterName().toLower().startsWith( "date/time" ) == true ) || ( ParameterName().toLower() == "date" ) || ( ParameterName() == "1599" ) )
        setType( isDateTime );

    if ( ( ParameterName().startsWith( "origin of values", Qt::CaseInsensitive ) == true ) || ( ParameterName().startsWith( "doi", Qt::CaseInsensitive ) == true ) )
        setType( isDOI );

    if ( ParameterName().startsWith( "url", Qt::CaseInsensitive ) == true )
        setType( isURL );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-01-23

void PlotSettings::setParameterNameUnit( const QString &s_ParameterName, const QString &s_ParameterUnit )
{
    name        = s_ParameterName;
    unit        = s_ParameterUnit;

    if ( s_ParameterUnit.startsWith( "[" ) == true )
        parameter = s_ParameterName + " " + s_ParameterUnit;
    else
        parameter = s_ParameterName + " [" + s_ParameterUnit + "]";
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-01-05

void PlotSettings::setParameterNameUnit( const QString &s_Header )
{
    parameter = s_Header.simplified();

    parameter.replace( "\"", "" );

    if ( parameter.endsWith( "]" ) == true ) // parameter [unit]
    {
        name = parameter.section( " [", 0, 0 );
        unit = parameter.section( " [", 1, 1 ).section( "]", 0, 0 );
    }

    if ( parameter.endsWith( ")" ) == true ) // parameter [unit] (comment) or parameter (unit)
    {
        if ( parameter.contains( "] (") == true )
        {
            name    = parameter.section( " [", 0, 0 );
            unit    = parameter.section( " [", 1, 1 ).section( "]", 0, 0 );
            comment = parameter.section( "] (", 1, 1 );
        }
        else
        {
            name = parameter.section( " (", 0, 0 );
            unit = parameter.section( " (", 1, 1 ).section( ")", 0, 0 );
        }
    }

    if ( parameter == "Origin of Values" ) // datawarehouse header
    {
        name = "Origin of Values";
        unit = "doi:10.1594/PANGAEA.";
    }

    if ( unit.isEmpty() == true )
    {
        name = parameter;
    }
    else
    {
        unit      = "[" + unit + "]";
        parameter = name + " " + unit;
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2009-12-04

bool PlotSettings::isGeocode( const QString &s_ParameterName )
{
    if ( s_ParameterName.startsWith( "date/time", Qt::CaseInsensitive ) == true )
        return( true );

    if ( s_ParameterName.startsWith( "depth [m]", Qt::CaseInsensitive ) == true )
        return( true );

    if ( s_ParameterName.startsWith( "depth, sediment [m]", Qt::CaseInsensitive ) == true )
        return( true );

    if ( s_ParameterName.startsWith( "depth, sediment/rock [m]", Qt::CaseInsensitive ) == true )
        return( true );

    if ( s_ParameterName.startsWith( "depth, water [m]", Qt::CaseInsensitive ) == true )
        return( true );

    if ( s_ParameterName.startsWith( "depth water [m]", Qt::CaseInsensitive ) == true )
        return( true );

    if ( s_ParameterName.startsWith( "depth, ice/snow [m]", Qt::CaseInsensitive ) == true )
        return( true );

    if ( s_ParameterName.startsWith( "depth ice/snow [m]", Qt::CaseInsensitive ) == true )
        return( true );

    if ( s_ParameterName.startsWith( "age [ka bp]", Qt::CaseInsensitive ) == true )
        return( true );

    if ( s_ParameterName.startsWith( "altitude [m]", Qt::CaseInsensitive ) == true )
        return( true );

    if ( s_ParameterName.startsWith( "height [m]", Qt::CaseInsensitive ) == true )
        return( true );

    if ( s_ParameterName.startsWith( "latitude", Qt::CaseInsensitive ) == true )
        return( true );

    if ( s_ParameterName.startsWith( "longitude", Qt::CaseInsensitive ) == true )
        return( true );

    if ( ( s_ParameterName == "1619" ) || ( s_ParameterName == "1599" ) || ( s_ParameterName == "1" ) )
        return( true );

    return( false );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void PlotSettings::setXTicksOptions( const int XTickmarkLength, const bool drawXTickmarksLeftOutside, const bool drawXTickmarksLeftInside, const bool drawXTickmarksRightOutside, const bool drawXTickmarksRightInside, const bool drawXTicklines, const bool drawXTickmarkLabels )
{
    xtl    = XTickmarkLength;
    dxtmLO = drawXTickmarksLeftOutside;
    dxtmLI = drawXTickmarksLeftInside;
    dxtmRO = drawXTickmarksRightOutside;
    dxtmRI = drawXTickmarksRightInside;
    dxtl   = drawXTicklines;
    dxtml  = drawXTickmarkLabels;
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void PlotSettings::setXMinorTicksOptions( const int NumOfXMinorTicks, const bool drawXMinorTickmarksLeftOutside, const bool drawXMinorTickmarksLeftInside, const bool drawXMinorTickmarksRightOutside, const bool drawXMinorTickmarksRightInside, const bool drawXMinorTicklines )
{
    xmt     = NumOfXMinorTicks+1;
    dxmtmLO = drawXMinorTickmarksLeftOutside;
    dxmtmLI = drawXMinorTickmarksLeftInside;
    dxmtmRO = drawXMinorTickmarksRightOutside;
    dxmtmRI = drawXMinorTickmarksRightInside;
    dxmtl   = drawXMinorTicklines;
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void PlotSettings::setYTicksOptions( const int YTickmarkLength, const bool drawYTickmarksTopOutside, const bool drawYTickmarksTopInside, const bool drawYTickmarksBottomOutside, const bool drawYTickmarksBottomInside, const bool drawYTicklines, const bool drawYTickmarkLabels )
{
    ytl    = YTickmarkLength;
    dytmTO = drawYTickmarksTopOutside;
    dytmTI = drawYTickmarksTopInside;
    dytmBO = drawYTickmarksBottomOutside;
    dytmBI = drawYTickmarksBottomInside;
    dytl   = drawYTicklines;
    dytml  = drawYTickmarkLabels;
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void PlotSettings::setYMinorTicksOptions( const int NumOfYMinorTicks, const bool drawYMinorTickmarksTopOutside, const bool drawYMinorTickmarksTopInside, const bool drawYMinorTickmarksBottomOutside, const bool drawYMinorTickmarksBottomInside, const bool drawYMinorTicklines )
{
    ymt     = NumOfYMinorTicks+1;
    dymtmTO = drawYMinorTickmarksTopOutside;
    dymtmTI = drawYMinorTickmarksTopInside;
    dymtmBO = drawYMinorTickmarksBottomOutside;
    dymtmBI = drawYMinorTickmarksBottomInside;
    dymtl   = drawYMinorTicklines;
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void PlotSettings::setDataTextOptions( const bool var1, const QFont var2, const QColor var3 )
{
    drawdatatext      = var1;
    datatextfont      = var2;
    datatextcolor     = var3;
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void PlotSettings::setMarkerOptions( const bool var1, const int var2, const QColor var3 )
{
    drawmarker  = var1;
    markersize  = var2;
    markercolor = var3;
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void PlotSettings::setLineOptions( const bool var1, const int var2, const QColor var3 )
{
    drawline  = var1;
    linewidth = var2;
    linecolor = var3;
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void PlotSettings::setColorizedOptions( const bool var1, const int var2, const QColor var3, const QColor var4 )
{
    drawcolorized            = var1;
    pattern                  = var2;
    colorizedgreaterrefcolor = var3;
    colorizedlessrefcolor    = var4;
}

