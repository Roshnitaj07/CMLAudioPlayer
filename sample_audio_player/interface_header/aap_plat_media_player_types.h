/******************************************************************************
 *
 *
 *   ALLGO EMBEDDED SYSTEMS CONFIDENTIAL PROPRIETARY
 *
 *    (C) 2013 ALLGO EMBEDDED SYSTEMS PVT. LTD.
 *
 *   FILENAME        - aap_plat_media_player_types.h
 *
 *   COMPILER        - gcc 4.4.4
 *
 ******************************************************************************
 *
 *   CHANGE HISTORY
 *   DATE        VERSION        DESCRIPTION                      Author
 *   --------    -------        -----------                      ------
 *   26/12/2014    1.0         Initial Version                 Shiva Kumar
 *   10/04/2015    2.0         Updated & renamed for AAP       Vaisakh N
 *   02/12/2016    3.0         Reorganized and added           Dipankar Saha
 *                             descriptions.
 * *******************************************************************************
 *
 *   DESCRIPTION
 *   Header file for AAP player for internal modules only
 *
 ******************************************************************************/
#ifndef _AAP_PLAT_MEDIA_PLAYER_TYPES_H_
#define _AAP_PLAT_MEDIA_PLAYER_TYPES_H_

#include "aap_standard_types.h"
#include "aap_types.h"

#if defined __cplusplus
extern "C" {
#endif /* if defined __cplusplus */

/*! \file aap_plat_media_player_types.h
\brief Common data structures for media players.
*/

/*! \brief typedef unsigned long long AAP_PLAYER_HANDLE
Definition of player handle.
*/
typedef unsigned long long AAP_PLAYER_HANDLE;

/*! Audio mono channel */
#define AUDIO_CHANNEL_MONO 1
/*! Audio stereo channel */
#define AUDIO_CHANNEL_STEREO 2
/*! 8 bits per sample */
#define AUDIO_BPS_8 8
/*! 16 bits per sample */
#define AUDIO_BPS_16 16
/*! 32 bits per sample */
#define AUDIO_BPS_32 32

enum
{
    /*! Failed to start  */
    E_AAP_ERROR_PLAYER_START = 1,
    /*! Failed to init */
    E_AAP_ERROR_PLAYER_INIT ,
    /*! Player timeout */
    E_AAP_ERROR_PLAYER_TIMEOUT,
    /*! VPU error */
    E_AAP_ERROR_PLAYER_VPU,
    /*! Thread create error */
    E_AAP_ERROR_PLAYER_THREAD_CREATE,
    /*! Failed to do execute system call*/
    E_AAP_ERROR_PLAYER_SYSTEM_CALL,
    /*! State change failed */
    E_AAP_ERROR_PLAYER_STATE_CHANGE,
    /*! Player in invalid state */
    E_AAP_ERROR_PLAYER_INVALID_STATE,
    /*! Failed to push buffer */
    E_AAP_ERROR_PLAYER_PUSH_BUFFER,
    /*! Failed to pull buffer */
    E_AAP_ERROR_PLAYER_PULL_BUFFER,
    /*! Reached EOS */
    E_AAP_ERROR_PLAYER_EOS, /* Treated as ERROR */
    /*! Failed to pull data, time out */
    E_AAP_ERROR_PLAYER_NO_DATA_TIMEOUT /* Treated as ERROR */
};

/*! \enum AAPPlayer_Events
 * \brief Different players state */
typedef enum
{
    /*! \brief Player faced an error */
    E_AAP_PLAYER_FACED_ERROR,
    /*! \brief Player is in ready state */
    E_AAP_PLAYER_READY,
    /*! \brief Player is in pause state */
    E_AAP_PLAYER_PAUSED,
    /*! \brief Player is in playing state */
    E_AAP_PLAYER_PLAYING,
    /*! \brief input buffer from player/recorder*/
    E_AAP_PLAYER_INPUT_BUFFER,
    /*! \brief Player is in idle state */
    E_AAP_PLAYER_IDEL,
    /*! \brief Player stopped running */
    E_AAP_PLAYER_QUIT
}AAPPlayer_Events;

/*! \enum AAPPlayerStreamType
 * \brief Different codec type for audio and video */
typedef enum
{
    /*! Invalid stream */
    AUDIO_STREAM_INVALID = 0,
    /*! AAC stream */
    AUDIO_STREAM_AAC_LC,
    /*! AAC LC ADTS stream */
    AUDIO_STREAM_AAC_LC_ADTS,
    /*! PCM stream */
    AUDIO_STREAM_PCM,
    /*! H264 video stream. */
    VIDEO_STREAM_H264
}AAPPlayerStreamType;

/*! \enum AudioFreq
 * \brief Different sampling rates for audio */
typedef enum
{
    /*! 16 KHz audio sampling frequency */
    AUDIO_SAMPLING_FREQ_16K = 16000,
    /*! 44.1 KHz audio sampling frequency */
    AUDIO_SAMPLING_FREQ_44K = 44100,
    /*! 48 KHz audio sampling frequency */
    AUDIO_SAMPLING_FREQ_48K = 48000
}AudioFreq;

/*! \typedef AAP_VOID (*AAPPlayerCbFunc)(AAPPlayer_Events uiEvtId,
 *         AAP_UINT32 uiDataLen,
 *         AAP_VOID *pvData,
 *         AAP_VOID *pvCbParam);
 * \brief Common callback for players to send the different states of the player.
 *
 * \note This function doesn't propagate these information to application.
 *
 * \param uiEvtId       [in] Different states of the player.
 * \param uiDataLen     [in] Length of the data buffer being passed.
 * \param pvData        [in] This is to pass any specific state data of the
 *                           player. For an example any information related to
 *                           any error case or state.
 * \param pvCbParam     [in] User data of the called function.
 */
typedef AAP_VOID (*AAPPlayerCbFunc)(AAPPlayer_Events uiEvtId,
        AAP_UINT32 uiDataLen,
        AAP_VOID *pvData,
        AAP_VOID *pvCbParam);

#if defined __cplusplus
}
#endif /* if defined __cplusplus */

#endif  /* _AAP_PLAT_MEDIA_PLAYER_TYPES_H_ */
