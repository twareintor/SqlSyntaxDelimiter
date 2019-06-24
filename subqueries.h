#include <stdio.h>
#include <stdlib.h>


/**
 * Function getting a subquery in an embedded-query string. 
 * E.g.: form "select * from TestPointList where id = (select ModId from DesignList where PicId = mid(PlanId, 3, 3))"
 * the first argument "*szText" will be "select ModId from DesignList where PicId = mid(PlanId, 3, 3)"
 * Supports as many levels as technically possible through using recurrence - for this, is szPos necessary.
 * Call this function only with szPos = szCode: it will call itself with the currently calculated szPos
 * See the comments inside the function(s) for details
 */
int getCurrentSubquery(char** szText, const char* szCode, const size_t codeSize, const char* szPos);


