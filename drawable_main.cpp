
#include "stdafx.h"
#include "drawable.h"
#include "texture.h"

void adv::cDrawable::updateBrush()
{
	if (brushShape & SHAPE_RECT) {
		brushRect.setSize(size());
		brushRect.setPosition(pos());
		brushRect.setOrigin(center());
		brushRect.setRotation(angle());
		brushRect.setFillColor(color(255, 255, 255));
	}
	if (brushShape & SHAPE_TEXT) {
		brushText.setPosition(pos());
	}
}

void adv::cDrawable::updateBrushPos()
{
	if (brushShape & SHAPE_RECT) {
		brushRect.setPosition(pos());
	}
	if (brushShape & SHAPE_TEXT) {
		brushText.setPosition(pos());
	}
}

void adv::cDrawable::updateBrushPrepaint()
{
	if (brushShape & SHAPE_RECT) {
		// Updating texture pointer
		if (_texture != MISSINGNO) { brushRect.setTexture(advTexture.getHandle(_texture), true); }
		else { brushRect.setTexture(0, true); }
	}
}

void adv::cDrawable::paint(sf::RenderTexture* target, sf::Transform matrix)
{
	_begin();
	updateBrushPrepaint();
	if (brushShape & SHAPE_RECT) {
		target->draw(brushRect, matrix);
	}
	if (brushShape & SHAPE_OVERLAY) {
		target->draw(brushRectOver, matrix);
	}
	if (brushShape & SHAPE_TEXT) {
		target->draw(brushText, matrix);
	}
	if (brushShape & SHAPE_OVERLAY) {
		target->draw(brushTextOver, matrix);
	}
	_end();
}

void adv::cDrawable::_begin()
{
	while (_state != MUTEX_FREE) { Sleep(1); }
	_state = MUTEX_LOCK;
}

void adv::cDrawable::_end()
{
	_state = MUTEX_FREE;
}