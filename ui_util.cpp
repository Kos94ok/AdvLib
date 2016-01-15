
#include "stdafx.h"
#include "ui.h"
#include "texture.h"

void adv::cUIWindow::show(bbool val)
{
	val.apply(&__hidden);
	__hidden = !__hidden;
}

void adv::cUIWindow::addBorder(string idMask, vec2f bPos, vec2f bSize, string texMask)
{
	int idAstPos = idMask.find("*");
	int texAstPos = texMask.find("*");
	if (idAstPos == string::npos || texAstPos == string::npos) {
		advException.crash(WARNING::BADUIMASK, idMask + " | " + texMask);
		return;
	}
	string idPref = idMask.substr(0, idAstPos);
	string idPost = idMask.substr(idAstPos + 1);
	string texPref = texMask.substr(0, texAstPos);
	string texPost = texMask.substr(texAstPos + 1);

	vec2f brdSize = vec2f(4, 4);
	addImage(idPref + "lt" + idPost, vec2f(0, 0), brdSize, advTexture.add(texPref + "lt" + texPost));
	addImage(idPref + "top" + idPost, vec2f(brdSize.x, 0), vec2f(size.x - brdSize.x * 2, brdSize.y), advTexture.add(texPref + "top" + texPost));
	addImage(idPref + "rt" + idPost, vec2f(size.x - brdSize.x, 0), brdSize, advTexture.add(texPref + "rt" + texPost));
	addImage(idPref + "right" + idPost, vec2f(size.x - brdSize.x, brdSize.y), vec2f(brdSize.x, size.y - brdSize.y * 2), advTexture.add(texPref + "right" + texPost));
	addImage(idPref + "rb" + idPost, vec2f(size.x - brdSize.x, size.y - brdSize.y), brdSize, advTexture.add(texPref + "rb" + texPost));
	addImage(idPref + "bot" + idPost, vec2f(brdSize.x, size.y - brdSize.y), vec2f(size.x - brdSize.x * 2, brdSize.y), advTexture.add(texPref + "bot" + texPost));
	addImage(idPref + "lb" + idPost, vec2f(0, size.y - brdSize.y), brdSize, advTexture.add(texPref + "lb" + texPost));
	addImage(idPref + "left" + idPost, vec2f(0, brdSize.y), vec2f(brdSize.x, size.y - brdSize.y * 2), advTexture.add(texPref + "left" + texPost));
}

void adv::cUIWindow::addLabelOutline(string idMask, vec2f pos, wstring text, string fontId, color clr, int align)
{
	int idAstPos = idMask.find("*");
	if (idAstPos == string::npos) {
		idMask += "*";
		idAstPos = idMask.find("*");
	}
	string idPref = idMask.substr(0, idAstPos);
	string idPost = idMask.substr(idAstPos + 1);

	addLabel(idPref + "lt" + idPost, pos - vec2f(-1, -1), text, fontId, clr, align);
	addLabel(idPref + "top" + idPost, pos - vec2f(0, -1), text, fontId, clr, align);
	addLabel(idPref + "rt" + idPost, pos - vec2f(1, -1), text, fontId, clr, align);
	addLabel(idPref + "right" + idPost, pos - vec2f(1, 0), text, fontId, clr, align);
	addLabel(idPref + "rb" + idPost, pos - vec2f(1, 1), text, fontId, clr, align);
	addLabel(idPref + "bot" + idPost, pos - vec2f(0, 1), text, fontId, clr, align);
	addLabel(idPref + "lb" + idPost, pos - vec2f(-1, 1), text, fontId, clr, align);
	addLabel(idPref + "left" + idPost, pos - vec2f(-1, 0), text, fontId, clr, align);
}