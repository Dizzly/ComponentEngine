#ifndef SCOREMANAGER_H_INCLUDED
#define SCOREMANAGER_H_INCLUDED
#include <Singleton.h>
#include <NonCopyable.h>
#include <File.h>
#include <list>
class ScoreManager;
typedef Singleton<ScoreManager> TheScoreManager;
class ScoreManager:public NonCopyable
{
public:
	void AddScore(int score);
	int GetCurrentScore();
	int GetHighScore();
	void MinusScore(int score);
	void Load();
	void SaveScore(const std::string& tag);
	void WriteScores();
	void ClearScore();
public:
	typedef std::pair<int,std::string> Score;
	typedef std::list<Score> ScoreList;
private:
	ScoreManager();
	friend TheScoreManager;
	int currentScore_;
	ScoreList::iterator scoreStanding_;
	ScoreList scores_;
	std::string scoreFilename_;
};


#endif