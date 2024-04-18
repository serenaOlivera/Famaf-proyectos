#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "weather_utils.h"

int min_temp_cba (WeatherTable array){
    int min = array [0][0][0]._min_temp;

    for (int year = 0; year < YEARS; year++){
        for (int month = 0; month < MONTHS; month++){
            for (int day = 0; day < DAYS; day++){
              if (array [year][month][day]._min_temp < min){
                min = array [year][month][day]._min_temp;
              }  
            }
            
        }
        
    }

    return min;    
}

void max_temp_anual (WeatherTable array, int output[YEARS]){
    for (int year = 0; year < YEARS; year++){
        int maximum = array [year][0][0]._max_temp;
        for (int month = 0; month < MONTHS; month++){
            for (int day = 0; day < DAYS; day++){
                if (maximum < array [year][month][day]._max_temp){
                    output[year] = array [year][month][day]._max_temp;
                }
            }
            
        }
        
    }
    
}

void mes_precip (WeatherTable array, month_t rainiest_month[YEARS]){   // years because there's going to be 37 prints
    for (int year = 0; year < YEARS; year++){
        int comparing = 0;
        for (int month = 0; month < MONTHS; month++){
            int counter = 0;
            for (int day = 0; day < DAYS; day++){
                if (array [year][month][day]._rainfall != 0){
                    counter = counter + 1;
                }
            }
            if (comparing < counter){
                    rainiest_month[year] = month;
                    comparing = counter;
                }
            
        }
        
    }
    
}

void print_month_per_year (WeatherTable array, month_t rainiest_month [YEARS]){
    char * month;

    for (int year = 0; year < YEARS; year++){
        if (rainiest_month[year] == 0) month = "january";
        else if (rainiest_month[year] == 1) month = "february";
        else if (rainiest_month[year] == 2) month = "march";
        else if (rainiest_month[year] == 3) month = "april";
        else if (rainiest_month[year] == 4) month = "may";
        else if (rainiest_month[year] == 5) month = "june";
        else if (rainiest_month[year] == 6) month = "july";
        else if (rainiest_month[year] == 7) month = "august";
        else if (rainiest_month[year] == 8) month = "september";
        else if (rainiest_month[year] == 9) month = "october";
        else if (rainiest_month[year] == 10) month = "november";
        else month = "december";
        printf ("\nThe rainiest month in %u is %s \n", year+1980, month);
    }
}