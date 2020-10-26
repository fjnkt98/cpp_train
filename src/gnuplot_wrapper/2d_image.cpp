#include <cstdio>

int main(void) {
  FILE* gp = popen("gnuplot", "w");

  std::fprintf(gp, "set terminal pdf\n");
  std::fprintf(gp, "set output 'plot.pdf'\n");
  std::fprintf(gp, "set xrange[-10:10]\n");
  std::fprintf(gp, "set yrange[-1:1]\n");

  std::fprintf(gp, "plot sin(x)\n");

  fflush(gp);
  
  std::fprintf(gp, "exit\n");
  
  pclose(gp);
}