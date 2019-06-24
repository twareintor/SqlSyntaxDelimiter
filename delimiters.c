
#include "delimiters.h"


int getCurrentQuotes(char** szText, const char* szCode, const size_t codeSize, const char* szPos, const char szQuote)
{
    if(!szPos) return -3449;
    size_t i = 0; /** to let unchanged the szCode */
    size_t pos = szPos-szCode;
    int nOdd = 0; /** switches 1/0/1/0 with every found qualifier; if 1 till szPos, is inside (odd nr. of '-s) */
    while(i<=(szPos-szCode))
    {
        if(szQuote==*(szCode+i))
        {
            nOdd = !nOdd;
            if(nOdd)
            {
                szText[0] = szCode+i+1; /** do not include the begin quote */
            }
        }
        i++;
    }
    if(nOdd)
    {
        while(i<codeSize)
        {
            if(szQuote==*(szCode+i))
            {
                szText[1] = szCode+i; /** do not include the end quote */
                return 0;
            }
            i++;
        }
    }
    else
    {
        szText[1] = szCode+codeSize;
        return -3222;
    }
    return -3209;
}


