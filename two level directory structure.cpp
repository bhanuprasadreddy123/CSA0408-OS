#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_FILENAME_LEN 256
#define MAX_FILES 100

void create_directory(const char *path) {
mkdir(path, 0777); 
}

void organize_files(const char *source_dir, const char *dest_dir) {

create_directory(dest_dir);

for (int i = 0; i < 10; i++) {
char level2_dir[MAX_FILENAME_LEN];
snprintf(level2_dir, sizeof(level2_dir), "%s/level%d", dest_dir, i);
create_directory(level2_dir);
}

DIR *dir;
struct dirent *entry;
dir = opendir(source_dir);
if (dir == NULL) {
perror("Error opening directory");
exit(EXIT_FAILURE);
}

while ((entry = readdir(dir)) != NULL) {
if (entry->d_type == DT_REG) { 
char source_file[MAX_FILENAME_LEN];
snprintf(source_file, sizeof(source_file), "%s/%s", source_dir, entry->d_name);
char dest_file[MAX_FILENAME_LEN];
snprintf(dest_file, sizeof(dest_file), "%s/level%d/%s", dest_dir, (entry->d_name[4] - '0'), entry->d_name);
rename(source_file, dest_file); 
}
}

closedir(dir);
}

int main() {
const char *source_dir = "source";
const char *dest_dir = "level1";

create_directory(source_dir);

FILE *fp;
char filename[MAX_FILENAME_LEN];
for (int i = 0; i < MAX_FILES; i++) {
snprintf(filename, sizeof(filename), "%s/file%d.txt", source_dir, i);
fp = fopen(filename, "w");
if (fp == NULL) {
perror("Error creating file");
exit(EXIT_FAILURE);
}
fclose(fp);
}

organize_files(source_dir, dest_dir);

printf("Files organized successfully!\n");

return 0;
}
