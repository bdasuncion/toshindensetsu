#ifndef CHARACTER_KANKANDARA
#define CHARACTER_KANKANDARA

#include "GBAObject.h"
#include "GBACharacter.h"

typedef enum KankandaraAction
{
	EKankandaraInitialize = -1,
	EKankandaraWait,
	EKankandaraDissappaer,
	EKankandaraCrawl,
	EKankandaraActionCount
} KankandaraAction;

typedef enum KankandaraStatus
{
	EKankandaraStatusWaiting,
	EKankandaraStatusDissappear,
	EKankandaraStatusNormal,
	EKankandaraStatusTurnAround,
} KankandaraStatus;


void kankandara_init(CharacterAttr* character, ControlTypePool* controlPool);
#endif