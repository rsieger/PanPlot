#ifndef RENDERAREA_H
#define RENDERAREA_H

#include "Application.h"

class ScaleContainer
{
public:
    ScaleContainer( const QString &text = "", const int textHeight = 0, const int textWidth = 0, const int textPosX = 0, const int textPosY = 0, const bool textDraw = false )
                  { Text = text; Height = textHeight; Width = textWidth; X = textPosX; Y = textPosY; Draw = textDraw; }

    QString text() const { return( Text ); }
    bool    draw() const { return( Draw ); }
    int     height() const { return( Height ); }
    int     width() const { return( Width ); }
    int     x() const { return( X ); }
    int     y() const { return( Y ); }

    void setText( const QString &var ) { Text = var; }
    void setHeight( int var ) { Height = var; }
    void setWidth( int var ) { Width = var; }
    void setX( int var ) { X = var; }
    void setY( int var ) { Y = var; }
    void setPos( int var1, int var2 ) { X = var1; Y = var2; }
    void setDraw( bool var ) { Draw = var; }

private:
    QString Text;
    bool    Draw;
    int     Height;
    int     Width;
    int     X;
    int     Y;
};

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    RenderArea( QWidget *parent = 0 );

    void plotV();
    void plotH();

    void resetCount( const int val=0 ) { count = val; }

    void setRotate( const int val ) { rot = val; }
    void setScale( const double val1, const double val2 ) { scale1 = val1; scale2 = val2; }
    void setTranslate( const int val1, const int val2 ) { translate1 = val1; translate2 = val2; }
    void setMinimumSizeHint( const int val1=250, const int val2=250 ) { wx = val1; wy = val2; }

    void setParameterNameOrientation( const int val ) { parameterNameOrientation = val; }
    void setPlotOrientation( const int var ) { plotOrientation = var; }
    void setFilenamePlot( const QString& var ) { filenameplot = var; }

    void setHeaderTextFont( const QFont val ) { fontHeaderText = val; }
    void setHeaderTextColor( const QColor val ) { colorHeaderText = val; }

    void setMouseLeftButton( const bool state=false, const int x=0, const int y=0 ) { mouseLeftButtonState = state; mlbx = x; mlby = y; }
    void setMouseRightButton( const bool state=false, const int x=0, const int y=0 ) { mouseRightButtonState = state; mrbx = x; mrby = y; }
    void setMouseMidButton( const bool state=false, const int x=0, const int y=0 ) { mouseMidButtonState = state; mmbx = x; mmby = y; }
    void setResizeState( const bool state=false ) { resizeState = state; }

    void setMargin( const int val1=0, const int val2=0, const int val3=0, const int val4=0, const int val5=0 ) { marginLeft = val1; marginRight = val2; marginTop = val3; marginBottom = val4; marginScale = val5; }

    void setFixedDiagramSize( const bool val=false ) { fixeddiagramsize = val; }

    void setStatusBarHeight( const int val ) { statusBarHeight = val; }

    void setDiagramSize( const bool fds=false, const int dh=0, const int dw=0, const int dd=0 ) { diagramHeight = dh; diagramWidth  = dw; diagramDistance = dd; fixeddiagramsize = fds; }
    void setDiagramHeight( const int val ) { diagramHeight = val; }
    void setDiagramWidth( const int val ) { diagramWidth = val; }

    void setDiagramFrameWidth( const int val=1 ) { diagramFrameWidth = val; }
    void setDiagramFrameColor( const QColor val ) { colorDiagramFrame = val; }

    void setAntialiasing( const bool val=false ) { antialiasing = val; }
    void setBackgroundBrush( const QBrush val ) { brushBackground = val; }
    void setBackgroundColor( const QColor val ) { colorBackground = val; }
    void setDrawBackground( const bool val=false ) { drawbackground = val; }
    void setTickColor( const QColor TickmarkColor=Qt::black, const QColor TicklineColor=Qt::gray, const QColor MinorTicklineColor=Qt::gray ) { colorTickmark = TickmarkColor; colorTickline = TicklineColor; colorMinorTickline = MinorTicklineColor; }
    void setTickWidth( const int TickmarkWidth, const int MinorTickmarkWidth, const int TicklineWidth, const int MinorTicklineWidth ) { tickmarkWidth = TickmarkWidth,  minorTickmarkWidth = MinorTickmarkWidth, ticklineWidth = TicklineWidth, minorTicklineWidth =  MinorTicklineWidth; }
    void setXReverseGraphRange( const bool val=true ) { rxr = val; }

    void setPosDialog( const QPoint val ) { posdialog = val; }
    void setSavePlotFormat( const int val ) { saveplotformat = val; }
    void setDateTimeFormat( const int val ) { datetimeformat = val; }
    void setData( const QVector<DataItem> &Data ) { v_Data = Data; }
    void setPrameterSettings( const QVector<PlotSettings> &PS ) { v_PS = PS; }
    void setParameterPosition( QVector<int> &PP ) { v_PP = PP; }

    QVector<PlotSettings> ParameterSettings() const { return( v_PS ); }

    int StatusBarHeight() const { return( statusBarHeight ); }

    int DiagramHeight() const { return( diagramHeight ); }
    int DiagramWidth() const {  return( diagramWidth ); }
    int DiagramDistance() const { return( diagramDistance ); }
    int DiagramFrameWidth() const { return( diagramFrameWidth ); }

    int MarginLeft() const { return( marginLeft ); }
    int MarginRight() const { return( marginRight ); }
    int MarginTop() const { return( marginTop ); }
    int MarginBottom() const { return( marginBottom ); }
    int MarginScale() const { return( marginScale ); }

    int PointSizeHeader() const { return( fontHeaderText.pointSize() ); }
    int PointSizeName() const { return( fontHeaderText.pointSize() ); }
    int PointSizeUnit() const { return( fontHeaderText.pointSize()-4 ); }
    int PointSizeScale() const { return( fontHeaderText.pointSize()-2 ); }

    int ParameterNameOrientation() const { return( parameterNameOrientation ); }
    int PlotOrientation() const { return( plotOrientation ); }

    int TickmarkWidth() const { return( tickmarkWidth ); }
    int MinorTickmarkWidth() const { return( minorTickmarkWidth ); }
    int TicklineWidth() const { return( ticklineWidth ); }
    int MinorTicklineWidth() const { return( minorTicklineWidth ); }

    int DateTimeFormat() const { return( datetimeformat ); }
    int SavePlotFormat() const { return( saveplotformat ); }

    bool MouseLeftButtonState() const { return( mouseLeftButtonState ); }
    bool MouseRightButtonState() const { return( mouseRightButtonState ); }
    bool MouseMidButtonState() const { return( mouseMidButtonState ); }
    bool ResizeState() const { return( resizeState ); }

    bool Antialiasing() const { return( antialiasing ); }
    bool drawBackground() const { return( drawbackground ); }
    bool XReverseGraphRange()  const { return( rxr ); }
    bool fixedDiagramSize() const { return( fixeddiagramsize ); }

    double round( double r );

    QBrush BackgroundBrush() const { return( brushBackground ); }
    QColor BackgroundColor() const { return( colorBackground ); }

    QFont HeaderTextFont() const { return( fontHeaderText ); }

    QColor HeaderTextColor() const { return( colorHeaderText ); }
    QColor DiagramFrameColor() const { return( colorDiagramFrame ); }
    QColor TickmarkColor() const { return( colorTickmark ); }
    QColor TicklineColor() const { return( colorTickline ); }
    QColor MinorTickmarkColor() const { return( colorTickmark ); }
    QColor MinorTicklineColor() const { return( colorMinorTickline ); }

    QSize minimumSizeHint() const { return QSize( wx, wy ); }
    QSize sizeHint() const { return QSize( 400, 400 ); }

    QPoint posDialog() const { return posdialog; }

    QString FilenamePlot() const { return filenameplot; }

