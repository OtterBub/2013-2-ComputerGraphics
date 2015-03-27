#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "fmod\fmod.hpp"

#pragma comment(lib, "fmodex_vc.lib")

#define SOUND SoundManager::Instance()

enum SOUNDKIND {
	SD_GUN_COCKING = 0,
	SD_GUN_SHOT,
	SD_END
};

class SoundManager {
	SoundManager(const SoundManager&);
	SoundManager operator=(const SoundManager&);

	SoundManager()
	{
		FMOD::System_Create(&pSystem);

		pSystem->init(4, FMOD_INIT_NORMAL, 0);

		char* filename[] = {
			"mp3/gun-cocking-01.mp3",
			"mp3/gun-gunshot-01.mp3"
		};

		for( int i = 0; i < SD_END; i++) {
			pSystem->createSound(filename[i], FMOD_HARDWARE, 0, &pSound[i]);
		}
		pSystem->createStream("06._kokkis_one_man_show.mp3", FMOD_LOOP_NORMAL, 0, &pSound[SD_END]);

	}

	~SoundManager() {
		pSystem->close();
		for( int i = 0; i < SD_END; i++) {
			pSound[i]->release();
		}
	}

public:
	static SoundManager& Instance() {
		static SoundManager instance;
		return instance;
	}

	// Sound Value
	FMOD::System* pSystem;
	FMOD::Sound* pSound[SD_END];
	FMOD::Channel* pChannel;

};

#endif // SOUNDMANAGER_H