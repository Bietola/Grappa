#pragma once

#include <SFML/Graphics.hpp>

class GameState {
    public:
        // constructor
        GameState(sf::RenderWindow& window): mWindow(&window) {}

        // virtual destructor
        virtual ~GameState() {}

        // deallocate given gstate and change it to point to the next one
        static void change(GameState*& gstate);

        /// setters
        // sets next gstate only if current next gstate is null
        // returns success
        bool setNext(GameState* gstate);

        /// interface functions
        // handle user event
        virtual void handleEvent(const sf::Event& e) = 0;
        // handle logical operations
        virtual void handleLogic(const sf::Time& time) = 0;
        // draw interface
        virtual void handleDrawing() const = 0;

    protected:
        // window on which the interface is shown
        sf::RenderWindow* mWindow;

    private:
        // next gstate to be used
        static GameState* mNext;
};
