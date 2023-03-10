#include <stdio.h>

#include "sim_engine.h"
#include "node.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table dt0;
static int node_id = 0;
static bool neighbor[MAX_NODES];

/* Students to write the following two routines, and maybe some others */

void rtinit0() {
  initDistanceTable(&dt0);

  dt0.costs[0][node_id] = 0;
  dt0.costs[1][node_id] = 1;
  dt0.costs[2][node_id] = 3;
  dt0.costs[3][node_id] = 7;
  neighbor[0] = false;
  neighbor[1] = true;
  neighbor[2] = true;
  neighbor[3] = true;

  sendPacket(node_id, 1, dt0);
  sendPacket(node_id, 2, dt0);
  sendPacket(node_id, 3, dt0);

  printf("Node %d initialized.\n", node_id);
  printdt0(&dt0);
}

void rtupdate0(struct rtpkt *rcvdpkt) {
  if(updateCosts(node_id, rcvdpkt->sourceid, &dt0, rcvdpkt, neighbor)) {
    sendPacket(node_id, 1, dt0);
    sendPacket(node_id, 2, dt0);
    sendPacket(node_id, 3, dt0);
    printf("Node %d updated by Node %d.\n", node_id, rcvdpkt->sourceid);
  } 
  printMatrix(dt0.costs, node_id);
}

void printdt0(struct distance_table *dtptr) {
  printf("                via     \n");
  printf("   D0 |    1     2    3 \n");
  printf("  ----|-----------------\n");
  printf("     1|  %3d   %3d   %3d\n",dtptr->costs[1][1],
	 dtptr->costs[1][2],dtptr->costs[1][3]);
  printf("dest 2|  %3d   %3d   %3d\n",dtptr->costs[2][1],
	 dtptr->costs[2][2],dtptr->costs[2][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][1],
	 dtptr->costs[3][2],dtptr->costs[3][3]);
}

void linkhandler0(int linkid, int newcost) {
  /* DON'T CHANGE */
}

