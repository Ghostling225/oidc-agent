#include "oidc-add.h"

#include "account/account.h"
#include "add_handler.h"
#include "privileges/add_privileges.h"
#include "utils/disableTracing.h"
#include "utils/file_io/fileUtils.h"

#include <syslog.h>

int main(int argc, char** argv) {
  platform_disable_tracing();
  openlog("oidc-add", LOG_CONS | LOG_PID, LOG_AUTHPRIV);
  setlogmask(LOG_UPTO(LOG_NOTICE));
  struct arguments arguments;

  initArguments(&arguments);

  argp_parse(&argp, argc, argv, 0, 0, &arguments);
  if (arguments.debug) {
    setlogmask(LOG_UPTO(LOG_DEBUG));
  }
  if (arguments.seccomp) {
    initOidcAddPrivileges(&arguments);
  }

  if (arguments.list) {
    add_handleList();
    return EXIT_SUCCESS;
  }
  if (arguments.removeAll) {
    add_handleRemoveAll();
    return EXIT_SUCCESS;
  }
  add_assertAgent();
  if (arguments.lock || arguments.unlock) {
    add_handleLock(arguments.lock);
    return EXIT_SUCCESS;
  }
  checkOidcDirExists();

  char* account = arguments.args[0];
  if (!accountConfigExists(account)) {
    printError("No account configured with that short name\n");
    exit(EXIT_FAILURE);
  }
  if (arguments.print) {
    add_handlePrint(account, &arguments);
    return EXIT_SUCCESS;
  }

  if (arguments.remove) {
    add_handleRemove(account);
  } else {
    add_handleAdd(account, &arguments);
  }

  return EXIT_SUCCESS;
}
