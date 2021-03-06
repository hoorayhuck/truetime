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

#ifndef SET_DATA
#define SET_DATA

#include "getnode.cpp"

void ttSetDataAux(const char *nameOfTask, const mxArray *data) {  
  DataNode* dn = getNode(nameOfTask, rtsys->taskList);
  if (dn == NULL) {
    char buf[200];
    sprintf(buf, "ttSetData: Non-existent task '%s'!", nameOfTask);
    TT_MEX_ERROR(buf);
    return;
  }
  UserTask* task = (UserTask*) dn->data; 
  if (task->dataMATLAB == NULL) {
    char buf[200];
    sprintf(buf, "ttSetData: Task '%s' doesn't have data!", nameOfTask);
    TT_MEX_ERROR(buf);
    return;
  }
  mxDestroyArray(task->dataMATLAB);
  task->dataMATLAB = mxDuplicateArray(data);
  mexMakeArrayPersistent(task->dataMATLAB);
}

/*void* ttGetData(char *nameOfTask) {  
  DataNode* dn = getNode(nameOfTask, rtsys->taskList);
  if (dn == NULL) {
    char buf[200];
    sprintf(buf, "ttGetPeriod: Non-existent task '%s'!", nameOfTask);
    TT_MEX_ERROR(buf);
  }
  UserTask* task = (UserTask*) dn->data; 
  if (task->data == NULL) {
    char buf[200];
    sprintf(buf, "ttGetData: Task '%s' doesn't have data!", nameOfTask);
    TT_MEX_ERROR(buf);
  }
  return task->data;
  
}*/
#endif
