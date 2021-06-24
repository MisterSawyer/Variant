#include "observer.h"

namespace vrt::utils {

	void Subject::attach(Observer* observer)
	{
		observers_list.push_back(observer);
	}

	void Subject::detach(Observer* observer)
	{
		observers_list.remove(observer);
	}

	void Subject::notify(const std::string& message_to_subject)
	{
		for (auto& obs : observers_list)
		{
			obs->update(message_to_subject);
		}
	}

}