
#ifndef BOOST_MPL_AUX_NTTP_DECL_HPP_INCLUDED
#define BOOST_MPL_AUX_NTTP_DECL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: nttp_decl.hpp 254826 2013-01-10 12:29:18Z akosteltsev $
// $Date: 2013-01-10 13:29:18 +0100 (Do, 10. Jan 2013) $
// $Revision: 254826 $

#include <boost/mpl/aux_/config/nttp.hpp>

#if defined(BOOST_MPL_CFG_NTTP_BUG)

typedef bool        _mpl_nttp_bool;
typedef int         _mpl_nttp_int;
typedef unsigned    _mpl_nttp_unsigned;
typedef long        _mpl_nttp_long;

#   include <boost/preprocessor/cat.hpp>
#   define BOOST_MPL_AUX_NTTP_DECL(T, x) BOOST_PP_CAT(_mpl_nttp_,T) x /**/

#else

#   define BOOST_MPL_AUX_NTTP_DECL(T, x) T x /**/

#endif

#endif // BOOST_MPL_AUX_NTTP_DECL_HPP_INCLUDED
