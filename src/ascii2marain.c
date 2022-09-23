#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mchar_t.h"

// program that takes a file in ASCII as input and converts it to a 16-bit Marain encoding
/* Note: because Marain naturally uses a 9-bit encoding, the highest 7 bits of each 16-bit
 * Marain codepoint are zeros. These seven bits could potentially be used to some creative
 * end, such as specifying the color of each character, italicization, rotation, etc. */
int main(int argc, char *argv[]) {
  char *out_file_path = NULL, *in_file_path = NULL;
  if (argc == 4 && !strcmp(argv[2], "-o")) {
    out_file_path = argv[3];
    in_file_path = argv[1]; 
  } else if (argc == 4 && !strcmp(argv[1], "-o")) {
    out_file_path = argv[2];
    in_file_path = argv[3];
  } else {
    fprintf(stderr, "usage: %s <input file> -o <output file>\n", argv[0]);
    return 1;
  }

  FILE *in_file = fopen(in_file_path, "r");
  if (in_file == NULL) {
    fprintf(
      stderr, "%s: %s: no such file or directory\n",
      argv[0], in_file_path
    );
    return 1;
  }
  FILE *out_file = fopen(out_file_path, "wb+");
  fseek(in_file, 0L, SEEK_END);
  size_t n_chars = ftell(in_file);
  rewind(in_file);

  for (size_t i = 0; i < n_chars; i++) {
    char input_char;
    mchar_t output_mchar;
    fread(&input_char, 1, 1, in_file);
    output_mchar = mc_ascii_to_mchar(input_char);
    fwrite(&output_mchar, sizeof(mchar_t), 1, out_file);
  }

  fclose(in_file);
  fclose(out_file);
  return 0;
}
