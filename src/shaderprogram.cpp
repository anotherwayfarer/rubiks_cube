#include "all.h"

#include "shaderprogram.h"

#include "shader.h"
#include <iostream>

using namespace std;

ShaderProgram::ShaderProgram()
{
	m_id = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram( m_id );
}

void ShaderProgram::attachShader( const Shader & shader )
{
	glAttachShader( m_id, shader.getId() );
}

void ShaderProgram::linkProgram()
{
	glLinkProgram( m_id );

	GLint linkStatus = GL_FALSE;
	glGetProgramiv( m_id, GL_LINK_STATUS, &linkStatus );
	if ( linkStatus == GL_FALSE )
	{
//		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "glLinkProgram:");
		std::cout << "Shader program linking failed." << std::endl;
//		glfwTerminate();
	}
	else
	{
		std::cout << "Shader program linking OK." << std::endl;
	}
}

GLint ShaderProgram::addAttribute( const std::string & attributeName )
{
	GLint attr = glGetAttribLocation( m_id, attributeName.c_str() );

	if ( attr == -1 )
	{
		std::cout << "Could not add attribute: " << attributeName << " - location returned -1!" << endl;
		return -1;
	}
	else
	{
		m_attributes[ attributeName ] = attr;
		cout << "Attribute " << attributeName << " bound to location: " << m_attributes[attributeName] << endl;
	}

	return attr;
}

GLint ShaderProgram::addUniform( const string & uniformName )
{
	GLint attr = glGetUniformLocation( m_id, uniformName.c_str() );

	if ( attr == -1 )
	{
		cout << "Could not add uniform: " << uniformName << " - location returned -1!" << endl;
		return -1;
	}
	else
	{
		m_uniforms[ uniformName ] = attr;
		cout << "Uniform " << uniformName << " bound to location: " << m_uniforms[uniformName] << endl;
	}

	return attr;
}