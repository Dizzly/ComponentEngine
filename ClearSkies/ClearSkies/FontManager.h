#ifndef FONTMANAGER_H_INCLUDED
#define FONTMANAGER_H_INCLUDED
#include <Singleton.h>
#include <NonCopyable.h>
#include <BitmapFontUI.h>
#include <BitmapFont.h>
#include <map>

class FontManager;
typedef Singleton<FontManager> TheFontManager;
class FontManager
{
public:
	bool AddBitFont(const std::string& file,const std::string& name,int size);
	bool AddBitUIFont(const std::string& file,const std::string& name, int size);
	BitmapFont* GetBitFont(const std::string&);
	BitmapFontUI* GetBitUIFont(const std::string&);

private:
	FontManager();
	friend TheFontManager;
private:
	typedef std::map<std::string,BitmapFont> BitFontMap;
	typedef std::map<std::string,BitmapFontUI> BitFontUIMap;
	BitFontMap bitFontMap_;
	BitFontUIMap bitFontUIMap_;
};

#endif