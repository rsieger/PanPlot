#ifndef PLOTSETTINGS_H
#define PLOTSETTINGS_H

// Type
const int isNumeric         = 1;
const int isText            = 2;
const int isDateTime        = 3;
const int isDOI             = 4;
const int isURL             = 5;

// Quality
const int hasQualityFlags   = 1;
const int hasEmptyEntries   = 2;

class PlotSettings
{
public:
    PlotSettings( const bool allSettings = true, const int parameter = 0, const int count = 0, const QString &header = "" );

// Parameter settings
    QString ParameterName() const { return( name ); }
    QString ParameterUnit() const { return( unit ); }
    QString Parameter() const { return( parameter ); }

    int ID() const { return( id ); }
    int StartPos() const { return( p ); }
    int DataCount() const { return( c ); }
    int Type() const { return( type ); }
    int Quality() const { return( quality ); }
    int NumOfPointsNumeric() const { return( npn ); }
    int NumOfPointsDataText() const { return( npt ); }
    int NumOfXMinorTicks() const { return( xmt ); }
    int NumOfYMinorTicks() const { return( ymt ); }
    int MarkerSize() const { return( markersize ); }
    int DataTextPointSize() const { return( datatextfont.pointSize() ); }
    int LineWidth() const { return( linewidth ); }
    int Pattern() const { return( pattern ); }

    double Median() const { return( median ); }
    double Mean() const { return( mean ); }
    double StandardDeviation() const { return( stddev ); }

    double XMinimum() const { return( xmin ); }
    double XMaximum() const { return( xmax ); }
    double XGraphMin() const { return( xgmin ); }
    double XGraphMax() const { return( xgmax ); }
    double XGraphRange() const { return( xgr ); }
    double XRefline() const { return( xrefline ); }
    double XTickmarkSpacing() const { return( xtms ); }
    int    XnFrac() const { return( xnf ); }
    int    XReflineWidth() const { return( xreflinewidth ); }

    double AutoXGraphMin() const { return( axgmin ); }
    double AutoXGraphMax() const { return( axgmax ); }
    double AutoXTickmarkSpacing() const { return( axtms ); }
    int    AutoXnFrac() const { return( axnf ); }

    double ManualXGraphMin() const { return( mxgmin ); }
    double ManualXGraphMax() const { return( mxgmax ); }
    double ManualXTickmarkSpacing() const { return( mxtms ); }
    int    ManualXnFrac() const { return( mxnf ); }

    double YMinimum() const { return( ymin ); }
    double YMaximum() const { return( ymax ); }
    double YGraphMin() const { return( ygmin ); }
    double YGraphMax() const { return( ygmax ); }
    double YGraphRange() const { return( ygr ); }
    double YRefline() const { return( yrefline ); }
    double YTickmarkSpacing() const { return( ytms ); }
    int    YnFrac() const { return( ynf ); }
    int    YReflineWidth() const { return( yreflinewidth ); }

    double AutoYGraphMin() const { return( aygmin ); }
    double AutoYGraphMax() const { return( aygmax ); }
    double AutoYTickmarkSpacing() const { return( aytms ); }
    int    AutoYnFrac() const { return( aynf ); }

    double ManualYGraphMin() const { return( mygmin ); }
    double ManualYGraphMax() const { return( mygmax ); }
    double ManualYTickmarkSpacing() const { return( mytms ); }
    int    ManualYnFrac() const { return( mynf ); }

    bool useManualScaleSettings() const { return( umss ); }
    bool YReverseGraphRange() const { return( ryr ); }
    bool drawXRefline() const { return( dxrl ); }
    bool drawYRefline() const { return( dyrl ); }
    bool drawDataText() const { return( drawdatatext ); }
    bool drawMarker() const { return( drawmarker ); }
    bool drawLine() const { return( drawline ); }
    bool drawColorized() const { return( drawcolorized ); }
    bool drawDiagramBackground() const { return( ddbgr ); }

    QColor LineColor() const { return( linecolor ); }
    QColor ColorizedGreaterRefColor() const { return( colorizedgreaterrefcolor ); }
    QColor ColorizedLessRefColor() const { return( colorizedlessrefcolor ); }
    QColor MarkerColor() const { return( markercolor ); }
    QColor DataTextColor() const { return( datatextcolor ); }
    QColor DiagramBackgroundColor() const { return( diagrambackgroundcolor ); }
    QColor XReflineColor() const { return( xreflinecolor ); }
    QColor YReflineColor() const { return( yreflinecolor ); }

