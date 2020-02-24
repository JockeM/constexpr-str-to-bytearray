#include "signature.h"

auto sig_scan() {
    constexpr auto signature = make_signature("?? DE AD ?? BE EF ??");

    std::array<uint8_t, 16> bytes = {0xFF, 0xFF, 0xFF, 0xFF, 0x23, 0xDE, 0xAD, 0xFF,
                                 0xBE, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    return search_address(bytes.data(), bytes.data() + x.size(), signature);
}