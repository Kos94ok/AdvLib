
#pragma once

#include "core.h"
#include "drawable.h"

#define FND_NOFLAGS					0
#define FND_EX_HIDDEN				1

#define TYPE_IMAGE					0
#define TYPE_LABEL					1
#define TYPE_BUTTON					2				

namespace adv
{
	class cUIWindow;

	class cUIParent
	{
	protected:
		vector<cUIWindow> __childWindow;
	public:
		bool __root = false;
		vec2f pos;
		/*
		// Create a new virtual sub-window.
		Warning: Should only be used during initialization.
		*/
		cUIWindow* addWindow(string id, vec2f pos = vec2f(0.f, 0.f), vec2f size = vec2f(800.f, 600.f), int align = ALIGN_LEFT);
		/*
		// Find a window, if you have lost one.
		*/
		cUIWindow* getWindow(string id);
		/*
		// Move a child window to a new position.
		*/
		void moveChildWindow(string id, vec2f newPos);
	};

	class cUIElement : public cDrawable
	{
	private:
		bool _toShow = true;

		int __image_align;

		wstring __label_text;
		color __label_color;
		int __label_fontIndex;
		int __label_align;

		string __button_name;
		int __button_align;
		float __button_fadeCur;
		float __button_fadeMax;
		int __button_hoverTex;
		color __button_hoverTextColor;
	public:
		int type;
		string id;

		void show(bbool val) { _begin(); val.apply(&_toShow); updateBrush(); _end(); }
		void setImageTexture(int tex) {	_texture = tex; }
		void setImageAlign(int align) { _begin(); __image_align = align; updateBrush(); _end(); }
		void setLabelText(wstring text) { _begin(); __label_text = text; updateBrush(); _end(); }
		void setLabelColor(color clr) { _begin(); __label_color = clr; updateBrush(); _end(); }
		void setLabelFont(int fontIndex) { _begin(); __label_fontIndex = fontIndex;	updateBrush(); _end(); }
		void setLabelAlign(int align) { _begin(); __label_align = align; updateBrush();	_end(); }
		void setButtonName(string name) { __button_name = name; }
		void setButtonAlign(int align) { _begin(); __button_align = align; updateBrush(); _end(); }
		void setButtonTexture(int tex) { _texture = tex; }
		void setButtonTextString(wstring text) { _begin(); __label_text = text; updateBrush(); _end(); }
		void setButtonTextColor(color clr) { _begin(); __label_color = clr; updateBrush(); _end(); }
		void setButtonTextFont(int fontIndex) { _begin(); __label_fontIndex = fontIndex;	updateBrush(); _end(); }
		void setButtonTextAlign(int align) { _begin(); __label_align = align; updateBrush();	_end(); }
		void setButtonHoverTexture(int tex)	{ __button_hoverTex = tex; _end(); }
		void setButtonHoverFadeTime(float time) { setButtonFadeMax(time); }
		void setButtonHoverTextColor(color clr) { _begin(); __button_hoverTextColor = clr; updateBrush();	_end(); }
		void setButtonFadeMax(float val) { __button_fadeMax = max(0.001f, val); }
		void _setButtonFadeCur(float val) { _begin(); __button_fadeCur = val; updateBrush();	_end(); }

		bool isShown() { return _toShow; }
		string getButtonName() { return __button_name; }
		float getButtonFadeMax() { return __button_fadeMax; }
		float _getButtonFadeCur() { return __button_fadeCur; }

		void updateBrush();
		void updateBrushPrepaint();
	};

	class cUIWindow : public cUIParent, public cFlags
	{
	private:
		bool __hidden = false;
		vector<cUIElement> __childElement;

