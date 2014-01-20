#include <errno.h>
#include <libgen.h> // basename(char*)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // getopt

/** Print help and exit. */
static void help(char *name) {
  fprintf(stderr, "usage: %s [-h] [file ...]\n", basename(name));
  fputs("expand Greeek letters to Latin names\n", stderr);
  fputs("-h      print this help and exit\n", stderr);
  exit(0);
}

/* Expand 0xCE 0x?? byte pairs if they encode Greek letters and return the last byte. */
int fgetce(FILE *stream) {
  int c = fgetc(stream);

  switch (c) {
    case 0x91: printf("Alph");   c = 'a'; break;
    case 0x92: printf("Bet");    c = 'a'; break;
    case 0x93: printf("Gamm");   c = 'a'; break;
    case 0x94: printf("Delt");   c = 'a'; break;
    case 0x95: printf("Epsilo"); c = 'n'; break;
    case 0x96: printf("Zet");    c = 'a'; break;
    case 0x97: printf("Et");     c = 'a'; break;
    case 0x98: printf("Thet");   c = 'a'; break;
    case 0x99: printf("Iot");    c = 'a'; break;
    case 0x9a: printf("Kapp");   c = 'a'; break;
    case 0x9b: printf("Lambd");  c = 'a'; break;
    case 0x9c: printf("M");      c = 'u'; break;
    case 0x9d: printf("N");      c = 'u'; break;
    case 0x9e: printf("X");      c = 'i'; break;
    case 0x9f: printf("Omicro"); c = 'n'; break;
    case 0xa0: printf("P");      c = 'i'; break;
    case 0xa1: printf("Rh");     c = 'o'; break;
    case 0xa3: printf("Sigm");   c = 'a'; break;
    case 0xa4: printf("Ta");     c = 'u'; break;
    case 0xa5: printf("Upsilo"); c = 'n'; break;
    case 0xa6: printf("Ph");     c = 'i'; break;
    case 0xa7: printf("Ch");     c = 'i'; break;
    case 0xa8: printf("Ps");     c = 'i'; break;
    case 0xa9: printf("Omeg");   c = 'a'; break;
    case 0xb1: printf("alph");   c = 'a'; break;
    case 0xb2: printf("bet");    c = 'a'; break;
    case 0xb3: printf("gamm");   c = 'a'; break;
    case 0xb4: printf("delt");   c = 'a'; break;
    case 0xb5: printf("epsilo"); c = 'n'; break;
    case 0xb6: printf("zet");    c = 'a'; break;
    case 0xb7: printf("et");     c = 'a'; break;
    case 0xb8: printf("thet");   c = 'a'; break;
    case 0xb9: printf("iot");    c = 'a'; break;
    case 0xba: printf("kapp");   c = 'a'; break;
    case 0xbb: printf("lambd");  c = 'a'; break;
    case 0xbc: printf("m");      c = 'u'; break;
    case 0xbd: printf("n");      c = 'u'; break;
    case 0xbe: printf("x");      c = 'i'; break;
    case 0xbf: printf("omicro"); c = 'n'; break;
    default: putchar(0xce);
  }

  return c;
}

/* Expand 0xCF 0x?? byte pairs if they encode Greek letters and return the last byte. */
int fgetcf(FILE *stream) {
  int c = fgetc(stream);

  switch (c) {
    case 0x80: printf("p");      c = 'i'; break;
    case 0x81: printf("rh");     c = 'o'; break;
    case 0x82: printf("sigm");   c = 'a'; break;
    case 0x83: printf("sigm");   c = 'a'; break;
    case 0x84: printf("ta");     c = 'u'; break;
    case 0x85: printf("upsilo"); c = 'n'; break;
    case 0x86: printf("ph");     c = 'i'; break;
    case 0x87: printf("ch");     c = 'i'; break;
    case 0x88: printf("ps");     c = 'i'; break;
    case 0x89: printf("omeg");   c = 'a'; break;
    case 0x90: printf("bet");    c = 'a'; break;
    case 0x91: printf("thet");   c = 'a'; break;
    case 0x95: printf("ph");     c = 'i'; break;
    case 0x96: printf("p");      c = 'i'; break;
    case 0x97: printf("ka");     c = 'i'; break;
    default: putchar(0xcf);
  }

  return c;
}

/** Parse input file and write to <stdout>. */
int parse(FILE *stream) {
  int c = fgetc(stream);

  while (c != EOF) {
    if (c == 0xce) c = fgetce(stream);
    else if (c == 0xcf) c = fgetcf(stream);

    if (putchar(c) != c) break;

    c = fgetc(stream);
  }

  return errno;
}

/** Convert Greek letters in files (or <stdin> if len == 0). */
void run(char **files, int len) {
  for (int idx = 0; idx < len; idx++)
  {
    FILE *in = fopen(files[idx], "rb");

    if (!in) {
      fprintf(stderr, "error opening file '%s': %s\n", files[idx], strerror(errno));
      exit(EXIT_FAILURE);
    }

    if (parse(in) != 0) {
      fprintf(stderr, "error while reading file '%s': %s\n", files[idx], strerror(errno));
      exit(EXIT_FAILURE);
    }

    fclose(in);
  }

  if (len == 0) {
    if (parse(stdin) != 0) {
      fprintf(stderr, "error while reading from <stdin>: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  if (errno) {
    fprintf(stderr, "unknown error: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char **argv) {
  int show_help = 0;
  int c;
  
  while ((c = getopt(argc, argv, "h")) != -1)
    switch (c) {
      case 'h': show_help = 1; break;
      case '?': break; // getopt prints an error message
      default: abort();
    }

  if (show_help) help(argv[0]);

  run(argv + optind, argc - optind);
  exit(EXIT_SUCCESS);
}
