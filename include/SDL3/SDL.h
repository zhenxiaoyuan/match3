/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2022 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 *  \file SDL.h
 *
 *  Main include header for the SDL library
 */


#ifndef SDL_h_
#define SDL_h_

#include <SDL3/SDL_main.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_assert.h>
#include <SDL3/SDL_atomic.h>
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_bits.h>
#include <SDL3/SDL_blendmode.h>
#include <SDL3/SDL_clipboard.h>
#include <SDL3/SDL_cpuinfo.h>
#include <SDL3/SDL_endian.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_filesystem.h>
#include <SDL3/SDL_gamecontroller.h>
#include <SDL3/SDL_gesture.h>
#include <SDL3/SDL_guid.h>
#include <SDL3/SDL_haptic.h>
#include <SDL3/SDL_hidapi.h>
#include <SDL3/SDL_hints.h>
#include <SDL3/SDL_joystick.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_loadso.h>
#include <SDL3/SDL_locale.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_messagebox.h>
#include <SDL3/SDL_metal.h>
#include <SDL3/SDL_misc.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_mutex.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_platform.h>
#include <SDL3/SDL_power.h>
#include <SDL3/SDL_quit.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_revision.h>
#include <SDL3/SDL_rwops.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_sensor.h>
#include <SDL3/SDL_shape.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_system.h>
#include <SDL3/SDL_thread.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_touch.h>
#include <SDL3/SDL_version.h>
#include <SDL3/SDL_video.h>

#include <SDL3/begin_code.h>
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* As of version 0.5, SDL is loaded dynamically into the application */

/**
 *  \name SDL_INIT_*
 *
 *  These are the flags which may be passed to SDL_Init().  You should
 *  specify the subsystems which you will be using in your application.
 */
/* @{ */
#define SDL_INIT_TIMER          0x00000001u
#define SDL_INIT_AUDIO          0x00000010u
#define SDL_INIT_VIDEO          0x00000020u  /**< SDL_INIT_VIDEO implies SDL_INIT_EVENTS */
#define SDL_INIT_JOYSTICK       0x00000200u  /**< SDL_INIT_JOYSTICK implies SDL_INIT_EVENTS */
#define SDL_INIT_HAPTIC         0x00001000u
#define SDL_INIT_GAMECONTROLLER 0x00002000u  /**< SDL_INIT_GAMECONTROLLER implies SDL_INIT_JOYSTICK */
#define SDL_INIT_EVENTS         0x00004000u
#define SDL_INIT_SENSOR         0x00008000u
#define SDL_INIT_NOPARACHUTE    0x00100000u  /**< compatibility; this flag is ignored. */
#define SDL_INIT_EVERYTHING ( \
                SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS | \
                SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_SENSOR \
            )
/* @} */

/**
 * Initialize the SDL library.
 *
 * SDL_Init() simply forwards to calling SDL_InitSubSystem(). Therefore, the
 * two may be used interchangeably. Though for readability of your code
 * SDL_InitSubSystem() might be preferred.
 *
 * The file I/O (for example: SDL_RWFromFile) and threading (SDL_CreateThread)
 * subsystems are initialized by default. Message boxes
 * (SDL_ShowSimpleMessageBox) also attempt to work without initializing the
 * video subsystem, in hopes of being useful in showing an error dialog when
 * SDL_Init fails. You must specifically initialize other subsystems if you
 * use them in your application.
 *
 * Logging (such as SDL_Log) works without initialization, too.
 *
 * `flags` may be any of the following OR'd together:
 *
 * - `SDL_INIT_TIMER`: timer subsystem
 * - `SDL_INIT_AUDIO`: audio subsystem
 * - `SDL_INIT_VIDEO`: video subsystem; automatically initializes the events
 *   subsystem
 * - `SDL_INIT_JOYSTICK`: joystick subsystem; automatically initializes the
 *   events subsystem
 * - `SDL_INIT_HAPTIC`: haptic (force feedback) subsystem
 * - `SDL_INIT_GAMECONTROLLER`: controller subsystem; automatically
 *   initializes the joystick subsystem
 * - `SDL_INIT_EVENTS`: events subsystem
 * - `SDL_INIT_EVERYTHING`: all of the above subsystems
 * - `SDL_INIT_NOPARACHUTE`: compatibility; this flag is ignored
 *
 * Subsystem initialization is ref-counted, you must call SDL_QuitSubSystem()
 * for each SDL_InitSubSystem() to correctly shutdown a subsystem manually (or
 * call SDL_Quit() to force shutdown). If a subsystem is already loaded then
 * this call will increase the ref-count and return.
 *
 * \param flags subsystem initialization flags
 * \returns 0 on success or a negative error code on failure; call
 *          SDL_GetError() for more information.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_InitSubSystem
 * \sa SDL_Quit
 * \sa SDL_SetMainReady
 * \sa SDL_WasInit
 */