		cUIElement* _getElement(string id, int type);
	public:
		string id;
		vec2f size;
		/*
		// Is the window hidden.
		*/
		bool isHidden() { return __hidden; }
		/*
		// Move this window to an offset.
		*/
		void move(vec2f offset);
		/*
		// Show or hide this window and all the sub-windows.
		*/
		void show(bbool val);
		/*
		// Show or hide specified element.
		*/
		void showElement(string id, int type, bbool val);
		/*
		// Create a new image element.
		Warning: Should only be used during initialization.
		*/
		void addImage(string id, vec2f pos, vec2f size, int tex, int align = ALIGN_LEFT);
		/*
		// Create a new label element.
		Warning: Should only be used during initialization.
		*/
		void addLabel(string id, vec2f pos, wstring text, string fontId, color clr = color(0, 0, 0), int align = ALIGN_LEFT);
		/*
		// Create a new button element.
		Warning: Should only be used during initialization.
		*/
		void addButton(string id, vec2f pos, vec2f size, string name, int bgTex = -1, int align = ALIGN_LEFT);
		/*
		// Create a standard border for the window.
		Texture mask example: "ui_border_*.png"
		Warning: Should only be used during initialization.
		*/
		void addBorder(string idMask, vec2f bPos, vec2f bSize, string texMask);
		/*
		// Create an outline for the label text. Should be called before the actual label is created.
		ID mask example: "label*"
		Warning: Should only be used during initialization.
		*/
		void addLabelOutline(string idMask, vec2f pos, wstring text, string fontId, color clr = color(0, 0, 0), int align = ALIGN_LEFT);
		/*
		// Recursive search through all the windows to find elements by filter.
		*/
		vector<cUIElement*> findByPoint(vec2f point, int type, int flags = FND_NOFLAGS);
		vector<cUIElement*> findById(string name, int type, int flags = FND_NOFLAGS);
		vector<cUIElement*> findByName(string name, int type, int flags = FND_NOFLAGS);
		/*
		// Send paint signal to all child windows and elements.
		*/
		void paint(sf::RenderTexture* texHandle);

		void addButtonText(string id, wstring text, string fontIndex, color clr = color(0, 0, 0), int align = ALIGN_LEFT);
		void addButtonHover(string id, int texture, float time, color textColor = color(0, 0, 0));

		void setImagePos(string id, vec2f newPos);
		void setImageSize(string id, vec2f newSize);
		void setImageAlign(string id, int align);
		void setImageTexture(string id, int tex);
		void setLabelPos(string id, vec2f newPos);
		void setLabelText(string id, wstring text);
		void setLabelColor(string id, color clr);
		void setLabelFont(string id, int fontIndex);
		void setLabelAlign(string id, int align);
		void setButtonPos(string id, vec2f newPos);
		void setButtonSize(string id, vec2f newSize);
		void setButtonName(string id, string name);
		void setButtonAlign(string id, int align);
		void setButtonTexture(string id, int tex);
		void setButtonTextString(string id, wstring text);
		void setButtonTextColor(string id, color clr);
		void setButtonTextFont(string id, int fontIndex);
		void setButtonTextAlign(string id, int align);
		void setButtonHoverTexture(string id, int tex);
		void setButtonHoverFadeTime(string id, float time);
		void setButtonHoverTextColor(string id, color clr);

		vec2f getButtonPos(string id) { return _getElement(id, TYPE_BUTTON)->pos() - pos; }
	};

	class cUIFont
	{
	public:
		string id;
		bool isValid = false;

		int size;
		sf::Font handle;
	};

	class cUIMain : public cUIParent
	{
	private:
		vector<cUIFont> __font;
	public:
		vec2f desktopSize;
		vector<cUIElement*> __hoveredUIButtons;
		vector<cUIElement*> __pressedUIButtons;
		vector<cUIElement*> __fadeoutUIButtons;
		/*
		// Initialize the UI system.
		*/
		void init();
		/*
		// Search for elements.
		*/
		int getHoveredButtonCount();
		int getPressedButtonCount();
		vector<cUIElement*> findHoveredButtons();
		vector<cUIElement*> findPressedButtons();
		vector<cUIElement*> findByPoint(vec2f point, int type, int flags = FND_NOFLAGS);
		vector<cUIElement*> findById(string name, int type, int flags = FND_NOFLAGS);
		vector<cUIElement*> findByName(string name, int type, int flags = FND_NOFLAGS);
		/*
		// Create a new font database entry.
		*/
		int addFont(string id, string filename, int size);
		/*
		// Convert font id to index.
		*/
		int getFontIndex(string id);
		/*
		// Get font handle.
		*/
		cUIFont* getFont(int index);
		/*
		// Send paint signal to all the windows and elements.
		*/
		void paint(sf::RenderTexture* texHandle);
		/*
		// Check the font.
		Internal use only.
		*/
		bool _isFontValid(int index);
	};

	// Main function
	void threadUIMain(int id, cArgs args);
}

extern adv::cUIMain advUI;