/*
 * -------------
 *  Dark Oberon
 * -------------
 *
 * An advanced strategy game.
 *
 * Copyright (C) 2002 - 2005 Valeria Sventova, Jiri Krejsa, Peter Knut,
 *                           Martin Kosalko, Marian Cerny, Michal Kral
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License (see docs/gpl.txt) as
 * published by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 */

/**
 *  @file dologs.cpp
 *
 *  Log files methods.
 *
 *  @author Peter Knut
 *  @author Marian Cerny
 *
 *  @date 2003, 2004
 */

#include "dologs.h"

//=========================================================================
// Variables
//=========================================================================

std::string user_dir = "/home/skyrimgamer/Schreibtisch/DarkOberon/dologs";

std::mutex log_mutex; //!< Mutex for LogMsg function.

/**
 *  Error log file. By default, only errors come here. This can be changed by
 *  #ERR_LOG_LEVELS.
 */
FILE *err_log;

/**
 *  Full log file. By default, all logs go here. This can be changed by
 *  #FULL_LOG_LEVELS.
 */
FILE *full_log;

/**
 *  Variable holding pointer to callback function which is called every time a
 *  log message is created. It is set by RegisterLogCallback().
 */
void (*log_callback)(int, const char *, const char *, const char *, int) = NULL;

/**
 *  String for function LogMsg().
 */
TLOG_MESSAGE log_msg;

// GLFWmutex log_mutex = NULL;            //!< Mutex for LogMsg function.
// std::mutex log_mutex; //!< Mutex for LogMsg function.

//=========================================================================
// Functions
//=========================================================================

//=========================================================================
// LogFileInfo
//=========================================================================

/**
 *  Write information about source file and line number, where one of the
 *  macros Debug(), Info(), Warning(), Error(), Critical() was used.
 *
 *  @param logfile Log file (FILE *).
 *
 *  @note Macro #DEBUG must be defined to enable this. (not true currently)
 */
void LogFileInfo(FILE *logfile, char *file, int line)
{
  do
  {
    fprintf(logfile, "[%13s:%4d] ", file, line);
    fflush(logfile);
  } while (0);
}

//=========================================================================
// Log_logfile
//=========================================================================

/**
 *  Log log message to logfile. If #DEBUG is defined, information about
 *  source file and line number, where the Log() was used, is printed using
 *  LogFileInfo().
 *
 *  @param logfile Log file (FILE *).
 *  @param header  Header to be printed (char *).
 *  @param msg     Log message (char *).
 *
 *  @note Macro #LOG_TO_LOGFILES must be defined, to enable logging to
 *        logfiles.
 */
void Log_logfile(FILE *logfile, char *header, char *msg, char *file, int line)
{
  do
  {
    if (logfile != NULL)
    {
      LogFileInfo(logfile, file, line);
      fprintf(logfile, "%s ", header);
      fprintf(logfile, "%s\n", msg);
      fflush(logfile);
    }
  } while (0);
}

//=========================================================================
// Log_logfiles
//=========================================================================

/**
 *  Log log message to logfiles.
 *
 *  @param level   Log level (#LOG_DEBUG, #LOG_INFO, #LOG_WARNING, #LOG_ERROR, #LOG_CRITICAL).
 *  @param header  Header to be printed (char *).
 *  @param msg     Log message (char *).
 *
 *  @note Macro #LOG_TO_LOGFILES must be defined, to enable logging to
 *        logfiles.
 */
void Log_logfiles(int level, char *header, char *msg, char *file, int line)
{
  do
  {
    if (level & ERR_LOG_LEVELS)
      Log_logfile(err_log, header, msg, file, line);
    if (level & FULL_LOG_LEVELS)
      Log_logfile(full_log, header, msg, file, line);
  } while (0);
}

//=========================================================================
// Log_stderr
//=========================================================================

/**
 *  Log log message to stderr. If #DEBUG is defined, information about
 *  source file and line number, where the Log() was used, is printed using
 *  LogFileInfo().
 *
 *  @param level  Log level (#LOG_DEBUG, #LOG_INFO, #LOG_WARNING, #LOG_ERROR, #LOG_CRITICAL).
 *  @param header Header to be printed (char *).
 *  @param msg    Log message (char *).
 *
 *  @note Macro #LOG_TO_STDERR must be defined, to enable logging to stderr.
 */
void Log_stderr(int level, char *header, char *msg, char *file, int line)
{
  do
  {
    if (level & STDERR_LOG_LEVELS)
    {
      LogFileInfo(stderr, file, line);
      fprintf(stderr, "%s ", header);
      fprintf(stderr, "%s\n", msg);
    }
  } while (0);
}

//=========================================================================
// Log_callback
//=========================================================================

/**
 *  Log a messages with external callback registered with
 *  RegisterLogCallback().
 *
 *  @param level   Log level (#LOG_DEBUG, #LOG_INFO, #LOG_WARNING, #LOG_ERROR, #LOG_CRITICAL).
 *  @param header  Header to be printed before message (char *).
 *  @param msg     Log message (char *).
 *
 *  @note Macro #LOG_TO_EXTERNAL_CALLBACK must be defined, to enable logging
 *  with external callback.
 */

