
#pragma once

#include "core.h"

#define SHAPE_RECT					1
#define SHAPE_TEXT					2
#define SHAPE_OVERLAY				4

#define MUTEX_FREE					0
#define MUTEX_LOCK					1

namespace adv
{
	class cDrawable : public cID, public cFlags
	{
	private:
		vec2f _pos;
		vec2f _size;
		vec2f _center;
		float _angle = 0.f;
	protected:
		int _texture = -1;
		int brushShape = SHAPE_RECT;
		sf::Text brushText;
		sf::Text brushTextOver;
		sf::RectangleShape brushRect;
		sf::RectangleShape brushRectOver;

		void _begin();
		void _end();
		int _state = MUTEX_FREE;

		virtual void updateBrush(); 
		virtual void updateBrushPos();
		virtual void updateBrushPrepaint();
	public:
		vec2f pos() { return _pos; }																	// Get position
		vec2f size() { return _size; }																	// Get size
		vec2f center() { return _center; }																// Get origin point
		float angle() { return _angle; }																// Get rotation

		void move(vec2f offset) { _begin(); _pos += offset; updateBrush(); _end(); }					// Change position
		void moveto(vec2f newpos) { _begin(); _pos = newpos; updateBrush(); _end(); }					// Change position
		void rotate(float offset) { _begin(); _angle += offset; updateBrush(); _end(); }				// Change rotation
		void faceto(float angle) { _begin(); _angle = angle; updateBrush(); _end(); }					// Change rotation
		void resize(vec2f newsize) { _begin(); _size = newsize; updateBrush(); _end(); }				// Change size
		void centralize(vec2f newcenter) { _begin(); _center = newcenter; updateBrush(); _end(); }		// Change origin point
		void texturize(int texid) { _texture = texid; }													// Change texture

		void update() { _begin(); updateBrush(); _end(); }												// Force update brushes

		/*
		// Paint the object to the render texture.
		*/
		void paint(sf::RenderTexture* target, sf::Transform matrix = sf::Transform());
	};
}