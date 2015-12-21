
#include "stdafx.h"
#include "ui.h"
#include "texture.h"

void adv::cUIMain::paint(sf::RenderTexture* texHandle)
{
	for (int i = 0; i < (int)__childWindow.size(); i++) {
		__childWindow[i].paint(texHandle);
	}
}

void adv::cUIWindow::paint(sf::RenderTexture* texHandle)
{
	if (__hidden) { return; }
	for (int i = 0; i < (int)__childElement.size(); i++) {
		if (__childElement[i].isShown()) {
			__childElement[i].paint(texHandle, sf::Transform());
		}
	}
	for (int i = 0; i < (int)__childWindow.size(); i++) {
		__childWindow[i].paint(texHandle);
	}
}

void adv::cUIElement::updateBrush()
{
	if (!_toShow) { return; }

	if (type == TYPE_IMAGE) { brushShape = SHAPE_RECT; }
	else if (type == TYPE_LABEL) { brushShape = SHAPE_TEXT; }
	else if (type == TYPE_BUTTON) { brushShape = SHAPE_RECT | SHAPE_TEXT | SHAPE_OVERLAY; }

	cDrawable::updateBrush();

	if (type == TYPE_IMAGE) {
		// Main brush
		brushRect.setPosition(math.round(pos()));
		brushRect.setSize(size());

		// Origin
		vec2f origin;
		if (__image_align & ALIGN_CENTER) { origin.x = (float)math.round(size().x / 2.00f); }
		else if (__image_align & ALIGN_RIGHT) { origin.x = (float)math.round(size().x); }
		if (__image_align & ALIGN_MID) { origin.y = (float)math.round(size().y / 2.00f); }
		else if (__image_align & ALIGN_BOT) { origin.y = (float)math.round(size().y); }
		brushRect.setOrigin(origin);
	}
	if (type == TYPE_LABEL) {
		// Main brush
		brushText.setPosition(math.round(pos()));
		brushText.setFont(advUI.getFont(__label_fontIndex)->handle);
		brushText.setCharacterSize(advUI.getFont(__label_fontIndex)->size);
		brushText.setString(sf::String(__label_text));
		brushText.setColor(__label_color);

		// Origin
		sf::FloatRect bounds = brushText.getLocalBounds();
		bounds.height = 26;
		vec2f origin;
		if (__label_align & ALIGN_LEFT) { origin.x = 0.00f; }
		else if (__label_align & ALIGN_CENTER) { origin.x = (float)math.round(bounds.width / 2.00f); }
		else if (__label_align & ALIGN_RIGHT) { origin.x = (float)math.round(bounds.width); }
		if (__label_align & ALIGN_TOP) { origin.y = 0.00f; }
		else if (__label_align & ALIGN_MID) { origin.y = (float)math.round(bounds.height / 2.00f); }
		else if (__label_align & ALIGN_BOT) { origin.y = (float)math.round(bounds.height); }
		brushText.setOrigin(origin);
	}
	if (type == TYPE_BUTTON) {
		// Main brush
		brushRect.setPosition(math.round(pos()));
		brushRect.setSize(size());
		// Origin
		brushRect.setOrigin(center());
		brushRectOver.setOrigin(center());
		// Texture check
		if (_texture == MISSINGNO) {
			brushRect.setSize(vec2f(0, 0));
		}

		// Overlay brush
		brushRectOver = brushRect;
		if (__button_hoverTex != MISSINGNO) {
			brushRectOver.setSize(size());
			brushRectOver.setFillColor(color(255, 255, 255, (int)((float)__button_fadeCur / (float)__button_fadeMax * 255)));
		}

		// Text brush
		brushText.setPosition(math.round(pos()));
		brushText.setFont(advUI.getFont(__label_fontIndex)->handle);
		brushText.setCharacterSize(advUI.getFont(__label_fontIndex)->size);
		brushText.setString(sf::String(__label_text));
		float fadeVal = (float)__button_fadeCur / (float)__button_fadeMax;
		brushText.setColor(
			color(
				math.round(__label_color.r * (1 - fadeVal) + __button_hoverTextColor.r * fadeVal),
				math.round(__label_color.g * (1 - fadeVal) + __button_hoverTextColor.g * fadeVal),
				math.round(__label_color.b * (1 - fadeVal) + __button_hoverTextColor.b * fadeVal)
			));

		sf::FloatRect bounds = brushText.getLocalBounds();
		bounds.height = 26;
		vec2f origin = center();
		if (__label_align & ALIGN_CENTER) { origin.x += (float)math.round(bounds.width / 2.00f) - (float)math.round(size().x / 2.00f); }
		else if (__label_align & ALIGN_RIGHT) { origin.x += (float)math.round(bounds.width) - size().x; }
		if (__label_align & ALIGN_MID) { origin.y += (float)math.round(bounds.height) - (float)math.round(size().y / 2.00f); }
		else if (__label_align & ALIGN_BOT) { origin.y += (float)math.round(bounds.height * 2) - size().y; }
		brushText.setOrigin(origin);
	}
}

void adv::cUIElement::updateBrushPrepaint()
{
	adv::cDrawable::updateBrushPrepaint();

	if (brushShape & SHAPE_OVERLAY) {
		if (__button_hoverTex != MISSINGNO) { brushRectOver.setTexture(advTexture.getHandle(__button_hoverTex), true); }
		else { brushRectOver.setTexture(0, true); }
	}
}