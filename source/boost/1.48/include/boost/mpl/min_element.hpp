
#ifndef BOOST_MPL_MIN_ELEMENT_HPP_INCLUDED
#define BOOST_MPL_MIN_ELEMENT_HPP_INCLUDED

// Copyright David Abrahams 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: min_element.hpp 254826 2013-01-10 12:29:18Z akosteltsev $
// $Date: 2013-01-10 13:29:18 +0100 (Do, 10. Jan 2013) $
// $Revision: 254826 $

#include <boost/mpl/max_element.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(min_element)

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename Predicate = less<_,_>
    >
struct min_element
    : max_element<
          Sequence
        , mpl::not_<Predicate>
        >
{
};

BOOST_MPL_AUX_NA_SPEC(1, min_element)

}}

#endif // BOOST_MPL_MIN_ELEMENT_HPP_INCLUDED
