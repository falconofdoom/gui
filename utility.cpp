#include "utility.h"

Utility::Utility()
{}

QString Utility::intToMonth(int i)
{
    switch (i) {
        case 1:
            return "January";
            break;
        case 2:
            return "February";
            break;
        case 3:
            return "March";
            break;
        case 4:
            return "April";
            break;
        case 5:
            return "May";
            break;
        case 6:
            return "June";
            break;
        case 7:
            return "July";
            break;
        case 8:
            return "August";
            break;
        case 9:
            return "September";
            break;
        case 10:
            return "October";
            break;
        case 11:
            return "November";
            break;
        case 12:
            return "December";
            break;
        default:
            return "Invalid Integer! Cannot convert!";
            break;
    }
}

QString Utility::accumulate(int i, QVector < QVector < QString > > vvqs)
{
    QString str="";
    if(!vvqs.empty())
    for(int j=0;j<vvqs[i].size();j++)
    {
        if(vvqs[i][j].trimmed()!="" && vvqs[i][j].trimmed()!="\n")
        {
            if(vvqs[i][j].indexOf("\n")==-1)
           str= str.append(vvqs[i][j]).append("\n");
             else
                str = str.append(vvqs[i][j]);
        }
    }
    return str;
}

int Utility::sumOverErrors(QVector<int> vI)
{
    int total = 0;

    for(int i = 0;i < vI.size();i++) total+= vI[i];

    return total;
}
