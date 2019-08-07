/******************************************************************************
 *
 *
 *   ALLGO EMBEDDED SYSTEMS CONFIDENTIAL PROPRIETARY
 *
 *    (C) 2015-16 ALLGO EMBEDDED SYSTEMS PVT. LTD.
 *
 *   FILENAME        - aap_plat_aplayer_interface.h
 *
 *   COMPILER        - gcc <4.6.3 or similar>
 *
 ******************************************************************************
 *
 *   CHANGE HISTORY
 *   DATE        VERSION        DESCRIPTION                      Author
 *   --------    -------        -----------                      ------
 *   18/03/2015     1.0         Initial Version                 Shiva Kumar
 *   07/04/2015     2.0         Cleaned up for AAP              Vaisakh N
 *   01/12/2016     3.0         Added description to APIs       Dipankar Saha
 *                              and data structure
 * *******************************************************************************
 *
 *   DESCRIPTION
 *   Interface header file for AAP platform audio player
 *
 ******************************************************************************/

#ifndef _AAP_PLAT_APLAYER_INTERFACE_H_
#define _AAP_PLAT_APLAYER_INTERFACE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "aap_standard_types.h"
#include "aap_plat_media_player_types.h"

#if defined __cplusplus
    extern "C" {
#endif

/*! \file aap_plat_aplayer_interface.h
\brief APIs for AAP audio player.
*/

/*! \struct AAPAudioConfig
 * \brief This structure contains different configuration parameters of
 * audio player.
 * */
typedef struct
{
    /*! Number of channels of the incoming audio stream */
    AAP_UINT32 uiChannels;
    /*! Audio sample rate of the incoming audio stream */
    AudioFreq eAudioFreq;
    /*! BitsPerSample of the incoming audio stream */
    AAP_UINT32 uiAudioBps;
    /*! This is codec type of the incoming audio stream */
    AAPPlayerStreamType eAudioType;
    /*! Audio Stream Type i.e, MEDIA/GUIDANCE/SYSTEM for which audio player is
     * being set up */
    AAP_StreamType eStreamType;
    /*! Audio Device ID where audio will be played by the audio player. */
    AAP_CHAR acAudioDeviceID[AAP_SMALL_ARRAY_LEN];
}AAPAudioConfig;

/*!
 * \fn AAP_RetType aap_plat_aplayer_init(AAP_HANDLE* pulPlayerHandle,
 *          AAPAudioConfig *psAudioConfig, AAPPlayerCbFunc pfAppCb,
 *          void* pvUserParam);
 *
 * \brief Audio player should be initialized in this function. This function will be called
 * first and once for an AAP session.
 *
 * In this function, allocate all resources which are required by audio player.
 *
 * \ingroup Audio
 *
 * \param [out] pulPlayerHandle Returns the handle of the audio player.
 * \param [in]  psAudioConfig   Audio configurations. Audio player to be
 *                              configured according to this configuration.
 * \param [in]  pfAppCb         Callback function pointer to let the upper
 *                              layer know about the state or any error case of
 *                              the audio player.
 * \param [in]  pvUserParam     User data which will be passed along with the callback
 *                              function.
 *
 * \retval 0 On success.
 * \retval -1 On failure.
 *
 * \par Sequence Diagram:
 * \ref diag2 "AAP Audio player API sequence diagram"
 */
AAP_RetType aap_plat_aplayer_init(AAP_HANDLE* pulPlayerHandle,
        AAPAudioConfig *psAudioConfig, AAPPlayerCbFunc pfAppCb,
        void* pvUserParam);

/*!
 * \fn AAP_RetType aap_plat_aplayer_play(AAP_HANDLE ulPlayerHandle);
 *
 * \brief This function is to get the audio player ready for playing. After this
 * function audio player must be in a state to play the audio frames as and
 * when audio data is pushed to the audio player.
 *
 * \par Precondition:
 * #aap_plat_aplayer_init
 *
 * \note
 * 1. This function can be called multiple times during an active AAP session.
 * 2. #aap_plat_aplayer_init must be done before calling this function. However once
 * #aap_plat_aplayer_init is done, for each call of this function #aap_plat_aplayer_init
 * must not be done provided #aap_plat_aplayer_deinit is not called in between.
 *
 *
 * \ingroup Audio
 *
 * \param [in]  ulPlayerHandle  Handle of audio player returned by aap_plat_aplayer_init() API.
 *
 * \retval 0 On success.
 * \retval -1 On failure.
 *
 * \par Sequence Diagram:
 * \ref diag2 "AAP Audio player API sequence diagram"
 */
AAP_RetType aap_plat_aplayer_play(AAP_HANDLE ulPlayerHandle);

/*!
 * \fn AAP_RetType aap_plat_aplayer_process_data(AAP_HANDLE ulPlayerHandle,
 *          unsigned char *pucData, unsigned int uiSize,
 *          uint64_t ulTimeStamp);
 *
 * \brief In this function, audio data to be processed by the audio player for
 * playing the incoming audio samples.
 *
 * \par Precondition:
 * #aap_plat_aplayer_init\n
 * #aap_plat_aplayer_play
 *
 * \note
 * 1. This function likely to get called frequently and multiple times.
 * 2. Before calling this function, only once #aap_plat_aplayer_init and
 * #aap_plat_aplayer_play functions will be called.
 *
 * \ingroup Audio
 *
 * \param [in]  ulPlayerHandle  Handle of audio player returned by aap_plat_aplayer_init() API.
 * \param [in]  pucData         Buffer pointer of the audio data. Audio player
 *                              MUST not free this memory.
 * \param [in]  uiSize          Audio data size in bytes.
 * \param [in]  ulTimeStamp     Time stamp of the audio frame.
 *
 * \retval 0 On success.
 * \retval -1 On failure.
 *
 * \par Sequence Diagram:
 * \ref diag2 "AAP Audio player API sequence diagram"
 */
AAP_RetType aap_plat_aplayer_process_data(AAP_HANDLE ulPlayerHandle,
        unsigned char *pucData, unsigned int uiSize,
        uint64_t ulTimeStamp);

/*!
 * \fn AAP_RetType aap_plat_aplayer_pause(AAP_HANDLE ulPlayerHandle);
 *
 * \brief This function is called to pause the data processing temporarily.
 *
 * \ingroup Audio
 *
 * \param [in]  ulPlayerHandle  Handle of audio player returned by aap_plat_aplayer_init() API.
 *
 * \par Precondition:
 * #aap_plat_aplayer_init\n
 * #aap_plat_aplayer_play
 *
 * \retval 0 On success.
 * \retval -1 On failure.
 */
AAP_RetType aap_plat_aplayer_pause(AAP_HANDLE ulPlayerHandle);

/*!
 * \fn AAP_RetType aap_plat_aplayer_stop(AAP_HANDLE ulPlayerHandle);
 *
 * \brief This function is called to stop the data processing. After pushing all
 * data this function will be called.
 *
 * \par Precondition:
 * #aap_plat_aplayer_init\n
 * #aap_plat_aplayer_play
 *
 * \note
 * 1. This function can be called multiple times during an active AAP session
 * with the pair of #aap_plat_aplayer_play.
 *
 * \ingroup Audio
 *
 * \param [in]  ulPlayerHandle  Handle of audio player returned by aap_plat_aplayer_init() API.
 *
 * \retval 0 On success.
 * \retval -1 On failure.
 *
 * \par Sequence Diagram:
 * \ref diag2 "AAP Audio player API sequence diagram"
 */
AAP_RetType aap_plat_aplayer_stop(AAP_HANDLE ulPlayerHandle);

/*!
 * \fn AAP_RetType aap_plat_aplayer_deinit(AAP_HANDLE *pulPlayerHandle);
 *
 * \brief In this function, uninitialize the audio player. Must deallocate all the
 * resources which all were allocated at the time of audio player initialization
 * in aap_plat_aplayer_init().
 *
 * \par Precondition:
 * #aap_plat_aplayer_init
 *
 * \note
 * 1. This function gets called only once during an active AAP session.
 *
 * \ingroup Audio
 *
 * \param [in]  pulPlayerHandle  Pointer to the audio player handle returned by aap_plat_aplayer_init() API.
 *
 * \retval 0 On success.
 * \retval -1 On failure.
 *
 * \par Sequence Diagram:
 * \ref diag2 "AAP Audio player API sequence diagram"
 */
AAP_RetType aap_plat_aplayer_deinit(AAP_HANDLE *pulPlayerHandle);

#if defined __cplusplus
}
#endif

#endif  /* _AAP_PLAT_APLAYER_INTERFACE_H_ */
