
#include "stdafx.h"
#include "event.h"
#include "ui.h"
#include "input.h"

void adv::cEventMain::handle(sf::Event eventPoll, sf::RenderWindow* winHandle)
{
	vector<cUIElement*> elements;
	/*
	// Mouse button press
	*/
	if (eventPoll.type == sf::Event::MouseButtonPressed) {
		// Creating L0 event
		add(EVENT_MOUSE_PRESS, cEventArgs(eventPoll.mouseButton.button, sf::Mouse::getPosition(*winHandle)), FAMILY_GENERIC);
		// UI buttons - L1 event
		elements = advUI.findByPoint(vec2f((float)eventPoll.mouseButton.x, (float)eventPoll.mouseButton.y), TYPE_BUTTON, FND_EX_HIDDEN);
		// Button press
		if (elements.size() > 0) {
			for (int i = 0; i < (int)elements.size(); i++) {
				add(EVENT_UIBTN_PRESS, cEventArgs(eventPoll.mouseButton.button, elements[i]->getButtonName()));
			}
			advUI.__pressedUIButtons = elements;
		}
		// Empty press
		else {
			add(EVENT_NOBTN_PRESS, cEventArgs(eventPoll.mouseButton.button));
		}
	}
	/*
	// Mouse button release
	*/
	else if (eventPoll.type == sf::Event::MouseButtonReleased) {
		// Creating L0 event
		add(EVENT_MOUSE_RELEASE, cEventArgs(eventPoll.mouseButton.button, sf::Mouse::getPosition(*winHandle)), FAMILY_GENERIC);
		// UI buttons - L1 event
		if ((int)advUI.__pressedUIButtons.size() > 0) {
			// Button release
			for (int i = 0; i < (int)advUI.__pressedUIButtons.size(); i++) {
				add(EVENT_UIBTN_RELEASE, cEventArgs(eventPoll.mouseButton.button, advUI.__pressedUIButtons[i]->getButtonName()));
			}
			advUI.__pressedUIButtons.clear();
		}
		else {
			// Empty release
			add(EVENT_NOBTN_RELEASE, cEventArgs(eventPoll.mouseButton.button));
		}
	}
	/*
	// Mouse move
	*/
	else if (eventPoll.type == sf::Event::MouseMoved) {
		vec2i mousePos = sf::Mouse::getPosition(*winHandle);
		// L0 event
		add(EVENT_MOUSE_MOVE, cEventArgs(-1, mousePos), FAMILY_GENERIC);
		// UI buttons - L1 event
		// Find new buttons
		elements = advUI.findByPoint(vec2f((float)mousePos.x, (float)mousePos.y), TYPE_BUTTON);
		for (int i = 0; i < (int)elements.size(); i++) {
			// The element is new
			auto iter = find(advUI.__hoveredUIButtons.begin(), advUI.__hoveredUIButtons.end(), elements[i]);
			if (iter == advUI.__hoveredUIButtons.end()) {
				add(EVENT_UIBTN_HOVER, elements[i]->getButtonName());
				elements[i]->_setButtonFadeCur(elements[i]->getButtonFadeMax());
			}
			// The element is old
			else {
				advUI.__hoveredUIButtons.erase(iter, iter + 1);
			}
		}
		// Elements are not hovered anymore
		for (int i = 0; i < (int)advUI.__hoveredUIButtons.size(); i++) {
			//advUI.__hoveredUIButtons[i]->_setButtonHover(false);
			add(EVENT_UIBTN_NOHOVER, advUI.__hoveredUIButtons[i]->getButtonName());
			advUI.__fadeoutUIButtons.push_back(advUI.__hoveredUIButtons[i]);
		}
		advUI.__hoveredUIButtons = elements;
	}
	/*
	// Keyboard key press
	*/
	else if (eventPoll.type == sf::Event::KeyPressed) {
		// L0 event
		add(EVENT_KEY_PRESS, cEventArgs(eventPoll.key.code), FAMILY_GENERIC);
	}
	/*
	// Keyboard key release
	*/
	else if (eventPoll.type == sf::Event::KeyReleased) {
		// L0 event
		add(EVENT_KEY_RELEASE, cEventArgs(eventPoll.key.code), FAMILY_GENERIC);
	}
	/*
	// Text input
	*/
	else if (eventPoll.type == sf::Event::TextEntered) {
		// Text input - L0 event
		bool val = advInput.add(eventPoll.text.unicode);
		if (val) {
			add(EVENT_INPUT_ADD, cEventArgs(eventPoll.text.unicode), FAMILY_GENERIC);
		}
		else if (advInput.__isOpen()) {
			add(EVENT_INPUT_WRONG, cEventArgs(eventPoll.text.unicode), FAMILY_GENERIC);
		}
	}
	/*
	// Main window close
	*/
	else if (eventPoll.type == sf::Event::Closed) {
		advCore.exit();
	}
}