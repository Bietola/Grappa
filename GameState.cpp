#include "GameState.h"

#include <cassert>

/// GameState static variables
// next gstate to be set by change function
GameState* GameState::mNext = nullptr;

/// GameState functions
// change gstate (static)
void GameState::change(GameState*& gstate)
{
    assert(gstate);
    if(mNext != nullptr)
    {
        delete gstate;
        gstate = mNext;
        mNext = nullptr;
    }
}
// set next gstate - return false on failure
bool GameState::setNext(GameState* gstate)
{
    if(mNext != nullptr || gstate == nullptr)
        return false;
    mNext = gstate;
    return true;
}
