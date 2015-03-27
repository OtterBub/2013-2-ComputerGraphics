#include "TextureManager.h"

bool TextureManager::drawTextureBegin(int index) {
	if(m_textures[index] == NULL) {
		return false;
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_textures[index]);

	return true;
}

void TextureManager::drawTextureEnd() {
	glDisable(GL_TEXTURE_2D);
}