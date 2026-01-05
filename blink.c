#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	while(1)
	{
		system("echo 1 > /sys/class/gpio/gpio21/value");
		usleep(100*1000);
		system("echo 0 > /sys/class/gpio/gpio21/value");
		usleep(100*1000);
	}
}

