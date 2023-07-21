#pragma once

#include "./tox_event_interface.hpp"

#include <vector>
#include <array>

// implements common code for tox event dispatching
struct ToxEventProviderBase : public ToxEventProviderI {
	protected:
		void dispatchEvents(const Tox_Events* events);

	public: // event provider
		virtual void subscribe(ToxEventI* object, const Tox_Event event_type) override;

	protected:
		std::array<std::vector<ToxEventI*>, 39> _subscribers; // rn 39 event types
};

