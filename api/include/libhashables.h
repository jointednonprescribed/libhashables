
#ifndef _LIBHASHABLES_
#define _LIBHASHABLES_ 1



/* Header Dependency Tree:
 *
 * |   : Top file is a dependency of the bottom file.
 * | | : Both files include each other at their own separate
 *       points in each file.
 *
 *   libhashables/
 *     config.h
 *      | |
 *     def.h
 *      |
 *     platform.h
 *      |
 *     includes.h
 *      |
 *     exceptions.h
 *      |
 *     loggingapi.h
 *      |
 *     memoryapi.h
 *      |
 *     table.h
 *
 * Include from the bottom(s) of the header inclusion tree. */
#include "libhashables/table.h"



#endif // _LIBHASHABLES_
