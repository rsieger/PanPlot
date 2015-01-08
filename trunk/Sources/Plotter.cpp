/* PlotArea.cpp               */
/* 2009-12-07                 */
/* Dr. Rainer Sieger          */

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

const int _DIAGRAMMINWIDTH_    = 20;

const int _NORMAL_             = 0;
const int _BOLD_               = 1;

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::paintEvent( QPaintEvent * /* event */ )
{
    switch ( PlotOrientation() )
    {
    case _SHOWPLOTV_:
        plotV();
        break;
    case _SHOWPLOTH_:
        plotH();
        break;
    default:
        break;
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::plotH()
{
    int  j                        = 0;

    int  i_NumOfParameter         = v_PS.count();
    int  i_XAxisParameterID       = v_PP.at( 0 );
    int  i_XAxisParameterType     = v_PS.at( i_XAxisParameterID ).Type();

    int  i_WindowWidth            = window()->width();
    int  i_WindowHeight           = window()->height();

    int  i_DiagramTop             = 0;
    int  i_DiagramHeight          = 0;
    int  i_DiagramHeightTotal     = 0;
    int  i_DiagramWidth           = 0;
    int  i_DiagramDistance        = 0;

    int  i_DiagramLeft            = 0;
    int  i_MinDiagramHeight       = 0;
    int  i_YAxisParameterID       = 0;
    int  i_NumOfVisibleParameters = 0;
    int  i_LastVisibleParameter   = 0;
    int  i_XAxisTextHeight        = 0;
    int  i_MaxYAxisScaleWidth     = 0;
    int  i_YAxisTickmarkLength    = 0;
    int  i_ParameterNameHeight    = 0;
    int  i_MaxParameterWidth      = 0;
    int  i_StartPosNumeric        = 0;
    int  i_StartPosDataText       = 0;

    QPen DiagramPen         = QPen( DiagramFrameColor(), DiagramFrameWidth(), Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
    QPen TickmarkPen        = QPen( TickmarkColor(), TickmarkWidth(), Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
    QPen TicklinePen        = QPen( TicklineColor(), TicklineWidth(), Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
    QPen MinorTickmarkPen   = QPen( MinorTickmarkColor(), MinorTickmarkWidth(), Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
    QPen MinorTicklinePen   = QPen( MinorTicklineColor(), MinorTicklineWidth(), Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );

    QStringList      sl_DataText;

    QVector<QPointF> v_PointsNumeric;
    QVector<QPointF> v_PointsDataText;

// **********************************************************************************************
// get number of visible parameters

    i_NumOfVisibleParameters = getNumberOfVisibleParameter( v_PP );
    i_LastVisibleParameter   = getLastVisibleParameter( v_PP );

    if ( ( i_NumOfVisibleParameters < 1 ) || ( i_LastVisibleParameter < 1 ) )
        return;

// **********************************************************************************************

    i_DiagramHeight   = DiagramHeight();
    i_DiagramWidth    = DiagramWidth();
    i_DiagramDistance = DiagramDistance();

// **********************************************************************************************

    setMinimumSize( 100, 100 );
    setMaximumSize( 16777215, 16777215 );

// **********************************************************************************************

    if ( fixedDiagramSize() == true )
       setFixedWidth( marginLeft + DiagramWidth() + marginRight );

// **********************************************************************************************

    QFileInfo       fi( FilenamePlot() );

    QSvgGenerator   generatorH;
    QPainter        painterH;
    QPrinter        printerH;
    QImage          image( i_WindowWidth, i_WindowHeight, QImage::Format_RGB32 );

// **********************************************************************************************

    switch ( SavePlotFormat() )
    {
    case _FORMATSVG_:
        generatorH.setFileName( FilenamePlot() );
        generatorH.setSize( QSize( i_WindowWidth, i_WindowHeight ) );
        generatorH.setViewBox( QRect( 0, 0, i_WindowWidth, i_WindowHeight ) );
        generatorH.setTitle( fi.completeBaseName() );
        generatorH.setDescription( tr("Plot created by PanPlot (doi:10.1594/PANGAEA.816201)" ) );
        painterH.begin( &generatorH );
        break;
    case _FORMATBMP_:
    case _FORMATPNG_:
        painterH.begin( &image );
        break;
    case _FORMATPDF_:
        if ( i_WindowWidth > i_WindowHeight )
            printerH.setPageOrientation( QPageLayout::Landscape );
        else
            printerH.setPageOrientation( QPageLayout::Portrait );
        printerH.setOutputFileName( FilenamePlot() );
        printerH.setPageMargins( QMarginsF( 0., 0., 0., 0.) );
        painterH.begin( &printerH );
        break;
    case _FORMATPRINT_:
        if ( i_WindowWidth > i_WindowHeight )
            printerH.setPageOrientation( QPageLayout::Landscape );
        else
            printerH.setPageOrientation( QPageLayout::Portrait );
        painterH.begin( &printerH );
        break;
    default:
        painterH.begin( this );
        break;
    }

    transformPainter( painterH );

// **********************************************************************************************
// Init

    i_ParameterNameHeight = getTextHeight( painterH, HeaderTextFont(), PointSizeName(), _BOLD_, tr( "gG" ) );
    i_XAxisTextHeight     = getTextHeight( painterH, HeaderTextFont(), PointSizeName(), _BOLD_, tr( "gG" ) );
    i_MaxYAxisScaleWidth  = calcMaxScaleWidth( painterH, v_PS, v_PP );

    i_YAxisTickmarkLength = v_PS.at( i_XAxisParameterID ).YTickmarkLength();

    switch ( ParameterNameOrientation() )
    {
    case 0:
        i_MaxParameterWidth = getMaxParameterWidth( painterH, false, HeaderTextFont(), PointSizeHeader(), _BOLD_, v_PS, v_PP );
        i_DiagramLeft       = marginLeft + i_MaxParameterWidth + i_MaxYAxisScaleWidth + i_ParameterNameHeight + i_YAxisTickmarkLength;
        break;
    default:
        i_DiagramLeft       = marginLeft + 2*i_ParameterNameHeight + i_MaxYAxisScaleWidth + i_YAxisTickmarkLength;
        break;
    }

// **********************************************************************************************
// set diagram width

    i_DiagramWidth = calcDiagramWidthH( painterH, i_DiagramLeft, marginRight );

// **********************************************************************************************
// set diagram height

    if ( fixedDiagramSize() == true )
    {
        setFixedHeight( marginTop + ( i_NumOfVisibleParameters * ( i_DiagramHeight + i_DiagramDistance ) ) + i_DiagramDistance + 2*i_XAxisTextHeight + marginBottom );
        i_DiagramHeightTotal = marginTop + v_PS.at( i_XAxisParameterID ).XTickmarkLength() + i_XAxisTextHeight + i_NumOfVisibleParameters * ( i_DiagramHeight + i_DiagramDistance );
    }
    else
    {
        if ( ( ResizeState() == true ) || ( SavePlotFormat() != _FORMATNULL_ ) )
        {
            i_DiagramHeight      = calcDiagramHeightH( painterH, marginTop, marginBottom + v_PS.at( i_XAxisParameterID ).XTickmarkLength() + 4*i_XAxisTextHeight, i_DiagramDistance, i_MinDiagramHeight, i_NumOfVisibleParameters ) + StatusBarHeight()/i_NumOfVisibleParameters;
            i_DiagramHeightTotal = calcDiagramHeightH( painterH, marginTop, marginBottom + v_PS.at( i_XAxisParameterID ).XTickmarkLength() + 4*i_XAxisTextHeight, 0, i_MinDiagramHeight, 1 ) + marginTop + v_PS.at( i_XAxisParameterID ).XTickmarkLength() + StatusBarHeight();
        }
        else
        {
            i_DiagramHeight      = calcDiagramHeightH( painterH, marginTop, marginBottom + v_PS.at( i_XAxisParameterID ).XTickmarkLength() + 4*i_XAxisTextHeight, i_DiagramDistance, i_MinDiagramHeight, i_NumOfVisibleParameters );
            i_DiagramHeightTotal = calcDiagramHeightH( painterH, marginTop, marginBottom + v_PS.at( i_XAxisParameterID ).XTickmarkLength() + 4*i_XAxisTextHeight, 0, i_MinDiagramHeight, 1 ) + marginTop + v_PS.at( i_XAxisParameterID ).XTickmarkLength();
        }
    }

// **********************************************************************************************
// draw background

    painterH.fillRect( 0, 0, painterH.window().width(), painterH.window().height(), BackgroundBrush() );

// **********************************************************************************************
// draw X-Axis

    drawXAxis( painterH, v_PS.at( i_XAxisParameterID ), QPoint( i_DiagramLeft, i_DiagramHeightTotal + 3*i_XAxisTextHeight ), i_DiagramWidth, 0 );

// **********************************************************************************************
// calc point coordinates and draw diagrams

    j = 0;

    for ( int i=1; i<i_NumOfParameter; i++ )
    {
        if ( v_PP.at( i ) > -1 )
        {
            i_YAxisParameterID = v_PP.at( i );

            i_DiagramTop = marginTop + ( j++ )*( i_DiagramHeight + i_DiagramDistance ) + v_PS.at( i_XAxisParameterID ).XTickmarkLength();

            switch ( ParameterNameOrientation() )
            {
            case 0:
                setHeaderRect( QRect( i_DiagramLeft-i_MaxParameterWidth-i_MaxYAxisScaleWidth-i_ParameterNameHeight-i_YAxisTickmarkLength, i_DiagramTop, i_MaxParameterWidth, i_ParameterNameHeight ), v_PS[i_YAxisParameterID] );
                break;
            default:
                setHeaderRect( QRect( marginLeft+i_ParameterNameHeight/2, i_DiagramTop+i_DiagramHeight/2+getTextWidth( painterH, HeaderTextFont(), PointSizeScale(), _NORMAL_, " [unit]" )/2, i_MaxParameterWidth, i_ParameterNameHeight ), v_PS[i_YAxisParameterID] );
                break;
            }

            setDiagramRect( QRect( i_DiagramLeft, i_DiagramTop, i_DiagramWidth, i_DiagramHeight ), v_PS[i_YAxisParameterID] );

            if ( ( ResizeState() == false ) || ( fixedDiagramSize() == true ) )
            {
                drawDiagram( painterH, v_PS.at( i_YAxisParameterID ), DiagramPen );
                drawXScaleH( painterH, v_PS.at( i_YAxisParameterID ), i_DiagramDistance, TickmarkPen, TicklinePen, MinorTickmarkPen, MinorTicklinePen, j, i_LastVisibleParameter, i_XAxisParameterType, XReverseGraphRange() ); // X-Axis, Geocode
                drawYScaleH( painterH, v_PS.at( i_YAxisParameterID ), i_DiagramDistance, TickmarkPen, TicklinePen, MinorTickmarkPen, MinorTicklinePen );                                                                        // Y-Axis, Parameter
                drawHeaderH( painterH, v_PS.at( i_YAxisParameterID ) );
                drawDiagramFrame( painterH, v_PS.at( i_YAxisParameterID ), DiagramPen );

                calcPointCoordinatesNumericH( i_XAxisParameterID, i_YAxisParameterID, XReverseGraphRange(), v_PS, v_Data, v_PointsNumeric );
                calcPointCoordinatesTextH( i_XAxisParameterID, i_YAxisParameterID, XReverseGraphRange(), v_PS, v_Data, v_PointsDataText, sl_DataText );
            }
            else
            {
                drawDiagramFrame( painterH, v_PS.at( i_YAxisParameterID ), DiagramPen );
                drawHeaderH( painterH, v_PS.at( i_YAxisParameterID ) );
                drawText( painterH, v_PS.at( i_YAxisParameterID ).DiagramRect(), HeaderTextFont(), HeaderTextColor(), 10, _NORMAL_, Qt::AlignLeft, 0, tr( " processing..." ) );
            }
        }
    }

    drawCopyrightH( painterH, QRect( i_DiagramLeft, i_DiagramTop, i_DiagramWidth+ v_PS.at( i_XAxisParameterID ).YTickmarkLength(), i_DiagramHeight ), "PanPlot (doi:10.1594/PANGAEA.816201)" );

// **********************************************************************************************
//  resize window

    if ( ( ResizeState() == true ) && ( fixedDiagramSize() == false ) && ( SavePlotFormat() == _FORMATNULL_ ) )
    {
        setResizeState( false );

        if ( count++ < 1)
            QTimer::singleShot( 1000, this, SLOT( update() ) );

        if ( count > 10 )
            resetCount();

        return;
    }

    resetCount();

// **********************************************************************************************
// draw data

    painterH.setRenderHint( QPainter::Antialiasing, Antialiasing() );

    j = 0;

    for ( int i=1; i<i_NumOfParameter; i++ )
    {
        if ( v_PP.at( i ) > -1 )
        {
            i_YAxisParameterID = v_PP.at( i );

            i_DiagramTop = marginTop + ( j++ )*( i_DiagramHeight + i_DiagramDistance ) + v_PS.at( i_XAxisParameterID ).XTickmarkLength();
            painterH.setClipRect( QRect( i_DiagramLeft, i_DiagramTop, i_DiagramWidth, i_DiagramHeight ) );

            if ( v_PS.at( i_YAxisParameterID ).drawColorized() == true )
                drawDataColorizedH( painterH, v_PS.at( i_YAxisParameterID ), i_StartPosNumeric, v_PointsNumeric );

            if ( v_PS.at( i_YAxisParameterID ).drawLine() == true )
                drawDataLine( painterH, v_PS.at( i_YAxisParameterID ), i_StartPosNumeric, v_PointsNumeric );

            if ( v_PS.at( i_YAxisParameterID ).drawMarker() == true )
                drawDataMarker( painterH, v_PS.at( i_YAxisParameterID ), i_StartPosNumeric, v_PointsNumeric );

            if ( v_PS.at( i_YAxisParameterID ).drawDataText() == true )
                drawDataText( painterH, v_PS.at( i_YAxisParameterID ), i_StartPosDataText, v_PointsDataText, sl_DataText );

            if ( v_PS.at( i_YAxisParameterID ).drawXRefline() == true )
                drawXReflineH( painterH, v_PS.at( i_YAxisParameterID ), XReverseGraphRange() );

            if ( v_PS.at( i_YAxisParameterID ).drawYRefline() == true )
                drawYReflineH( painterH, v_PS.at( i_YAxisParameterID ) );

            i_StartPosNumeric  += v_PS.at( i_YAxisParameterID ).NumOfPointsNumeric();
            i_StartPosDataText += v_PS.at( i_YAxisParameterID ).NumOfPointsDataText();
        }
    }

    painterH.end();

// **********************************************************************************************
// Save plot to file

    if ( ( SavePlotFormat() == _FORMATPNG_ ) || ( SavePlotFormat() == _FORMATBMP_ ) )
    {
        QImageWriter writer;
        writer.setFileName( FilenamePlot() );

        switch ( SavePlotFormat() )
        {
        case _FORMATPNG_:
            writer.setFormat( "png" );
            break;
        case _FORMATBMP_:
            writer.setFormat( "bmp" );
            break;
        default:
            break;
        }

        writer.write( image );
    }

    setSavePlotFormat( _FORMATNULL_ );

    return;
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::plotV()
{
    int  j                        = 0;

    int  i_NumOfParameter         = v_PS.count();
    int  i_XAxisParameterID       = v_PP.at( 0 );
    int  i_XAxisParameterType     = v_PS.at( i_XAxisParameterID ).Type();

    int  i_WindowWidth            = window()->width();
    int  i_WindowHeight           = window()->height();

    int  i_DiagramTop             = 0;
    int  i_DiagramHeight          = 0;
    int  i_DiagramWidth           = 0;
    int  i_DiagramDistance        = 0;
    int  i_DiagramLeft            = 0;
    int  i_FirstDiagramLeft       = 0;
    int  i_MinDiagramWidth        = 0;

    int  i_YAxisParameterID       = 0;
    int  i_NumOfVisibleParameters = 0;
    int  i_LastVisibleParameter   = 0;
    int  i_XAxisTextHeight        = 0;
    int  i_XAxisScaleWidth        = 0;
    int  i_YAxisTickmarkLength    = 0;
    int  i_ParameterNameHeight    = 0;
    int  i_ParameterUnitHeight    = 0;
    int  i_MaxParameterWidth      = 0;
    int  i_HeaderHeight           = 0;
    int  i_HeaderTop              = 0;
    int  i_StartPosNumeric        = 0;
    int  i_StartPosDataText       = 0;

    QPen DiagramPen         = QPen( DiagramFrameColor(), DiagramFrameWidth(), Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
    QPen TickmarkPen        = QPen( TickmarkColor(), TickmarkWidth(), Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
    QPen TicklinePen        = QPen( TicklineColor(), TicklineWidth(), Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
    QPen MinorTickmarkPen   = QPen( MinorTickmarkColor(), MinorTickmarkWidth(), Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
    QPen MinorTicklinePen   = QPen( MinorTicklineColor(), MinorTicklineWidth(), Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );

    QStringList      sl_DataText;

    QVector<QPointF> v_PointsNumeric;
    QVector<QPointF> v_PointsDataText;

// **********************************************************************************************
// get number of visible parameters

    i_NumOfVisibleParameters = getNumberOfVisibleParameter( v_PP );
    i_LastVisibleParameter   = getLastVisibleParameter( v_PP );

    if ( ( i_NumOfVisibleParameters < 1 ) || ( i_LastVisibleParameter < 1 ) )
        return;

// **********************************************************************************************

    i_DiagramHeight   = DiagramHeight();
    i_DiagramWidth    = DiagramWidth();
    i_DiagramDistance = DiagramDistance();

// **********************************************************************************************

    setMinimumSize( 100, 100 );
    setMaximumSize( 16777215, 16777215 );

// **********************************************************************************************

    QFileInfo       fi( FilenamePlot() );

    QSvgGenerator   generatorV;
    QPainter        painterV;
    QPrinter        printerV;
    QImage          image( i_WindowWidth, i_WindowHeight, QImage::Format_RGB32 );

// **********************************************************************************************

    switch ( SavePlotFormat() )
    {
    case _FORMATSVG_:
        generatorV.setFileName( FilenamePlot() );
        generatorV.setSize( QSize( i_WindowWidth, i_WindowHeight ) );
        generatorV.setViewBox( QRect( 0, 0, i_WindowWidth, i_WindowHeight ) );
        generatorV.setTitle( fi.completeBaseName() );
        generatorV.setDescription( tr("Plot created by PanPlot (doi:10.1594/PANGAEA.816201)" ) );
        painterV.begin( &generatorV );
        break;
    case _FORMATBMP_:
    case _FORMATPNG_:
        painterV.begin( &image );
        break;
    case _FORMATPDF_:
        if ( i_WindowWidth > i_WindowHeight )
            printerV.setPageOrientation( QPageLayout::Landscape );
        else
            printerV.setPageOrientation( QPageLayout::Portrait );
        printerV.setOutputFileName( FilenamePlot() );
        printerV.setPageMargins( QMarginsF( 0., 0., 0., 0.) );
        painterV.begin( &printerV );
        break;
    case _FORMATPRINT_:
        if ( i_WindowWidth > i_WindowHeight )
            printerV.setPageOrientation( QPageLayout::Landscape );
        else
            printerV.setPageOrientation( QPageLayout::Portrait );
        painterV.begin( &printerV );
        break;
    default:
        painterV.begin( this );
        break;
    }

    transformPainter( painterV );

// **********************************************************************************************
// Init

    i_ParameterNameHeight = getTextHeight( painterV, HeaderTextFont(), PointSizeName(), _BOLD_, tr( "gG" ) );
    i_ParameterUnitHeight = getTextHeight( painterV, HeaderTextFont(), PointSizeUnit(), _NORMAL_, tr( "gG" ) );
    i_XAxisTextHeight     = getTextHeight( painterV, HeaderTextFont(), PointSizeName(), _BOLD_, tr( "gG" ) );

    if ( i_XAxisParameterType == isDateTime )
        i_XAxisScaleWidth = getDateTimeWidth( painterV, HeaderTextFont(), PointSizeScale(), _NORMAL_, DateTimeFormat() );
    else
        i_XAxisScaleWidth = getTextWidth( painterV, HeaderTextFont(), PointSizeScale(), _NORMAL_, v_PS.at( i_XAxisParameterID ).XGraphMax(), v_PS.at( i_XAxisParameterID ).XnFrac() );

    i_YAxisTickmarkLength = v_PS.at( i_XAxisParameterID ).YTickmarkLength();

    switch ( ParameterNameOrientation() )
    {
    case 0:
        i_MinDiagramWidth = _DIAGRAMMINWIDTH_;
        i_DiagramTop      = marginTop + i_ParameterNameHeight + 4*i_ParameterUnitHeight + 2*i_YAxisTickmarkLength;
        i_HeaderTop       = marginTop + i_MaxParameterWidth;
        break;
    case 45:
        i_MaxParameterWidth  = getMaxParameterWidth( painterV, true, HeaderTextFont(), PointSizeHeader(), _NORMAL_, v_PS, v_PP );
        i_HeaderHeight       = (int) sqrt( (double) ( i_MaxParameterWidth*i_MaxParameterWidth)/2. ) + _DIAGRAMMINWIDTH_ ;
        i_MinDiagramWidth    = i_ParameterNameHeight + _DIAGRAMMINWIDTH_;
        i_DiagramTop         = marginTop + 2*i_ParameterNameHeight + i_HeaderHeight;
        i_HeaderTop          = i_DiagramTop - 2*i_ParameterNameHeight + 2*i_YAxisTickmarkLength;
        break;
    case 90:
        i_MinDiagramWidth    = i_ParameterNameHeight + _DIAGRAMMINWIDTH_;
        i_MaxParameterWidth  = getMaxParameterWidth( painterV, true, HeaderTextFont(), PointSizeHeader(), _BOLD_, v_PS, v_PP );
        i_DiagramTop         = marginTop + 2*i_ParameterNameHeight + i_MaxParameterWidth + i_YAxisTickmarkLength;
        i_HeaderTop          = i_DiagramTop - i_ParameterNameHeight;
        break;
    default:
        break;
    }

// **********************************************************************************************
// set diagram width

    i_FirstDiagramLeft = marginLeft + 2*i_XAxisTextHeight + i_XAxisScaleWidth + v_PS.at( i_XAxisParameterID ).XTickmarkLength();

    if ( fixedDiagramSize() == true )
       setFixedWidth( ( i_FirstDiagramLeft + i_DiagramWidth ) + ( ( i_NumOfVisibleParameters - 1 ) * ( i_DiagramWidth + i_DiagramDistance ) ) + marginRight );
    else
       i_DiagramWidth = calcDiagramWidthV( painterV, i_FirstDiagramLeft, marginRight, i_DiagramDistance, i_MinDiagramWidth, i_NumOfVisibleParameters ) - v_PS.at( i_XAxisParameterID ).XTickmarkLength();

// **********************************************************************************************
// set diagram height

    if ( fixedDiagramSize() == true )
       setFixedHeight( i_DiagramTop + DiagramHeight() + marginBottom );

    i_DiagramHeight = calcDiagramHeightV( painterV, i_DiagramTop, marginBottom ) - i_YAxisTickmarkLength;

// **********************************************************************************************
// draw background

    painterV.fillRect( 0, 0, painterV.window().width(), painterV.window().height(), BackgroundBrush() );

// **********************************************************************************************
// draw X-Axis

    drawXAxis( painterV, v_PS.at( i_XAxisParameterID ), QPoint( marginLeft, i_DiagramTop + i_DiagramHeight/2 ), 0, 90 );

// **********************************************************************************************
// calc point coordinates and draw diagrams

    j = 0;

    for ( int i=1; i<i_NumOfParameter; i++ )
    {
        if ( v_PP.at( i ) > -1 )
        {
            i_YAxisParameterID = v_PP.at( i );

            i_DiagramLeft = marginLeft + 2*i_XAxisTextHeight + i_XAxisScaleWidth + ( j++ )*( i_DiagramWidth + i_DiagramDistance ) + v_PS.at( i_XAxisParameterID ).XTickmarkLength();

            setHeaderRect( QRect( i_DiagramLeft, i_HeaderTop, i_DiagramWidth, i_ParameterNameHeight ), v_PS[i_YAxisParameterID] );

            if ( ( ResizeState() == false ) || ( fixedDiagramSize() == true ) )
            {
                setDiagramRect( QRect( i_DiagramLeft, i_DiagramTop, i_DiagramWidth, i_DiagramHeight ), v_PS[i_YAxisParameterID] );

                drawDiagram( painterV, v_PS.at( i_YAxisParameterID ), DiagramPen );
                drawXScaleV( painterV, v_PS.at( i_YAxisParameterID ), i_DiagramDistance, TickmarkPen, TicklinePen, MinorTickmarkPen, MinorTicklinePen, j, i_LastVisibleParameter, i_XAxisParameterType, XReverseGraphRange() ); // X-Axis, Geocode
                drawYScaleV( painterV, v_PS.at( i_YAxisParameterID ), i_DiagramDistance, TickmarkPen, TicklinePen, MinorTickmarkPen, MinorTicklinePen );                                                                        // Y-Axis, Parameter
                drawHeaderV( painterV, v_PS.at( i_YAxisParameterID ) );
                drawDiagramFrame( painterV, v_PS.at( i_YAxisParameterID ), DiagramPen );

                calcPointCoordinatesNumericV( i_XAxisParameterID, i_YAxisParameterID, XReverseGraphRange(), v_PS, v_Data, v_PointsNumeric );
                calcPointCoordinatesTextV( i_XAxisParameterID, i_YAxisParameterID, XReverseGraphRange(), v_PS, v_Data, v_PointsDataText, sl_DataText );
            }
            else
            {
                setDiagramRect( QRect( i_DiagramLeft, i_DiagramTop, i_DiagramWidth, i_DiagramHeight + StatusBarHeight() ), v_PS[i_YAxisParameterID] );

                drawDiagramFrame( painterV, v_PS.at( i_YAxisParameterID ), DiagramPen );
                drawHeaderV( painterV, v_PS.at( i_YAxisParameterID ) );
                drawText( painterV, v_PS.at( i_YAxisParameterID ).DiagramRect(), HeaderTextFont(), HeaderTextColor(), 10, _NORMAL_, Qt::AlignLeft, 0, tr( " processing..." ) );
            }
        }
    }

    drawCopyrightV( painterV, QRect( i_DiagramLeft+i_DiagramWidth+v_PS.at( i_LastVisibleParameter ).XTickmarkLength(), i_DiagramTop, marginRight, i_DiagramHeight ), "PanPlot (doi:10.1594/PANGAEA.816201)" );

// **********************************************************************************************
//  resize window

    if ( ( ResizeState() == true ) && ( fixedDiagramSize() == false ) && ( SavePlotFormat() == _FORMATNULL_ ) )
    {
        setResizeState( false );

        if ( count++ < 1)
            QTimer::singleShot( 1000, this, SLOT( update() ) );

        if ( count > 10 )
            resetCount();

        return;
    }

    resetCount();

// **********************************************************************************************
// draw data

    painterV.setRenderHint( QPainter::Antialiasing, Antialiasing() );

    j = 0;

    for ( int i=1; i<i_NumOfParameter; i++ )
    {
        if ( v_PP.at( i ) > -1 )
        {
            i_YAxisParameterID = v_PP.at( i );

            i_DiagramLeft = marginLeft + 2*i_XAxisTextHeight + i_XAxisScaleWidth + ( j++ )*( i_DiagramWidth + i_DiagramDistance ) + v_PS.at( i_XAxisParameterID ).XTickmarkLength();
            painterV.setClipRect( QRect( i_DiagramLeft, i_DiagramTop, i_DiagramWidth, i_DiagramHeight ) );

            if ( v_PS.at( i_YAxisParameterID ).drawColorized() == true )
                drawDataColorizedV( painterV, v_PS.at( i_YAxisParameterID ), i_StartPosNumeric, v_PointsNumeric );

            if ( v_PS.at( i_YAxisParameterID ).drawLine() == true )
                drawDataLine( painterV, v_PS.at( i_YAxisParameterID ), i_StartPosNumeric, v_PointsNumeric );

            if ( v_PS.at( i_YAxisParameterID ).drawMarker() == true )
                drawDataMarker( painterV, v_PS.at( i_YAxisParameterID ), i_StartPosNumeric, v_PointsNumeric );

            if ( v_PS.at( i_YAxisParameterID ).drawDataText() == true )
                drawDataText( painterV, v_PS.at( i_YAxisParameterID ), i_StartPosDataText, v_PointsDataText, sl_DataText );

            if ( v_PS.at( i_YAxisParameterID ).drawXRefline() == true )
                drawXReflineV( painterV, v_PS.at( i_YAxisParameterID ), XReverseGraphRange() );

            if ( v_PS.at( i_YAxisParameterID ).drawYRefline() == true )
                drawYReflineV( painterV, v_PS.at( i_YAxisParameterID ) );

            i_StartPosNumeric  += v_PS.at( i_YAxisParameterID ).NumOfPointsNumeric();
            i_StartPosDataText += v_PS.at( i_YAxisParameterID ).NumOfPointsDataText();
        }
    }

    painterV.end();

// **********************************************************************************************
// Save plot to file

    if ( ( SavePlotFormat() == _FORMATPNG_ ) || ( SavePlotFormat() == _FORMATBMP_ ) )
    {
        QImageWriter writer;
        writer.setFileName( FilenamePlot() );

        switch ( SavePlotFormat() )
        {
        case _FORMATPNG_:
            writer.setFormat( "png" );
            break;
        case _FORMATBMP_:
            writer.setFormat( "bmp" );
            break;
        default:
            break;
        }

        writer.write( image );
    }

    setSavePlotFormat( _FORMATNULL_ );

    return;
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawXReflineV( QPainter &painter, const PlotSettings PS, const bool b_XReverseGraphRange )
{
    if ( PS.drawXRefline() == true )
    {
        QRect rect = PS.DiagramRect();

        QPen Pen = QPen( PS.XReflineColor(), PS.XReflineWidth(), Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );

        painter.setPen( Pen );

        double a0 = 0.;
        double a1 = 0.;

        if ( b_XReverseGraphRange == true )
        {
            a0  = (double) ( rect.top() );
            a1  = (double) ( rect.height() )/( PS.XGraphMax() - PS.XGraphMin() );
        }
        else
        {
            a0  = (double) ( rect.top() + rect.height() );
            a1  = (double) -1 * ( rect.height() )/( PS.XGraphMax() - PS.XGraphMin() );
        }

        double a = a0 + ( PS.XRefline() - PS.XGraphMin() ) * a1;

        painter.drawLine( rect.left(), (int) a, rect.right(), (int) a );
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawXReflineH( QPainter &painter, const PlotSettings PS, const bool b_XReverseGraphRange )
{
    if ( PS.drawXRefline() == true )
    {
        QRect rect = PS.DiagramRect();

        QPen Pen = QPen( PS.XReflineColor(), PS.XReflineWidth(), Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );

        painter.setPen( Pen );

        double a0 = 0.;
        double a1 = 0.;

        if ( b_XReverseGraphRange == false )
        {
            a0  = (double) ( rect.left() );
            a1  = (double) ( rect.width() )/( PS.XGraphMax() - PS.XGraphMin() );
        }
        else
        {
            a0  = (double) ( rect.left() + rect.width() );
            a1  = (double) -1. * ( rect.width() )/( PS.XGraphMax() - PS.XGraphMin() );
        }

        double a = a0 + ( PS.XRefline() - PS.XGraphMin() ) * a1;

        painter.drawLine( (int) a, rect.top(), (int) a, rect.bottom() );
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawYReflineV( QPainter &painter, const PlotSettings PS )
{
    if ( PS.drawYRefline() == true )
    {
        double b0 = 0.;
        double b1 = 0.;

        QRect rect = PS.DiagramRect();

        QPen Pen = QPen( PS.YReflineColor(), PS.YReflineWidth(), Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );

        painter.setPen( Pen );

        if ( PS.YReverseGraphRange() == false )
        {
            b0 = (double) ( rect.left() );
            b1 = (double) ( rect.width() )/( PS.YGraphMax() - PS.YGraphMin() );
        }
        else
        {
            b0 = (double) ( rect.left() + rect.width() );
            b1 = (double) -1. * ( rect.width() )/( PS.YGraphMax() - PS.YGraphMin() );
        }

        double b = b0 + ( PS.YRefline() - PS.YGraphMin() ) * b1 + 1;

        painter.drawLine( (int) b, rect.top(), (int) b, rect.bottom() );
    }

}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawYReflineH( QPainter &painter, const PlotSettings PS )
{
    if ( PS.drawYRefline() == true )
    {
        QRect rect = PS.DiagramRect();

        QPen Pen = QPen( PS.YReflineColor(), PS.YReflineWidth(), Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );

        painter.setPen( Pen );

        double b0 = 0.;
        double b1 = 0.;

        if ( PS.YReverseGraphRange() == true )
        {
            b0  = (double) ( rect.top() );
            b1  = (double) ( rect.height() )/( PS.YGraphMax() - PS.YGraphMin() );
        }
        else
        {
            b0  = (double) ( rect.top() + rect.height() );
            b1  = (double) -1 * ( rect.height() )/( PS.YGraphMax() - PS.YGraphMin() );
        }

        double b = b0 + ( PS.YRefline() - PS.YGraphMin() ) * b1;

        painter.drawLine( rect.left(), (int) b, rect.right(), (int) b );
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2014-08-23

void RenderArea::drawDataColorizedV( QPainter &painter, const PlotSettings PS, int startPos, const QVector<QPointF> &v_P )
{
    int s = startPos;
    int e = startPos + PS.NumOfPointsNumeric();

    if ( e <= s )
        return;

    QVector<QPointF> Points;

    for ( int j=s; j<e; j++ )
        Points.append( v_P.at( j ) );

    if ( PS.drawYRefline() == true )
    {
        int i_DiagramLeft   = painter.clipBoundingRect().left();
        int i_DiagramTop    = painter.clipBoundingRect().top();
        int i_DiagramWidth  = painter.clipBoundingRect().width();
        int i_DiagramHeight = painter.clipBoundingRect().height();

        double YRefline     = PS.YRefline();

        if ( YRefline < PS.YGraphMin() )
            YRefline = PS.YGraphMin();

        if ( YRefline > PS.YGraphMax() )
            YRefline = PS.YGraphMax();

        QPen   Pen1, Pen2;
        QBrush Brush1, Brush2;

        if ( PS.YReverseGraphRange() == false )
        {
            Pen1   = QPen( QColor( PS.ColorizedLessRefColor() ), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
            Brush1 = QBrush( QColor( PS.ColorizedLessRefColor() ), Qt::BrushStyle( PS.Pattern() ) );
            Pen2   = QPen( QColor( PS.ColorizedGreaterRefColor() ), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
            Brush2 = QBrush( QColor( PS.ColorizedGreaterRefColor() ), Qt::BrushStyle( PS.Pattern() ) );
        }
        else
        {
            Pen1   = QPen( QColor( PS.ColorizedGreaterRefColor() ), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
            Brush1 = QBrush( QColor( PS.ColorizedGreaterRefColor() ), Qt::BrushStyle( PS.Pattern() ) );
            Pen2   = QPen( QColor( PS.ColorizedLessRefColor() ), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
            Brush2 = QBrush( QColor( PS.ColorizedLessRefColor() ), Qt::BrushStyle( PS.Pattern() ) );
        }

        painter.setPen( Pen1 );
        painter.setBrush( Brush1 );

        painter.setClipRect( QRect( i_DiagramLeft, i_DiagramTop, i_DiagramWidth, i_DiagramHeight ) );
        painter.drawPolygon( Points );

        QRect  rect   = PS.DiagramRect();

        double b0 = 0.;
        double b1 = 0.;

        if ( PS.YReverseGraphRange() == false )
        {
            b0 = (double) ( rect.left() );
            b1 = (double) ( rect.width() )/( PS.YGraphMax() - PS.YGraphMin() );
        }
        else
        {
            b0  = (double) ( rect.left() + rect.width() );
            b1  = (double) -1. * ( rect.width() )/( PS.YGraphMax() - PS.YGraphMin() );
        }

        double b = b0 + ( PS.YRefline() - PS.YGraphMin() ) * b1 + 1;

        painter.setPen( Pen2 );
        painter.setBrush( Brush2 );

        painter.setClipRect( QRect( (int) b, i_DiagramTop, ( i_DiagramLeft + i_DiagramWidth - (int) b ), i_DiagramHeight ) );
        painter.drawPolygon( Points );

        painter.setClipRect( QRect( i_DiagramLeft, i_DiagramTop, i_DiagramWidth, i_DiagramHeight ) );
    }
    else
    {
        QPen   Pen   = QPen( QColor( PS.ColorizedGreaterRefColor() ), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
        QBrush Brush = QBrush( QColor( PS.ColorizedGreaterRefColor() ), Qt::BrushStyle( PS.Pattern() ) );

        painter.setPen( Pen );
        painter.setBrush( Brush );

        painter.drawPolygon( Points );
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2014-08-23

void RenderArea::drawDataColorizedH( QPainter &painter, const PlotSettings PS, int startPos, const QVector<QPointF> &v_P )
{
    int s = startPos;
    int e = startPos + PS.NumOfPointsNumeric();

    if ( e <= s )
        return;

    QVector<QPointF> Points;

    for ( int j=s; j<e; j++ )
        Points.append( v_P.at( j ) );

    if ( PS.drawYRefline() == true )
    {
        int i_DiagramLeft   = painter.clipBoundingRect().left();
        int i_DiagramTop    = painter.clipBoundingRect().top();
        int i_DiagramWidth  = painter.clipBoundingRect().width();
        int i_DiagramHeight = painter.clipBoundingRect().height();

        double YRefline     = PS.YRefline();

        if ( YRefline < PS.YGraphMin() )
            YRefline = PS.YGraphMin();

        if ( YRefline > PS.YGraphMax() )
            YRefline = PS.YGraphMax();

        QPen   Pen1, Pen2;
        QBrush Brush1, Brush2;

        if ( PS.YReverseGraphRange() == false )
        {
            Pen1   = QPen( QColor( PS.ColorizedGreaterRefColor() ), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
            Brush1 = QBrush( QColor( PS.ColorizedGreaterRefColor() ), Qt::BrushStyle( PS.Pattern() ) );
            Pen2   = QPen( QColor( PS.ColorizedLessRefColor() ), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
            Brush2 = QBrush( QColor( PS.ColorizedLessRefColor() ), Qt::BrushStyle( PS.Pattern() ) );
        }
        else
        {
            Pen1   = QPen( QColor( PS.ColorizedLessRefColor() ), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
            Brush1 = QBrush( QColor( PS.ColorizedLessRefColor() ), Qt::BrushStyle( PS.Pattern() ) );
            Pen2   = QPen( QColor( PS.ColorizedGreaterRefColor() ), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
            Brush2 = QBrush( QColor( PS.ColorizedGreaterRefColor() ), Qt::BrushStyle( PS.Pattern() ) );
        }

        painter.setPen( Pen1 );
        painter.setBrush( Brush1 );

        painter.setClipRect( QRect( i_DiagramLeft, i_DiagramTop, i_DiagramWidth, i_DiagramHeight ) );
        painter.drawPolygon( Points );

        QRect  rect = PS.DiagramRect();

        double b0 = 0.;
        double b1 = 0.;

        if ( PS.YReverseGraphRange() == true )
        {
            b0  = (double) ( rect.top() );
            b1  = (double) ( rect.height() )/( PS.YGraphMax() - PS.YGraphMin() );
        }
        else
        {
            b0  = (double) ( rect.top() + rect.height() );
            b1  = (double) -1 * ( rect.height() )/( PS.YGraphMax() - PS.YGraphMin() );
        }

        double b = b0 + ( YRefline - PS.YGraphMin() ) * b1;

        painter.setPen( Pen2 );
        painter.setBrush( Brush2 );

        painter.setClipRect( QRect( i_DiagramLeft, (int) b, i_DiagramWidth, i_DiagramTop + i_DiagramHeight - (int) b ) );
        painter.drawPolygon( Points );

        painter.setClipRect( QRect( i_DiagramLeft, i_DiagramTop, i_DiagramWidth, i_DiagramHeight ) );
    }
    else
    {
        QPen   Pen   = QPen( QColor( PS.ColorizedGreaterRefColor() ), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
        QBrush Brush = QBrush( QColor( PS.ColorizedGreaterRefColor() ), Qt::BrushStyle( PS.Pattern() ) );

        painter.setPen( Pen );
        painter.setBrush( Brush );

        painter.drawPolygon( Points );
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-01-15

void RenderArea::drawDataLine( QPainter &painter, const PlotSettings PS, int startPos, const QVector<QPointF> &v_P )
{
    int s = startPos;
    int e = startPos + PS.NumOfPointsNumeric();

    if ( PS.drawColorized() == false )
        e -= 3;

    if ( e <= s )
        return;

    QVector<QPointF> Points;

    for ( int j=s; j<e; j++ )
        Points.append( v_P.at( j ) );

    QPen   Pen   = QPen( QColor( PS.LineColor() ), PS.LineWidth(), Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
    QBrush Brush = QBrush( QColor( PS.LineColor() ), Qt::SolidPattern );

    painter.setPen( Pen );
    painter.setBrush( Brush );

    painter.drawPolyline( Points );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-01-15

void RenderArea::drawDataMarker( QPainter &painter, const PlotSettings PS, int startPos, const QVector<QPointF> &v_P )
{
    int s = startPos;
    int e = startPos + PS.NumOfPointsNumeric();

    if ( PS.NumOfPointsNumeric() > 3 )
        e -= 3;

    if ( e <= s )
        return;

    QPen   Pen   = QPen( QColor( PS.MarkerColor() ), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin );
    QBrush Brush = QBrush( QColor( PS.MarkerColor() ), Qt::SolidPattern );

    painter.setPen( Pen );
    painter.setBrush( Brush );

    for ( int j=s; j<e; j++ )
      painter.drawEllipse( v_P.at( j ), PS.MarkerSize(), PS.MarkerSize() );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2011-01-03

void RenderArea::drawDataText( QPainter &painter, const PlotSettings PS, const int startPos, const QVector<QPointF> &v_P, const QStringList &sl_Data )
{
    int s = startPos;
    int e = startPos + PS.NumOfPointsDataText();

    int i_TextWidth  = 0;
    int i_TextHeight = getTextHeight( painter, PS.DataTextFont(), PS.DataTextPointSize(), _NORMAL_, tr( "gG" ) );

    if ( e <= s )
        return;

    for ( int j=s; j<e; j++ )
    {
        i_TextWidth  = getTextWidth( painter, PS.DataTextFont(), PS.DataTextPointSize(), _NORMAL_, sl_Data.at( j ) );
        drawText( painter, QRect( v_P.at( j ).x(), v_P.at( j ).y()-i_TextHeight/2-3, i_TextWidth, i_TextHeight ), PS.DataTextFont(), PS.DataTextColor(), PS.DataTextPointSize(), _NORMAL_, Qt::AlignLeft, 0, sl_Data.at( j ) );
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawDiagramFrame( QPainter &painter, const PlotSettings PS, const QPen Pen )
{
    painter.setPen( Pen );
    painter.setBrush( Qt::NoBrush );
    painter.drawRect( PS.DiagramRect() );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawDiagram( QPainter &painter, const PlotSettings PS, const QPen Pen )
{
    painter.setPen( Pen );
    painter.setBrush( Qt::NoBrush );

    if ( PS.drawDiagramBackground() == true )
    {
        QBrush Brush = QBrush( PS.DiagramBackgroundColor(), Qt::SolidPattern );
        painter.setBrush( Brush );
    }

    painter.drawRect( PS.DiagramRect() );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawCopyrightV( QPainter &painter, const QRect rect, const QString &s_CopyrightText )
{
    int i_TextWidth  = getTextWidth( painter, HeaderTextFont(), PointSizeUnit(), _NORMAL_, s_CopyrightText ) + 1;
    int i_TextHeight = getTextHeight( painter, HeaderTextFont(), PointSizeUnit(), _NORMAL_, tr( "gG" ) );

    if ( i_TextHeight + 5 < rect.width() )
        drawText( painter, QRect( rect.left() + 5, rect.bottom(), i_TextWidth, i_TextHeight ), HeaderTextFont(), HeaderTextColor(), PointSizeUnit(), _NORMAL_, Qt::AlignLeft, 90, s_CopyrightText );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawCopyrightH( QPainter &painter, const QRect rect, const QString &s_CopyrightText )
{
    int i_TextWidth  = getTextWidth( painter, HeaderTextFont(), PointSizeUnit(), _NORMAL_, s_CopyrightText ) + 1;
    int i_TextHeight = getTextHeight( painter, HeaderTextFont(), PointSizeUnit(), _NORMAL_, tr( "gG" ) );

    if ( i_TextWidth < rect.width() )
        drawText( painter, QRect( rect.right()+5, rect.bottom(), i_TextWidth, i_TextHeight ), HeaderTextFont(), HeaderTextColor(), PointSizeUnit(), _NORMAL_, Qt::AlignLeft, 90, s_CopyrightText );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawHeaderV( QPainter &painter, const PlotSettings PS )
{
    QRect rect = PS.HeaderRect();

    switch ( ParameterNameOrientation() )
    {
    case 0:
        drawParameter( painter, PS, rect.topLeft(), rect.width(), Qt::AlignCenter, 0 );
        break;
    case 45:
        drawParameter( painter, PS, rect.topLeft(), rect.width(), Qt::AlignLeft, 45 );
        break;
    case 90:
        QPoint Point( rect.left() + ( rect.width() - rect.height() )/2, rect.top() );
        drawParameter( painter, PS, Point, rect.width(), Qt::AlignLeft, 90 );
        break;
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawHeaderH( QPainter &painter, const PlotSettings PS )
{
    QRect rect = PS.HeaderRect();

    switch ( ParameterNameOrientation() )
    {
    case 0:
        drawParameter( painter, PS, rect.topLeft(), rect.width(), Qt::AlignCenter, 0 );
        break;
    case 45:
        drawParameter( painter, PS, rect.topLeft(), rect.width(), Qt::AlignLeft, 45 );
        break;
    case 90:
        QPoint Point( rect.left() + ( rect.width() - rect.height() )/2, rect.top() );
        drawParameter( painter, PS, Point, rect.width(), Qt::AlignCenter, 90 );
        break;
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawYScaleV( QPainter &painter, const PlotSettings PS, const int i_DiagramDistance, const QPen TickmarkPen, const QPen TicklinePen, const QPen MinorTickmarkPen, const QPen MinorTicklinePen )
{
    QRect rect = PS.DiagramRect();

// **********************************************************************************************

    if ( PS.Type() == isText )
        return;

// **********************************************************************************************

    QVector<int> X;  // y of ticks
    QVector<int> Xm; // y of minor ticks

// **********************************************************************************************

    calcYTicksPositionV( rect, PS, X, Xm );

// **********************************************************************************************

    if ( PS.drawYTickmarkLabels() == true )
        drawYTickLabelsV( painter, QRect( rect.left(), rect.top(), rect.width(), PS.YTickmarkLength() ), Qt::black, PS, X, i_DiagramDistance );

// **********************************************************************************************
//  Major tickmarks

    if ( PS.drawYTicklines() == true )
        drawYTicksV( painter, QRect( rect.left(), rect.top()+1, rect.width(), rect.height()-2 ), TicklinePen, X );

    if ( PS.drawYTickmarksTopOutside() == true )
        drawYTicksV( painter, QRect( rect.left(), rect.top()-PS.YTickmarkLength(), rect.width(), PS.YTickmarkLength() ), TickmarkPen, X );

    if ( PS.drawYTickmarksTopInside() == true )
        drawYTicksV( painter, QRect( rect.left(), rect.top(), rect.width(), PS.YTickmarkLength() ), TickmarkPen, X );

    if ( PS.drawYTickmarksBottomOutside() == true )
        drawYTicksV( painter, QRect( rect.left(), rect.bottom()+1, rect.width(), PS.YTickmarkLength() ), TickmarkPen, X );

    if ( PS.drawYTickmarksBottomInside() == true )
        drawYTicksV( painter, QRect( rect.left(), rect.bottom()+1-PS.YTickmarkLength(), rect.width(), PS.YTickmarkLength() ), TickmarkPen, X );

// **********************************************************************************************
// Minor tickmarks

    if ( PS.drawYMinorTicklines() == true )
        drawYMinorTicksV( painter, QRect( rect.left(), rect.top()+1, rect.width(), rect.height()-2 ), MinorTicklinePen, Xm );

    if ( PS.drawYMinorTickmarksTopOutside() == true )
        drawYMinorTicksV( painter, QRect( rect.left(), rect.top()-PS.YTickmarkLength()/2, rect.width(), PS.YTickmarkLength()/2 ), MinorTickmarkPen, Xm );

    if ( PS.drawYMinorTickmarksTopInside() == true )
        drawYMinorTicksV( painter, QRect( rect.left(), rect.top(), rect.width(), PS.YTickmarkLength()/2 ), MinorTickmarkPen, Xm );

    if ( PS.drawYMinorTickmarksBottomOutside() == true )
        drawYMinorTicksV( painter, QRect( rect.left(), rect.bottom()+1, rect.width(), PS.YTickmarkLength()/2 ), MinorTickmarkPen, Xm );

    if ( PS.drawYMinorTickmarksBottomInside() == true )
        drawYMinorTicksV( painter, QRect( rect.left(), rect.bottom()+1-PS.YTickmarkLength()/2, rect.width(), PS.YTickmarkLength()/2 ), MinorTickmarkPen, Xm );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawYScaleH( QPainter &painter, const PlotSettings PS, const int i_DiagramDistance, const QPen TickmarkPen, const QPen TicklinePen, const QPen MinorTickmarkPen, const QPen MinorTicklinePen )
{
    QRect rect = PS.DiagramRect();

// **********************************************************************************************

    if ( PS.Type() == isText )
        return;

// **********************************************************************************************

    QVector<int> Y;  // y of ticks
    QVector<int> Ym; // y of minor ticks

// **********************************************************************************************

    calcYTicksPositionH( rect, PS, Y, Ym );

// **********************************************************************************************

    if ( PS.drawYTickmarkLabels() == true )
        drawYTickLabelsH( painter, QRect( rect.left()-PS.YTickmarkLength(), rect.top(), rect.width(), PS.YTickmarkLength() ), Qt::black, PS, Y, i_DiagramDistance );

// **********************************************************************************************
//  Major tickmarks

    if ( PS.drawYTicklines() == true )
        drawYTicksH( painter, QRect( rect.left(), rect.top(), rect.width(), rect.height() ), TicklinePen, Y );

    if ( PS.drawYTickmarksTopOutside() == true )
        drawYTicksH( painter, QRect( rect.left()-PS.YTickmarkLength(), rect.top(), PS.YTickmarkLength(), rect.height() ), TickmarkPen, Y );

    if ( PS.drawYTickmarksTopInside() == true )
        drawYTicksH( painter, QRect( rect.left(), rect.top(), PS.YTickmarkLength(), rect.height() ), TickmarkPen, Y );

    if ( PS.drawYTickmarksBottomOutside() == true )
        drawYTicksH( painter, QRect( rect.right()+1, rect.top(), PS.YTickmarkLength(), rect.height() ), TickmarkPen, Y );

    if ( PS.drawYTickmarksBottomInside() == true )
        drawYTicksH( painter, QRect( rect.right()-PS.YTickmarkLength()+1, rect.top(), PS.YTickmarkLength(), rect.height() ), TickmarkPen, Y );

// **********************************************************************************************
// Minor tickmarks

    if ( PS.drawYMinorTicklines() == true )
        drawYMinorTicksH( painter, QRect( rect.left(), rect.top(), rect.width(), rect.height() ), MinorTicklinePen, Ym );

    if ( PS.drawYMinorTickmarksTopOutside() == true )
        drawYMinorTicksH( painter, QRect( rect.left()-PS.YTickmarkLength()/2, rect.top(), PS.YTickmarkLength()/2, rect.height() ), MinorTickmarkPen, Ym );

    if ( PS.drawYMinorTickmarksTopInside() == true )
        drawYMinorTicksH( painter, QRect( rect.left(), rect.top(), PS.YTickmarkLength()/2, rect.height() ), MinorTickmarkPen, Ym );

    if ( PS.drawYMinorTickmarksBottomOutside() == true )
        drawYMinorTicksH( painter, QRect( rect.right()+1, rect.top(), PS.YTickmarkLength()/2, rect.height() ), MinorTickmarkPen, Ym );

    if ( PS.drawYMinorTickmarksBottomInside() == true )
        drawYMinorTicksH( painter, QRect( rect.right()-PS.YTickmarkLength()/2+1, rect.top(), PS.YTickmarkLength()/2, rect.height() ), MinorTickmarkPen, Ym );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawXScaleV( QPainter &painter, const PlotSettings PS, const int i_DiagramDistance, const QPen TickmarkPen, const QPen TicklinePen, const QPen MinorTickmarkPen, const QPen MinorTicklinePen, const int p, const int i_LastVisibleParameter, const int i_XAxisParameterType, const bool b_XReverseGraphRange )
{
    QRect rect = PS.DiagramRect();

    QVector<int> Y;  // y of ticks
    QVector<int> Ym; // y of minor ticks

// **********************************************************************************************

    calcXTicksPositionV( rect, PS, b_XReverseGraphRange, Y, Ym );

// **********************************************************************************************

    if ( ( PS.drawXTickmarkLabels() == true ) && ( p == 1 ) )
        drawXTickLabelsV( painter, QRect( rect.left(), rect.top(), PS.XTickmarkLength(), rect.height() ), Qt::black, PS, Y, i_XAxisParameterType );

// **********************************************************************************************
// Major tickmarks

    if ( PS.drawXTicklines() == true )
        drawXTicksV( painter, QRect( rect.left()+1, rect.top(), rect.width()-2, rect.height() ), TicklinePen, Y );

    if ( ( PS.drawXTickmarksLeftOutside() == true ) && ( ( p == 1 ) || ( i_DiagramDistance >= 3*PS.XTickmarkLength() ) ) )
        drawXTicksV( painter, QRect( rect.left()-PS.XTickmarkLength(), rect.top(), PS.XTickmarkLength(), rect.height() ), TickmarkPen, Y );

    if ( PS.drawXTickmarksLeftInside() == true )
        drawXTicksV( painter, QRect( rect.left(), rect.top(), PS.XTickmarkLength(), rect.height() ), TickmarkPen, Y );

    if ( ( PS.drawXTickmarksRightOutside() == true ) && ( ( p == i_LastVisibleParameter ) || ( i_DiagramDistance >= 3*PS.XTickmarkLength() ) ) )
        drawXTicksV( painter, QRect( rect.right()+1, rect.top(), PS.XTickmarkLength(), rect.height() ), TickmarkPen, Y );

    if ( PS.drawXTickmarksRightInside() == true )
        drawXTicksV( painter, QRect( rect.right()+1-PS.XTickmarkLength(), rect.top(), PS.XTickmarkLength(), rect.height() ), TickmarkPen, Y );

// **********************************************************************************************
// Minor tickmarks

    if ( PS.drawXMinorTicklines() == true )
        drawXMinorTicksV( painter, QRect( rect.left()+1, rect.top(), rect.width()-2, rect.height() ), MinorTicklinePen, Ym );

    if ( ( PS.drawXMinorTickmarksLeftOutside() == true ) && ( PS.NumOfXMinorTicks() > 0 ) && ( ( p == 1 ) || ( i_DiagramDistance >= 3*PS.XTickmarkLength() ) ) )
        drawXMinorTicksV( painter, QRect( rect.left()-PS.XTickmarkLength()/2, rect.top(), PS.XTickmarkLength()/2, rect.height() ), MinorTickmarkPen, Ym );

    if ( ( PS.drawXMinorTickmarksLeftInside() == true ) && ( PS.NumOfXMinorTicks() > 0 ) )
        drawXMinorTicksV( painter, QRect( rect.left(), rect.top(), PS.XTickmarkLength()/2, rect.height() ), MinorTickmarkPen, Ym );

    if ( ( PS.drawXMinorTickmarksRightOutside() == true ) && ( PS.NumOfXMinorTicks() > 0 ) && ( ( p == i_LastVisibleParameter ) || ( i_DiagramDistance >= 3*PS.XTickmarkLength() ) ) )
        drawXMinorTicksV( painter, QRect( rect.right()+1, rect.top(), PS.XTickmarkLength()/2, rect.height() ), MinorTickmarkPen, Ym );

    if ( ( PS.drawXMinorTickmarksRightInside() == true ) && ( PS.NumOfXMinorTicks() > 0 ) )
        drawXMinorTicksV( painter, QRect( rect.right()+1-PS.XTickmarkLength()/2, rect.top(), PS.XTickmarkLength()/2, rect.height() ), MinorTickmarkPen, Ym );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawXScaleH( QPainter &painter, const PlotSettings PS, const int i_DiagramDistance, const QPen TickmarkPen, const QPen TicklinePen, const QPen MinorTickmarkPen, const QPen MinorTicklinePen, const int p, const int i_LastVisibleParameter, const int i_XAxisParameterType, const bool b_XReverseGraphRange )
{
    QRect rect = PS.DiagramRect();

    QVector<int> X;  // x of ticks
    QVector<int> Xm; // x of minor ticks

// **********************************************************************************************

    calcXTicksPositionH( rect, PS, b_XReverseGraphRange, X, Xm );

// **********************************************************************************************

    if ( ( PS.drawXTickmarkLabels() == true ) && ( p == i_LastVisibleParameter ) )
        drawXTickLabelsH( painter, QRect( rect.left(), rect.top()+PS.XTickmarkLength(), rect.width(), rect.height() ), Qt::black, PS, X, i_XAxisParameterType );

// **********************************************************************************************
// Major tickmarks

    if ( PS.drawXTicklines() == true )
        drawXTicksH( painter, QRect( rect.left(), rect.top(), rect.width(), rect.height() ), TicklinePen, X );

    if ( ( PS.drawXTickmarksLeftOutside() == true ) && ( ( p == 1 ) || ( i_DiagramDistance >= 3*PS.XTickmarkLength() ) ) ) // top and outside
        drawXTicksH( painter, QRect( rect.left(), rect.top()-PS.XTickmarkLength(), rect.width(), PS.XTickmarkLength() ), TickmarkPen, X );

    if ( PS.drawXTickmarksLeftInside() == true ) // top and inside
        drawXTicksH( painter, QRect( rect.left(), rect.top(), rect.width(), PS.XTickmarkLength() ), TickmarkPen, X );

    if ( ( PS.drawXTickmarksRightOutside() == true ) && ( ( p == i_LastVisibleParameter ) || ( i_DiagramDistance >= 3*PS.XTickmarkLength() ) ) ) // bottom and outside
        drawXTicksH( painter, QRect( rect.left(), rect.bottom()+1, rect.width(), PS.XTickmarkLength() ), TickmarkPen, X );

    if ( PS.drawXTickmarksRightInside() == true ) // bottom and inside
        drawXTicksH( painter, QRect( rect.left(), rect.bottom()-PS.XTickmarkLength()+1, rect.width(), PS.XTickmarkLength() ), TickmarkPen, X );

// **********************************************************************************************
// Minor tickmarks

    if ( PS.drawXMinorTicklines() == true )
        drawXMinorTicksH( painter, QRect( rect.left(), rect.top(), rect.width(), rect.height() ), MinorTicklinePen, Xm );

    if ( ( PS.drawXMinorTickmarksLeftOutside() == true ) && ( PS.NumOfXMinorTicks() > 0 ) && ( ( p == 1 ) || ( i_DiagramDistance >= 3*PS.XTickmarkLength() ) ) )// top and outside
        drawXMinorTicksH( painter, QRect( rect.left(), rect.top()-PS.XTickmarkLength()/2, rect.width(), PS.XTickmarkLength()/2 ), MinorTickmarkPen, Xm );

    if ( ( PS.drawXMinorTickmarksLeftInside() == true ) && ( PS.NumOfXMinorTicks() > 0 ) ) // top and inside
        drawXMinorTicksH( painter, QRect( rect.left(), rect.top(), rect.width(), PS.XTickmarkLength()/2 ), MinorTickmarkPen, Xm );

    if ( ( PS.drawXMinorTickmarksRightOutside() == true ) && ( PS.NumOfXMinorTicks() > 0 ) && ( ( p == i_LastVisibleParameter ) || ( i_DiagramDistance >= 3*PS.XTickmarkLength() ) ) ) // bottom and outside
        drawXMinorTicksH( painter, QRect( rect.left(), rect.bottom()+1, rect.width(), PS.XTickmarkLength()/2 ), MinorTickmarkPen, Xm );

    if ( ( PS.drawXMinorTickmarksRightInside() == true ) && ( PS.NumOfXMinorTicks() > 0 ) ) // bottom and inside
        drawXMinorTicksH( painter, QRect( rect.left(), rect.bottom()-PS.XTickmarkLength()/2+1, rect.width(), PS.XTickmarkLength()/2 ), MinorTickmarkPen, Xm );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawXTickLabelsV( QPainter &painter, const QRect rect, const QColor TickLabelColor, const PlotSettings PS, const QVector<int> Y, const int i_XAxisParameterType )
{
    int     i_TextHeight = getTextHeight( painter, HeaderTextFont(), PointSizeScale(), _NORMAL_, tr( "gG" ) );
    int     i_TextWidth  = 0;

    QString s_Text       = "";

// **********************************************************************************************

    painter.setPen( TickLabelColor );

    for ( int i=0; i<Y.count(); i++ )
    {
        if ( i_XAxisParameterType == isDateTime )
            s_Text = buildDateTimeString( DateTimeFormat(), PS.XGraphMin() + (double) i*PS.XTickmarkSpacing() );
        else
            s_Text = QString( "%1" ).arg( PS.XGraphMin() + (double) i*PS.XTickmarkSpacing(), 0, 'f', PS.XnFrac() );

        i_TextWidth = getTextWidth( painter, HeaderTextFont(), PointSizeScale(), _NORMAL_, s_Text );

        drawText( painter, QRect( rect.left() - i_TextWidth - rect.width() - 5, Y.at( i ) - i_TextHeight/2, i_TextWidth, i_TextHeight ), HeaderTextFont(), HeaderTextColor(), PointSizeScale(), _NORMAL_, Qt::AlignRight, 0, s_Text );
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawXTickLabelsH( QPainter &painter, const QRect rect, const QColor TickLabelColor, const PlotSettings PS, const QVector<int> X, const int i_XAxisParameterType )
{
    int     i_TextHeight = getTextHeight( painter, HeaderTextFont(), PointSizeScale(), _NORMAL_, tr( "gG" ) );
    int     i_TextWidth  = 0;

    QString s_Text       = "";

// **********************************************************************************************

    painter.setPen( TickLabelColor );

    for ( int i=0; i<X.count(); i++ )
    {
        if ( i_XAxisParameterType == isDateTime )
            s_Text = buildDateTimeString( DateTimeFormat(), PS.XGraphMin() + (double) i*PS.XTickmarkSpacing() );
        else
            s_Text = QString( "%1" ).arg( PS.XGraphMin() + (double) i*PS.XTickmarkSpacing(), 0, 'f', PS.XnFrac() );

        i_TextWidth = getTextWidth( painter, HeaderTextFont(), PointSizeScale(), _NORMAL_, s_Text );

        drawText( painter, QRect( X.at( i ) - i_TextWidth/2, rect.bottom() + 2*PS.XTickmarkLength(), i_TextWidth, i_TextHeight ), HeaderTextFont(), HeaderTextColor(), PointSizeScale(), _NORMAL_, Qt::AlignLeft, 0, s_Text );
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawXTicksV( QPainter &painter, const QRect rect, const QPen Pen, const QVector<int> Y )
{
    painter.setPen( Pen );

    for ( int i=0; i<Y.count(); i++ )
        painter.drawLine( rect.left(), Y.at( i ), rect.left() + rect.width(), Y.at( i ) );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawXTicksH( QPainter &painter, const QRect rect, const QPen Pen, const QVector<int> X )
{
    painter.setPen( Pen );

    for ( int i=0; i<X.count(); i++ )
        painter.drawLine( X.at( i ), rect.top(), X.at( i ), rect.top() + rect.height() );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawXMinorTicksV( QPainter &painter, const QRect rect, const QPen Pen, const QVector<int> Ym )
{
    painter.setPen( Pen );

    for ( int i=0; i<Ym.count(); i++ )
        painter.drawLine( rect.left(), Ym.at( i ), rect.left() + rect.width(), Ym.at( i ) );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawXMinorTicksH( QPainter &painter, const QRect rect, const QPen Pen, const QVector<int> Xm )
{
    painter.setPen( Pen );

    for ( int i=0; i<Xm.count(); i++ )
        painter.drawLine( Xm.at( i ), rect.top(), Xm.at( i ), rect.top() + rect.height() );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawYTickLabelsV( QPainter &painter, const QRect rect, const QColor TickLabelColor, const PlotSettings PS, const QVector<int> X, const int i_DiagramDistance )
{
    QVector<ScaleContainer> ScaleLabel;

    painter.setPen( TickLabelColor );

    buildScaleLabelV( painter, rect, PS, i_DiagramDistance, X, ScaleLabel );

    for ( int i=0; i<ScaleLabel.count(); i++ )
    {
        if ( ScaleLabel.at( i ).draw() == true )
            drawText( painter, QRect( ScaleLabel.at( i ).x(), ScaleLabel.at( i ).y(), ScaleLabel.at( i ).width(), ScaleLabel.at( i ).height() ), HeaderTextFont(), HeaderTextColor(), PointSizeScale(), _NORMAL_, Qt::AlignLeft, 0, ScaleLabel.at( i ).text() );
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawYTickLabelsH( QPainter &painter, const QRect rect, const QColor TickLabelColor, const PlotSettings PS, const QVector<int> Y, const int i_DiagramDistance )
{
    QVector<ScaleContainer> ScaleLabel;

    painter.setPen( TickLabelColor );

    buildScaleLabelH( painter, rect, PS, i_DiagramDistance, Y, ScaleLabel );

    for ( int i=0; i<ScaleLabel.count(); i++ )
    {
        if ( ScaleLabel.at( i ).draw() == true )
            drawText( painter, QRect( ScaleLabel.at( i ).x(), ScaleLabel.at( i ).y(), ScaleLabel.at( i ).width(), ScaleLabel.at( i ).height() ), HeaderTextFont(), HeaderTextColor(), PointSizeScale(), _NORMAL_, Qt::AlignRight, 0, ScaleLabel.at( i ).text() );
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawYTicksV( QPainter &painter, const QRect rect, const QPen Pen, const QVector<int> X )
{
    painter.setPen( Pen );

    for ( int i=0; i<X.count(); i++ )
        painter.drawLine( X.at( i ), rect.top(), X.at( i ), rect.top() + rect.height() );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawYTicksH( QPainter &painter, const QRect rect, const QPen Pen, const QVector<int> Y )
{
    painter.setPen( Pen );

    for ( int i=0; i<Y.count(); i++ )
        painter.drawLine( rect.left(), Y.at( i ), rect.left() + rect.width(), Y.at( i ) );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawYMinorTicksV( QPainter &painter, const QRect rect, const QPen Pen, const QVector<int> Xm )
{
    painter.setPen( Pen );

    for ( int i=0; i<Xm.count(); i++ )
        painter.drawLine( Xm.at( i ), rect.top(), Xm.at( i ), rect.top() + rect.height() );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawYMinorTicksH( QPainter &painter, const QRect rect, const QPen Pen, const QVector<int> Ym )
{
    painter.setPen( Pen );

    for ( int i=0; i<Ym.count(); i++ )
        painter.drawLine( rect.left(), Ym.at( i ), rect.left() + rect.width(), Ym.at( i ) );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-02-04

void RenderArea::calcXTicksPositionV( const QRect rect, const PlotSettings PS, const bool b_XReverseGraphRange, QVector<int> &Y, QVector<int> &Ym )
{
    double a0 = 0.;
    double a1 = 0.;

    int    i_NumOfTicks = 0;

// **********************************************************************************************

    if ( b_XReverseGraphRange == true )
    {
        a0 = (double) ( rect.top() );
        a1 = (double) ( rect.height() )/( PS.XGraphMax() - PS.XGraphMin() );
    }
    else
    {
        a0 = (double) ( rect.top() + rect.height() );
        a1 = (double) -1 * ( rect.height() )/( PS.XGraphMax() - PS.XGraphMin() );
    }

    i_NumOfTicks = (int) round( ( PS.XGraphMax() - PS.XGraphMin() )/PS.XTickmarkSpacing() );

// **********************************************************************************************

    Y.clear();
    Ym.clear();

    for ( int i=0; i<=i_NumOfTicks; i++ )
    {
        int a = (int) round( a0 + ( PS.XGraphMin() + (double) i*PS.XTickmarkSpacing() - PS.XGraphMin() ) * a1 );

        if ( ( a < rect.bottom()+2 ) && ( a > rect.top()-2 ) )
            Y.append( a );
    }

    if ( Y.count() > 1 )
    {
        double d_MinorTickSpacing =  (double) ( Y.at( 1 ) - Y.at( 0 ) ) / (double) PS.NumOfXMinorTicks();

        for ( int i=0; i<Y.count(); i++ )
        {
            for ( int j=1; j<PS.NumOfXMinorTicks(); j++ )
            {
                int y = Y.at( i ) + (int) round( (double) j * d_MinorTickSpacing );

                if ( ( y < rect.bottom() ) && ( y > rect.top() ) )
                    Ym.append( y );
            }
        }
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-02-04

void RenderArea::calcXTicksPositionH( const QRect rect, const PlotSettings PS, const bool b_XReverseGraphRange, QVector<int> &X, QVector<int> &Xm )
{
    double a0 = 0.;
    double a1 = 0.;

    int    i_NumOfTicks = 0;

// **********************************************************************************************

    if ( b_XReverseGraphRange == false )
    {
        a0 = (double) ( rect.left() );
        a1 = (double) ( rect.width() )/( PS.XGraphMax() - PS.XGraphMin() );
    }
    else
    {
        a0 = (double) ( rect.left() + rect.width() );
        a1 = (double) -1 * ( rect.width() )/( PS.XGraphMax() - PS.XGraphMin() );
    }

    i_NumOfTicks = (int) round( ( PS.XGraphMax() - PS.XGraphMin() )/PS.XTickmarkSpacing() );

// **********************************************************************************************

    X.clear();
    Xm.clear();

    for ( int i=0; i<=i_NumOfTicks; i++ )
    {
        int a = (int) round( a0 + ( PS.XGraphMin() + (double) i*PS.XTickmarkSpacing() - PS.XGraphMin() ) * a1 );

        if ( ( a < rect.right()+2 ) && ( a > rect.left()-2 ) )
            X.append( a );
    }

    if ( X.count() > 1 )
    {
        double d_MinorTickSpacing =  (double) ( X.at( 1 ) - X.at( 0 ) ) / (double) PS.NumOfXMinorTicks();

        for ( int i=0; i<X.count(); i++ )
        {
            for ( int j=1; j<PS.NumOfXMinorTicks(); j++ )
            {
                int x = X.at( i ) + (int) round( (double) j * d_MinorTickSpacing );

                if ( ( x < rect.right() ) && ( x > rect.left() ) )
                    Xm.append( x );
            }
        }
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::calcYTicksPositionV( const QRect rect, const PlotSettings PS, QVector<int> &X, QVector<int> &Xm )
{
    double b0 = 0.;
    double b1 = 0.;

    int    i_NumOfTicks = 0;

// **********************************************************************************************

    if ( PS.YReverseGraphRange() == false )
    {
        b0 = (double) ( rect.left() );
        b1 = (double) ( rect.width() )/( PS.YGraphMax() - PS.YGraphMin() );
    }
    else
    {
        b0 = (double) ( rect.left() + rect.width() );
        b1 = (double) -1. * ( rect.width() )/( PS.YGraphMax() - PS.YGraphMin() );
    }

    i_NumOfTicks = (int) round( ( PS.YGraphMax() - PS.YGraphMin() ) / PS.YTickmarkSpacing() );

// **********************************************************************************************

    X.clear();
    Xm.clear();

    for ( int i=0; i<=i_NumOfTicks; i++ )
        X.append( (int) round( b0 + ( PS.YGraphMin() + (double) i*PS.YTickmarkSpacing() - PS.YGraphMin() ) * b1 ) );

    if ( X.count() > 1 )
    {
        double d_MinorTickSpacing =  (double) ( X.at( 1 ) - X.at( 0 ) ) / (double) PS.NumOfYMinorTicks();

        for ( int i=0; i<X.count()-1; i++ )
        {
            for ( int j=1; j<PS.NumOfYMinorTicks(); j++ )
            {
                int x = X.at( i ) + (int) round( (double) j * d_MinorTickSpacing );

                if ( ( x > rect.left() ) && ( x < rect.right() ) )
                    Xm.append( x );
            }
        }
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::calcYTicksPositionH( const QRect rect, const PlotSettings PS, QVector<int> &Y, QVector<int> &Ym )
{
    double b0 = 0.;
    double b1 = 0.;

    int    i_NumOfTicks = 0;

// **********************************************************************************************

    if ( PS.YReverseGraphRange() == false )
    {
        b0 = (double) ( rect.top() );
        b1 = (double) ( rect.height() )/( PS.YGraphMax() - PS.YGraphMin() );
    }
    else
    {
        b0 = (double) ( rect.top() + rect.height() );
        b1 = (double) -1. * ( rect.height() )/( PS.YGraphMax() - PS.YGraphMin() );
    }

    i_NumOfTicks = (int) round( ( PS.YGraphMax() - PS.YGraphMin() ) / PS.YTickmarkSpacing() );

// **********************************************************************************************

    Y.clear();
    Ym.clear();

    for ( int i=0; i<=i_NumOfTicks; i++ )
        Y.append( (int) round( b0 + ( PS.YGraphMin() + (double) i*PS.YTickmarkSpacing() - PS.YGraphMin() ) * b1 ) );

    if ( Y.count() > 1 )
    {
        double d_MinorTickSpacing =  (double) ( Y.at( 1 ) - Y.at( 0 ) ) / (double) PS.NumOfYMinorTicks();

        for ( int i=0; i<Y.count()-1; i++ )
        {
            for ( int j=1; j<PS.NumOfYMinorTicks(); j++ )
            {
                int y = Y.at( i ) + (int) round( (double) j * d_MinorTickSpacing );

                if ( ( y > rect.top() ) && ( y < rect.bottom() ) )
                    Ym.append( y );
            }
        }
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-01-15

double RenderArea::round( double r )
{
    return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-01-15

void RenderArea::calcPointCoordinatesNumericV( const int XAxisParameterID, const int YAxisParameterID, const bool b_XReverseGraphRange, QVector<PlotSettings> &v_PS, const QVector<DataItem> &v_Data, QVector<QPointF> &v_P )
{
    QRect rect = v_PS.at( YAxisParameterID ).DiagramRect();

    int    s   = v_PS.at( XAxisParameterID ).StartPos();
    int    e   = s + v_PS.at( XAxisParameterID ).DataCount();

    int    j   = v_PS.at( YAxisParameterID ).StartPos();

    int    k   = 0;
    int    k0  = v_P.count();

    double a0  = 0.;
    double a1  = 0.;
    double a   = 0.;

    double b0  = 0.;
    double b1  = 0.;
    double b   = 0.;

    if ( b_XReverseGraphRange == true )
    {
        a0  = (double) ( rect.top() + 1 );
        a1  = (double) ( rect.height() - 1 )/( v_PS.at( XAxisParameterID ).XGraphMax() - v_PS.at( XAxisParameterID ).XGraphMin() );
    }
    else
    {
        a0  = (double) ( rect.top() + rect.height() - 1 );
        a1  = (double) -1 * ( rect.height() - 1 )/( v_PS.at( XAxisParameterID ).XGraphMax() - v_PS.at( XAxisParameterID ).XGraphMin() );
    }

    if ( v_PS.at( YAxisParameterID ).YReverseGraphRange() == false )
    {
        b0  = (double) ( rect.left() + 1 );
        b1  = (double) ( rect.width() - 1 )/( v_PS.at( YAxisParameterID ).YGraphMax() - v_PS.at( YAxisParameterID ).YGraphMin() );
    }
    else
    {
        b0  = (double) ( rect.left() + rect.width() - 1 );
        b1  = (double) -1. * ( rect.width() - 1 )/( v_PS.at( YAxisParameterID ).YGraphMax() - v_PS.at( YAxisParameterID ).YGraphMin() );
    }

// **********************************************************************************************

    for ( int i=s; i<e; i++ )
    {
        if ( ( v_Data.at( i ).Status() == _OK_ ) && ( v_Data.at( j ).Status() == _OK_ ) )
        {
            a = a0 + ( v_Data.at( i ).Value() - v_PS.at( XAxisParameterID ).XGraphMin() ) * a1;
            b = b0 + ( v_Data.at( j ).Value() - v_PS.at( YAxisParameterID ).YGraphMin() ) * b1;

            v_P.append( QPointF( b, a ) );

            ++k;
        }

        ++j;
    }

// **********************************************************************************************

    if ( k > 1 )
    {
        if ( v_PS.at ( YAxisParameterID ).drawYRefline() == true )
            b = b0 + ( v_PS.at( YAxisParameterID ).YRefline() - v_PS.at( YAxisParameterID ).YGraphMin() ) * b1;
        else
            b = b0 - 1;

        v_P.append( QPointF( b, v_P.at( k0+k-1 ).y() ) );
        v_P.append( QPointF( b, v_P.at( k0 ).y() ) );
        v_P.append( QPointF( v_P.at( k0 ).x(), v_P.at( k0 ).y() ) );

        k += 3;
    }

// **********************************************************************************************

    v_PS[YAxisParameterID].setNumOfPointsNumeric( k );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-01-15

void RenderArea::calcPointCoordinatesTextV( const int XAxisParameterID, const int YAxisParameterID, const bool b_XReverseGraphRange, QVector<PlotSettings> &v_PS, const QVector<DataItem> &v_Data, QVector<QPointF> &v_P, QStringList &sl_Data )
{
    QRect rect = v_PS.at( YAxisParameterID ).DiagramRect();

    int    s   = v_PS.at( XAxisParameterID ).StartPos();
    int    e   = s + v_PS.at( XAxisParameterID ).DataCount();

    int    j   = v_PS.at( YAxisParameterID ).StartPos();

    int    k   = 0;

    double a0  = 0.;
    double a1  = 0.;
    double a   = 0.;

    double b0  = 0.;
    double b1  = 0.;
    double b   = 0.;

// **********************************************************************************************

    if ( b_XReverseGraphRange == true )
    {
        a0  = (double) ( rect.top() + 1 );
        a1  = (double) ( rect.height() - 1 )/( v_PS.at( XAxisParameterID ).XGraphMax() - v_PS.at( XAxisParameterID ).XGraphMin() );
    }
    else
    {
        a0  = (double) ( rect.top() + rect.height() - 1 );
        a1  = (double) -1 * ( rect.height() - 1 )/( v_PS.at( XAxisParameterID ).XGraphMax() - v_PS.at( XAxisParameterID ).XGraphMin() );
    }

    b0  = (double) ( rect.left() + 1 );
    b1  = (double) ( rect.width() - 1 )/( v_PS.at( YAxisParameterID ).YGraphMax() - v_PS.at( YAxisParameterID ).YGraphMin() );

    b = b0 + 10 + ( v_PS.at( YAxisParameterID ).YRefline() - v_PS.at( YAxisParameterID ).YGraphMin() ) * b1;

// **********************************************************************************************

    for ( int i=s; i<e; i++ )
    {
        if ( ( v_Data.at( i ).Status() == _OK_ ) && ( v_Data.at( j ).Text().isEmpty() == false ) )
        {
            a = a0 + ( v_Data.at( i ).Value() - v_PS.at( XAxisParameterID ).XGraphMin() ) * a1;

            v_P.append( QPointF( b, a ) );

            sl_Data.append( v_Data.at( j ).Text() );

            ++k;
        }

        ++j;
    }

// **********************************************************************************************

    v_PS[YAxisParameterID].setNumOfPointsDataText( k );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2013-06-11

void RenderArea::calcPointCoordinatesNumericH( const int XAxisParameterID, const int YAxisParameterID, const bool b_XReverseGraphRange, QVector<PlotSettings> &v_PS, const QVector<DataItem> &v_Data, QVector<QPointF> &v_P )
{
    QRect rect = v_PS.at( YAxisParameterID ).DiagramRect();

    int    s   = v_PS.at( XAxisParameterID ).StartPos();
    int    e   = s + v_PS.at( XAxisParameterID ).DataCount();

    int    j   = v_PS.at( YAxisParameterID ).StartPos();

    int    k   = 0;
    int    k0  = v_P.count();

    double a0  = 0.;
    double a1  = 0.;
    double a   = 0.;

    double b0  = 0.;
    double b1  = 0.;
    double b   = 0.;

// **********************************************************************************************

    if ( b_XReverseGraphRange == false )
    {
        a0  = (double) ( rect.left() + 1 );
        a1  = (double) ( rect.width() - 1 )/( v_PS.at( XAxisParameterID ).XGraphMax() - v_PS.at( XAxisParameterID ).XGraphMin() );
    }
    else
    {
        a0  = (double) ( rect.left() + rect.width() - 1 );
        a1  = (double) -1. * ( rect.width() - 1 )/( v_PS.at( XAxisParameterID ).XGraphMax() - v_PS.at( XAxisParameterID ).XGraphMin() );
    }

    if ( v_PS.at( YAxisParameterID ).YReverseGraphRange() == true )
    {
        b0  = (double) ( rect.top() + 1 );
        b1  = (double) ( rect.height() - 1 )/( v_PS.at( YAxisParameterID ).YGraphMax() - v_PS.at( YAxisParameterID ).YGraphMin() );
    }
    else
    {
        b0  = (double) ( rect.top() + rect.height() - 1 );
        b1  = (double) -1 * ( rect.height() - 1 )/( v_PS.at( YAxisParameterID ).YGraphMax() - v_PS.at( YAxisParameterID ).YGraphMin() );
    }

// **********************************************************************************************

    for ( int i=s; i<e; i++ )
    {
        if ( ( v_Data.at( i ).Status() == _OK_ ) && ( v_Data.at( j ).Status() == _OK_ ) )
        {
            a = a0 + ( v_Data.at( i ).Value() - v_PS.at( XAxisParameterID ).XGraphMin() ) * a1;
            b = b0 + ( v_Data.at( j ).Value() - v_PS.at( YAxisParameterID ).YGraphMin() ) * b1;

            v_P.append( QPointF( a, b ) );

            ++k;
        }

        ++j;
    }

// **********************************************************************************************

    if ( k > 1 )
    {
        if ( v_PS.at ( YAxisParameterID ).drawYRefline() == true )
            b = b0 + ( v_PS.at( YAxisParameterID ).YRefline() - v_PS.at( YAxisParameterID ).YGraphMin() ) * b1;
        else
            b = b0 + 2;

        v_P.append( QPointF( v_P.at( k0+k-1 ).x(), b ) );
        v_P.append( QPointF( v_P.at( k0 ).x(), b ) );
        v_P.append( QPointF( v_P.at( k0 ).x(), v_P.at( k0 ).y() ) );

        k += 3;
    }

// **********************************************************************************************

    v_PS[YAxisParameterID].setNumOfPointsNumeric( k );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2013-06-11

void RenderArea::calcPointCoordinatesTextH( const int XAxisParameterID, const int YAxisParameterID, const bool b_XReverseGraphRange, QVector<PlotSettings> &v_PS, const QVector<DataItem> &v_Data, QVector<QPointF> &v_P, QStringList &sl_Data )
{
    QRect rect = v_PS.at( YAxisParameterID ).DiagramRect();

    int    s   = v_PS.at( XAxisParameterID ).StartPos();
    int    e   = s + v_PS.at( XAxisParameterID ).DataCount();

    int    j   = v_PS.at( YAxisParameterID ).StartPos();

    int    k   = 0;

    double a0  = 0.;
    double a1  = 0.;
    double a   = 0.;

    double b0  = 0.;
    double b1  = 0.;
    double b   = 0.;

// **********************************************************************************************

    if ( b_XReverseGraphRange == false )
    {
        a0  = (double) ( rect.left() + 1 );
        a1  = (double) ( rect.width() - 1 )/( v_PS.at( XAxisParameterID ).XGraphMax() - v_PS.at( XAxisParameterID ).XGraphMin() );
    }
    else
    {
        a0  = (double) ( rect.left() + rect.width() - 1 );
        a1  = (double) -1. * ( rect.width() - 1 )/( v_PS.at( XAxisParameterID ).XGraphMax() - v_PS.at( XAxisParameterID ).XGraphMin() );
    }

    b0  = (double) ( rect.top() + 1 );
    b1  = (double) ( rect.height() - 1 )/( v_PS.at( YAxisParameterID ).YGraphMax() - v_PS.at( YAxisParameterID ).YGraphMin() );

//  b = b0 + 10 + ( v_PS.at( YAxisParameterID ).YRefline() - v_PS.at( YAxisParameterID ).YGraphMin() ) * b1;
    b = b0 + ( v_PS.at( YAxisParameterID ).YGraphMax() - v_PS.at( YAxisParameterID ).YGraphMin() )/2. * b1;

// **********************************************************************************************

    for ( int i=s; i<e; i++ )
    {
        if ( ( v_Data.at( i ).Status() == _OK_ ) && ( v_Data.at( j ).Text().isEmpty() == false ) )
        {
            a = a0 + ( v_Data.at( i ).Value() - v_PS.at( XAxisParameterID ).XGraphMin() ) * a1;

            v_P.append( QPointF( a, b ) );

            sl_Data.append( v_Data.at( j ).Text() );

            ++k;
        }

        ++j;
    }

// **********************************************************************************************

    v_PS[YAxisParameterID].setNumOfPointsDataText( k );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-02-14

int RenderArea::getNumberOfVisibleParameter( const QVector<int> v_PP )
{
    int i_NumOfVisibleParameter = 0;

    for ( int i=1; i<v_PP.count(); i++ )
    {
        if ( v_PP.at( i ) > -1 )
            ++i_NumOfVisibleParameter;
    }

    return( i_NumOfVisibleParameter );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2010-02-14

int RenderArea::getLastVisibleParameter( const QVector<int> v_PP )
{
    for ( int i=v_PP.count()-1; i>0; i-- )
    {
        if ( v_PP.at( i ) > -1 )
            return( i );
    }

    return( -1 );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

int RenderArea::calcMaxScaleWidth( QPainter &painter, const QVector<PlotSettings> v_PS, const QVector<int> v_PP )
{
    int i_maxScaleWidth = 0;

    for ( int i=1; i<v_PS.count(); i++ )
    {
        if ( v_PP.at( i ) > -1 )
        {
            QString s_Text = QString( "%1" ).arg( v_PS.at(i).YGraphMax() + (double) v_PS.at(i).YTickmarkSpacing() );
            i_maxScaleWidth = qMax( i_maxScaleWidth, getTextWidth( painter, HeaderTextFont(), PointSizeName(), _NORMAL_, s_Text ) );
        }
    }

    return( i_maxScaleWidth );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

QString RenderArea::buildDateTimeString( const int i_Format, const double d_Value )
{
    int     i_JulianDay = (int) d_Value;
    int     i_Secs      = (int) ( (d_Value - (double) i_JulianDay) * 86400. );

    QString s_DateTime  = "";

    QDate  date         = QDate().fromJulianDay( i_JulianDay );
    QTime  time( 0, 0, 0 );

// **********************************************************************************************

    // const int _FORMATISODATETIME_         = 0;
    // const int _FORMATYEAR_                = 1;
    // const int _FORMATYEARMONTH_           = 2;
    // const int _FORMATISODATE_             = 3;
    // const int _FORMATISODATETIMESECS_     = 4;

    switch( i_Format )
    {
    case _FORMATYEAR_ :
        s_DateTime = date.toString( "yyyy" );
        break;

    case _FORMATYEARMONTH_ :
        s_DateTime = date.toString( "yyyy-MM" );
        break;

    case _FORMATISODATE_ :
        s_DateTime = date.toString( Qt::ISODate );
        break;

    case _FORMATISODATETIME_ :
        s_DateTime = date.toString( Qt::ISODate ) + tr( "T" ) + time.addSecs( i_Secs ).toString( "hh:mm" );
        break;

    case _FORMATISODATETIMESECS_ :
        s_DateTime = date.toString( Qt::ISODate ) + tr( "T" ) + time.addSecs( i_Secs ).toString( "hh:mm:ss" );
        break;

    default:
        s_DateTime = date.toString( Qt::ISODate ) + tr( "T" ) + time.addSecs( i_Secs ).toString( "hh:mm" );
        break;
    }

    return ( s_DateTime );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::buildScaleLabelH( QPainter &painter, const QRect rect, const PlotSettings PS, const int i_DiagramDistance, const QVector<int> Y, QVector<ScaleContainer> &ScaleLabel )
{
    QString s_Text           = "";

    int     i_TextHeight     = getTextHeight( painter, HeaderTextFont(), PointSizeScale(), _NORMAL_, tr( "gG" ) );
    int     i_TextWidthMin   = getTextWidth( painter, HeaderTextFont(), PointSizeScale(), _NORMAL_, QString( "%1" ).arg( PS.YGraphMin(), 0, 'f', PS.YnFrac() ) );
    int     i_TextWidthMax   = getTextWidth( painter, HeaderTextFont(), PointSizeScale(), _NORMAL_, QString( "%1" ).arg( PS.YGraphMax(), 0, 'f', PS.YnFrac() ) );
    int     i_TextPosX       = i_DiagramDistance;

// **********************************************************************************************

    i_TextWidthMax = qMax( i_TextWidthMin, i_TextWidthMax );
    i_TextPosX     = rect.left() - i_TextWidthMax - PS.YTickmarkLength();

    for ( int i=0; i<Y.count(); i++ )
    {
        s_Text = QString( "%1" ).arg( PS.YGraphMax() - (double) i*PS.YTickmarkSpacing(), 0, 'f', PS.YnFrac() );
        ScaleLabel.append( ScaleContainer( s_Text, i_TextHeight, i_TextWidthMax, i_TextPosX, Y.at( i ) - i_TextHeight/2, i_TextWidthMax ) );
    }

    for ( int i=0; i<ScaleLabel.count(); i++ )
    {
        if ( ( rect.top() <= Y.at( i ) ) && ( Y.at( i ) <= rect.bottom() ) )
            ScaleLabel[i].setDraw( true );
    }

    return;
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::buildScaleLabelV( QPainter &painter, const QRect rect, const PlotSettings PS, const int i_DiagramDistance, const QVector<int> X, QVector<ScaleContainer> &ScaleLabel )
{
    QString s_Text           = "";

    int     i_TextWidth      = 0;
    int     i_TextWidthTotal = 0;

    int     i_TextHeight     = getTextHeight( painter, HeaderTextFont(), PointSizeScale(), _NORMAL_, tr( "gG" ) );
    int     i_TextWidthMin   = getTextWidth( painter, HeaderTextFont(), PointSizeScale(), _NORMAL_, QString( "%1" ).arg( PS.YGraphMin(), 0, 'f', PS.YnFrac() ) );
    int     i_TextWidthMax   = getTextWidth( painter, HeaderTextFont(), PointSizeScale(), _NORMAL_, QString( "%1" ).arg( PS.YGraphMax(), 0, 'f', PS.YnFrac() ) );
    int     i_TextPosY       = rect.top() - PS.YTickmarkLength() - i_TextHeight - 5;

// **********************************************************************************************

    i_TextWidthMax = qMax( i_TextWidthMin, i_TextWidthMax );

// **********************************************************************************************
// first

    if ( PS.YReverseGraphRange() == true )
    {
        s_Text = QString( "%1" ).arg( PS.YGraphMax(), 0, 'f', PS.YnFrac() );

        i_TextWidth = getTextWidth( painter, HeaderTextFont(), PointSizeScale(), _NORMAL_, s_Text );

        if ( i_DiagramDistance > i_TextWidthMax )
        {
            ScaleLabel.append( ScaleContainer( s_Text, i_TextHeight, i_TextWidth, X.last() - i_TextWidth/2, i_TextPosY ) );
            i_TextWidthTotal += i_TextWidth/2 + MarginScale();
        }
        else
        {
            ScaleLabel.append( ScaleContainer( s_Text, i_TextHeight, i_TextWidth, X.last() + MarginScale(), i_TextPosY ) );
            i_TextWidthTotal += i_TextWidth + MarginScale();
        }
    }
    else
    {
        s_Text = QString( "%1" ).arg( PS.YGraphMin(), 0, 'f', PS.YnFrac() );

        i_TextWidth = getTextWidth( painter, HeaderTextFont(), PointSizeScale(), _NORMAL_, s_Text );

        if ( i_DiagramDistance > i_TextWidthMax )
        {
            ScaleLabel.append( ScaleContainer( s_Text, i_TextHeight, i_TextWidth, X.first() - i_TextWidth/2, i_TextPosY ) );
            i_TextWidthTotal += i_TextWidth/2 + MarginScale();
        }
        else
        {
            ScaleLabel.append( ScaleContainer( s_Text, i_TextHeight, i_TextWidth, X.first() + MarginScale(), i_TextPosY ) );
            i_TextWidthTotal += i_TextWidth + MarginScale();
        }
    }

// **********************************************************************************************
// all

    if ( PS.YReverseGraphRange() == true )
    {
        for( int i=X.count()-2; i>0; i-- )
        {
            s_Text            = QString( "%1" ).arg( PS.YGraphMin() + i*PS.YTickmarkSpacing(), 0, 'f', PS.YnFrac() );
            i_TextWidth       = getTextWidth( painter, HeaderTextFont(), PointSizeScale(), _NORMAL_, s_Text );
            i_TextWidthTotal += i_TextWidth + 2*MarginScale();

            ScaleLabel.append( ScaleContainer( s_Text, i_TextHeight, i_TextWidth, X.at( i ) - i_TextWidth/2, i_TextPosY ) );
        }
    }
    else
    {
        for( int i=1; i<X.count()-1; i++ )
        {
            s_Text            = QString( "%1" ).arg( PS.YGraphMin() + i*PS.YTickmarkSpacing(), 0, 'f', PS.YnFrac() );
            i_TextWidth       = getTextWidth( painter, HeaderTextFont(), PointSizeScale(), _NORMAL_, s_Text );
            i_TextWidthTotal += i_TextWidth + 2*MarginScale();

            ScaleLabel.append( ScaleContainer( s_Text, i_TextHeight, i_TextWidth, X.at( i ) - i_TextWidth/2, i_TextPosY ) );
        }
    }

// **********************************************************************************************
// last

    if ( PS.YReverseGraphRange() == true )
    {
        s_Text = QString( "%1" ).arg( PS.YGraphMin(), 0, 'f', PS.YnFrac() );

        i_TextWidth = getTextWidth( painter, HeaderTextFont(), PointSizeScale(), _NORMAL_, s_Text );

        if ( i_DiagramDistance > i_TextWidthMax )
        {
            ScaleLabel.append( ScaleContainer( s_Text, i_TextHeight, i_TextWidth, X.first() - i_TextWidth/2, i_TextPosY ) );
            i_TextWidthTotal += i_TextWidth/2 + MarginScale();
        }
        else
        {
            ScaleLabel.append( ScaleContainer( s_Text, i_TextHeight, i_TextWidth, X.first() - i_TextWidth - MarginScale(), i_TextPosY ) );
            i_TextWidthTotal += i_TextWidth + MarginScale();
        }
    }
    else
    {
        s_Text = QString( "%1" ).arg( PS.YGraphMax(), 0, 'f', PS.YnFrac() );

        i_TextWidth = getTextWidth( painter, HeaderTextFont(), PointSizeScale(), _NORMAL_, s_Text );

        if ( i_DiagramDistance > i_TextWidthMax )
        {
            ScaleLabel.append( ScaleContainer( s_Text, i_TextHeight, i_TextWidth, X.last() - i_TextWidth/2, i_TextPosY ) );
            i_TextWidthTotal += i_TextWidth/2 + MarginScale();
        }
        else
        {
            ScaleLabel.append( ScaleContainer( s_Text, i_TextHeight, i_TextWidth, X.last() - i_TextWidth - MarginScale(), i_TextPosY ) );
            i_TextWidthTotal += i_TextWidth + MarginScale();
        }
    }

// **********************************************************************************************

    if ( i_TextWidthTotal < rect.width() )
    {
        for ( int i=0; i<X.count(); i++ )
            ScaleLabel[i].setDraw( true );

        if ( ScaleLabel.first().x() + ScaleLabel.first().width() + 2*MarginScale() > ScaleLabel.at( 1 ).x() )
            ScaleLabel[1].setDraw( false );

        if ( ScaleLabel.at( X.count()-2 ).x() + ScaleLabel.at( X.count()-2 ).width() + 2*MarginScale() > ScaleLabel.last().x() )
            ScaleLabel[X.count()-2].setDraw( false );
    }
    else
    {
        if ( ScaleLabel.last().width() + 2*MarginScale() < rect.width() )
           ScaleLabel[X.count()-1].setDraw( true );

        if ( ScaleLabel.first().x() + ScaleLabel.first().width() + 2*MarginScale() < ScaleLabel.last().x() )
            ScaleLabel[0].setDraw( true );

        int mid = X.count()/2;

        if ( ( ScaleLabel.first().x() + ScaleLabel.first().width() + 2*MarginScale() < ScaleLabel.at( mid ).x() ) && ( ScaleLabel.at( mid ).x() + ScaleLabel.at( mid ).width() + 2*MarginScale() < ScaleLabel.last().x() )  )
          ScaleLabel[mid].setDraw( true );
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawXAxis( QPainter &painter, const PlotSettings PS, QPoint Point, const int i_DiagramWidth, const int i_Orientation )
{
    QString s_XAxisName = "";

    int i_NameHeight     = 0;
    int i_NameWidth      = 0;
    int i_UnitWidth      = 0;
    int i_ScaleHeight    = 0;

// **********************************************************************************************

    switch ( i_Orientation )
    {
    case 0:
        s_XAxisName = PS.ParameterName();

        if ( PS.ParameterUnit().isEmpty() == false )
            s_XAxisName.append( tr( " " ) + PS.ParameterUnit() );

        i_NameHeight = getTextHeight( painter, HeaderTextFont(), PointSizeName(), _BOLD_, tr( "gG" ) );
        i_NameWidth  = getTextWidth( painter, HeaderTextFont(), PointSizeName(), _BOLD_, s_XAxisName );

        drawText( painter, QRect( Point.x() + i_DiagramWidth/2 - ( i_NameWidth + i_UnitWidth )/2, Point.y(), i_NameWidth, i_NameHeight ), HeaderTextFont(), HeaderTextColor(), PointSizeName(), _BOLD_, Qt::AlignLeft, 0, s_XAxisName );
        break;

    case 90:
        i_ScaleHeight = getTextHeight( painter, HeaderTextFont(), PointSizeScale(), _NORMAL_, tr( "gG" ) );
        i_NameHeight  = getTextHeight( painter, HeaderTextFont(), PointSizeName(), _BOLD_, tr( "gG" ) );
        i_NameWidth   = getTextWidth( painter, HeaderTextFont(), PointSizeName(), _BOLD_, PS.ParameterName() );

        if ( PS.ParameterUnit().isEmpty() == false )
            i_UnitWidth  = getTextWidth( painter, HeaderTextFont(), PointSizeName(), _NORMAL_, tr( "  " ) + PS.ParameterUnit() );

        drawText( painter, QRect( Point.x(), Point.y() + ( i_NameWidth + i_UnitWidth )/2 - PS.YTickmarkLength() - i_ScaleHeight, i_NameWidth, i_NameHeight ), HeaderTextFont(), HeaderTextColor(), PointSizeName(), _BOLD_, Qt::AlignLeft, 90, PS.ParameterName() );

        if ( PS.ParameterUnit().isEmpty() == false )
            drawText( painter, QRect( Point.x(), Point.y() + ( i_NameWidth + i_UnitWidth )/2 - i_NameWidth - PS.YTickmarkLength() - i_ScaleHeight, i_UnitWidth, i_NameHeight ), HeaderTextFont(), HeaderTextColor(), PointSizeName(), _NORMAL_, Qt::AlignLeft, 90, tr( "  " ) + PS.ParameterUnit() );
        break;
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawParameter( QPainter &painter, const PlotSettings PS, QPoint Point, const int i_DiagramWidth, const int i_Align, const int i_Orientation )
{
    int i_NameHeight     = getTextHeight( painter, HeaderTextFont(), PointSizeName(), _BOLD_, tr( "gG" ) );
    int i_NameWidth      = getTextWidth( painter, HeaderTextFont(), PointSizeName(), _BOLD_, PS.ParameterName() );
    int i_UnitHeight     = 0;
    int i_UnitWidth      = 0;
    int i_ParameterWidth = 0;
    int i_ScaleHeight    = 0;

    QString s_Parameter  = "";

// **********************************************************************************************

    switch ( i_Orientation )
    {
    case 0:
        drawText( painter, QRect( Point.x(), Point.y(), i_DiagramWidth, i_NameHeight ), HeaderTextFont(), HeaderTextColor(), PointSizeName(), _BOLD_, Qt::AlignCenter, 0, PS.ParameterName() );

        if ( PS.ParameterUnit().isEmpty() == false )
        {
            i_UnitHeight = getTextHeight( painter, HeaderTextFont(), PointSizeUnit(), _NORMAL_, tr( "gG" ) );
            i_UnitWidth  = getTextWidth( painter, HeaderTextFont(), PointSizeUnit(), _NORMAL_, tr( "  " ) + PS.ParameterUnit() );

            drawText( painter, QRect( Point.x(), Point.y() + i_NameHeight + i_UnitHeight/2, i_DiagramWidth, i_UnitHeight ), HeaderTextFont(), HeaderTextColor(), PointSizeUnit(), _NORMAL_, Qt::AlignCenter, 0, PS.ParameterUnit() );
        }
        break;

    case 45:
        s_Parameter      = PS.ParameterName() + tr( "  " ) + PS.ParameterUnit();
        i_ParameterWidth = getTextWidth( painter, HeaderTextFont(), PointSizeName(), _BOLD_, s_Parameter );
        i_ScaleHeight    = getTextHeight( painter, HeaderTextFont(), PointSizeScale(), _NORMAL_, tr( "gG" ) );

        switch ( i_Align )
        {
        case Qt::AlignLeft:
            drawText( painter, QRect( Point.x(), Point.y() - PS.YTickmarkLength() - i_ScaleHeight, i_ParameterWidth, i_NameHeight ), HeaderTextFont(), HeaderTextColor(), PointSizeName(), _BOLD_, Qt::AlignLeft, 45, s_Parameter );
            break;

        case Qt::AlignCenter:
            drawText( painter, QRect( Point.x() + i_ParameterWidth/10, Point.y() + i_ParameterWidth/2 - PS.YTickmarkLength() - i_ScaleHeight, i_ParameterWidth, i_NameHeight ), HeaderTextFont(), HeaderTextColor(), PointSizeName(), _BOLD_, Qt::AlignLeft, 45, PS.ParameterName() );
            break;
        }
        break;

    case 90:
        i_ScaleHeight = getTextHeight( painter, HeaderTextFont(), PointSizeScale(), _NORMAL_, tr( "gG" ) );

        if ( PS.ParameterUnit().isEmpty() == false )
        {
            i_UnitHeight = getTextHeight( painter, HeaderTextFont(), PointSizeName(), _NORMAL_, tr( "gG" ) );
            i_UnitWidth  = getTextWidth( painter, HeaderTextFont(), PointSizeName(), _NORMAL_, tr( "  " ) + PS.ParameterUnit() );
        }

        switch ( i_Align )
        {
        case Qt::AlignLeft:
            drawText( painter, QRect( Point.x(), Point.y() - PS.YTickmarkLength() - i_ScaleHeight, i_NameWidth, i_NameHeight ), HeaderTextFont(), HeaderTextColor(), PointSizeName(), _BOLD_, Qt::AlignLeft, 90, PS.ParameterName() );

            if ( PS.ParameterUnit().isEmpty() == false )
                drawText( painter, QRect( Point.x(), Point.y() - i_NameWidth - PS.YTickmarkLength() - i_ScaleHeight, i_UnitWidth, i_NameHeight ), HeaderTextFont(), HeaderTextColor(), PointSizeName(), _NORMAL_, Qt::AlignLeft, 90, tr( "  " ) + PS.ParameterUnit() );
            break;

        case Qt::AlignCenter:
            drawText( painter, QRect( Point.x(), Point.y() + ( i_NameWidth + i_UnitWidth )/2 - PS.YTickmarkLength() - i_ScaleHeight, i_NameWidth, i_NameHeight ), HeaderTextFont(), HeaderTextColor(), PointSizeName(), _BOLD_, Qt::AlignLeft, 90, PS.ParameterName() );

            if ( PS.ParameterUnit().isEmpty() == false )
                drawText( painter, QRect( Point.x(), Point.y() + ( i_NameWidth + i_UnitWidth )/2 - i_NameWidth - PS.YTickmarkLength() - i_ScaleHeight, i_UnitWidth, i_NameHeight ), HeaderTextFont(), HeaderTextColor(), PointSizeName(), _NORMAL_, Qt::AlignLeft, 90, tr( "  " ) + PS.ParameterUnit() );
            break;
        }
        break;
    }
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::drawText( QPainter &painter, const QRect rect, const QFont FontIn, const QColor Color, const int i_PointSize, const int i_Face, const int i_Flags, const int i_Orientation, const QString &s_Text )
{
    QFont Font = FontIn;
    bool  test = false;

// **********************************************************************************************

    painter.save();

    if ( i_Face == _BOLD_ )
        Font.setBold( true );
    else
        Font.setBold( false );

    if ( i_PointSize > 5 )
        Font.setPointSize( i_PointSize );
    else
        Font.setPointSize( 5 );

    painter.setFont( Font );
    painter.setPen( Color );
    painter.setBrush( Qt::NoBrush );

    painter.translate( rect.topLeft() );
    painter.rotate( -i_Orientation );

    switch ( i_Flags )
    {
    case Qt::AlignRight:
        painter.drawText( -2, 0, rect.width()+2, rect.height()+1, i_Flags, s_Text );
        break;

    case Qt::AlignCenter:
        painter.drawText( -1, 0, rect.width()+2, rect.height()+1, i_Flags, s_Text );
        break;

    default:
        painter.drawText( 0, 0, rect.width()+2, rect.height()+1, i_Flags, s_Text );
        break;
    }

    if ( test == true )
    {
        switch ( i_Flags )
        {
        case Qt::AlignRight:
            painter.drawRect( -2, 0, rect.width()+2, rect.height()+1 );
            break;

        case Qt::AlignCenter:
            painter.drawRect( -1, 0, rect.width()+2, rect.height()+1 );
            break;

        default:
            painter.drawRect( 0, 0, rect.width()+2, rect.height()+1 );
            break;
        }
    }

    painter.restore();
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

int RenderArea::getMaxParameterWidth( QPainter &painter, const bool b_NamePlusUnit, const QFont Font, const int i_PointSize, const int i_Face, const QVector<PlotSettings> v_PS, const QVector<int> v_PP )
{
    QString s_Parameter               = "";
    QString s_Unit                    = "";
    QString s_ParameterWithMaxLength  = "";
    QString s_UnitWithMaxLength       = "";

    QString s_Text                    = "";

// **********************************************************************************************

    for ( int i=1; i<v_PP.count(); i++ )
    {
        if ( b_NamePlusUnit == true )
        {
            if ( v_PP.at( i ) > 0 )
            {
                s_Parameter = v_PS.at( v_PP.at( i ) ).ParameterName();

                if (  v_PS.at( v_PP.at( i ) ).ParameterUnit().isEmpty() == false )
                    s_Parameter.append( tr( " ") + v_PS.at( v_PP.at( i ) ).ParameterUnit() );

                if ( s_ParameterWithMaxLength.length() < s_Parameter.length() )
                    s_ParameterWithMaxLength = s_Parameter;
            }
        }
        else
        {
            if ( v_PP.at( i ) > 0 )
            {
                s_Parameter = v_PS.at( v_PP.at( i ) ).ParameterName();
                s_Unit      = v_PS.at( v_PP.at( i ) ).ParameterUnit();

                if ( s_ParameterWithMaxLength.length() < s_Parameter.length() )
                    s_ParameterWithMaxLength = s_Parameter;

                if ( s_UnitWithMaxLength.length() < s_Unit.length() )
                    s_UnitWithMaxLength = s_Unit;
            }
        }
    }

// **********************************************************************************************

    s_Text = s_ParameterWithMaxLength;

    if ( s_Text.length() < s_UnitWithMaxLength.length() )
        s_Text = s_UnitWithMaxLength;

    return( getTextWidth( painter, Font, i_PointSize, i_Face, s_Text ) );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

int RenderArea::getTextWidth( QPainter &painter, const QFont FontIn, const int i_PointSize, const int i_Face, const QString &s_Text )
{
    QFont Font        = FontIn;
    int   i_TextWidth = 0;

    painter.save();

    Font.setPointSize( i_PointSize );

    if ( i_Face == _BOLD_ )
        Font.setBold( true );
    else
        Font.setBold( false );

    painter.setFont( Font );

    QFontMetrics FontMetrics( Font );

    i_TextWidth = FontMetrics.boundingRect( s_Text ).width();

    painter.restore();

    return( i_TextWidth );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

int RenderArea::getDateTimeWidth( QPainter &painter, const QFont Font, const int i_PointSize, const int i_Face, int i_DateTimeFormat )
{
    QString s_DateTime = "";

    // const int _FORMATISODATETIME_         = 0;
    // const int _FORMATYEAR_                = 1;
    // const int _FORMATYEARMONTH_           = 2;
    // const int _FORMATISODATE_             = 3;
    // const int _FORMATISODATETIMESECS_     = 4;

    switch ( i_DateTimeFormat )
    {
    case _FORMATYEAR_ :
        s_DateTime = "2013";
        break;
    case _FORMATYEARMONTH_ :
        s_DateTime = "2013-10";
        break;
    case _FORMATISODATE_ :
        s_DateTime = "2013-10-23";
        break;
    case _FORMATISODATETIMESECS_ :
        s_DateTime = "2013-12-31T23:59:59";
        break;
    default: // _FORMATISODATETIME_
        s_DateTime = "2013-12-31T23:59";
        break;
    }

    return( getTextWidth( painter, Font, i_PointSize, i_Face, s_DateTime ) );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

int RenderArea::getTextWidth( QPainter &painter, const QFont Font, const int i_PointSize, const int i_Face, const double d_Value, int i_nFrac )
{
    return( getTextWidth( painter, Font, i_PointSize, i_Face, QString( "%1" ).arg( d_Value, 0, 'f', i_nFrac ) ) );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

int RenderArea::getTextHeight( QPainter &painter, const QFont FontIn, const int i_PointSize, const int i_Face, const QString &s_Text )
{
    QFont Font = FontIn;

    painter.save();

    Font.setPointSize( i_PointSize );

    if ( i_Face == _BOLD_ )
        Font.setBold( true );
    else
        Font.setBold( false );

    painter.setFont( Font );

    QFontMetrics FontMetrics( Font );
    int i_TextHeight = FontMetrics.boundingRect( s_Text ).height();

    painter.restore();

    return( i_TextHeight );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

int RenderArea::calcNumberOfParameter( QPainter &painter, const int i_Left, const int i_Right, const int i_DiagramDistance, const int i_Width, const int i_maxNumOfParameter )
{
    int i_NumOfParameter = i_maxNumOfParameter;

    while ( ( i_NumOfParameter*( i_Width + i_DiagramDistance ) - i_DiagramDistance ) > ( painter.window().width() - i_Left - i_Right ) )
        --i_NumOfParameter;

    if ( i_NumOfParameter == i_maxNumOfParameter )
        --i_NumOfParameter;

    if ( i_NumOfParameter == 0 )
        i_NumOfParameter = 1;

    return( i_NumOfParameter );
}


// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

int RenderArea::calcDiagramHeightV( QPainter &painter, const int i_Top, const int i_Bottom )
{
    return( painter.window().height() - i_Top - i_Bottom - StatusBarHeight() );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

int RenderArea::calcDiagramHeightH( QPainter &painter, const int i_Top, const int i_Bottom, const int i_DiagramDistance, const int i_minHeight, const int i_NumOfParameter )
{
    int i_Height = i_minHeight;

    while ( ( i_NumOfParameter * ( i_Height + i_DiagramDistance ) - i_DiagramDistance ) < ( painter.window().height() - i_Top - i_Bottom - StatusBarHeight() ) )
        i_Height++;

    return( i_Height );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

int RenderArea::calcDiagramWidthV( QPainter &painter, const int i_Left, const int i_Right, const int i_DiagramDistance, const int i_minWidth, const int i_NumOfParameter )
{
    int i_Width = i_minWidth;

    while ( ( i_NumOfParameter * ( i_Width + i_DiagramDistance ) - i_DiagramDistance ) < ( painter.window().width() - i_Left - i_Right ) )
        i_Width++;

    return( i_Width );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

int RenderArea::calcDiagramWidthH( QPainter &painter, const int i_Left, const int i_Right )
{
    return( painter.window().width() - i_Left - i_Right );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

RenderArea::RenderArea( QWidget *parent ) : QWidget(parent)
{
    setBackgroundRole( QPalette::Base );
    setAutoFillBackground( true );

    setRotate( 0 );
    setScale( 1., 1. );
    setTranslate( 0, 0 );
}

 // **********************************************************************************************
 // **********************************************************************************************
 // **********************************************************************************************

 void RenderArea::transformPainter( QPainter &painter )
 {
     painter.rotate( rot );
     painter.scale( scale1, scale2 );
     painter.translate( translate1, translate2 );
 }

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

int RenderArea::getParameterID_Body( const QVector<PlotSettings> v_PS, const QVector<int> v_PP )
{
    for ( int i=1; i<v_PP.count(); i++ )
    {
        QRect rect = v_PS.at( v_PP.at( i ) ).DiagramRect();

        if ( ( rect.left() <= mlbx ) && ( mlbx <= rect.right() ) && ( rect.top() <= mlby ) && ( mlby <= rect.bottom() ) )
            return( v_PP.at( i ) );
    }

    return( -1 );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

int RenderArea::getParameterID_Header( const QVector<PlotSettings> v_PS, const QVector<int> v_PP )
{
    for ( int i=1; i<v_PP.count(); i++ )
    {
        QRect rect = v_PS.at( v_PP.at( i ) ).HeaderRect();

        if ( ( rect.left() <= mlbx ) && ( mlbx <= rect.right() ) )
            return( v_PP.at( i ) );
    }

    return( -1 );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::mousePressEvent( QMouseEvent *event )
{
    if ( event->button() == Qt::LeftButton )
         setMouseLeftButton( true, event->x(), event->y() );

    if ( event->button() == Qt::RightButton )
         setMouseRightButton( true, event->x(), event->y() );

    if ( event->button() == Qt::MidButton )
         setMouseMidButton( true, event->x(), event->y() );

    update();
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::mouseReleaseEvent ( QMouseEvent *event )
{
    if ( event->button() == Qt::LeftButton )
         setMouseLeftButton( false );

    if ( event->button() == Qt::RightButton )
         setMouseRightButton( false );

    if ( event->button() == Qt::MidButton )
         setMouseMidButton( false );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void RenderArea::resizeEvent ( QResizeEvent * event )
{
    if ( ( event->oldSize().width() != -1 ) && ( event->size() != event->oldSize() ) )
        setResizeState( true );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::doShowPlot()
{
    if ( ( gv_Data.count() > 0 ) && ( gv_PS.count() > 0 ) )
        setMainWindowWidget( gi_PlotOrientation, false );
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::doShowPlotV()
{
    if ( ( gi_PlotOrientation == _SHOWPLOTH_ ) && ( renderArea->fixedDiagramSize() == true ) )
    {
        int temp = renderArea->DiagramHeight();
        renderArea->setDiagramHeight( renderArea->DiagramWidth() );
        renderArea->setDiagramWidth( temp );
    }

    saveGraphicOptions( true );
    saveParameterOptions( true );

    gi_PlotOrientation = _SHOWPLOTV_;

    doShowPlot();
}

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

void MainWindow::doShowPlotH()
{
    if ( ( gi_PlotOrientation == _SHOWPLOTV_ ) && ( renderArea->fixedDiagramSize() == true ) )
    {
        int temp = renderArea->DiagramHeight();
        renderArea->setDiagramHeight( renderArea->DiagramWidth() );
        renderArea->setDiagramWidth( temp );
    }

    saveGraphicOptions( true );
    saveParameterOptions( true );

    gi_PlotOrientation = _SHOWPLOTH_;

    doShowPlot();
}
