#include <iostream>
#include "score.hpp"
#include"NPC.hpp"

Score::Score() {
	scoreVal(0);
}

Score::~Score() {
	clearScore();
}

void Score::clearScore() 
{
	score = 0;
}

void Score::scoreVal(int scoreVal) 
{
	/*clearScore();
	
	if (score == 0) {
		for (int i = 0; i < 100; i++) {
			if (std::shared_ptr<NPC> defeat def)
		}
	}*/
}

void Score::inreaseScore(int amt)
{
	score += amt;
}