void Log_callback(int level, char *header, char *msg, char *file, int line)
{
  do
  {
    if (level & EXTERNAL_LOG_LEVELS)
    {
      if (log_callback)
      {
        log_callback(level, header, msg, file, line);
      }
    }
  } while (0);
}

//=========================================================================
// Log
//=========================================================================

/**
 *  Log a messages. It will be logged to logfiles using Log_logfiles(), @c
 *  stderr using Log_stderr() and with external callback function using
 *  Log_callback().
 *
 *  @param level   Log level (#LOG_DEBUG, #LOG_INFO, #LOG_WARNING, #LOG_ERROR, #LOG_CRITICAL).
 *  @param header  Header to be printed before message (char *).
 *  @param msg     Log message (char *).
 *
 *  @note Macro #LOG_TO_LOGFILES must be defined, to enable logging to
 *        logfiles.
 *  @note Macro #LOG_TO_STDERR must be defined, to enable logging to stderr.
 *  @note Macro #LOG_TO_EXTERNAL_CALLBACK must be defined, to enable logging
 *        to external callback function.
 *
 *  @see Debug(), Info(), Warning(), Error(), Critical()
 */

// Thread-safe logging function
// void Log(int level, char *header, char *msg)
void Log(int level, char *header, char *msg, char *file, int line)
{
  do
  {
    log_mutex.lock();
    Log_stderr(level, header, msg, file, line);
    Log_logfiles(level, header, msg, file, line);
    Log_callback(level, header, msg, file, line);
    log_mutex.unlock();
  } while (0);
}

//=========================================================================
// LogMsg
//=========================================================================

/**
 *  Construct the log message. This function is similar to sprintf, but the
 *  output is always in @c log_msg, so you don't need to care about memory
 *  allocation.
 *
 *  @param msg Format of the message
 *  @param ... Arguments
 *
 *  @return Pointer to message in memory.
 */
char *LogMsg(char *msg, ...)
{
  va_list arg;

  va_start(arg, msg);

  vsnprintf(log_msg, MAX_LOG_MESSAGE_SIZE, msg, arg);

  va_end(arg);

  return log_msg;
}

//=========================================================================
// LogFiles
//=========================================================================

/**
 *  Creates mutex for LogMsg() method.
 */
// bool CreateLogMutex(void)
// {
//   // create mutex
//   // if ((log_mutex = glfwCreateMutex ()) == NULL) {
//   //   Critical ("Could not create log mutex");
//   //   return false;
//   // }

//   return true;
// }

// /**
//  *  Destroys mutex for LogMsg() method.
//  */
// void DestroyLogMutex(void)
// {
//   // glfwDestroyMutex(log_mutex);
//   // log_mutex = NULL;
// }

/**
 *  Opens a log file for writing.
 *
 *  @param name Filename of the log file.
 *
 *  @note Macro #LOG_TO_LOGFILES must be set to 1 to enable logging to log
 *        files.
 *
 *  @return FILE pointer to newly opened file or NULL on error.
 */
FILE *OpenLogFile(const char *name)
{
  FILE *ret;

  if ((ret = fopen(name, "w")) == NULL)
    Error(LogMsg("Can not open '%s' file. Logging is disabled", name));

  return ret;
}

/**
 *  Opens all log files. Also creates directory for log files, if not yet
 *  created. It calls OpenLogFile() for every log file.
 *
 *  @note Macro @c LOG_TO_LOGFILES must be set to 1 to enable logging to log
 *        files.
 *
 *  @return @c true on success, otherwise @c false.
 */
bool OpenLogFiles(void)
{
#if LOG_TO_LOGFILES
  // do_mkdir (LOG_PATH);
  // mkdir(LOG_PATH);
  std::filesystem::create_directories(LOG_PATH);
  err_log = OpenLogFile(LOG_ERR_NAME);
  full_log = OpenLogFile(LOG_FULL_NAME);

  return err_log != NULL && full_log != NULL;
#else
  return false;
#endif
}

/**
 *  Closes all log files.
 *
 *  @note Macro #LOG_TO_LOGFILES must be set to 1 to enable logging to log
 *        files.
 */
void CloseLogFiles(void)
{
#if LOG_TO_LOGFILES
  if (err_log)
    fclose(err_log);
  if (full_log)
    fclose(full_log);
#endif

  // glfwDestroyMutex(log_mutex);
}

/**
 *  Registers a callback function which should be called every time a log
 *  message is created. This is used for logging to some external place. We use
 *  it to log to screen using #ost.
 *
 *  @param f  Pointer to callback function. The function should have the
 *            following prototype:
 *
 *            @code
 *            void function_name (int level, const char *header, const char *message, const char *file, int line)
 *            @endcode
 *
 *            Where @a level is level of the log message (one of #LOG_DEBUG,
 *            #LOG_INFO, #LOG_WARNING, #LOG_ERROR or #LOG_CRITICAL), @a header
 *            is text description of the log level and @a message is the log
 *            message itself.
 *
 *  @note Only one function can be registered. Every time a new callback
 *        function is registered, the previous is forgeted.
 */
void RegisterLogCallback(void (*f)(int, const char *, const char *, const char *, int))
{
  log_callback = f;
}

//=========================================================================
// END
//=========================================================================
// vim:ts=2:sw=2:et:
