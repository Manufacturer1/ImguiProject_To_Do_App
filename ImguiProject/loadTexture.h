#define STB_IMAGE_IMPLEMENTATION
#include <GL/gl3w.h>
#include "stb_image.h"


bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height) {
	int image_width = 0;
	int image_height = 0;
	int channels = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, &channels, 0);
	if (image_data == NULL) {
		fprintf(stderr, "Failed to load image: %s\n", filename);
		return false;
	}

	GLuint image_texture;
	glGenTextures(1, &image_texture);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		fprintf(stderr, "Error after glGenTextures: %d\n", error);
		stbi_image_free(image_data);
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, image_texture);
	error = glGetError();
	if (error != GL_NO_ERROR) {
		fprintf(stderr, "Error after glBindTexture: %d\n", error);
		stbi_image_free(image_data);
		return false;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLenum format = GL_RGB;
	if (channels == 1)
		format = GL_RED;
	else if (channels == 3)
		format = GL_RGB;
	else if (channels == 4)
		format = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, format, image_width, image_height, 0, format, GL_UNSIGNED_BYTE, image_data);
	error = glGetError();
	if (error != GL_NO_ERROR) {
		fprintf(stderr, "Error after glTexImage2D: %d\n", error);
		stbi_image_free(image_data);
		return false;
	}

	stbi_image_free(image_data);

	*out_texture = image_texture;
	*out_width = image_width;
	*out_height = image_height;

	return true;
}