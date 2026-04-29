#include "Player.hpp";
#include "NPC.hpp";
#include"Vector3f.hpp";
#include "Texture.hpp";
#include "Window.hpp";
#include <vector>
class Score {

private:
	float score = 0;
	std::vector<Texture*>mscore;
public:
	Score();
	~Score();
	

	void scoreVal(int val (std::shared_ptr<NPC>));

	void Render();

private:
	void clearScore();

};