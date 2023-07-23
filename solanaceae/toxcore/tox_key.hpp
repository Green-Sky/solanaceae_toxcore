#pragma once

#include <array>
#include <vector>
#include <cstdint>

// public key or secret key, or conf uid
struct ToxKey {
	std::array<std::uint8_t, 32> data;

	ToxKey(void) = default;
	ToxKey(const std::vector<std::uint8_t>& v);
	ToxKey(const std::uint8_t* d, std::size_t s);

	constexpr bool operator==(const ToxKey& other) const { return data == other.data; }
	constexpr bool operator!=(const ToxKey& other) const { return data != other.data; }

	bool operator<(const ToxKey& other) const;

	constexpr std::size_t size(void) const { return data.size(); }
};

//std::ostream& operator<<(std::ostream& out, const SHA1Digest& v);

