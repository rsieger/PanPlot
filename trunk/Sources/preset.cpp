/* preset.cpp                 */
/* 2014-06-07                 */
/* Dr. Rainer Sieger          */

#include "Application.h"


// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// vertical, reverse geocode range

void MainWindow::doPresetVR()
{
    gi_ParameterOrientation = 0;
    gi_PlotOrientation      = _SHOWPLOTV_;
    gb_XReverseGraphRange   = true;
    gb_YReverseGraphRange   = false;

    setUpdateGlobalParameterOptions( true );
    doShowPlot();
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// vertical

void MainWindow::doPresetVN()
{
    gi_ParameterOrientation = 0;
    gi_PlotOrientation      = _SHOWPLOTV_;
    gb_XReverseGraphRange   = false;
    gb_YReverseGraphRange   = false;

    setUpdateGlobalParameterOptions( true );
    doShowPlot();
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// horizontal, reverse geocode range

void MainWindow::doPresetHR()
{
    gi_ParameterOrientation = 90;
    gi_PlotOrientation      = _SHOWPLOTH_;
    gb_XReverseGraphRange   = true;
    gb_YReverseGraphRange   = false;

    setUpdateGlobalParameterOptions( true );
    doShowPlot();
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// horizontal

void MainWindow::doPresetHN()
{
    gi_ParameterOrientation = 90;
    gi_PlotOrientation      = _SHOWPLOTH_;
    gb_XReverseGraphRange   = false;
    gb_YReverseGraphRange   = false;

    setUpdateGlobalParameterOptions( true );
    doShowPlot();
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// marker color

void MainWindow::doPresetCM()
{
    gb_drawMarkers = true;

    for ( int i=0; i<gv_PS.count(); i++ )
        gv_PS[i].setMarkerOptions( true, gv_PS.at( i ).MarkerSize(), QColor( rangedRand( 0, 255 ), rangedRand( 0, 255 ), rangedRand( 0, 255 ) ) );

    setUpdateGlobalParameterOptions( false );
    doShowPlot();
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// line color

void MainWindow::doPresetCL()
{
    gb_drawLines = true;

    for ( int i=0; i<gv_PS.count(); i++ )
        gv_PS[i].setLineOptions( true, gv_PS.at( i ).LineWidth(), QColor( rangedRand( 0, 255 ), rangedRand( 0, 255 ), rangedRand( 0, 255 ) ) );

    setUpdateGlobalParameterOptions( false );
    doShowPlot();
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// colorize color

void MainWindow::doPresetCC()
{
    gb_drawColorized = true;

    for ( int i=0; i<gv_PS.count(); i++ )
        gv_PS[i].setColorizedOptions( true, gv_PS.at( i ).Pattern(), QColor( rangedRand( 0, 255 ), rangedRand( 0, 255 ), rangedRand( 0, 255 ) ), QColor( rangedRand( 0, 255 ), rangedRand( 0, 255 ), rangedRand( 0, 255 ) ) );

    setUpdateGlobalParameterOptions( false );
    doShowPlot();
}
