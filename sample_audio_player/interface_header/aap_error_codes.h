/*******************************************************************************
 *
 *   ALLGO EMBEDDED SYSTEMS CONFIDENTIAL PROPRIETARY
 *
 *   (C) 2015-16 ALLGO EMBEDDED SYSTEMS INDIA PVT. LTD.
 *
 *   FILENAME       - aap_error_codes.h
 *
 *   COMPILER       - <gcc 4.6.3 or similar>
 *
 *******************************************************************************
 *   CHANGE HISTORY
 *   ---------------------------------------------------------------------------
 *   DATE           REVISION      COMMENTS
 *   ---------------------------------------------------------------------------
 *   03/03/2015      1.0          Initial version
 *   20/02/2018      1.1          Updated description
 *******************************************************************************
 *  File Description
 *  ---------------------
 *  This file provides all the error codes definitions
  ******************************************************************************/
#ifndef _AAP_ERROR_CODES_H_
#define _AAP_ERROR_CODES_H_
/*! \file aap_error_codes.h
\brief Includes all the error code definitions
*/
/*! Success value */
#define AAP_SUCCESS (0)
/*! Error failure */
#define AAP_FAILURE (-1)
/*! Invalid handle passed */
#define AAP_ERR_INVALID_HANDLE (0x100)
/*! Invalid parameters */
#define AAP_ERR_INVALID_PARAMS (0x101)
/*! System call failed. Application can retry on this error.
 * If the same error occurs repeatedly, application has to restart the service. */
#define AAP_ERR_SYS_CALL_FAILED (0x102)
/*! Memory allocation failed. Application may try to free up the memory already
 * allocated. */
#define AAP_ERR_OUT_OF_MEM (0x103)
/*! Time out error */
#define AAP_ERR_TIMEOUT (0x104)
/*! Service not responding */
#define AAP_ERR_SERVICE_NOT_RESPONDING (0x105)
/*! Invalid response received */
#define AAP_ERR_INVALID_RESPONSE (0x106)
/*! Session state is invalid. Pre-condition may be rechecked */
#define AAP_ERR_INVALID_SESSION (0x108)
/*! Interface is busy in waiting for some response
 * Application must retry the same request*/
#define AAP_ERR_IFACE_BUSY (0x109)
/*! Service is busy in processing some requests
 *  Application must retry the same request*/
#define AAP_ERR_SERVICE_BUSY (0x10A)
/*! Caller not meet the precondition(s). Check for the respective API's
 * pre-condition.*/
#define AAP_ERR_PRECOND_NOT_MET (0x10B)
/*! Invalid request from application.
 * Possible reason could be outdated aap_service or libaap_interface.so library. */
#define AAP_ERR_INVALID_REQ (0x10C)
/*! AAP service process died. AAP service needs to be started and application
 * has to create a new session. */
#define AAP_ERR_SERVICE_DIED (0x10D)
/*! When MD is not responding */
#define AAP_ERR_MD_STOPPED (0x10F)
/*! Unsupported Video configuration */
#define AAP_ERR_UNSUPPORTED_VIDEO_CONFIG (0x111)
/*! SSL authentication failure (only in start session) */
#define AAP_ERR_SSL_AUTH_FAILURE (0x112)
/*! Data framing error. It could be due to I/O operation error or SSL
 * decryption error. The recommended course of action is to reset the
 * usb link at this point. A re-establishment of the GAL connection may
 * be attempted after that */
#define AAP_ERR_FRAMING (0x113)
/*! In case of unknown error */
#define AAP_ERR_UNKNOWN (0x114)
/*! Application can retry */
#define AAP_ERR_RETRY (0x115)
/*! If the VEC data is more than the MAX supported data size */
#define AAP_ERR_MAX_VEC_SIZE (0x116)
/*! When session is already started */
#define AAP_ERR_SESSION_ALREADY_STARTED (0x117)
/*! Transport read/write error */
#define AAP_ERR_TRANS_READ_WRITE (0x118)
/*! This aap_service version is not compatible with AAP SDK library */
#define AAP_SERVICE_VERSION_INCOMPATIBILITY (0x119)
/*! This error comes when there is some problem with AAP connection.
 * Under such conditions, application should start fresh AAP session */
#define AAP_ERR_AAP_HAS_STOPPED (0x120)
/*! This is the notification to the application that device switch happened
 * successfully. */
#define AAP_DEVICE_SWITCH_SUCCESS (0x121)
/*! This is the notification to the application that device switch failed. */
#define AAP_DEVICE_SWITCH_FAILED (0x122)
/*! SSL authentication failure since SSL certificates are not yet valid (only in start session) */
#define AAP_ERR_SSL_AUTH_FAILURE_CERT_NOT_YET_VALID (0x123)
/*! SSL authentication failure since SSL certificates are expired (only in start session) */
#define AAP_ERR_SSL_AUTH_FAILURE_CERT_EXPIRED (0x124)
/*! This error code will be sent when AAP session is connected over Wi-Fi and its signal strength is low.
 * This is could be due to MD is far away from the HU.
 * When this error is received by Application should notify user to place MD near to the HU's Wi-Fi AP. */
#define AAP_ERR_WIFI_LOW_SIGNAL (0x125)
/*! This error comes when Application tries to send more than AAP_MAX_DEVICES_CONNECTIONS
 * number of devices through #aap_supported_device_list() API. */
#define AAP_ERR_EXCEED_MAX_NUM_DEV (0x126)
/*! This error indicates that Application called aap_start_session() API with a
 * device which is not switched to AOA mode */
#define AAP_ERR_DEV_NOT_IN_AOA (0x127)
/*! This error indicates that Application called aap_start_session() API with a
 * device for which TCP connection is not received from MD. */
#define AAP_ERR_NO_TCP_CONNECTION (0x128)

#endif /*_AAP_ERROR_CODES_H_*/
