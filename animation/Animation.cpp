#include "Animation.h"

// constructor
Animation::Animation(const AnimationInfo& info):
    mInfo(&info)
{}

// set current animation frame based on time
sf::Time Animation::update(const sf::Time& time) {
    sf::Time remainingTime = sf::Time::Zero;
    auto initialFrameIndex = mCurrentFrameIndex;
    auto frameIncrement = mInfo->speed * time.asSeconds() + mFrameDebt;
    mCurrentFrameIndex += int(frameIncrement);
    mFrameDebt = frameIncrement - int(frameIncrement);
    if(mCurrentFrameIndex >= getFramesNum()){
        if(mInfo->isLooping){
            mCurrentFrameIndex %= getFramesNum();
            remainingTime = sf::Time::Zero;
        }
        else{
            mIsDone = true;
            remainingTime = sf::seconds(time.asSeconds() - float(mCurrentFrameIndex - initialFrameIndex) / mInfo->speed);
        }
    }
    return remainingTime;
}
