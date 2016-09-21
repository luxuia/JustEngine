#pragma once

#include "pch.h"

#include <unordered_map>
#include <functional>
#include <map>
#include <string>

namespace JustEngine {

	#define BIND_FUNC(listener, func) std::bind(func, listener.get(), std::placeholders::_1)
	
	class DLL_EXPORT Signal {
	private:
		using TYPE_FUNC = std::function< void(const std::shared_ptr<void>& sender)>;
		class Slot {
		public:
			ObjTypePtr(Slot);

			std::map< std::weak_ptr<void>,
				TYPE_FUNC,
				std::owner_less< std::weak_ptr<void>> >
				Listeners;
		};

		std::unordered_map<size_t, Slot::Ptr> mSignal;
		public:
			ObjTypePtr(Signal);

			static Signal::Ptr Create();

			void CreateSlot(const std::string& slotName);

			bool Connect(const std::string& slotName, const std::shared_ptr<void>& listener, const TYPE_FUNC& func);
			bool Connect(size_t slotName, const std::shared_ptr<void>& listener, const TYPE_FUNC& func);

			void Disconnect(const std::string& slotName, const std::shared_ptr<void>& listener);
			void Disconnect(size_t slotName, const std::shared_ptr<void>& listener);

			void Emit(const std::string& slotName, const std::shared_ptr<void>& sender);
			void Emit(size_t slotName, const std::shared_ptr<void>& sender);
	};
}