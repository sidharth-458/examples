/**
 * first pinsel, then use setval.
 */
#define SETVAL(bias, val) DACR = ((bias <<16) | val<<6)

