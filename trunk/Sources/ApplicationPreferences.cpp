/****************************************************************
**
** Preferences
** 2008-12-01, Dr. Rainer Sieger
** last change: 2011-01-03
**
****************************************************************/

#include "Application.h"

/*! @brief Sichern der Programmeinstellungen */

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2012-07-03

void MainWindow::savePreferences()
{
    #if defined(Q_OS_LINUX)
        QSettings settings( getPreferenceFilename(), QSettings::IniFormat );
    #endif

    #if defined(Q_OS_MAC)
        QSettings settings( getPreferenceFilename(), QSettings::NativeFormat );
    #endif

    #if defined(Q_OS_WIN)
        QSettings settings( getPreferenceFilename(), QSettings::IniFormat );
    #endif

    settings.beginGroup( QCoreApplication::applicationName() );

    settings.beginGroup( "GeneralSettings" );
    settings.setValue( "NumOfProgramStarts", gi_NumOfProgramStarts );
    settings.setValue( "WindowX", x() );
    settings.setValue( "WindowY", y() );
    settings.setValue( "WindowHeight", height() );
    settings.setValue( "WindowWidth", width() );

    settings.setValue( "DialogX", posDialog.x() );
    settings.setValue( "DialogY", posDialog.y() );
    settings.setValue( "DialogHeight", sizeParameterDialog.height() );
    settings.setValue( "DialogWidth", sizeParameterDialog.width() );

    settings.setValue( "Path", gs_Path );
    settings.setValue( "FilenameFormat", gs_FilenameFormat );
    settings.setValue( "Codec", gi_Codec );
    settings.endGroup();

    settings.beginGroup( "GlobalSettings" );
    settings.setValue( "ParameterOrientation", gi_ParameterOrientation );
    settings.setValue( "PlotOrientation", gi_PlotOrientation );
    settings.setValue( "XReverseGraphRange", gb_XReverseGraphRange );
    settings.setValue( "YReverseGraphRange", gb_YReverseGraphRange );
    settings.setValue( "Antialiasing", gb_Antialiasing );
    settings.setValue( "drawBackground", gb_drawBackground );
    settings.setValue( "marginLeft", gi_marginLeft );
    settings.setValue( "marginRight", gi_marginRight );
    settings.setValue( "marginTop", gi_marginTop );
    settings.setValue( "marginBottom", gi_marginBottom );
    settings.setValue( "marginScale", gi_marginScale );
    settings.setValue( "fixedDiagramSize", gb_fixedDiagramSize );
    settings.setValue( "diagramWidth", gi_diagramWidth );
    settings.setValue( "diagramHeight", gi_diagramHeight );
    settings.setValue( "diagramDistance", gi_diagramDistance );
    settings.setValue( "diagramFrameWidth", gi_diagramFrameWidth );
    settings.setValue( "DateTimeFormat", gi_DateTimeFormat );
    settings.setValue( "TicklineWidth", gi_TicklineWidth );
    settings.setValue( "TickmarkLength", gi_TickmarkLength );
    settings.setValue( "TickmarkWidth", gi_TickmarkWidth );
    settings.setValue( "MinorTickmarkWidth", gi_MinorTickmarkWidth );
    settings.setValue( "MinorTicklineWidth", gi_MinorTicklineWidth );
    settings.setValue( "numMinorXTicks", gi_numMinorXTicks );
    settings.setValue( "numMinorYTicks", gi_numMinorYTicks );
    settings.setValue( "drawMajorXTicklines", gb_drawMajorXTicklines );
    settings.setValue( "drawMajorXTicksLeft", gb_drawMajorXTicksLeft );
    settings.setValue( "drawMajorXTicksRight", gb_drawMajorXTicksRight );
    settings.setValue( "drawMajorXTicksInside", gb_drawMajorXTicksInside );
    settings.setValue( "drawMajorXTicksOutside", gb_drawMajorXTicksOutside );
    settings.setValue( "drawMajorYTicklines", gb_drawMajorYTicklines );
    settings.setValue( "drawMajorYTicksTop", gb_drawMajorYTicksTop );
    settings.setValue( "drawMajorYTicksBottom", gb_drawMajorYTicksBottom );
    settings.setValue( "drawMajorYTicksInside", gb_drawMajorYTicksInside );
    settings.setValue( "drawMajorYTicksOutside", gb_drawMajorYTicksOutside );
    settings.setValue( "drawMinorXTicklines", gb_drawMinorXTicklines );
    settings.setValue( "drawMinorXTicksLeft", gb_drawMinorXTicksLeft );
    settings.setValue( "drawMinorXTicksRight", gb_drawMinorXTicksRight );
    settings.setValue( "drawMinorXTicksInside", gb_drawMinorXTicksInside );
    settings.setValue( "drawMinorXTicksOutside", gb_drawMinorXTicksOutside );
    settings.setValue( "drawMinorYTicklines", gb_drawMinorYTicklines );
    settings.setValue( "drawMinorYTicksTop", gb_drawMinorYTicksTop );
    settings.setValue( "drawMinorYTicksBottom", gb_drawMinorYTicksBottom );
    settings.setValue( "drawMinorYTicksInside", gb_drawMinorYTicksInside );
    settings.setValue( "drawMinorYTicksOutside", gb_drawMinorYTicksOutside );
    settings.setValue( "drawYTickmarkLabels", gb_drawXTickmarkLabels );
    settings.setValue( "drawYTickmarkLabels", gb_drawYTickmarkLabels );
    settings.setValue( "drawXRefline", gb_drawXRefline );
    settings.setValue( "drawYRefline", gb_drawYRefline );
    settings.setValue( "drawMarkers", gb_drawMarkers );
    settings.setValue( "drawLines", gb_drawLines );
    settings.setValue( "drawColorized", gb_drawColorized );
    settings.setValue( "drawDataText", gb_drawDataText );
    settings.setValue( "drawDiagramBackground", gb_drawDiagramBackground );
    settings.setValue( "MarkerSize", gi_MarkerSize );
    settings.setValue( "LineWidth", gi_LineWidth );
    settings.setValue( "ColorizedPattern", gi_ColorizedPattern );
    settings.setValue( "MarkerColor", ColorStr( gc_MarkerColor ) );
    settings.setValue( "LineColor", ColorStr( gc_LineColor ) );
    settings.setValue( "ColorizedGreaterRefColor", ColorStr( gc_ColorizedGreaterRefColor ) );
    settings.setValue( "ColorizedLessRefColor", ColorStr( gc_ColorizedLessRefColor ) );
    settings.setValue( "DiagramBackgroundColor", ColorStr( gc_DiagramBackgroundColor ) );
    settings.setValue( "DataTextColor", ColorStr( gc_DataTextColor ) );
    settings.setValue( "DiagramFrameColor", ColorStr( gc_DiagramFrameColor ) );
    settings.setValue( "BackgroundColor", ColorStr( gc_BackgroundColor ) );
    settings.setValue( "HeaderTextColor", ColorStr( gc_HeaderTextColor ) );
    settings.setValue( "TickmarkColor", ColorStr( gc_TickmarkColor ) );
    settings.setValue( "TicklineColor", ColorStr( gc_TicklineColor ) );
    settings.setValue( "MinorTicklineColor", ColorStr( gc_MinorTicklineColor ) );
    settings.setValue( "DataTextFont", FontStr( gf_DataTextFont ) );
    settings.setValue( "HeaderTextFont", FontStr( gf_HeaderTextFont ) );
    settings.endGroup();
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2012-07-03

/*! @brief Laden der Programmeinstellungen */

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::loadPreferences()
{
    #if defined(Q_OS_LINUX)
        gi_Codec                = _UTF8_; // UTF-8
    #endif

    #if defined(Q_OS_MAC)
        gi_Codec                = _APPLEROMAN_; // Mac Roman
    #endif

    #if defined(Q_OS_WIN)
        gi_Codec                = _LATIN1_; // Latin-1 = ISO 8859-1
    #endif

    #if defined(Q_OS_LINUX)
        QSettings settings( getPreferenceFilename(), QSettings::IniFormat );
    #endif

    #if defined(Q_OS_MAC)
        QSettings settings( getPreferenceFilename(), QSettings::NativeFormat );
    #endif

    #if defined(Q_OS_WIN)
        QSettings settings( getPreferenceFilename(), QSettings::IniFormat );
    #endif

    settings.beginGroup( QCoreApplication::applicationName() );

    settings.beginGroup( "GeneralSettings" );
    posWindow.setX( settings.value( "WindowX", 100 ).toInt() );
    posWindow.setY( settings.value( "WindowY", 100 ).toInt() );
    sizeWindow.setHeight( settings.value( "WindowHeight", 1000 ).toInt() );
    sizeWindow.setWidth( settings.value( "WindowWidth", 1200 ).toInt() );

    posDialog.setX( settings.value( "DialogX", 110 ).toInt() );
    posDialog.setY( settings.value( "DialogY", 110 ).toInt() );
    sizeParameterDialog.setHeight( settings.value( "DialogHeight", 100 ).toInt() );
    sizeParameterDialog.setWidth( settings.value( "DialogWidth", 100 ).toInt() );

    gs_Path                 = settings.value( "Path", getDocumentDir() ).toString();
    gs_FilenameFormat       = settings.value( "FilenameFormat", "zz%a_%N.txt" ).toString();
    gi_Codec                = settings.value( "Codec", gi_Codec ).toInt();
    gi_Extension            = settings.value( "Extension", _TXT_ ).toInt();
    gi_NumOfProgramStarts   = settings.value( "NumOfProgramStarts", 0 ).toInt();
    settings.endGroup();

    settings.beginGroup( "GlobalSettings" );
    gi_ParameterOrientation     = settings.value( "ParameterOrientation", 0 ).toInt();
    gi_PlotOrientation          = settings.value( "PlotOrientation", _SHOWPLOTV_ ).toInt();
    gb_XReverseGraphRange       = settings.value( "XReverseGraphRange", true ).toBool();
    gb_YReverseGraphRange       = settings.value( "YReverseGraphRange", false ).toBool();
    gb_Antialiasing             = settings.value( "Antialiasing", false ).toBool();
    gb_drawBackground           = settings.value( "drawBackground", false ).toBool();
    gi_marginLeft               = settings.value( "marginLeft", 10 ).toInt();
    gi_marginRight              = settings.value( "marginRight", 20 ).toInt();
    gi_marginTop                = settings.value( "marginTop", 10 ).toInt();
    gi_marginBottom             = settings.value( "marginBottom", 15 ).toInt();
    gi_marginScale              = settings.value( "marginScale", 3 ).toInt();
    gb_fixedDiagramSize         = settings.value( "fixedDiagramSize", false ).toBool();
    gi_diagramWidth             = settings.value( "diagramWidth", 50 ).toInt();
    gi_diagramHeight            = settings.value( "diagramHeight", 500 ).toInt();
    gi_diagramDistance          = settings.value( "diagramDistance", 10 ).toInt();
    gi_diagramFrameWidth        = settings.value( "diagramFrameWidth", 1 ).toInt();
    gi_DateTimeFormat           = settings.value( "DateTimeFormat", _FORMATISODATETIME_ ).toInt();

    gi_TicklineWidth            = settings.value( "TicklineWidth", 1 ).toInt();
    gi_TickmarkLength           = settings.value( "TickmarkLength", 6 ).toInt();
    gi_TickmarkWidth            = settings.value( "TickmarkWidth", 1 ).toInt();
    gi_MinorTickmarkWidth       = settings.value( "MinorTickmarkWidth", 1 ).toInt();
    gi_MinorTicklineWidth       = settings.value( "MinorTicklineWidth", 1 ).toInt();
    gi_numMinorXTicks           = settings.value( "numMinorXTicks", 3 ).toInt();
    gi_numMinorYTicks           = settings.value( "numMinorYTicks", 3 ).toInt();

    gb_drawMajorXTicklines      = settings.value( "drawMajorXTicklines", true ).toBool();
    gb_drawMajorXTicksLeft      = settings.value( "drawMajorXTicksLeft", true ).toBool();
    gb_drawMajorXTicksRight     = settings.value( "drawMajorXTicksRight", false ).toBool();
    gb_drawMajorXTicksInside    = settings.value( "drawMajorXTicksInside", false ).toBool();
    gb_drawMajorXTicksOutside   = settings.value( "drawMajorXTicksOutside", true ).toBool();
    gb_drawMajorYTicklines      = settings.value( "drawMajorYTicklines", true ).toBool();
    gb_drawMajorYTicksTop       = settings.value( "drawMajorYTicksTop", true ).toBool();
    gb_drawMajorYTicksBottom    = settings.value( "drawMajorYTicksBottom", false ).toBool();
    gb_drawMajorYTicksInside    = settings.value( "drawMajorYTicksInside", false ).toBool();
    gb_drawMajorYTicksOutside   = settings.value( "drawMajorYTicksOutside", true ).toBool();
    gb_drawMinorXTicklines      = settings.value( "drawMinorXTicklines", true ).toBool();
    gb_drawMinorXTicksLeft      = settings.value( "drawMinorXTicksLeft", true ).toBool();
    gb_drawMinorXTicksRight     = settings.value( "drawMinorXTicksRight", false ).toBool();
    gb_drawMinorXTicksInside    = settings.value( "drawMinorXTicksInside", false ).toBool();
    gb_drawMinorXTicksOutside   = settings.value( "drawMinorXTicksOutside", true ).toBool();
    gb_drawMinorYTicklines      = settings.value( "drawMinorYTicklines", false ).toBool();
    gb_drawMinorYTicksTop       = settings.value( "drawMinorYTicksTop", true ).toBool();
    gb_drawMinorYTicksBottom    = settings.value( "drawMinorYTicksBottom", false ).toBool();
    gb_drawMinorYTicksInside    = settings.value( "drawMinorYTicksInside", false ).toBool();
    gb_drawMinorYTicksOutside   = settings.value( "drawMinorYTicksOutside", true ).toBool();
    gb_drawXTickmarkLabels      = settings.value( "drawYTickmarkLabels", true ).toBool();
    gb_drawYTickmarkLabels      = settings.value( "drawYTickmarkLabels", true ).toBool();
    gb_drawXRefline             = settings.value( "drawXRefline", false ).toBool();
    gb_drawYRefline             = settings.value( "drawYRefline", false ).toBool();
    gb_drawMarkers              = settings.value( "drawMarkers", false ).toBool();
    gb_drawLines                = settings.value( "drawLines", true ).toBool();
    gb_drawColorized            = settings.value( "drawColorized", false ).toBool();
    gb_drawDataText             = settings.value( "drawDataText", true ).toBool();
    gb_drawDiagramBackground    = settings.value( "drawDiagramBackground", true ).toBool();
    gi_MarkerSize               = settings.value( "MarkerSize", 3 ).toInt();
    gi_LineWidth                = settings.value( "LineWidth", 1 ).toInt();
    gi_ColorizedPattern         = settings.value( "ColorizedPattern", 1 ).toInt();
    gc_MarkerColor              = setColor( settings.value( "MarkerColor", ColorStr( Qt::black ) ).toString() );
    gc_LineColor                = setColor( settings.value( "LineColor", ColorStr( Qt::black ) ).toString() );
    gc_ColorizedGreaterRefColor = setColor( settings.value( "ColorizedGreaterRefColor", ColorStr( Qt::red ) ).toString() );
    gc_ColorizedLessRefColor    = setColor( settings.value( "ColorizedLessRefColor", ColorStr( Qt::blue ) ).toString() );
    gc_DiagramBackgroundColor   = setColor( settings.value( "DiagramBackgroundColor", "232-232-232" ).toString() );
    gc_DataTextColor            = setColor( settings.value( "DataTextColor", ColorStr( Qt::red ) ).toString() );
    gc_DiagramFrameColor        = setColor( settings.value( "DiagramFrameColor", ColorStr( Qt::black ) ).toString() );
    gc_BackgroundColor          = setColor( settings.value( "BackgroundColor", "240-240-240" ).toString() );
    gc_HeaderTextColor          = setColor( settings.value( "HeaderTextColor", ColorStr( Qt::black ) ).toString() );
    gc_TickmarkColor            = setColor( settings.value( "TickmarkColor", ColorStr( Qt::black ) ).toString() );
    gc_TicklineColor            = setColor( settings.value( "TicklineColor", ColorStr( Qt::gray ) ).toString() );
    gc_MinorTicklineColor       = setColor( settings.value( "MinorTicklineColor", ColorStr( Qt::gray ) ).toString() );
    gf_DataTextFont             = setFont( settings.value( "DataTextFont", FontStr( QFont( "Lucdia Grande", 12, 0, false ) ) ).toString() );
    gf_HeaderTextFont           = setFont( settings.value( "HeaderTextFont", FontStr( QFont( "Lucdia Grande", 16, 0, false ) ) ).toString() );
    settings.endGroup();
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

/*! @brief Ermitteln des Dateinamens fuer die Programmeinstellungen.
*   @return Name der Datei fuer die Programmeinstellungen. Dateiname ist gleich "_ERROR_",
*   wenn Betriebssystem ungleich Windows, Mac OS oder Unix ist.
*/

QString MainWindow::getPreferenceFilename()
{
    QString s_PrefFilename = "";

    #if defined(Q_OS_LINUX)
        s_PrefFilename = QDir::homePath() + QLatin1String( "/.config/" ) + QCoreApplication::organizationName() + "/" + QCoreApplication::applicationName() + "/" + QCoreApplication::applicationName() + QLatin1String( ".conf" );
    #endif

    #if defined(Q_OS_MAC)
        s_PrefFilename = QDir::homePath() + QLatin1String( "/Library/Preferences/" ) + QCoreApplication::organizationDomain().section( ".", 1, 1 ) + "." + QCoreApplication::organizationDomain().section( ".", 0, 0 ) + "." + QCoreApplication::applicationName() + QLatin1String( ".plist" );
    #endif

    #if defined(Q_OS_WIN)
        if ( QCoreApplication::applicationName().toLower().endsWith( "portable" ) )
        {
            s_PrefFilename = QCoreApplication::applicationDirPath() + "/" + QCoreApplication::applicationName() + QLatin1String( ".ini" );
        }
        else
        {
            QSettings cfg( QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName() );
            s_PrefFilename = QFileInfo( cfg.fileName() ).absolutePath() + "/" + QCoreApplication::applicationName() + "/" + QCoreApplication::applicationName() + QLatin1String( ".ini" );
        }
    #endif

    return( s_PrefFilename );
}
