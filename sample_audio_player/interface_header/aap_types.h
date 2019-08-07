/*******************************************************************************
 *
 *   ALLGO EMBEDDED SYSTEMS CONFIDENTIAL PROPRIETARY
 *
 *   (C) 2015-16 ALLGO EMBEDDED SYSTEMS INDIA PVT. LTD.
 *
 *   FILENAME       - aap_types.h
 *
 *   COMPILER       - <gcc 4.6.3 or similar>
 *
 *******************************************************************************
 *   CHANGE HISTORY
 *   ---------------------------------------------------------------------------
 *   DATE           REVISION      COMMENTS
 *   ---------------------------------------------------------------------------
 *   02/03/2015     1.0           Initial version
 *   13/05/2015     1.1           Fixed sensor data structure.
 *   19/06/2015     1.2           Added enums and variables
 *                                to get navigation status data.
 *   26/06/2015     1.3           Fixed BT callback typedef.
 *   29/06/2015     1.4           Fixed media data structure.
 *   10/07/2015     1.5           Fixed touch structure and added
 *                                more action for multi touch.
 *   05/08/2015     1.6           Modified key event structure.
 *   20/02/2018     1.7           Removed AAPDeviceStatusCb and updated
 *                                description
 *******************************************************************************
 *  File Description
 *  ---------------------
 *  This file includes the definition of various data structures used by AAP SDK
 *******************************************************************************/

#ifndef  _AAP_TYPES_H_
#define  _AAP_TYPES_H_

#include "aap_standard_types.h"
#include "aap_defines.h"

/*! Maximum number of VEC services supported */
#define AAP_MAX_VEC_SERVICES 1
/*! Maximum number of VEC apps supported per service */
#define AAP_MAX_NUM_VEC_APPS 5
/*! Maximum length of a VEC app name */
#define MAX_VEC_APP_NAME_LENGTH 128
/*! Maximum length of a VEC service name */
#define MAX_VEC_SERVICE_NAME_LENGTH 128
/*! Maximum length of GAL Major, Mid or Minor versions */
#define MAX_GAL_VERSION_LEN 5

