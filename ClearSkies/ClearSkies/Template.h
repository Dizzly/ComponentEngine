#ifndef TEMPLATE_H_INCLUDED
#define TEMPLATE_H_INCLUDED
#include <string>
class Template
{
public:
virtual ~Template()=0;
virtual std::string GetFileName()const{}=0;
virtual std::string GetTypeName()const{}=0;
private:
}

#endif