#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <stdlib.h>

#include "Shader.h"
#include "vec2f.h"
#include "ConvexHull.h"

#pragma comment(lib, "opengl32.lib")

// settings
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

unsigned int setPolyVAO(const std::vector<vec2f>& points)
{
    float* vertices = new float[points.size() * 2];

    int i = 0;

    for (auto p : points)
    {
        vertices[i] = p.x;
        vertices[i + 1] = p.y;

        i += 2;
    }

    unsigned int VBO, PolyVAO;

    glGenBuffers(1, &VBO);

    glGenVertexArrays(1, &PolyVAO);

    glBindVertexArray(PolyVAO);

    //vbo
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size() * 2, vertices, GL_STATIC_DRAW);

    //vao
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    delete[] vertices;

    return PolyVAO;

    //done
}

int main()
{
    srand(time(0));

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(WIDTH, HEIGHT, "CH", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return -1;
    }

    Shader shader("shader.vs", "shader.fs");
    std::vector<vec2f> points, hull;

    glm::vec3 pointsColor(0.2f, 0.4f, 0.0f), linesColor(1.0f, 0.0f, 0.0f);

    unsigned int pointsVAO = setPolyVAO(points), linesVAO = setPolyVAO(hull);

    while (!glfwWindowShouldClose(window))
    {

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            double x, y;
            glfwGetCursorPos(window, &x, &y);

            x = x / (WIDTH / 2) - 1;
            y = 1 - y / (HEIGHT / 2);

            vec2f p(x, y);

            bool toAdd = true;
            float eps = 0.01f;

            for (auto q : points)
            {
                if ((p - q).magnitude() < eps)
                {
                    toAdd = false;
                }
            }
            
            if (toAdd)
            {
                points.push_back(p);
                pointsVAO = setPolyVAO(points);

                //hull = ConvexHull(points);
                //linesVAO = setPolyVAO(hull);
            }
        }

        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
            hull = ConvexHull(points);
            linesVAO = setPolyVAO(hull);
        }

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //white background
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        //draw points
        shader.setVec3("color", pointsColor);
        glPointSize(10);

        glBindVertexArray(pointsVAO);
        glDrawArrays(GL_POINTS, 0, points.size());

        //draw lines
        shader.setVec3("color", linesColor);
        //glLineWidth(1);

        glBindVertexArray(linesVAO);
        glDrawArrays(GL_LINE_LOOP, 0, hull.size());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;

}

