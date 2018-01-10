
#ifndef BOOST_MPL_SIZEOF_HPP_INCLUDED
#define BOOST_MPL_SIZEOF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: sizeof.hpp 254826 2013-01-10 12:29:18Z akosteltsev $
// $Date: 2013-01-10 13:29:18 +0100 (Do, 10. Jan 2013) $
// $Revision: 254826 $

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct sizeof_
    : mpl::size_t< sizeof(T) >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,sizeof_,(T))
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, sizeof_)

}}

#endif // BOOST_MPL_SIZEOF_HPP_INCLUDED
