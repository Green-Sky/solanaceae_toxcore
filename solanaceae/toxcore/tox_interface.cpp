#include <tox/tox.h> // before interface
#include "./tox_interface.hpp"

#include "./utils.hpp"

std::string ToxI_raw::toxSelfGetAddressStr(void) {
	// TODO: cache
	return bin2hex(toxSelfGetAddress());
}

std::vector<uint8_t> ToxI_raw::toxHash(const std::vector<uint8_t>& data) {
	std::vector<uint8_t> hash(TOX_HASH_LENGTH);
	tox_hash(hash.data(), data.data(), data.size()); // TODO: return value?
	return hash;
}

