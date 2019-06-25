#include "oidc_jws.h"
#include "oidc-agent/oidcd/jose/joseUtils.h"
#include "utils/logger.h"
#include "utils/oidc_error.h"

#include <string.h>

char* jws_sign(const char* plain, cjose_jwk_t* jwk, const char* alg) {
  if (plain == NULL || jwk == NULL || alg == NULL) {
    oidc_setArgNullFuncError(__func__);
    return NULL;
  }
  cjose_err       err;
  cjose_header_t* hdr = cjose_getSignHeader(alg);
  cjose_jws_t*    jws =
      cjose_jws_sign(jwk, hdr, (uint8_t*)plain, strlen(plain), &err);
  secFreeJoseHeader(hdr);
  if (jws == NULL) {
    char* err_msg = oidc_sprintf("jws error: %s", err.message);
    oidc_setInternalError(err_msg);
    logger(ERROR, err_msg);
    secFree(err_msg);
    return NULL;
  }

  char* ret = export_jws(jws);
  secFreeJWS(jws);
  return ret;
}

oidc_error_t jws_verify(const char* signed_msg, cjose_jwk_t* jwk) {
  if (signed_msg == NULL || jwk == NULL) {
    oidc_setArgNullFuncError(__func__);
    return oidc_errno;
  }
  cjose_err    err;
  cjose_jws_t* jws = import_jws(signed_msg);
  if (jws == NULL) {
    return oidc_errno;
  }
  if (!cjose_jws_verify(jws, jwk, &err)) {
    secFreeJWS(jws);
    // TODO
    oidc_errno = OIDC_EJWSVERIF;
    return oidc_errno;
  }
  secFreeJWS(jws);
  return OIDC_SUCCESS;
}

cjose_jws_t* import_jws(const char* sign) {
  if (sign == NULL) {
    oidc_setArgNullFuncError(__func__);
    return NULL;
  }
  cjose_err    err;
  cjose_jws_t* jws = cjose_jws_import(sign, strlen(sign), &err);
  if (jws == NULL) {
    char* err_msg = oidc_sprintf("jws import error: %s", err.message);
    oidc_setInternalError(err_msg);
    logger(ERROR, err_msg);
    secFree(err_msg);
    return NULL;
  }
  return jws;
}

char* export_jws(cjose_jws_t* jws) {
  if (jws == NULL) {
    oidc_setArgNullFuncError(__func__);
    return NULL;
  }
  cjose_err   err;
  const char* tmp = NULL;
  cjose_jws_export(jws, &tmp, &err);
  if (tmp == NULL) {
    char* err_msg = oidc_sprintf("jws export error: %s", err.message);
    oidc_setInternalError(err_msg);
    logger(ERROR, err_msg);
    secFree(err_msg);
    return NULL;
  }
  char* ret = oidc_strcopy(tmp);
  return ret;
}

void secFreeJWS(cjose_jws_t* jws) { cjose_jws_release(jws); }