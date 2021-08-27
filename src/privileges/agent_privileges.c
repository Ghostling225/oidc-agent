#include "agent_privileges.h"

#include <seccomp.h>
#include <stdio.h>
#include <stdlib.h>

#include "privileges.h"

void initOidcAgentPrivileges(struct arguments* arguments) {
  int             rc  = -1;
  scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_KILL);
  if (ctx == NULL) {
    perror("seccomp_init");
    exit(EXIT_FAILURE);
  }
  addGeneralSysCalls(ctx);
  addLoggingSysCalls(ctx);
  // addPrintingSysCalls(ctx);
  if (arguments->kill_flag) {
    addKillSysCall(ctx);
  }
  addSocketSysCalls(ctx);
  addAgentIpcSysCalls(ctx);
  addCryptSysCalls(ctx);
  addDaemonSysCalls(ctx);
  addHttpSysCalls(ctx);
  addHttpServerSysCalls(ctx);

  rc = seccomp_load(ctx);
  seccomp_release(ctx);
  checkRc(rc, "seccomp_load", "");
  // access("STARTOFPROGRAM", F_OK);
}
