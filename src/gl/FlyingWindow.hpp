#ifndef FLYING_WINDOW_H
#define FLYING_WINDOW_H

#include <string>
#include <opencv2/opencv.hpp>
#include "Camera.hpp"
#include "Model.hpp"
#include "TextRenderer.hpp"

class FlyingWindow {
public:
    FlyingWindow(const Camera& camera, const Model& parentModel, const glm::vec3& offset, const std::string& text, const cv::Mat& image)
        : camera(camera), parentModel(parentModel), offset(offset), text(text), image(image) {
        init();
    }

    void render() {
        // Render quad with texture
        shader.use();
        shader.setMat4("projection", camera.GetProjectionMatrix());
        shader.setMat4("view", camera.GetViewMatrix());
        glm::mat4 model = glm::translate(parentModel.modelMatrix, offset);
        shader.setMat4("model", model);
        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);

        // Render text
        textRenderer.renderText(text, model);
    }

private:
    Camera camera;
    Model parentModel;
    glm::vec3 offset;
    std::string text;
    cv::Mat image;
    Shader shader;
    GLuint VAO, VBO;
    GLuint texture;
    TextRenderer textRenderer; // Your custom TextRenderer class

    void init() {
        initShader();
        initQuad();
        initTexture();
        initTextRenderer();
    }

    void initShader() {
        // Load your vertex and fragment shaders
        shader = Shader("path/to/vertex_shader.glsl", "path/to/fragment_shader.glsl");
    }

    void initQuad() {
        float quadVertices[] = {
            // positions   // texture coordinates
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
            -0.5f,  0.5f, 0.0f, 1.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

        glBindVertexArray(0);
    }

    void initTexture() {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (image.empty()) {
            std::cout << "Failed to load image for FlyingWindow texture" << std::endl;
        } else {
            cv::cvtColor(image, image, cv::COLOR_BGR2RGBA);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.cols, image.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void initTextRenderer() {
        // Initialize your custom TextRenderer class
        textRenderer = TextRenderer(); // Add necessary arguments for your TextRenderer constructor
    }
};

#endif
