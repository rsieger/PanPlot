#ifndef DATAITEM_H
#define DATAITEM_H

// Status
const int _EMPTY_            = -1;
const int _OK_               =  1;

// Quality flag and type
const int _GOOD_             = 0;  // OK
const int _UNKNOWN_          = 1;  // *
const int _NOTVALID_         = 2;  // /
const int _INDDEF_           = 3;  // #
const int _QUESTIONABLE_     = 4;  // ?
const int _LESSTHAN_         = 5;  // <
const int _GREATERTHAN_      = 6;  // >
const int _MEAN_             = 7;  // mean
const int _DATETIME_         = 10;
const int _NUMERIC_          = 20;
const int _TEXT_             = 40;
const int _DOI_              = 80;
const int _URL_              = 160;

class DataItem
{
public:
    DataItem( const int Column = -1, const int Row = -1, const QString &Text = "", const int Type = 0 );
    DataItem( const int Column, const int Row, const QString &Text, const double Value, const int QualityFlag, const int Status );

    int Status() const { return( status ); }
    QString Text() const { return( text ); }
    double Value() const { return( value ); }
    int QualityFlag() const { return( qualityflag ); }
    int Row() const { return( row ); }
    int Column() const { return( column ); }

    void setStatus( int Status = 0 ) { status = Status; }
    void setText( const QString &Text = "" ) { text = Text; }
    void setValue( double Value = -999. ) { value = Value; }
    void setQualityFlag( int QualityFlag = 0 ) { qualityflag = QualityFlag; }
    void setColumn( int Column ) { column = Column; }
    void setRow( int Row ) { row = Row; }

private:
    int row;            // Row ID
    int column;         // Column ID
    int status;         // Status
    QString text;       // Item text
    double value;       // Value
    int qualityflag;    // Quality flag and type
};

#endif // DATAITEM_H
