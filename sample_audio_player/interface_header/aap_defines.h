
/*******************************************************************************
 *
 *   ALLGO EMBEDDED SYSTEMS CONFIDENTIAL PROPRIETARY
 *
 *   (C) 2015-16 ALLGO EMBEDDED SYSTEMS INDIA PVT. LTD.
 *
 *   FILENAME       - aap_defines.h
 *
 *   COMPILER       - <gcc 4.6.3 or similar>
 *
 *******************************************************************************
 *   CHANGE HISTORY
 *   ---------------------------------------------------------------------------
 *   DATE           REVISION      COMMENTS
 *   ---------------------------------------------------------------------------
 *   03/03/2015     1.0           Initial version
 *   29/06/2015     1.1           New definition for media data.
 *   10/07/2015     1.2           New definition for phone status.
 *   20/02/2018     1.3           Updated description
 *******************************************************************************
 *  File Description
 *  ---------------------
 *  This file contains all the macros used in AAP SDK
  ******************************************************************************/
#ifndef _AAP_DEFINES_H_
#define _AAP_DEFINES_H_

/*! \file aap_defines.h
\brief Includes the macros needed for AAP SDK
*/

/*! Default string length in bytes */
#define  AAP_DEFAULT_STRING_LEN 256
/*! Small string length in bytes */
#define  AAP_SMALL_STRING_LEN 64
/*! Maximum time out value of synchronous APIs in seconds */
#define  AAP_API_MAX_TIME_OUT 6
/*! Default size of LIST arrays  */
#define AAP_DEFAULT_LIST_LEN 10
/*! Small size of arrays  */
#define AAP_SMALL_ARRAY_LEN 128
/*! Default size of arrays  */
#define AAP_DEFAULT_ARRAY_LEN 256
/*! Medium size of arrays  */
#define AAP_MEDIUM_ARRAY_LEN 512
/*! Large size of arrays  */
#define AAP_LARGE_ARRAY_LEN 2048
/*! Invalid vehicle data */
#define AAP_INVALID_VEHICLE_DATA  (-1)
/*! Maximum number of touch inputs*/
#define AAP_MAX_NUM_TOUCH_INPUT (10)
/*! Driver sits on the left e.g. US */
#define AAP_DRIVER_POSITION_LEFT   (0x001)
/*! Driver sits on the right e.g. UK, India */
#define AAP_DRIVER_POSITION_RIGHT   (0x002)
/*! Driver sits in the center e.g. Formula 1. */
#define AAP_DRIVER_POSITION_CENTRE (0x003)
/*! Driver position is unknown. */
#define AAP_DRIVER_POSITION_UNKNOWN (0x004)
/*! BT pairing methods */
/*! Secure simple pairing(Currently Not Supported) */
#define AAP_BT_PAIRING_OOB  (0x004)
/*! Both sides display a number, user authorizes */
#define AAP_BT_PAIRING_NUMERIC (0x005)
/*! Passkey based pairing(Currently Not Supported) */
#define AAP_BT_PAIRING_PASSKEY (0x006)
/*! Pin based pairing*/
#define AAP_BT_PAIRING_PIN (0x007)
/*! Video fps 60 */
#define AAP_VIDEO_FPS_60 (60)
/*! Video fps 30*/
#define AAP_VIDEO_FPS_30 (30)
/*! Maximum number of tires */
#define AAP_MAX_NUM_TIRE 4
/*! Maximum number of doors */
#define AAP_MAX_NUM_DOOR 4
/*! Maximum number of satelites */
#define AAP_MAX_NUM_SATELITE 50
/*! Maximum BT pairing methods supported by HU */
#define AAP_MAX_BT_PAIRING_METHOD 4
/*! Maximum number of media sources */
#define AAP_MAX_NUM_MEDIA_SOURCES 10
/*! Maximun number of playlist */
#define AAP_MAX_NUM_PLAYLIST 20
/*! Maximun number of song list */
#define AAP_MAX_NUM_SONG_LIST 500
/*! Maximum album art length */
#define AAP_MAX_ALBUM_ART_LEN (200*1024)
/*! Maximum digit of a phone number */
#define AAP_MAX_DIGIT_IN_PHONE_NUMBER 20
/*! Maximum simultaneous number of calls allowed */
#define AAP_MAX_NUM_CALL_ALLOWED 5
/*! Maximum caller ID length */
#define AAP_MAX_CALLER_ID_LEN 30
/*! Audio device path */
#define AAP_MAX_AUDIO_DEVICE_PATH 64
/*! Maximum number of sensors */
#define AAP_MAX_NUM_SENSORS 22
/*! Maximum number of fuel types */
#define AAP_MAX_NUM_FUEL_TYPES 12
/*! Maximum number of connector types */
#define AAP_MAX_NUM_CONNECTOR_TYPES 11
/*! Default viewing distance between HU and eye in millimeters.
 * This is purely our assumption */
