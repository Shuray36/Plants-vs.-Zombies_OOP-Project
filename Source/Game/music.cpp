#include "stdafx.h"
#include "music.h"
#include "../Library/audio.h"
#include "map.h"

void Music::load_music() {
	sound = game_framework::CAudio::Instance();
	sound->Load(0, "Plants_vs_Zombies_Image/music/Begin.wav");
	sound->Load(1, "Plants_vs_Zombies_Image/music/fight.wav");
	sound->Load(2, "Plants_vs_Zombies_Image/music/atk.wav");
	sound->Load(3, "Plants_vs_Zombies_Image/music/place.wav");
	sound->Load(4, "Plants_vs_Zombies_Image/music/chili.wav");
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