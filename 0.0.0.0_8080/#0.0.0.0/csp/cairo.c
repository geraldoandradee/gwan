// ============================================================================
// C servlet sample for the G-WAN Web Application Server (http://trustleap.ch/)
// ----------------------------------------------------------------------------
// cairo.c: generates a PNG bitmap with the "Hello World" string rendered with
//          the selected font and RGB 24-bit color.
// ----------------------------------------------------------------------------
// Cairo is a 2D graphics library with support for multiple output devices:
//
//   - the X Window System (via both Xlib and XCB), 
//   - Quartz, 
//   - Win32,
//   - image buffers,
//   - PostScript,
//   - PDF,
//   - OpenGL,
//   - SVG file output.
//
// Cairo support stroking and filling cubic Bézier splines, transforming and 
// compositing translucent images, and antialiased text rendering. All drawing 
// operations can be transformed by any affine transformation (scale, rotation, 
// shear, etc.). More on http://cairographics.org/
//
// Examples of use:
//
//  - GNUplot and PLplot are 2D and 3D graph plotting utility using Cairo,
//  - Firefox 3.0 uses cairo for rendering all content and UI,
//  - The GTK+ widget toolkit version 2.8+ relies on Cairo.
//
// Installation: sudo apt-get install libcairo2 libcairo2-dev
// ----------------------------------------------------------------------------
#pragma link "cairo"
#pragma include "/usr/include/cairo"

#include "cairo.h"
#include "gwan.h"
// ----------------------------------------------------------------------------
int main(int argc, char **argv)
{
   // -------------------------------------------------------------------------
   // build the destination file name
   // -------------------------------------------------------------------------
   char filename[512] = {0};
   s_snprintf(filename, sizeof(filename), "%s/hello.png", 
             (char*)get_env(argv, WWW_ROOT));

   // -------------------------------------------------------------------------
   // build the bitmap using Cairo
   // -------------------------------------------------------------------------
   cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 240, 80);
   cairo_t *cr = cairo_create (surface);

   cairo_select_font_face(cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
   cairo_set_font_size   (cr, 32.0);
   cairo_set_source_rgb  (cr, 0.0, 0.0, 1.0);
   cairo_move_to         (cr, 10.0, 50.0);
   cairo_show_text       (cr, "Hello, world");
   cairo_destroy         (cr);
   cairo_surface_write_to_png(surface, filename);
   cairo_surface_destroy(surface);
   
   xbuf_cat(get_reply(argv), "Generated hello.png under G-WAN root folder");
   return 200;
}
// ============================================================================
// End of Source Code
// ============================================================================
