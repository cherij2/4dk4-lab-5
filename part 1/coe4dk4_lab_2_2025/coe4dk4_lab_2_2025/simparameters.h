
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
// #define PACKET_LENGTH 1e3 /* bits */
// #define LINK_BIT_RATE 1e6 /* bits per second */
#define RUNLENGTH 10e5 /* packets */
#define QUEUE_SIZE_LIST 10
#define TOKEN_QUEUE_SIZE_LIST 3 
#define BUFFER_SIZE 50 /* max packets waiting in queue */


/* Comma separated list of random seeds to run. */
#define RANDOM_SEED_LIST 400343389, 400381481


#define PACKET_XMT_TIME 2.5e-3, 3e-3, 6e-3, 9e-3, 12e-3, 15e-3, 20e-3  /* seconds per packet */
#define BLIPRATE (RUNLENGTH/1000)

#define N_LIST 2500, 5000, 7500, 10000, 15000, 20000 /* bucket capacity in bits */
#define CLOCK_TICK_PERIOD 0.01, 0.02, 0.04, 0.08, 0.12, 0.16, 0.24, 0.3 /* in microseconds */

/******************************************************************************/

#endif /* simparameters.h */



