/**
 * @file OmegaFileSystemController.h
 * @author Chameera Subasinghe
 * @date Friday, 1st March 2024 3:28:41 am
 * @copyright Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * */
/*
 * Project: OmegaESP32Services
 * File Name: OmegaFileSystemController.h
 * File Created: Friday, 1st March 2024 3:28:41 am
 * Author: Chameera Subasinghe (omegaki113r@gmail.com)
 * -----
 * Last Modified: Thursday, 7th March 2024 8:23:04 am
 * Modified By: Chameera Subasinghe (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 */

#ifndef __OMEGA_FILE_SYSTEM_CONTROLLER__
#define __OMEGA_FILE_SYSTEM_CONTROLLER__

#ifdef __cplusplus
extern "C"
{
#endif

    /// @brief ReturnTypes/StatusCodes for the File System Controller
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

    /**
     * @brief FileSystemOpenMode(s) that needs to be specified when calling `OmegaFileSystemController_open_file()`
     *
     * Possible combinations are,
     *      READING|WRITING|OVERWRITE
     *      READING|WRITING|APPEND
     *      READING
     *      WRITING|OVERWRITE
     *      WRITING|APPEND
     *
     */
    typedef enum
    {
        READING = 1 << 0,
        WRITING = 1 << 1,
        APPEND = 1 << 2,
        OVERWRITE = 1 << 3,
    } FileSystemOpenMode;

    /**
     * @brief ReadMode(s) that needs to be specified when calling `OmegaFileSystemController_read_file()`
     *
     * READ_LINE => Reads set of characters till '\n' including the '\n'. If EOF (End Of File) met just the content upto EOF is read
     * READ_CHUNK => Read only pre-specified number of bytes
     * READ_ALL => Read the whole file in 1 go
     *
     */
    typedef enum
    {
        READ_LINE,
        READ_CHUNK,
        READ_ALL,
    } FileSystemReadMode;

    /// @brief FileHandle that needs to be used to operate using FileSystemController
    typedef uint64_t FileHandle;

    /// @brief Used to store information about, read bytes, read number of bytes, written bytes and file handle
    typedef struct
    {
        /**
         * @brief pointer to the file content that needs to be written or read
         *
         */
        uint8_t *in_out_buffer;
        /**
         * @brief size of the in_out_buffer
         *
         */
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