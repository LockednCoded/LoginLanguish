#pragma once

#include "stage.h"
#include <vector>
#include "../game_manager.h"

const std::vector<std::string> MOVES = {"paper", "scissors", "rock"};
const std::vector<std::string> NUMS = {"zero", "one", "two", "three"};

class DwayneStage : public Stage
{
public:
	DwayneStage(GameManager *gameManager);

	bool validateStage();
	void update(const rapidjson::Value &req);
	rapidjson::Value getFieldStates(rapidjson::Document::AllocatorType &allocator);

private:
	std::string face;
	void newMatch();
	void handleMove(std::string move);
	void rerollFaces();
	char round;
	int wins;
	int losses;
	std::string top_text;
	std::string bottom_text;
	int iteration;
	bool game_over;
	bool game_win;
	std::string temp_sound;
	std::string temp_face;
	std::vector<std::string> reaction_faces = {"react1", "react2", "react3"};
	std::vector<std::string> neutral_faces = {"neutral1", "neutral2"};
	std::string getFacePath(std::string face);
	std::string getSoundPath(std::string face);
	void endGame();
	int timemout_ms;
};