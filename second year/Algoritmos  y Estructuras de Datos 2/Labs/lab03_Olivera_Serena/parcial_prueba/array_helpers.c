/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"

static const int EXPECTED_DIM_VALUE = 2;

static const char* CITY_NAMES[CITIES] = {
    "Cordoba", "Rosario", "Posadas", "Tilcara", "Bariloche"};
static const char* SEASON_NAMES[SEASONS] = {"low", "high"};

void array_dump(BakeryProductTable a)
{
    for (unsigned int city = 0u; city < CITIES; ++city)
    {
        for (unsigned int season = 0u; season < SEASONS; ++season)
        {
            fprintf(stdout, "%s in %s season: flour (%u,%u) Yeast (%u,%u) Butter (%u,%u) Sales value %u",
                    CITY_NAMES[city], SEASON_NAMES[season], a[city][season].flour_cant,
                    a[city][season].flour_price, a[city][season].yeast_cant,
                    a[city][season].yeast_price, a[city][season].butter_cant,
                    a[city][season].butter_price, a[city][season].sale_value);
            fprintf(stdout, "\n");
        }
    }
}

/*calculates the profit from a bussiness*/
unsigned int profit (BakeryProduct a)
{
    unsigned int sum = (a.butter_cant*a.butter_price) + (a.flour_cant*a.flour_price) + (a.yeast_cant*a.yeast_price);
    unsigned int the_profit = a.sale_value - sum;

    return the_profit;
}

unsigned int best_profit(BakeryProductTable a)
{
    unsigned int max_profit = 0u;
    for (unsigned int ciudad = 0; ciudad < CITIES; ciudad++)
    {
        unsigned int city_profit = 0;
        if (profit (a [ciudad] [0]) > profit (a [ciudad] [1]))
        {   
            city_profit = profit(a [ciudad] [0]);
        }else{
            city_profit = profit (a [ciudad] [1]);
        }

        if (city_profit > max_profit)
        {
            max_profit = city_profit;
        }
            
                    
    }
    
    return max_profit;
}


void array_from_file(BakeryProductTable array, const char* filepath)
{
    FILE* file = NULL;

    file = fopen(filepath, "r" );
    if (file == NULL)
    {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }

    unsigned int  city = 0;
    unsigned int season = 0;
    while (!feof(file))
    {
        int res = fscanf(file, " ##%u??%u ", &city, &season);
        if (res != EXPECTED_DIM_VALUE)
        {
            fprintf(stderr, "Invalid file.\n");
            exit(EXIT_FAILURE);
        }
        BakeryProduct product = bakery_product_from_file(file);
        array [city] [season] = product;        

    }
    fclose(file);
}