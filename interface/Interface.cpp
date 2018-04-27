#include "Interface.h"

#include "PictureBox.h" //to remove
#include "TextBox.h" //to remove

///Interface functions
//copy constructor
gr::Interface::Interface(const Interface& other):
    TransBox(other),
    mChildInterfaces(),
    mParent(other.mParent),
    mIsActive(other.mIsActive),
    mMargins(other.mMargins)
{
    for(const auto& ele : other.mChildInterfaces)
        mChildInterfaces.insert({ele.first, ele.second->clone()});
}
//destructor
gr::Interface::~Interface() {
    for(auto& inter : mChildInterfaces) {
        delete inter.second;
    }
}
//handle event
void gr::Interface::handleEvent(const sf::Event& e) {
    if(isActive()) {
        //handle parent
        parentHandleEvent(e);
        //make all child inter.s handle events
        for(auto& inter : mChildInterfaces) {
            inter.second->handleEvent(e);
        }
    }
}
//handle logic
void gr::Interface::update(const sf::RenderWindow& window) {
    if(isActive()) {
        //handle parent
        parentUpdate(window);
        //make all child inter.s handle logic
        for(auto& inter : mChildInterfaces) {
            inter.second->update(window);
        }
    }
}
//draw interface and all of its child interfaces
void gr::Interface::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(isActive()){
        //draw parent and modify states for child nodes
        parentDraw(target, states);
        //apply parent transformation to render states for child nodes
        states.transform *= getTransform();
        //draw child inter.s
        for(const auto& inter : mChildInterfaces){
            inter.second->draw(target, states);
        }
    }
}
//set margins
gr::Interface& gr::Interface::setMargins(const sf::FloatRect& margins) {
    //set margins
    mMargins = margins;
    //transform margins according to parent
    const auto& parentBounds = getParent().getBounds();
    mMargins.left *= parentBounds.width;
    mMargins.top *= parentBounds.height;
    mMargins.width = -(parentBounds.width * mMargins.width) - mMargins.left;
    mMargins.height = -(parentBounds.height * mMargins.height) - mMargins.top;
    //update margins for parent
    mBounds = mBounds + mMargins;
    //update margins for all child nodes
    for(auto& inter : mChildInterfaces) {
        inter.second->setBounds(inter.second->getBounds() + mMargins);
    }
	//
	return *this;
}
