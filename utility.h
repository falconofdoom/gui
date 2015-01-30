#ifndef UTILITY_H
#define UTILITY_H
#include "QString"
#include "QVector"


/**
 * @brief The Utility class for reusable code
 */
class Utility
{
public:
    Utility();

    /**
     * @brief Utility::intToMonth - converts an integer from 1-12 such that
     * the resulting string is a month which corresponds to that integer
     * @param i
     * @return
     */

    static QString intToMonth(int i);

    /**
     * @brief accumulate combines separated data fields from an AGM into ONE
     * @param i
     * @param vvqs
     * @return
     */
    static QString accumulate(int i,QVector < QVector < QString > > vvqs);
    /**
     * @brief sumOverErrors returns total of errors
     * @param vI
     * @return
     */
    static int sumOverErrors(QVector <int> vI);
};

#endif // UTILITY_H
