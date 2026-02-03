#include "FrameBuffer.h"

static uint32_t s_CurrentBoundFBO = 0;

Framebuffer::Framebuffer(int32_t width,
                         int32_t height,
                         bool createDepthAttachment,
                         int32_t colorAttachmentCount)
    : width(width),
      height(height) {

    glGenFramebuffers(1, &id);

    if (s_CurrentBoundFBO != id) {
        glBindFramebuffer(GL_FRAMEBUFFER, id);
        s_CurrentBoundFBO = id;
    }

    if (createDepthAttachment) {
        depthAttachment = std::make_shared<Texture>(
            GL_TEXTURE_2D,
            GL_DEPTH_COMPONENT,
            GL_DEPTH_COMPONENT,
            GL_FLOAT,
            false
        );

        depthAttachment->allocateTexture(width, height);

        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_DEPTH_ATTACHMENT,
            GL_TEXTURE_2D,
            depthAttachment->getId(),
            0
        );
    }

    for (int32_t i = 0; i < colorAttachmentCount; ++i) {
        Ref<Texture> attachment = std::make_shared<Texture>(
            GL_TEXTURE_2D,
            GL_RGBA16,
            GL_RGBA,
            GL_SHORT,
            false,
            0
        );

        attachment->allocateTexture(width, height);

        uint32_t attachmentName = GL_COLOR_ATTACHMENT0 + i;
        glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            attachmentName,
            GL_TEXTURE_2D,
            attachment->getId(),
            0
        );

        attachmentNames.push_back(attachmentName);
        attachments.push_back(attachment);
    }

    if (!attachmentNames.empty()) {
        glDrawBuffers(
            static_cast<int32_t>(attachmentNames.size()),
            attachmentNames.data()
        );
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    s_CurrentBoundFBO = 0;
}

Framebuffer::~Framebuffer() {
    if (id) {
        if (s_CurrentBoundFBO == id) {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            s_CurrentBoundFBO = 0;
        }
        glDeleteFramebuffers(1, &id);
    }
}

Ref<Texture> Framebuffer::getDepthAttachment() {
    return depthAttachment;
}

Ref<Texture> Framebuffer::getColorAttachment(int32_t index) {
    assert(index >= 0 && index < static_cast<int32_t>(attachments.size()));
    return attachments[index];
}

void Framebuffer::clearColorAttachment(int32_t index,
                                       const glm::vec4& value) {
    assert(index >= 0 && index < static_cast<int32_t>(attachments.size()));
    glClearBufferfv(GL_COLOR, index, &value.x);
}

void Framebuffer::bind(bool ) {
    if (s_CurrentBoundFBO != id) {
        glBindFramebuffer(GL_FRAMEBUFFER, id);
        s_CurrentBoundFBO = id;
    }
}

void Framebuffer::unbind() {
    if (s_CurrentBoundFBO != 0) {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        s_CurrentBoundFBO = 0;
    }
}
