
#include "Sound.h"
#include "../debug.h"

Sound* Sound::__Instance = NULL;

Sound::Sound()
{
	Init();
	LoadResourceSound();
}



void Sound::LoadResourceSound()
{
	AddSound(eSound::soundArea2,					L"sound/Area2.wav");
	AddSound(eSound::soundIntro,					L"sound/Intro.wav");
	AddSound(eSound::soundOutro,					L"sound/Outro.wav");
	AddSound(eSound::soundCollectItem,				L"sound/CollectItem.wav");
	AddSound(eSound::soundEnemyDestroyed,			L"sound/EnemyDestroyed.wav");
	AddSound(eSound::soundJumperJump,				L"sound/JumperJump.wav");
	AddSound(eSound::soundSkullBombDrop,			L"sound/SkullBombDrop.wav");
	AddSound(eSound::soundSkullBombExplosion,		L"sound/SkullBombExplosion.wav");
	AddSound(eSound::soundSophiaBulletExplosion,	L"sound/SophiaBulletExplosion.wav");
	AddSound(eSound::soundSophiaDamaged,			L"sound/SophiaDamaged.wav");
	AddSound(eSound::soundSophiaGroundTouch,		L"sound/SophiaGroundTouch.wav");
	AddSound(eSound::soundSophiaLongJump,			L"sound/SophiaLongJump.wav");
	AddSound(eSound::soundSophiaShoot,				L"sound/SophiaShoot.wav");
	AddSound(eSound::soundTeleporterTransform,		L"sound/TeleporterTransform.wav");
	AddSound(eSound::soundWormCrawl,				L"sound/WormCrawl.wav");
}

bool Sound::isPlaying(eSound type)
{
	return _ArrSound[type]->IsSoundPlaying();
}

void Sound::StopAll()
{
	for (auto& x : _ArrSound)
	{
		if (x.second->IsSoundPlaying())
			x.second->Stop();
	}
}


void Sound::AddSound(eSound type, LPTSTR filename)
{
	CSound* wave;
	HRESULT result = dsound->Create(&wave, filename);
	if (result != DS_OK)
	{
		DebugOut(L"[SOUND] Load Sound that bai. eSound = %d \n", (int)type);
		return;
	}
	_ArrSound[type] = wave;
}

void Sound::Play(eSound type, bool isLoop, LONG lVolume)
{	_ArrSound[type]->Play(0, isLoop, lVolume);
	//DSBPLAY_LOOPING             0x00000001 -> int = 1

}

void Sound::Stop(eSound type)
{
	_ArrSound[type]->Stop();
}



void Sound::Init()
{
	dsound = new CSoundManager();
	dsound->Initialize(CGame::GetInstance()->GetWindowHandle(), DSSCL_PRIORITY);
	dsound->SetPrimaryBufferFormat(2, 22050, 16);
}

Sound* Sound::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new Sound();
	return __Instance;
}