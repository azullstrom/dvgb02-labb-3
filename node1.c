#include <stdio.h>

#include "sim_engine.h"
#include "node.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table dt1;
static int node_id = 1;
static bool neighbor[MAX_NODES];

/* Students to write the following two routines, and maybe some others */

void rtinit1() {
  initDistanceTable(&dt1);

  dt1.costs[0][node_id] = 1;
  dt1.costs[1][node_id] = 0;
  dt1.costs[2][node_id] = 1;
  neighbor[0] = true;
  neighbor[1] = false;
  neighbor[2] = true;
  neighbor[3] = false;

  sendPacket(node_id, 0, dt1);
  sendPacket(node_id, 2, dt1);

  printf("Node %d initialized.\n", node_id);
  printdt1(&dt1);
}

void rtupdate1(struct rtpkt *rcvdpkt) {
  if(updateCosts(node_id, rcvdpkt->sourceid, &dt1, rcvdpkt, neighbor)) {
    sendPacket(node_id, 0, dt1);
    sendPacket(node_id, 2, dt1);
    printf("Node %d updated by Node %d.\n", node_id, rcvdpkt->sourceid);
  }
  printMatrix(dt1.costs, node_id);
}

void printdt1(struct distance_table *dtptr) {
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);
}

void linkhandler1(int linkid, int newcost) {
  /* DON'T CHANGE */
}


