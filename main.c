#include "ver.h"

#include <windows.h>

#include "testData.h"
#include "delimiters.h"
#include "subqueries.h"
#include "subqueries.c"

/**
 * Test getting the text included between quotation marks. 
 * see "getCurrentQuotes()" function for full description
 */
void test__getCurrentSubquery();


/** 
 * Test getting subqueries in a query.
 * See "getCurrentSubquery()" description for more info about the tested function.
 */
void test__getCurrentQuotes();

/** return function */
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


