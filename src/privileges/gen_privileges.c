#include "gen_privileges.h"

#include <seccomp.h>
#include <stdio.h>
#include <stdlib.h>

#include "privileges.h"

void initOidcGenPrivileges(
    __attribute__((unused)) struct arguments* arguments) {
  int             rc  = -1;
  scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_KILL);
  if (ctx == NULL) {
    perror("seccomp_init");
    exit(EXIT_FAILURE);
  }
  addGeneralSysCalls(ctx);
  addLoggingSysCalls(ctx);
  addPromptingSysCalls(ctx);
  addSocketSysCalls(ctx);
  addFileWriteSysCalls(ctx);
  addCryptSysCalls(ctx);
  addSignalHandlingSysCalls(
      ctx);  // needed if auth code flow is executed -> not needed if flow!=code
  addSleepSysCalls(ctx);

  rc = seccomp_load(ctx);
  seccomp_release(ctx);
  checkRc(rc, "seccomp_load", "");
  // access("STARTOFPROGRAM", F_OK);
}
