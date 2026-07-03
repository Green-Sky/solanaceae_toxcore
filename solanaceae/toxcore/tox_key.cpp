#include "./tox_key.hpp"

#include <stdexcept>
#include <cassert>

ToxKey::ToxKey(const std::vector<std::uint8_t>& v) {
	assert(v.size() >= data.size());
	if (v.size() < data.size()) {
		throw std::runtime_error("tox key construction size mismatch");
	}
	for (size_t i = 0; i < data.size(); i++) {
		data[i] = v[i];
	}
}

ToxKey::ToxKey(const std::uint8_t* d, std::size_t s) {
	assert(s >= data.size());
	if (s < data.size()) {
		throw std::runtime_error("tox key construction size mismatch");
	}
	for (size_t i = 0; i < data.size(); i++) {
		data[i] = d[i];
	}
}


bool ToxKey::operator<(const ToxKey& other) const {
	for (size_t i = 0; i < size(); i++) {
		if (data[i] < other.data[i]) {
			return true;
		} else if (data[i] > other.data[i]) {
			return false;
		}
	}

	return false; // equal
}

//std::ostream& operator<<(std::ostream& out, const SHA1Digest& v) {
	//std::string str{};
	//str.resize(v.size()*2, '?');

	//// HECK, std is 1 larger than size returns ('\0')
	//sodium_bin2hex(str.data(), str.size()+1, v.data.data(), v.data.size());

	//out << str;

	//return out;
//}

