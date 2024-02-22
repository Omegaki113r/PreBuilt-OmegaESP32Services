#ifndef __OMEGA_HASH_CONTROLLER__
#define __OMEGA_HASH_CONTROLLER__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <string.h>

#include <mbedtls/sha256.h>

    typedef struct
    {
        mbedtls_sha256_context ctx;
    } OmegaHashController_t;

    void OmegaHashController_reset_module(OmegaHashController_t *);

#ifdef __cplusplus
}
#endif

#endif