    QFont DataTextFont() const { return( datatextfont ); }

// Global parameter settings
    int XTickmarkLength() const { return( xtl ); }
    int YTickmarkLength() const { return( ytl ); }

    bool drawXTickmarksLeftOutside() const { return( dxtmLO ); }
    bool drawXTickmarksLeftInside() const { return( dxtmLI ); }
    bool drawXTickmarksRightOutside() const { return( dxtmRO ); }
    bool drawXTickmarksRightInside() const { return( dxtmRI ); }
    bool drawXMinorTickmarksLeftOutside() const { return( dxmtmLO ); }
    bool drawXMinorTickmarksLeftInside() const { return( dxmtmLI ); }
    bool drawXMinorTickmarksRightOutside() const { return( dxmtmRO ); }
    bool drawXMinorTickmarksRightInside() const { return( dxmtmRI ); }
    bool drawXTicklines() const { return( dxtl ); }
    bool drawXMinorTicklines() const { return( dxmtl ); }
    bool drawXTickmarkLabels() const { return( dxtml ); }

    bool drawYTickmarksTopOutside() const { return( dytmTO ); }
    bool drawYTickmarksTopInside() const { return( dytmTI ); }
    bool drawYTickmarksBottomOutside() const { return( dytmBO ); }
    bool drawYTickmarksBottomInside() const { return( dytmBI ); }
    bool drawYMinorTickmarksTopOutside() const { return( dymtmTO ); }
    bool drawYMinorTickmarksTopInside() const { return( dymtmTI ); }
    bool drawYMinorTickmarksBottomOutside() const { return( dymtmBO ); }
    bool drawYMinorTickmarksBottomInside() const { return( dymtmBI ); }
    bool drawYTicklines() const { return( dytl ); }
    bool drawYMinorTicklines() const { return( dymtl ); }
    bool drawYTickmarkLabels() const { return( dytml ); }

    bool isGeocode() const { return( geocode ); }
    bool isGeocode( const QString &ParameterName );

    QRect DiagramRect() const { return( diagramrect ); }
    QRect HeaderRect() const { return( headerrect ); }

    void setParameterNameUnit( const QString &ParameterName, const QString &ParameterUnit );
    void setParameterNameUnit( const QString &Header );

    void setXMinimum( const double var ) { xmin = var; }
    void setXMaximum( const double var ) { xmax = var; }
    void setXMinMax( const double var1, const double var2 ) { xmin = var1; xmax = var2; }
    void setXGraphMinimum( const double var ) { xgmin = var; }
    void setXGraphMaximum( const double var ) { xgmax = var; }
    void setXGraphMinMax( const double var1, const double var2 ) { xgmin = var1; xgmax = var2; }
    void setXGraphRange( const double var ) { xgr = var; }
    void setXReverseGraphRange( const bool var=true ) { rxr = var; }

    void setAutoXGraphMinimum( const double var ) { axgmin = var; }
    void setAutoXGraphMaximum( const double var ) { axgmax = var; }
    void setAutoXGraphMinMax( const double var1, const double var2 ) { axgmin = var1; axgmax = var2; }

    void setManualXGraphMinimum( const double var ) { mxgmin = var; }
    void setManualXGraphMaximum( const double var ) { mxgmax = var; }
    void setManualXGraphMinMax( const double var1, const double var2 ) { mxgmin = var1; mxgmax = var2; }

    void setUseManualScaleSettings( const bool var=false ) { umss=var; }

    void setYMinimum( const double var ) { ymin = var; }
    void setYMaximum( const double var ) { ymax = var; }
    void setYMinMax( const double var1, const double var2 ) { ymin = var1; ymax = var2; }
    void setYGraphMinimum( const double var ) { ygmin = var; }
    void setYGraphMaximum( const double var ) { ygmax = var; }
    void setYGraphMinMax( const double var1, const double var2 ) { ygmin = var1; ygmax = var2; }
    void setYGraphRange( const double var ) { ygr = var; }
    void setYReverseGraphRange( const bool var=false ) { ryr = var; }

    void setAutoYGraphMinimum( const double var ) { aygmin = var; }
    void setAutoYGraphMaximum( const double var ) { aygmax = var; }
    void setAutoYGraphMinMax( const double var1, const double var2 ) { aygmin = var1; aygmax = var2; }

    void setManualYGraphMinimum( const double var ) { mygmin = var; }
    void setManualYGraphMaximum( const double var ) { mygmax = var; }
    void setManualYGraphMinMax( const double var1, const double var2 ) { mygmin = var1; mygmax = var2; }

