/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 30

char names[][MAX] = {"javer", "david", "alejandro", "pedro", "valeria", "susana", "frida", "sebastiÁn", "linus", "erick", "daniel", "mario", "victor", "leonardo", "augusto", "salvador"};

char lastnm[][MAX] = {"almaraz", "robles", "rosales", "gomez", "tapia", "canales", "romo", "reyes", "torval", "lopex", "danielson", "dominguez", "sanabria", "pedrosa", "dalÍ", "cienfuegos"};

float random_float(const float min, const float max)
{
    if (max == min) return min;
    else if (min < max) return (max - min) * ((float)rand() / RAND_MAX) + min;

    // return 0 if min > max
    return 0;
}

int main() {
  FILE *fp = fopen("log.txt", "w");
  srand(time(NULL));
  for(size_t i = 0; i < 70; i++) {
    fputs("1\n", fp);
    fprintf(fp, "%s %s\n", names[rand() % 16], lastnm[rand() % 16]);
    fprintf(fp, "%d\n", abs(rand()) % 70 + 18);
    fprintf(fp, "%c%c%c%c\n", rand() % ('z' - 'a' + 1) + 'a', rand() % ('z' - 'a' + 1) + 'a', rand() % ('9' - '0' + 1) + '0', rand() % ('9' - '0' + 1) + '0');
    for(size_t j = 0; j < 3; j++) {
      fprintf(fp, "%c\n", (rand() % 2) ? 'c' : 'd');
      fprintf(fp, "%.2f\n", random_float(100.00, 10000000.00));
    }
    putc(10, fp);
  }

  fclose(fp);
}
*/