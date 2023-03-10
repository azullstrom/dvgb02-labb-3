#include <stdio.h>

#include "sim_engine.h"
#include "node.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table dt2;
static int node_id = 2;
static bool neighbor[MAX_NODES];

/* Students to write the following two routines, and maybe some others */

void rtinit2() {
  initDistanceTable(&dt2);

  dt2.costs[0][node_id] = 3;
  dt2.costs[1][node_id] = 1;
  dt2.costs[2][node_id] = 0;
  dt2.costs[3][node_id] = 2;
  neighbor[0] = true;;
  neighbor[1] = true;
  neighbor[2] = false;
  neighbor[3] = true;

  sendPacket(node_id, 0, dt2);
  sendPacket(node_id, 1, dt2);
  sendPacket(node_id, 3, dt2);

  printf("Node %d initialized.\n", node_id);
  printdt2(&dt2);
}

void rtupdate2(struct rtpkt *rcvdpkt) {
  if(updateCosts(node_id, rcvdpkt->sourceid, &dt2, rcvdpkt, neighbor)) {
    sendPacket(node_id, 0, dt2);
    sendPacket(node_id, 1, dt2);
    sendPacket(node_id, 3, dt2);
    printf("Node %d updated by Node %d.\n", node_id, rcvdpkt->sourceid);
  } 
  printMatrix(dt2.costs, node_id);
}

void printdt2(struct distance_table *dtptr) {
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}







