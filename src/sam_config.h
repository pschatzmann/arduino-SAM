/**
 * @file sam_config.h
 * @brief Configuration settings for Arduino
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define LOG_BUFFER_LEN 512
extern char log_buffer_sam[LOG_BUFFER_LEN];
void printLog(char* msg);

// activate/deactivate Logging
#define SAM_LOG_ACTIVE 0

// activate/deactivate debugging
#define SAM_DEBUG 0

// generate LOG command only if SAM_LOG_ACTIVE 
#if SAM_LOG_ACTIVE
#define SAM_LOG(...)  { snprintf(log_buffer_sam, LOG_BUFFER_LEN, __VA_ARGS__); printLog(log_buffer_sam); }
#else
#define SAM_LOG(...)
#endif


#ifdef __cplusplus
}
#endif

