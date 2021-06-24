#pragma once
#include <string>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

namespace vrt::render
{
	class Shader
	{
	private:
		unsigned int id;

	public:
		Shader();
		Shader(const Shader& other);
		~Shader();

	protected:
		bool includeFile(const char* path, std::string& target, size_t begin, size_t end);
		bool iterateIncludes(const char* directory, std::string& target);

	public:
		bool loadFromFiles(const char* vs_path, const char* fs_path);
		bool loadFromMemory(std::string vs_code, std::string fs_code);

	public:
		void use();

	public:
		void send(int value, const char* target);
		void send(float value, const char* target);
		void send(glm::vec2 value, const char* target);
		void send(glm::vec3 value, const char* target);
		void send(glm::vec4 value, const char* target);
		void send(glm::mat3 value, const char* target);
		void send(glm::mat4 value, const char* target);
	};
}
