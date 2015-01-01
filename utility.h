#ifndef UTILITY_H
#define UTILITY_H
#include "QString"


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
};

#endif // UTILITY_H
