#include "dwayne_stage.h"
#include "file_utils.h"
#include "random_utils.h"

DwayneStage::DwayneStage(GameManager *gameManager) : Stage(gameManager)
{
	name = "dwayne";
	iteration = 0;
	newMatch();
}
void DwayneStage::handleMove(std::string move)
{
	// action: paper (0) | scissors (1) | rock (2) | rematch

	if (game_over)
	{
		if (move.compare("rematch") == 0)
			newMatch();
		return;
	}

	const int dwayne_move = rand_utils::randomInt(0, 2);
	int player_move;
	for (int i = 0; i < 3; i++)
		if (move.compare(MOVES[i]) == 0)
			player_move = i;

	int outcome = 0; // 0 = tie, 1 = player win, 2 = player lose
	if ((player_move + 1) % 3 == dwayne_move)
		outcome = 2;
	else if ((dwayne_move + 1) % 3 == player_move)
		outcome = 1;

	std::string outcome_str;
	timemout_ms = 2000;
	if (outcome == 1)
	{
		wins++;
		outcome_str = "win round " + NUMS[round] + ".";
		temp_sound = getSoundPath("vine_boom");
		temp_face = getFacePath("sad");
	}
	else if (outcome == 2)
	{
		losses++;
		outcome_str = "lose round " + NUMS[round] + ".";
		temp_sound = getSoundPath("vine_explode");
		temp_face = getFacePath("happy");
	}
	else
	{
		outcome_str = "tie.";
		temp_face = getFacePath("tie");
	}
	iteration++;

	top_text = "Dwayne chose " + MOVES[dwayne_move] + ". You " + outcome_str;

	if (wins >= 2 || losses >= 2 || round >= 3)
	{
		endGame();
		return;
	}
	round++;

	rerollFaces();
	face = getFacePath(neutral_faces[0]);
}

void DwayneStage::endGame()
{
	game_over = true;
	if (wins < losses)
	{
		face = getFacePath("win"); // Dwayne wins, you lose
		bottom_text = "You have been defeated.";
	}
	else if (wins > losses)
	{
		face = getFacePath("lose"); // Dwayne loses, you win.
		bottom_text = "Dwayne has been defeated.";
		game_win = true;
	}
	else
	{
		face = getFacePath("tie");
		bottom_text = "You tie with Dwayne.";
	}
}

std::string DwayneStage::getFacePath(std::string face)
{
	return file_utils::convertPathToFrontendString(file_utils::getPathToResource("datasets/dwayne/faces/" + face + ".jpeg"));
}
std::string DwayneStage::getSoundPath(std::string face)
{
	return file_utils::convertPathToFrontendString(file_utils::getPathToResource("datasets/dwayne/sounds/" + face + ".mp3"));
}

void DwayneStage::rerollFaces()
{
	rand_utils::shuffle(reaction_faces);
	rand_utils::shuffle(neutral_faces);
}
void DwayneStage::newMatch()
{
	round = 1;
	wins = 0;
	losses = 0;
	game_over = false;
	game_win = false;
	rerollFaces();
	face = getFacePath(neutral_faces[0]);
	bottom_text = "Make your choice.";
	top_text = "Dwayne is waiting";
}

bool DwayneStage::validateStage()
{
	return game_win;
}
void DwayneStage::update(const rapidjson::Value &req)
{
	std::string field = req[REQ_FIELD_INDEX].GetString();
	if (field.compare("action") == 0)
	{
		const std::string action = req[REQ_VALUE_INDEX].GetString();
		handleMove(action);
	}
	else if (field.compare("hover") == 0)
	{
		const int hover = std::stoi(req[REQ_VALUE_INDEX].GetString());
		// hover: 0 | 1 | 2 | 3 (0 = no hover, 1,2,3 = rock, paper, scissors)
		if (hover == 0)
			face = getFacePath(neutral_faces[0]);
		else
			face = getFacePath(reaction_faces[hover - 1]);
		return;
	}
}

rapidjson::Value DwayneStage::getFieldStates(rapidjson::Document::AllocatorType &allocator)
{
	rapidjson::Value state(rapidjson::kObjectType);

	rapidjson::Value faceValue(face.c_str(), allocator);
	state.AddMember("face", faceValue, allocator);

	rapidjson::Value topTextValue(top_text.c_str(), allocator);
	state.AddMember("topText", topTextValue, allocator);

	rapidjson::Value bottomTextValue(bottom_text.c_str(), allocator);
	state.AddMember("bottomText", bottomTextValue, allocator);

	state.AddMember("gameOver", game_over, allocator);
	state.AddMember("gameWon", game_win, allocator);

	state.AddMember("iteration", iteration, allocator);
	state.AddMember("round", round, allocator);

	rapidjson::Value tempData(rapidjson::kObjectType);
	{
		tempData.AddMember("timeout", timemout_ms, allocator);

		rapidjson::Value tempSoundValue(temp_sound.c_str(), allocator);
		tempData.AddMember("sound", tempSoundValue, allocator);

		rapidjson::Value tempFaceValue(temp_face.c_str(), allocator);
		tempData.AddMember("face", tempFaceValue, allocator);
	}
	state.AddMember("tempData", tempData, allocator);

	return state;
}