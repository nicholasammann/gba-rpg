#pragma once
#include <optional>

namespace bn {
    // Map Butano's optional to the standard C++ library equivalent
    template <typename T>
    using optional = std::optional<T>;

    // Map nullopt flag
    inline constexpr std::nullopt_t nullopt = std::nullopt;
}