    void setMarkerColor( const QColor var ) { markercolor = var; }
    void setLineColor( const QColor var ) { linecolor = var; }
    void setColorizedGreaterRefColor( const QColor var ) { colorizedgreaterrefcolor = var; }
    void setColorizedLessRefColor( const QColor var ) { colorizedlessrefcolor = var; }
    void setXReflineColor( const QColor var ) { xreflinecolor = var; }
    void setYReflineColor( const QColor var ) { yreflinecolor = var; }

    void setDrawMarker( const bool var=false ) { drawmarker = var; }
    void setDrawLine( const bool var=false ) { drawline = var; }
    void setDrawColorized( const bool var=false ) { drawcolorized = var; }

    void setID( const int ID ) { id = ID; }
    void setDataCount( const int var ) { c = var; }
    void setStartPos( const int var ) { p = var; }
    void setNumOfPointsNumeric( const int var ) { npn = var; }
    void setNumOfPointsDataText( const int var ) { npt = var; }

    void setXNiceLabel( const int var1, const double var2, const double var3, const double var4 ) { xnf = var1; xtms = var2; xgmin = var3; xgmax = var4; }
    void setYNiceLabel( const int var1, const double var2, const double var3, const double var4 ) { ynf = var1; ytms = var2; ygmin = var3; ygmax = var4; }

    void setAutoXNiceLabel( const int var1, const double var2, const double var3, const double var4 ) { axnf = var1; axtms = var2; axgmin = var3; axgmax = var4; }
    void setAutoYNiceLabel( const int var1, const double var2, const double var3, const double var4 ) { aynf = var1; aytms = var2; aygmin = var3; aygmax = var4; }

    void setManualXNiceLabel( const int var1, const double var2, const double var3, const double var4 ) { mxnf = var1; mxtms = var2; mxgmin = var3; mxgmax = var4; }
    void setManualYNiceLabel( const int var1, const double var2, const double var3, const double var4 ) { mynf = var1; mytms = var2; mygmin = var3; mygmax = var4; }

    void setXTicksOptions( const int XTickmarkLength=6, const bool drawTickmarksLeftOutside=true, const bool drawTickmarksLeftInside=false, const bool drawTickmarksRightOutside=false, const bool drawTickmarksRightInside=false, const bool drawTicklines=true, const bool drawTickmarkLabels=true );
    void setXMinorTicksOptions( const int XNumOfMinorTicks=3, const bool drawMinorTickmarksLeftOutside=true, const bool drawMinorTickmarksLeftInside=false, const bool drawMinorTickmarksRightOutside=false, const bool drawMinorTickmarksRightInside=false, const bool drawMinorTicklines=true );
    void setYTicksOptions( const int YTickmarkLength=6, const bool drawTickmarksTopOutside=true, const bool drawTickmarksTopInside=false, const bool drawTickmarksBottomOutside=false, const bool drawTickmarksBottomInside=false, const bool drawTicklines=true, const bool drawTickmarkLabels=true );
    void setYMinorTicksOptions( const int YNumOfMinorTicks=3, const bool drawMinorTickmarksTopOutside=true, const bool drawMinorTickmarksTopInside=false, const bool drawMinorTickmarksBottomOutside=false, const bool drawMinorTickmarksBottomInside=false, const bool drawMinorTicklines=true );

    void setXReflineOptions( const bool var1=true, const int var2=1, const QColor var3=Qt::black, const double var4=0. ) { dxrl = var1; xreflinewidth = var2; xreflinecolor = var3; xrefline = var4; }
    void setYReflineOptions( const bool var1=true, const int var2=1, const QColor var3=Qt::black, const double var4=0. ) { dyrl = var1; yreflinewidth = var2; yreflinecolor = var3; yrefline = var4; }

    void setType( const int Type=1 ) { type = Type; }
    void setQuality( const int Quality=0 ) { quality = Quality; }
    void setDiagramRect( const QRect Rect ) { diagramrect = Rect; }
    void setHeaderRect( const QRect Rect ) { headerrect = Rect; }
    void setGeocode( const bool Geocode=false ) { geocode = Geocode; }
    void setMedian( const double Median=-999. ) { median = Median; }
    void setMean( const double Mean=-999. ) { mean = Mean; }
    void setStandardDeviation( const double StdDev=-999. ) { stddev = StdDev; }

