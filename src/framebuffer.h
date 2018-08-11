#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_

#include "debug.h"
#include "opengl.h"

class FrameBuffer {
public:
	FrameBuffer(): mCreated(false) {}
	FrameBuffer(int width, int height, int col, bool depth) { create(width, height, col, depth); }
	~FrameBuffer() { destroy(); }
	
	void create(int width, int height, int col, bool depth);
	void destroy();
	
	int size() { return mSize; }
	bool created() { return mCreated; }

	void bindBuffer(int index);
	void bind();
	void unbind() {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glDrawBuffer(GL_BACK);
		glReadBuffer(GL_BACK);
	}

	void bindColorTextures(int startNumber) {
		for (int i = 0; i < mColorAttachCount; i++) {
			glActiveTexture(GL_TEXTURE0 + startNumber + i);
			glBindTexture(GL_TEXTURE_2D, mColorTextures[i]);
		}
		glActiveTexture(GL_TEXTURE0);
	}

	void bindDepthTexture(int number) {
		if (mDepthAttach) {
			glActiveTexture(GL_TEXTURE0 + number);
			glBindTexture(GL_TEXTURE_2D, mDepthTexture);
		}
		glActiveTexture(GL_TEXTURE0);
	}

private:
	int mSize, mColorAttachCount;
	bool mCreated, mDepthAttach;
	
	GLuint mID, mColorTextures[16], mDepthTexture;
};

#endif // !FRAMEBUFFER_H_
