#include "shader.h"
#include "../Code/log/log.h"
#include <GL/glew.h>

namespace vrt::render
{
	Shader::Shader()
	{
		id = 0;
	}

	Shader::Shader(const Shader& other)
	{
		if (id != 0)
		{
			glDeleteProgram(id);
		}
		id = other.id;
	}

	Shader::~Shader()
	{
		if (id != 0)
		{
			glDeleteProgram(id);
			id = 0;
		}
	}

	bool Shader::includeFile(const char* path, std::string& target, size_t begin, size_t end)
	{
		std::string		code;
		std::ifstream	file;

		file.exceptions(std::ifstream::badbit);

		try
		{
			std::stringstream stream;

			file.open(path);
			stream << file.rdbuf();
			file.close();

			code = stream.str();
		}
		catch (std::ifstream::failure)
		{
			LOG_ERR("Reading file: \"" + std::string(path) + "\" failed.");
			return false;
		}

		target.replace(begin, end - begin, code);

		return true;
	}

	bool Shader::iterateIncludes(const char* directory, std::string& target)
	{
		size_t begin = target.find("#include");
		while (begin != std::string::npos)
		{
			size_t end = target.find_first_of('\n', begin);
			std::string include = target.substr(begin, end - begin);

			size_t b = include.find_first_of('"') + 1;
			size_t e = include.find_last_of('"');
			std::string path = std::string(directory) + include.substr(b, e - b);

			if (!includeFile(path.c_str(), target, begin, end))
			{
				return false;
			}

			begin = target.find("#include");
		}

		return true;
	}

	bool Shader::loadFromFiles(const char* vs_path, const char* fs_path)
	{
		if (id != 0)
		{
			LOG_WAR("Shader exists.");
			return false;
		}

		std::string		vs_code, fs_code;
		std::ifstream	vs_file, fs_file;

		vs_file.exceptions(std::ifstream::badbit);
		fs_file.exceptions(std::ifstream::badbit);

		try
		{
			std::stringstream vs_stream, fs_stream;

			vs_file.open(vs_path);
			vs_stream << vs_file.rdbuf();
			vs_file.close();

			fs_file.open(fs_path);
			fs_stream << fs_file.rdbuf();
			fs_file.close();

			vs_code = vs_stream.str();
			fs_code = fs_stream.str();
		}
		catch (std::ifstream::failure)
		{
			LOG_ERR("Reading file: \"" + std::string(vs_path) + "\" failed.");
			return false;
		}

		std::string vs_directory = std::string(vs_path); vs_directory = vs_directory.substr(0, vs_directory.find_last_of('/') + 1);
		std::string fs_directory = std::string(fs_path); fs_directory = fs_directory.substr(0, fs_directory.find_last_of('/') + 1);

		if (!iterateIncludes(vs_directory.c_str(), vs_code)) return false;
		if (!iterateIncludes(fs_directory.c_str(), fs_code)) return false;

		const GLchar* gl_vs_code = vs_code.c_str();
		const GLchar* gl_fs_code = fs_code.c_str();

		GLuint	vs_id, fs_id;
		GLchar	errors_log[1024];
		GLint	result;

		vs_id = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs_id, 1, &gl_vs_code, nullptr);
		glCompileShader(vs_id);
		glGetShaderiv(vs_id, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(vs_id, 1024, nullptr, errors_log);

			LOG_ERR("Vertex shader:" << errors_log);

			glDeleteShader(vs_id);

			return false;
		}

		fs_id = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs_id, 1, &gl_fs_code, nullptr);
		glCompileShader(fs_id);
		glGetShaderiv(fs_id, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(fs_id, 1024, nullptr, errors_log);

			LOG_ERR("Fragment shader :" << errors_log);

			glDeleteShader(vs_id);
			glDeleteShader(fs_id);

			return false;
		}

		id = glCreateProgram();
		glAttachShader(id, vs_id);
		glAttachShader(id, fs_id);
		glLinkProgram(id);
		glGetProgramiv(id, GL_LINK_STATUS, &result);
		if (!result)
		{
			glGetProgramInfoLog(id, 1024, nullptr, errors_log);

			LOG_ERR("Program linking:" << errors_log);

			glDeleteShader(vs_id);
			glDeleteShader(fs_id);
			glDeleteProgram(id);
			id = 0;

			return false;
		}

		glDeleteShader(vs_id);
		glDeleteShader(fs_id);

		return true;
	}

	bool Shader::loadFromMemory(std::string vs_code, std::string fs_code)
	{
		if (id != 0)
		{
			LOG_WAR("Shader exists.");
			return false;
		}

		if (!iterateIncludes("", vs_code)) return false;
		if (!iterateIncludes("", fs_code)) return false;

		const GLchar* gl_vs_code = vs_code.c_str();
		const GLchar* gl_fs_code = fs_code.c_str();

		GLuint	vs_id, fs_id;
		GLchar	errors_log[1024];
		GLint	result;

		vs_id = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs_id, 1, &gl_vs_code, nullptr);
		glCompileShader(vs_id);
		glGetShaderiv(vs_id, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(vs_id, 1024, nullptr, errors_log);

			LOG_ERR("Vertex shader:" << errors_log);

			glDeleteShader(vs_id);

			return false;
		}

		fs_id = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs_id, 1, &gl_fs_code, nullptr);
		glCompileShader(fs_id);
		glGetShaderiv(fs_id, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(fs_id, 1024, nullptr, errors_log);

			LOG_ERR("Fragment shader :" << errors_log);

			glDeleteShader(vs_id);
			glDeleteShader(fs_id);

			return false;
		}

		id = glCreateProgram();
		glAttachShader(id, vs_id);
		glAttachShader(id, fs_id);
		glLinkProgram(id);
		glGetProgramiv(id, GL_LINK_STATUS, &result);
		if (!result)
		{
			glGetProgramInfoLog(id, 1024, nullptr, errors_log);

			LOG_ERR("Program linking:" << errors_log);

			glDeleteShader(vs_id);
			glDeleteShader(fs_id);
			glDeleteProgram(id);
			id = 0;

			return false;
		}

		glDeleteShader(vs_id);
		glDeleteShader(fs_id);

		return true;
	}

	void Shader::use()
	{
		glUseProgram(id);
	}

	void Shader::send(int value, const char* target)
	{
		glUniform1i(glGetUniformLocation(id, target), value);
	}

	void Shader::send(float value, const char* target)
	{
		glUniform1f(glGetUniformLocation(id, target), value);
	}

	void Shader::send(glm::vec2 value, const char* target)
	{
		glUniform2fv(glGetUniformLocation(id, target), 1, glm::value_ptr(value));
	}

	void Shader::send(glm::vec3 value, const char* target)
	{
		glUniform3fv(glGetUniformLocation(id, target), 1, glm::value_ptr(value));
	}

	void Shader::send(glm::vec4 value, const char* target)
	{
		glUniform4fv(glGetUniformLocation(id, target), 1, glm::value_ptr(value));
	}

	void Shader::send(glm::mat3 value, const char* target)
	{
		glUniformMatrix3fv(glGetUniformLocation(id, target), 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::send(glm::mat4 value, const char* target)
	{
		glUniformMatrix4fv(glGetUniformLocation(id, target), 1, GL_FALSE, glm::value_ptr(value));
	}
}
