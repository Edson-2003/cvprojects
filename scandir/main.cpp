#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h> 

struct images
{
  char *name;
  struct images *next;
};

struct list
{
  struct images *first;
};

struct list *list = NULL;

void
insert(const char *name)
{
  if(name == NULL) return;
  if(list == NULL)
  {
    list = (struct list *) malloc(sizeof(struct list));
    struct images *nw;
    nw = (struct images *) malloc(sizeof(struct images));
    int len = strlen(name);
    nw->name = (char *) malloc(sizeof(char));
    nw->next = NULL;
    strcpy(nw->name, name);
    list->first = nw;
    return;
  }
  
  
  struct images *nw;
  nw = (struct images *) malloc(sizeof(struct images));
  int len = strlen(name);
  nw->name = (char *) malloc(sizeof(char));
  //nw->next = NULL;
  
  struct images *tmp;
  tmp = list->first;
  strcpy(nw->name, name);
  nw->next = tmp;
  list->first = nw;
  
  return;
}

void
printlist()
{
  
  if((list == NULL) && (list->first == NULL)) return;
  struct images *temp;
  temp = list->first;
  // printf("%s \n", temp->name);

  while(temp != NULL)
  {
    printf("%s \n", temp->name);
    temp = temp->next;
  }

  return;
}



bool
extension(const char *name)
{
  if(name == NULL) return NULL;
  int len = strlen(name);
  if(*name[len - 5] == ".")
  {
    if((*name[len - 4] == "p") && (*name[len - 3] == "n") && (*name[len - 2] == "g")) return true;
  }
}


void
listFiles(const char *dirpath)
{
  DIR *dirp;
  //struct dirent *dp;
  
  dirp = opendir(dirpath);
  
  if (dirp == NULL) return;

  while(1)
  {
    //printf("inside the while loop\n");
    struct dirent *dp = readdir(dirp);
    
    if (dp == NULL) break;
    
    if ((strcmp(dp->d_name, ".") == 0) || (strcmp(dp->d_name, "..") == 0)) continue; 
    
    if(dp->d_name != NULL) //printf("%s\n", dp->d_name);
    { 
      //printf("%s \n", dp->d_name);
      
      /*
      char *name;
      strcpy(name, dp->d_name);

      char separator[] = ".";
      strtok(dp->d_name, separator);
      strtok(NULL, separator);
      //if((strcmp(strtok(dp->d_name, "."), "png") == 0) || (strcmp(strtok(dp->d_name, "."), "jpg") == 0)) continue;
      //printf("%s \n", extension);
      */
      if(extension(dp->d_name)) insert(dp->d_name);

    }
   // printf("%s/", dirpath);
  }

}

int 
main(int argc, char **argv)
{
  //printf("%s\n", argv[1]);
  listFiles(argv[1]);
  printlist();
  return 0;
}
