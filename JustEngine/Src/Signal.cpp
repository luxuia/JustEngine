#include "Signal.h"

namespace JustEngine {

	Signal::Ptr Signal::Create()
	{
		return std::make_shared<Signal>();
	}
	void Signal::CreateSlot(const std::string & slotName)
	{
		auto hash = Utility::HashArray(slotName.c_str(), slotName.length());
		auto it = mSignal.find(hash);
		ASSERT(it == mSignal.end());
		mSignal.emplace(hash, Slot());
	}
	bool Signal::Connect(const std::string & slotName, const std::shared_ptr<void>& listener, const TYPE_FUNC & func)
	{
		return Connect(Utility::HashArray(slotName.c_str(), slotName.length()), listener, func);
	}

	bool Signal::Connect(size_t slotName, const std::shared_ptr<void>& listener, const TYPE_FUNC& func)
	{
		auto it = mSignal.find(slotName);
		if (it != mSignal.end()) {
			auto& result = it->second.Listeners.emplace(listener, func);
			return result.second;
		}
		return false;
	}

	void Signal::Disconnect(const std::string & slotName, const std::shared_ptr<void>& listener)
	{
		Disconnect(Utility::HashArray(slotName.c_str(), slotName.length()), listener);
	}

	void Signal::Disconnect(size_t slotName, const std::shared_ptr<void>& listener)
	{
		auto it = mSignal.find(slotName);
		if (it != mSignal.end()) {
			it->second.Listeners.erase(listener);
		}
	}

	void Signal::Emit(const std::string & slotName, const std::shared_ptr<void>& sender)
	{
		Emit(Utility::HashArray(slotName.c_str(), slotName.length()), sender);
	}

	void Signal::Emit(size_t slotName, const std::shared_ptr<void>& sender)
	{
		auto it = mSignal.find(slotName);
		if (it != mSignal.end()) {
			auto& listens = it->second.Listeners;

			for (auto it = listens.begin(); it != listens.end();) {
				if (it->first.expired()) {
					it = listens.erase(it);
				}
				else {
					it->second(sender);
					++it;
				}
			}
		} else {
			ASSERT(false);
		}
	}

}