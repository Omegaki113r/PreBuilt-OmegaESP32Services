/**
 * @file OmegaHashController.h
 * @author Chameera Subasinghe
 * @date Friday, 1st March 2024 2:28:17 am
 * @copyright Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * */
/*
 * Project: OmegaESP32Services
 * File Name: OmegaHashController.h
 * File Created: Friday, 1st March 2024 2:28:17 am
 * Author: Chameera Subasinghe (omegaki113r@gmail.com)
 * -----
 * Last Modified: Tuesday, 28th May 2024 8:16:03 pm
 * Modified By: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 *
 * 05-03-2024	0m3g4	Declared the OmegaHashController_deinit
 *
 * 03-03-2024	0m3g4	Writing documentation that generate doxygen docs
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

    /// @brief ReturnTypes/StatusCodes for the Hash Controller
    typedef enum
    {
        /// @brief Indicates success in any operation related to HashController
        HSC_SUCCESS,
        /// @brief Indicates failure in any operation related to HashController
        HSC_FAILED,
        /// @brief Indicates failure due to invalid parameters provided to functions/sub-routines and/or structures
        HSC_INVALID_PARAMETERS,
        /// @brief Indicates that provided HashAlgorithm parameter in `OmegaHashController_init` is not valid.
        HSC_HASH_ALGO_NOT_FOUND,
        /**
         * @brief Indicates that API is trying to use unsupported hash algorithms.
         * mbedtls supports many hash algorithms [described inside `mbedtls_md_type_t`].
         * But this controller only supports SHA256 as of 2024-03-03
         *
         */
        HSC_HASH_ALGO_NOT_SUPPORTED,
        /// @brief Indicate that there is not enough Heap/Stack memory to allocate for the necessary operations
        HSC_NO_MEM,
        /// @brief Indicates Unknown error has occured
        HSC_UNKNOWN
    } HashControllerStatus;

    /// @brief Hash Algorithms that are supported by Hash Controller
    typedef enum
    {
        /// @brief abstraction for `MBEDTLS_MD_SHA256` inside md.h `mbedtls_md_type_t`
        HASH256 = MBEDTLS_MD_SHA256,
    } HashAlgorithm;

    typedef uint64_t HashControllerHandle;

    /**
     * @brief Initialize and allocate required memory for the specified hash algorithm for the HashController instance.
     *
     * @param in_controller Input parameter. Instance of the `OmegaHashController_t` that needs to be initialized. Cannot be `NULL`
     * @param in_hash_algorithm Input parameter. Indicates the hash algorithm that is going to be used by this instance of HashController
     * @return HashControllerStatus HSC_SUCCESS if `OmegaHashController_t` initialized successfully.
     */
    HashControllerHandle OmegaHashController_init(HashAlgorithm in_hash_algorithm);
    /**
     * @brief After a successful `OmegaHashController_ingest_data_streamed()` hashing operation, `OmegaHashController_t` needs to be reset before doing another hash operation. Purpose of this function is to reset all the internal variables, free old memory and allocate new memory.
     *          This function isn't required to be called if the hash operation was `OmegaHashController_ingest_data_single()`. This function will be called internally in `OmegaHashController_ingest_data_single()`
     *
     * @param in_controller Input parameter. Instance of the `OmegaHashController_t` that needs to be reset
     * @return HashControllerStatus HSC_SUCCESS if `OmegaHashController_t` reset succesfully
     */
    HashControllerStatus OmegaHashController_reset(HashControllerHandle in_handle);
    /**
     * @brief If all the bytes needs to be hashed is known before hashing and/or system has enough heap/stack memory to allocate to all the bytes, This function can be called.
     *
     * @param in_controller Input parameter. Instance of the `OmegaHashController_t` that previously initialized/reset. Therefore this cannot be NULL
     * @param in_buffer Input parameter. buffer that contains the bytes needs to be hashed. Cannot be NULL.
     * @param in_buffer_size Input parameter. Size of the input buffer that was provided in the `in_buffer` parameter. Cannot be NULL, 0 or negative.
     * @param out_buffer Output parameter. Result of the hash operation will be set in this byte buffer. This needs to be in the correct size.
     * @return HashControllerStatus HSC_SUCCESS if hash operation was successful.
     */
    HashControllerStatus OmegaHashController_ingest_data_single(HashControllerHandle in_handle, const uint8_t *in_buffer, const size_t in_buffer_size, const uint8_t *out_buffer);
    /**
     * @brief If all the bytes needs to be hashed is not known before hashing and/or system doesn't have enough heap/stack memory to allocate to all the bytes, This function can be called.
     *          To ingest the input data as well as retireve the final hash output this function is being used with providing some parameters as NULL
     *
     * @param in_controller Input parameter. Instance of the `OmegaHashController_t` that previously initialized/reset. Therefore this cannot be NULL
     * @param in_buffer Input parameter. buffer that contains the bytes needs to be hashed. This cannot be NULL during data ingestion and can be NULL when retireving hashed data.
     * @param in_buffer_size Input parameter. Size of the input buffer that was provided in the `in_buffer` parameter. This cannot be NULL during data ingestion and can be NULL, 0 or negative when retireving hashed data.
     * @param out_buffer Output parameter. Result of the hash operation will be set in this byte buffer. This can be NULL during ingestion of data. Cannot be NULL when retireving hashed data.
     * @return HashControllerStatus HSC_SUCCESS if the hash operations [ingestion and digestion] was successful.
     */
    HashControllerStatus OmegaHashController_ingest_data_streamed(HashControllerHandle in_handle, const uint8_t *in_buffer, const size_t in_buffer_size, const uint8_t *out_buffer);
    /**
     * @brief used to free all the allocated resources
     *
     * @param in_controller Input parameter. Instance of `OmegaHashController_t` that previously initialized.
     * @return HashControllerStatus  HSC_SUCCESS if the freeing of resources was successful
     */
    HashControllerStatus OmegaHashController_deinit(HashControllerHandle in_handle);
#ifdef __cplusplus
}
#endif

#endif