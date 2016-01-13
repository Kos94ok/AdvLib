
#include "core.h"

namespace adv
{
	class cTexture
	{
	public:
		string name;
		sf::Texture handle;
	};

	class cTextureMain
	{
	private:
		sf::Mutex access;
		vector<cTexture> dataList;
	public:
		int add(string name);
		sf::Texture* getHandle(int id);
	};
}

extern adv::cTextureMain advTexture;