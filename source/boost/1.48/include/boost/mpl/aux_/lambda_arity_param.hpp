
#ifndef BOOST_MPL_AUX_LAMBDA_ARITY_PARAM_HPP_INCLUDED
#define BOOST_MPL_AUX_LAMBDA_ARITY_PARAM_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: lambda_arity_param.hpp 254826 2013-01-10 12:29:18Z akosteltsev $
// $Date: 2013-01-10 13:29:18 +0100 (Do, 10. Jan 2013) $
// $Revision: 254826 $

#include <boost/mpl/aux_/config/ttp.hpp>

#if !defined(BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING)
#   define BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(param)    
#else
#   define BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(param) , param
#endif

#endif // BOOST_MPL_AUX_LAMBDA_ARITY_PARAM_HPP_INCLUDED
