/*
 * Project: OmegaESP32Services
 * File Name: OmegaFileSystemController.h
 * File Created: Friday, 23rd February 2024 4:53:37 pm
 * Author: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Last Modified: Thursday, 29th February 2024 1:46:19 am
 * Modified By: Omegaki113r (omegaki113r@gmail.com>)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 *
 * 28-02-2024	0m3g4	POSIX on x86/64 and SPIFFS on Xtensa seems to have different notion of <NEWLINE> character     POSIX => \n      SPIFFS => \r\n therefore had to fix that inorder to hash function to work
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
        FSC_SUCCESS,
        FSC_FAILED,
        FSC_INVALID_OPENMODE,
        FSC_INVALID_PARAMETERS,
        FSC_FILE_NOT_EXIST,
        FSC_FILE_HANDLE_NOT_EXIST,
        FSC_NO_MEM,
        FSC_END_OF_FILE,
        FSC_UNKNOWN
    } FileSystemControllerStatus;

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

    FileSystemControllerStatus OmegaFileSystemController_init(OmegaFileSystemController_t *);
    FileSystemControllerStatus OmegaFileSystemController_open_file(OmegaFileSystemController_t *, const FileHandle *, const char *, FileSystemOpenMode);
    FileSystemControllerStatus OmegaFileSystemController_close_file(OmegaFileSystemController_t *, FileHandle);
    FileSystemControllerStatus OmegaFileSystemController_read_file(OmegaFileSystemController_t *, FileHandle, FileSystemReadMode);
#ifdef __cplusplus
}
#endif

#endif