/* boost random/detail/enable_warnings.hpp header file
 *
 * Copyright Steven Watanabe 2009
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id: enable_warnings.hpp 254826 2013-01-10 12:29:18Z akosteltsev $
 *
 */

// No #include guard.  This header is intended to be included multiple times.

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
