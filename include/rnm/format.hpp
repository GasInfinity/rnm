#ifndef _RENA_MATHEMATICS_FORMAT_HPP_
#define _RENA_MATHEMATICS_FORMAT_HPP_

#include "vec.hpp"
#include "mat.hpp"

#include <format>


namespace std
{
    template<typename T, std::size_t N>
    struct formatter<::rnm::vec<T, N>> {
        std::formatter<T> formatter;

        constexpr auto parse(std::format_parse_context& ctx) {
            return formatter.parse(ctx);
        }

        constexpr auto format(const rnm::vec<T, N>& v, std::format_context& ctx) const {
            std::format_to(ctx.out(), "(");
            format_next(v, ctx, std::make_index_sequence<N>{});
            return std::format_to(ctx.out(), ")");
        }
    private:
        template<std::size_t... I>
        rnm_forceinline constexpr auto format_next(const rnm::vec<T, N>& v, std::format_context& ctx, const std::index_sequence<0, I...>&) const {
            formatter.format(v[0], ctx);
            ((*ctx.out()++ = ',', *ctx.out()++ = ' ', formatter.format(v[I], ctx)), ...);
        }
    };

    template<typename T, std::size_t R, std::size_t C>
    struct formatter<rnm::mat<T, R, C>> {
        std::formatter<T> formatter;

        constexpr auto parse(std::format_parse_context& ctx) {
            return formatter.parse(ctx);
        }

        constexpr auto format(const rnm::mat<T, R, C>& v, std::format_context& ctx) const {
            return format_rows(v, ctx, std::make_index_sequence<R>{});
        }
    private:
        template<std::size_t... I>
        rnm_forceinline constexpr auto format_rows(const rnm::mat<T, R, C>& m, std::format_context& ctx, const std::index_sequence<0, I...>&) const {
            *ctx.out()++ = '[';
            format_row<0>(m, ctx, std::make_index_sequence<C>{});
            ((*ctx.out()++ = ',', *ctx.out()++ = ' ', format_row<I>(m, ctx, std::make_index_sequence<C>{})), ...);
            *ctx.out()++ = ']';
            return ctx.out();
        }

        template<std::size_t CR, std::size_t... I>
        rnm_forceinline constexpr auto format_row(const rnm::mat<T, R, C>& m, std::format_context& ctx, const std::index_sequence<0, I...>&) const {
            *ctx.out()++ = '(';
            formatter.format(m[CR, 0], ctx);
            ((*ctx.out()++ = ',', *ctx.out()++ = ' ', formatter.format(m[CR, I], ctx)), ...);
            *ctx.out()++ = ')';
            return ctx.out();
        }
    };
}

#endif // _RENA_MATHEMATICS_FORMAT_HPP_