#define AAP_DEFAULT_VIEWING_DISTANCE 450
/*! Maximum number of device connections */
#define AAP_MAX_DEVICES_CONNECTIONS 15
/*! Maximum bytes for Device name */
#define AAP_MAX_DEVICE_NAME 64
/*! Maximum bytes for Device serial ID */
#define AAP_MAX_DEVICE_SERIAL_ID 64
/*! Maximum number of input devices. Ex: TouchScreeen, TouchPad, Key input */
#define AAP_MAX_INPUT_DEVICES_TYPE 3
/*! Maximum number of Radio endpoints */
#define AAP_MAX_RADIO_ENDPOINTS 2
/*! Maximum number of key codes that can be registered */
#define AAP_MAX_NUM_KEY_CODES 277
/*! Maximum supported video resoultions */
#define AAP_MAX_VIDEO_RESLNS 3
/*! This values are based on typical certificates size */
/*! Maximum Root Certificate file data length */
#define MAX_SSL_ROOT_CERT_LEN 2000
/*! Maximum Client Certificate file data length */
#define MAX_SSL_CLIENT_CERT_LEN 2000
/*! Maximum Client Private Key file data length */
#define MAX_SSL_CLIENT_KEY_LEN 2000
/*! Maximum status features that an application can subscribe */
#define AAP_SUBSCRIPTION_LIST_LEN 6
/*! Maximum number of WiFi frequency channels */
#define AAP_MAX_WIFI_CHANNELS 10
/*! Minimum touchpad sensitivity value */
#define AAP_MIN_TOUCHPAD_SENSITIVITY 1
/*! Maximum touchpad sensitivity value */
#define AAP_MAX_TOUCHPAD_SENSITIVITY 10
/*! Touch screen input device path */
#define AAP_MAX_INPUT_DEV_PATH 128

/*! \brief Maximum number of threads that can be configured for priority.
 * Presently MAX_CONFIGURABLE_AAP_THREADS number of threads can be configured. */
#define MAX_CONFIGURABLE_AAP_THREADS                (7)

/*! \brief Transport reader thread which reads data from transport endpoints
 * USB bulk/TCP socket (for USB/Wi-Fi device resp.) and copy data to a circular buffer*/
#define AAP_THREAD_INDEX_TRANS_READER               (0)
/*! \brief GAL reader thread which reads data from circular buffer and give it to
 * GAL for data processing. */
#define AAP_THREAD_INDEX_GAL_READER                 (1)
/*! \brief GAL writer thread which writes data to transport endpoint USB bulk/TCP socket
 * (for USB/Wi-Fi device resp.) */
#define AAP_THREAD_INDEX_GAL_WRITER                 (2)
/*! \brief Media Channel workqueue queues all the audio data received on Media
 * Channel in a workqueue whose thread deques and feeds it to the audio player. */
#define AAP_THREAD_INDEX_AUDIO_MEDIA                (3)
/*! \brief Guidance channel workqueue queues all the audio data received on Guidance
 * Channel in a workqueue and the workqueue thread deques and feeds it to the audio player. */
#define AAP_THREAD_INDEX_AUDIO_GUIDANCE             (4)
/*! \brief Video Sink workqueue queues all the video data received from the
 * phone in a workqueue and the workqueue thread deques and feeds it to the video player. */
#define AAP_THREAD_INDEX_VIDEO_SINK                 (5)
/*! brief Audio source thread that Reads the data from microphone and sends it
 * to the phone. */
#define AAP_THREAD_INDEX_AUDIO_RECORDER             (6)

#endif /*_AAP_DEFINES_H_*/

