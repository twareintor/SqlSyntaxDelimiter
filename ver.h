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


/** ******************** */
#define VER_MAJOR "000"
#define VER_MINOR "000"
/** ******************** */
#define VER_ALPHA
#define VER_BETHA

#if defined(VER_ALPHA)
#define _VL "A"
#elif defined(VER_BETA)
#define _VL "B"
#else
#define _VL "R"
#endif
/** ******************** */
#define VER_COMPILED "12"
/** ******************** */
#define VER_AUTHOR "Claudiu \"Twareintor\" Ciutacu"
#define VER_COPYRIGHT  "2002-2019" " " VER_AUTHOR
/** ******************** */
#define VER_COMMENT \
    "SQL variable and macro interpreter. Simply replacing the macros "\
    "with their definitions and variables with their definitions too"
/** ******************** */
#define VER_INFO_01 VER_MAJOR "." VER_MINOR "." _VL VER_COMPILED "\n" 
#ifdef VER_COPYRIGHT
#define VER_INFO_02 VER_INFO_01 "\nCopyright (c) " VER_COPYRIGHT "\n"
#elif defined(VER_AUTHOR)
#define VER_INFO_02 VER_INFO_01 "\nAuthor: " VER_AUTHOR "\n"
#else
#define VER_INFO_02 ""
#endif
#ifdef VER_COMMENT
#define VER_INFO_03 "\nVersion comment:\n" VER_COMMENT "\n"
#else
#define VER_INFO_03
#endif
/* ******************** */
#define VERSION_INFO VER_INFO_01 VER_INFO_02 VER_INFO_03
/* ******************** */


