
#ifndef BOOST_MPL_AUX_CONFIG_MSVC_TYPENAME_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_MSVC_TYPENAME_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: msvc_typename.hpp 386076 2013-10-16 12:24:31Z heinzeti $
// $Date: 2013-10-16 14:24:31 +0200 (Mi, 16. Okt 2013) $
// $Revision: 386076 $

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
#   define BOOST_MSVC_TYPENAME
#else
#   define BOOST_MSVC_TYPENAME typename
#endif

#endif // BOOST_MPL_AUX_CONFIG_MSVC_TYPENAME_HPP_INCLUDED
