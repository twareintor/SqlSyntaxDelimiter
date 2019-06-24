#include <stdio.h>
#include <stdlib.h>

/**
 * IN DEVELOPMENT! IN DEVELOPMENT! IN DEVELOPMENT! 
 * Getting the text between two quotes (between two identical characters sent to function as the last argument
 * "szQuote" - e.g.: form "select * from Tpl where lcase(Description) like "%high%press%" or lcase(DescriptionDe)
 * like "%hoch%dr%" will get the "%high%press%" and "%hoch%dr%" as well. Recurrent function: provide szPos = szCode
 * always; the function will provide the currently calcluated szPos at the next run.
 */
int getCurrentQuotes(char** szText, const char* szCode, const size_t codeSize, const char* szPos, const char szQuote);

