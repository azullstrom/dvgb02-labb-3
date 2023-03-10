#include "node.h"

void sendPacket(int sourceid, int destid, struct distance_table dt) {
  struct rtpkt packet;
  packet.sourceid = sourceid;
  packet.destid = destid;
  packet.mincost[0] = dt.costs[0][sourceid];
  packet.mincost[1] = dt.costs[1][sourceid];
  packet.mincost[2] = dt.costs[2][sourceid];
  packet.mincost[3] = dt.costs[3][sourceid];
  tolayer2(packet);
}

void initDistanceTable(struct distance_table* dt) {
  for(int i = 0; i < MAX_NODES; i++) {
    for(int j = 0; j < MAX_NODES; j++) {
      dt->costs[i][j] = INF;
    }
  }
}

bool updateCosts(int src_id, int rx_id, struct distance_table* src_dt, struct rtpkt* rx_dt, bool neighbor[]) {
  bool update = false;
  for(int i = 0; i < MAX_NODES; i++) {
    /* Store neighbor dt info in this dt */
    src_dt->costs[i][rx_id] = rx_dt->mincost[i];
    /* If current cost is > than sender nodes mincost to dst + the distance to the sender => update. */
    if(src_dt->costs[i][src_id] > rx_dt->mincost[i] + src_dt->costs[rx_id][src_id]) {
      src_dt->costs[i][src_id] = rx_dt->mincost[i] + src_dt->costs[rx_id][src_id];
      update = true;
    }
  }
  /* Updating non-neighbors based on neighbors distance tables/mincost and stores it in this dt. */
  for(int i = 0; i < MAX_NODES; i++) {
    for(int j = 0; j < MAX_NODES; j++) {
      if(src_dt->costs[j][i] > src_dt->costs[i][j] && !neighbor[i]) {
        src_dt->costs[j][i] = src_dt->costs[i][j];
        src_dt->costs[i][i] = 0;
      }
    }
  }
  return update;
}

void printMatrix(int costs[MAX_NODES][MAX_NODES], int nodeid) {
    printf("\n   D%d |    0    1    2    3 \n", nodeid);
    printf("------|---------------------\n");
    printf("     0|  %3d  %3d  %3d  %3d \n", costs[0][0], costs[0][1], costs[0][2], costs[0][3]);
    printf("     1|  %3d  %3d  %3d  %3d \n", costs[1][0], costs[1][1], costs[1][2], costs[1][3]);
    printf("     2|  %3d  %3d  %3d  %3d \n", costs[2][0], costs[2][1], costs[2][2], costs[2][3]);
    printf("     3|  %3d  %3d  %3d  %3d \n", costs[3][0], costs[3][1], costs[3][2], costs[3][3]);
}