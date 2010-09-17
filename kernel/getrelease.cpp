/*
 * Copyright (c) 2009 Lund University
 *
 * Written by Anton Cervin, Dan Henriksson and Martin Ohlin,
 * Department of Automatic Control LTH, Lund University, Sweden.
 *   
 * This file is part of Truetime 2.0 beta.
 *
 * Truetime 2.0 beta is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Truetime 2.0 beta is distributed in the hope that it will be useful, but
 * without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Truetime 2.0 beta. If not, see <http://www.gnu.org/licenses/>
 */

#ifndef GET_RELEASE
#define GET_RELEASE

#include "getnode.cpp"

// get release of specific task
double ttGetRelease(const char *nameOfTask) {
    
  DataNode* dn = getNode(nameOfTask, rtsys->taskList);
  if (dn == NULL) {
    char buf[200];
    sprintf(buf, "ttGetRelease: Non-existent task '%s'!", nameOfTask);
    TT_MEX_ERROR(buf);
    return 0.0;
  }

  UserTask* task = (UserTask*) dn->data; 
  if (task->nbrInvocations == 0) {
    char buf[200];
    sprintf(buf, "ttGetRelease: No jobs for task '%s'!",nameOfTask);
    TT_MEX_ERROR(buf);
    return 0.0;
  }

  return task->release;
}

// get release of calling task
double ttGetRelease() {

  if (!rtsys->running->isUserTask()) {
    TT_MEX_ERROR("ttGetRelease: Can not be called by interrupt handler!");
    return 0.0;
  }

  UserTask* task = (UserTask*) (rtsys->running); 

  return task->release;
}

#endif
