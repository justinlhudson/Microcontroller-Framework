/*-----------------------------------------------------------------------------
 * 
 * Released: <2009/11/28>
 * Modified: <YEAR/MONTH/DAY>
 * 
 * Description: Used to set memory vector table pointers.
 * 
 *-----------------------------------------------------------------------------
 */

#ifndef _MEMORY_MAP_H_ //if not defined
#define _MEMORY_MAP_H_ //define

#include <memory.h>

namespace Core
{

  volatile struct MemoryMap_Type
  {
    //place any data type here to share such as structs, ints, strings...
  };
  typedef struct MemoryMap_Type *MEMORY_MAP;  //make pointer
  typedef MEMORY_MAP SharedMemory;  //define pointer

  /*
    Note: Example to map memmory to specific address using the vector table.
   */

  /* Example:
    #include <sys/kernel.h> 
    #define MEMORY_LOCATION(VECTOR_TABLE) 0x123123 //master memory struct pointer to actual location in memory
    master_memory_tag memory_map = (SharedMemory)*MEMORY_LOCATION; 
   */
};

#endif
