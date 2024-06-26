R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;
uniform mat4 proj;
void main()
{
    gl_Position = proj * vec4(aPos.x, aPos.y, 0.0, 1.0);
    ourColor = aColor;
}
)"