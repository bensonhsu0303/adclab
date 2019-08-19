#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

char ups[20] = "ups";
char host[30] = "127.0.0.1";
int pollFreq = 5;
int shutDownTime = 60;
int onBatteryTime = 0;

void logmsg(const char *msg)
{
	FILE *fp = fopen("/etc/ups-parse/ups-parse.log", "at");
	time_t timert;
	time(&timert);
	struct tm timer = (*localtime(&timert));
	fprintf(fp, "%d/%d/%d %02d:%02d:%02d\t%s", 
		timer.tm_year+1900, timer.tm_mon+1, timer.tm_mday, 
		timer.tm_hour, timer.tm_min, timer.tm_sec, msg);
	fclose(fp);
}

void wall(const char *msg)
{
	char cmd[2048];
	strcpy(cmd, "wall \"");
	strcat(cmd, msg);
	strcat(cmd, "\"");
	system(cmd);
	logmsg(msg);
}

void shutdown()
{
	wall("System will shutdown due to power lost.\n");
	system("/sbin/shutdown -h +0");
}

void updateups(const char *status)
{
	if(strstr(status, "OL") != NULL)
	{
		// on line power
		if(onBatteryTime != 0)
			wall("Back on line power.\n");
		onBatteryTime = 0;
	}
	else if(strstr(status, "OB") != NULL)
	{	
		if(strstr(status, "LB") != NULL)
		{
			// on battery, Low battery	
			wall("On battery power, battery is low.\n");
			shutdown();
		}
		else
		{
			// on battery, but not low battery
			onBatteryTime += pollFreq;
			if(onBatteryTime >= shutDownTime)
				shutdown();
			else if(onBatteryTime == pollFreq)
			{
				char line[2048];
				sprintf(line, "On battery power, system will shutdown in %d seconds.\n",
				shutDownTime - onBatteryTime);
				wall(line);
			}
		}
	}
}

void parse()
{
	FILE *fp;
	char line[2048], status[2048], cmd[2048];

	/* Open the command for reading. */
	sprintf(cmd, "/usr/bin/upsc %s@%s", ups, host);
	fp = popen(cmd, "r");

	if(fp == NULL)
		exit(1);
	int isStatus = 0;
	strcpy(status, "");

	while(fscanf(fp, "%s", line) != EOF)		
	{
		if(strchr(line, ':') != NULL)
			isStatus = 0;
		if(isStatus)
		{
			strcat(status, line);
			strcat(status, ",");
		}
		if(!strcmp(line, "ups.status:"))
			isStatus = 1;
	}

	pclose(fp);
	updateups(status);
}

void loop()
{
	while(1)
	{
		parse();
		sleep(pollFreq);
	}
}

void readconfig()
{
	FILE *fp = fopen("/etc/ups-parse/ups-parse.config", "rt");
	if(fp == NULL)
	{
		logmsg("/etc/ups-parse/ups-parse.config not found, use default settings\n");
		return;
	}
	else
	{
		char line[2048];
		int status = 0;
		while(fscanf(fp, "%s", line) != EOF)
		{
			if(!strcmp(line, "ups:"))
				status = 1;
			else if(!strcmp(line, "host:"))
				status = 2;
			else if(!strcmp(line, "pollfreq:"))
				status = 3;
			else if(!strcmp(line, "shutdowntime:"))
				status = 4;
			else
			{
				switch(status)
				{
					case 1:	strcpy(ups, line);	break;
					case 2:	strcpy(host, line);	break;
					case 3:	
						if(sscanf(line, "%d", &pollFreq) == 0)
						{
							logmsg("[config error] invalid type of pollfreq\n");
							exit(1);
						}
						else if(pollFreq <= 0)
						{
							logmsg("[config error] pollfreq should larger than 0\n");
							exit(1);
						}
						break;
					case 4:	
						if(sscanf(line, "%d", &shutDownTime) == 0)
						{
							logmsg("[config error] invalid type of shutdowntime\n");
							exit(1);
						}
						else if(shutDownTime <= 0)
						{
							logmsg("[config error] shutdowntime should larger than 0\n");
							exit(1);
						}
						break;	
					default:
						break;
				}
			}
		}
	}

	fclose(fp);
}

void logconfig()
{
	char msg[2048];
	sprintf(msg, "[config] ups: %s, host: %s\n", ups, host);
	logmsg(msg);
	sprintf(msg, "[config] pollfreq: %d, shutdowntime: %d\n", pollFreq, shutDownTime);
	logmsg(msg);
}

int main(void) {      
	
    // Our process ID and Session ID
    pid_t pid, sid;
        
    // Fork off the parent process 
    pid = fork();
    if (pid < 0) {
            exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // Change the file mode mask 
    umask(0);
            
    // Open any logs here   
            
    // Create a new SID for the child process
    sid = setsid();
    if (sid < 0) {
        // Log the failure 
        exit(EXIT_FAILURE);
    }
        
    // Change the current working directory
    if ((chdir("/")) < 0) {
        // Log the failure
        exit(EXIT_FAILURE);
    }
        
    // Close out the standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
   
    // Daemon-specific initialization goes here
    readconfig();
	logconfig();
	loop();
        
	exit(EXIT_SUCCESS);
}
