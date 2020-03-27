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
    char *s = calloc(10000, sizeof(char));
    char *res_header = calloc(1000000000, sizeof(char));
    char *res4 = calloc(1000, sizeof(char));
    char *res_end = calloc(1000, sizeof(char));
    data_t *data = calloc(1, sizeof(data_t));
    data->from = calloc(1000, sizeof(char));
    data->to = calloc(1000000000, sizeof(char));
    data->date = calloc(1000, sizeof(char));
    char *boundary = calloc(1000, sizeof(char));
    int flag = 0;
    int flag_from = 0;
    int flag_to = 0;
    int flag_date = 0;
    int flag_boundary = 0;
    int count = 0;
    int count_bin = 0;
    int bin_flag = 0;
    int end_flag = 0;
    while((c = fgetc(file)) != EOF) {
        if(c == '\n') {
            if (flag == 1) {
                char next_char = '_';
                if (strcasecmp ("From:", s) == 0 && flag_from == 0) {
                    next_char = fgetc(file);
                    fseek(file, -1, SEEK_CUR);
                    if(next_char == ' ') {
                        continue;
                    }
                    strcpy(data->from, res_header);
                    flag_from = 1;
                    res_header[0] = '\0';
                }
                
                if (strcasecmp ("To:", s) == 0  && flag_to == 0) {
                    next_char = fgetc(file);
                    fseek(file, -1, SEEK_CUR);
                    if(next_char == ' ') {
                        continue;
                    }
                    strcpy(data->to, res_header);
                    flag_to = 1;
                    res_header[0] = '\0';
                }
                
                if (strcasecmp ("Date:", s) == 0  && flag_date == 0) {
                    strcpy(data->date, res_header);
                    flag_date = 1;
                    res_header[0] = '\0';
                }
                
                if (strcasecmp ("boundary=", boundary) == 0 && flag_boundary == 0) {
                    flag_boundary = 1;
                    strcpy(res_end, res4);
                    append(res_end,'-');
                    append(res_end,'-');
                }
            }
            
            if (strstr(s, res4) != NULL && flag_boundary == 1) {
                ++count;
                bin_flag = 1;
            }
            
            if (strstr(s, res_end) != NULL && flag_boundary == 1) {
                --count;
                bin_flag = 1;
            }
            s[0] = '\0';
            boundary[0] = '\0';
            flag = 0;
            end_flag++;
        }
        else {
            if(c != '\r') {
                end_flag = 0;
                if (flag == 0) {
                    if (c == ' ' || c == '\t' || c == ';') {
                        boundary[0] = '\0';
                    }
                    else {
                        append(boundary,c);
                    }
                    
                    append(s,c);
                }
                
                if (strcasecmp ("From:", s) == 0 && flag_from == 0) {
                    append(res_header,c);
                    if (res_header[0] == ' ' || res_header[0] == ':') {
                        res_header[0] = '\0';
                    }
                    flag = 1;
                    continue;
                }
                
                if (strcasecmp ("To:", s) == 0 && flag_to == 0) {
                    append(res_header,c);
                    if (res_header[0] == ' ' || res_header[0] == ':') {
                        res_header[0] = '\0';
                    }
                    flag = 1;
                    continue;
                }
                    
                if (strcasecmp ("Date:", s) == 0 && flag_date == 0) {
                    append(res_header,c);
                    
                    if (res_header[0] == ' ' || res_header[0] == ':') {
                        res_header[0] = '\0';
                    }
                    
                    flag = 1;
                    continue;
                }
                
                if (strcasecmp ("boundary=", boundary) == 0 && flag_boundary == 0) {
                    if (count_bin > 2) {
                        continue;
                    }
                    
                    append(res4,c);
                    if (res4[0] == '='){
                        res4[0] = '\0';
                        append(res4,'-');
                        append(res4,'-');
                    }
                    
                    if (c == '"' || c == ' ' || c == ';') {
                        ++count_bin;
                        res4[strlen(res4)-1] = '\0';
                    }
                    
                    flag = 1;
                }
            }
        }
    }

    fclose(file);
    
    if (strstr(s, res4) != NULL && flag_boundary == 1) {
        ++count;
        bin_flag = 1;
    }
    
    if (strstr(s, res_end) != NULL && flag_boundary == 1) {
        --count;
        bin_flag = 1;
    }
    
    if (count == 0 && end_flag < 3 && bin_flag == 0) {
           count = 1;
    }
    
    data->part = count;
    
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

