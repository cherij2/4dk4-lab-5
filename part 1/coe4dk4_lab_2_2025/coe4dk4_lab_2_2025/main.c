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
  double xmt_times[] = {PACKET_XMT_TIME_LIST, 0};

  unsigned random_seed;
  double queue_size;
  double xmt_time;
  int i = 0, j, k;

  while ((queue_size = queue_sizes[i++]) != 0) {
    data.queue_size = (int) queue_size;

    k = 0;
    while ((xmt_time = xmt_times[k++]) != 0) {

      j = 0; /* reset seeds for each transmission time */
      while ((random_seed = RANDOM_SEEDS[j++]) != 0) {

        simulation_run = simulation_run_new(); /* Create a new simulation run. */
        simulation_run_attach_data(simulation_run, (void *) &data);

        /* Initialize per-run stats. */
        data.blip_counter = 0;
        data.arrival_count = 0;
        data.number_of_packets_processed = 0;
        data.accumulated_delay = 0.0;
        data.random_seed = random_seed;
        data.dropped_count = 0;
        data.packet_xmt_time = xmt_time;

        /* Create the packet buffer and transmission link. */
        data.buffer = fifoqueue_new();
        data.link   = server_new();

        /* Set per-run transmission time (service time). */
        set_packet_transmission_time(xmt_time);

        /* Set RNG seed and schedule first arrival at t = 0. */
        random_generator_initialize(random_seed);
        schedule_packet_arrival_event(simulation_run,
              simulation_run_get_time(simulation_run));

        /* Execute events until finished. */
        while (data.number_of_packets_processed < RUNLENGTH) {
          simulation_run_execute_event(simulation_run);
        }

        /* Output results and clean up. */
        output_results(simulation_run);
        cleanup_memory(simulation_run);
      }
    }
  }

  return 0;
}
