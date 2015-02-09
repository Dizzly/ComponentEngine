#ifndef GAMEOBJECTFACTORY_H_INCLUDED
#define GAMEOBJECTFACTORY_H_INCLUDED
#include "Singleton.h"
#include "GameObject.h"
#include "Factory.h"

typedef Factory<GameObject> GameObjectFactory;
typedef Singleton<GameObjectFactory> TheGameObjectFactory;

#endif