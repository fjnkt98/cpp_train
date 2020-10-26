#include <cstdio>

int main(void) {
  FILE* gp = popen("gnuplot", "w");

  std::fprintf(gp, "set terminal gif animate optimize delay 10 size 400,400\n");
  std::fprintf(gp, "set output 'animation.gif'\n");
  std::fprintf(gp, "set nokey\n");
  std::fprintf(gp, "set size square\n");
  std::fprintf(gp, "set xrange[-10:10]\n");
  std::fprintf(gp, "set yrange[-2:2]\n");

  for (int i = 0; i < 10; i++) {
    std::fprintf(gp, "plot sin(x + %d) with lines\n", i);
  }

  fflush(gp);
  pclose(gp);
}