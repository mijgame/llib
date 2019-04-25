#ifndef LLIB_STREAM_BASE_HPP
#define LLIB_STREAM_BASE_HPP

namespace llib {
    enum class base {
        HEX,
        DEC,
        OCT,
        BIN
    };

    namespace {
        constexpr base _default_base = base::DEC;
        constexpr bool _default_boolalpha = false;
    }

    template<base B = _default_base, bool Boolalpha = _default_boolalpha>
    class ostream {
    public:
        constexpr static llib::base base = B;
        constexpr static bool boolalpha = Boolalpha;

        template<llib::base IB, bool IBoolalpha>
        using instance = ostream<IB, IBoolalpha>;
    };

    class istream {
    public:
        using instance = istream;
    };
}

#endif //LLIB_STREAM_BASE_HPP