protected:
    void paintEvent( QPaintEvent *event );
    void mousePressEvent( QMouseEvent *event );
    void mouseReleaseEvent( QMouseEvent *event );
    void resizeEvent ( QResizeEvent * event );

private:
    int calcDiagramHeightV( QPainter &painter, const int Top, const int Bottom );
    int calcDiagramWidthV( QPainter &painter, const int Left, const int Right, const int DiagramDistance, const int minWidth, const int NumOfParameter );
    int calcDiagramHeightH( QPainter &painter, const int Top, const int Bottom, const int DiagramDistance, const int minHeight, const int NumOfParameter );
    int calcDiagramWidthH( QPainter &painter, const int Left, const int Right );
    int calcNumberOfParameter( QPainter &painter, const int Left, const int Right, const int DiagramDistance, const int Width, const int maxNumOfParameter );
    int calcMaxScaleWidth( QPainter &painter, const QVector<PlotSettings> v_PS, const QVector<int> v_PP );
    int getNumberOfVisibleParameter( const QVector<int> v_PP );
    int getLastVisibleParameter( const QVector<int> v_PP );
    int getParameterID_Body( const QVector<PlotSettings> v_PS, const QVector<int> v_PP );
    int getParameterID_Header( const QVector<PlotSettings> v_PS, const QVector<int> v_PP );

    void buildScaleLabelV( QPainter &painter, const QRect rect, const PlotSettings PS, const int DiagramDistance, const QVector<int> X, QVector<ScaleContainer> &ScaleLabel );
    void buildScaleLabelH( QPainter &painter, const QRect rect, const PlotSettings PS, const int DiagramDistance, const QVector<int> Y, QVector<ScaleContainer> &ScaleLabel );

    QString buildDateTimeString( const int Format, const double Value );

    int getTextWidth(QPainter &painter, const QFont Font, const int PointSize, const int Face, const double Value , int nFrac);
    int getTextWidth( QPainter &painter, const QFont Font, const int PointSize, const int Face, const QString &Text );
    int getDateTimeWidth( QPainter &painter, const QFont Font, const int PointSize, const int Face, int Format );
    int getTextHeight( QPainter &painter, const QFont Font, const int PointSize, const int Face, const QString &Text );
    int getMaxParameterWidth( QPainter &painter, const bool NamePlusUnit, const QFont Font, const int PointSize, const int Face, const QVector<PlotSettings> PS, const QVector<int> v_PP );

    void setDiagramRect( const QRect rect, PlotSettings &PS ) { PS.setDiagramRect( rect ); }
    void setHeaderRect( const QRect rect, PlotSettings &PS ) { PS.setHeaderRect( rect ); }

    void drawDiagram( QPainter &painter, const PlotSettings PS, const QPen Pen );
    void drawDiagramFrame( QPainter &painter, const PlotSettings PS, const QPen Pen );
    void drawDataMarker( QPainter &painter, const PlotSettings PS, const int startPos, const QVector<QPointF> &P );
    void drawDataLine( QPainter &painter, const PlotSettings PS, const int startPos, const QVector<QPointF> &P );
    void drawDataText( QPainter &painter, const PlotSettings PS, const int startPos, const QVector<QPointF> &P, const QStringList &Data );
    void drawXAxis( QPainter &painter, const PlotSettings PS, const QPoint Point, const int Width, const int Orientation );
    void drawParameter( QPainter &painter, const PlotSettings PS, const QPoint Point, const int Width, const int Align, const int Orientation );
    void drawText( QPainter &painter, const QRect rect, const QFont Font, const QColor Color, const int PointSize, const int Face, const int Flags, const int Orientation, const QString &Text );

    void calcPointCoordinatesNumericV( const int XAxisParameterID, const int YAxisParameterID, const bool XReverseGraphRange, QVector<PlotSettings> &PS, const QVector<DataItem> &Data, QVector<QPointF> &P );
    void calcPointCoordinatesNumericH( const int XAxisParameterID, const int YAxisParameterID, const bool XReverseGraphRange, QVector<PlotSettings> &PS, const QVector<DataItem> &Data, QVector<QPointF> &P );
    void calcPointCoordinatesTextV( const int XAxisParameterID, const int YAxisParameterID, const bool XReverseGraphRange, QVector<PlotSettings> &PS, const QVector<DataItem> &Data, QVector<QPointF> &P, QStringList &TextData );
    void calcPointCoordinatesTextH( const int XAxisParameterID, const int YAxisParameterID, const bool XReverseGraphRange, QVector<PlotSettings> &PS, const QVector<DataItem> &Data, QVector<QPointF> &P, QStringList &TextData );

    void calcXTicksPositionV( const QRect rect, const PlotSettings PS, const bool XReverseGraphRange, QVector<int> &Y, QVector<int> &Ym );
    void calcXTicksPositionH( const QRect rect, const PlotSettings PS, const bool XReverseGraphRange, QVector<int> &X, QVector<int> &Xm );
    void calcYTicksPositionV( const QRect rect, const PlotSettings PS, QVector<int> &X, QVector<int> &Xm );
    void calcYTicksPositionH( const QRect rect, const PlotSettings PS, QVector<int> &Y, QVector<int> &Ym );

    void drawHeaderV( QPainter &painter, const PlotSettings PS );
    void drawHeaderH( QPainter &painter, const PlotSettings PS );

    void drawDataColorizedV( QPainter &painter, const PlotSettings PS, const int startPos, const QVector<QPointF> &P );
    void drawDataColorizedH( QPainter &painter, const PlotSettings PS, const int startPos, const QVector<QPointF> &P );

    void drawXReflineV( QPainter &painter, const PlotSettings PS, const bool XReverseGraphRange );
    void drawXReflineH( QPainter &painter, const PlotSettings PS, const bool XReverseGraphRange );
    void drawYReflineV( QPainter &painter, const PlotSettings PS );
    void drawYReflineH( QPainter &painter, const PlotSettings PS );

    void drawXScaleV( QPainter &painter, const PlotSettings PS, const int DiagramDistance, const QPen TickmarkPen, const QPen TicklinePen, const QPen MinorTickmarkPen, const QPen MinorTicklinePen, const int ParameterID, const int LastVisibleParameter, const int Type, const bool XReverseGraphRange );
    void drawXScaleH( QPainter &painter, const PlotSettings PS, const int DiagramDistance, const QPen TickmarkPen, const QPen TicklinePen, const QPen MinorTickmarkPen, const QPen MinorTicklinePen, const int ParameterID, const int LastVisibleParameter, const int Type, const bool XReverseGraphRange );
    void drawYScaleV( QPainter &painter, const PlotSettings PS, const int DiagramDistance, const QPen TickmarkPen, const QPen TicklinePen, const QPen MinorTickmarkPen, const QPen MinorTicklinePen );
    void drawYScaleH( QPainter &painter, const PlotSettings PS, const int DiagramDistance, const QPen TickmarkPen, const QPen TicklinePen, const QPen MinorTickmarkPen, const QPen MinorTicklinePen );

    void drawXTicksV( QPainter &painter, const QRect rect, const QPen TickmarkPen, const QVector<int> Y );
    void drawXTicksH( QPainter &painter, const QRect rect, const QPen TickmarkPen, const QVector<int> X );
    void drawYTicksV( QPainter &painter, const QRect rect, const QPen TickmarkPen, const QVector<int> X );
    void drawYTicksH( QPainter &painter, const QRect rect, const QPen TickmarkPen, const QVector<int> Y );

    void drawXMinorTicksV( QPainter &painter, const QRect rect, const QPen Pen, const QVector<int> Ym );
    void drawXMinorTicksH( QPainter &painter, const QRect rect, const QPen Pen, const QVector<int> Xm );
    void drawYMinorTicksV( QPainter &painter, const QRect rect, const QPen Pen, const QVector<int> Xm );
    void drawYMinorTicksH( QPainter &painter, const QRect rect, const QPen Pen, const QVector<int> Ym );

    void drawXTickLabelsV( QPainter &painter, const QRect rect, const QColor TickLabelColor, const PlotSettings PS, const QVector<int> Y, const int Type );
    void drawXTickLabelsH( QPainter &painter, const QRect rect, const QColor TickLabelColor, const PlotSettings PS, const QVector<int> X, const int Type );
    void drawYTickLabelsV( QPainter &painter, const QRect rect, const QColor TickLabelColor, const PlotSettings PS, const QVector<int> X, const int DiagramDistance );
    void drawYTickLabelsH( QPainter &painter, const QRect rect, const QColor TickLabelColor, const PlotSettings PS, const QVector<int> Y, const int DiagramDistance);

    void drawCopyrightV( QPainter &painter, const QRect rect, const QString &CopyrightText );
    void drawCopyrightH( QPainter &painter, const QRect rect, const QString &CopyrightText );

    void transformPainter( QPainter &painter );

    QVector<DataItem>     v_Data;
    QVector<PlotSettings> v_PS;
    QVector<int>          v_PP;

    int count;

    int  mlbx, mlby;
    int  mrbx, mrby;
    int  mmbx, mmby;

    int saveplotformat;
    int datetimeformat;

    int rot;
    int translate1, translate2;
    int wx, wy, statusBarHeight;
    int pointSizeHeader, parameterNameOrientation, plotOrientation;
    int marginLeft, marginRight, marginTop, marginBottom, marginScale;
    int diagramWidth, diagramHeight, diagramDistance, diagramFrameWidth;
    int tickmarkWidth, minorTickmarkWidth, ticklineWidth, minorTicklineWidth;

    double scale1, scale2;

    bool mouseLeftButtonState;
    bool mouseRightButtonState;
    bool mouseMidButtonState;
    bool resizeState;
    bool antialiasing;
    bool drawbackground;
    bool fixeddiagramsize;

    bool rxr;

    QColor colorDiagramBackground, colorDiagramFrame, colorHeaderText;
    QColor colorTickmark, colorTickline, colorMinorTickline, colorBackground;

    QBrush brushBackground;

    QFont  fontHeaderText;

    QPoint posdialog;

    QString filenameplot;
};

#endif // RENDERAREA_H
