
#ifndef PUBLIC_FPDF_SYSFONTINFO_H_
#define PUBLIC_FPDF_SYSFONTINFO_H_

// clang-format off
// NOLINTNEXTLINE(build/include)
#include "fpdfview.h"

/* Character sets for the font */
#define FXFONT_ANSI_CHARSET 0
#define FXFONT_DEFAULT_CHARSET 1
#define FXFONT_SYMBOL_CHARSET 2
#define FXFONT_SHIFTJIS_CHARSET 128
#define FXFONT_HANGEUL_CHARSET 129
#define FXFONT_GB2312_CHARSET 134
#define FXFONT_CHINESEBIG5_CHARSET 136
#define FXFONT_GREEK_CHARSET 161
#define FXFONT_VIETNAMESE_CHARSET 163
#define FXFONT_HEBREW_CHARSET 177
#define FXFONT_ARABIC_CHARSET 178
#define FXFONT_CYRILLIC_CHARSET 204
#define FXFONT_THAI_CHARSET 222
#define FXFONT_EASTERNEUROPEAN_CHARSET 238

/* Font pitch and family flags */
#define FXFONT_FF_FIXEDPITCH (1 << 0)
#define FXFONT_FF_ROMAN (1 << 4)
#define FXFONT_FF_SCRIPT (4 << 4)

/* Typical weight values */
#define FXFONT_FW_NORMAL 400
#define FXFONT_FW_BOLD 700

// Exported Functions
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Interface: FPDF_SYSFONTINFO
 *          Interface for getting system font information and font mapping
 */
typedef struct _FPDF_SYSFONTINFO {
  /*
   * Version number of the interface. Currently must be 1.
   */
  int version;

  /**/
  void (*Release)(struct _FPDF_SYSFONTINFO* pThis);

  /**/
  void (*EnumFonts)(struct _FPDF_SYSFONTINFO* pThis, void* pMapper);

  /**/
  void* (*MapFont)(struct _FPDF_SYSFONTINFO* pThis,
                   int weight,
                   FPDF_BOOL bItalic,
                   int charset,
                   int pitch_family,
                   const char* face,
                   FPDF_BOOL* bExact);

  void* (*GetFont)(struct _FPDF_SYSFONTINFO* pThis, const char* face);

  /*
   * Method: GetFontData
   *          Get font data from a font
   * Interface Version:
   *          1
   * Implementation Required:
   *          Yes
   * Parameters:
   *          pThis       -   Pointer to the interface structure itself
   *          hFont       -   Font handle returned by MapFont or GetFont method
   *          table       -   TrueType/OpenType table identifier (refer to
   *                          TrueType specification), or 0 for the whole file.
   *          buffer      -   The buffer receiving the font data. Can be NULL if
   *                          not provided.
   *          buf_size    -   Buffer size, can be zero if not provided.
   * Return Value:
   *          Number of bytes needed, if buffer not provided or not large
   *          enough, or number of bytes written into buffer otherwise.
   * Comments:
   *          Can read either the full font file, or a particular
   *          TrueType/OpenType table.
   */
  unsigned long (*GetFontData)(struct _FPDF_SYSFONTINFO* pThis,
                               void* hFont,
                               unsigned int table,
                               unsigned char* buffer,
                               unsigned long buf_size);

  /*
   * Method: GetFaceName
   *          Get face name from a font handle
   * Interface Version:
   *          1
   * Implementation Required:
   *          No
   * Parameters:
   *          pThis       -   Pointer to the interface structure itself
   *          hFont       -   Font handle returned by MapFont or GetFont method
   *          buffer      -   The buffer receiving the face name. Can be NULL if
   *                          not provided
   *          buf_size    -   Buffer size, can be zero if not provided
   * Return Value:
   *          Number of bytes needed, if buffer not provided or not large
   *          enough, or number of bytes written into buffer otherwise.
   */
  unsigned long (*GetFaceName)(struct _FPDF_SYSFONTINFO* pThis,
                               void* hFont,
                               char* buffer,
                               unsigned long buf_size);

  /*
   * Method: GetFontCharset
   *          Get character set information for a font handle
   * Interface Version:
   *          1
   * Implementation Required:
   *          No
   * Parameters:
   *          pThis       -   Pointer to the interface structure itself
   *          hFont       -   Font handle returned by MapFont or GetFont method
   * Return Value:
   *          Character set identifier. See defined constants above.
   */
  int (*GetFontCharset)(struct _FPDF_SYSFONTINFO* pThis, void* hFont);

  /*
   * Method: DeleteFont
   *          Delete a font handle
   * Interface Version:
   *          1
   * Implementation Required:
   *          Yes
   * Parameters:
   *          pThis       -   Pointer to the interface structure itself
   *          hFont       -   Font handle returned by MapFont or GetFont method
   * Return Value:
   *          None
   */
  void (*DeleteFont)(struct _FPDF_SYSFONTINFO* pThis, void* hFont);
} FPDF_SYSFONTINFO;

/*
 * Struct: FPDF_CharsetFontMap
 *    Provides the name of a font to use for a given charset value.
 */
typedef struct FPDF_CharsetFontMap_ {
  int charset;  // Character Set Enum value, see FXFONT_*_CHARSET above.
  const char* fontname;  // Name of default font to use with that charset.
} FPDF_CharsetFontMap;

/*
 * Function: FPDF_GetDefaultTTFMap
 *    Returns a pointer to the default character set to TT Font name map. The
 *    map is an array of FPDF_CharsetFontMap structs, with its end indicated
 *    by a { -1, NULL } entry.
 * Parameters:
 *     None.
 * Return Value:
 *     Pointer to the Charset Font Map.
 */
FPDF_EXPORT const FPDF_CharsetFontMap* FPDF_CALLCONV FPDF_GetDefaultTTFMap();

/**/
FPDF_EXPORT void FPDF_CALLCONV FPDF_AddInstalledFont(void* mapper,
                                                     const char* face,
                                                     int charset);

/**/
FPDF_EXPORT void FPDF_CALLCONV
FPDF_SetSystemFontInfo(FPDF_SYSFONTINFO* pFontInfo);

/**/
FPDF_EXPORT FPDF_SYSFONTINFO* FPDF_CALLCONV FPDF_GetDefaultSystemFontInfo();

/**/
FPDF_EXPORT void FPDF_CALLCONV
FPDF_FreeDefaultSystemFontInfo(FPDF_SYSFONTINFO* pFontInfo);

#ifdef __cplusplus
}
#endif

#endif  // PUBLIC_FPDF_SYSFONTINFO_H_
