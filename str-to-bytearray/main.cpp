#include "signature.h"

int main() {
    constexpr auto signature = make_signature("DE AD ?? BE EF");

    std::array<uint8_t, 16> x = {0xFF, 0xFF, 0xFF, 0xFF, 0x23, 0xDE, 0xAD, 0xFF,
                                 0xBE, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    auto results = search_address(x.data(), x.data() + x.size(), signature);

    return reinterpret_cast<int>(results);
}