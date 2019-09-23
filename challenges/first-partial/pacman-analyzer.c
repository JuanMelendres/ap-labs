//Juan Antonio Melendres Villa A00369017
/*
  References:
    -> In this web site I see the different types of Sys calls. Web site: http://codewiki.wikidot.com/c:system-calls:open. Also in GeeksForGeeks
    -> I see more information about open, read, write. WebSite: https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/.
    -> In the book in the section 8.1 File descriptors I read about the sys calls.
    -> in this web site I see a general idea of how to implement my solution. Webs site: http://www.wellho.net/resources/ex.php4?item=c209/lunches.c
    -> Problem: There is a problem with the read function, the size to be espesific it doesn't take all the chars
        and create me problems to store in the varibles, I tryed with diferente size and the with 55 (read(readFile, buffer, 55)),
        I got 526 installed pakages, removed 30, Current 496, but when I came to the while loop there is an error. thats why the code doesn't works well sorry.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define REPORT_FILE "packages_report.txt"
#define BUFSIZE 512
#define MAXARRAY 10000

void analizeLog(char *logFile, char *report);

typedef struct {
  char pkgName[30];
  char insDate[20];
  char update[20];
  int numUpd;
  char remDate[20];
} packages;

typedef struct {
  int insPkg;
  int remPkg;
  int updPkg;
  int curInsPkg;
} packagesReport;

int main(int argc, char **argv) {

    if (argc < 2) {
	     printf("Usage:./pacman-analizer.o pacman.log\n");
	     return 1;
    }

    analizeLog(argv[1], REPORT_FILE);

    return 0;
}

void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);

    // Implement your solution here.
    int readFile = open(logFile, O_RDONLY);
    /* Works but only report 1 package
    if(readFile < 0) {
      perror("Error message: ");
      exit(1);
    }
    int fileLength = lseek(readFile, 512, SEEK_END);
    close(readFile);
    lseek(readFile, 512, SEEK_SET);
    readFile = open(logFile, O_RDONLY);
    */
    if(readFile < 0) {
      perror("Error message: ");
      exit(1);
    }
    packages arrPackages[MAXARRAY];
    packagesReport pkgReport;
    char *line;
    char buffer[BUFSIZE];
    //char *buffer = (char *) calloc(512, sizeof(char));
    char auxDate[20];
    char auxName[30];
    int n = 0;
    int count = 0;
    char *checkType;
    while((count = read(readFile, buffer, BUFSIZE)) > 0) { //(count = read(readFile, buffer, 1024)) > 0
      checkType = strstr(buffer, "[ALPM] installed");
      if (checkType != NULL) {
        line = strtok(buffer, " ");
        line++;
        strcpy(arrPackages[n].insDate, line);
        strcpy(arrPackages[n].update, line);
        line = strtok(NULL, "]");
        strcat(arrPackages[n].insDate, " ");
        strcat(arrPackages[n].update, " ");
        strcat(arrPackages[n].insDate, line);
        strcat(arrPackages[n].update, line);
        line = strtok(NULL, " ");
        line = strtok(NULL, " ");
        line = strtok(NULL, " ");
        strcpy(arrPackages[n].pkgName, line);
        pkgReport.insPkg++;
        n++;
      }
      else {
        checkType = strstr(buffer, "[ALPM] removed");
        if (checkType != NULL) {
          line = strtok(buffer, " ");
          line++;
          strcpy(auxDate, line);
          line = strtok(NULL, "]");
          strcat(auxDate, " ");
          strcat(auxDate, line);
          line = strtok(NULL, " ");
          line = strtok(NULL, " ");
          line = strtok(NULL, " ");
          strcpy(auxName, line);
          int j = 0;
          while(strcmp(arrPackages[j].pkgName, auxName) == 0){
            j++;
          }
          strcpy(arrPackages[j].remDate, auxDate);
          pkgReport.remPkg++;
        }
        else {
          checkType = strstr(buffer, "[ALPM] upgraded");
          if (checkType != NULL) {
            line = strtok(buffer, " ");
            line++;
            strcpy(auxDate, line);
            line = strtok(NULL,"]");
            strcat(auxDate," ");
            strcat(auxDate, line);
            line = strtok(NULL, " ");
            line = strtok(NULL, " ");
            line = strtok(NULL, " ");
            strcpy(auxName, line);
            int j = 0;
            while(strcmp(arrPackages[j].pkgName, auxName) == 0){
              j++;
            }
            strcpy(arrPackages[j].update, auxDate);
            arrPackages[j].numUpd++;
            pkgReport.updPkg++;
          }
        }
      }
      memset(buffer, ' ', 512);
    }
    pkgReport.curInsPkg = pkgReport.insPkg - pkgReport.remPkg;
    close(readFile);
    FILE *repFile;
    repFile = fopen(report, "w");
    fprintf(repFile, "Pacman Packages Report\n");
    fprintf(repFile, "----------------------\n");
    fprintf(repFile, "- Installed packages : %d\n", pkgReport.insPkg);
    fprintf(repFile, "- Removed packages   : %d\n", pkgReport.remPkg);
    fprintf(repFile, "- Upgraded packages  : %d\n", pkgReport.updPkg);
    fprintf(repFile, "- Current installed  : %d\n\n", pkgReport.curInsPkg);
    fprintf(repFile, "List of packages\n");
    fprintf(repFile, "----------------\n");
    int i = 0;
    while(arrPackages[i].pkgName[0] != '\0'){
      fprintf(repFile, "- Package Name        : %s\n", arrPackages[i].pkgName);
      fprintf(repFile, "\t- Install date      : %s\n", arrPackages[i].insDate);
      fprintf(repFile, "\t- Last update date  : %s\n", arrPackages[i].update);
      fprintf(repFile, "\t- How many updates  : %d\n", arrPackages[i].numUpd);
      if(arrPackages[i].remDate[0] != '\0') {
        fprintf(repFile, "\t- Removal date      : %s\n", arrPackages[i].remDate);
      }
      else{
        fprintf(repFile, "\t- Removal date      : -\n");
      }
      i++;
    }
    fclose(repFile);
    printf("Report is generated at: [%s]\n", report);
}
