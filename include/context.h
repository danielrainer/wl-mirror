#ifndef WL_MIRROR_CONTEXT_H_
#define WL_MIRROR_CONTEXT_H_

#include <stdint.h>
#include <stdbool.h>
#include <wayland-client.h>
#include <wayland-egl.h>
#include <EGL/egl.h>
#include "xdg-shell.h"
#include "xdg-output-unstable-v1.h"
#include "wlr-export-dmabuf-unstable-v1.h"

typedef struct {
    struct wl_display * display;
    struct wl_registry * registry;

    // registry objects
    struct wl_compositor * compositor;
    struct xdg_wm_base * wm_base;
    struct zxdg_output_manager_v1 * output_manager;
    struct zwlr_export_dmabuf_manager_v1 * dmabuf_manager;
    // registry ids
    uint32_t compositor_id;
    uint32_t wm_base_id;
    uint32_t output_manager_id;
    uint32_t dmabuf_manager_id;

    // surface objects
    struct wl_surface * surface;
    struct xdg_surface * xdg_surface;
    struct xdg_toplevel * xdg_toplevel;

    // state flags
    uint32_t last_surface_serial;
    bool xdg_surface_configured;
    bool xdg_toplevel_configured;
    bool configured;
    bool closing;
} ctx_wl_t;

typedef struct {
    EGLDisplay display;
    EGLContext context;
    EGLConfig config;
    EGLSurface surface;
    struct wl_egl_window * window;

    // state flags
    uint32_t width;
    uint32_t height;
    bool initialized;
} ctx_egl_t;

typedef struct {
    char * output;
} ctx_mirror_t;

typedef struct {
    ctx_wl_t * wl;
    ctx_egl_t * egl;
    ctx_mirror_t * mirror;
} ctx_t;

void init_wl(ctx_t * ctx);
void init_egl(ctx_t * ctx);
void init_mirror(ctx_t * ctx, char * output);

void exit_fail(ctx_t * ctx);
void cleanup(ctx_t * ctx);
void cleanup_wl(ctx_t * ctx);
void cleanup_egl(ctx_t * ctx);
void cleanup_mirror(ctx_t * ctx);

#endif
