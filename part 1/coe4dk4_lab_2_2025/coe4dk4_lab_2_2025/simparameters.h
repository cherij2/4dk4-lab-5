
/*
 * 
 * Simulation of A Single Server Queueing System
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

#ifndef _SIMPARAMETERS_H_
#define _SIMPARAMETERS_H_

/******************************************************************************/

#define PACKET_ARRIVAL_RATE 100 /* packets per second */
#define RUNLENGTH 10e6 /* packets */

#define QUEUE_SIZE_LIST 30
#define PACKET_SIZE_LIST 500, 1000, 1500, 2000, 2500 /* bits */

#define TICK_PERIOD_LIST 1e-3, 2e-3, 5e-3           /* seconds per tick */
#define LINK_RATE_LIST 1e6/*, 1.5e6, 0.5e6             bits per second */

/* Comma separated list of random seeds to run. */
#define RANDOM_SEED_LIST 400343389, 400381481

#define PACKET_XMT_TIME 1e-3 /* Seconds pers packet */
// #define PACKET_XMT_TIME_LIST 1e-3, 3e-3, 6e-3, 9e-3, 12e-3, 15e-3
#define BLIPRATE (RUNLENGTH/1000)

/******************************************************************************/

#endif /* simparameters.h */



