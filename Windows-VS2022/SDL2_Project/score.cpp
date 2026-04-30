#include <iostream>
#include "score.hpp"
#include"NPC.hpp"

Score::Score() {
	scoreVal(0);
}

Score::~Score() {
	clearScore();
}

void Score::clearScore() {
	for (int i = 0; i < mscore.size(); i++) {
		delete mscore[i];
		mscore[i] = NULL;
	}
	mscore.clear();
}

void Score::scoreVal(int scoreVal (std::shared_ptr<NPC>)) {
	clearScore();
	
	if (score == 0) {
		for (int i = 0; i < 100; i++) {
			mscore.push_back(new Texture("0", 32, {230, 230, 230}));
		}
	}
}