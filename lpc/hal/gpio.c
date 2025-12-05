#include"hal.h"

/* port0:
 * 31 .. 0
 * - 24, 26, 27
 * 31 is output only
 *
 * port1:
 * 31 .. 16
 */

/*Usage: use pinsel() first, FIOxDIR set bit to 1 if output, FIOxSET set bit to 1 to high, FIOxCLR set bit to 1 to clear*/
