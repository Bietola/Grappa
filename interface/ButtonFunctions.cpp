#include "ButtonFunctions.h"

#include "PictureBox.h"

//Clip
gr::Clip::Clip(Button& button, const sf::Texture& texture):
	Clip(
		button,
		texture,
		[size = texture.getSize()] {
			float xs = size.x / CLICKST_MAX;
			float ys = size.y;
			FrameArray<int> retVal;
			std::generate(begin(retVal), end(retVal), [j = 0, &xs, &ys] () mutable {
				return sf::IntRect(xs * j++, 0, xs, ys);
			});
			return retVal;
		}()
	)
{}

gr::Clip::Clip(Button& button, const sf::Texture& texture, Orientation orientation,
			   std::initializer_list<CLICKSTATUS> states):
	Clip(
		button,
		texture,
		[&states, &orientation, ts = texture.getSize()] {
			FrameArray<int> frames;
			std::function<sf::IntRect(size_t)> makeFrame; 
			if(orientation == Orientation::Horizontal) {
				makeFrame = [&ts, frdim = ts.x / states.size()] (size_t indx) {
					return sf::IntRect(frdim * indx, 0, frdim, ts.y);
				};
			}
			else {
				makeFrame = [&ts, frdim = ts.x / states.size()] (size_t indx) {
					return sf::IntRect(0, frdim * indx, ts.x, frdim);
				};
			}
			size_t j = 0;
			for(const auto& ele : states) {
				frames[int(ele)] = makeFrame(j++);
			}
			return frames;
		}()
	)
{}

gr::Clip::Clip(Button& button, const sf::Texture& texture,
			   const FrameArray<int>& textrFrames):
	mTextureFrames(textrFrames)
{
	mPictureBox = &button.addRelative<gr::PictureBox>("_clip", sf::FloatRect(0, 0, 1, 1), texture, mTextureFrames[0].value());
}

void gr::Clip::operator()(Button& button) const {
	assert(mPictureBox);
	mPictureBox->setTextureRect(pickTextureFrame(button.getClickStatus()));
}

sf::IntRect gr::Clip::pickTextureFrame(gr::CLICKSTATUS clickStatus) const {
	return mTextureFrames[int(clickStatus)].value_or(mTextureFrames[gr::CLICKST_DEFAULT].value());
}
