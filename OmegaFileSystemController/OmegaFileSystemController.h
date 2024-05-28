/**
 * @file OmegaFileSystemController.h
 * @author Chameera Subasinghe
 * @date Friday, 1st March 2024 2:28:17 am
 * @copyright Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * */
/*
 * Project: OmegaESP32Services
 * File Name: OmegaFileSystemController.h
 * File Created: Friday, 1st March 2024 2:28:17 am
 * Author: Chameera Subasinghe (omegaki113r@gmail.com)
 * -----
 * Last Modified: Tuesday, 28th May 2024 7:33:55 pm
 * Modified By: Omegaki113r (omegaki113r@gmail.com)
 * -----
 * Copyright 2024 - 2024 0m3g4ki113r, Xtronic
 * -----
 * HISTORY:
 * Date      	By	Comments
 * ----------	---	---------------------------------------------------------
 * 
 * 28-05-2024	0m3g4	refactor the code to replicate the current code structure
 *
 * 08-03-2024	0m3g4	documentation added
 *
 * 07-03-2024	0m3g4	`OmegaFileSystemController_write_file()` function prototype
 *
 * 07-03-2024	0m3g4	new parameter to `OmegaFileSystemController_read_file()` called bytes_to_read to handle CHUNK_READ
 *
 * 28-02-2024	0m3g4	POSIX on x86/64 and SPIFFS on Xtensa seems to have different notion of <NEWLINE> character     POSIX => \n      SPIFFS => \r\n therefore had to fix that inorder to hash function to work
 *
 * 26-02-2024	0m3g4	basics of the FileSystemController code added
 *
 * 23-02-2024   0m3g4   open file and close file feature implemented
 */

#ifndef __OMEGA_FILE_SYSTEM_CONTROLLER__
#define __OMEGA_FILE_SYSTEM_CONTROLLER__

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /// @brief ReturnTypes/StatusCodes for the File System Controller
    typedef enum
    {
        /// @brief Indicates success in any operation related to FileSystemController
        FSC_SUCCESS,
        /// @brief Indicates failure in any operation related to FileSystemController
        FSC_FAILED,
        /// @brief Indicate failure due to FileSystemController functions are being called before `OmegaFileSystemController_init()`
        FSC_NOT_INIT,
        /// @brief Indicates API misuse of using invalid `FileSystemOpenMode` in `OmegaFileSystemController_open_file()`
        FSC_INVALID_OPENMODE,
        /// @brief Indicates failure fir to invalid parameters
        FSC_INVALID_PARAMETERS,
        /// @brief Indicates a failure "File Not existing on the file system" when calling `OmegaFileSystemController_open_file()` with READING only
        FSC_FILE_NOT_EXIST,
        /// @brief Indicates a API misuse of invalid parameter of type FileHandle being received to functions
        FSC_FILE_HANDLE_NOT_EXIST,
        /// @brief Indicates failure due to not having enough heap memory needed to allocate for the operation
        FSC_NO_MEM,
        /// @brief Indicates a failure during file writing operation. All the content were no written to the file
        FSC_INCOMPLETE_FILE_WRITE,
        /// @brief Indicates the end of file reading a file
        FSC_END_OF_FILE,
        /// @brief //!TODO: Implement the usage of this inside `OmegaFileSystemController_open_file()`
        FSC_FILE_ALREADY_OPENED,
        /// @brief Indicates an unknown error
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
        /// @brief Indicates Reading
        READING = 1 << 0,
        /// @brief Indicates Writing
        WRITING = 1 << 1,
        /// @brief Indicates Appending
        APPEND = 1 << 2,
        /// @brief Indicates Overwrite
        OVERWRITE = 1 << 3,
    } FileSystemOpenMode;

    /**
     * @brief ReadMode(s) that needs to be specified when calling `OmegaFileSystemController_read_file()`
     *
     */
    typedef enum
    {
        /// @brief Reads set of characters till '\n' including the '\n'. If EOF (End Of File) met just the content upto EOF is read
        READ_LINE,
        /// @brief Read only pre-specified number of bytes
        READ_CHUNK,
        /// @brief Read the whole file in 1 go
        READ_ALL,
    } FileSystemReadMode;

    /// @brief FileHandle that needs to be used to operate using FileSystemController
    typedef uint64_t FileHandle;

    /**
     * @brief Used to open a file.
     *
     * @param in_file_name Input parameter. Path of the file that needs to be opened with the filename and the extention of the file.
     * @param in_open_mode Input parameter. Enumaration of type `FileSystemOpenMode`. Please see the brief of `FileSystemOpenMode`
     * @return FileHandle greather than 0 if the file opened successfully else 0. FileHandle needs to be used to do file operations (Read, Write, ...). Cannot be 0.
     */
    FileHandle OmegaFileSystemController_open_file(const char *in_file_name, FileSystemOpenMode in_open_mode);
    /**
     * @brief Used to close a previously opened file.
     *
     * @param in_file_handle Input parameter. Instance of `FileHandle` which were used to open a file using `OmegaFileSystemController_open_file()`. Cannot be 0.
     * @return FileSystemControllerStatus FSC_SUCCESS if the file closed successfully
     */
    FileSystemControllerStatus OmegaFileSystemController_close_file(const FileHandle in_file_handle);
    /**
     * @brief Read from a previously opened file.
     *              Can be used on the same file multiple times depending on the `FileSystemReadMode` i.e. READ_LINE,READ_CHUNK
     *
     * @param in_file_handle Input parameter. Instance of `FileHandle` which were used to open a file using `OmegaFileSystemController_open_file()`. Cannot be 0.
     * @param in_read_mode Input parameter. Enumaration of type `FileSystemReadMode` that will help to use the API flexibly. i.e. read the whole file, read till a new line is found, read a predefined amount of bytes
     * @param in_size_to_read Input parameter. If the `in_read_mode` is `READ_CHUNK` then this parameter is used to read that amount of bytes from the file, else this cannot be NULL
     * @return FileSystemControllerStatus FSC_SUCCESS if the file read successfully
     */
    FileSystemControllerStatus OmegaFileSystemController_read_file(const FileHandle in_file_handle, FileSystemReadMode in_read_mode, uint8_t *in_buffer, size_t *in_out_size_to_read);
    /**
     * @brief Write a previously opened file.
     *
     * @param in_file_handle Input parameter. Instance of `FileHandle` which were used to open a file using `OmegaFileSystemController_open_file()`. Cannot be NULL.
     * @param in_buffer Input parameter. Content of this will be used to write the file. Cannot be NULL
     * @param in_size_to_write Input parameter. Amount of bytes that needs to be written from the `in_buffer`. Should be less or equal to the size of `in_buffer`
     * @return FileSystemControllerStatus FSC_SUCCESS if the filw written successfully
     */
    FileSystemControllerStatus OmegaFileSystemController_write_file(const FileHandle in_file_handle, const uint8_t *in_buffer, size_t *in_size_to_write);
#ifdef __cplusplus
}
#endif

#endif