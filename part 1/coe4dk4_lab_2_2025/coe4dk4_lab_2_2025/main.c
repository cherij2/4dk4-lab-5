/*
 * 
 * Simulation_Run of A Single Server Queueing System
 * 
 * Copyright (C) 2014 Terence D. Todd Hamilton, Ontario, CANADA,
 * todd@mcmaster.ca
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "output.h"
#include "simparameters.h"
#include "packet_arrival.h"
#include "packet_transmission.h"
#include "cleanup_memory.h"
#include "trace.h"
#include "main.h"

/******************************************************************************/

/*
 * main.c declares and creates a new simulation_run with parameters defined in
 * simparameters.h. The code creates a fifo queue and server for the single
 * server queueuing system. It then loops through queue sizes, transmission
 * times, and random seeds, doing a separate simulation run for each. To start a
 * run, it schedules the first packet arrival event. When each run is finished,
 * output is printed on the terminal.
 */

int
main(void)
{
  Simulation_Run_Ptr simulation_run;
  Simulation_Run_Data data;

  /* Seeds, queue sizes (B), and transmission times (seconds/packet) to sweep. */
  unsigned RANDOM_SEEDS[] = {RANDOM_SEED_LIST, 0};
  double queue_sizes[] = {QUEUE_SIZE_LIST, 0};
  double tick_periods[] = {TICK_PERIOD_LIST, 0};
  double link_rates[] = {LINK_RATE_LIST, 0};

  unsigned random_seed;
  double link_rate;
  double tick_period;
  double queue_size;
  double xmt_time;
  int i = 0, j, k;

  while ((queue_size = queue_sizes[i++]) != 0) {
    data.queue_size = (int) queue_size;

    k = 0;
    double tick_period;
    while ((tick_period = tick_periods[k++]) != 0) {

      int r = 0;
      double link_rate;
      while ((link_rate = link_rates[r++]) != 0) {

        j = 0;
        while ((random_seed = RANDOM_SEEDS[j++]) != 0) {

          simulation_run = simulation_run_new();
          simulation_run_attach_data(simulation_run, (void *) &data);

          data.blip_counter = 0;
          data.arrival_count = 0;
          data.number_of_packets_processed = 0;
          data.accumulated_delay = 0.0;
          data.random_seed = random_seed;
          data.dropped_count = 0;
          data.bits_sent = 0.0;
          data.tick_period = tick_period;
          data.bits_per_tick = (long)(link_rate * tick_period);
          data.packet_xmt_time = 0.0; /* unused for part 2 */

          data.buffer = fifoqueue_new();
          data.link   = server_new(); /* unused */

          random_generator_initialize(random_seed);

          /* Schedule first arrival and first bucket tick */
          schedule_packet_arrival_event(simulation_run,
                simulation_run_get_time(simulation_run));
          schedule_bucket_tick_event(simulation_run,
                simulation_run_get_time(simulation_run));

          while (data.number_of_packets_processed < RUNLENGTH) {
            simulation_run_execute_event(simulation_run);
          }

          output_results(simulation_run);
          cleanup_memory(simulation_run);
        }
      }
    }
  }
