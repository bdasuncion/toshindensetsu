#include <stdlib.h>
//#include <malloc.h>
#include "GBASound.h"
#include "GBADMA.h"
#include "GBATimer.h"
#include "UtilCommonValues.h"
#include "ManagerSound.h"

#define BUFFER_SIZE 176
#define SAMPLING_FREQUENCY 10512
#define SOUND_TIMER  63940
#define INDEX_FRACTION 12
//#define INDEX_FRACTION 8
#define RCPMIXFREQFRACTION 16
#define SOUNDEFFECT_NUM_CHANNEL 5
#define MUSIC_NUM_CHANNEL 4

#define UPDATE_ONFRAME_1 = 0
#define UPDATE_ONFRAME_2 = 7
#define UPDATE_MAXCOUNT = 14
#define NATIVE_GBA_SAMPLERATE 32768 

const int PLAYBACKFREQ[ESoundQualityCount] = {
	10512, 13379, 18157, 21024, 26758, 31536
};

const int SOUNDBUFFERSIZE[ESoundQualityCount] = {
	176, 224, 304, 352, 448, 528
};

const s32 sound_zero[] = {0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0};

#define MAX_DISTANCE 16
const u32 distanceAttenuation[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

const SampleSoundChannel freeSoundEffectChannel = { 0, 0, 0, true, false, true, true, false, false, 0, 0, NULL, NULL };
const MusicChannel freeMusicChannel = { NULL, 0, 0, 0, 0};
SoundBuffer soundBuffer;
SampleSoundChannel soundChannels[SOUNDEFFECT_NUM_CHANNEL];
MusicChannel musicChannels[MUSIC_NUM_CHANNEL];

void msound_init() {
    int i;
    for (i = 0; i < SOUNDEFFECT_NUM_CHANNEL; ++i) {
	    soundChannels[i] = freeSoundEffectChannel;
	}
	
	for (i = 0; i < MUSIC_NUM_CHANNEL; ++i) {
		musicChannels[i] = freeMusicChannel;
	}
}

void msound_setUpMono(int quality) {
	*REG_SOUNDCNT_H = DIRECT_SOUNDA_VOL(1) | DIRECT_SOUNDB_OUTR |
					DIRECT_SOUNDB_OUTL | DIRECT_SOUNDB_TIMER(0)|
					DIRECT_SOUNDB_RESET;
	*REG_SOUNDCNT_X = SOUND_ON;
					
	soundBuffer.currentBuffer = 0;
	
	soundBuffer.bufferA = malloc(SOUNDBUFFERSIZE[quality]*2*sizeof(s8));
	soundBuffer.bufferB = malloc(SOUNDBUFFERSIZE[quality]*2*sizeof(s8));//Why does this crash when I remove this?
	soundBuffer.soundQuality = quality;
	soundBuffer.rcpMixFrequency = (1<<(INDEX_FRACTION + RCPMIXFREQFRACTION))/PLAYBACKFREQ[quality];
	gbatimer_set(GBA_CLOCK_SPEED/PLAYBACKFREQ[quality]);
	dma1_soundmode(soundBuffer.bufferA);
}

void msound_setUpStereo(int quality) {
	*REG_SOUNDCNT_H = DIRECT_SOUNDA_VOL(1) | DIRECT_SOUNDB_VOL(1) | 
	                  //DIRECT_SOUNDA_VOL(0) | DIRECT_SOUNDB_VOL(0) | 
	                  DIRECT_SOUNDA_OUTR | DIRECT_SOUNDA_TIMER(0) |
					  DIRECT_SOUNDB_OUTL | DIRECT_SOUNDB_TIMER(0) |
					  DIRECT_SOUNDA_RESET | DIRECT_SOUNDB_RESET;
	*REG_SOUNDCNT_X = SOUND_ON;
					
	soundBuffer.currentBuffer = 0;
	
	soundBuffer.bufferA = malloc(SOUNDBUFFERSIZE[quality]*2*sizeof(s8));
	soundBuffer.bufferB = malloc(SOUNDBUFFERSIZE[quality]*2*sizeof(s8));
	soundBuffer.soundQuality = quality;
	soundBuffer.rcpMixFrequency = (1<<(INDEX_FRACTION + RCPMIXFREQFRACTION))/PLAYBACKFREQ[quality];
	gbatimer_set(GBA_CLOCK_SPEED/PLAYBACKFREQ[quality]);
	dma1_soundmode(soundBuffer.bufferA);
	dma2_soundmode(soundBuffer.bufferB);
} 

SampleSoundChannel* getOpenChannel() {
    int i;
    for (i = 0; i < SOUNDEFFECT_NUM_CHANNEL; ++i) {
	    if (soundChannels[i].isOpen) {
	        return &soundChannels[i];
		}
	}
	return NULL;
}

void msound_setChannel3d(const Sound *sound, bool isRepeating, 
    int rightPhaseDelay, int leftPhaseDelay, int distAttenuation) {
    SampleSoundChannel *channel = getOpenChannel();
	if (!channel) {
	    return;
	}
	if (sound->sampleSize == 8) {
		channel->size = sound->size;
	} else {
		channel->size = sound->size >> 1;
	}
	channel->aOutOfPhase = rightPhaseDelay;
	channel->bOutOfPhase = leftPhaseDelay;
	channel->isOpen = false;
	channel->repeating = isRepeating;
	channel->idxStep = (sound->frequency * soundBuffer.rcpMixFrequency) >> RCPMIXFREQFRACTION;
	//channel->currentIdx = 0;
	channel->currentIdxA = 0;
	channel->currentIdxB = 0;
	channel->stopA = false;
	channel->stopB = false;
	channel->attenuationA = distAttenuation + (rightPhaseDelay > 0)*1;
	channel->attenuationB = distAttenuation + (leftPhaseDelay > 0)*1;
	//channel->attenuationA = distAttenuation;
	//channel->attenuationB = distAttenuation;
	channel->data = sound->data;
}

void msound_setChannel(const Sound *sound, bool isRepeating) {
	msound_setChannel3d(sound, isRepeating, 0, 0, 0);
}

void msound_updateTrack(Track *track) {
	if (track->framesPassed == UPDATE_ONFRAME_1) {
	} else if (track->framesPassed == UPDATE_ONFRAME_2 {
	}
	++track->framesPassed;
	if (track->framesPassed >= UPDATE_MAXCOUNT) {
		track->framesPassed = 0;
	}
}

void msound_setMusicChannel(int idx, PatternData *pattern) {
	if (pattern->instrument != NULL) {
		musicChannels[idx].instrument = pattern->instrument;
		musicChannels[idx].idx = 0;
		musicChannels[idx].idxStep = pattern->note*soundBuffer.rcpMixFrequency;
	}
}
void msound_mixMono() {
	//int zero = 0;
	int startingIdx = 0, i, idxChannel;
	if (!soundBuffer.currentBuffer) {
		startingIdx = BUFFER_SIZE;
		soundBuffer.currentBuffer = 1;
	} else {
		soundBuffer.currentBuffer = 0;
	}

	dma3_cpy32(&soundBuffer.bufferA[startingIdx], sound_zero, BUFFER_SIZE >> 2);
	//dma3_cpy32(&soundBuffer.bufferB[startingIdx], sound_zero, BUFFER_SIZE >> 2);
	
	for (idxChannel = 0; idxChannel < SOUNDEFFECT_NUM_CHANNEL; ++idxChannel) {
	    SampleSoundChannel *soundChannel = &soundChannels[idxChannel];
	    if (soundChannel->isOpen) {
		    continue;
		}
		
		for(i = 0; i < BUFFER_SIZE; ++i) {
		    if (!soundChannel->stopA) {
			    int idxData = soundChannel->currentIdxA >> INDEX_FRACTION;
			    soundBuffer.bufferA[startingIdx + i] += soundChannel->data[idxData];
				soundChannel->currentIdxA += soundChannel->idxStep;
			}
			
			/*if (!soundChannel->stopB) {
			    int idxData = soundChannel->currentIdxB >> INDEX_FRACTION;
				soundBuffer.bufferA[startingIdx + i] += soundChannel->data[idxData];
				soundChannel->currentIdxB += soundChannel->idxStep;
			}*/
			    
			if ((soundChannel->currentIdxA >> INDEX_FRACTION) >= soundChannel->size) {
				soundChannel->currentIdxA = 0;
				if (!soundChannel->repeating) {
				    soundChannel->stopA = true;
				}
			}
			
			/*if ((soundChannel->currentIdxB >> INDEX_FRACTION) >= soundChannel->size) {
				soundChannel->currentIdxB = 0;
				if (!soundChannel->repeating) {
				    soundChannel->stopB = true;
				}
			}*/
			
			if (soundChannel->stopA) {
				    *soundChannel = freeSoundEffectChannel;
					break;
			}
		}
	}
}

ARM_IWRAM void msound_mixStereo() {
	//int zero = 0;
	int startingIdx = 0, i, idxChannel, bufSize = SOUNDBUFFERSIZE[soundBuffer.soundQuality];
	if (!soundBuffer.currentBuffer) {
		//startingIdx = BUFFER_SIZE;
		startingIdx = bufSize;
		soundBuffer.currentBuffer = 1;
	} else {
		soundBuffer.currentBuffer = 0;
	}

	//dma3_cpy32_srcFix(&soundBuffer.buffer[startingIdx], sound_zero, BUFFER_SIZE >> 2);
	//dma3_cpy32(&soundBuffer.bufferA[startingIdx], sound_zero, BUFFER_SIZE >> 2);
	//dma3_cpy32(&soundBuffer.bufferB[startingIdx], sound_zero, BUFFER_SIZE >> 2);
	dma3_cpy32(&soundBuffer.bufferA[startingIdx], sound_zero, bufSize >> 2);
	dma3_cpy32(&soundBuffer.bufferB[startingIdx], sound_zero, bufSize >> 2);
	
	for (idxChannel = 0; idxChannel < SOUNDEFFECT_NUM_CHANNEL; ++idxChannel) {
	    SampleSoundChannel *soundChannel = &soundChannels[idxChannel];
	    if (soundChannel->isOpen) {
		    continue;
		}
		
		//for(i = 0; i < BUFFER_SIZE; ++i) {
		for(i = 0; i < bufSize; ++i) {
		    if (!soundChannel->stopA && i >= soundChannel->aOutOfPhase) {
			    int idxData = soundChannel->currentIdxA >> INDEX_FRACTION;
				if (soundChannel->attenuationA < MAX_DISTANCE) {
			        //soundBuffer.bufferA[startingIdx + i] += (soundChannel->data[idxData] >> 
					//    distanceAttenuation[soundChannel->attenuationA]);
					int sound = 0;
					if (soundChannel->data[idxData] > 0) {
						sound = soundChannel->data[idxData] - soundChannel->attenuationA;
						if (sound < 0){
							sound = 0;
						}
					} else if (soundChannel->data[idxData] < 0){
						sound = soundChannel->data[idxData] + soundChannel->attenuationA;
						if (sound > 0){
							sound = 0;
						}
					}
					soundBuffer.bufferA[startingIdx + i] += sound;
				}
				//soundBuffer.bufferA[startingIdx + i] += (soundChannel->data[idxData]);
				//soundBuffer.bufferA[startingIdx + i] -= (soundChannel->data[idxData] >> 4)*(soundChannel->attenuationA);
				soundChannel->currentIdxA += soundChannel->idxStep;
			}
			
			if (!soundChannel->stopB  && i >= soundChannel->bOutOfPhase) {
			    int idxData = soundChannel->currentIdxB >> INDEX_FRACTION;
				if (soundChannel->attenuationB < MAX_DISTANCE) {
				    //soundBuffer.bufferB[startingIdx + i] += (soundChannel->data[idxData] >> 
					//distanceAttenuation[soundChannel->attenuationB]);
					int sound = 0;
					if (soundChannel->data[idxData] > 0) {
						sound = soundChannel->data[idxData] - soundChannel->attenuationB;
						if (sound < 0){
							sound = 0;
						}
					} else if (soundChannel->data[idxData] < 0){
						sound = soundChannel->data[idxData] + soundChannel->attenuationB;
						if (sound > 0){
							sound = 0;
						}
					}
					soundBuffer.bufferB[startingIdx + i] += sound;
				}
				//soundBuffer.bufferB[startingIdx + i] += (soundChannel->data[idxData]);
				//soundBuffer.bufferB[startingIdx + i] -= (soundChannel->data[idxData] >> 4)*(soundChannel->attenuationB);
				soundChannel->currentIdxB += soundChannel->idxStep;
			}
			    
			if ((soundChannel->currentIdxA >> INDEX_FRACTION) >= soundChannel->size) {
				soundChannel->currentIdxA = 0;
				if (!soundChannel->repeating) {
				    soundChannel->stopA = true;
				}
			}
			
			if ((soundChannel->currentIdxB >> INDEX_FRACTION) >= soundChannel->size) {
				soundChannel->currentIdxB = 0;
				if (!soundChannel->repeating) {
				    soundChannel->stopB = true;
				}
			}
			
			if (soundChannel->stopA && soundChannel->stopB) {
				    *soundChannel = freeSoundEffectChannel;
					break;
			}
		}
		
		soundChannel->aOutOfPhase = 0;
		soundChannel->bOutOfPhase = 0;
	}
}

ARM_IWRAM void msound_mixMusic() {
	int i, idxChannel;
	int bufSize = SOUNDBUFFERSIZE[soundBuffer.soundQuality], startingIdx;
	
	if (!soundBuffer.currentBuffer) {
		startingIdx = bufSize;
		soundBuffer.currentBuffer = 1;
	} else {
		soundBuffer.currentBuffer = 0;
	}
	
	for (idxChannel = 0; idxChannel < MUSIC_NUM_CHANNEL; ++idxChannel) {
		MusicChannel *currentChannel = &musicChannels[idxChannel];
		for(i = 0; i < bufSize; ++i) {
			if (!currentChannel->length) {
				continue;
			}
			int idxData = currentChannel->idx >> INDEX_FRACTION;
			soundBuffer.bufferA[startingIdx + i] += currentChannel->instrument->data[idxData];
			soundBuffer.bufferB[startingIdx + i] += currentChannel->instrument->data[idxData];
			currentChannel->idx += currentChannel->idxStep;
			
			if ((currentChannel->idx >> INDEX_FRACTION) >= currentChannel->length) {
				currentChannel->idx = 0;
			}
		}
	}
}

void msound_mixStereoASMR() {
	//int zero = 0;
	int startingIdx = 0, i, idxChannel, bufSize = SOUNDBUFFERSIZE[soundBuffer.soundQuality];
	if (!soundBuffer.currentBuffer) {
		startingIdx = bufSize;
		soundBuffer.currentBuffer = 1;
	} else {
		soundBuffer.currentBuffer = 0;
	}

	//dma3_cpy32_srcFix(&soundBuffer.buffer[startingIdx], sound_zero, BUFFER_SIZE >> 2);
	
	//dma3_cpy32(&soundBuffer.bufferA[startingIdx], sound_zero, BUFFER_SIZE >> 2);
	//dma3_cpy32(&soundBuffer.bufferB[startingIdx], sound_zero, BUFFER_SIZE >> 2);
	dma3_cpy32(&soundBuffer.bufferA[startingIdx], sound_zero, bufSize >> 2);
	dma3_cpy32(&soundBuffer.bufferB[startingIdx], sound_zero, bufSize >> 2);
	
	for (idxChannel = 0; idxChannel < SOUNDEFFECT_NUM_CHANNEL; ++idxChannel) {
	    SampleSoundChannel *soundChannel = &soundChannels[idxChannel];
	    if (soundChannel->isOpen) {
		    continue;
		}
		
		for(i = 0; i < bufSize; ++i) {
		    if (!soundChannel->stopA && i >= soundChannel->aOutOfPhase) {
			    int idxData = soundChannel->currentIdxA >> INDEX_FRACTION;
				if (soundChannel->attenuationA < MAX_DISTANCE) {
			        soundBuffer.bufferA[startingIdx + i] += (soundChannel->data[idxData] >> 
					    distanceAttenuation[soundChannel->attenuationA]);
				}
				/*if (soundChannel->attenuationA < MAX_DISTANCE) {
					soundBuffer.bufferA[startingIdx + i] += (soundChannel->data[idxData]) - 
					    ((soundChannel->data[idxData] >> 4)*soundChannel->attenuationA);
				}*/
				//soundBuffer.bufferA[startingIdx + i] += (soundChannel->data[idxData]);
				//soundBuffer.bufferA[startingIdx + i] -= (soundChannel->data[idxData] >> 4)*(soundChannel->attenuationA);
				soundChannel->currentIdxA += soundChannel->idxStep;
			}
			
			if (!soundChannel->stopB  && i >= soundChannel->bOutOfPhase) {
			    int idxData = soundChannel->currentIdxB >> INDEX_FRACTION;
				if (soundChannel->attenuationB < MAX_DISTANCE) {
				    soundBuffer.bufferB[startingIdx + i] += (soundChannel->data[idxData] >> 
					distanceAttenuation[soundChannel->attenuationB]);
				}
				/*if (soundChannel->attenuationB < MAX_DISTANCE) {
					soundBuffer.bufferB[startingIdx + i] += (soundChannel->data[idxData]) - 
					    ((soundChannel->data[idxData] >> 4)*soundChannel->attenuationB);
				}*/
				//soundBuffer.bufferB[startingIdx + i] += (soundChannel->data[idxData]);
				//soundBuffer.bufferB[startingIdx + i] -= (soundChannel->data[idxData] >> 4)*(soundChannel->attenuationB);
				soundChannel->currentIdxB += soundChannel->idxStep;
			}
			    
			if ((soundChannel->currentIdxA >> INDEX_FRACTION) >= soundChannel->size) {
				soundChannel->currentIdxA = 0;
				if (!soundChannel->repeating) {
				    soundChannel->stopA = true;
				}
			}
			
			if ((soundChannel->currentIdxB >> INDEX_FRACTION) >= soundChannel->size) {
				soundChannel->currentIdxB = 0;
				if (!soundChannel->repeating) {
				    soundChannel->stopB = true;
				}
			}
			
			if (soundChannel->stopA && soundChannel->stopB) {
				    *soundChannel = freeSoundEffectChannel;
					break;
			}
		}
		
		soundChannel->aOutOfPhase = 0;
		soundChannel->bOutOfPhase = 0;
	}
}

void msound_changeBuf() {
	if (!soundBuffer.currentBuffer) {
		dma2_soundmode(soundBuffer.bufferA);
		dma1_soundmode(soundBuffer.bufferB);
	}
}

void msound_process3dSound(int *distance, int *rightPhaseDelay, int *leftPhaseDelay){
	*rightPhaseDelay = 6*(*distance < 0);
	*leftPhaseDelay = 6*(*distance > 0);
	*distance = *distance >> 4;
	*distance *= (*distance < 0)*(-1) + (*distance >= 0)*1;
}

/*void MusicMix() {
	s32 i;
	for(i = 0; i < soundVars.mixBufferSize; i++) {
	// copy a sample
	soundVars.curMixBuffer[i] = channel.data[ channel.pos>>12 ] * channel.vol >> 6;
	channel.pos += channel.inc;
	// loop the sound if it hits the end
		if(channel.pos >= channel.length){
			channel.pos = 0;
		}
	}
}*/
