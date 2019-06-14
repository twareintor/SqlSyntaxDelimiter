/** 
RE: detect and extract subqueries last go's Remake: see comment inside the code: This (last one) works! 
go ahead and perfect it!
 */
/*
the detection of the quoted text works pretty well
The detection of the subqueries must be completely reworked: 
    Detect first if we are inside a pair of parantheses (inside a block) then search for the
    first block in this block to be 'select'; that's all
NOTE: the actual version doesn't work if the current check position is inside another group of parantheses
    REWORK

*/

/** Permanent link: http://rextester.com/OMAM60845 */
/** Microsoft (R) C/C++ Optimizing Compiler Version 19.00.23506 for x86 */
/** Get subqueries from a SQL string */
/** code by Twareintor */
/** DISCLAIMER: not fully tested and implemented, no responsibility for results */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>


char szTestCode[] = 
    "select ID, KKS, Sig from (select * from (select * from Export01 where KKS not in (select distinct KKS from Excluded where Project not like '%1997%' or false)) where KKS not like '%XXX%') where KKS like '% C%' and isnumeric(right(Sig, 2)) and Sig like '____';";                                 
/** "0000000000000000111111111111111122222222222222223333333333333333444444444444444455555555555555556666666666666666777777777777777778888888888888889999999999999999aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbccccccccccccccccddddddddddddddddeeeeeeeeeeeeeeeeffffffffffffffff";*/                                                                                    
/** "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";*/

char szTestCode2[] = 
    "select id, class, selection from (select * from (select * from Threads where description not like '%(%)%' and (selected = true or deselected = false))) where isNum() sqlstr like 'select * from % where sopen=1 or portId>25 and type=1 and deselected=false;';";                                 
/** "0000000000000000111111111111111122222222222222223333333333333333444444444444444455555555555555556666666666666666777777777777777778888888888888889999999999999999aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbccccccccccccccccddddddddddddddddeeeeeeeeeeeeeeeeffffffffffffffff";*/                                                                                    
/** "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef";*/

char szTestCode3[] = 
    "update Queries, TestPoints set updated=true, date=time(null), String=\"select % from TestPoints where Sig like '%CT%' and DesId in (select DesId from Checked where UsrId=3209 and Year(ChkDate)>2003) order by ChkDate desc;\" where User=3209 and Descr like \"C*\";";                                 
/** "000000000000000011111111111111112222222222222222333333333333333344444 4444444444455555555555555556666666666666666777777777777777778888888888888889999999999999999aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbccccccccccccccccdddddddddd ddddddeeeeeeeeeeeeeeeefffffffffff fff ff";*/                                                                                    
/** "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef01234 56789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789 abcdef0123456789abcdef0123456789a bcd ef";*/


int getCurrentQuotes(char** szText, const char* szCode, const size_t codeSize, const char* szPos, const char szQuote);

int getCurrentSubquery(char** szText, const char* szCode, const size_t codeSize, const char* szPos);

int getCurrentSubquery2(char** szText, const char* szCode, const size_t codeSize, const char* szPos);

void test__getCurrentSubquery();
void test__getCurrentQuotes();

int main(void)
{
    test__getCurrentSubquery();
    // test__getCurrentQuotes(); 

    printf("Hello, world!\n");
    return 0;
}

void test__getCurrentQuotes()
{
    char** szText = GlobalAlloc(GPTR, 2*sizeof(char*));
    char* szCode = GlobalAlloc(GPTR, sizeof(szTestCode2)+1);
    memcpy(szCode, szTestCode2, sizeof(szTestCode2));
    int i;
    
    for(i=0x00; i<0x100; i++)
    {
        printf("0x%02x\t", i);
        char* szPos = szCode+i;
        if(0==getCurrentQuotes(szText, szCode, strlen(szCode), szPos, '\''))
        {
            size_t len = szText[1]-szText[0];
            printf("len = 0x%x\t", len);
            char* szQuot = GlobalAlloc(GPTR, len*sizeof(char)+1);
            memcpy(szQuot, szText[0], len);
            printf("%s\n", szQuot);
            GlobalFree(szQuot);
            
        }
        else
        {
            printf("not inside quotes (not text)\n");
        }
    }
    if(szCode) GlobalFree(szCode);
    if(szText) GlobalFree(szText);
    
}

void test__getCurrentSubquery()
{
    char** szText = GlobalAlloc(GPTR, 2*sizeof(char*));
    char* szCode = GlobalAlloc(GPTR, sizeof(szTestCode2)+1);
    memcpy(szCode, szCode, sizeof(szCode));
    int i;
    /*******/
    for(i=0xff; i>=0; i--)
    {
        // if(i!=0xe8) continue;
        printf("0x%02x\t%c\t", i, szCode[i]);
        char* szPos = szTestCode+i;
        if(0==getCurrentSubquery(szText, szTestCode, strlen(szTestCode), szPos))
        {
            /** printf("%zx, %zx\n", szText[0], szText[1]); */
            printf("len = %d\t", szText[1]-szText[0]);
            char* szSubquery = GlobalAlloc(GPTR, szText[1]-szText[0]+1);
            if(memcpy(szSubquery, szText[0], szText[1]-szText[0]))
            {
                /** memset(szSubquery+(szText[1]-szText[0]), '\0', 1); */
                printf("%s\n", szSubquery);
            }
            else
            {
                printf("memcpy failed\n");
            }
            GlobalFree(szSubquery);
        }
        else
        {
            printf("no subquery\n");
        }
    }
    GlobalFree(szCode);
    /*******/
    if(szText) GlobalFree(szText);
    
}

int getCurrentSubquery2(char** szText, const char* szCode, const size_t codeSize, const char* szPos)
{
    if(!szPos) return -3429;
    
    while(0);
    
}

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


