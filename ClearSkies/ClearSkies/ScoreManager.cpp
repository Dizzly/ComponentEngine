#include "ScoreManager.h"
#include <vector>
#include <assert.h>
#include <ReportError.h>
#include <algorithm>

ScoreManager::ScoreManager()
{currentScore_=0;
scoreStanding_=scores_.begin();}

void ScoreManager::AddScore(int score)
{
	currentScore_+=score;
	while(currentScore_>scoreStanding_->first)
	{
		++scoreStanding_;
		if(scoreStanding_==scores_.end())
		{
		--scoreStanding_;
		break;
		}
	}

}

void ScoreManager::ClearScore()
{
	currentScore_=0;
	scoreStanding_=scores_.begin();
}
void ScoreManager::MinusScore(int score)
{
	currentScore_-=score;
	ScoreList::iterator it=scoreStanding_;
	--it;
	while(currentScore_<it->first&&it!=scores_.begin())
	{
		scoreStanding_=it;
		--it;
	}
}

int ScoreManager::GetCurrentScore()
{
	return currentScore_;
}

int ScoreManager::GetHighScore()
{
	if(currentScore_>(--scores_.cend())->first)
	{
		return currentScore_;
	}
	return (--scores_.end())->first;
}

void ScoreManager::SaveScore(const std::string& tag)
{
	scores_.insert(scoreStanding_,Score(currentScore_,tag));
	currentScore_=0;
	scoreStanding_=scores_.begin();
}

void ScoreManager::Load()
{
	std::string read;
	ScoreList temp;
	std::vector<bool> scoreLoad;
	scoreLoad.resize(10);
	int numOfScores=0;
	bool corruption=false;
	File file;
	scoreFilename_="Config/Scores.txt";
	if(!file.OpenRead(scoreFilename_))
	{
		ReportError(std::string("Score file "+file.GetFileName()+
				" is corrupt, will use and default scores"));
		numOfScores=scoreLoad.size();
			corruption=true;
	}
	while(numOfScores<scoreLoad.size())
	{
		std::string tag;
		int score;
		bool tagCheck=false,scoreCheck=false;

		tagCheck=file.GetString(&tag);
		scoreCheck=file.GetInteger(&score);

		scoreLoad[numOfScores]=tagCheck&&scoreCheck;
		if(!scoreLoad[numOfScores])
		{
			ReportError(std::string("Score file "+file.GetFileName()+
				" is corrupt, will use and default scores"));
			corruption=true;
			break;
		}

		temp.push_front(Score(score,tag));
		++numOfScores;
	}
	if(corruption||temp.size()==0)
	{
		scoreLoad.clear();
		scoreLoad.resize(10);
		temp.clear();
		for(int i=0;i<scoreLoad.size();++i)
		{
			temp.push_back(Score((i*1000)+1000,"BOT"));
		}
		scores_=temp;
		WriteScores();
	}
	scores_=temp;
	currentScore_=0;
	scoreStanding_=scores_.begin();
}

void ScoreManager::WriteScores()
{
	File file;
	int maxScores=9;
	int pos=maxScores;
	if(file.OpenWrite(scoreFilename_))
	{
		for(ScoreList::reverse_iterator it=scores_.rbegin();
			pos>=0;
			++it)
		{
			file.WriteString(it->second);
			file.WriteInt(it->first);
			--pos;
		}
	}

}