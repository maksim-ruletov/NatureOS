#if !defined(L0_TYPES_H)

#define L0_TYPES_H

#include <vector>
#include <string>

namespace misc {
    typedef std::vector<std::string> _CompositionPart;
    typedef std::vector<std::vector<std::string>> _Composition;
    typedef std::vector<std::vector<::size_t>> _SizeComposition;
    typedef std::vector<::size_t> _SizeCompositionPart;
} // #misc

#endif