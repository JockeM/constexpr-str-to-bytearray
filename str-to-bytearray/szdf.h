#pragma once

#pragma once
#include <array>
#include <utility>

struct optional_byte_t {
    bool    has_value;
    uint8_t value;
};

template <size_t N>
using signature_t = std::array<optional_byte_t, N>;

namespace details {
constexpr auto char_to_byte(char input) -> uint8_t {
    if (input >= 'a' && input <= 'f') {
        return input - 87;
    } else if (input >= 'A' && input <= 'F') {
        return input - 55;
    } else if (input >= '0' && input <= '9') {
        return input - 48;
    }
    throw std::invalid_argument("not a hex char");
}

constexpr auto hex_to_byte(char high, char low) -> optional_byte_t {
    if (high == '?' && low == '?') {
        return {false, 0};
    }
    return {true, static_cast<uint8_t>(char_to_byte(high) << 4 | char_to_byte(low))};
}

template <typename T, std::size_t N, std::size_t... index>
constexpr auto signature_string(const char (&input)[N], const std::index_sequence<index...>&) -> T {
    return {hex_to_byte(input[index * 3], input[(index * 3) + 1])...};
}

template <size_t I = 0, size_t N>
constexpr auto pattern_matches(const uint8_t* bytes, const signature_t<N>& sig) -> bool {
    if constexpr (I == N) {
        return true;
    } else if (sig[I].has_value && sig[I].value != bytes[I]) {
        return false;
    } else {
        return pattern_matches<I + 1>(bytes, sig);
    }
}

} // namespace details

template <size_t N>
constexpr auto search_address(const uint8_t* begin, const uint8_t* end, const signature_t<N>& sig) -> const uint8_t* {
    const auto last_search = end - sig.size();
    if (begin >= last_search) {
        return end;
    }

    for (; begin != last_search; ++begin) {
        if (details::pattern_matches(begin, sig)) {
            return begin;
        }
    }

    return end;
}

template <size_t N>
constexpr auto make_signature(const char (&input)[N]) {
    static_assert(N > 1);
    return details::signature_string<signature_t<N / 3>>(input, std::make_index_sequence<N / 3>{});
}
