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

typedef enum {
    STATE_FROM = 0,
    STATE_TO,
    STATE_DATE
} state_t;

void insert_to_data(data_t *data, char *text, int *flag, state_t state);

void insert_to_data(data_t *data, char *text, int *flag, state_t state) {
    switch (state) {
        case STATE_FROM:
            strcpy(data->from, text);
            break;
        case STATE_TO:
            if (strlen(text) == 0) {
                strcpy(data->to, "sdf");
            }
            else {
            strcpy(data->to, text);
            }
            break;
        case STATE_DATE:
            strcpy(data->date, text);
            break;
        default:
            break;
    }
    
    *flag = 1;
    text[0] = '\0';
}
void add_to_text(char *text, char c, int *flag);

void add_to_text(char *text, char c, int *flag) {
    append(text,c);
    if (text[0] == ' ' || text[0] == ':') {
        text[0] = '\0';
    }
    *flag = 1;
}

int parse(data_t *data, FILE *file);
int parse(data_t *data, FILE *file){
    char c;
    char *s = calloc(10000, sizeof(char));
    char *res_header = calloc(100000000, sizeof(char));
    char *res4 = calloc(1000, sizeof(char));
    char *res_end = calloc(1000, sizeof(char));
    
    if (data == NULL) {
        return -1;
    }
    
    data->to = (char*)malloc(1);
    
    if (data->to == NULL) {
        return -1;
    }
    
    data->from = (char*)malloc(1);
    
    if (data->from == NULL) {
        return -1;
    }
    
    data->date = (char*)malloc(1);
    
    if (data->date == NULL) {
        return -1;
    }
    
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
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            if (flag == 1) {
                char next_char = '_';
                if (strcasecmp ("From:", s) == 0 && flag_from == 0) {
                    next_char = fgetc(file);
                    fseek(file, -1, SEEK_CUR);
                    if (next_char == ' ') {
                        continue;
                    }
                    if (strlen(res_header) == 0){
                        data->from = realloc(data->from,1);
                    }
                    else {
                        data->from = realloc(data->from,sizeof(char) * strlen(res_header)+1);
                    }
                    if (data->from == NULL) {
                        return -1;
                    }
                    insert_to_data(data, res_header, &flag_from, STATE_FROM);
                }
                
                if (strcasecmp ("To:", s) == 0  && flag_to == 0) {
                    next_char = fgetc(file);
                    fseek(file, -1, SEEK_CUR);
                    
                    if(next_char == ' ') {
                        continue;
                    }
                    
                    if (strlen(res_header) == 0){
                        data->to = realloc(data->to,1);
                    }
                    else {
                        data->to = realloc(data->to,sizeof(char) * strlen(res_header)+1);
                    }
                    if (data->to == NULL) {
                        return -1;
                    }
                    insert_to_data(data, res_header, &flag_to, STATE_TO);
                }
                
                if (strcasecmp ("Date:", s) == 0  && flag_date == 0) {
                    if (strlen(res_header) == 0){
                        data->date = realloc(data->date,1);
                    }
                    else {
                        data->date = realloc(data->date,sizeof(char) * strlen(res_header)+1);
                    }
                    if (data->date == NULL) {
                        return -1;
                    }
                    insert_to_data(data, res_header, &flag_date, STATE_DATE);
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
            if (c != '\r') {
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
                    add_to_text(res_header, c, &flag);
                    continue;
                }
                
                if (strcasecmp ("To:", s) == 0 && flag_to == 0) {
                    add_to_text(res_header, c, &flag);
                    continue;
                }
                    
                if (strcasecmp ("Date:", s) == 0 && flag_date == 0) {
                    add_to_text(res_header, c, &flag);
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
    return 0;
}
int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }

    const char *path_to_eml = argv[1];
    FILE *file = fopen(path_to_eml, "r");
    
    if (file == NULL) {
        return -1;
    }
    data_t *data = calloc(1, sizeof(data_t));
    if (parse(data,file) == -1) {
        free(data->to);
        free(data->from);
        free(data->date);
        free(data);
        return -1;
    }
    printf("%s|%s|%s|%d",data->from,data->to,data->date,data->part);
    free(data->to);
    free(data->from);
    free(data->date);
    free(data);
    return 0;
}

int append(char *s, char c) {
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
    return 0;
}

