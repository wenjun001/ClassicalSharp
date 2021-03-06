#ifndef CC_DATETIME_H
#define CC_DATETIME_H
#include "Typedefs.h"
/* Represents a particular instance in time in some timezone. Not necessarily UTC time.
   Copyright 2017 ClassicalSharp | Licensed under BSD-3
*/

typedef struct DateTime_ {
	UInt16 Year; /* Year of this point in time, ranges from 0 to 65535. */	
	UInt8 Month; /* Month of this point in time, ranges from 1 to 12. */	
	UInt8 Day; /* Day of this point in time, ranges from 1 to 31. */	
	UInt8 Hour; /* Hour of this point in time, ranges from 0 to 23. */
	UInt8 Minute; /* Minute of this point in time, ranges from 0 to 59. */
	UInt8 Second; /* Second of this point in time, ranges from 0 to 59. */
	UInt16 Milliseconds; /* Milliseconds of this point in time, ranges from 0 to 999. */
} DateTime;

#define DATETIME_MILLISECS_PER_SECOND 1000
#define DATETIME_SECONDS_PER_MINUTE 60
#define DATETIME_SECONDS_PER_HOUR (60 * 60)
#define DATETIME_SECONDS_PER_DAY (60 * 60 * 24)

Int64 DateTime_TotalMilliseconds(DateTime* time);
Int64 DateTime_MillisecondsBetween(DateTime* start, DateTime* end);
#endif