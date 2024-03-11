#pragma once

#include <cstdint>

#include <string>
#include <optional>
#include <tuple>

#include "./toxcore_enums.hpp"

// defines the private interface for tox
struct ToxPrivateI {
	static constexpr const char* version {"2"};

	virtual ~ToxPrivateI(void) {}

	virtual uint16_t toxDHTGetNumCloselist(void) = 0;
	virtual uint16_t toxDHTGetNumCloselistAnnounceCapable(void) = 0;

	virtual std::tuple<std::optional<std::string>, Tox_Err_Group_Peer_Query> toxGroupPeerGetIPAddress(uint32_t group_number, uint32_t peer_id) = 0;
};

