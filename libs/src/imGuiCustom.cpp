//
// Created by Kim Huber on 23.01.2021.
//


#include "imGuiCustom.h"

imGuiCustom::~imGuiCustom() {
    if(m_created)
        destroyWindow();
    glfwTerminate();
}

static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int imGuiCustom::createWindow() {
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;


    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    m_window = glfwCreateWindow(windowWidth, windowHeight, programName, fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
    if (m_window == nullptr)
        return 1;
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    if (docking)
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    m_created = true;
    return 0;
}

void imGuiCustom::destroyWindow() {
    if (!m_created)
        return;

    // Cleanup
    glfwDestroyWindow(m_window);
    m_window = nullptr;
    m_created = false;
}

bool imGuiCustom::checkWindow() const {
    return m_created;
}

void imGuiCustom::createFrame() {
    glfwPollEvents();
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void imGuiCustom::renderFrame() {
    // Render the Dear ImGui elements
    ImGui::Render();

    // Get the size of the framebuffer for the current window
    int display_w, display_h;
    glfwGetFramebufferSize(m_window, &display_w, &display_h);

    // Set the viewport for rendering
    glViewport(0, 0, display_w, display_h);

    // Set the clear color for the background
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Render the ImGui data using OpenGL 3
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Swap buffers and poll events
    glfwSwapBuffers(m_window);

    // If the window should close, destroy it
    if(glfwWindowShouldClose(m_window)){
        destroyWindow();
        return;
    }
}
