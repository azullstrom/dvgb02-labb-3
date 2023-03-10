#include <stdio.h>

#include "sim_engine.h"
#include "node.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table dt3;
static int node_id = 3;
static bool neighbor[MAX_NODES];

/* Students to write the following two routines, and maybe some others */

void rtinit3() {
  initDistanceTable(&dt3);

  dt3.costs[0][node_id] = 7;
  dt3.costs[2][node_id] = 2;
  dt3.costs[3][node_id] = 0;
  neighbor[0] = true;
  neighbor[1] = false;
  neighbor[2] = true;
  neighbor[3] = false;

  sendPacket(node_id, 0, dt3);
  sendPacket(node_id, 2, dt3);

  printf("Node %d initialized.\n", node_id);
  printdt3(&dt3);
}


void rtupdate3(struct rtpkt *rcvdpkt) {
  if(updateCosts(node_id, rcvdpkt->sourceid, &dt3, rcvdpkt, neighbor)) {
    sendPacket(node_id, 0, dt3);
    sendPacket(node_id, 2, dt3);
    printf("Node %d updated by Node %d.\n", node_id, rcvdpkt->sourceid);
  }
  printMatrix(dt3.costs, node_id);
}

void printdt3(struct distance_table *dtptr) {
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
}







