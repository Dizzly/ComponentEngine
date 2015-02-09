#ifndef SKYBOX_H_INCLUDED
#define SKYBOX_H_INCLUDED
#include <string>
#include "Texture.h"
#include "Singleton.h"
#include "NonCopyable.h"
class Skybox;
typedef Singleton<Skybox> TheSkybox;

class Skybox: public NonCopyable
{
public:
	
	bool Load(const std::string& filename, const std::string& filetype, float size);
	~Skybox();
	void Draw();
private:
	Skybox();
	friend TheSkybox;
	float size_;
	Texture texFront_,
		texRight_,
		texBack_,
		texLeft_,
		texUp_,
		texDown_;
};

#endif