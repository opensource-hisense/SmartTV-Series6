
#ifndef BOOST_MPL_AUX_RANGE_C_FRONT_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_FRONT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: front.hpp 254826 2013-01-10 12:29:18Z akosteltsev $
// $Date: 2013-01-10 13:29:18 +0100 (Do, 10. Jan 2013) $
// $Revision: 254826 $

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct front_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
    {
        typedef typename Range::start type;
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_FRONT_HPP_INCLUDED