extern DECLSPEC int SDLCALL SDL_Init(Uint32 flags);

/**
 * Compatibility function to initialize the SDL library.
 *
 * This function and SDL_Init() are interchangeable.
 *
 * \param flags any of the flags used by SDL_Init(); see SDL_Init for details.
 * \returns 0 on success or a negative error code on failure; call
 *          SDL_GetError() for more information.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_Init
 * \sa SDL_Quit
 * \sa SDL_QuitSubSystem
 */
extern DECLSPEC int SDLCALL SDL_InitSubSystem(Uint32 flags);

/**
 * Shut down specific SDL subsystems.
 *
 * If you start a subsystem using a call to that subsystem's init function
 * (for example SDL_VideoInit()) instead of SDL_Init() or SDL_InitSubSystem(),
 * SDL_QuitSubSystem() and SDL_WasInit() will not work. You will need to use
 * that subsystem's quit function (SDL_VideoQuit()) directly instead. But
 * generally, you should not be using those functions directly anyhow; use
 * SDL_Init() instead.
 *
 * You still need to call SDL_Quit() even if you close all open subsystems
 * with SDL_QuitSubSystem().
 *
 * \param flags any of the flags used by SDL_Init(); see SDL_Init for details.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_InitSubSystem
 * \sa SDL_Quit
 */
extern DECLSPEC void SDLCALL SDL_QuitSubSystem(Uint32 flags);

/**
 * Get a mask of the specified subsystems which are currently initialized.
 *
 * \param flags any of the flags used by SDL_Init(); see SDL_Init for details.
 * \returns a mask of all initialized subsystems if `flags` is 0, otherwise it
 *          returns the initialization status of the specified subsystems.
 *
 *          The return value does not include SDL_INIT_NOPARACHUTE.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_Init
 * \sa SDL_InitSubSystem
 */
extern DECLSPEC Uint32 SDLCALL SDL_WasInit(Uint32 flags);

/**
 * Clean up all initialized subsystems.
 *
 * You should call this function even if you have already shutdown each
 * initialized subsystem with SDL_QuitSubSystem(). It is safe to call this
 * function even in the case of errors in initialization.
 *
 * If you start a subsystem using a call to that subsystem's init function
 * (for example SDL_VideoInit()) instead of SDL_Init() or SDL_InitSubSystem(),
 * then you must use that subsystem's quit function (SDL_VideoQuit()) to shut
 * it down before calling SDL_Quit(). But generally, you should not be using
 * those functions directly anyhow; use SDL_Init() instead.
 *
 * You can use this function with atexit() to ensure that it is run when your
 * application is shutdown, but it is not wise to do this from a library or
 * other dynamically loaded code.
 *
 * \since This function is available since SDL 3.0.0.
 *
 * \sa SDL_Init
 * \sa SDL_QuitSubSystem
 */
extern DECLSPEC void SDLCALL SDL_Quit(void);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif
#include <SDL3/close_code.h>

#endif /* SDL_h_ */

/* vi: set ts=4 sw=4 expandtab: */
