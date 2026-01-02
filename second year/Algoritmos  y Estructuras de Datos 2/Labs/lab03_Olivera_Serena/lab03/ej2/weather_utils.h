#ifndef  _WEATHER_UTILS_H
#define  _WEATHER_UTILS_H  

#include "array_helpers.h"

int min_temp_cba (WeatherTable array);
/*ffunction that obtains the minimum temperature in the data*/

void max_temp_anual (WeatherTable array, int max_anual[YEARS]);
/*proc that detects the maximum temperature per year*/


void mes_precip (WeatherTable array, month_t rainiest_month[YEARS]);

/*proc that detects the months with most rainfall*/

void print_month_per_year (WeatherTable array, month_t rainiest_month [YEARS]);

/* instead of writing a big chunk for printing in main I put it on a proc*/

#endif
