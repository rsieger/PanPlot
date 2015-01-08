#ifndef PARAMETERSETTINGS_H
#define PARAMETERSETTINGS_H

#include <QMainWindow>

class ParameterSettings
{
public:
    ParameterSettings( const int i = -1, const QString& name = "", const QString& unit = "", const int p = -1, const int c = -1 );

    int id() const { return( i ); }
    int startPos() const { return( p ); }
    int count() const { return( c ); }
    int nfrac() const { return ( nf ); }
    double Minimum() const { return( min ); }
    double Maximum() const { return( max ); }
    double GraphMin() const { return ( gmin ); }
    double GraphMax() const { return ( gmax ); }
    double TickmarkSpacing() const { return ( tms ); }
    double Range() const { return ( range ); }
    QString Name() const { return( name ); }
    QString Unit() const { return( unit ); }

    void setName( const QString& var ) { name = var; }
    void setUnit( const QString& var ) { unit = var; }
    void setMinimum( double var ) { min = var; }
    void setMaximum( double var ) { max = var; }
    void setMinMax( double var1, double var2 ) { min = var1; max = var2; }
    void setGraphMinimum( double var ) { gmin = var; }
    void setGraphMaximum( double var ) { gmax = var; }
    void setGraphMinMax( double var1, double var2 ) { gmin = var1; gmax = var2; }
    void setID( int ID ) { i = ID; }
    void setStartPos( int var ) { p = var; }
    void setCount( int var ) { c = var; }
    void setNiceLabel( int var1, double var2, double var3, double var4, double var5 ) { nf = var1; tms = var2; gmin = var3; gmax = var4; range = var5; }

private:
    int     i;                  // Parameter ID
    int     p;                  // Start position of parameter
    int     c;                  // Number of data items
    int     nf;                 // # of fractional digits to show

    double  min;                // Minimum
    double  max;                // Maximum
    double  tms;                // Tick mark spacing
    double  gmin;               // Graphic minimum
    double  gmax;               // Graphic maximum
    double  range;              // Range

    QString name;               // Parameter name
    QString unit;               // Parameter unit
};

#endif // PARAMETERSETTINGS_H
