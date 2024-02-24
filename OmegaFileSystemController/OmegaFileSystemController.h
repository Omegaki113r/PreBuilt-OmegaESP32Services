#ifndef __OMEGA_FILE_SYSTEM_CONTROLLER__
#define __OMEGA_FILE_SYSTEM_CONTROLLER__

#ifdef __cplusplus
extern "C"
{
#endif

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

    typedef enum
    {
        SUCCESS,
        FAILED,
        FILE_NOT_EXIST,
        NO_MEM,
        UNKNOWN
    } FileSystemStatus;

    typedef enum
    {
        READING = 1 << 0,
        WRITING = 1 << 1,
        APPEND = 1 << 2,
        OVERWRITE = 1 << 3,
    } FileSystemOpenMode;

    typedef uint32_t FileHandle;

    typedef struct
    {
        char *x;
    } OmegaFileSystemController_t;

    void OmegaFileSystemController_reset_module(OmegaFileSystemController_t *);
    FileSystemStatus OmegaFileSystemController_open_file(OmegaFileSystemController_t *, FileHandle *, const char *, FileSystemOpenMode);
    FileSystemStatus OmegaFileSystemController_close_file(OmegaFileSystemController_t *, FileHandle);

#ifdef __cplusplus
}
#endif

#endif