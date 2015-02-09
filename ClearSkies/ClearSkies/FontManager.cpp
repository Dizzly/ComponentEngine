#include "FontManager.h"

FontManager::FontManager()
{}

bool FontManager::AddBitFont(const std::string& file,const std::string& name,int size)
{
	if(bitFontMap_[name].Load(file,size,size,1))
	{
	// the reason I leave this open is because some extended error checking may want to happen
	// the alternative is I just return the .Load()
	return true;
	}
	return false;
}

bool FontManager::AddBitUIFont(const std::string& file, const std::string& name, int size)
{
	if(bitFontUIMap_[name].Load(file,size,size,1))
	{
	return true;
	}
	return false;
}

BitmapFont* FontManager::GetBitFont(const std::string& str)
{
	return &bitFontMap_[str];
}

BitmapFontUI* FontManager::GetBitUIFont(const std::string& str)
{
	return &bitFontUIMap_[str];
}