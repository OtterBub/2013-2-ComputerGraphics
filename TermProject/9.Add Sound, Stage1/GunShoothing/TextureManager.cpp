#include "TextureManager.h"

bool TextureManager::drawTextureBegin(int index) {
	if(m_textures[index] == NULL) {
		return false;
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_textures[index]);

	return true;
}

void TextureManager::drawAutoMapping(int mappingmode) {
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, mappingmode);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, mappingmode);
}

void TextureManager::drawTextureEnd() {
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_2D);
}