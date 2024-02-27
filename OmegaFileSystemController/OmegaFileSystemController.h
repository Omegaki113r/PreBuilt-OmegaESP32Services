/*
 * Project: OmegaESP32Services
 * File Name: OmegaFileSystemController.h
 * File Created: Friday, 23rd February 2024 4:53:37 pm
 * Author: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Last Modified: Tuesday, 27th February 2024 5:15:07 pm
 * Modified By: Omegaki113r (omegaki113r@gmail.com>)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 *
 * 27-02-2024	0m3g4	TODO
 *
 * 26-02-2024	0m3g4	basics of the FileSystemController code added
 *
 * 23-02-2024   0m3g4   open file and close file feature implemented
 *
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
        FILE_HANDLE_NOT_EXIST,
        NO_MEM,
        END_OF_FILE,
        UNKNOWN
    } FileSystemStatus;

    typedef enum
    {
        READING = 1 << 0,
        WRITING = 1 << 1,
        APPEND = 1 << 2,
        OVERWRITE = 1 << 3,
    } FileSystemOpenMode;

    typedef enum
    {
        READ_LINE,
        READ_CHUNK,
        READ_ALL,
    } FileSystemReadMode;

    typedef uint64_t FileHandle;

    typedef struct
    {
        uint8_t *in_out_buffer;
        size_t buffer_size;
        size_t read_written_size;
        FileHandle file_handle;
    } OmegaFileData_t;
    typedef struct
    {
        OmegaFileData_t in_out_data;
    } OmegaFileSystemController_t;

    void OmegaFileSystemController_reset_module(OmegaFileSystemController_t *);
    FileSystemStatus OmegaFileSystemController_open_file(OmegaFileSystemController_t *, const FileHandle *, const char *, FileSystemOpenMode);
    FileSystemStatus OmegaFileSystemController_close_file(OmegaFileSystemController_t *, FileHandle);
    FileSystemStatus OmegaFileSystemController_read_file(OmegaFileSystemController_t *, FileHandle, FileSystemReadMode);
#ifdef __cplusplus
}
#endif

#endif