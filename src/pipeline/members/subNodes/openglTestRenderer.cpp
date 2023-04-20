#include "subNodes.hpp"

OpenglTestRenderer::OpenglTestRenderer(){
    setup();
}

void OpenglTestRenderer::setup() {
    // OpenGL settings
    glEnable(GL_DEPTH_TEST);

    // Load shaders and set up camera, models, and related OpenGL resources
    Shader shader("./_shaders/vertex_shader.glsl", "./_shaders/fragment_shader.glsl");
    camera = Camera(glm::vec3(0.0f, 0.0f, 5.0f));

    model1 = Model("./_models/hand.obj");
    model2 = Model("./_models/hand.obj");
}

void OpenglTestRenderer::processFrame(cv::UMat &input, cv::Point2d &cursorPos) {
    // Clear the buffers
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the view and projection matrices
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(camera.Zoom, (float)input.cols / (float)input.rows, 0.1f, 100.0f);

    // Draw the first model
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.0f, 0.0f, 0.0f));
    shader.use();
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    shader.setMat4("model", modelMatrix);
    model1.Draw(shader);

    // Draw the second model
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(2.0f, 0.0f, 0.0f));
    shader.setMat4("model", modelMatrix);
    model2.Draw(shader);

    // Add any other OpenGL drawing logic you need

    // Update the texture with the rendered OpenGL scene
    glFlush();
    cv::ogl::Texture2D(input).copyFromFramebuffer();
}