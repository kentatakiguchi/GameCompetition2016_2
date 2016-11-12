#include "FontManager.h"

FontManager::FontManager()
{
	int size = 100;
	fontData_[LoadingFont] = CreateFontToHandle(NULL, size, 10);
	fontSize_[LoadingFont] = size;
	size = 64;
	fontData_[TitleFont] = CreateFontToHandle(NULL, size, 10);
	fontSize_[TitleFont] = size;
	size = 50;
	fontData_[GamePlayFont] = CreateFontToHandle(NULL, size, 1);
	fontSize_[GamePlayFont] = size;
}

FontManager & FontManager::GetInstance()
{
	static FontManager instance;
	return instance;
}

int FontManager::ChangeFont(FontName targetFont)
{
	return fontData_[targetFont];
}

int FontManager::GetFontSize(FontName targetFont)
{
	return fontSize_[targetFont];
}

