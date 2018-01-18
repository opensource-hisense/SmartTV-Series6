
#ifndef BOOST_MPL_CONTAINS_FWD_HPP_INCLUDED
#define BOOST_MPL_CONTAINS_FWD_HPP_INCLUDED

// Copyright Eric Friedman 2002
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: contains_fwd.hpp 254826 2013-01-10 12:29:18Z akosteltsev $
// $Date: 2013-01-10 13:29:18 +0100 (Do, 10. Jan 2013) $
// $Revision: 254826 $

namespace boost { namespace mpl {

template< typename Tag > struct contains_impl;
template< typename Sequence, typename T > struct contains;

}}

#endif // BOOST_MPL_CONTAINS_FWD_HPP_INCLUDED