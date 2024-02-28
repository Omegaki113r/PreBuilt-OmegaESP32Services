/*
 * Project: OmegaESP32Services
 * File Name: OmegaHashController.h
 * File Created: Thursday, 22nd February 2024 4:42:02 pm
 * Author: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Last Modified: Thursday, 29th February 2024 1:28:47 am
 * Modified By: Omegaki113r (omegaki113r@gmail.com>)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 */

#ifndef __OMEGA_HASH_CONTROLLER__
#define __OMEGA_HASH_CONTROLLER__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <mbedtls/md.h>
#include <mbedtls/sha256.h>

    typedef enum
    {
        HSC_SUCCESS,
        HSC_FAILED,
        HSC_INVALID_PARAMETERS,
        HSC_HASH_ALGO_NOT_FOUND,
        HSC_NO_MEM,
        HSC_UNKNOWN
    } HashControllerStatus;

    typedef enum
    {
        HASH256,
    } HashAlgorithm;

    typedef struct
    {
        mbedtls_md_context_t ctx;
    } OmegaHashController_t;

    HashControllerStatus OmegaHashController_init(OmegaHashController_t *, HashAlgorithm);
    HashControllerStatus OmegaHashController_reset(OmegaHashController_t *);
    HashControllerStatus OmegaHashController_ingest_data_single(OmegaHashController_t *, const uint8_t *, const size_t, uint8_t *);
    HashControllerStatus OmegaHashController_ingest_data_streamed(OmegaHashController_t *, const uint8_t *, const size_t, uint8_t *out_buffer);

#ifdef __cplusplus
}
#endif

#endif