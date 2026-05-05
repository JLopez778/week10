#ifndef SCORE_HPP_
#define SCORE_HPP_

#include "Player.hpp";
#include "NPC.hpp";
#include"Vector3f.hpp";
#include "Texture.hpp";
#include "Window.hpp";
#include <vector>

class Score {

private:
	int score;
	//std::vector<Texture*>mscore;
public:
	Score();
	~Score();
	

	void scoreVal(int val);
	void inreaseScore(int amt);

	void Render();

private:
	void clearScore();
	//float mscore = 50;

};

#endif