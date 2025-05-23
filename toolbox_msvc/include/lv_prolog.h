/**
    (c) Copyright 2007-2025 by National Instruments Corp.
    All rights reserved.

    @author National Instruments Corp.
    @file
    @brief  Ensure proper structure alignment for data structures. Bookend with lv_epilog.h.

    Data structures requiring platform-specific structure alignment should include this
    header prior to the definition of the structure. You must then include lv_epilog.h
    to restore structure packing to its previous setting.

    @note Never put include guards in this header. It is designed to be included multiple times.

    @note Take care to when including other headers between a lv_prolog.h / lv_epilog.h pair -
          be careful to ensure consistency across software components.

    Example usage:
    @code
    #include "some_header.h"

    #include "lv_prolog.h"
    #include "platdefines.h"

    typedef struct {
        int m_int;
        double m_double;
    } MyStruct;

    #include "lv_epilog.h"

    @endcode
*/

#include "platdefines.h"

#if !defined(NIDL)
#if MSWin && (ProcessorType == kX86)
// Windows x86 targets use 1-byte structure packing.
#pragma pack(push, 1)
#pragma warning(disable : 4103) // disable warning: alignment changed after including header
#elif Mac
// Use natural alignment on the Mac.
#if Compiler == kGCC
#pragma options align = natural
#else
#error "Unsupported compiler. Figure out how to set alignment to native/natural"
#endif
#else
// Use default (or build's) alignment
#endif // struct alignment set
#endif // !defined(NIDL)
