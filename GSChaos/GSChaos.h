/**
 * Copyright - ScriptedSnark, 2024.
 * GSChaos.h
 *
 * Project (GSChaos) header file
 * Authors: ScriptedSnark.
 * Do not delete this comment block. Respect others' work!
 */

#ifdef GSCHAOS_H_RECURSE_GUARD
#error Recursive header files inclusion detected in GSChaos.h
#else //GSCHAOS_H_RECURSE_GUARD

#define GSCHAOS_H_RECURSE_GUARD

#ifndef GSCHAOS_H_GUARD
#define GSCHAOS_H_GUARD
#pragma once

#ifdef __cplusplus

typedef int(__stdcall* _wglSwapBuffers)(HDC);
typedef LRESULT (APIENTRY* _WndProc)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern _wglSwapBuffers ORIG_wglSwapBuffers;
extern _WndProc ORIG_WndProc;

extern bool g_bHL25;
extern bool g_bPreSteamPipe;
extern bool g_bDrawHUD;

void HookEngine();
void HookClient();

#else //!__cplusplus
#error C++ compiler required to compile GSChaos.h
#endif //__cplusplus

#endif //GSCHAOS_H_GUARD

#undef GSCHAOS_H_RECURSE_GUARD
#endif //GSCHAOS_H_RECURSE_GUARD