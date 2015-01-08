/* setRange.cpp               */
/* 2009-12-03                 */
/* Dr. Rainer Sieger          */

#include "Application.h"
#include "DataItem.h"
#include "PlotSettings.h"

// **********************************************************************************************
// **********************************************************************************************
// **********************************************************************************************
// 2009-12-03

void MainWindow::setRange( const int j, const QVector<DataItem> &v_Data, QVector<PlotSettings> &v_PS, const bool b_isDateTime )
{
    int    start                = v_PS.at( j ).startPos();
    int    end                  = v_PS.at( j ).startPos() + v_PS.at( j ).count() - 1;

    double d_Minimum            = 10E99;
    double d_Maximum            = -10E99;

    int     i_nfrac             = 0;
    double  d_tickMarkSpacing   = 1;
    double  d_graphMin          = 0;
    double  d_graphMax          = 0;
    double  d_range             = 0;

// **********************************************************************************************

    if ( b_isDateTime == TRUE )
    {
        for ( int i=start; i<=end; i++ )
        {
            if ( ( v_Data.at( i ).qualityFlag() == DATETIME ) && ( d_Minimum > v_Data.at( i ).value() ) )
                d_Minimum = v_Data.at( i ).value();

            if ( ( v_Data.at( i ).qualityFlag() == DATETIME ) && ( d_Maximum < v_Data.at( i ).value() ) )
                d_Maximum = v_Data.at( i ).value();
        }
    }
    else
    {
        for ( int i=start; i<=end; i++ )
        {
            if ( ( v_Data.at( i ).qualityFlag() > EMPTY ) && ( v_Data.at( i ).qualityFlag() < TEXT ) && ( d_Minimum > v_Data.at( i ).value() ) )
                d_Minimum = v_Data.at( i ).value();

            if ( ( v_Data.at( i ).qualityFlag() > EMPTY ) && ( v_Data.at( i ).qualityFlag() < TEXT ) && ( d_Maximum < v_Data.at( i ).value() ) )
                d_Maximum = v_Data.at( i ).value();
        }
    }

    if ( d_Maximum != d_Minimum )
        calcLooseLabel( d_Minimum, d_Maximum, i_nfrac, d_tickMarkSpacing, d_graphMin, d_graphMax, d_range );
    else
        calcLooseLabel( d_Minimum-1., d_Maximum+1., i_nfrac, d_tickMarkSpacing, d_graphMin, d_graphMax, d_range );

    v_PS[j].setMinMax( d_Minimum, d_Maximum );
    v_PS[j].setNiceLabel( i_nfrac, d_tickMarkSpacing, d_graphMin, d_graphMax, d_range );
}

