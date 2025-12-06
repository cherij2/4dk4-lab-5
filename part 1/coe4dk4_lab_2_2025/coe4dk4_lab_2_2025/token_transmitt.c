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

/******************************************************************************/

#include <stdio.h>
#include "main.h"
#include "token_arr.h"

/******************************************************************************/

/*
 * This function will schedule a token arrival event at a time given by
 * event_time. At that time the function "token_arrival_event" (located in
 * token_gen.c) is executed. Tokens are generated at regular intervals to
 * replenish the token bucket used in the leaky bucket algorithm.
 */

long int
schedule_token_arrival_event(Simulation_Run_Ptr simulation_run,
                              double event_time)
{
  Event event;

  event.description = "Token Arrival";
  event.function = token_arrival_event;
  event.attachment = (void *) NULL;

  return simulation_run_schedule_event(simulation_run, event, event_time);
}

/******************************************************************************/

/*
 * This is the event function which is executed when a token arrival event
 * occurs. A token is added to the token queue if there is space. If the token
 * queue is full, the token is lost (discarded). Tokens are generated at
 * regular intervals to implement the token bucket rate limiting algorithm.
 */

void
token_arrival_event(Simulation_Run_Ptr simulation_run, void * ptr)
{
  Simulation_Run_Data_Ptr data;

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

  /* 
   * Token bucket algorithm: add a token if there is space in the token queue.
   * If the token queue is full, the token is lost (dropped).
   */
  
  if (fifoqueue_size(data->token_buffer) < data->token_queue_size) {
    /* There is space in the token queue, add a token */
    int *token = (int *) xmalloc(sizeof(int));
    *token = 1;  /* Token value */
    fifoqueue_put(data->token_buffer, (void*) token);
  } else {
    /* Token queue is full, drop the token */
    data->lost_tokens_count++;
  }

  /* 
   * Schedule the next token arrival event after one token interval.
   */

  schedule_token_arrival_event(simulation_run,
                               simulation_run_get_time(simulation_run) + 
                               data->token_interval);
}

/******************************************************************************/
