#include "running_server.h"

#include "utils/agentLogger.h"
#include "utils/listUtils.h"
#include "utils/memory.h"
#include "utils/stringUtils.h"

static list_t* servers = NULL;

void _secFreeRunningServer(struct running_server* s) {
  secFree(s->state);
  secFree(s);
}

int matchRunningServer(char* state, struct running_server* s) {
  return strequal(s->state, state);
}

void addServer(struct running_server* running_server) {
  if (servers == NULL) {
    servers        = list_new();
    servers->free  = (void(*)(void*)) & _secFreeRunningServer;
    servers->match = (matchFunction)matchRunningServer;
  }
  list_rpush(servers, list_node_new(running_server));
  agent_log(DEBUG, "Added Server. Now %d server run", servers->len);
}

pid_t removeServer(const char* state) {
  if (servers == NULL) {
    agent_log(DEBUG, "No servers running");
    return -1;
  }
  list_node_t* n = findInList(servers, (char*)state);
  if (n == NULL) {
    agent_log(DEBUG, "No server found for state %s", state);
    return -1;
  }
  pid_t pid = ((struct running_server*)n->val)->pid;
  list_remove(servers, n);
  agent_log(DEBUG, "Removed Server. Now %d server run", servers->len);
  return pid;
}
