#include "types.h"
#include "user.h"

//Usar los ticks dados por uptime() no es tan preciso.

int main (int argc, char *argv[]){

	int ctime = uptime();
	int rseconds = ctime / 100;
	int hour = rseconds / 3600;
	int minute = (rseconds - (hour * 3600)) / 60;
	int second = (rseconds - (minute * 60));

	printf(1, " %d horas %d minutos %d segundos\n", hour, minute, second);
	exit();
}
