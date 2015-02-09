#ifndef LOADLEVEL_H_INCLUDED
#define LOADLEVEL_H_INCLUDED

#include <string>
class File;
bool LoadLevel(const std::string& levelFileName);
bool LoadLevel(File*);

#endif