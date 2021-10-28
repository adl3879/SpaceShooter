#include "LevelOne.h"
#include "LevelFactory.h"

static LevelRegistrar<LevelOne> registrar( "one" );

LevelOne::LevelOne()
{
    SDL_Log("level manager works!");
}

void LevelOne::Draw()
{

}

void LevelOne::Update( float dt )
{

}

void LevelOne::Clean()
{

}
