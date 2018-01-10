#ifndef DATE_TIME_DATE_DEFS_HPP
#define DATE_TIME_DATE_DEFS_HPP

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland
 * $Date: 2013-10-16 14:24:31 +0200 (Mi, 16. Okt 2013) $
 */


namespace boost {
namespace date_time {

  //! An enumeration of weekday names
  enum weekdays {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};

  //! Simple enum to allow for nice programming with Jan, Feb, etc
  enum months_of_year {Jan=1,Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dec,NotAMonth,NumMonths};

} } //namespace date_time



#endif
