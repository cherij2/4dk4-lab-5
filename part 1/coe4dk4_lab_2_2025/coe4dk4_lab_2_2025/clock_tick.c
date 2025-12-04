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
#include "clock_tick.h"

/******************************************************************************/

/*
 * This function will schedule a clock tick event at a time given by
 * event_time. At that time the function "clock_tick_event" (located in
 * clock_tick.c) is executed. The clock tick event resets the bit counter
 * (n_malluable) allowing new transmissions to proceed.
 */

long int
schedule_clock_tick_event(Simulation_Run_Ptr simulation_run,
                          double event_time)
{
  Event event;

  event.description = "Clock Tick";
  event.function = clock_tick_event;
  event.attachment = (void *) NULL;

  return simulation_run_schedule_event(simulation_run, event, event_time);
}

/******************************************************************************/

/*
 * This is the event function which is executed when a clock tick event
 * occurs. It resets the bit counter (n_malluable) to its maximum value (n),
 * allowing a fresh window of transmission capacity for the next clock tick
 * period. It then schedules the next clock tick event.
 */

void
clock_tick_event(Simulation_Run_Ptr simulation_run, void * ptr)
{
  Simulation_Run_Data_Ptr data;

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

  /* 
   * Reset the bit counter for the next clock tick period.
   * This effectively creates a new window where n_malluable bits can be
   * transmitted until the next clock tick.
   */
  
  data->n_malluable = data->n;

  /* 
   * Schedule the next clock tick event after one clock tick period.
   */

  schedule_clock_tick_event(simulation_run,
                            simulation_run_get_time(simulation_run) + 
                            data->clock_tick_period);
}

/******************************************************************************/
