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

#ifndef _TOKEN_GEN_H_
#define _TOKEN_GEN_H_

/******************************************************************************/

#include "simlib.h"

/******************************************************************************/

/*
 * Function prototypes
 */

void
token_arrival_event(Simulation_Run_Ptr, void*);

long
schedule_token_arrival_event(Simulation_Run_Ptr, double);

/******************************************************************************/

#endif /* token_gen.h */
