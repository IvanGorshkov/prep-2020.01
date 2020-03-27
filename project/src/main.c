#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int append(char *s, char c);
typedef struct {
    char *from;
    char *to;
    char *date;
    int part;
} data_t;


int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }

    const char *path_to_eml = argv[1];
    FILE *file = fopen(path_to_eml, "r");
    if (file == NULL) {
        return -1;
    }
    char c;
    char *s = calloc(1000, sizeof(char));
    char *res = calloc(1000, sizeof(char));
    char *res2 = calloc(1000000000, sizeof(char));
    char *res3 = calloc(1000, sizeof(char));
    char *res4 = calloc(1000, sizeof(char));
    data_t *data = calloc(1, sizeof(data_t));
    data->from = calloc(1000, sizeof(char));
    data->to = calloc(1000000000, sizeof(char));
    data->date = calloc(1000, sizeof(char));
    char *boundary = calloc(1000, sizeof(char));
    int flag = 0;
    //int flag_space = 0;
    int flag_from = 0;
    int flag_to = 0;
    int flag_date = 0;
    int flag_boundary = 0;
    int flag_2 = 0;
    int count = 0;
    while((c = fgetc(file)) != EOF) {
        if(c == '\n') {
            if (flag == 1) {
                if (strcasecmp ("From:", s) == 0 && flag_from == 0) {
                    strcpy(data->from, res);
                    flag_from = 1;
                }
                if (strcasecmp ("To:", s) == 0  && flag_to == 0) {
                    strcpy(data->to, res2);
                    flag_to = 1;
                }
                if (strcasecmp ("Date: ", s) == 0  && flag_date == 0) {
                strcpy(data->date, res3);
                    flag_date = 1;

                }
                if (strcasecmp ("boundary=", boundary) == 0 && flag_boundary == 0) {
                    flag_boundary = 1;
                   // puts(res4);
                }
                
            }
            if (strstr(s, res4) != NULL && flag_boundary == 1) {
                count++;
                
            }
            s[0] = '\0';
            flag = 0;
            flag_2 = 0;
        }
        else { if(c == '\r') {
            
        }
        else{
            if (flag == 0) {
                if (c == ' ' || c == '\t' || c == ';') {
                    boundary[0] = '\0';
                }
                else {
                    append(boundary,c);
                   // printf("%s\n",boundary);
                }
            
            append(s,c);
            }
            if (strcasecmp ("From:", s) == 0) {
                if (flag_2 == 1 ){
                    append(res,c);
                    if (res[0] == ' '){
                        res[0] = '\0';
                    }
                }
                flag = 1;
                flag_2 = 1;
            }
            
            if (strcasecmp ("To:", s) == 0) {
                if (flag_2 == 1){
                append(res2,c);
                    if (res2[0] == ' '){
                        res2[0] = '\0';
                    }
                }
                flag = 1;
                flag_2 = 1;
            }
            if (strcasecmp ("Date: ", s) == 0) {
                 if (flag_2 == 1){
                    append(res3,c);
                }
                    flag = 1;
                    flag_2 = 1;
            }
            if (strcasecmp ("boundary=", boundary) == 0 && flag_boundary == 0) {
                
                if (flag_2 == 0){
                    append(res4,'-');
                    append(res4,'-');
                }
                else{
                    if(c == '"' || c == ' ' || c == ';'){
                        
                    }
                    else {
                        append(res4,c);
                    }
                }
               
                flag_2 = 1;
                flag = 1;
            }
        }
        }
    }
    //printf("<%s>\n",s);
    //printf("<%s>\n",res4);
    //printf("%s\n",strstr(s, res4));
    if (strstr(s, res4) != NULL && flag_boundary == 1) {
      //  puts("asdasd");
     count++;
    }
    --count;
    if (count == -1){
        count = 1;
    }
    data->part = count;
    fclose(file);
    if (data->from[strlen(data->from)] != '\0') {
    data->from[strlen(data->from)-1] = '\0';
    data->to[strlen(data->to)-1] = '\0';
    data->date[strlen(data->date)-1] = '\0';
    }
        
    printf("%s|%s|%s|%d",data->from,data->to,data->date,data->part);
    return 0;
}

int append(char *s, char c) {
  
     int len = strlen(s);
     s[len] = c;
     s[len+1] = '\0';
     return 0;
}
