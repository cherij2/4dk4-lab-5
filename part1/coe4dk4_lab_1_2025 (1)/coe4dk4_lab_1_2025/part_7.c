/*
 *
 * Simulation of Single Server Queueing System
 * 
 * Copyright (C) 2014 Terence D. Todd Hamilton, Ontario, CANADA,
 * todd@mcmaster.ca
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option) any later
 * version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/*******************************************************************************/

#include <stdio.h>
#include "simlib.h"
#include <time.h>

/*******************************************************************************/

/*
 * Simulation Parameters
 */

// #define RANDOM_SEED 5259140
#define NUMBER_TO_SERVE 50e6
//#define QUEUE_MAX 10
// #define SERVICE_TIME 10
// #define ARRIVAL_RATE 0.1

#define BLIP_RATE 10000

/*******************************************************************************/

/*
 * main() uses various simulation parameters and creates a clock variable to
 * simulate real time. A loop repeatedly determines if the next event to occur
 * is a customer arrival or customer departure. In either case the state of the
 * system is updated and statistics are collected before the next
 * iteration. When it finally reaches NUMBER_TO_SERVE customers, the program
 * outputs some statistics such as mean delay.
 */

int main()
{

  int seeds[10] = {400343389, 987654321, 400321456, 789456123, 159357258, 456123789, 321654987, 852741963, 147258369, 963852741};
  int queue_caps[5] = {10, 50, 100, 500, 1000, 2500};

  int customers_rejected = 0;
  float rejection_ratio = 0;
  int customers_in_queue = 0;
  int q = 0;


  for(int q = 0; q <5; q++) {
    int QUEUE_MAX = queue_caps[q];
    for(float i = 0.01; i <= 0.61 ;i += 0.12){
      
      double ARRIVAL_RATE = i;
      double SERVICE_TIME_exponential = 10;
      //double SERVICE_TIME = exponential_generator((double)10);
    
      for (int s = 0; s < 10; s++) {
        int RANDOM_SEED = seeds[s];

    
        double clock = 0; /* Clock keeps track of simulation time. */

        /* System state variables. */
        int number_in_system = 0;
        double next_arrival_time = 0;
        double next_departure_time = 0;

        /* Data collection variables. */
        long int total_served = 0;
        long int total_arrived = 0;

        double total_busy_time = 0;
        double integral_of_n = 0;
        double last_event_time = 0;

        /* Set the seed of the random number generator. */
        random_generator_initialize(RANDOM_SEED);

        /* Process customers until we are finished. */
        while (total_served < NUMBER_TO_SERVE) {

          /* Test if the next event is a customer arrival or departure. */
        if(number_in_system == 0 || next_arrival_time < next_departure_time) { //SYTEM ARRIVAL CODE

          /*
            * A new arrival is occurring.
            */
            
            clock = next_arrival_time;
            next_arrival_time = clock + exponential_generator((double) 1/ARRIVAL_RATE);

            /* Update our statistics. */
            integral_of_n += number_in_system * (clock - last_event_time);
            last_event_time = clock;

            total_arrived++;
            
            /*
            Since mean delay only depends on number_in_system(integral_of_n) and total served, we just need to control number_in_system to change the graph we need to obtain (mean delay vs arrival times M/M/1)
            */
            if(number_in_system < QUEUE_MAX+1) { //+1 for the element in service
              number_in_system++;
            }
            else {
              customers_rejected++;
            }
            /* If this customer has arrived to an empty system, start its
          service right away. */
            if(number_in_system == 1) next_departure_time = clock + exponential_generator((double)10);
          
          


        } else { //SYSTEM DEPARTURE CODE

          /*
            * A customer departure is occuring. 
            */

          clock = next_departure_time;

          /* Update our statistics. */
          integral_of_n += number_in_system * (clock - last_event_time);
          last_event_time = clock;

          number_in_system--;
          customers_in_queue--;
          total_served++;
          total_busy_time += exponential_generator((double)10);

          /* 
            * If there are other customers waiting, start one in service
            * right away.
            */

          if(number_in_system > 0) next_departure_time = clock + exponential_generator((double)10);

          /* 
            * Every so often, print an activity message to show we are active. 
            */

          /*if (total_served % BLIP_RATE == 0)
            printf("Customers served = %ld (Total arrived = %ld)\r",
              total_served, total_arrived);*/
        }

        }
  /*
    int customers_rejected = 0;
    float rejection_ratio = 0;
    int customers_in_queue = 0;
  */

        rejection_ratio = customers_rejected / total_arrived;
        /* Output final results. */
        //printf("\nUtilization = %f\n", total_busy_time/clock);
        //printf("Fraction served = %f\n", (double) total_served/total_arrived);
        //printf("Mean number in system = %f\n", integral_of_n/clock);
        //printf("Mean delay = %f\n", integral_of_n/total_served);
        printf("%d, %f, %ld, %ld, %f, %f, %f , %f, %f\n" ,RANDOM_SEED, ARRIVAL_RATE, total_arrived, total_served, integral_of_n/total_served, total_busy_time/clock, (double) total_served/total_arrived, integral_of_n/clock, rejection_ratio);
        /* Halt the program before exiting. */
        //printf("Hit Enter to finish ... \n");
        //getchar(); 

        

      }
      
    }
  }
  return 0;
}