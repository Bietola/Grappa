#ifndef TEXTBOX_H_INCLUDED
#define TEXTBOX_H_INCLUDED

#include <cassert>

#include "Interface.h"

namespace gr {

///TextBox class
class TextBox: public InterfaceImpl<TextBox> {
    public:
        //structures
        struct TextInfo {
            std::string text;
            unsigned int charSize;
            const sf::Font* font;
			sf::Color color = sf::Color::White;
        };
        //constructor
        TextBox(const sf::FloatRect& bounds);
        TextBox(const sf::FloatRect& bounds, const sf::Font* font, unsigned int charSize);
        TextBox(const TextBox& other);
        //destructor
        ;
        //setters
        TextBox& setFont(const sf::Font* font) {mTextInfo.font = font; return *this;}
        TextBox& setCharacterSize(unsigned int size) {mTextInfo.charSize = size; return *this;}
		TextBox& setColor(const sf::Color& color) {mTextInfo.color = color; mNeedToUpdateVertices = true; return *this;} 
        //text editing functions
        TextBox& setText(const std::string& text);
        TextBox& addText(const std::string& text);
		TextBox& operator<<(const std::string& text) {addText(text); return *this;}
        /*!WIP
        void setTextSize(unsigned int textSize);
        */
    private:
        //variables
        TextInfo mTextInfo;
        mutable sf::VertexArray mVertices;
        mutable bool mNeedToUpdateVertices;
        //functions
        void parentDraw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}

#endif // TEXTBOX_H_INCLUDED