    void setDiagramBackgroundOptions( const bool drawDiagramBackground=false, const QColor DiagramBackgroundColor=Qt::lightGray ) { ddbgr = drawDiagramBackground; diagrambackgroundcolor = DiagramBackgroundColor; }
    void setDataTextOptions( const bool drawText=true, const QFont DataTextFont=QFont( "Lucdia grande", 14, 0, false ), const QColor DataTextColor=Qt::black );
    void setMarkerOptions( const bool drawMarker=true, const int MarkerSize=3, const QColor MarkerColor=Qt::black );
    void setLineOptions( const bool drawLine=true, const int LineWidth=1, const QColor LineColor=Qt::black );
    void setColorizedOptions( const bool drawColorized=true, const int Pattern=1, const QColor ColorGreaterRef=Qt::red, const QColor ColorLessRef=Qt::blue );

private:
    int     id;                 // Parameter ID
    int     p;                  // Start position of parameter
    int     c;                  // Number of data items
    int     npn;                // Number of points of numeric data to draw
    int     npt;                // Number of points of text data to draw
    int     type;               // Type (1=Numeric, 2=Text, 4=DateTime, 8=DOI, 16=URL)
    int     quality;            // Quality of data

    double  median;             // Meadian
    double  mean;               // Mean
    double  stddev;             // Standard deviation

    double  xmin;               // Minimum, x-Axis
    double  xmax;               // Maximum, x-Axis
    double  xgmin;              // Graphic minimum, x-Axis
    double  xgmax;              // Graphic maximum, x-Axis
    double  xrefline;           // Reference line, x-Axis
    double  xtms;               // Tick mark spacing, x-Axis
    double  xgr;                // Range, x-Axis
    int     xnf;                // # of fractional digits to show, x-Axis
    bool    rxr;                // Reverse range, x-Axis

    double  axgmin;             // Graphic minimum, x-Axis, automatically
    double  axgmax;             // Graphic maximum, x-Axis, automatically
    double  axtms;              // Tick mark spacing, x-Axis, automatically
    int     axnf;               // # of fractional digits to show, x-Axis, automatically

    double  mxgmin;             // Graphic minimum, x-Axis, manually
    double  mxgmax;             // Graphic maximum, x-Axis, manually
    double  mxtms;              // Tick mark spacing, x-Axis, manually
    int     mxnf;               // # of fractional digits to show, x-Axis, manually

    double  ymin;               // Minimum, y-Axis
    double  ymax;               // Maximum, y-Axis
    double  ygmin;              // Graphic minimum, y-Axis
    double  ygmax;              // Graphic maximum, y-Axis
    double  yrefline;           // Reference line, y-Axis
    double  ytms;               // Tick mark spacing, y-Axis
    double  ygr;                // Range, y-Axis
    int     ynf;                // # of fractional digits to show, y-Axis
    bool    ryr;                // Reverse range, y-Axis

    double  aygmin;             // Graphic minimum, y-Axis, automatically
    double  aygmax;             // Graphic maximum, y-Axis, automatically
    double  aytms;              // Tick mark spacing, y-Axis, automatically
    int     aynf;               // # of fractional digits to show, y-Axis, automatically

    double  mygmin;             // Graphic minimum, y-Axis, manually
    double  mygmax;             // Graphic maximum, y-Axis, manually
    double  mytms;              // Tick mark spacing, y-Axis, manually
    int     mynf;               // # of fractional digits to show, y-Axis, manually

    QString name;               // Parameter name
    QString unit;               // Parameter unit
    QString comment;            // Parameter comment
    QString parameter;          // Parameter name+unit+comment

    int  xtl, ytl;
    int  xmt, ymt;

    bool geocode;               // is Geocode

    bool dxtmLO, dxtmLI;
    bool dxtmRO, dxtmRI;
    bool dxmtmLO, dxmtmLI;
    bool dxmtmRO, dxmtmRI;
    bool dxtl, dxmtl, dxtml;
    bool dxrl;

    bool dytmTO, dytmTI;
    bool dytmBO, dytmBI;
    bool dymtmTO, dymtmTI;
    bool dymtmBO, dymtmBI;
    bool dytl, dymtl, dytml;
    bool dyrl;

    bool ddbgr;

    bool umss;

    bool drawdatatext, drawmarker, drawline, drawcolorized;
    int  markersize, linewidth, pattern, xreflinewidth, yreflinewidth;

    QColor datatextcolor, markercolor, linecolor;
    QColor colorizedgreaterrefcolor, colorizedlessrefcolor;
    QColor diagrambackgroundcolor, xreflinecolor, yreflinecolor;

    QRect  diagramrect, headerrect;

    QFont  datatextfont;
};

#endif // PLOTSETTINGS_H