#if defined __cplusplus
    extern "C" {
#endif

/*! \file aap_types.h
\brief Includes all the data types needed for AAP SDK.
*/

/*! \struct AAP_Version
  * \brief Structure to specify the AllGo AAP SDK version.
  *
  */
typedef struct
{
    /*! AAP SDK Major Version */
    AAP_UINT16 uwMajor;
    /*! AAP SDK Mid Version */
    AAP_UINT16 uwMid;
    /*! AAP SDK Minor Version */
    AAP_UINT16 uwMinor;
    /*! GAL Receiver library Major Version */
    AAP_BYTE aucGalMajor[MAX_GAL_VERSION_LEN];
    /*! GAL Receiver library Mid Version */
    AAP_BYTE aucGalMid[MAX_GAL_VERSION_LEN];
    /*! GAL Receiver library Minor Version */
    AAP_BYTE aucGalMinor[MAX_GAL_VERSION_LEN];
    /*! Release Year in YY */
    AAP_UINT16 uwYear;
    /*! Release Month in MM*/
    AAP_UINT16 uwMonth;
    /*! Release Date in DD*/
    AAP_UINT16 uwDate;
}AAP_Version;

/*! \enum AAP_DevStatusType
 * \brief Defines the device status */
typedef enum
{
    /*! Device is disconnected from the Head Unit */
    AAP_DEVICE_DISCONNECTED = 0x100,
    /*! Device is connected to the Head Unit */
    AAP_DEVICE_CONNECTED
}AAP_DevStatusType;

/*! \enum AAP_DeviceType
 * \brief Defines the device connection type */
typedef enum
{
    /*! USB device */
    AAP_DEVICE_TYPE_USB = 0x1,
    /*! WiFi device */
    AAP_DEVICE_TYPE_WIFI
}AAP_DeviceType;

/*! \struct AAP_UsbMdInfo
  * \brief structure to specify the connected USB mobile device's information */
typedef struct
{
    /*! Device vendor id */
    AAP_UINT16 uwVendorId;
    /*! Device product id */
    AAP_UINT16 uwProductId;
}AAP_UsbMdInfo;

/*! \struct AAP_WifiMdInfo
  * \brief structure to specify the connected WiFi mobile device's information */
typedef struct
{
    /*! This structure is for future use */
}AAP_WifiMdInfo;

/*! \struct AAP_DeviceInfo
  * \brief structure to specify the connected mobile device's information */
typedef struct
{
    /*! Device type USB / WiFi */
    AAP_DeviceType eDeviceType;
    /*! Device name. This string can be used to display on the UI */
    AAP_CHAR acDevName[AAP_MAX_DEVICE_NAME];
    /*! Device unique serial id */
    AAP_CHAR acSerial[AAP_MAX_DEVICE_SERIAL_ID];
    union
    {
        /*! If eDeviceType is AAP_DEVICE_TYPE_USB, AAP_UsbMdInfo structure will be used */
        AAP_UsbMdInfo sUsbMdInfo;
        /*! If eDeviceType is AAP_DEVICE_TYPE_WIFI, AAP_WifiMdInfo structure will be used */
        AAP_WifiMdInfo sWifiMdInfo;
    };
 }AAP_DeviceInfo;

/*! \struct AAP_DevConnStatus
 * \brief Structure to specify Device's connection status and Device info */
typedef struct
{
    /*! Device Connection Status */
    AAP_DevStatusType eDevStatus;
    /*! Device Info : refer #AAP_DeviceInfo */
    AAP_DeviceInfo sDeviceInfo;
}AAP_DevConnStatus;

/*! \enum AAP_ThreadSchedPolicy
 * \brief Scheduling policy for a thread */
typedef enum
{
    /*! Scheduling policy is Round Robin */
    AAP_THREAD_SCHEDULING_POLICY_RR = 1,
    /*! Scheduling policy is First In First Out */
    AAP_THREAD_SCHEDULING_POLICY_FIFO
}AAP_ThreadSchedPolicy;

/*! \struct AAP_ThreadConfig
 * \brief This structure is to configure a AAP thread.
 */
typedef struct
{
    /*! This is to indicate that iPriorityValue value to be considered or not.
     * Setting to AAP_TRUE will make the iPriorityValue under consideration. */
    AAP_BOOL bIsValidPriority;
    /*! Priority value of the thread */
    AAP_INT32 iPriorityValue;
    /*! Scheduling policy. */
    AAP_ThreadSchedPolicy eThreadSchedPolicy;
    /*! This is to indicate that iAffinityValue value to be considered or not.
     * Setting to AAP_TRUE will make the iAffinityValue under consideration. */
    AAP_BOOL bIsValidAffinity;
    /*! thread affinity value. */
    AAP_INT32 iAffinityValue;
}AAP_ThreadConfig;

/*! \struct AAP_ConfigParams
 * Structure to configure AAP stack
 */
typedef struct
{
    /*! \brief Array of Priorities for various threads in AAP stack.\n
     * Here is list of threads that can be configured.\n
     * AAP_THREAD_INDEX_TRANS_READER \n
     * AAP_THREAD_INDEX_GAL_READER \n
     * AAP_THREAD_INDEX_GAL_WRITER \n
     * AAP_THREAD_INDEX_AUDIO_MEDIA \n
     * AAP_THREAD_INDEX_AUDIO_GUIDANCE \n
     * AAP_THREAD_INDEX_VIDEO_SINK \n
     * AAP_THREAD_INDEX_AUDIO_RECORDER \n
     * For an example: If the application wants to set the thread priority and affinity
     * of device transport(USB/TCP socket) reader thread -
     * asThreadConfig[AAP_THREAD_INDEX_TRANS_READER].bIsValidPriority = AAP_TRUE;
     * asThreadConfig[AAP_THREAD_INDEX_TRANS_READER].iPriorityValue = 99;
     * asThreadConfig[AAP_THREAD_INDEX_TRANS_READER].bIsValidAffinity = AAP_TRUE;
     * asThreadConfig[AAP_THREAD_INDEX_TRANS_READER].iAffinityValue = 0;
     * asThreadConfig[AAP_THREAD_INDEX_TRANS_READER].eThreadSchedPolicy = AAP_THREAD_SCHEDULING_POLICY_RR; */
    AAP_ThreadConfig asThreadConfig[MAX_CONFIGURABLE_AAP_THREADS];
}AAP_ConfigParams;

/*! \enum AAP_SessionStatus
  * \brief Enumeration to specify the various session events */
typedef enum
{
    /*! Invalid session state
     * After stop session, session will be in this state.
     * \note If stop session is called during device switch, then stop session
     * wouldn't be in invalid state if the device switch was successful.
     * For reason refer #AAP_SessionInfo->iStatus. */
    AAP_SESSION_STATE_INVALID = 0x000,
    /*! Failed to connect to the device.
     * For reason refer #AAP_SessionInfo->iStatus.
     *
     * \note Application MUST call #aap_stop_session( ) in this case.*/
    AAP_SESSION_STATE_DISCONNECTED = 0x300,
    /*! Connection takes more time. For reason refer #AAP_SessionInfo->iStatus */
    AAP_SESSION_STATE_CONNECTING,
    /*! AAP Session established.
     * For reason refer #AAP_SessionInfo->iStatus. */
    AAP_SESSION_STATE_CONNECTED,
    /*! When AAP device connected over Wi-Fi and signal strength between MD and HU is low
     * then AAP_SESSION_STATE_POOR_CONNECTIVITY will be notified with #AAP_SessionInfo->iStatus
     * contains error code AAP_ERR_WIFI_LOW_SIGNAL.
     *
     * \note When This message is received by the application/HMI, it should display native
     * message suggesting user to place the MD near the HU's Wi-Fi AP(Access Point) to avoid poor connection.*/
    AAP_SESSION_STATE_POOR_CONNECTIVITY,
    /*! \note This is only valid for AAP WiFi.
     * This status is used to notify the Application about the received TCP
     * connection from MD. Once a Wi-Fi capable AAP MD is detected and prepared,
     * i.e. as soon as the application receives a WiFi connect status with
     * STATUS_SUCCESS from MD, it should start a timer of 45 seconds
     * and wait for AAP_SESSION_STATE_TCP_CONN_RECEIVED event as part of
     * AAP_SessionStatusCb from AAP stack. If the Application receives
     * AAP_SESSION_STATE_TCP_CONN_RECEIVED event before the timer expires,
     * call start session else Application should show a popup prompting the
     * user to restart Bluetooth and WiFi on the MD. */
    AAP_SESSION_STATE_TCP_CONN_RECEIVED
}AAP_SessionStatus;

/*! \enum AAP_SessionConfig
 * \brief These are the different values to configure MD's behavior during projection. */
typedef enum
{
    /* This is to hide clock in the projection */
    AAP_UI_CONFIG_HIDE_CLOCK = 1,
    /* This is to hide phone signal in the projection */
    AAP_UI_CONFIG_HIDE_PHONE_SIGNAL = 2,
    /* This is to hide battery indicator in the projection */
    AAP_UI_CONFIG_HIDE_BATTERY_LEVEL = 4,
    /* This is to indicate that native media can be played during AAP VR session */
    AAP_NATIVE_MEDIA_PLAY_DURING_VR = 8
}AAP_SessionConfig;

/*! \enum AAP_MediaDataEvent
 * \brief Enumeration to specify different browsing event\n
  * This events will be asynchronous responses to the application's media browsing queries.*/
typedef enum
{
    /*! Invalid event type */
    AAP_MEDIA_DATA_INVALID_EVENT = 0x00,
    /*! Media browser event for source list query */
    AAP_MEDIA_BROWSER_SOURCE_LIST_EVENT = 0x300,
    /*! Media browser event for play-list query */
    AAP_MEDIA_BROWSER_MEDIA_LIST_EVENT,
    /*! Media browser event for track list */
    AAP_MEDIA_BROWSER_TRACK_LIST_EVENT,
    /*! Media browser event for track info query */
    AAP_MEDIA_BROWSER_SONG_INFO_EVENT
}AAP_MediaDataEvent;

/*! \struct AAP_MediaSource
 * \brief Contains information about a media source.*/
typedef struct
{
    /*! Path of the media source, NULL terminate string */
    AAP_BYTE aucPath[AAP_DEFAULT_STRING_LEN];
    /*! Name of the media source, NULL terminate string */
    AAP_BYTE aucName[AAP_DEFAULT_STRING_LEN];
    /*! Album art of this media source as PNG */
    AAP_CHAR acAlbumArt[AAP_MAX_ALBUM_ART_LEN];
    /*! Length of the image */
    AAP_UINT32 uiAlbumArtLen;
}AAP_MediaSource;

/*! \struct AAP_MediaRootList
 * \brief Contains information about the root media node.*/
typedef  struct
{
    /*! Path of the media source, NULL terminate string \n
     * It maps to the media query string (root path) */
    AAP_BYTE aucPath[AAP_DEFAULT_STRING_LEN];
    /*! Media source array */
    AAP_MediaSource asSourceList[AAP_MAX_NUM_MEDIA_SOURCES];
    /*! Number of sources in the list */
    AAP_UINT32 uiNumSource;
}AAP_MediaRootList;

/*! \struct AAP_MediaPlayList
 * \brief Contains information about a media source.*/
typedef struct
{
    /*! Path of the playlist, NULL terminate string */
    AAP_BYTE aucPath[AAP_DEFAULT_STRING_LEN];
    /*! Name of the playlist, NULL terminate string */
    AAP_BYTE aucName[AAP_DEFAULT_STRING_LEN];
    /*! Album art of this playlist as PNG */
    AAP_CHAR acAlbumArt[AAP_MAX_ALBUM_ART_LEN];
    /*! Length of the image */
    AAP_UINT32 uiAlbumArtLen;
    /*! Type of the playlist */
    AAP_UINT32 uiType;
}AAP_MediaPlayList;

/*! \struct AAP_SourceMediaList
 * \brief Structure to specify source list */
typedef  struct
{
    /*! Points to the selected media source\n
     *  Track list will be part of this source */
    AAP_MediaSource sSource;
    /*! Total number of lists in this source */
    AAP_UINT32 uiTotalNoList;
    /*! Starting position of returned lists */
    AAP_UINT32 uiStartPos;
    /*! Array of play lists */
    AAP_MediaPlayList asPlayList[AAP_MAX_NUM_PLAYLIST];
    /*! Number of play-lists in the list\n
     *  Size of the AAP_MediaPlayList array */
    AAP_UINT32 uiNumList;
}AAP_SourceMediaList;

/*! \struct AAP_MediaSong
 * \brief Structure to specify the information of song.\n*/
typedef struct
{
    /*! Path of a song, NULL terminate string */
    AAP_BYTE aucPath[AAP_DEFAULT_STRING_LEN];
    /*! Name of a song, NULL terminate string */
    AAP_BYTE aucName[AAP_DEFAULT_STRING_LEN];
    /*! Name of the Artist, NULL terminate string */
    AAP_BYTE aucArtistName[AAP_DEFAULT_STRING_LEN];
    /*!Name of the Album, NULL terminate string */
    AAP_BYTE aucAlbumName[AAP_DEFAULT_STRING_LEN];
}AAP_MediaSong;

/*! \struct AAP_MediaSongList
 *  \brief Structure to specify the song list
 */
typedef struct
{
    /*! Points to the selected media list */
    AAP_MediaPlayList sMediaList;
    /*!Total number of songs in this list */
    AAP_UINT32 uiTotal;
    /*! Starting position of the returned lists */
    AAP_UINT32 uiStart;
    /*! Array of song lists */
    AAP_MediaSong asSongList[AAP_MAX_NUM_SONG_LIST];
    /*! Number of songs in the list\n
     *  Size of the array AAP_MediaSong list */
    AAP_UINT32 uiNumSongs;
}AAP_MediaSongList;

/*! AAP_SongInfo
 * \brief Structure to specify the song information
 */
typedef  struct
{
    /*! Points to the selected song */
    AAP_MediaSong sSong;
    /*! Album art of this song as PNG */
    AAP_CHAR acAlbumArt[AAP_MAX_ALBUM_ART_LEN];
    /*! Length of the image */
    AAP_UINT32 uiAlbumArtLen;
    /*! Duration of this song */
    AAP_UINT32 uiDuration;
}AAP_SongInfo;

/*! \enum AAP_ProjectionEventType
 * \brief Enumeration to specify different projection states
 */
typedef enum
{
    /*! Invalid projection event */
    AAP_PROJECTION_NONE = 0x400,
    /*! Projection is ON. MD is rendering the video onto the HU display */
    AAP_PROJECTION_ON,
    /*! Projection is OFF. Native mode */
    AAP_PROJECTION_OFF,
    /*! This gets called when video setup is completed. This is to indicate that
     * now application can make request for sending video focus state. */
    AAP_PROJECTION_SETUP,
    /*! This gives the information about the video resolution selected by Mobile
     * device */
    AAP_PROJECTION_CONFIG
}AAP_ProjectionEventType;

/*! \enum AAP_VideoResType
 * \brief Enumeration to specify different video resolution types
 */
typedef enum
{
    /*! Video resolution 480p */
    AAP_VIDEO_RESOLUTION_800x480 = 0x1,
    /*! Video resolution 720p */
    AAP_VIDEO_RESOLUTION_1280x720,
    /*! Video resolution 1080p */
    AAP_VIDEO_RESOLUTION_1920x1080
}AAP_VideoResType;

/*! \struct AAP_ProjConfigData
 * This contains data video configuration data which is selected by mobile device
 * during video setup.
 */
typedef struct
{
    /*! This will contain selected resolution type by MD. */
    AAP_VideoResType eVideoResType;
}AAP_ProjConfigData;

/*! \union AAP_ProjectionData
 * \brief This contains relevant data corresponding to #AAP_ProjectionEventType.
 * One of the structure will be accessed based on the #AAP_ProjectionEventType
 */
typedef union
{
    /*! This should be accessed only when #AAP_ProjectionEventType is #AAP_PROJECTION_CONFIG
     * */
    AAP_ProjConfigData sProjConfigData;
}AAP_ProjectionData;

/*! \enum AAP_MediaPlaybackState
 * \brief Enumeration to specify media's playback status.
 *
 * This can be used to display the playback status of a media in native screen.
 */
typedef enum
{
    /*! Playback is stopped */
    AAP_MEDIA_PLAYBACK_STOPPED = 1,
    /*! Media is playing */
    AAP_MEDIA_PLAYBACK_PLAYING,
    /*! Media is paused */
    AAP_MEDIA_PLAYBACK_PAUSED
}AAP_MediaPlaybackState;

/*! \struct AAP_MediaPlaybackInfo
 * \brief Defines the playback status structure.
 *
 * When a song is playing, MD keeps on sending this info to the Application.
 * This info can be used to display on the native screen or cluster display.
 *
 * Application has to subscribe to this activity through config XML file and
 * must register #AAP_MediaPlaybackStatusCb callback */
typedef struct
{
    /*! State of playback */
    AAP_MediaPlaybackState eState;
    /*! Source of current media. NULL terminated string */
    AAP_BYTE aucMediaSource[AAP_DEFAULT_STRING_LEN];
    /*! Current playback of song in seconds. */
    AAP_UINT32 uiPlaybackSeconds;
    /*! Is shuffle enabled */
    AAP_BOOL bShuffle;
    /*! Is repeat enabled */
    AAP_BOOL bRepeat;
    /*! Is repeat one enabled */
    AAP_BOOL bRepeatOne;
}AAP_MediaPlaybackInfo;

/*! \struct AAP_MediaPlaybackMetadata
 *  \brief Defines the meta data associated with now playing media.
 *
 *  When the song starts or when the track changes, this meta data of the song
 *  is received. This info can be used to display on the native screen or
 *  cluster display.
 *
 * Application has to subscribe to this activity through config XML file and
 * must register #AAP_MediaPlaybackStatusCb callback */
typedef struct
{
    /*! Song name length */
    AAP_UINT32 uiSongLength;
    /*! Song name. NULL terminated string.
     * \note NULL if #uiSongLength is zero. */
    AAP_CHAR *pcSong;
    /*! Album name length */
    AAP_UINT32 uiAlbumLength;
    /*! Album name. NULL terminated string.
     * \note NULL if #uiAlbumLength is zero. */
    AAP_CHAR *pcAlbum;
    /*! Artist name length */
    AAP_UINT32 uiArtistLength;
    /*! Artist name. NULL terminated string.
     * \note NULL if #uiArtistLength is zero. */
    AAP_CHAR *pcArtist;
    /*! Album art length */
    AAP_UINT32 uiAlbumArtLength;
    /*! Album art
     * \note NULL if #uiAlbumArtLength is zero. */
    AAP_CHAR *pcAlbumArt;
    /*! Playlist length */
    AAP_UINT32 uiPlaylistLength;
    /*! Play list name. NULL terminated string.
     * \note NULL if #uiPlaylistLength is zero. */
    AAP_CHAR *pcPlaylist;
    /*! Total duration in seconds */
    AAP_UINT32 uiDuration;
    /*! Rating on a scale of 0 to 5 */
    AAP_UINT32  uiRating;
}AAP_MediaPlaybackMetadata;

/*! \struct AAP_MediaPlayBackStatus
 * \brief Structure to provide playback status
 */
typedef struct
{
    /*! If it is TRUE then meta data fields are available otherwise playback
     * status fields will be available */
    AAP_BOOL bIsMetaData;
    /*! Media info container */
    union
    {
        /*! For play back status. (When song is playing) */
        AAP_MediaPlaybackInfo sPlayBack;
        /*! For meta data of play back. (When the song starts or the track
         * changes) */
        AAP_MediaPlaybackMetadata sMetaData;
    };
}AAP_MediaPlayBackStatus;

/*! \struct AAP_MediaData
 * \brief Structure to get information about media browsing. */
typedef struct
{
    /*! Media data type*/
    AAP_MediaDataEvent eEvent;
    union
    {
        /*! Information about media sources \n
          * Available if the eEvent is #AAP_MEDIA_BROWSER_SOURCE_LIST_EVENT */
        AAP_MediaRootList sMediaRootList;
        /*! Information about media lists \n
         *  Available if the eEvent is #AAP_MEDIA_BROWSER_MEDIA_LIST_EVENT */
        AAP_SourceMediaList sSourceMediaList;
        /*! Information about list of songs \n
         *  Available if the eEvent is #AAP_MEDIA_BROWSER_TRACK_LIST_EVENT */
        AAP_MediaSongList sMediaSongList;
        /*! Information about a song \n
         *  Available if the eEvent is #AAP_MEDIA_BROWSER_SONG_INFO_EVENT */
        AAP_SongInfo sSongInfo;
    };
}AAP_MediaData;

/*! \enum AAP_CallState
 * \brief Enumeration to specify the different call state
 */
typedef enum
{
    /*! Currently in a call. */
    AAP_PHONE_STATUS_IN_CALL = 1,
    /*! Call is on hold. */
    AAP_PHONE_STATUS_ON_HOLD,
    /*! No on going calls. */
    AAP_PHONE_STATUS_INACTIVE,
    /*! Call is incoming. */
    AAP_PHONE_STATUS_INCOMING,
    /*! Call is conferenced */
    AAP_PHONE_STATUS_CONFERENCED,
    /*! Call is muted. */
    AAP_PHONE_STATUS_MUTED
}AAP_CallState;

/*! \struct AAP_CallInfo
 * \brief Structure to specify phone call Information */
typedef struct
{
    /*! State of phone call. */
    AAP_CallState eCallState;
    /*! Length of the caller's phone number. */
    AAP_UINT32 uiCallerNumberLength;
    /*! The phone number of the caller. NULL terminated string.
     * \note NULL if #uiCallerNumberLength is zero. */
    AAP_CHAR *pcCallerNumber;
    /*! Length of caller Id. */
    AAP_UINT32 uiCallerIdLength;
    /*! Caller Id. NULL terminated string.
     * \note NULL if #uiCallerIdLength is zero. */
    AAP_CHAR *pcCallerId;
    /*! Length of caller Number type. */
    AAP_UINT32 uiCallerNoTypeLength;
    /*! Number type ex.Home, Mobile, Work etc. NULL terminated string.
     * \note NULL if #uiCallerNoTypeLength is zero. */
    AAP_CHAR *pcCallerNumberType;
    /*! Length of thumbnail buffer. */
    AAP_UINT32 uiThumbnailLen;
    /*! A PNG thumbnail of the caller. NULL terminated string.
     * \note NULL if #uiThumbnailLen is zero. */
    AAP_CHAR *pcThumbnail;
    /*! Current duration of the call in seconds. */
    AAP_UINT32 uiCallDuration;
}AAP_CallInfo;

/*! \struct AAP_PhoneStatus
 * \brief Structure to specify status of phone activity.*/
typedef struct
{
    /*! Array of all current calls. */
    AAP_CallInfo asCallInfo[AAP_MAX_NUM_CALL_ALLOWED];
    /*! Number of calls in the array */
    AAP_UINT32 uiNumCalls;
    /*! Relative signal strength from 0-100. */
    AAP_UINT32 uiSignStrength;
}AAP_PhoneStatus;

/*! \enum AAP_NavMessageType
 * \brief Enumeration to specify the different navigation messages from MD */
typedef enum
{
    /*! When navigation status message comes through */
    AAP_NAV_MSG_TYPE_STATUS= 0x500,
    /*! When next turn message comes through */
    AAP_NAV_MSG_TYPE_NEXT_TURN_INFO,
    /*! When a next turn distance message comes through */
    AAP_NAV_MSG_TYPE_NEXT_TURN_DIST_INFO
}AAP_NavMessageType;

/*! \enum AAP_NavStatusEvent
 *  \brief Enumeration to specify the different navigation status event */
typedef enum
{
    /*! When navigation status is unavailable */
    AAP_NAV_STATUS_UNAVAILABLE = 0x0,
    /*! When navigation status is active */
    AAP_NAV_STATUS_ACTIVE,
    /*! When navigation status is inactive */
    AAP_NAV_STATUS_INACTIVE
}AAP_NavStatusEvent;

/*! \enum AAP_NavTurnSide
 *  \brief Enumeration to specify the different turn side */
typedef enum
{
    /*! When navigation turn side left */
    AAP_NAV_TURNSIDE_LEFT = 0x01,
    /*! When navigation turn side right */
    AAP_NAV_TURNSIDE_RIGHT,
    /*! When navigation turn side unspecified (straight ahead, road name change,
     * unknown, etc) */
    AAP_NAV_TURNSIDE_UNSPECIFIED
}AAP_NavTurnSide;

/*! \enum AAP_NavNextTurnEnum
 *  \brief Enumeration to specify the different next turn type */
typedef enum
{
    /*! Unknown */
    AAP_NAV_NEXT_TURN_ENUM_UNKNOWN = 0x0,
    /*! Depart from starting point. */
    AAP_NAV_NEXT_TURN_ENUM_DEPART,
    /*! Street name change without turn. */
    AAP_NAV_NEXT_TURN_ENUM_NAME_CHANGE,
    /*! Slight turn. */
    AAP_NAV_NEXT_TURN_ENUM_SLIGHT_TURN,
    /*! Turn. */
    AAP_NAV_NEXT_TURN_ENUM_TURN,
    /*! Sharp turn. */
    AAP_NAV_NEXT_TURN_ENUM_SHARP_TURN,
    /*! U-turn. */
    AAP_NAV_NEXT_TURN_ENUM_U_TURN,
    /*! On ramp. */
    AAP_NAV_NEXT_TURN_ENUM_ON_RAMP,
    /*! Off ramp.*/
    AAP_NAV_NEXT_TURN_ENUM_OFF_RAMP,
    /*! Forks in the ramp. */
    AAP_NAV_NEXT_TURN_ENUM_FORK,
    /*! Road merges. */
    AAP_NAV_NEXT_TURN_ENUM_MERGE,
    /*! Roundabout entrance on which the route ends.
     * Instruction says "Enter roundabout".  */
    AAP_NAV_NEXT_TURN_ENUM_ROUNDABOUT_ENTER,
    /*! Roundabout exit. */
    AAP_NAV_NEXT_TURN_ENUM_ROUNDABOUT_EXIT,
    /*! Roundabout entrance and exit. E.g. "At the roundabout, take Nth exit." */
    AAP_NAV_NEXT_TURN_ENUM_ROUNDABOUT_ENTER_AND_EXIT,
    /*! Potentially confusing intersection where the user should steer straight. */
    AAP_NAV_NEXT_TURN_ENUM_STRAIGHT,
    /*! Boat ferries. */
    AAP_NAV_NEXT_TURN_ENUM_FERRY_BOAT,
    /*! Train ferries for vehicles. */
    AAP_NAV_NEXT_TURN_ENUM_FERRY_TRAIN,
    /*! Destination. */
    AAP_NAV_NEXT_TURN_ENUM_DESTINATION
}AAP_NavNextTurnEnum;

/*! \enum AAP_NavNextTurnDistanceUnits
 *  \brief Enumeration to specify the distance in different units */
typedef enum
{
    /*! Unknown */
    AAP_NAV_NEXT_TURN_DIST_UNIT_UNKNOWN = 0x0,
    /*! Distance in METERS */
    AAP_NAV_NEXT_TURN_DIST_UNIT_METERS,
    /*! Distance in KILOMETERS */
    AAP_NAV_NEXT_TURN_DIST_UNIT_KILOMETERS,
    /*! Distance in KILOMETERS_P1 */
    AAP_NAV_NEXT_TURN_DIST_UNIT_KILOMETERS_P1,
    /*! Distance in MILES */
    AAP_NAV_NEXT_TURN_DIST_UNIT_MILES,
    /*! Distance in MILES_P1 */
    AAP_NAV_NEXT_TURN_DIST_UNIT_MILES_P1,
    /*! Distance in FEET */
    AAP_NAV_NEXT_TURN_DIST_UNIT_FEET,
    /*! Distance in YARDS */
    AAP_NAV_NEXT_TURN_DIST_UNIT_YARDS
}AAP_NavNextTurnDistanceUnits;

/*! \struct AAP_NextTurnDistance
 * \brief Structure to specify the next turn distance message */
typedef struct
{
    /*! Distance to next turn event. */
    AAP_INT32 iDistance;
    /*! Time to next turn event, in seconds. */
    AAP_INT32 iTime;
    /*! Distance to next turn event, in E3. */
    AAP_INT32  iDistanceE3;
    /*! Enum Distance to next turn */
    AAP_NavNextTurnDistanceUnits eDistanceUnit;
}AAP_NextTurnDistance;

/*! \struct AAP_NextTurnInfo
 * \brief Structure to specify the next turn message.
 *
 * For an example of a roundabout: if a roundabout has 4 exits, spaced evenly,
 * then the first exit will have iTurnNum=1, iTurnAngle=90;
 * the second will have iTurnNum=2, iTurnAngle=180;
 * the third will have iTurnNum=3, iTurnAngle=270.
 * iTurnNum and iTurnAngle are counted in the direction of travel around the
 * roundabout (clockwise for roads where the car drives on the left-hand side
 * of the road, such as India; anti-clockwise for roads where the car drives
 * on the right, such as the USA). */
typedef struct
{
    /*! Road name. This is a NULL terminated string.
     * \note NULL if #uiRoadLength is zero. */
    AAP_BYTE *pcRoadName;
    /*! Length of road name */
    AAP_UINT32 uiRoadLength;
    /*! Turn side */
    AAP_NavTurnSide eTurnSide;
    /*! Next Turn enum type */
    AAP_NavNextTurnEnum eNextTurnEnum;
    /*! Turn image in PNG format. This is a NULL terminated string.
     * \note NULL if #uiImageLength is zero. */
    AAP_BYTE *pcImage;
    /*! Image length. If the length is 0, then use enum instead of image */
    AAP_UINT32 uiImageLength;
    /*! Turn angle in degrees between the roundabout entry and exit (0..359).
     * Only used for event type #AAP_NAV_NEXT_TURN_ENUM_ROUNDABOUT_ENTER_AND_EXIT.
     * -1 if unused. */
    AAP_INT32 iTurnAngle;
    /*! Turn number, counting around from the roundabout entry to the exit.
     * Only used for event type #AAP_NAV_NEXT_TURN_ENUM_ROUNDABOUT_ENTER_AND_EXIT.
     * -1 if unused. */
    AAP_INT32 iTurnNum;
}AAP_NextTurnInfo;

/*! \struct AAP_NavigationStatus
 * \brief Structure to specify the status of navigation activity.*/
typedef struct
{
    /*! Navigation messages type*/
    AAP_NavMessageType eMesgTye;
    union
    {
        /*! Navigation status\n
         *  Available if the eMesgTye is #AAP_NAV_MSG_TYPE_STATUS */
        AAP_NavStatusEvent eStatus;
        /*! Next Turn info \n
          * Available if the eMesgTye is #AAP_NAV_MSG_TYPE_NEXT_TURN_INFO */
        AAP_NextTurnInfo sNextTurnInfo;
        /*! Next Turn distance info\n
         *  Available if the eMesgTye is #AAP_NAV_MSG_TYPE_NEXT_TURN_DIST_INFO */
        AAP_NextTurnDistance sNextTurnDistance;
    };
}AAP_NavigationStatus;

/*! \struct AAP_BatteryStatus
 * \brief Structure to specify the status of the MD battery. */
typedef struct
{
    /*! Current battery percentage of the mobile device */
    AAP_INT32 iBatteryLevel;
    /*! An estimate of how long the battery will last, in seconds */
    AAP_INT32 iTimeRemainingS;
    /*! It will be set to AAP_TRUE if the battery level is critical else AAP_FALSE.
     * If bIsBatteryCritical is set to AAP_TRUE and video focus is #AAP_PROJECTION_OFF, then
     * application must display a native message to instruct the user to connect
     * the MD to a power source. The message should also include battery level
     * i.e. #iBatteryLevel and time remaining i.e. #iTimeRemainingS information.
     * If bIsBatteryCritical is set to AAP_TRUE and video focus is AAP_PROJECTION_ON, then
     * application must not show any message as Android Auto UI will display a
     * message. */
    AAP_BOOL bIsBatteryCritical;
}AAP_BatteryStatus;

/*! struct AAP_BugReportReq */
typedef struct
{
    /*! Timestamp */
    AAP_INT64 liTimestamp;
}AAP_BugReportReq;

/*! \enum AAP_NativeAppType
 * \brief Enumeration to specify different native applications\n
 *  These are applications which can be controlled through AAP.
 */
typedef enum
{
    /*! Native radio activity */
    AAP_NATIVE_APP_RADIO = 0x600,
    /*! Native HVAC app (not supported now) */
    AAP_NATIVE_APP_HVAC
}AAP_NativeAppType;

/*! \enum AAP_NativeAppAction
  * \brief Enumeration to specify different action supported by native application.\n
  * See #AAP_NativeAppType
  */
typedef enum
{
    /*! Native radio activity */
    AAP_NATIVE_APP_RADIO_TUNE = 0x700
}AAP_NativeAppAction;

/*! \typedef AAP_SIZE_T AAP_HANDLE
 *  \brief AAP session handle */
typedef AAP_SIZE_T AAP_HANDLE;

/*! \enum AAP_DrivingStatusType
 *  \brief Enumeration to specify different driving status.
 *  (use to avoid driver distraction). Defined as a bitmask
 */
typedef enum
{
    /*! Parking mode. No restrictions. */
    AAP_DRIVE_STATUS_UNRESTRICTED = 0x0,
    /*! No video playback allowed. Video playback is media such as movies,
     * YouTube, games, etc. (not UI)*/
    AAP_DRIVE_STATUS_NO_VIDEO = 0x1,
    /*! No keyboard or rotary controller input allowed.
     * Also limits map scroll and pan.*/
    AAP_DRIVE_STATUS_NO_KEYBOARD_INPUT = 0x2,
    /*! No voice input allowed.*/
    AAP_DRIVE_STATUS_NO_VOICE_INPUT = 0x4,
    /*! No setup/configuration allowed. */
    AAP_DRIVE_STATUS_NO_CONFIG = 0x8,
    /*! Limit displayed message length. */
    AAP_DRIVE_STATUS_LIMIT_MESSAGE_LEN = 0x10
}AAP_DrivingStatusType;

/*! \enum AAP_StreamRequest
 * Enumeration to specify the type of stream requests made by MD to HU.
 *
 * e.g. MD sends an audio focus request to the HU when the MD wants to gain focus to play audio.
 * HU has to respond to this with proper focus state notification define in #AAP_StreamState
 * using #aap_send_stream_focus_state
 *
 * \note
 * Requests are defined with respect to the calling module where as the states are defined with respect to MD.
 */
typedef enum
{
    /*! Invalid focus request */
    AAP_STREAM_FOCUS_REQ_NONE = 0x00,
    /*! Request to gain audio focus for an unknown duration. All other audio
     *  sources (i.e. vehicle audio sources) lose focus and stop playing audio.
     *  The mobile device (MD) OR the vehicle can have full (GAIN) audio focus.
     */
    AAP_AUDIO_STREAM_FOCUS_REQ_GAIN = 0x800,
    /*!Request to gain audio focus for a short duration. The audio source with
     * focus temporarily loses focus (and stops playing content) and then
     * regains focus when the mobile device sends the RELEASE message.
     * The mobile device sends this request only when it does not already
     * have full (GAIN) focus.
     */
    AAP_AUDIO_STREAM_FOCUS_REQ_GAIN_TRANSIENT,
    /*! Request to gain audio focus for a short duration and that it is
    * acceptable for other audio sources to keep playing after having lowered
    * their output level (referred to as "ducking"). The mobile device sends
    * this request only when it does not already have full (GAIN) focus OR
    * GAIN_TRANSIENT focus.
    */
    AAP_AUDIO_STREAM_FOCUS_REQ_GAIN_TRANSIENT_MAY_DUCK,
    /*! Request to release audio focus.*/
    AAP_AUDIO_STREAM_FOCUS_REQ_LOSS,
    /*! Request to gain video / projection focus */
    AAP_VIDEO_STREAM_FOCUS_REQ_GAIN,
    /*! Request to release video / projection focus */
    AAP_VIDEO_STREAM_FOCUS_REQ_LOSS,
    /*! Request for transient release video / projection focus. This is to
     * indicate the video loss is for short period of time. */
    AAP_VIDEO_STREAM_FOCUS_REQ_LOSS_TRANSIENT,
    /*! Request to gain navigation focus by MD */
    AAP_NAVIGATION_STREAM_FOCUS_REQ_GAIN,
    /*! Request to release navigation focus
     * HU can turn on its navigation */
    AAP_NAVIGATION_STREAM_FOCUS_REQ_LOSS
}AAP_StreamRequest;

/*! \enum AAP_StreamState
 * \brief Enumeration to specify the stream focus notifications sent by the HU
 * to the MD to inform its focus state.
 *
 * \note
 * Application can send stream state as a response to stream focus requests from
 * MD or as unsolicited messages prompted by external events.
 * Refer #aap_send_stream_focus_state.
 *
 * \note
 * This states are define with respect to the Mobile Device.
 */
typedef enum
{
    /*! Invalid stream state */
    AAP_STREAM_STATE_NONE = 0x00,
    /*! MD has gained stream focus (when in response to an
     *  audio focus request) or re-gained audio focus (when it
     *  was temporarily lost).*/
    AAP_AUDIO_STATE_GAIN = 0x900,
    /*! MD has gained audio focus for a short duration.*/
    AAP_AUDIO_STATE_GAIN_TRANSIENT,
    /*! MD has gained audio focus for a short duration but is
     *  only allowed to play on the GUIDANCE channel.*/
    AAP_AUDIO_STATE_GAIN_TRANSIENT_GUIDANCE_ONLY,
    /*! DEPRECATED(Will be removed in near future):
     *  MD has gained audio focus but is only allowed to play
     *  on the MEDIA channel.*/
    AAP_AUDIO_STATE_GAIN_MEDIA_ONLY,
    /*! MD can continue playing through MEDIA channel if
     *  volume is lowered */
    AAP_AUDIO_STATE_LOSS_TRANSIENT_CAN_DUCK,
    /*! MD has lost audio focus or failed to gain audio focus */
    AAP_AUDIO_STATE_LOSS,
    /*! MD has temporarily lost audio focus or has failed to
     *  gain audio focus. */
    AAP_AUDIO_STATE_LOSS_TRANSIENT,
    /*! In this projection state, the HU renders a full-screen video stream from the MD
     *  and forwards all touch/controller events to the MD. This is the
     *  preferred mode for active AAP connections. */
    AAP_VIDEO_STATE_PROJECTION,
    /*! In this state HU renders the full-screen native UI (such as for a backup camera)
     * and the MD does not stream video to the HU.*/
    AAP_VIDEO_STATE_NATIVE,
    /*! This is same as #AAP_VIDEO_STATE_NATIVE. But the purpose is to provide behavioral
     * hints to the MD. This is to indicate transient native screens expected to show for
     * a short period of time. In addition its content may overlay the projected video */
    AAP_VIDEO_STATE_NATIVE_TRANSIENT,
    /*! In this state, the HU allows MD to run turn by turn navigation.*/
    AAP_NAVIGATION_STATE_PROJECTION,
    /*! In this state, the HU starts its own turn by turn navigation */
    AAP_NAVIGATION_STATE_NATIVE
}AAP_StreamState;

/*! \enum AAP_StreamType
 * \brief Enumeration to specify the various stream source(or resource) from MD.
 *
 */
typedef enum
{
    /*! Invalid stream type */
    AAP_STREAM_NONE = 0x00,
    /*! Projection video stream */
    AAP_STREAM_VIDEO =  0xA00,
    /*! Generic audio stream. This stream type is used when the MD wants
     * to get audio focus. As of now application receives any audio focus request
     * through this stream only. */
    AAP_AUDIO_STREAM,
    /*! Driver guidance voice: High priority stream. This stream is used to indicate
     * guidance channel is about to receive audio data stream or the stream has stopped. */
    AAP_AUDIO_STREAM_GUIDANCE,
    /*! Cabin media stream. This stream is used to indicate media channel is about
     * to receive audio data stream or the stream has stopped. */
    AAP_AUDIO_STREAM_MEDIA,
    /*! User interface feedback stream (Reserved for future)*/
    AAP_AUDIO_STREAM_SYSTEM,
    /*! Conversational voice, e.g. Phone call (Reserved for future)*/
    AAP_AUDIO_STREAM_VOICE,
    /*! Captures microphone audio using the built-in vehicle microphones and
     * transmits that audio to the MD\n */
    AAP_AUDIO_STREAM_MICROPHONE,
    /*! Bi directional legacy call stream type over BT SCO (Reserved for future) */
    AAP_AUDIO_STREAM_LEGACY_IN_CALL,
    /*! Navigation channel. The stream in which navigation data i.e next turn data
     * is received by the application. This data can be used by the application
     * to display on the native screen or on the secondary/cluster display. */
    AAP_STREAM_NAVIGATION
}AAP_StreamType;

/*! \enum AAP_AudioState
 * \brief Enumeration to specify the state of the audio playback. This can be for
 * media, guidance, system or microphone stream.
 */
typedef enum
{
    /*! When audio is about to start.
     * \note
     * When this event comes for #AAP_AUDIO_STREAM_MICROPHONE
     * stream type, HU should stop all sounds regardless of audio focus state
     */
    AAP_AUDIO_STATE_START = 0x1,
    /*! When audio is stopped */
    AAP_AUDIO_STATE_STOP
}AAP_AudioState;

/*! \enum AAP_ByeByeReason */
typedef enum
{
    /*! User initiated AAP exit. In this case MD supports AAP but doesn't want to
     * continue any more. For eg. After establishing AAP connection, from MD side
     * clicking on "Touch to exit car mode" to exit AAP or in First Run
     * Experience(FRX) intentionally exiting without completing FRX on MD side. */
    AAP_BYEBYE_REASON_USER_INITIATED_EXIT = 1,
    /*! Device switch */
    AAP_BYEBYE_REASON_AAP_DEVICE_SWITCH,
    /*! Unsupported AAP device */
    AAP_BYEBYE_REASON_AAP_UNSUPPORTED_DEV,
    /*! Currently AAP is not supported */
    AAP_BYEBYE_REASON_NOT_CURRENTLY_SUPPORTED,
    /*! AAP supported device */
    AAP_BYEBYE_REASON_AAP_SUPPORTED_DEV
}AAP_ByeByeReason;

/*! \enum AAP_DevSwitchStatus */
typedef enum
{
    /*! Status success when device is prepared successfully. */
    AAP_DSS_SUCCESS = 0x1,
    /*! If the device can not be prepared since RFCOMM connection is lost. */
    AAP_DSS_NO_RFCOMM_CONNECTION,
    /*! If the device can not be prepared since BT is turned off before start
     * request. */
    AAP_DSS_BT_CLOSED_BEFORE_START,
    /*! If the device can not be prepared since BT is turned off after start
     * request. */
    AAP_DSS_BT_CLOSED_AFTER_START,
    /*! If the device can not be prepared since RFCOMM protocol version is
     * wrong. */
    AAP_DSS_INCOMPATIBLE_PHONE_PROTOCOL_VERSION,
    /*! If the device can not be prepared since unable to connect WIFI. */
    AAP_DSS_PHONE_UNABLE_TO_CONNECT_WIFI,
    /*! If the device can not be prepared since multiple user switch request. */
    AAP_DSS_MULTIPLE_USER_SWITCH_REQUEST,
    /*! If the device can not be prepared since other errors encountered by HU
     * which is not mentioned here. */
    AAP_DSS_HU_INTERNAL,
    /*! If the device can not be prepared since invalid switch request. */
    AAP_DSS_INVALID_REQUEST,
    /*! If the device can not be prepared since timeout. */
    AAP_DSS_REQUEST_TIMEOUT
}AAP_DevSwitchStatus;

/*! \enum AAP_AppCategory
 * \brief Enumeration to specify the available applications on MD which accepts
 * an action i.e #AAP_ActionType.
 * \note
 * Head Unit Application can send specific data and action for these MD Applications
 * through #aap_send_action( ) API.
 */
typedef enum
{
    /*! Music / Media application in MD */
    AAP_CATEGORY_MEDIA = 0xB00,
    /*! Phone Call application of MD */
    AAP_CATEGORY_PHONE
}AAP_AppCategory;

/*! \enum AAP_ActionType
 * \brief Enumeration to specify the available actions to perform on a MD
 * application. Indicates the button pressed in the instruction cluster.
 *
 * \note
 * Head Unit Application can send these actions for the MD applications such as
 * phone and media. Refer #aap_send_action( ) API.
 */
typedef enum
{
    /*! Up was pressed. */
    AAP_ACTION_UP = 0xD00,
    /*! Down was pressed. */
    AAP_ACTION_DOWN,
    /*! Left was pressed. */
    AAP_ACTION_LEFT,
    /*! Right was pressed. */
    AAP_ACTION_RIGHT,
    /*! Enter was pressed. */
    AAP_ACTION_ENTER,
    /*! Back was pressed. */
    AAP_ACTION_BACK,
    /*! Call was pressed. */
    AAP_ACTION_CALL
}AAP_ActionType;

/*! \struct AAP_PhoneData
 * \brief This structure contains data to report an action for phone status.
 */
typedef struct
{
    /*! Caller number */
    AAP_CHAR acCallerNumber[AAP_MAX_DIGIT_IN_PHONE_NUMBER];
    /*! Caller id */
    AAP_CHAR acCallerId[AAP_MAX_CALLER_ID_LEN];
}AAP_PhoneData;

/*! \struct AAP_ActionData
 * \brief This structure contains application category, corresponding structure, and
 * action type. For each app category user needs to fill corresponding
 * structure.
 */
typedef struct
{
    /*! Application category type */
    AAP_AppCategory eAppCategory;
    /*! Action type */
    AAP_ActionType eActionType;
    /*! Union to fill based on eAppCategory */
    union
    {
        /*! Fill this if application is AAP_CATEGORY_MEDIA */
        AAP_CHAR acMediaPath[AAP_DEFAULT_STRING_LEN];
        /*! Fill this if application is AAP_CATEGORY_PHONE */
        AAP_PhoneData sPhoneData;
    };
}AAP_ActionData;

/*!\enum AAP_TouchDevType
  \brief Enumeration to specify the available touch input devices type */
typedef enum
{
    /*! Invalid device */
    AAP_INPUT_DEVICE_INVALID = 0x00,
    /*! Touch screen */
    AAP_INPUT_DEVICE_TOUCH_SCREEN,
    /*! Touch pad */
    AAP_INPUT_DEVICE_TOUCH_PAD
}AAP_TouchDevType;

/*!  \enum AAP_TouchAction
 *   \brief Enumeration to specify touch action
 */
typedef enum
{
    /*! Invalid touch action*/
    AAP_TOUCH_ACTION_INVALID = 0x0,
    /*! First finger went down. */
    AAP_TOUCH_ACTION_DOWN,
    /*! Last finger went up. */
    AAP_TOUCH_ACTION_UP,
    /*! Finger(s) were moved. */
    AAP_TOUCH_ACTION_MOVED,
    /*! 2nd to nth finger went down. */
    AAP_TOUCH_POINTER_DOWN,
    /*! nth to 2nd last finger went up. */
    AAP_TOUCH_POINTER_UP
}AAP_TouchAction;

/*! \struct AAP_TouchEvent
 *  \brief Structure to specify the touch events */
typedef struct
{
    /*! Type of touch device, Should be AAP_INPUT_DEVICE_TOUCH_SCREEN or
     * AAP_INPUT_DEVICE_TOUCH_PAD*/
    AAP_TouchDevType eDevType;
    /*! Number of pointers */
    AAP_INT32 iNumPointers;
    /*! X co-ordinate values. These X,Y co-ordinate values are with respect to
     * display dimension, stack will do the scaling. */
    AAP_INT32 auiX[AAP_MAX_NUM_TOUCH_INPUT];
    /*! Y co-ordinate value */
    AAP_INT32 auiY[AAP_MAX_NUM_TOUCH_INPUT];
    /*! Id of this pointer */
    AAP_UINT32 auiPointerId[AAP_MAX_NUM_TOUCH_INPUT];
    /*! Touch action down or released or moved */
    AAP_TouchAction eAction;
    /*! This index corresponds to the pointer ID for which action is taken.
     * For an example: Lets say 2 simultaneous touch events.
     * iNumPointers = 2, auiX[0] = 580, auiY[0] = 100, auiPointerId[0] = 0
     * auiX[1] = 450, auiY[1] = 245, auiPointerId[1] = 1,
     * eAction = AAP_TOUCH_ACTION_MOVED,
     * iActionIndex = This represents the index in the auiPointerId array for which
     * action has been taken. This value will be greater than or equal to 0 and
     * lesser than iNumPointers.*/
    AAP_INT32 iActionIndex;
}AAP_TouchEvent;

/*! \enum AAP_KeyValType
 *  \brief Contains various key value type
 */
typedef enum
{
    /*! Normal key pressed or down state */
    AAP_KEY_VALUE_NORMAL = 0xE00,
    /*! Key long press */
    AAP_KEY_VALUE_LONG_PRESS,
    /*! Relative key value */
    AAP_KEY_VALUE_RELATIVE,
    /*! Absolute key value */
    AAP_KEY_VALUE_ABSOLUTE
}AAP_KeyValType;

/*! \enum AAP_KeyCodes
 *  \brief Enumeration to specify AAP key codes.
 *
 *  First register all the available key codes in the config XML.\n
 *  When the key is pressed, send the respective key code via #aap_send_key_input( )
 */
typedef enum
{
    AAP_KEYCODE_UNKNOWN = 0,
    AAP_KEYCODE_SOFT_LEFT = 1,
    AAP_KEYCODE_SOFT_RIGHT = 2,
    AAP_KEYCODE_HOME = 3,
    AAP_KEYCODE_BACK = 4,
    AAP_KEYCODE_CALL = 5,
    AAP_KEYCODE_ENDCALL = 6,
    AAP_KEYCODE_0 = 7,
    AAP_KEYCODE_1 = 8,
    AAP_KEYCODE_2 = 9,
    AAP_KEYCODE_3 = 10,
    AAP_KEYCODE_4 = 11,
    AAP_KEYCODE_5 = 12,
    AAP_KEYCODE_6 = 13,
    AAP_KEYCODE_7 = 14,
    AAP_KEYCODE_8 = 15,
    AAP_KEYCODE_9 = 16,
    AAP_KEYCODE_STAR = 17,
    AAP_KEYCODE_POUND = 18,
    AAP_KEYCODE_DPAD_UP = 19,
    AAP_KEYCODE_DPAD_DOWN = 20,
    AAP_KEYCODE_DPAD_LEFT = 21,
    AAP_KEYCODE_DPAD_RIGHT = 22,
    AAP_KEYCODE_DPAD_CENTER = 23,
    AAP_KEYCODE_VOLUME_UP = 24,
    AAP_KEYCODE_VOLUME_DOWN = 25,
    AAP_KEYCODE_POWER = 26,
    AAP_KEYCODE_CAMERA = 27,
    AAP_KEYCODE_CLEAR = 28,
    AAP_KEYCODE_A = 29,
    AAP_KEYCODE_B = 30,
    AAP_KEYCODE_C = 31,
    AAP_KEYCODE_D = 32,
    AAP_KEYCODE_E = 33,
    AAP_KEYCODE_F = 34,
    AAP_KEYCODE_G = 35,
    AAP_KEYCODE_H = 36,
    AAP_KEYCODE_I = 37,
    AAP_KEYCODE_J = 38,
    AAP_KEYCODE_K = 39,
    AAP_KEYCODE_L = 40,
    AAP_KEYCODE_M = 41,
    AAP_KEYCODE_N = 42,
    AAP_KEYCODE_O = 43,
    AAP_KEYCODE_P = 44,
    AAP_KEYCODE_Q = 45,
    AAP_KEYCODE_R = 46,
    AAP_KEYCODE_S = 47,
    AAP_KEYCODE_T = 48,
    AAP_KEYCODE_U = 49,
    AAP_KEYCODE_V = 50,
    AAP_KEYCODE_W = 51,
    AAP_KEYCODE_X = 52,
    AAP_KEYCODE_Y = 53,
    AAP_KEYCODE_Z = 54,
    AAP_KEYCODE_COMMA = 55,
    AAP_KEYCODE_PERIOD = 56,
    AAP_KEYCODE_ALT_LEFT = 57,
    AAP_KEYCODE_ALT_RIGHT = 58,
    AAP_KEYCODE_SHIFT_LEFT = 59,
    AAP_KEYCODE_SHIFT_RIGHT = 60,
    AAP_KEYCODE_TAB = 61,
    AAP_KEYCODE_SPACE = 62,
    AAP_KEYCODE_SYM = 63,
    AAP_KEYCODE_EXPLORER = 64,
    AAP_KEYCODE_ENVELOPE = 65,
    AAP_KEYCODE_ENTER = 66,
    AAP_KEYCODE_DEL = 67,
    AAP_KEYCODE_GRAVE = 68,
    AAP_KEYCODE_MINUS = 69,
    AAP_KEYCODE_EQUALS = 70,
    AAP_KEYCODE_LEFT_BRACKET = 71,
    AAP_KEYCODE_RIGHT_BRACKET = 72,
    AAP_KEYCODE_BACKSLASH = 73,
    AAP_KEYCODE_SEMICOLON = 74,
    AAP_KEYCODE_APOSTROPHE = 75,
    AAP_KEYCODE_SLASH = 76,
    AAP_KEYCODE_AT = 77,
    AAP_KEYCODE_NUM = 78,
    AAP_KEYCODE_HEADSETHOOK = 79,
    AAP_KEYCODE_FOCUS = 80,
    AAP_KEYCODE_PLUS = 81,
    AAP_KEYCODE_MENU = 82,
    AAP_KEYCODE_NOTIFICATION = 83,
    AAP_KEYCODE_SEARCH = 84,
    AAP_KEYCODE_MEDIA_PLAY_PAUSE = 85,
    AAP_KEYCODE_MEDIA_STOP = 86,
    AAP_KEYCODE_MEDIA_NEXT = 87,
    AAP_KEYCODE_MEDIA_PREVIOUS = 88,
    AAP_KEYCODE_MEDIA_REWIND = 89,
    AAP_KEYCODE_MEDIA_FAST_FORWARD = 90,
    AAP_KEYCODE_MUTE = 91,
    AAP_KEYCODE_PAGE_UP = 92,
    AAP_KEYCODE_PAGE_DOWN = 93,
    AAP_KEYCODE_PICTSYMBOLS = 94,
    AAP_KEYCODE_SWITCH_CHARSET = 95,
    AAP_KEYCODE_BUTTON_A = 96,
    AAP_KEYCODE_BUTTON_B = 97,
    AAP_KEYCODE_BUTTON_C = 98,
    AAP_KEYCODE_BUTTON_X = 99,
    AAP_KEYCODE_BUTTON_Y = 100,
    AAP_KEYCODE_BUTTON_Z = 101,
    AAP_KEYCODE_BUTTON_L1 = 102,
    AAP_KEYCODE_BUTTON_R1 = 103,
    AAP_KEYCODE_BUTTON_L2 = 104,
    AAP_KEYCODE_BUTTON_R2 = 105,
    AAP_KEYCODE_BUTTON_THUMBL = 106,
    AAP_KEYCODE_BUTTON_THUMBR = 107,
    AAP_KEYCODE_BUTTON_START = 108,
    AAP_KEYCODE_BUTTON_SELECT = 109,
    AAP_KEYCODE_BUTTON_MODE = 110,
    AAP_KEYCODE_ESCAPE = 111,
    AAP_KEYCODE_FORWARD_DEL = 112,
    AAP_KEYCODE_CTRL_LEFT = 113,
    AAP_KEYCODE_CTRL_RIGHT = 114,
    AAP_KEYCODE_CAPS_LOCK = 115,
    AAP_KEYCODE_SCROLL_LOCK = 116,
    AAP_KEYCODE_META_LEFT = 117,
    AAP_KEYCODE_META_RIGHT = 118,
    AAP_KEYCODE_FUNCTION = 119,
    AAP_KEYCODE_SYSRQ = 120,
    AAP_KEYCODE_BREAK = 121,
    AAP_KEYCODE_MOVE_HOME = 122,
    AAP_KEYCODE_MOVE_END = 123,
    AAP_KEYCODE_INSERT = 124,
    AAP_KEYCODE_FORWARD = 125,
    AAP_KEYCODE_MEDIA_PLAY = 126,
    AAP_KEYCODE_MEDIA_PAUSE = 127,
    AAP_KEYCODE_MEDIA_CLOSE = 128,
    AAP_KEYCODE_MEDIA_EJECT = 129,
    AAP_KEYCODE_MEDIA_RECORD = 130,
    AAP_KEYCODE_F1 = 131,
    AAP_KEYCODE_F2 = 132,
    AAP_KEYCODE_F3 = 133,
    AAP_KEYCODE_F4 = 134,
    AAP_KEYCODE_F5 = 135,
    AAP_KEYCODE_F6 = 136,
    AAP_KEYCODE_F7 = 137,
    AAP_KEYCODE_F8 = 138,
    AAP_KEYCODE_F9 = 139,
    AAP_KEYCODE_F10 = 140,
    AAP_KEYCODE_F11 = 141,
    AAP_KEYCODE_F12 = 142,
    AAP_KEYCODE_NUM_LOCK = 143,
    AAP_KEYCODE_NUMPAD_0 = 144,
    AAP_KEYCODE_NUMPAD_1 = 145,
    AAP_KEYCODE_NUMPAD_2 = 146,
    AAP_KEYCODE_NUMPAD_3 = 147,
    AAP_KEYCODE_NUMPAD_4 = 148,
    AAP_KEYCODE_NUMPAD_5 = 149,
    AAP_KEYCODE_NUMPAD_6 = 150,
    AAP_KEYCODE_NUMPAD_7 = 151,
    AAP_KEYCODE_NUMPAD_8 = 152,
    AAP_KEYCODE_NUMPAD_9 = 153,
    AAP_KEYCODE_NUMPAD_DIVIDE = 154,
    AAP_KEYCODE_NUMPAD_MULTIPLY = 155,
    AAP_KEYCODE_NUMPAD_SUBTRACT = 156,
    AAP_KEYCODE_NUMPAD_ADD = 157,
    AAP_KEYCODE_NUMPAD_DOT = 158,
    AAP_KEYCODE_NUMPAD_COMMA = 159,
    AAP_KEYCODE_NUMPAD_ENTER = 160,
    AAP_KEYCODE_NUMPAD_EQUALS = 161,
    AAP_KEYCODE_NUMPAD_LEFT_PAREN = 162,
    AAP_KEYCODE_NUMPAD_RIGHT_PAREN = 163,
    AAP_KEYCODE_VOLUME_MUTE = 164,
    AAP_KEYCODE_INFO = 165,
    AAP_KEYCODE_CHANNEL_UP = 166,
    AAP_KEYCODE_CHANNEL_DOWN = 167,
    AAP_KEYCODE_ZOOM_IN = 168,
    AAP_KEYCODE_ZOOM_OUT = 169,
    AAP_KEYCODE_TV = 170,
    AAP_KEYCODE_WINDOW = 171,
    AAP_KEYCODE_GUIDE = 172,
    AAP_KEYCODE_DVR = 173,
    AAP_KEYCODE_BOOKMARK = 174,
    AAP_KEYCODE_CAPTIONS = 175,
    AAP_KEYCODE_SETTINGS = 176,
    AAP_KEYCODE_TV_POWER = 177,
    AAP_KEYCODE_TV_INPUT = 178,
    AAP_KEYCODE_STB_POWER = 179,
    AAP_KEYCODE_STB_INPUT = 180,
    AAP_KEYCODE_AVR_POWER = 181,
    AAP_KEYCODE_AVR_INPUT = 182,
    AAP_KEYCODE_PROG_RED = 183,
    AAP_KEYCODE_PROG_GREEN = 184,
    AAP_KEYCODE_PROG_YELLOW = 185,
    AAP_KEYCODE_PROG_BLUE = 186,
    AAP_KEYCODE_APP_SWITCH = 187,
    AAP_KEYCODE_BUTTON_1 = 188,
    AAP_KEYCODE_BUTTON_2 = 189,
    AAP_KEYCODE_BUTTON_3 = 190,
    AAP_KEYCODE_BUTTON_4 = 191,
    AAP_KEYCODE_BUTTON_5 = 192,
    AAP_KEYCODE_BUTTON_6 = 193,
    AAP_KEYCODE_BUTTON_7 = 194,
    AAP_KEYCODE_BUTTON_8 = 195,
    AAP_KEYCODE_BUTTON_9 = 196,
    AAP_KEYCODE_BUTTON_10 = 197,
    AAP_KEYCODE_BUTTON_11 = 198,
    AAP_KEYCODE_BUTTON_12 = 199,
    AAP_KEYCODE_BUTTON_13 = 200,
    AAP_KEYCODE_BUTTON_14 = 201,
    AAP_KEYCODE_BUTTON_15 = 202,
    AAP_KEYCODE_BUTTON_16 = 203,
    AAP_KEYCODE_LANGUAGE_SWITCH = 204,
    AAP_KEYCODE_MANNER_MODE = 205,
    AAP_KEYCODE_3D_MODE = 206,
    AAP_KEYCODE_CONTACTS = 207,
    AAP_KEYCODE_CALENDAR = 208,
    AAP_KEYCODE_MUSIC = 209,
    AAP_KEYCODE_CALCULATOR = 210,
    AAP_KEYCODE_ZENKAKU_HANKAKU = 211,
    AAP_KEYCODE_EISU = 212,
    AAP_KEYCODE_MUHENKAN = 213,
    AAP_KEYCODE_HENKAN = 214,
    AAP_KEYCODE_KATAKANA_HIRAGANA = 215,
    AAP_KEYCODE_YEN = 216,
    AAP_KEYCODE_RO = 217,
    AAP_KEYCODE_KANA = 218,
    AAP_KEYCODE_ASSIST = 219,
    AAP_KEYCODE_BRIGHTNESS_DOWN = 220,
    AAP_KEYCODE_BRIGHTNESS_UP = 221,
    AAP_KEYCODE_MEDIA_AUDIO_TRACK = 222,
    AAP_KEYCODE_SLEEP = 223,
    AAP_KEYCODE_WAKEUP = 224,
    AAP_KEYCODE_PAIRING = 225,
    AAP_KEYCODE_MEDIA_TOP_MENU = 226,
    AAP_KEYCODE_11 = 227,
    AAP_KEYCODE_12 = 228,
    AAP_KEYCODE_LAST_CHANNEL = 229,
    AAP_KEYCODE_TV_DATA_SERVICE = 230,
    AAP_KEYCODE_VOICE_ASSIST = 231,
    AAP_KEYCODE_TV_RADIO_SERVICE = 232,
    AAP_KEYCODE_TV_TELETEXT = 233,
    AAP_KEYCODE_TV_NUMBER_ENTRY = 234,
    AAP_KEYCODE_TV_TERRESTRIAL_ANALOG = 235,
    AAP_KEYCODE_TV_TERRESTRIAL_DIGITAL = 236,
    AAP_KEYCODE_TV_SATELLITE = 237,
    AAP_KEYCODE_TV_SATELLITE_BS = 238,
    AAP_KEYCODE_TV_SATELLITE_CS = 239,
    AAP_KEYCODE_TV_SATELLITE_SERVICE = 240,
    AAP_KEYCODE_TV_NETWORK = 241,
    AAP_KEYCODE_TV_ANTENNA_CABLE = 242,
    AAP_KEYCODE_TV_INPUT_HDMI_1 = 243,
    AAP_KEYCODE_TV_INPUT_HDMI_2 = 244,
    AAP_KEYCODE_TV_INPUT_HDMI_3 = 245,
    AAP_KEYCODE_TV_INPUT_HDMI_4 = 246,
    AAP_KEYCODE_TV_INPUT_COMPOSITE_1 = 247,
    AAP_KEYCODE_TV_INPUT_COMPOSITE_2 = 248,
    AAP_KEYCODE_TV_INPUT_COMPONENT_1 = 249,
    AAP_KEYCODE_TV_INPUT_COMPONENT_2 = 250,
    AAP_KEYCODE_TV_INPUT_VGA_1 = 251,
    AAP_KEYCODE_TV_AUDIO_DESCRIPTION = 252,
    AAP_KEYCODE_TV_AUDIO_DESCRIPTION_MIX_UP = 253,
    AAP_KEYCODE_TV_AUDIO_DESCRIPTION_MIX_DOWN = 254,
    AAP_KEYCODE_TV_ZOOM_MODE = 255,
    AAP_KEYCODE_TV_CONTENTS_MENU = 256,
    AAP_KEYCODE_TV_MEDIA_CONTEXT_MENU = 257,
    AAP_KEYCODE_TV_TIMER_PROGRAMMING = 258,
    AAP_KEYCODE_HELP = 259,
    AAP_KEYCODE_NAVIGATE_PREVIOUS = 260,
    AAP_KEYCODE_NAVIGATE_NEXT = 261,
    AAP_KEYCODE_NAVIGATE_IN = 262,
    AAP_KEYCODE_NAVIGATE_OUT = 263,
    AAP_KEYCODE_DPAD_UP_LEFT = 268,
    AAP_KEYCODE_DPAD_DOWN_LEFT = 269,
    AAP_KEYCODE_DPAD_UP_RIGHT = 270,
    AAP_KEYCODE_DPAD_DOWN_RIGHT = 271,
    AAP_KEYCODE_SENTINEL = 65535,
    AAP_KEYCODE_ROTARY_CONTROLLER = 65536,
    AAP_KEYCODE_MEDIA = 65537,
    AAP_KEYCODE_NAVIGATION = 65538,
    AAP_KEYCODE_RADIO = 65539,
    AAP_KEYCODE_TEL = 65540,
    AAP_KEYCODE_PRIMARY_BUTTON = 65541,
    AAP_KEYCODE_SECONDARY_BUTTON = 65542,
    AAP_KEYCODE_TERTIARY_BUTTON = 65543
}AAP_KeyCodes;

/*! \enum AAP_TouchScreenType
 * \brief Enumeration to specify all supported touch screen type. */
typedef enum
{
    /*! Touch screen type is capacitive. */
    AAP_TOUCH_SCREEN_TYPE_CAPACITIVE = 0x10,
    /*! Touch screen type is resistive. */
    AAP_TOUCH_SCREEN_TYPE_RESISTIVE
}AAP_TouchScreenType;

/*! \struct AAP_Key
 * \brief Structure to hold information about a key action.
 *
 * This is the preferred interface for signaling key presses.*/
typedef struct
{
    /*! true if it is a press, false if it is a release. */
    AAP_BOOL bDown;
    /*! Can be used to represent shift, alt etc. Currently unused.*/
    AAP_UINT32 uiMetaState;
}AAP_Key;

/*! \struct AAP_Absolute
 * \brief Structure to report a value from a device to send out an absolute value */
typedef struct
{
    /*! The absolute value associated with that device.
     * For example, if a wheel goes from 0-10, the value would be that. */
    AAP_INT32 iValue;
}AAP_Absolute;

/*! \struct AAP_KeyLongPress
 * \brief Structure to hold information to signal a long press of a button.
 *
 * Do not report a key up after this. Use this input method only if applications have to. */
typedef struct
{
    /*! Can be used to represent shift, alt etc. Currently unused.*/
    AAP_UINT32 uiMetaState;
}AAP_KeyLongPress;

/*! \struct AAP_Relative
 * \brief Structure to report a value from a device to send out a relative value */
typedef struct
{
    /*! The value associated with this event. Application can indicate a magnitude and
     * direction using the value and its sign. For instance, if a jog dial were
     * turned two steps to the left, delta would be -2. If it were turned 5 steps
     * to the right, delta would be +5. */
    AAP_INT32 iDelta;
}AAP_Relative;

/*! \struct AAP_KeyEvent
 *  \brief Structure to specify various key events
 */
typedef struct
{
    /*! Type of the value : key, relative, absolute or long press */
    AAP_KeyValType eType;
    /*! Key code associated with the key event*/
    AAP_KeyCodes eKeyCode;
    /*! Event data*/
    union
    {
        /*! This structure to be accessed if #AAP_KEY_VALUE_NORMAL is the value of
         * AAP_KeyValType */
        AAP_Key sKey;
        /*! This structure to be accessed if #AAP_KEY_VALUE_ABSOLUTE is the value of
         * AAP_KeyValType */
        AAP_Absolute sAbsolute;
        /*! This structure to be accessed if #AAP_KEY_VALUE_LONG_PRESS is the value of
         * AAP_KeyValType */
        AAP_KeyLongPress sKeyLongPress;
        /*! This structure to be accessed if #AAP_KEY_VALUE_RELATIVE is the value of
         * AAP_KeyValType */
        AAP_Relative sRelative;
    };
}AAP_KeyEvent;

/*! \struct AAP_LocationData
  * \brief Structure to specify the GPS Location data
  * \note
  * - Should be raw GPS values.
  * - May be dead reckoned (DR) values and/or sensor fusion values.
  * - Must not be map matched values.
  * - Must be characterized using the locationCharacterization flag.
  * - May be sent to MD when no GPS fix available if the most recent number of satellites reported was zero (0).
  * - The eX multiplication is to allow for fixed point representation of decimal values using an int32.\n
  *   For example, the value 3.1415 becomes 31415000 in E7 notation and can be represented as an integer.
 */
typedef struct
{
    /*! Time-stamp of this GPS location in nanoseconds.*/
    AAP_UINT64 ulTimestamp;
    /*! Latitude value [-90.0, +90.0] multiplied by 1e7. */
    AAP_INT32 iLatitudeE7;
    /*! Longitude value [-180.0, +180.0) multiplied by 1e7.*/
    AAP_INT32 iLongitudeE7;
    /*! True if accuracy of this location is known and iAccuracyE3 param is valid.*/
    AAP_BOOL bHasAccuracy;
    /*! Horizontal 68% radius meters value multiplied by 1e3*/
    AAP_INT32 iAccuracyE3;
    /*! True if the iAltitudeE2 param should be considered, false otherwise.*/
    AAP_BOOL bHasAltitude;
    /*! The altitude in meters above sea level multiplied by 1e2.*/
    AAP_INT32 iAltitudeE2;
    /*! True if the iSpeedE3 param should be considered, false otherwise*/
    AAP_BOOL bHasSpeed ;
    /*! The speed in m/s absolute velocity multiplied by 1e3*/
    AAP_INT32 iSpeed;
    /*! True if the iBearingE6 param should be considered, false otherwise*/
    AAP_BOOL bHasBearing;
    /*! The compass bearing [0, 360) multiplied by 1e6.*/
    AAP_INT32 iBearingE6;
}AAP_LocationData;

/*! \struct AAP_CompassData;
  * \brief Structure to specify report the current car's orientation (3D) or on-board magnetic compass
  * \note
  * Values reported here might be used in dead reckoning the position of the vehicle in the event of a GPS signal loss
 */
typedef struct
{
    /*! TRUE if 3D data available */
    AAP_BOOL bHas3D;
    /*! The compass bearing [0, 360) multiplied by 1e6*/
    AAP_INT32 iBearingE6;
    /*! True if pitch parameter provided is valid.*/
    AAP_BOOL bHasPitch;
    /*! Car's pitch [-90, 90] multiplied by 1e6. Nose down is positive.*/
    AAP_INT32 iPitchE6;
    /*! True if roll parameter provided is valid.*/
    AAP_BOOL bHasRoll;
    /*! Car's roll (-180, 180] multiplied by 1e6. Right door down is positive.*/
    AAP_INT32 iRollE6;
}AAP_CompassData;

/*! \struct AAP_SpeedData
 * \brief Structure to specify the current speed of the vehicle.
 */
typedef struct
{
    /*! The speed in m/s absolute velocity multiplied by 1e3*/
    AAP_INT32 iSpeedE3;
    /*! TRUE if the #bIsCarEngaged parameter is valid. */
    AAP_BOOL bIsCarEngagedValid;
    /*! Whether are not car control is engaged. */
    AAP_BOOL bIsCarEngaged;
    /*! TRUE if the #iCarSetSpeed parameter is valid. */
    AAP_BOOL bIsCarSetSpeedValid;
    /*! To set the speed of the car in meter/second. */
    AAP_INT32 iCarSetSpeed;
}AAP_SpeedData;

/*! \struct AAP_RpmData
 * \brief Structure to specify the current engine RPM value.
 */
typedef struct
{
    /*! The engine RPM value multiplied by 1e3. */
    AAP_INT32 iRpmE3;
}AAP_RpmData;

/*! \struct AAP_OdometerData
 * \brief Structure to specify the current value of the odometer.
 */
typedef struct
{
    /*! The odometer data in kilometers multiplied by 1e1. */
    AAP_INT32 iKmsE1;
    /*! TRUE if the #iCurrTripKmsE1 parameter is valid */
    AAP_BOOL bCurrTripKmsValid;
    /*! Distance travelled since ignition was turned on multiplied by 1e1, in km.
     * */
    AAP_INT32 iCurrTripKmsE1;
}AAP_OdometerData;

/*! \struct AAP_FuelData
 * \brief Structure to specify the information about fuel
 */
typedef struct
{
    /*! True if the fuel remaining percent parameter should be considered, false otherwise*/
    AAP_BOOL bHasFuelRemainingPercent;
    /*! Fuel remaining in whole number percent values*/
    AAP_INT32 iFuelRemainingPercent;
    /*! True if the rangeKm parameter should be considered, false otherwise*/
    AAP_BOOL bHasRangeKm;
    /*! The estimated remaining range for the current amount of fuel*/
    AAP_INT32 iRangeKm;
    /*! True if the low fuel warning parameter is valid*/
    AAP_BOOL bHasLowFuelWarning;
    /*! True if the low fuel warning is on, false otherwise*/
    AAP_BOOL bLowFuelWarning;
}AAP_FuelData;

/*! \struct AAP_ParkingBrakeData
 * \brief Structure to report whether the parking brake is engaged or not.
 */
typedef struct
{
    /*! True if the parking brake is engaged, false otherwise*/
    AAP_BOOL bParkingBreakEngaged;
}AAP_ParkingBrakeData;

/*! \enum AAP_GearType
 \brief Enumeration to specify different types of gear
*/
typedef enum
{
     /*! In Neutral*/
     AAP_GEAR_NEUTRAL = 0xF00,
     /*! Gear 1 */
     AAP_GEAR_1,
     /*! Gear 2 */
     AAP_GEAR_2,
     /*! Gear 3 */
     AAP_GEAR_3,
     /*! Gear 4 */
     AAP_GEAR_4,
     /*! Gear 5 */
     AAP_GEAR_5,
     /*! Gear 6 */
     AAP_GEAR_6,
     /*! Gear 7 */
     AAP_GEAR_7,
     /*! Gear 8 */
     AAP_GEAR_8,
     /*! Gear 9 */
     AAP_GEAR_9,
     /*! Gear 10 */
     AAP_GEAR_10,
     /*! Gear drive */
     AAP_GEAR_DRIVE,
     /*! Gear park */
     AAP_GEAR_PARK,
     /*! Gear reverse */
     AAP_GEAR_REVERSE
}AAP_GearType;

/*! \struct AAP_GearData
 * \brief Structure to report which gear the vehicle is in.
 */
typedef struct
{
    /*! Current Gear. */
    AAP_GearType eGear;
}AAP_GearData;

/*! \struct AAP_NightModeData
 * \brief Structure to report the value of the day-night sensor.
 *
 * The value of this sensor will affect the UI of projected applications.
 */
typedef struct
{
    /*! true if night mode is enabled, false otherwise */
    AAP_BOOL bNightMode;
}AAP_NightModeData;

/*! \struct AAP_EnvData
\brief Structure to specify data about the external environment.
*/
typedef struct
{
    /*! Is the temperature value valid*/
    AAP_BOOL bHasTemp;
    /*! The temperature in Celsius multiplied by 1e3 */
    AAP_INT32 iTemperatureE3;
    /*! Is the pressure parameter value valid*/
    AAP_BOOL bHasPressure;
    /*! Pressure in kPA multiplied by 1e3*/
    AAP_INT32 iPressureE3;
    /*! TRUE if the #iRainLevel parameter is valid. */
    AAP_BOOL bRainLevelValid;
    /*! The rain detection level. 0 means no rain. */
    AAP_INT32 iRainLevel;
}AAP_EnvData;

/*! \struct AAP_HVACData
 * \brief Structure to specify the data about the HVAC system.
 */
typedef struct
{
    /*! Is the target temperature parameter valid*/
    AAP_BOOL bHasTargetTemp;
    /*! Target temperature in Celsius multiplied by 1e3*/
    AAP_INT32 iTargetTempE3;
    /*! Is the cabin temperature param valid*/
    AAP_BOOL bHasCurrentTemp;
    /*! Current cabin temperature in Celsius multiplied by 1e3*/
    AAP_INT32 iCurrentTempE3;
}AAP_HVACData;

/*! \struct AAP_DrivingStatusData
 * \brief Structure that contains the value of the driving status i.e drive level.
 */
typedef struct
{
    /*! Driving status. A bitmask of restrictions currently in effect.
     * Refer #AAP_DrivingStatusType */
    AAP_INT32 iDrivingStatus;
}AAP_DrivingStatusData;

/*! \struct AAP_DeadReckData
  * \brief Structure to specify data about wheel speed and steering angle
 */
typedef struct
{
    /*! Is the steeringAngleE1 param valid */
    AAP_BOOL bHasSteeringAngle;
    /*! Steering angle in tenths of a degree multiplied by 10. Left is negative*/
    AAP_INT32 iSteeringAngleE1;
    /*! An array of wheel speeds in m/s multiplied by 1e3. Start from the front left and go clockwise */
    AAP_INT32 aiWheelSpeedE3[AAP_MAX_NUM_TIRE];
    /*! WheelSpeedEntries   Number of elements in the wheel speed array*/
    AAP_INT32 iWheelSpeedEntries;
}AAP_DeadReckData;

/*! \struct AAP_PassengerData
 * \brief Structure to report data about passenger presence.
 */
typedef struct
{
    /*! TRUE if a passenger is present, false otherwise*/
    AAP_BOOL bPassengerPresent;
}AAP_PassengerData;

/*! \struct AAP_TollCardData
 * \brief Structure to report data about Toll card presence.
 */
typedef struct
{
    /*! TRUE if Toll card is present, false otherwise */
    AAP_BOOL bTollCardPresent;
}AAP_TollCardData;

/*! \struct AAP_DoorData
\brief Structure to specify date about opened or closed doors.
*/
typedef struct
{
    /*! Is the hoodOpen param valid.*/
    AAP_BOOL bHasHoodOpen;
    /*! True if the hood is open, false otherwise*/
    AAP_BOOL bHoodOpen;
    /*! Is the trunkOpen param valid */
    AAP_BOOL bHasTrunkOpen;
    /*! True if the trunk is open, false otherwise*/
    AAP_BOOL bTrunkOpen;
    /*! Array of door states, true if the door is open, false otherwise*/
    AAP_BOOL abDoorOpen[AAP_MAX_NUM_DOOR];
    /*! Number of elements in the door open array*/
    AAP_INT32 iNumDoorOpen;
}AAP_DoorData;

/*! \enum AAP_HeadLightState
 \brief Enumeration to specify different head light state
*/
typedef enum
{
     /*! For head light off */
     AAP_HEAD_LIGHT_STATE_OFF = 1,
     /*! For head light on */
     AAP_HEAD_LIGHT_STATE_ON,
     /*! For head light on and high */
     AAP_HEAD_LIGHT_STATE_HIGH
}AAP_HeadLightState;

/*! \enum AAP_TurnIndicatorState
 \brief Enumeration to specify the turn indicator values.
*/
typedef enum
{
     /*! For no turn indication */
     AAP_TURN_INDICATOR_NONE = 1,
     /*! For left turn indication */
     AAP_TURN_INDICATOR_LEFT,
     /*! For right turn indication */
     AAP_TURN_INDICATOR_RIGHT
}AAP_TurnIndicatorState;

/*! \struct AAP_LightData
\brief Structure to specify safety data
*/
typedef struct
{
    /*! Is the headLightState param valid*/
    AAP_BOOL bHasHeadLightState;
    /*! The state of the head lights*/
    AAP_HeadLightState eHeadLightState;
    /*! Is the turnIndicatorState param valid*/
    AAP_BOOL bHasTurnIndicatorState;
    /*! The turn indicator state.*/
    AAP_TurnIndicatorState eTurnIndicatorState;
    /*! Is the hazardLightsOn param valid. */
    AAP_BOOL bHasHazardLightsOn;
    /*! True if hazard lights are on, false otherwise.*/
    AAP_BOOL bHazardLightsOn;
}AAP_LightData;

/*! \struct AAP_TirePressureData
\brief Structure to report data about tire pressures.
*/
typedef struct
{
    /*! An array of tire pressure values in psi multiplied by 1e2*/
    AAP_INT32 aiTirePressuresE2[AAP_MAX_NUM_TIRE];
    /*! The number of elements in the TirePressuresE2 array*/
    AAP_INT32 iNumTireEntries;
}AAP_TirePressureData;

/*! \struct AAP_AcceleroMeterData
 * \brief Structure to specify data from accelerometer (include gravity).
 *
 * Units are in m/s^2 multiplied by 1e3.
*/
typedef struct
{
    /*! Acceleration along X-axis is valid*/
    AAP_BOOL bHasAccelerationX;
    /*! Acceleration from left door to right, multiplied by 1e3 */
    AAP_INT32 iXAccelerationE3;
    /*! Acceleration along Y-axis is valid*/
    AAP_BOOL bHasAccelerationY;
    /*! Acceleration from back to nose*/
    AAP_INT32 iYAccelerationE3;
    /*! Acceleration along Z-axis is valid*/
    AAP_BOOL bHasAccelerationZ;
    /*! Acceleration from floor to ceiling*/
    AAP_INT32 iZAccelerationE3;
}AAP_AcceleroMeterData;

/*! \struct AAP_GyroData
  * \brief Structure to specify data from gyroscope.
  *
  * Units are in rad/s multiplied by 1e3.
 */
typedef struct
{
    /*! Rotation speed around X-axis is valid*/
    AAP_BOOL bHasRotationSpeedX;
    /*! Rotation speed around axis from left door to right*/
    AAP_INT32 iXRotationSpeedE3;
    /*! Rotation speed around Y-axis is valid*/
    AAP_BOOL  bHasRotationSpeedY;
    /*! Rotation speed around axis from back to nose*/
    AAP_INT32 iYRotationSpeedE3;
    /*! Rotation speed around Z-axis is valid*/
    AAP_BOOL bHasRotationSpeedZ;
    /*! Rotation speed around axis from floor to ceiling*/
    AAP_INT32 iZRotationSpeedE3;
}AAP_GyroData;

/*! \struct AAP_GpsSateliteData
 * \brief Structure to specify the satellite data from GPS.
 * \note
 *  - Must include the number of GPS satellites used in determining the location.
 *  - Must have the number of GPS satellites used in determining the location set to zero (0) when the HU does not have GPS lock.
 *  - Must have the number of GPS satellites used in determining the location set to greater than zero (0) when the HU has GPS lock.
 *  - Must be sent all the time, regardless of whether location fix was acquired or not.
 *  - May include the number of GPS satellites in view.
 *  - May include per-satellite information
 */
typedef struct
{
    /*! Number of satellites used in GPS fix*/
    AAP_INT32  iNumberInUse;
    /*! Whether number in view is valid*/
    AAP_BOOL bHasNumberInView;
    /*! Number of satellites visible to the GPS receiver*/
    AAP_INT32 iNumberInView;
    /*! Array of PRNs of satellites in view or NULL if per-satellite info unavailable*/
    AAP_INT32 aiPRNS[AAP_MAX_NUM_SATELITE];
    /*! Array of SNRs of satellites in view in dB multiplied by 1e3 or NULL if per-satellite info unavailable*/
    AAP_INT32 aiSNRSE3[AAP_MAX_NUM_SATELITE];
    /*! Array of flags whether this satellite was used in GPS fix or NULL if per-satellite info unavailable*/
    AAP_BOOL abUsedInFix[AAP_MAX_NUM_SATELITE];
    /*! Array of azimuths of satellites in degrees clockwise from north multiplied by 1e3 or NULL if per-satellite\n
    info unavailable or position data for satellites is absent*/
    AAP_INT32 aiAzimuthsE3[AAP_MAX_NUM_SATELITE];
    /*! Array of elevations of satellites in degrees from horizon to zenith multiplied by 1e3 or NULL if per-satellite\n
    info unavailable or position data for satellites is absent*/
    AAP_INT32 aiElevationsE3[AAP_MAX_NUM_SATELITE];
}AAP_GpsSateliteData;

/*! \enum AAP_SensorType
 * \brief Enumeration of different sensor type.
 */
typedef enum
{
    /*! GPS sensor */
    AAP_SENSOR_LOCATION = 0x01,
    /*! Compass sensor */
    AAP_SENSOR_COMPASS,
    /*! Speed sensor */
    AAP_SENSOR_SPEED,
    /*! RPM sensor */
    AAP_SENSOR_RPM,
    /*! Odometer sensor */
    AAP_SENSOR_ODOMETER,
    /*! Fuel sensor */
    AAP_SENSOR_FUEL,
    /*! Parking brake sensor */
    AAP_SENSOR_PARKING_BRAKE,
    /*! Gear sensor */
    AAP_SENSOR_GEAR,
    /*! OBDII diagnostic code */
    AAP_SENSOR_OBDII_DIAGNOSTIC_CODE,
    /*! Night mode sensor */
    AAP_SENSOR_NIGHT_MODE,
    /*! Environment sensor */
    AAP_SENSOR_ENVIRONMENT_DATA,
    /*! HVAC data */
    AAP_SENSOR_HVAC_DATA,
    /*! Driving status data */
    AAP_SENSOR_DRIVING_STATUS_DATA,
    /*! Dead reckoning data */
    AAP_SENSOR_DEAD_RECKONING_DATA,
    /*! Pasenger data */
    AAP_SENSOR_PASSENGER_DATA,
    /*! Door data */
    AAP_SENSOR_DOOR_DATA,
    /*! Light data */
    AAP_SENSOR_LIGHT_DATA,
    /*! Sensors for tire pressure */
    AAP_SENSOR_TIRE_PRESSURE_DATA,
    /*! Accelerometer data */
    AAP_SENSOR_ACCELEROMETER_DATA,
    /*! Gyroscope data */
    AAP_SENSOR_GYROSCOPE_DATA,
    /*! GPS satelite data */
    AAP_SENSOR_GPS_SATELLITE_DATA,
    /*! Toll card data */
    AAP_SENSOR_TOLL_CARD_DATA,
    /*! This is to report sensor errors for any sensor type.
     * \note No need to register this sensor type to report the sensor errors.
     */
    AAP_SENSOR_ERROR_DATA
}AAP_SensorType;

/*! \enum AAP_SensorErrorType
 * \brief These are the sensor error types */
typedef enum
{
    /*! This is used to report the recovery from sensor error state. */
    AAP_SENSOR_OK = 0x1,
    /*! This is used to report when HU can recover from the sensor errors. */
    AAP_SENSOR_ERROR_TRANSIENT,
    /*! This is used to report when HU can not recover from the sensor errors. */
    AAP_SENSOR_ERROR_PERMANENT
}AAP_SensorErrorType;

/*! \struct AAP_SensorErrorData
\brief Structure to report sensor errors.
\note If error is recoverable immediately, there is no need to send this message.
*/
typedef struct
{
    /*! This is to indicate which sensor is encountering problems. */
    AAP_SensorType eSensorType;
    /*! This indicates the type of sensor errors. */
    AAP_SensorErrorType eSensorErrorType;
}AAP_SensorErrorData;

/*! \enum AAP_LocationCharacterization
 * \brief TODO:: Need to add explanation */
typedef enum
{
    AAP_PRIOR_LOCATIONS = 1,
    AAP_GYROSCOPE_FUSION = 2,
    AAP_ACCELEROMETER_FUSION = 4,
    AAP_COMPASS_FUSION = 8,
    AAP_WHEEL_SPEED_FUSION = 16,
    AAP_STEERING_ANGLE_FUSION = 32,
    AAP_CAR_SPEED_FUSION = 64,
    AAP_DEAD_RECKONED = 128,
    AAP_RAW_GPS_ONLY = 256
}AAP_LocationCharacterization;

/*! \enum AAP_FuelType
 * \brief Enumeration of different fuel type.
 */
typedef enum
{
    /*! Unleaded fuel type */
    AAP_FUEL_TYPE_UNLEADED = 1,
    /*! Leaded fuel type */
    AAP_FUEL_TYPE_LEADED = 2,
    /*! Diesel_1 fuel type */
    AAP_FUEL_TYPE_DIESEL_1 = 3,
    /*! Diesel_2 fuel type */
    AAP_FUEL_TYPE_DIESEL_2 = 4,
    /*! Biodiesel fuel type */
    AAP_FUEL_TYPE_BIODIESEL = 5,
    /*! E85 fuel type */
    AAP_FUEL_TYPE_E85 = 6,
    /*! LPG fuel type */
    AAP_FUEL_TYPE_LPG = 7,
    /*! CNG fuel type */
    AAP_FUEL_TYPE_CNG = 8,
    /*! LNG fuel type */
    AAP_FUEL_TYPE_LNG = 9,
    /*! Electric fuel type */
    AAP_FUEL_TYPE_ELECTRIC = 10,
    /*! Hydrogen fuel type */
    AAP_FUEL_TYPE_HYDROGEN = 11,
    /*! Other fuel type */
    AAP_FUEL_TYPE_OTHER = 12
}AAP_FuelType;

/*! \enum AAP_EvConnectorType
 * \brief Enumeration of different connector type.
 */
typedef enum
{
    /*! Unknown connector type */
    AAP_EV_CONNECTOR_TYPE_UNKNOWN = 0,
    /*! J1772 connector type */
    AAP_EV_CONNECTOR_TYPE_J1772 = 1,
    /*! Mennekes connector type */
    AAP_EV_CONNECTOR_TYPE_MENNEKES = 2,
    /*! Chademo connector type */
    AAP_EV_CONNECTOR_TYPE_CHADEMO = 3,
    /*! Combo_1 connector type */
    AAP_EV_CONNECTOR_TYPE_COMBO_1 = 4,
    /*! Combo_2 connector type */
    AAP_EV_CONNECTOR_TYPE_COMBO_2 = 5,
    /*! Tesla roadster connector type */
    AAP_EV_CONNECTOR_TYPE_TESLA_ROADSTER = 6,
    /*! Tesla HPWC connector type */
    AAP_EV_CONNECTOR_TYPE_TESLA_HPWC = 7,
    /*! Tesla supercharger connector type */
    AAP_EV_CONNECTOR_TYPE_TESLA_SUPERCHARGER = 8,
    /*! GBT connector type */
    AAP_EV_CONNECTOR_TYPE_GBT = 9,
    /*! Other connector type */
    AAP_EV_CONNECTOR_TYPE_OTHER = 101
}AAP_EvConnectorType;


/*! \struct AAP_VECService
  \brief Structure to specify all the information of the phone side service and
  the application to which VEC has to be connected. */
typedef struct
{
    /*! Android Service name to which the VEC has to be connected\n
     * \note: The array must consist of a NULL terminated string */
    AAP_CHAR acServiceName[MAX_VEC_SERVICE_NAME_LENGTH];
    /*! Number of whitelisted applications in acApps array */
    AAP_UINT32 uiNumApps;
    /*! 2-d array containing names of all the whitelisted apps to which VEC can
     * be connected to\n
     * \note: The array must consist of a NULL terminated string */
    AAP_CHAR acApps[AAP_MAX_NUM_VEC_APPS][MAX_VEC_APP_NAME_LENGTH];
}AAP_VECService;

/*! \struct AAP_VECInfo
 * \brief Structure to specify number of VEC services registered and maintain a
 * list containing information related to each service. */
typedef struct
{
  /*! Number of VEC to be created. Max: #AAP_MAX_VEC_SERVICES. */
  AAP_UINT32 uiNumVecServices;
  /*! Structure to specify info of service and applications on phone side */
  AAP_VECService asVecServices[AAP_MAX_VEC_SERVICES];
}AAP_VECInfo;

/*! \struct AAP_Attributes
 * \brief Structure to specify the configurations accepted after create session
 * but before starting a session.
 *
 * \note If AAP stack fails to set the attributes due to some invalid value, session
 * will either use default values given in the respective attributes of this structure
 * or last valid attributes successfully set using #aap_set_attributes(),
 * provided, in latter case, #aap_destroy_session() was not called in between. */
typedef struct
{
    /*! The Car Maker.
     * AAP SDK Integrator can change this string appropriately.
     * It is a NULL terminated string.\n
     * <b>Default:</b> "AllGo" */
    AAP_CHAR acVehicleMake[AAP_DEFAULT_STRING_LEN];
    /*! Car model name. It is a NULL terminated string.\n
     * <b>Default:</b> "AndroidAuto" */
    AAP_CHAR acVehicleModel[AAP_DEFAULT_STRING_LEN];
    /*! Car Production year. It is a NULL terminated string.\n
     * <b>Default:</b> "multi" */
    AAP_CHAR acModelYear[AAP_DEFAULT_STRING_LEN];
    /*! String which MD will display as-is to refer to the native software experience.
     * This string will appear on the head unit to return
     * to native screen. It will display "Return to <String in acDisplayName>".
     * If it is not set, the value of #acVehicleMake will be used instead.
     * It is a NULL terminated string.\n
     * <b>Default:</b> "AllgoAAP" */
    AAP_CHAR acDisplayName[AAP_DEFAULT_STRING_LEN];
    /*! Vehicle Identifier for the vehicle.
     * A valid Vehicle ID should exhibit the properties below.
     * - <b>Unique ID per HU:</b>
     *   Android Auto uses Vehicle ID to determine if the First Run Experience
     *   has run on a given head unit (HU). The Vehicle ID must be unique to
     *   the individual HU, ie. not shared across multiple HUs of the same make/model.
     *   The value can be random, as long as the same value is retained within
     *   a HU until factory reset occurs.
     * - <b>Minimum 64 Bits:</b>
     *   To reduce the chances of ID collision, Vehicle IDs should have at least 64 bits.
     *   That is, at least 2^64 values are possible within the definition of the ID.\n
     *   For example, if an ID can be made up of the following characters: [A-Z, a-z, 0-9],
     *   that gives 62 possible values for each character, which can be represented
     *   by 6 bits (2^6=64). To exceed 64 bits, at least 11 characters would be needed (roundup 64/6).\n
     *   Likewise, if an ID consists of [A-Z, 0-9], each character has 36 possible
     *   values, which is roughly 5 bits (2^5=32). The ID would need 13 characters
     *   to cover 64-bit space (roundup 64/5).
     *
     * <b>Default:</b> "8d11fb57-c7cb-44c6-8599-19d763969437" */
    AAP_CHAR acVehicleId[AAP_DEFAULT_STRING_LEN];
    /*! Indicates the position (#AAP_DRIVER_POSITION_LEFT, #AAP_DRIVER_POSITION_RIGHT,
     * #AAP_DRIVER_POSITION_CENTRE, #AAP_DRIVER_POSITION_UNKNOWN) of the steering wheel,
     * which may influence the position of UI elements.\n
     * <b>Default:</b> #AAP_DRIVER_POSITION_RIGHT */
    AAP_UINT32 uiDriverPosition;
    /*! Software build of the head unit. It is a NULL terminated string.\n
     * <b>Default:</b> "Generic" */
    AAP_CHAR acHUSWBuild[AAP_DEFAULT_STRING_LEN];
    /*! Software version of the head unit. It is a NULL terminated string.\n
     * <b>Default:</b> "1.0" */
    AAP_CHAR acHUSWVersion[AAP_DEFAULT_STRING_LEN];
    /*! Head unit BT MAC ID in the form of NULL terminated string e.g. "00:02:5B:77:11:22"\n
     * If the HU wants the MD to skip the Bluetooth pairing and connection
     * process, the HU can send "SKIP_THIS_BLUETOOTH" string through this variable.\n
     * <b>Default:</b> No default is assumed by the SDK.*/
    AAP_CHAR acBTMacId[AAP_DEFAULT_STRING_LEN];
    /*! Number of pairing types supported by the HU i.e the length of auiBTPairMethod array.\n
     * <b>Max:</b> #AAP_MAX_BT_PAIRING_METHOD\n
     * <b>Default:</b> 0 */
    AAP_UINT32 uiNumPairTypes;
    /*! Array of BT pairing methods.\n
     * Application must add all the BT pairing methods which it supports.
     * One among these methods will be used by the phone to pair.\n
     * Available options: #AAP_BT_PAIRING_PIN, #AAP_BT_PAIRING_NUMERIC\n
     * <b>Default:</b> Array initialized to 0 */
    AAP_UINT32 auiBTPairMethod[AAP_MAX_BT_PAIRING_METHOD];
    /*! Number of sensor device supported i.e the length of aeSensors array.\n
     * <b>Max:</b> #AAP_MAX_NUM_SENSORS\n
     * <b>Default:</b> 4*/
    AAP_UINT32 uiNumSensors;
    /*! Specify all the supported sensors in this array. This array will replace
     * the elements of the default array.\n
     * <b>Default:</b> #AAP_SENSOR_LOCATION, #AAP_SENSOR_DRIVING_STATUS_DATA
     * #AAP_SENSOR_NIGHT_MODE and #AAP_SENSOR_GPS_SATELLITE_DATA\n
     * <b>Mandatory:</b> #AAP_SENSOR_DRIVING_STATUS_DATA, #AAP_SENSOR_NIGHT_MODE, and
     * #AAP_SENSOR_LOCATION if the HU supports Wireless AAP.\n
     * Even if the application doesn't add this mandatory sensors to the array,
     * AAP SDK will take care of adding it except #AAP_SENSOR_LOCATION.*/
    AAP_SensorType aeSensors[AAP_MAX_NUM_SENSORS];
    /*! Bitmask of different enum value of #AAP_LocationCharacterization*/
    AAP_UINT32 uiLocCharacterization;
    /*! Number of fuel types car supported.\n
     * <b>Max:</b> #AAP_MAX_NUM_FUEL_TYPES*/
    AAP_UINT32 uiNumFuelTypes;
    /*! List of all fuel types supported by car.\n
     * \note If application mention AAP_FUEL_TYPE_ELECTRIC as fuel type but doesn't
     * have any connector type, then AAP stack will add the
     * #AAP_EV_CONNECTOR_TYPE_UNKNOWN as one of the connector type. */
    AAP_FuelType aeFuelTypes[AAP_MAX_NUM_FUEL_TYPES];
    /*! Number of connectors types car supported for electric charging.\n
     * <b>Max:</b> #AAP_MAX_NUM_CONNECTOR_TYPES*/
    AAP_UINT32 uiNumConnectorTypes;
    /*! List of all electric charging connector types supported by car,
     * sorted from most preferred connector to least preferred. If this list
     * is non-empty, the #aeFuelTypes set must contain #AAP_FUEL_TYPE_ELECTRIC element.\n
     * \note If #aeFuelTypes doesn't contain #AAP_FUEL_TYPE_ELECTRIC but #aeConnectorTypes
     * contains valid connector types then AAP stack will add the
     * #AAP_FUEL_TYPE_ELECTRIC as one of the fuel type. */
    AAP_EvConnectorType aeConnectorTypes[AAP_MAX_NUM_CONNECTOR_TYPES];
    /*! Average screen-eye viewing distance in millimeters.\n
     * <b>Default:</b> #AAP_DEFAULT_VIEWING_DISTANCE\n*/
    AAP_UINT32 uiViewDistance;
    /*! Indicates whether the information set in #AAP_VECInfo structure is valid
     *  or not.\n If #bIsValidVecInfo is #AAP_TRUE, the data contained by #AAP_VECInfo
     *  structure will be considered else not.\n
     *  <b>Default:</b> #AAP_FALSE\n*/
    AAP_BOOL bIsValidVecInfo;
    /*! Specify info of all the VEC services to be registered.\n
     *
     *  If AAP stack fails to set the values through #aap_set_attributes(), VEC
     *  details will be used either from aap_system_attributes.xml or from the
     *  last valid VEC details set through #aap_set_attributes() provided in
     *  latter case #aap_destroy_session() was not called in between.
     *
     *  \note Will only be accessed if #bIsValidVecInfo is set to #AAP_TRUE.\n
     *
     *  <b>Ex:</b> To register a service with name "com.example.xyz" and an app
     *  namely "com.example.echovendor", following shall be done:\n
     *  - Assign "com.example.xyz" to sVecInfo.asVecServices[0].acServiceName,
     *  - Assign sVecInfo.asVecServices[0].uiNumApps = 1,
     *  - Assign "com.example.echovendor" to sVecInfo.asVecServices[0].acApps[0] */
    AAP_VECInfo sVecInfo;
    /*! Bit mask of different enum value of #AAP_SessionConfig.
     * <b>Default:</b> 0\n
     * For an example if HU doesn't want to show the phone clock and battery
     * indicator on projection, then set as below:
     * uiSessionConfig = AAP_UI_CONFIG_HIDE_CLOCK | AAP_UI_CONFIG_HIDE_BATTERY_LEVEL */
    AAP_UINT32 uiSessionConfig;
}AAP_Attributes;


/*! \enum AAP_InputDevType
 * \brief Enumeration to specify the available input device type */
typedef enum
{
    /*! Touch screen */
    AAP_INPUT_TYPE_TOUCH_SCREEN = 0x01,
    /*! Touch pad */
    AAP_INPUT_TYPE_TOUCH_PAD,
    /*! Key codes */
    AAP_INPUT_TYPE_KEY_CODES
}AAP_InputDevType;

/*! \struct AAP_VideoRes
 *  \brief Structure to specify all the supported resolution and the
 *  corresponding density */
typedef struct
{
    /*! Video Resolution Value */
    AAP_VideoResType eResValue;
    /*! Height margin\n
     * Height margin and width margin are used to support the wide range of
     * in-vehicle hardware display.
     * These should be used when HU display resolution is lesser than a video resolution.
     * When MD encodes the video stream, it fills horizontal and vertical margins
     * with arbitrary content. So when the HU decodes the stream it MUST discard
     * the margins and render the video except the margin area.
     * For an example, HU has a screen with a resolution of 1200x720, the HU advertises
     * to support for both 1280x720 and 800x480 video. Then the width margin is set to 80
     * and height margin is set to 0 for the 1280x720 configuration,
     * while 800x480 video is scaled 1.5 times before rendering. */
    AAP_INT32 iHeightMargin;
    /*! Width margin\n
     *  Refer to #iHeightMargin */
    AAP_INT32 iWidthMargin;
    /*! Density corresponding to this value in DPI*/
    AAP_INT32 iDensity;
    /*! Real density */
    AAP_INT32 iRealDensity;
    /*! Fps value 60 or 30
     * \par Default: 60 */
    AAP_UINT32 uiVideoFps;
    /*! Pixel Aspect Ratio is the ratio of physical pixel width over height */
    AAP_UINT32 uiDisplayParE4;
    /*! This is to specify the frames needed by decoder to display a frame. */
    AAP_INT32 iDecoderAdditionalDepth;
}AAP_VideoRes;

/*! \enum AAP_VideoCodecType
 * \brief Enumeration to specify different video codec types*/
typedef enum
{
    /*! Video code type required for AAP_VIDEO_RESOLUTION_800x480 */
    AAP_VIDEO_CODEC_H264_BP_L3_1 = 0x1,
    /*! Video codec type required for AAP_VIDEO_RESOLUTION_1280x720 60fps*/
    AAP_VIDEO_CODEC_H264_BP_L3_2,
    /*! Video codec type required for AAP_VIDEO_RESOLUTION_1920x1080 60fps*/
    AAP_VIDEO_CODEC_H264_BP_L4_2
}AAP_VideoCodecType;

/*! \enum AAP_AudioCodecType
 * \brief Enumeration to specify different types of video resolutions */
typedef enum
{
    /*! AudioCodec AAC LC 16Khz mono*/
    AAP_AUDIO_CODEC_AAC_LC_16KHZ_1 = 0x1,
    /*! AudioCodec AAC LC 16Khz stereo */
    AAP_AUDIO_CODEC_AAC_LC_16KHZ_2,
    /*! AudioCodec AAC 44Khz mono */
    AAP_AUDIO_CODEC_AAC_LC_44KHZ_1,
    /*! AudioCodec AAC 44Khz stereo */
    AAP_AUDIO_CODEC_AAC_LC_44KHZ_2,
    /*! AudioCodec AAC 48Khz mono */
    AAP_AUDIO_CODEC_AAC_LC_48KHZ_1,
    /*! AudioCodec AAC 48Khz stereo */
    AAP_AUDIO_CODEC_AAC_LC_48KHZ_2,

    /*! AudioCodec AAC LC ADTS 16Khz mono*/
    AAP_AUDIO_CODEC_AAC_LC_ADTS_16KHZ_1,
    /*! AudioCodec AAC LC ADTS 16Khz stereo */
    AAP_AUDIO_CODEC_AAC_LC_ADTS_16KHZ_2,
    /*! AudioCodec AAC LC ADTS 44Khz mono */
    AAP_AUDIO_CODEC_AAC_LC_ADTS_44KHZ_1,
    /*! AudioCodec AAC LC ADTS 44Khz stereo */
    AAP_AUDIO_CODEC_AAC_LC_ADTS_44KHZ_2,
    /*! AudioCodec AAC LC ADTS 48Khz mono */
    AAP_AUDIO_CODEC_AAC_LC_ADTS_48KHZ_1,
    /*! AudioCodec AAC LC ADTS 48Khz stereo */
    AAP_AUDIO_CODEC_AAC_LC_ADTS_48KHZ_2,

    /*! AudioCodec PCM 16Khz mono*/
    AAP_AUDIO_CODEC_PCM_16KHZ_1,
    /*! AudioCodec PCM 16Khz stereo */
    AAP_AUDIO_CODEC_PCM_16KHZ_2,
    /*! AudioCodec PCM 44Khz mono */
    AAP_AUDIO_CODEC_PCM_44KHZ_1,
    /*! AudioCodec PCM 44Khz stereo */
    AAP_AUDIO_CODEC_PCM_44KHZ_2,
    /*! AudioCodec PCM 48Khz mono */
    AAP_AUDIO_CODEC_PCM_48KHZ_1,
    /*! AudioCodec PCM 48Khz stereo */
    AAP_AUDIO_CODEC_PCM_48KHZ_2
}AAP_AudioCodecType;

/*! \enum AAP_SubscriptionList
 * \brief Enumeration to specify the available features for subscription.
 *
 * These list refer to the applications running on the MD which provides
 * the respective data/status to the Head Unit. These data can be used by
 * the Head Unit application to display on native purpose-built UI such as
 * instrument clusters and heads-up displays.
 *
 * \note
 * Head unit Application can subscribe to these features via config XML or aap_set_extended_attributes() API and it
 * must register the respective callbacks. Refer #AAP_CallbackList
 */
typedef enum
{
    /*! Subscribe to get Music / Media status/data. */
    AAP_SUBSCRIBE_MEDIA_PLAYBACK =  0xC00,
    /*! Subscribe to get phone call status data. */
    AAP_SUBSCRIBE_PHONE,
    /*! Subscribe to get navigation status data. */
    AAP_SUBSCRIBE_NAVIGATION,
    /*! Subscribe to enable Media browsing data.
     * \note This is for future use. */
    AAP_SUBSCRIBE_MEDIA_BROWSING,
    /*! Subscribe to get notification data.
     * \note This is for future use. */
    AAP_SUBSCRIBE_NOTIFICATION,
    /*! Subscribe to get radio data like channel info, scan data etc.
     * \note This is for future use. */
    AAP_SUBSCRIBE_RADIO,
}AAP_SubscriptionList;

/*! \enum AAP_RadioType
  \brief Enumeration to specify radio types */
typedef enum
{
    /*! Type FM */
    AAP_RADIO_TYPE_FM = 0x1,
    /*! Type AM */
    AAP_RADIO_TYPE_AM
}AAP_RadioType;

/*! \struct AAP_RadioConfig
  \brief Structure to specify the radio configurations */
typedef struct
{
    /*! Type of the Radio */
    AAP_RadioType eType;
    /*! Radio start frequency*/
    AAP_INT32 iStartFreq;
    /*! Radio end frequency*/
    AAP_INT32 iEndFreq;
    /*! Spacing between channels */
    AAP_INT32 iFreqGap;
}AAP_RadioConfig;

/*! \struct AAP_NavImageInfo
  \brief Structure to specify navigation image characteristics. */
typedef struct
{
    /*! Navigation turn image icon width */
    AAP_INT32 iNavIconWidth;
    /*! Navigation turn image icon height */
    AAP_INT32 iNavIconHeight;
    /*! Navigation turn image color depth */
    AAP_INT32 iNavIconColorDepth;
}AAP_NavImageInfo;

/*! \enum AAP_NavInstrumentClusterType
 * \brief Enumeration to specify the different navigation status
 * service instrument cluster type. */
typedef enum
{
    /*! The cluster takes image and displays.
     * e.g. If the next turn is right, MD send a corresponding suitable image which can be displayed
     * on the cluster */
    AAP_NAV_INSTRUMENT_TYPE_IMAGE = 0x01,
    /*! MD send the enumeration corresponding to the event.
     * e.g. If there is a U-Turn, MD sends #AAP_NAV_NEXT_TURN_ENUM_U_TURN */
    AAP_NAV_INSTRUMENT_TYPE_ENUM
}AAP_NavInstrumentClusterType;

/*! \struct AAP_NavSubscriptionInfo
 \brief Structure to specify info when subscribing for Navigation. */
typedef struct
{
    /*! Different navigation status service instrument cluster type. */
    AAP_NavInstrumentClusterType eNavClusterType;
    /*! This is valid if eNavClusterType contains AAP_NAV_INSTRUMENT_TYPE_IMAGE */
    AAP_NavImageInfo sNavImageInfo;
    /*! Minimum interval time to get navigation status data in ms
     * \par Default: 500 */
    AAP_INT32 iNavMinIntervalMs;
}AAP_NavSubscriptionInfo;

/*! \struct AAP_RadioSubscriptionInfo
 \brief Structure to specify info when subscribing for Radio. */
typedef struct
{
    /*! Number of radio end points, Max 2 */
    AAP_UINT32 uiNumRadio;
    /*! Radio configuration: for two types of radio */
    AAP_RadioConfig *psRadioConfig[AAP_MAX_RADIO_ENDPOINTS];
}AAP_RadioSubscriptionInfo;

/*! \struct AAP_TouchPadInfo
 \brief Structure to specify configurations for the TouchPad */
typedef struct
{
    /*! Touch Pad width in pixels. This value will not be considered if TOUCHPAD is not
     * selected as one of the input method. */
    AAP_INT32 iTouchPadWidth;
    /*! Touch Pad height in pixels. This value will not be considered if TOUCHPAD is not
     * selected as one of the input method. */
    AAP_INT32 iTouchPadHeight;
    /*! Physical width of the touch pad in mm */
    AAP_INT32 iPhyTouchPadWidth;
    /*! Physical height of the touch pad in mm */
    AAP_INT32 iPhyTouchPadHeight;
    /*! To navigate UI. */
    AAP_BOOL bNavigateUi;
    /*! If bNavigateUi and this flag i.e. bAbsoluteUi set to AAP_TRUE,
     * Touchpad will map to the screen in terms of absolute coordinates when
     * navigating through the UI.
     *
     * If bNavigateUi is AAP_TRUE and this flag is AAP_FALSE,
     * Touchpad movements will be interpreted as gestures.
     *
     * If bNavigateUi is AAP_FALSE, then this flag has no effect. */
    AAP_BOOL bAbsoluteUi;
    /*! If this is AAP_TRUE, tap will work as select event. */
    AAP_BOOL bIsTapAsSelect;
    /*! To set touch pad sensitivity.
     * A number from 1 to 10 (inclusive) to configure the touchpad's sensitivity.
     * Larger numbers are more sensitive, requiring smaller inputs to trigger movement. */
    AAP_INT32 iTouchPadSenstivity;
}AAP_TouchPadInfo;

/*! \struct AAP_TouchPadSensitivity
 \brief Structure to update the Touchpad sensitivity. */
typedef struct
{
    /*! TouchPad sensitive value to be updated. */
    AAP_INT32 iTouchPadSenstivity;
}AAP_TouchPadSensitivity;

/*! \struct AAP_TouchScreenInfo
 \brief Structure to configure the TouchScreen. */
typedef struct
{
    /*! Touch screen type */
    AAP_TouchScreenType eTouchScreenType;
    /*! Set this flag to true if touch screen is secondary input */
    AAP_BOOL bIsTouchScreenSecondary;
    /*! Device path to get the touch input from the touch node directly. This is
     * strictly only for testing purpose.
     * \note In the production release, the application must provide the touch
     * input events through aap_send_touch_input() API. */
    AAP_CHAR acDevPath[AAP_MAX_INPUT_DEV_PATH];
    /*! If true, AAP stack will read the touch input from the given path and
     * report to MD.
     * \note In the production release, the application must set this to AAP_FALSE. */
    AAP_BOOL bInternal;
}AAP_TouchScreenInfo;

/*! \struct AAP_KeyInfo
 \brief Structure to configure the Key Codes */
typedef struct
{
    /*! Default number of key codes to be registered. */
    AAP_UINT32 uiNoKeyCodes;
    /*! Specify the key codes. */
    AAP_KeyCodes aeKeyCodes[AAP_MAX_NUM_KEY_CODES];
}AAP_KeyInfo;

/*! \struct AAP_ExtAttributes
 * \brief Structure to specify the configurations accepted after create session
 * but before starting a session.
 *
 * \note:
 * 1. Calling this will override the all the configuration of XML configuration.
 * 2. If AAP stack fails to set the attributes due to some invalid value, session
 * will use last valid attributes successfully set either through XML configuration
 * file or aap_set_extended_attributes() API.
 */
typedef struct
{
    /*! SSL Root certificate file content in a format supported by underlying SSL */
    AAP_BYTE aucSSLRootCert[MAX_SSL_ROOT_CERT_LEN];
    /*! Length of the Root certificate file put in #aucSSLRootCert */
    AAP_UINT32 uiSSLRootCertLen;
    /*! SSL Client certificate file content in a format supported by underlying SSL */
    AAP_BYTE aucSSLClientCert[MAX_SSL_CLIENT_CERT_LEN];
    /*! Length of the Client certificate file put in #aucSSLClientCert */
    AAP_UINT32 uiSSLClientCertLen;
    /*! SSL Client key file content in a format supported by underlying SSL */
    AAP_BYTE aucSSLClientKey[MAX_SSL_CLIENT_KEY_LEN];
    /*! Length of the Client private key file put in #aucSSLClientKey */
    AAP_UINT32 uiSSLClientKeyLen;
    /*! Head unit make :: NULL terminated string
     *  <b>Sample value:</b> "Generic" */
    AAP_CHAR acHUMake[AAP_SMALL_STRING_LEN];
    /*! Head unit model name :: NULL terminated string
     *  <b>Sample value:</b> "Generic" */
    AAP_CHAR acHUModel[AAP_SMALL_STRING_LEN];
    /*! Primary display width
     *  <b>Sample value:</b> 1024 */
    AAP_UINT32 uiDisplayWidth;
    /*! Primary display height
     *  <b>Sample value:</b> 600 */
    AAP_UINT32 uiDisplayHeight;
    /*! Default number of input devices to be registered */
    AAP_UINT32 uiNoInputDev;
    /*! Specify the supported input devices.
     * Possible combination to use:
     * 1. Only AAP_INPUT_TYPE_TOUCH_SCREEN.
     * 2. Only Rotary input which is part of AAP_INPUT_TYPE_KEY_CODES i.e. AAP_KEYCODE_ROTARY_CONTROLLER.
     * 3. Only AAP_INPUT_TYPE_TOUCH_PAD.
     * 4. AAP_INPUT_TYPE_TOUCH_SCREEN & Rotary input which is part of AAP_INPUT_TYPE_KEY_CODES i.e. AAP_KEYCODE_ROTARY_CONTROLLER.
     * 5. AAP_INPUT_TYPE_TOUCH_PAD & Rotary input which is part of AAP_INPUT_TYPE_KEY_CODES i.e. AAP_KEYCODE_ROTARY_CONTROLLER.
     * 6. AAP_INPUT_TYPE_TOUCH_SCREEN and AAP_INPUT_TYPE_TOUCH_PAD */
    AAP_InputDevType aeInputDevType[AAP_MAX_INPUT_DEVICES_TYPE];
    /*! This is valid if aeInputDevType contains AAP_INPUT_TYPE_TOUCH_SCREEN */
    AAP_TouchScreenInfo sTouchScreenInfo;
    /*! This is valid if aeInputDevType contains AAP_INPUT_TYPE_TOUCH_PAD */
    AAP_TouchPadInfo sTouchPadInfo;
    /*! This is valid if aeInputDevType contains AAP_INPUT_TYPE_KEY_CODES */
    AAP_KeyInfo sKeyInfo;
    /*! Number of valid video resolutions
     *  <b>Sample value:</b> 1 */
    AAP_UINT32 uiNumVideoReslns;
    /*! Specify the video resolution preference.
     * Provide highest resolution at the lowest index.
     * Ex: asVideoReslns[0].eResValue = AAP_VIDEO_RESOLUTION_1920x1080;
     * asVideoReslns[1].eResValue = AAP_VIDEO_RESOLUTION_1280x720;
     * asVideoReslns[2].eResValue = AAP_VIDEO_RESOLUTION_800x480;
     * <b>Sample value:</b> AAP_VIDEO_RESOLUTION_800x480 */
    AAP_VideoRes asVideoReslns[AAP_MAX_VIDEO_RESLNS];
    /*! Specify the video codec  for projection video
     *  <b>Sample value:</b> AAP_VIDEO_CODEC_H264_BP_L3_1 */
    AAP_VideoCodecType eVideoCodec;
    /*! Specify the audio codec setting for media playback
     *  <b>Sample value:</b> AAP_AUDIO_CODEC_PCM_48KHZ_2 */
    AAP_AudioCodecType eMediaCodec;
    /*! Bits per sample value of media codec
     *  <b>Sample value:</b> 16 */
    AAP_UINT32 uiMediaBps;
    /*! Device ID for media */
    AAP_CHAR acMediaDeviceID[AAP_SMALL_ARRAY_LEN];
    /*! Specify the audio codec setting for system sounds
     *  <b>Sample value:</b> AAP_AUDIO_CODEC_PCM_16KHZ_1 */
    AAP_AudioCodecType eGuidanceAudioCodec;
    /*! Bits per sample value of guidance voice
     *  <b>Sample value:</b> 16 */
    AAP_UINT32 uiGuidanceBps;
    /*! Device ID for guidance */
    AAP_CHAR acGuidanceDeviceID[AAP_SMALL_ARRAY_LEN];
    /*! Specify the audio codec setting for voice input
     *  <b>Sample value:</b> AAP_AUDIO_CODEC_PCM_16KHZ_1 */
    AAP_AudioCodecType eMicAudioCodec;
    /*! Bits per sample value of microphone input voice
     *  <b>Sample value:</b> 16 */
    AAP_UINT32 uiMicBps;
    /*! Device ID for microphone */
    AAP_CHAR acMicDeviceID[AAP_SMALL_ARRAY_LEN];
    /*! Number of subscribed features
     *  <b>Sample value:</b> 0 */
    AAP_UINT32 uiNoSubscription;
    /*! Application subscribed features for status */
    AAP_SubscriptionList aeSubscriptionList[AAP_SUBSCRIPTION_LIST_LEN];
    /*! This is valid if aeSubscriptionList contains AAP_SUBSCRIBE_NAVIGATION */
    AAP_NavSubscriptionInfo sNavSubscriptionInfo;
    /*! This is valid if aeSubscriptionList contains AAP_SUBSCRIBE_RADIO.
     * \note This is for future use. */
    AAP_RadioSubscriptionInfo sRadioSubscriptionInfo;
    /*! Specify info of all the VEC services to be registered
     *  <b>Ex:</b> To register a service with name "com.example.xyz" and an app
     *  namely "com.example.echovendor", following shall be done:\n
     *  - Assign "com.example.xyz" to sVecInfo.asVecServices[0].acServiceName,
     *  - Assign sVecInfo.asVecServices[0].uiNumApps = 1,
     *  - Assign "com.example.echovendor" to sVecInfo.asVecServices[0].acApps[0] */
    AAP_VECInfo sVECInfo;
}AAP_ExtAttributes;

/*! \struct AAP_VehicleData
 * \brief Structure to specify the vehicle data.
 *
 * Below table lists the data structure to be sent based on sensor type.
 * The Min Frequency column represents the minimum frequency at which the sensor data
 * has to be provided.
 *
 * <table border="2">
 *       <tr bgcolor="#6fb2ff">
 *           <th>Sensor Type (For eType)</th>
 *           <th>Data Structure (For pvData)</th>
 *           <th>Min Frequency</th>
 *           <th>Required</th>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_LOCATION</td>
 *           <td>AAP_LocationData</td>
 *           <td>Use the same update rate as the underlying\n GPS hardware</td>
 *           <td>Required if this sensor is present</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_COMPASS</td>
 *           <td>AAP_CompassData</td>
 *           <td>10 hz</td>
 *           <td>Required if this sensor is present</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_SPEED</td>
 *           <td>AAP_SpeedData</td>
 *           <td>10 hz</td>
 *           <td>Required if this sensor is present</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_RPM</td>
 *           <td>AAP_RpmData</td>
 *           <td>10 hz</td>
 *           <td>Optional</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_ODOMETER</td>
 *           <td>AAP_OdometerData</td>
 *           <td>On change</td>
 *           <td>Optional</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_FUEL</td>
 *           <td>AAP_FuelData</td>
 *           <td>On change</td>
 *           <td>Optional</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_PARKING_BRAKE</td>
 *           <td>AAP_ParkingBrakeData</td>
 *           <td>On change</td>
 *           <td>Optional</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_GEAR</td>
 *           <td>AAP_GearData</td>
 *           <td>On change</td>
 *           <td>Optional</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_OBDII_DIAGNOSTIC_CODE</td>
 *           <td>Send Raw Data</td>
 *           <td>NA</td>
 *           <td>Optional</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_NIGHT_MODE</td>
 *           <td>AAP_NightModeData</td>
 *           <td>On change</td>
 *           <td>Required</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_ENVIRONMENT_DATA</td>
 *           <td>AAP_EnvData</td>
 *           <td>0.1 hz</td>
 *           <td>Optional</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_HVAC_DATA</td>
 *           <td>AAP_HVACData</td>
 *           <td>NA</td>
 *           <td>Optional</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_DRIVING_STATUS_DATA</td>
 *           <td>AAP_DrivingStatusData</td>
 *           <td>On change</td>
 *           <td>Required</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_DEAD_RECKONING_DATA</td>
 *           <td>AAP_DeadReckData</td>
 *           <td>NA</td>
 *           <td>Optional</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_PASSENGER_DATA</td>
 *           <td>AAP_PassengerData</td>
 *           <td>On change</td>
 *           <td>Optional</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_DOOR_DATA</td>
 *           <td>AAP_DoorData</td>
 *           <td>On change</td>
 *           <td>Optional</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_LIGHT_DATA</td>
 *           <td>AAP_LightData</td>
 *           <td>On change</td>
 *           <td>Optional</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_TIRE_PRESSURE_DATA</td>
 *           <td>AAP_TirePressureData</td>
 *           <td>On change</td>
 *           <td>Optional</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_ACCELEROMETER_DATA</td>
 *           <td>AAP_AcceleroMeterData</td>
 *           <td>10hz</td>
 *           <td>Required if this sensor is present</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_GYROSCOPE_DATA</td>
 *           <td>AAP_GyroData</td>
 *           <td>10hz</td>
 *           <td>Required if this sensor is present</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_GPS_SATELLITE_DATA</td>
 *           <td>AAP_GpsSateliteData</td>
 *           <td>Use the same update rate as the underlying\n GPS hardware</td>
 *           <td>Required if this sensor is present</td>
 *       </tr>
 *       <tr>
 *           <td>#AAP_SENSOR_TOLL_CARD_DATA</td>
 *           <td>AAP_TollCardData</td>
 *           <td>On change</td>
 *           <td>Optional</td>
 *       </tr>
 * </table>
 * \note
 * If the application wants to send raw data to phone without being interpreted,
 * it should send #AAP_SENSOR_OBDII_DIAGNOSTIC_CODE as sensor type and pass
 * the raw data and the size of data as pvData and uiDataSize respectively.
 */
typedef struct
{
    /*! Type of the sensor source */
    AAP_SensorType eType;
    /*! Pointer to vehicle data, corresponding data depends on the source type.\n
     * Refer the above table. */
    AAP_VOID *pvData;
    /*! Length of the pvData in bytes */
    AAP_UINT32 uiDataSize;
}AAP_VehicleData;

/*! \struct AAP_ScreenInfo
 * \brief This structure contains information to setup video player.
 *
 * If application doesn't want to use this structure, it must be memset to 0x0.
 */
typedef struct
{
    /*! This variable is used to pass the surface window ID which is passed to video player \n
     * so that video player can pass the buffer to the same window. If this \n
     * variable is not being used, it must be assigned with 0x0. In this case \n
     * frame buffer will be shown on the default window by video player. */
    AAP_UINT64 ulWindowId;
}AAP_ScreenInfo;

/*! \struct AAP_PlatInfo
 * \brief This is platform specific information for the underlying OS/platform
 * which is needed during start of the AAP session.
 *
 * This information is passed to platform specific modules like Audio and Video (Screen) module. \n
 * For example, application may want to pass window ID of it's screen.\n
 * If this structure is not getting used, it must be memset to 0x0.
 */
typedef struct
{
    /*! This structure will be used by video player module. */
    AAP_ScreenInfo sScreenInfo;
    /*! Through this variable application can pass the extra information but the purpose/usage of information has \n
     * to be known by corresponding platform modules before hand. For the time being this is reserved. */
    AAP_VOID *pvExtInfo;
    /*! Length of the extra info buffer (pvExtInfo) */
    AAP_UINT32 uiExtInfoLength;
}AAP_PlatInfo;

/*! \struct AAP_StartInfo
 *  \brief Structure to specify the information for staring AAP session.
 */
typedef struct
{
    /*! This structure is needed by platform specific modules like Audio, Video. For more details refer to this \n
     * structure. If this platform information is not being used by application, it must be memset to 0x0 \n
     */
    AAP_PlatInfo sPlatInfo;
    /*! This is for automatic video projection start when the start session is called.
     * If this variable is false, video projection doesn't start. Later application must
     * send video focus to start the video projection.
     */
    AAP_BOOL bAutoVideoStart;
    /*! This is for automatic audio start (It may require to grant the corresponding
     * audio focus state.)
     * \note This variable is reserved for future.
     */
    AAP_BOOL bAutoAudioStart;
    /*! SDK will start AAP session for this device.
     * \note Application has to pass required structure based on device type
     */
    AAP_DeviceInfo sDevice;
    /*! Additional configuration parameter to configure AAP stack.
     */
    AAP_ConfigParams sConfigParams;
    /*! This flag indicates that this AAP session is only to
     * probe whether the connected device supports AAP or not */
    AAP_BOOL bIsSessionToProbe;
}AAP_StartInfo;

/*! \enum AAP_IconType
 * \brief Enumeration to specify the type of icon
 */
typedef enum
{
    /*! Invalid image */
    AAP_SESSION_ICON_TYPE_NONE = 0x00,
    /*! 32x32 png image */
    AAP_SESSION_ICON_TYPE_PNG_SMALL,
    /*! 64x64 png image */
    AAP_SESSION_ICON_TYPE_PNG_MEDIUM,
    /*! 128x128 png image */
    AAP_SESSION_ICON_TYPE_PNG_LARGE
}AAP_IconType;

/*! \enum AAP_WifiSecurityMode
 * \brief Enumeration to specify the encryption type of the HU's access point
 */
typedef enum
{
    /*! WiFi security mode is OPEN */
    AAP_WSM_OPEN = 0x1,
    /*! WiFi security mode is WEP_64 */
    AAP_WSM_WEP_64,
    /*! WiFi security mode is WEP_128 */
    AAP_WSM_WEP_128,
    /*! WiFi security mode is WPA_PERSONAL */
    AAP_WSM_WPA_PERSONAL,
    /*! WiFi security mode is WPA2_PERSONAL */
    AAP_WSM_WPA2_PERSONAL,
    /*! WiFi security mode is WPA_WPA2_PERSONAL */
    AAP_WSM_WPA_WPA2_PERSONAL,
    /*! WiFi security mode is WPA_ENTERPRISE */
    AAP_WSM_WPA_ENTERPRISE,
    /*! WiFi security mode is WPA2_ENTERPRISE */
    AAP_WSM_WPA2_ENTERPRISE,
    /*! WiFi security mode is WPA_WPA2_ENTERPRISE */
    AAP_WSM_WPA_WPA2_ENTERPRISE
}AAP_WifiSecurityMode;

/*! \struct AAP_WifiInfo
 * \brief Structure to specify wifi credentials
 */
typedef struct
{
    /*! This is to store HU's WiFi AP IP address. */
    AAP_CHAR acWifiApIpAddr[AAP_SMALL_ARRAY_LEN];
    /*! This is to store HU's WiFi AP port number */
    AAP_UINT32 uiWifiApPortNo;
    /*! This is to store HU's WiFi BSSID or MAC ID. Keeping this blank will not
     * register wifi projection endpoint. */
    AAP_CHAR acWifiBSSID[AAP_SMALL_ARRAY_LEN];
    /*! This is to store HU's WiFi SSID. Keeping this blank will not register
     * wifi projection endpoint. */
    AAP_CHAR acWifiSSID[AAP_SMALL_ARRAY_LEN];
    /*! This is to store HU's WiFi password */
    AAP_CHAR acWifiPwd[AAP_DEFAULT_STRING_LEN];
    /*! This is to store HU's WiFi security mode or encryption type */
    AAP_WifiSecurityMode eWifiSecurityMode;
    /*! Number of Wifi frequency channels to register to MD (min: 1).
     * These many channels will be read from #auiWifiChannels array */
    AAP_UINT32 uiNumChannels;
    /*! This is to store a list of WiFi channels supported by HU.
     * Ex: To set one supported frequency channel(say, 36), uiNumChannels = 1 and
     * auiWifiChannels[0] = 36 */
    AAP_UINT32 auiWifiChannels[AAP_MAX_WIFI_CHANNELS];
}AAP_WifiInfo;

/*! \struct AAP_SessionInfo
  * \brief Structure to specify session info
  *
  */
typedef struct
{
    /*! Current session status */
    AAP_SessionStatus eCurStatus;
    /*! Status of the session\n
     * On error cases this will point to specific error codes.
     *
     * Following status can come when eCurStatus is #AAP_SESSION_STATE_CONNECTED:\n
     * #AAP_SUCCESS, When AAP session is established successfully.\n
     * #AAP_DEVICE_SWITCH_SUCCESS, When AAP session is switched to the intended device based on user selection.\n
     * #AAP_DEVICE_SWITCH_FAILED, When AAP session has failed to switch to the intended device but
     * continuing AAP session with the previous device.
     *
     * Following status can come when eCurStatus is #AAP_SESSION_STATE_DISCONNECTED:\n
     * #AAP_ERR_MD_STOPPED, When MD is not responding.\n
     * #AAP_ERR_TRANS_READ_WRITE, If read write communication error has happened with device.\n
     * #AAP_BYEBYE_REASON_USER_INITIATED_EXIT, If user selected to exit.\n
     * #AAP_BYEBYE_REASON_AAP_UNSUPPORTED_DEV, If the device doesn't support AAP.\n
     * #AAP_BYEBYE_REASON_NOT_CURRENTLY_SUPPORTED, If the device currently doesn't support AAP.\n
     * #AAP_BYEBYE_REASON_AAP_SUPPORTED_DEV, If the device supports AAP.\n
     * #AAP_BYEBYE_REASON_AAP_DEVICE_SWITCH, If MD wants to disconnect due to Device switch.\n
     * #AAP_ERR_SSL_AUTH_FAILURE, In case of generic authentication failure.\n
     * #AAP_ERR_SSL_AUTH_FAILURE_CERT_NOT_YET_VALID, In case of SSL certificates are not yet valid.\n
     * #AAP_ERR_SSL_AUTH_FAILURE_CERT_EXPIRED, In case of SSL certificates are expired.\n
     * #AAP_ERR_FRAMING, In case of I/O operation error or SSL decryption error.\n
     * #AAP_ERR_UNKNOWN, In case of MD shutted down the connection for unknown reason. \n
     * #AAP_ERR_AAP_HAS_STOPPED, When AAP connection has some problem.
     *
     * Following status can come when eCurStatus is #AAP_SESSION_STATE_INVALID:\n
     * #AAP_SUCCESS, When #aap_stop_session() is called.\n
     * #AAP_ERR_DEV_NOT_IN_AOA, When #aap_start_session() is called with a non
     * AOA device.\n
     * #AAP_ERR_NO_TCP_CONNECTION, When #aap_start_session() is called with a
     * device for which TCP connection is not received from MD.\n
     * #AAP_DEVICE_SWITCH_FAILED, When AAP session has failed to switch to the intended device.
     * In this case previous AAP session is disconnected and starting AAP session with intended device has also failed.\n
     * #AAP_FAILURE, Generic error when #aap_start_session() is unable to start AAP session.\n
     * */
    AAP_RetType iStatus;
    /*! Type of the icon.
     * Access only if eCurStatus is #AAP_SESSION_STATE_CONNECTED and iStatus is #AAP_SUCCESS or #AAP_DEVICE_SWITCH_SUCCESS */
    AAP_IconType eIconType;
    /*! Length of the image buffer.
     * Access only if eCurStatus is #AAP_SESSION_STATE_CONNECTED and iStatus is #AAP_SUCCESS or #AAP_DEVICE_SWITCH_SUCCESS */
    AAP_UINT32 uiIconLen;
    /*! Image data.
     * Access only if eCurStatus is #AAP_SESSION_STATE_CONNECTED and iStatus is #AAP_SUCCESS or #AAP_DEVICE_SWITCH_SUCCESS */
    AAP_BYTE aucIconBuffer[AAP_LARGE_ARRAY_LEN];
    /*! Description or label string, NULL terminated string
     * Access only if eCurStatus is #AAP_SESSION_STATE_CONNECTED and iStatus is #AAP_SUCCESS or #AAP_DEVICE_SWITCH_SUCCESS */
    AAP_CHAR acDescription[AAP_DEFAULT_STRING_LEN];
    /*! Device name is string data, NULL terminated string.
     * Access only if eCurStatus is #AAP_SESSION_STATE_CONNECTED and iStatus is #AAP_SUCCESS or #AAP_DEVICE_SWITCH_SUCCESS */
    AAP_CHAR acDeviceName[AAP_DEFAULT_STRING_LEN];
}AAP_SessionInfo;

/*! \struct AAP_BtPairReqEvent
 * \brief Defines the Bluetooth pairing request event.
 */
typedef struct
{
    /*! BT MAC address of Mobile device. HU can use this MAC ID of phone to
     * check if it was already paired or not. */
    AAP_CHAR acPhoneMAC[AAP_DEFAULT_STRING_LEN];
    /*! Pairing method that the mobile will be using to pair.\n
     * This will be either #AAP_BT_PAIRING_NUMERIC or #AAP_BT_PAIRING_PIN. */
    AAP_INT32 iPairingMethod;
}AAP_BtPairReqEvent;

/*! \enum AAP_BtAuthStatus
 *  \brief Enumeration to specify the Bluetooth pairing authentication status.
 */
typedef enum
{
    /*! If Authentication Data was invalid */
    AAP_BT_AUTH_INVALID = 0,
    /*! If Authentication Data was a mismatch */
    AAP_BT_AUTH_MISMATCH,
    /*! If Authentication Data sent was correct */
    AAP_BT_AUTH_SUCCESS
}AAP_BtAuthStatus;

/*! \struct AAP_BtAuthStatusEvent
 * \brief Defines the Bluetooth authentication status.
 */
typedef struct
{
    /*! Authentication Status to make sure HU has paired with correct mobile device */
    AAP_BtAuthStatus eBtAuthStatus;
}AAP_BtAuthStatusEvent;

/*! \enum AAP_UpdateInfoType
 *  \brief Enumeration to specify the different fields that can be updated
 *  dynamically.
 */
typedef enum
{
    /*! This is for setting up TCP server or restarting TCP server due to
     * change in HU's WIFI Access point info */
    AAP_UPDATE_TCP_SERVER = 1
} AAP_UpdateInfoType;

/*! \struct AAP_UpdateInfo
 * \brief This structure contains data that can be used to update different
 * fields(ex: Update TCP server) during the session dynamically.
 * For each update info type user needs to fill the corresponding structure.
 */
typedef struct
{
    /*! Update info type */
    AAP_UpdateInfoType eUpdateInfoType;
    /*! Union to fill based on #AAP_UpdateInfoType */
    union
    {
        /*! This structure should be accessed only when #AAP_UpdateInfoType is
         * set to #AAP_UPDATE_TCP_SERVER */
        AAP_WifiInfo sWifiInfo;
    };
} AAP_UpdateInfo;

/*!
 * \typedef AAP_RetType (*AAP_OnErrorCb) (AAP_VOID *pvUserData,
                                AAP_RetType iErrorCode, AAP_CHAR *pcDescription);
 * \brief Application should implement this to receive the error messages from  AAP SDK.
 *
 * \param pvUserData [in]   Application context info
 * \param iErrorCode [in]   Error code
 * \param pcDescription [in] Description of the error, can be NULL
 * \note
 * On receiving this error callback, depending on the error code, application must restart the session.
 *
 */
typedef AAP_RetType (*AAP_OnErrorCb) (AAP_VOID *pvUserData,
                                AAP_RetType iErrorCode, AAP_CHAR *pcDescription);

/*! \typedef AAP_RetType (*AAP_SessionStatusCb) (AAP_VOID*pvUserData,
 *                        AAP_SessionInfo *psSessionInfo);
  *  \brief Session status will be received on this callback.
  *
  *  This will provide the session events and associated data (e.g.Icon, Label)\n
  *  This callback is called from the stack only after #aap_start_session( ) is called.\n
  *  Application can use this status to update the UI elements.\n
  *
  *  \note If the current session status i.e psSessionInfo->eCurStatus is
  *  #AAP_SESSION_STATE_DISCONNECTED for whatsoever reason,\n
  *  application must stop the session by calling #aap_stop_session( ).
  *
  * \param pvUserData [in]  application context info
  * \param psSessionInfo [in] Session info associated with the session event
  */
typedef AAP_RetType (*AAP_SessionStatusCb) (AAP_VOID*pvUserData,
        AAP_SessionInfo *psSessionInfo);

 /*! \typedef AAP_RetType (*AAP_NotificationCb) (AAP_VOID *pvUserData,
                                AAP_UCHAR *pucNotifictionText, AAP_UINT32 uiLen);
  *  \brief Application will receives the notification text send by the MD during
  *  active AAP session on this callback.
  *
  * \note This is reserved for future use.
  *
  * \param pvUserData [in]  application context info
  * \param pucNotifictionText [in]  Notification text
  * \param uiLen [in]   Length of the notification text
  */
typedef AAP_RetType (*AAP_NotificationCb) (AAP_VOID *pvUserData,
                                AAP_UCHAR *pucNotifictionText, AAP_UINT32 uiLen);

 /*! \typedef AAP_RetType (*AAP_BTPairingRequestCb) (AAP_VOID *pvUserData,
        AAP_BtPairReqEvent *psBtPairEvent);
  * \brief During AAP session establishment, MD will initiate BT pairing request
  * that will be received in this callback.
  *
  * Once receiving this, the head unit must make itself prepared for Bluetooth pairing
  * which will be initiated by the phone. To be ready for pairing, the head unit
  * must disconnect all the other HFP (Hands-Free Profile) connections if it
  * supports only one HFP connection, and set the AAP connected phone's priority
  * as the highest and make the car's Bluetooth module discoverable to the phone.
  *
  * When the head unit is ready to be paired, it must call #aap_bt_ready_to_pair,
  * then the phone will initiate the Bluetooth pairing-and-connection process with
  * the head unit. In this process, pairing step will be skipped if both the
  * phone and the car has link key (pairing information)for each other.
  * In that case the phone will initiate HFP (Hands-Free Profile) connection only.
  *
  * \note The HU must handle the following edge cases during pairing
  * - <b>Head unit is engaged in a HFP call with an other mobile device:</b>
  *   The HU MUST NOT disconnect this HFP connection. Once the call ends, application
  *   must call #aap_bt_ready_to_pair.
  * - <b>Non-AAP mobile device attempts to pair:</b>
  *   The HU must allow pairing with the AAP connected MD but can choose to
  *   allow or disallow pairing with other MDs.
  * - <b>Bluetooth disabled on head unit:</b>
  *   When this callback comes, HU must enable Bluetooth and pair with MD.
  * - HU must be able to handle multiple #AAP_BTPairingRequestCb callback in the
  *   same AAP connection.
  * - HU must allow the HFP connection from the MD. If the HFP connection process
  *   is already in progress before a user plugs in a phone to start AAP, the HU
  *   MUST continue the HFP connection process.
  * - If an HU can support only one HFP connection, it MUST NOT connect any other
  *   HFP devices while AAP is active.
  * - If the MD is already connected via HFP to the HU and on a call when the AAP
  *   connection process is initiated, no further pairing or HFP connection is
  *   required, but the HU MUST allow the AAP connection to proceed without waiting
  *   for the call to end.
  * - When the MD is already on a non Bluetooth call, the Bluetooth pairing and
  *   HFP connection process proceeds as normal.
  * - If the MD is already connected via HFP to a different HFP device than the
  *   HU and on a call when the AAP connection process is initiated, the MD will
  *   disconnect from the other HFP device and initiate pairing and connection to the HU.
  * - If the MD is connected to an Advanced Audio Distribution Profile (A2DP)
  *   device (including the HU) when connecting AAP, the MD leaves the A2DP
  *   connection intact. However, the HU MUST disconnect A2DP if an AAP session
  *   is started on a device connected via A2DP.
  * - On receiving this callback it must call #aap_bt_ready_to_pair even if the
  *   HU is already paired with the MD.
  *
  * \param pvUserData [in]  Application context info.
  * \param psBtPairEvent [in]  BT pairing event. Refer #AAP_BtPairReqEvent
  */
typedef AAP_RetType (*AAP_BTPairingRequestCb) (AAP_VOID *pvUserData,
        AAP_BtPairReqEvent *psBtPairEvent);

/*! \typedef AAP_RetType (*AAP_BTAuthStatusCb) (AAP_VOID *pvUserData,
        AAP_BtAuthStatusEvent *psBtAuthStatus);
  * \brief During/after AAP session establishment, MD will authenticate that HU has
  * paired with correct MD or not. The authentication status will be
  * received in this callback.
  *
  * \param pvUserData [in]  Application context info.
  * \param psBtAuthStatus [in]  BT authentication status event.
  * Refer #AAP_BtAuthStatusEvent.
  */
typedef AAP_RetType (*AAP_BTAuthStatusCb) (AAP_VOID *pvUserData,
        AAP_BtAuthStatusEvent *psBtAuthStatus);

 /*! \typedef AAP_RetType (*AAP_MediaBrowserCb) (AAP_VOID *pvUserData,
        AAP_MediaData *psMediaData);
  * \brief Media browsing responses will be received on this callback.
  *
  * Application will receive the browsing information (#AAP_MediaData) and
  * associated event through this callback.
  *
  * \note This is reserved for future use.
  *
  * \param pvUserData [in]  Application context info
  * \param psMediaData [in] Media data which includes event type and
  * corresponding media data
  */
typedef AAP_RetType (*AAP_MediaBrowserCb) (AAP_VOID *pvUserData,
        AAP_MediaData *psMediaData);

/*! \typedef AAP_RetType (*AAP_MediaPlaybackStatusCb) (AAP_VOID *pvUserData,
        AAP_MediaPlayBackStatus *psMediaPlayBackStatus);
  * \brief This callback will provide the playback status of the currently playing song.
  *
  * Application can use this data to enable tighter integration with native
  * purpose-built UI such as instrument clusters and heads-up displays.
  *
  * The MD continually sends status notifications whenever media is playing.
  *
  * \note Application has to subscribe to Media Playback status via config XML file.
  *
  * \param pvUserData [in]  Application context info
  * \param psMediaPlayBackStatus [in] Structure contains the playback status.
  *                                   Refer #AAP_MediaPlayBackStatus for details.
  */
typedef AAP_RetType (*AAP_MediaPlaybackStatusCb) (AAP_VOID *pvUserData,
        AAP_MediaPlayBackStatus *psMediaPlayBackStatus);

 /*! \typedef AAP_RetType (*AAP_ProjectionStatusCb) (AAP_VOID *pvUserData,
                            AAP_ProjectionEventType eEvent, AAP_ProjectionData unProjData);
  * \brief Projection status will be received on this callback.
  *
  * This callback will be asynchronously called when there is a change in the projection state.
  *
  * This callback information can be used for First Run Experience(FRX).
  * Start a timer of 3 seconds when #AAP_SESSION_STATE_CONNECTED event comes.
  * If the timer expires and this callback has not been called for eEvent == AAP_PROJECTION_SETUP,
  * then it is First Run Experience.
  *
  * \param pvUserData [in]  Application context info
  * \param eEvent [in]      Projection event
  * \param unProjData [in]  This contains data of corresponding projection event if any.
  */
typedef AAP_RetType (*AAP_ProjectionStatusCb) (AAP_VOID *pvUserData,
        AAP_ProjectionEventType eEvent, AAP_ProjectionData unProjData);

/*! \typedef AAP_RetType (*AAP_AudioStateCb) (AAP_VOID *pvUserData,
        AAP_StreamType eType, AAP_AudioState eState);
  * \brief Audio playback/recording state will be received through this callback.
  *
  * This callback will be asynchronously called when there is a change in
  * playback/recording state. For an example if media data is about to come from MD,
  * #AAP_StreamType will be #AAP_AUDIO_STREAM_MEDIA and #AAP_AudioState will be
  * #AAP_AUDIO_STATE_START. On receiving this callback, application must call
  * #aap_audio_setup() API for audio playback after taking the intended course of action (this
  * could be setting the device ID, preparing the device etc.). If the application
  * doesn't reply, stack assumes that application is not interested
  * in the playback and the audio frames will be dropped. In this case stack
  * doesn't change the playback state.
  *
  * \note
  * - This callback is only valid for stream type #AAP_AUDIO_STREAM_MEDIA, #AAP_AUDIO_STREAM_GUIDANCE.\n
  * - When this callback comes for #AAP_AUDIO_STREAM_MICROPHONE as #AAP_StreamType,
  *   it is just a notification about the VR state i.e. start or stop.
  *   No need to call #aap_audio_setup() API for this stream.
  *   When #AAP_AUDIO_STREAM_MICROPHONE as #AAP_StreamType and #AAP_AUDIO_STATE_START
  *   as #AAP_AudioState, HU must stop/mute the all native audio sources (except safty critical messages).
  *   When #AAP_AUDIO_STREAM_MICROPHONE as #AAP_StreamType and #AAP_AUDIO_STATE_STOP
  *   as #AAP_AudioState, HU must resume/unmute the all native audio sources if anything stopped/muted.
  * - If application doesn't register this callback, playback wouldn't happen.\n
  * - Due to GAL receiver limitation stack can't cancel the playback.\n
  *
  * \param pvUserData [in]  Application context info
  * \param eType [in]       Audio stream type
  * \param eState [in]      Playback/recording state
  */
typedef AAP_RetType (*AAP_AudioStateCb) (AAP_VOID *pvUserData,
        AAP_StreamType eType, AAP_AudioState eState);

/*! \typedef AAP_RetType (*AAP_StreamRequestCb) (AAP_VOID *pvUserData,
                                AAP_StreamType eType, AAP_StreamRequest eRequest);
  *  \brief Stream focus request from the MD will be received to this callback.
  *
  *  MD will request for a stream and the application MUST either grant or reject it
  *  through #aap_send_stream_focus_state( ) API. Here the parameter bUnsolicited will be AAP_FALSE
  *  because it is a solicited reply.
  *
  *  \note
  *  - If the stream type is audio, then the application has to grant it within 500ms.\n
  *  For other streams there is no restriction. Application can grant whenever it wants to.
  *
  *  - If the audio focus request indicates ducking is allowed (i.e. eRequest == AAP_AUDIO_STREAM_FOCUS_REQ_GAIN_TRANSIENT_MAY_DUCK),
  *  the HU MUST duck audio on native media and mix in transient audio from the MD.
  *
  * \param pvUserData [in] Application context info
  * \param eType      [in] Stream type
  * \param eRequest   [in] Request type
  */
typedef AAP_RetType (*AAP_StreamRequestCb) (AAP_VOID *pvUserData,
                                AAP_StreamType eType, AAP_StreamRequest eRequest);

/*! \typedef AAP_RetType (*AAP_PhoneStatusCb) (AAP_VOID *pvUserData,
                                AAP_PhoneStatus *psPhoneStatus);
  * \brief This callback will provide the current phone call status.
  *
  * Application can use this data to display on the instrument clusters or heads-up displays.
  *
  * \note Application has to subscribe to Phone status status via config XML file.
  *
  * \param pvUserData [in]      Application context info
  * \param psPhoneStatus [in]   Phone call status and other info. Refer #AAP_PhoneStatus
 */
typedef AAP_RetType (*AAP_PhoneStatusCb) (AAP_VOID *pvUserData,
                                AAP_PhoneStatus *psPhoneStatus);

/*! \typedef AAP_RetType (*AAP_BugReportReqCb) (AAP_VOID *pvUserData,
                                AAP_INT64 liTimestamp);
  * \brief This callback will provide the bug report req.
  *
  * \param pvUserData [in]   Application context info
  * \param liTimestamp [in]  Timestamp for bugreport request from phone.
 */
typedef AAP_RetType (*AAP_BugReportReqCb) (AAP_VOID *pvUserData,
        AAP_INT64 liTimestamp);

/*! \typedef AAP_RetType (*AAP_BatteryStatusCb) (AAP_VOID *pvUserData,
                                AAP_BatteryStatus *psBatteryStatus);
  * \brief This callback will provide the battery status of MD.
  *
  * \param pvUserData [in]       Application context info
  * \param psBatteryStatus [in]  Battery status of phone. Refer #AAP_BatteryStatus
 */
typedef AAP_RetType (*AAP_BatteryStatusCb) (AAP_VOID *pvUserData,
        AAP_BatteryStatus *psBatteryStatus);

/*! \typedef AAP_RetType (*AAP_CarConnectedDevReqCb) (AAP_VOID *pvUserData);
  * \brief This callback is to notify the application for listing the AAP supported connected
  * devices at that point of time. After getting this callback, HU must provide AAP supported
  * devices list using #aap_supported_device_list() API.
  *
  * \param pvUserData [in]       Application context info
 */
typedef AAP_RetType (*AAP_CarConnectedDevReqCb) (AAP_VOID *pvUserData);

/*! \typedef AAP_RetType (*AAP_PrepareDevForSwitchCb) (AAP_VOID *pvUserData,
                    AAP_DeviceInfo *psDeviceInfo);
  * \brief This callback will provide the device information to which user wants to switch.
  *
  * \param pvUserData [in]       Application context info
  * \param psDeviceInfo [in]     Device info to which user wants to switch. Refer #AAP_DeviceInfo
 */
typedef AAP_RetType (*AAP_PrepareDevForSwitchCb) (AAP_VOID *pvUserData,
        AAP_DeviceInfo *psDeviceInfo);

/*! \typedef AAP_RetType (*AAP_VECEndPointCb) (AAP_VOID *pvUserData,
                    AAP_UCHAR *psRawData, AAP_UINT32 uiLen);
  *  \brief VEC specific data will be received on this callback
  *
  *  \note psRawData will be freed once the callback controls come back from
  *  application.  Application must not hold that buffer pointer/use it.
  *  Application has to manage its own buffer.
  *
  * \param pvUserData [in] Application context info
  * \param psRawData  [in] Data received from the other end (MD).
  * \param uiLen      [in] Length of the data
 */
typedef AAP_RetType (*AAP_VECEndPointCb) (AAP_VOID *pvUserData,
                    AAP_UCHAR *psRawData, AAP_UINT32 uiLen);


/*! \typedef AAP_RetType (*AAP_NativeAppCb) (AAP_VOID *pvUserData,
                    AAP_UCHAR *psRaw, AAP_UINT32 uiLen);
  *  \brief Native application specific event / data will be received on this callback
  *
  *  Through this MD will control the native HU application.
  *
  *  \note This is reserved for future use.
  *
  * \param pvUserData [in] Application context info
  * \param psRaw [in]     Data received from the other end (MD).
  * \param uiLen [in]     Length of the data
 */
typedef AAP_RetType (*AAP_NativeAppCb) (AAP_VOID *pvUserData,
                    AAP_UCHAR *psRaw, AAP_UINT32 uiLen);

/*! \typedef AAP_RetType (*AAP_NavStatusCb) (AAP_VOID *pvUserData,
                    AAP_NavigationStatus *psNavStatus);
  *  \brief This callback is used to deliver navigation information like status,
  *  image of next turn, distance etc.
  *
  *  Use this data to display on cluster display.
  *
  *  \note Application has to subscribe to Navigation status via config XML file.
  *
  * \param pvUserData [in]  Application context info
  * \param psNavStatus [in] Navigation status data structure
  *
  * \par Sequence diagrams:
  * \ref diag13 "Navigation status"
  * \par Example Code:
  * \ref code3 "Navigation status"
 */
typedef AAP_RetType (*AAP_NavStatusCb) (AAP_VOID *pvUserData,
                    AAP_NavigationStatus *psNavStatus);


/*! \struct AAP_CallbackList
  * \brief Structure to specify the list of function pointers to be implemented and filled by application to
  * get callback events / messages from AAP SDK
  *
  * \warning
  * Application must not block or perform any computationally intensive operations
  * in the callback functions, else the AAP SDK stack may get stuck. Any such operations must
  * be performed in a separate application thread and return from the callback thread immediately.
  *
  * For a basic AAP setup, at least \n AAP_SessionStatusCb, AAP_StreamRequestCb, AAP_ProjectionStatusCb,
  * AAP_AudioStateCb \n callbacks must be implemented and registered by the application to start with AAP.\n
  * Rest of the callbacks are implementation dependent and can be enabled based
  * on the application use-case.\n
  *
  * \ref code0 "Example Code"\n
  *
 */
typedef struct
{
    /*!
     * \brief
     * Callback to be implemented for receiving error messages from AAP SDK.
     */
    AAP_OnErrorCb fpErrorCb;

    /*!
     * \brief
     * Callback to be implemented for receiving the session events and associated data (e.g.Icon, Label)\n
     *  This also provides the error status with error codes.
     */
    AAP_SessionStatusCb fpSessionCb;

    /*!
     * \brief
     * Callback to be implemented for receiving stream focus requests from MD.
     */
    AAP_StreamRequestCb fpStreamReqCb;

    /*!
     * \brief
     * Callback to be implemented for receiving the projection status event (#AAP_ProjectionEventType).
     */
    AAP_ProjectionStatusCb fpProjectionCb;

    /*!
     * \brief
     * Callback to be implemented for receiving the audio playback/recording state event (#AAP_AudioState).
     */
    AAP_AudioStateCb fpAudioStateCb;

    /*!
     * \brief
     * Callback to be implemented for receiving BT pairing request
     */
    AAP_BTPairingRequestCb fpBTpairingCb;

    /*!
     * \brief
     * Callback to be implemented for receiving BT authentication status
     */
    AAP_BTAuthStatusCb fpBTAuthStatusCb;

    /*!
     * \brief
     * Callback to be implemented for receiving the browsing and associated events
     */
    AAP_MediaBrowserCb fpMediaBrowserCb;

    /*!
     * \brief
     * Callback to be implemented for receiving the playback status of a song when it is playing.
     */
    AAP_MediaPlaybackStatusCb fpMediaPlaybackStatusCb;

    /*!
     * \brief
     * Callback to be implemented for receiving the on going phone call status information.
     */
    AAP_PhoneStatusCb fpPhoneStatusCb;

    /*!
     * \brief
     * Callback to be implemented for receiving navigation status data
     */
    AAP_NavStatusCb fpNavStatusCb;

    /*!
     * \brief
     * Callback to be implemented for receiving the notification text send by the MD during AAP session.
     */
    AAP_NotificationCb fpNotificationCb;

    /*!
     * \brief
     * Callback to be implemented for receiving VEC data / event
     */
    AAP_VECEndPointCb fpVECCb;

    /*!
     * \brief
     * Callback to be implemented for receiving native application related event / data
     */
    AAP_NativeAppCb fpNativeAppCb;

    /*!
     * \brief
     * Callback to be implemented for receiving bug report request.
     */
    AAP_BugReportReqCb fpBugReportReqCb;

    /*!
     * \brief
     * Callback to be implemented for receiving bug phone battery status.
     */
    AAP_BatteryStatusCb fpBatteryStatusCb;

    /*!
     * \brief
     * Callback to be implemented for receiving car connected devices request.
     */
    AAP_CarConnectedDevReqCb fpCarConnectedDevReqCb;

    /*!
     * \brief
     * Callback to be implemented for receiving user switch request.
     */
    AAP_PrepareDevForSwitchCb fpPrepareDevSwitchCb;

    /*!
     * \brief
     * Application context handle*/
    AAP_VOID *pvUserData;

}AAP_CallbackList;

#if defined __cplusplus
    }
#endif

#endif /* _AAP_TYPES_H_ */
