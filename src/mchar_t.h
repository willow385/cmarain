#ifndef MCHAR_T_H
#define MCHAR_T_H

#include <stdlib.h>
#include <stdint.h>

// Type representing a Marain character
typedef uint16_t mchar_t;

enum marain_character_set {
  mc_wa     = 0b100111100,
  mc_uh     = 0b100011001,
  mc_ma     = 0b001001111,
  mc_hek    = 0b101101010,
  mc_de     = 0b110010011,
  mc_a      = 0b111100010,
  mc_pika   = 0b100101111,
  mc_seth   = 0b011010101,
  mc_tawa   = 0b101111001,
  mc_ihk    = 0b110011001,
  mc_le     = 0b110111010,
  mc_tchey  = 0b111010100,
  mc_keluh  = 0b001111011,
  mc_ot     = 0b011011100,
  mc_bat    = 0b001011111,
  mc_chem   = 0b011101010,
  mc_ihf    = 0b111111001,
  mc_ayyuhm = 0b010101111,
  mc_vash   = 0b111101101,
  mc_llewu  = 0b101010111,
  mc_nek    = 0b110111110,
  mc_iye    = 0b101110111,
  mc_gu     = 0b010011110,
  mc_eng    = 0b011110001,
  mc_zau    = 0b101111010,
  mc_ep     = 0b110001111,
  mc_ye     = 0b111101011,
  mc_shihk  = 0b110110101,
  mc_yoter  = 0b111011110,
  mc_uf     = 0b110011101,
  mc_rek    = 0b101111111,
  mc_tham   = 0b111111011,

  mc_space  = 0b000000000,
  mc_openb  = 0b000100110,
  mc_closeb = 0b011001000,
  mc_stop   = 0b100100100,

  mc_nhech  = 0b111101111,
  mc_sto    = 0b000111110,
  mc_hre    = 0b011110111,
  mc_dosa   = 0b111111111,
  mc_llamih = 0b110011111,
  mc_ko     = 0b110110111,
  mc_gol    = 0b100111010,
  mc_lyeway = 0b010110111,

  mc_error  = 0b101010101,
  mc_newline = '\n'
};

struct mstr_t {
  size_t length;
  mchar_t *chars;
};

enum marain_font_size {
  s_3x3, s_5x5, s_7x7
};

void mc_render_char(
  mchar_t marain_char, // character to render
  enum marain_font_size font_size,
  int x, int y, // coordinates of top-left corner
  void (*render_px)(int x, int y, void *), // function to render a pixel at (x, y)
  void *context // third argument to render_px
);

void mc_render_str(
  struct mstr_t string,
  enum marain_font_size font_size,
  int x, int y,
  void (*render_px)(int x, int y, void *),
  void *context
);

char mc_mchar_to_ascii(mchar_t c);
mchar_t mc_ascii_to_mchar(char c);

/// Assumes `buf` is already allocated and big enough to hold `1 + mstr.length` characters.
void mc_mstr_to_ascii(char *buf, struct mstr_t mstr);

/// `mstr->chars` must be freed with `free()` from `stdlib.h` after this is called.
void mc_ascii_to_mstr(struct mstr_t *mstr, const char *cstr);

#endif // MCHAR_T_H
