/*******************************************************************************
 *
 *   ALLGO EMBEDDED SYSTEMS CONFIDENTIAL PROPRIETARY
 *
 *   (C) 2015-16 ALLGO EMBEDDED SYSTEMS INDIA PVT. LTD.
 *
 *   FILENAME       - aap_standard_types.h
 *
 *   COMPILER       - <gcc 4.6.3 or similar>
 *
 *******************************************************************************
 *   CHANGE HISTORY
 *   ---------------------------------------------------------------------------
 *   DATE           REVISION      COMMENTS
 *   ---------------------------------------------------------------------------
 *   02/03/2015     1.0           Initial version
 *******************************************************************************
 *  File Description
 *  ---------------------
 *  Standard data types
  ******************************************************************************/
#ifndef _AAP_STANDARD_TYPE_H_
#define _AAP_STANDARD_TYPE_H_

#if defined __cplusplus
    extern "C" {
#endif

#include "ales_types.h"

/*! \file aap_standard_types.h
\brief Includes the standard data types used in AAP SDK.
*/
/*! \name TRUE and FALSE constants
 * \n
 * Defines the value for TRUE and FALSE constant
 * \n
 */
/*! \{ */
/*! \brief TRUE (1) */
#define AAP_TRUE 1
/*! \brief FALSE (0) */
#define AAP_FALSE 0
/*! \} */


/*! \typedef ALES_CHAR AAP_CHAR
    Datatype to store signed character data
*/
typedef ALES_CHAR AAP_CHAR;

/*! \typedef ALES_UCHAR AAP_UCHAR
  * Datatype to store unsigned character data
*/
typedef ALES_UCHAR AAP_UCHAR;

/*! \typedef ALES_BYTE AAP_BYTE
    Datatype to store one byte unsigned data
*/
typedef ALES_BYTE AAP_BYTE;

/*! \typedef ALES_INT16 AAP_INT16
    Datatype to store signed short data
*/
typedef ALES_INT16 AAP_INT16;

/*! \typedef ALES_UINT16 AAP_UINT16
   Datatype to store unsigned short data
*/
typedef ALES_UINT16 AAP_UINT16;

/*! \typedef ALES_INT32 AAP_INT32
    Datatype to store signed integer data
*/
typedef ALES_INT32 AAP_INT32;

/*! \typedef ALES_UINT32 AAP_UINT32
    Datatype to store unsigned integer data
*/
typedef ALES_UINT32 AAP_UINT32;

/*! \typedef ALES_INT64 AAP_INT64
    Datatype to store signed long data
*/
typedef ALES_INT64 AAP_INT64;

/*! \typedef ALES_UINT64 AAP_UINT64
    Datatype to store signed long data
*/
typedef ALES_UINT64 AAP_UINT64;

/*! \typedef ALES_LONG AAP_LONG
    Datatype to store signed long data
*/
typedef ALES_LONG AAP_LONG;

/*! \typedef ALES_BOOL AAP_BOOL
    Datatype to store boolean data
*/
typedef ALES_BOOL AAP_BOOL;

/*! \typedef ALES_FLOAT AAP_FLOAT
    Datatype to store floating point numbers
*/
typedef ALES_FLOAT AAP_FLOAT;

/*! \typedef ALES_VOID AAP_VOID
    Datatype to store floating point numbers
*/
typedef ALES_VOID AAP_VOID;

/*! \typedef AAP_INT32 AAP_RetType
 *  Return type of AAP functions
 */
typedef AAP_INT32 AAP_RetType;

/*! \typedef ALES_SIZE_T AAP_SIZE_T
 * Size of this data type is dependent on platform
 */
typedef ALES_SIZE_T AAP_SIZE_T;

/*! \typedef ALES_SEM_T AAP_SEM_T
 * Size of this data type is dependent on platform
 */
typedef ALES_SEM_T AAP_SEM_T;

/*! \typedef ALES_TIME_T AAP_TIME_T
 * Size of this data type is dependent on platform
 */
typedef ALES_TIME_T AAP_TIME_T;
#if defined __cplusplus
    }
#endif

#endif /* _AAP_STANDARD_TYPE_H_ */
