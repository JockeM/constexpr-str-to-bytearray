#include "szdf.h"
#define LEAN_AND_MEAN
#include <Windows.h>

int main() {
    constexpr auto pattern = make_signature("DE AD ?? BE EF");

    std::array<uint8_t, 16> x = {0xFF, 0xFF, 0xFF, 0xFF, 0x23, 0xDE, 0xAD, 0xFF,
                                 0xBE, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    auto results = search_address(x.data(), x.data() + x.size(), pattern);

    return reinterpret_cast<int>(results);
}