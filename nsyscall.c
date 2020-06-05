#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{

 int nnsyscall = -1;
 if (argc == 2) {
  nnsyscall = atoi(argv[1]);
 }

 if (nnsyscall == -1) 
  // mostrar todas las llamadas al sistema
  // con su correspondiente numero de invocaciones
   nsyscall(-1);
 else 
  // mostrar la llamada al sistema dada en nsyscall
  // con su correspondiente numero de invocaciones
   nsyscall(nnsyscall);
 exit();
}


