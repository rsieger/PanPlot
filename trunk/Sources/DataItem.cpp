/* DataItem.cpp               */
/* 2009-12-01                 */
/* Dr. Rainer Sieger          */

#include "Application.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************

DataItem::DataItem( const int i_Column, const int i_Row, const QString &s_Text, const double d_Value, const int i_QualityFlag, const int i_Status )
{
    setRow( i_Row );
    setColumn( i_Column );

    setQualityFlag( i_QualityFlag );
    setStatus( i_Status );
    setText( s_Text );
    setValue( d_Value );
}

DataItem::DataItem( const int i_Column, const int i_Row, const QString &s_TextIn, const int i_Type )
{
    setColumn( i_Column );
    setRow( i_Row );

    setQualityFlag();
    setStatus(); // = 0
    setText();
    setValue();

// **********************************************************************************************

    if ( s_TextIn.isEmpty() == true )
    {
        setStatus( _EMPTY_ );
        return;
    }

// **********************************************************************************************

    if ( i_Type == isDOI )
    {
        setQualityFlag( _DOI_ );
        setText( s_TextIn );

        if ( s_TextIn.contains( "10.1594/pangaea.", Qt::CaseInsensitive ) == true )
        {
            setStatus( _OK_ );
            setValue( s_TextIn.toLower().section( "10.1594/pangaea.", 1, 1 ).toDouble() );
        }

        return;
    }

// **********************************************************************************************

    if ( i_Type == isURL )
    {
        setQualityFlag( _URL_ );
        setText( s_TextIn );

        if ( s_TextIn.contains( "10.1594/pangaea.", Qt::CaseInsensitive ) == true )
        {
            setStatus( _OK_ );
            setValue( s_TextIn.toLower().section( "10.1594/pangaea.", 1, 1 ).toDouble() );
        }

        return;
    }

// **********************************************************************************************

    if ( i_Type == isDateTime )
    {
        setQualityFlag( _DATETIME_ );
        setStatus( _OK_ );

        int     pos    = -1;

        QString s_date = s_TextIn;

        QDate   date   = QDate();
        QTime   time   = QTime();

        QRegExp rxDate1( "^\\d{4}-\\d{2}-\\d{2}" );  // 1961-02-22
        QRegExp rxDate2( "^\\d{4}-\\d{2}$" );        // 1961-02
        QRegExp rxDate3( "^\\d{4}$" );               // 1961

// **********************************************************************************************
// PanPlot supports ISODate only

        s_date.replace( " ", "T" );
        s_date = s_date.section( "T", 0, 0 );

        switch( s_date.length() )
        {
        case 10: // yyyy-MM-dd
            if ( rxDate1.indexIn( s_date ) == 0 )
            {
                date = QDate::fromString( s_date, "yyyy-MM-dd" );
                setValue( (double) date.toJulianDay() );
                if ( s_TextIn.length() == 10 )
                    return;
            }
            break;

        case 7: // yyyy-MM
            if ( rxDate2.indexIn( s_date ) == 0 )
            {
                date = QDate::fromString( QString( "%1-%2" ).arg( s_date ).arg( 15 ), "yyyy-MM-dd" );
                setValue( (double) date.toJulianDay() );
                if ( s_TextIn.length() == 7 )
                    return;
            }
            break;

        case 4: // yyyy
            if ( rxDate3.indexIn( s_date ) == 0 )
            {
                date = QDate::fromString( QString( "%1-%2-%3" ).arg( s_date ).arg( 6 ).arg( 30 ), "yyyy-MM-dd" );
                setValue( (double) date.toJulianDay() );
                if ( s_TextIn.length() == 4 )
                    return;
            }
            break;

        default:
            return;
            break;
        }

// **********************************************************************************************
// Time

        QRegExp rxTime0( "[\\sT](2[0-3]|[01][0-9])$" );  // 18 (data warehouse: hourly average)

        if ( ( pos = rxTime0.indexIn( s_TextIn ) ) > 0 )
        {
            time = QTime::fromString( s_TextIn.mid( pos+1 ), "hh" );
        }
        else
        {
            QRegExp rxTime1( "[\\sT](2[0-3]|[01][0-9]):([0-5][0-9])$" );  // 18:56

            if ( ( pos = rxTime1.indexIn( s_TextIn ) ) > 0 )
            {
                time = QTime::fromString( s_TextIn.mid( pos+1 ), "hh:mm" );
            }
            else
            {
                QRegExp rxTime2( "[\\sT](2[0-3]|[01][0-9]):([0-5][0-9]):([0-5][0-9])$" ); // 18:56:34

                if ( ( pos = rxTime2.indexIn( s_TextIn ) ) > 0 )
                {
                    time = QTime::fromString( s_TextIn.mid( pos+1 ), "hh:mm:ss" );
                }
                else
                {
                    QRegExp rxTime3( "[\\sT](2[0-3]|[01][0-9]):([0-5][0-9]):([0-5][0-9]).([0-9][0-9][0-9])$" ); // 18:56:34.267

                    if ( ( pos = rxTime3.indexIn( s_TextIn ) ) > 0 )
                    {
                        time = QTime::fromString( s_TextIn.mid( pos+1 ), "hh:mm:ss.zzz" );
                    }
                }
            }
        }

        setValue( Value() - (double) time.msecsTo( QTime( 0, 0 ) )/(double) 86400000. );

        return;
    }

// **********************************************************************************************
// Double with quality flags

    bool    b_OK    = false;
    QString s_Text  = s_TextIn;

    if ( ( s_Text.toLower() != "nan" ) && ( s_Text.toLower() != "inf" ) )
    {
        s_Text = s_Text.replace( ",", "." ).simplified();
        setValue( s_Text.toDouble( &b_OK ) );
    }

    if ( b_OK == false )
    {
        QString s_QV = s_Text.left( 1 );

        if ( s_QV == "?" )
            setQualityFlag( _QUESTIONABLE_ );

        else if ( s_QV == "<" )
            setQualityFlag( _LESSTHAN_ );

        else if ( s_QV == ">" )
            setQualityFlag( _GREATERTHAN_ );

        else if ( s_QV == "/" )
            setQualityFlag( _NOTVALID_ );

        else if ( s_QV == "#" )
            setQualityFlag( _INDDEF_ );

        else if ( s_QV == "*" )
            setQualityFlag( _UNKNOWN_ );

        else if ( s_QV == "ø" )
            setQualityFlag( _MEAN_ );

        if ( QualityFlag() > 0 )
        {
            if ( ( s_Text.mid( 1 ).toLower() != "nan" ) && ( s_Text.mid( 1 ).toLower() != "inf" ) )
                setValue( s_Text.mid( 1 ).toDouble( &b_OK ) );

            if ( b_OK == false )
            {
                setText( s_TextIn.mid( 1 ) );
                setValue( -999. );
                setQualityFlag( _TEXT_ + QualityFlag() );
            }
            else
            {
                setStatus( _OK_ );
                setQualityFlag( _NUMERIC_ + QualityFlag() );
            }
        }
        else
        {
            setText( s_TextIn );
            setValue( -999. );
            setQualityFlag( _TEXT_ );
        }
    }
    else
    {
        setStatus( _OK_ );
        setQualityFlag( _NUMERIC_ ); // cell is numeric, quality is good
    }
}
