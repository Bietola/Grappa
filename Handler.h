#pragma once

#include <SFML/Graphics.hpp>

///Handler base class
class Handler{
    public:
        // constructor
        Handler(sf::RenderWindow& window): mWindow(&window) {}

        // virtual destructor
        virtual ~Handler() {}

        // deallocate given handler and change it to point to the next one
        static void change(Handler*& handler);

        /// setters
        // sets next handler only if current next handler is null
        // returns success
        bool setNext(Handler* handler);

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
        // next handler to be used
        static Handler* mNext;
};
