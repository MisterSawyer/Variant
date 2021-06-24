#pragma once
#include <list>
#include <string>

namespace vrt::utils {
	class Observer {
	public:
		virtual ~Observer() = default;
		virtual void update(const std::string& message_from_subject) = 0;
	};

	class Subject {
	public:
		virtual ~Subject() = default;
		void attach(Observer* observer);
		void detach(Observer* observer);
		virtual void notify(const std::string& message_to_subject);
	private:
		std::list<Observer *> observers_list;
	};
}