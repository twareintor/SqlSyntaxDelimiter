
#include "subqueries.h"

int getCurrentSubquery(char** szText, const char* szCode, const size_t codeSize, const char* szPos)
{
    if(!szPos) return -3234;
    const char* szKey = "select";
    int isOoScope; /** if 'out of scope' means is inside a closed pair of (), if 0 is in scope */
    isOoScope = 0;
    while(szPos>=szCode && szPos<=(szCode+codeSize))
    {
        if(0==isOoScope)
        {
            if(*szKey==*szPos) /** if the 's' from 'select' fits... */
            {
                if(!memcmp(szKey, szPos, 6)) /** if the whole word 'select' fits... */
                {
                    if(!(0x61<*(szPos-1)&&*(szPos-1)<0x7a || 0x61<*(szPos+strlen(szKey))&&*(szPos+strlen(szKey))<0x7a))
                    { /** ... if not a letter, then */
                        szText[0] = szPos;
                        if(szPos==szCode) /** if is at the very beginning... */
                        {
                            szText[1] = szCode+codeSize;
                            return 0;
                        }
                        else
                        {
                            int nOdd = 1;
                            while(nOdd && szPos<(szCode+codeSize))
                            {
                                nOdd+=((0x28==*szPos)-(0x29==*szPos));
                                szPos++;
                            }
                            szText[1] = szPos-1;
                            return 0;
                        }   
                    }
                }
            }
        }
        szPos--;
        isOoScope+=((0x29==*szPos)-(0x28==*szPos));
        if(isOoScope<0) isOoScope = 0; /** no way to became negative, when cursor inide a () with no select */
        
    }
    return -3209;
}

