#ifndef RESOURCES_H_
#define RESOURCES_H_

#include "checkML.h"
#include "Texture.h"
#include "Font.h"
#include "Music.h"
#include "SoundEffect.h"
#include <vector>
#include <tuple>

class SDLGame;
class Resources {
public:
	// in this part we define the enums for the resources, and the
	// corresponding data to be used to create them. The enums are simple
	// used to make access readable ...

	// Images -- each image file is loaded as an instance of Texture
	//
	enum ImageId {
	};

	// Text Messages - each is loaded as an instance of a texture
	enum TextId {
		HelloWorld, PresAnyKey, GameOver
	};

	// Fonts -- they are pair of filename and size, each is loaded as
	// an instance of Font
	//
	enum FontId {
		ARIAL16, ARIAL24, NESChimera16, NESChimera24, CaptureIt16, CaptureIt24
	};


	// Music -- each file is loaded as an instance of Music
	//
	enum MusicId {
		MENU
	};


	// Sound Effects -- each file is loaded as an instance of SoundEffect
	//
	enum SoundEffectId {
	};

private:

	struct TextMsgInfo {
		string text;
		SDL_Color color;
		FontId fontId;
	};

	struct FontInfo {
		string fileName;
		int size;
	};

	static vector<string> imageFiles_; // initialized in .cpp
	static vector<TextMsgInfo> textMsgs_; // initialized in .cpp
	static vector<FontInfo> fontFiles_; // initialized in .cpp
	static vector<string> musicFiles_; // initialized in .cpp
	static vector<string> soundEffectFiles_; // initialized in .cpp


public:

	Resources(SDLGame* game);
	virtual ~Resources();


	Texture* getImageTexture(ImageId i) const;
	Texture* getTextTexture(TextId i) const;
	Font* getFont(FontId i) const;
	Music* getMusic(MusicId i) const;
	SoundEffect* getSoundEffect(SoundEffectId i) const;

private:
	void setImageTextures(vector<string> textures);
	void setTextTextures(vector<TextMsgInfo> texts);
	void setFonts(vector<FontInfo> fonts);
	void setMusic(vector<string> music);
	void setSoundEffects(vector<string> soundEffects);

	void closeImageTextures();
	void closeTextTextures();
	void closeFonts();
	void closeMusic();
	void closeSoundEffects();

	SDLGame* game_;

	int numOfImageTextures_;
	Texture** imageTextures_;

	int numOfTextTextures_;
	Texture** textTextures_;

	int numOfFonts_;
	Font** fonts_;

	int numOfMusic_;
	Music** music_;

	int numOfSoundEffects_;
	SoundEffect** soundEffects_;
};

#endif /* RESOURCES_H_ */
