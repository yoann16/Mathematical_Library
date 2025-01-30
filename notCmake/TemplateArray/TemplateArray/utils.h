#pragma once
namespace Mathematical_library
{
    template<typename InputIt, typename OutputIt, typename Fn>
    OutputIt transform(InputIt begin, InputIt end, OutputIt out, Fn fn)
    {
        for (auto it = begin;it != end;++it, ++out)
            *out = fn(it);
        return out;
    }
}