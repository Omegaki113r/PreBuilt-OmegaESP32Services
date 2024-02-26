/*
 * Project: OmegaESP32Services
 * File Name: OmegaFileSystemController.h
 * File Created: Friday, 23rd February 2024 4:53:37 pm
 * Author: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Last Modified: Monday, 26th February 2024 3:12:07 pm
 * Modified By: Omegaki113r (omegaki113r@gmail.com>)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 */



#ifndef __OMEGA_FILE_SYSTEM_CONTROLLER__
#define __OMEGA_FILE_SYSTEM_CONTROLLER__

#ifdef __cplusplus
extern "C"
{
#endif
    typedef enum
    {
        SUCCESS,
        FAILED,
        INVALID_OPENMODE,
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

    typedef uint64_t FileHandle;

    typedef struct
    {
        char *x;
    } OmegaFileSystemController_t;

    void OmegaFileSystemController_reset_module(OmegaFileSystemController_t *);
    FileSystemStatus OmegaFileSystemController_open_file(OmegaFileSystemController_t *, const FileHandle *, const char *, FileSystemOpenMode);
    FileSystemStatus OmegaFileSystemController_close_file(OmegaFileSystemController_t *, FileHandle);

#ifdef __cplusplus
}
#endif

#endif