#include "doshader.hpp"

Shader::Shader()
{
}

Shader::~Shader()
{
}

/**
 *  Creates the Shader.
 *  @param vertFilename      The filename of the vertex shader file.
 *  @param fragFilename      The filename of the fragment shader file.
 */
void Shader::Create(std::string vertFilename, std::string fragFilename)
{
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

    std::ifstream file(vertFilename);
    std::string vertexShaderSource((std::istreambuf_iterator<char>(file)),
                                   std::istreambuf_iterator<char>());

    const char *sourceCStr = vertexShaderSource.c_str();

    glShaderSource(vertexShaderID, 1, &sourceCStr, NULL);
    glCompileShader(vertexShaderID);

    // check success
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
        Error("Vertex Shader Compilation failed!");
    }

    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // read fragment shader from file
    std::ifstream file2(fragFilename);
    std::string fragmentShaderSource((std::istreambuf_iterator<char>(file2)),
                                     std::istreambuf_iterator<char>());

    const char *sourceCStr2 = fragmentShaderSource.c_str();

    glShaderSource(fragmentShaderID, 1, &sourceCStr2, NULL);
    glCompileShader(fragmentShaderID);

    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);

    // check success
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
        Error("Fragment Shader Compilation failed!");
    }

    shaderProgramID = glCreateProgram();

    glAttachShader(shaderProgramID, vertexShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);
    glLinkProgram(shaderProgramID);

    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
        Error("Linking Shader failed!");
    }
}

/**
 *  Binds the Shader.
 */
void Shader::Bind()
{
    glUseProgram(shaderProgramID);
}

/**
 *  Unbinds the Shader.
 */
void Shader::Unbind()
{
    glUseProgram(0);
}

/**
 *  Sets a Uniform1i.
 *  @param uniformLocation      The name of the uniform.
 *  @param value                The value for changing.
 */
void Shader::SetInt(const char *uniformLocation, int value)
{
    glUniform1i(glGetUniformLocation(shaderProgramID, "texture1"), 0);
}

/**
 *  Sets a UniformMatrix4fv.
 *  @param uniformLocation      The name of the uniform.
 *  @param value                The matrix for changing.
 */
void Shader::SetMatrix4f(const char *uniformLocation, glm::mat4 mat)
{
    unsigned int loc = glGetUniformLocation(shaderProgramID, uniformLocation);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}

/**
 *  Gets a Uniform Location.
 *  @param uniformLocation      The name of the uniform.
 */
int Shader::GetUniform(const char *uniformLocation)
{
    return glGetUniformLocation(shaderProgramID, uniformLocation);
}
