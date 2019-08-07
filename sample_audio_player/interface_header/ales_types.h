/*******************************************************************************
 *
 *   ALLGO EMBEDDED SYSTEMS CONFIDENTIAL PROPRIETARY
 *
 *   (C) 2012 ALLGO EMBEDDED SYSTEMS INDIA PVT. LTD.
 *
 *   FILENAME       - ales_types.h
 *
 *   COMPILER       - <gcc 4.4.4>
 *
 *******************************************************************************
 *   CHANGE HISTORY
 *   ---------------------------------------------------------------------------
 *   DATE            Description                       AUTHOR
 *   ---------------------------------------------------------------------------
 *  09/04/2013      Initial Version                    Manjari S
 *  19/06/2014      Modifications done to make
 *                  OSAL common for all projects        Yamuna
 *******************************************************************************
 *  File Description
 *  ---------------------
 *  This file defines typdefs for standard data types in C.
 *
 ******************************************************************************/

/*! \file ales_types.h
    \brief Contains all the typedefs for C standard data types.

    This file gives the complete list of standard data type typedefs only.
*/

#ifndef _ALES_TYPES_H_
#define _ALES_TYPES_H_

#include <stddef.h>
#include <stdio.h>
#if defined (_IRTOS)
#include "OS/OS_abstract.h"
#elif !defined (TARGET_OS_WEC7)
#include <semaphore.h>
#endif /* if defined (_IRTOS) elif !defined (TARGET_OS_WEC7) */


#ifdef __cplusplus
    extern "C" {
#endif

/*! \brief typedef char ALES_CHAR
Datatype to store signed character data
*/
typedef char ALES_CHAR;

/*! \brief typedef unsigned char ALES_UCHAR
Datatype to store unsigned character data
*/
typedef unsigned char ALES_UCHAR;

/*! \brief typedef unsigned char ALES_BYTE
Datatype to store one byte unsigned data
*/
typedef unsigned char ALES_BYTE;

/*! \brief typedef unsigned char ALES_BYTE
Datatype to store 8 bit signed value
*/
typedef signed char ALES_INT8;

/*! \brief typedef unsigned char ALES_UINT8
Datatype to store 8 bit unsigned value
*/
typedef unsigned char ALES_UINT8;

/*! \brief typedef signed short int ALES_INT16
Datatype to store signed short data
*/
typedef signed short ALES_INT16;

/*! \brief typedef unsigned short int ALES_UINT16
Datatype to store unsigned short data
*/
typedef unsigned short ALES_UINT16;

/*! \brief typedef signed int ALES_INT32
Datatype to store signed integer data
*/
#if !defined (TARGET_OS_WEC7) && !defined (_IRTOS)
typedef signed int ALES_INT32;
#else
typedef int ALES_INT32;
typedef ALES_INT32 key_t;
typedef ALES_INT32 clockid_t;
typedef wchar_t ALES_CHAR16;
#define CLOCK_REALTIME 1
#endif /* if !defined (TARGET_OS_WEC7) && !defined (_IRTOS) */

/*! \brief typedef unsigned int ALES_UINT32
Datatype to store unsigned integer data
*/
typedef unsigned int ALES_UINT32;

#if defined(__LP64__) || defined(_LP64)

/*! \brief typedef signed long ALES_INT64
Datatype to store signed long data
*/
typedef signed long  ALES_INT64;

/*! \brief typedef unsigned long ALES_UINT64
Datatype to store unsigned long data
*/
typedef unsigned long ALES_UINT64;

#else

/*! \brief typedef signed long long ALES_INT64
Datatype to store signed long long data
*/
typedef signed long long ALES_INT64;

/*! \brief typedef unsigned long long ALES_UINT64
Datatype to store unsigned long long data
*/
typedef unsigned long long ALES_UINT64;

#endif /* defined(__LP64__) || defined(_LP64) */

/*! \brief typedef signed long ALES_LONG
Datatype to store signed long data
*/
typedef signed long ALES_LONG;

/*! \brief typedef unsigned char ALES_BOOL
Datatype to store boolean data
*/
typedef unsigned char ALES_BOOL;

/*! \brief typedef float ALES_FLOAT
Datatype to store floating point numbers
*/
typedef float ALES_FLOAT;

/*! \brief typedef double ALES_DOUBLE
Datatype to store double value
*/
typedef double ALES_DOUBLE;

/*! \brief void data type */
typedef void ALES_VOID;

/*! \brief typedef ALES_UINT32 ALES_Status */
typedef ALES_UINT32 ALES_Status;

/*! \brief typedef size_t ALES_SIZE_T */
typedef size_t ALES_SIZE_T;

#if !defined (TARGET_OS_ANDROID) && !defined (_IRTOS)
/*! \brief typedef time_t ALES_TIME_T */
typedef time_t ALES_TIME_T;
#else
typedef long int ALES_TIME_T;
#endif /* if !defined (TARGET_OS_ANDROID) && !defined (_IRTOS) */

#if defined(_IRTOS)
#define sem_t SysSema_t
#endif /* if defined(_IRTOS) */

#if defined (_IRTOS)
typedef FS_File_t ALES_FILE;
#else
/*! \brief typedef FILE ALES_FILE */
typedef FILE ALES_FILE;
#endif /* if defined(_IRTOS) */

#ifndef TARGET_OS_WEC7
/*! \brief typedef sem_t ALES_SEM_T */
typedef sem_t ALES_SEM_T;
#else
typedef void ALES_SEM_T;
#endif /* ifndef TARGET_OS_WEC7 */

/*! \brief To suppress unused variable warning */
#define OSAL_UNUSED_PARAMS(val) (void)val

/*! \brief FALSE 0 */
#ifndef FALSE
#define FALSE 0
#endif /* ifndef FALSE */

/*! \brief TRUE 1 */
#ifndef TRUE
#define TRUE 1
#endif /* ifndef TRUE */

/*! \brief INFINITE 0xFFFFFFFF */
#ifndef TARGET_OS_WEC7
#define INFINITE 0xffffffff
#endif /* ifndef TARGET_OS_WEC7 */

#ifdef __cplusplus
    }
#endif

#endif /* _ALES_TYPES_H_ */
