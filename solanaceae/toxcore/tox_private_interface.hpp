#pragma once

#include <cstdint>

// defines the private interface for tox
struct ToxPrivateI {
	static constexpr const char* version {"1"};

	virtual ~ToxPrivateI(void) {}

	virtual uint16_t toxDHTGetNumCloselist(void) = 0;
	virtual uint16_t toxDHTGetNumCloselistAnnounceCapable(void) = 0;
};

