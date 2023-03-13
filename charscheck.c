#include <ctype.h>
#include <stdio.h>


void encoding() {
    #ifdef _WIN32
        system("chcp 65001");
    #endif
}

int main() {
   encoding();
   FILE *file = fopen("specialchars.txt", "r");
   char line[256];
   while (fgets(line, sizeof(line), file)) {
      printf("%s", line);
   }
}