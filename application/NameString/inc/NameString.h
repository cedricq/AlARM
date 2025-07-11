#ifndef NAME_STRING_H
#define NAME_STRING_H

#include <numeric>
#include <array>
#include <string>
#include <cstring>

using bool_t = bool;

namespace core
{
    class NameString
    {
    public:
        constexpr static std::size_t LENGTH{64};

        constexpr NameString() = default;
        constexpr NameString(NameString const& other) = default;
        constexpr NameString& operator=(NameString const& other) = default;

        NameString(char const* str)
        {
            std::fill(data_, data_+LENGTH, 0); // GCOVR_EXCL_LINE
            std::size_t const size = strnlen(str, LENGTH-1);
            std::copy(str, str + size, data_);
        }

        NameString(const std::string& str)
        {
            std::fill(data_, data_ + LENGTH, 0); // GCOVR_EXCL_LINE
            std::size_t const toCopy = std::min(str.size(), LENGTH-1);
            std::copy(str.begin(), str.begin() + toCopy, data_);
        }

        NameString& operator=(std::string& str) { *this = NameString(str); return *this; }
        NameString& operator=(char const* str)      { *this = NameString(str); return *this; }
        ~NameString() = default;

        std::string str() const
        {
            std::string str;
            std::size_t const size = strnlen(data_, LENGTH);
            str.insert(str.begin(), data_, data_ + size);
            return str;
        }
        char const* c_str() const { return data_; }
        char* data()              { return data_; }
        char const* data() const  { return data_; }

        char const& operator[](int index) const   { return data_[index]; }

        char data_[LENGTH]{};
    };

    bool operator< (NameString const& lhs, NameString const& rhs);

    void PrintTo(NameString const& name, std::ostream* os);
}

namespace std
{
    template<> struct hash<core::NameString>
    {
        std::size_t operator()(core::NameString const& k) const
        {
            return std::accumulate(k.data_, k.data_+core::NameString::LENGTH, 1, [](std::size_t h, auto c) { return h * 101 + c; });
        }
    };

    ostream& operator<<(ostream& os, core::NameString const& name);
}

#endif
