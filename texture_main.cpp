
#include "stdafx.h"
#include "texture.h"

adv::cTextureMain advTexture;

int adv::cTextureMain::add(string name)
{
	int retVal;
	access.lock();
	// Check for duplicates
	for (int i = 0; i < (int)dataList.size(); i++) {
		if (dataList[i].name == name) { access.unlock(); return i; }
	}
	// Add new
	string path = advValue.path_textures + name;
	cTexture newTexture;
	newTexture.name = name;
	if (!newTexture.handle.loadFromFile(path)) { access.unlock(); return MISSINGNO; }
	dataList.push_back(newTexture);
	retVal = dataList.size() - 1;

	access.unlock();
	return retVal;
}

sf::Texture* adv::cTextureMain::getHandle(int id)
{
	if (id == MISSINGNO)
	{
		advException.crash(CRASH::BADINDEX);
		return nullptr;
	}
	return &dataList[id].handle;
}