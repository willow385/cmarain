#include "mchar_t.h"
#include <stdbool.h>
#include <string.h>

static void mc_render_5x5_char(
  mchar_t marain_char,
  int x, int y,
  void (*render_px)(int, int, void *),
  void *context
) {
  // TODO
}

static void mc_render_7x7_char(
  mchar_t marain_char,
  int x, int y,
  void (*render_px)(int, int, void *),
  void *context
) {
  // TODO
}

void mc_render_char(
  mchar_t marain_char,
  enum marain_font_size font_size,
  int x, int y,
  void (*render_px)(int, int, void *),
  void *context
) {
  if (marain_char == mc_space) return;
  switch (font_size) {
    case s_3x3: {
      for (unsigned int i = 0; i < 9; i++) {
        if (marain_char & (0b100000000u >> i)) render_px(x + (i % 3), y + (i / 3), context);
      } 
    } break;
    case s_5x5:
      mc_render_5x5_char(marain_char, x, y, render_px, context);
    break;
    case s_7x7:
      mc_render_7x7_char(marain_char, x, y, render_px, context);
    default:
      return;
  }
}

void mc_render_str(
  struct mstr_t string,
  enum marain_font_size font_size,
  int x, int y,
  void (*render_px)(int, int, void *),
  void *context
) {
  unsigned int px_offset =
    font_size == s_3x3 ? 4 :
    font_size == s_5x5 ? 6 :
    font_size == s_7x7 ? 8 : 0;
  unsigned int x_offset_amount = 0;
  unsigned int line = 0;
  for (unsigned int i = 0; i < string.length; i++) {
    if (string.chars[i] == mc_newline) {
      line++;
      x_offset_amount = 0;
    } else {
      mc_render_char(
        string.chars[i],
        font_size,
        x + x_offset_amount, y + line * px_offset,
        render_px,
        context
      );
      x_offset_amount += px_offset;
    }
  }
}

char mc_mchar_to_ascii(mchar_t c) {
  switch (c) {
    case mc_wa:     return 'w';
    case mc_uh:     return 'u';
    case mc_ma:     return 'm';
    case mc_hek:    return 'h';
    case mc_de:     return 'd';
    case mc_a:      return 'a';
    case mc_pika:   return 'p';
    case mc_seth:   return 's';
    case mc_tawa:   return 't';
    case mc_ihk:    return 'i';
    case mc_le:     return 'l';
    case mc_tchey:  return 'C';
    case mc_keluh:  return 'k';
    case mc_ot:     return 'o';
    case mc_bat:    return 'b';
    case mc_chem:   return 'H';
    case mc_ihf:    return 'f';
    case mc_ayyuhm: return 'A';
    case mc_vash:   return 'v';
    case mc_llewu:  return 'L';
    case mc_nek:    return 'n';
    case mc_iye:    return 'E';
    case mc_gu:     return 'g';
    case mc_eng:    return 'G';
    case mc_zau:    return 'z';
    case mc_ep:     return 'e';
    case mc_ye:     return 'j';
    case mc_shihk:  return 'S';
    case mc_yoter:  return 'y';
    case mc_uf:     return 'O';
    case mc_rek:    return 'r';
    case mc_tham:   return 'T';

    case mc_space:  return ' ';
    case mc_openb:  return '(';
    case mc_closeb: return ')';
    case mc_stop:   return '.';
  
    case mc_nhech:  return '0';
    case mc_sto:    return '1';
    case mc_hre:    return '2';
    case mc_dosa:   return '3';
    case mc_llamih: return '4';
    case mc_ko:     return '5';
    case mc_gol:    return '6';
    case mc_lyeway: return '7';

    case mc_newline: return '\n';
    default:        return '?'; // TODO better error handling
  }
}

mchar_t mc_ascii_to_mchar(char c) {
    switch (c) {
    case 'w': return mc_wa;
    case 'u': return mc_uh;
    case 'm': return mc_ma;
    case 'h': return mc_hek;
    case 'd': return mc_de;
    case 'a': return mc_a;
    case 'p': return mc_pika;
    case 's': return mc_seth;
    case 't': return mc_tawa;
    case 'i': return mc_ihk;
    case 'l': return mc_le;
    case 'C': return mc_tchey;
    case 'k': return mc_keluh;
    case 'o': return mc_ot;
    case 'b': return mc_bat;
    case 'H': return mc_chem;
    case 'f': return mc_ihf;
    case 'A': return mc_ayyuhm;
    case 'v': return mc_vash;
    case 'L': return mc_llewu;
    case 'n': return mc_nek;
    case 'E': return mc_iye;
    case 'g': return mc_gu;
    case 'G': return mc_eng;
    case 'z': return mc_zau;
    case 'e': return mc_ep;
    case 'j': return mc_ye;
    case 'S': return mc_shihk;
    case 'y': return mc_yoter;
    case 'O': return mc_uf;
    case 'r': return mc_rek;
    case 'T': return mc_tham;

    case ' ': return mc_space;
    case '(': case ',': return mc_openb;
    case ')': case '"': return mc_closeb;
    case '.': return mc_stop;
  
    case '0': return mc_nhech;
    case '1': return mc_sto;
    case '2': return mc_hre;
    case '3': return mc_dosa;
    case '4': return mc_llamih;
    case '5': return mc_ko;
    case '6': return mc_gol;
    case '7': return mc_lyeway;

    case '\n': return mc_newline;
    default:   return mc_error; // TODO better error handling
  }
}

void mc_mstr_to_ascii(char *buf, struct mstr_t mstr) {
  size_t i;
  for (i = 0; i < mstr.length; i++) {
    buf[i] = mc_mchar_to_ascii(mstr.chars[i]);
  }
  buf[i] = '\0';
}

void mc_ascii_to_mstr(struct mstr_t *mstr, const char *cstr) {
  mstr->length = strlen(cstr);
  mstr->chars = malloc(mstr->length * sizeof(mchar_t));
  for (size_t i = 0, c = 0; i < mstr->length; i++, c++) {
    if (cstr[c] == '\\' && cstr[c+1] == 'n') {
      mstr->chars[i] = mc_newline;
      c++; // lol
    } else if (cstr[c] != '\0') {
      mstr->chars[i] = mc_ascii_to_mchar(cstr[c]);
    } else {
      return;
    }
  }
}
