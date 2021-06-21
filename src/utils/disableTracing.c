/*
 * Copyright (c) 2016 Darren Tucker.  All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "disableTracing.h"
#include "utils/logger.h"

#define HAVE_SYS_PTRACE_H

#ifdef __linux__
#include <sys/prctl.h> /* For prctl() and PR_SET_DUMPABLE */
#elif __APPLE__
#include <sys/types.h>
// types must be included before ptrace
#include <sys/ptrace.h>
#endif
// #ifdef HAVE_PRIV_H
// #include <priv.h> /* For setpflags() and __PROC_PROTECT  */
// #endif

void platform_disable_tracing() {
#ifdef __linux__
  /* Disable ptrace on Linux without sgid bit */
  if (prctl(PR_SET_DUMPABLE, 0) != 0) {
    logger(ERROR, "unable to make the process undumpable");
  }
// #if defined(HAVE_SETPFLAGS) && defined(__PROC_PROTECT)
//   /* On Solaris, we should make this process untraceable */
//   if (setpflags(__PROC_PROTECT, 1) != 0)
//     printError("unable to make the process untraceable");
// #endif
#elif __APPLE__
  /* Mac OS X */
  if (ptrace(PT_DENY_ATTACH, 0, 0, 0) == -1)
    logger(ERROR, "unable to set PT_DENY_ATTACH");
#endif
}
