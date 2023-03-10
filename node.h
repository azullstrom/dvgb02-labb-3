#include "sim_engine.h"
#include <stdbool.h>
#include <stdio.h>

#define INF 999
#define MAX_NODES 4

struct distance_table {
  int costs[MAX_NODES][MAX_NODES];
};

/*Sends the distance table from source to destination. Declared in "node.h".*/
void sendPacket(int sourceid, int destid, struct distance_table dt);

/*Inits a struct distance_table to infinity. Declared in "node.h".*/
void initDistanceTable(struct distance_table* dt);

/*Updates the distance table and return true or false if updated or not. Declared in "node.h".*/
bool updateCosts(int src_id, int rx_id, struct distance_table* src_dt, struct rtpkt* rx_dt, bool neighbor[]);

/*Custom print function to print the whole distance table. Declared in "node.h".*/
void printMatrix(int costs[MAX_NODES][MAX_NODES], int nodeid);

void printMatrix2(int costs[MAX_NODES], int nodeid);

void printdt0(struct distance_table *dtptr);
void printdt1(struct distance_table *dtptr);
void printdt2(struct distance_table *dtptr);
void printdt3(struct distance_table *dtptr);