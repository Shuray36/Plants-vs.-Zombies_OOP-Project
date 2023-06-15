#include "stdafx.h"
#include "music.h"
#include "../Library/audio.h"
#include "map.h"

void Music::load_music() {
	sound = game_framework::CAudio::Instance();
	sound->Load(1, "Plants_vs_Zombies_Image/music/fight.wav");
	sound->Load(0, "Plants_vs_Zombies_Image/music/Begin.wav");
}

void Music::play(int x, bool j) {
	sound->Play(x, j);
}

void Music::pause() {
	sound->Pause();
}

void Music::Stop(int n) {
	sound->Stop(n);
}