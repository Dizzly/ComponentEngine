#ifndef LOADLEVEL_H_INCLUDED
#define LOADLEVEL_H_INCLUDED
#include <string>
class File;
bool LoadLevel(File* level);
bool LoadLevel(const std::string& filename);
bool LoadTemplates(std::string& name);

#endif 