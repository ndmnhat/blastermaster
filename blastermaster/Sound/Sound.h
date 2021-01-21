#ifndef __SOUND_H__
#define __SOUND_H__

#include "dsutil.h"
#include <unordered_map>
#include "..\Define\Define.h"
#include "..\Game\Game.h"

enum eSound
{
	soundArea2 = 1,
	soundIntro = 2,
	soundOutro = 3,
	soundCollectItem = 4,
	soundEnemyDestroyed = 5,
	soundJumperJump = 6,
	soundSkullBombDrop = 7,
	soundSkullBombExplosion = 8,
	soundSophiaBulletExplosion = 9,
	soundSophiaDamaged = 10,
	soundSophiaGroundTouch = 11,
	soundSophiaLongJump = 12,
	soundSophiaShoot = 13,
	soundTeleporterTransform = 14,
	soundWormCrawl = 15,
	
};


class Sound
{
private:
	unordered_map<eSound, CSound* > _ArrSound;

public:
	static Sound* __Instance;
	static Sound* GetInstance();


	CSoundManager* dsound;

	void Init();
	Sound();

	void AddSound(eSound type, LPTSTR filename);
	void Play(eSound type, bool isLoop = false, LONG lVolume = 0L);
	void Stop(eSound type);
	void LoadResourceSound();

	bool isPlaying(eSound type);

	void StopAll();

};

#endif

