#pragma once

#include <cassert>
#include <array>
#include <optional>

#include <SFML/Graphics.hpp>

#include "Button.h"

namespace gr {

class PictureBox;

class Clip {
	public:
		template <typename T> using FrameArray = std::array<std::optional<sf::Rect<T>>,
												 			CLICKST_MAX>;

		Clip(Button& button, const sf::Texture& texture);
		Clip(Button& button, const sf::Texture& texture, Orientation orientation,
	  	     std::initializer_list<CLICKSTATUS> states);
		Clip(Button& button, const sf::Texture& texture, const FrameArray<int>& textureFrames);

		void operator()(Button& button) const;

	private:
		PictureBox* mPictureBox = nullptr; 

		FrameArray<int> mTextureFrames;

		sf::IntRect pickTextureFrame(CLICKSTATUS clickStatus) const;
};

}
