#include <string.h>
#include "header_work.h"
#include "utils.h"

void insert_to_data(data_t *data, char *text, int *flag, state_t state) {
  size_t len = strlen(text) + 1;

  switch (state) {
    case STATE_FROM:
      memmove(data->from, text, len);
      break;
    case STATE_TO:
      memmove(data->to, text, len);
      break;
    case STATE_DATE:
      memmove(data->date, text, len);
      break;
    default:
      break;
  }

  *flag = 1;
}

char* add_to_text(char *res, char c, int *flag, FILE* file) {
  c = fgetc(file);
  fseek(file, -1, SEEK_CUR);
  size_t space = c == ' ' ? 1 : 0;
  int i = 0;
  while (c != '\n' && c != '\r') {
    i++;
    c = fgetc(file);
  }

  size_t len = i - space + *flag;
  fseek(file, -len, SEEK_CUR);

  char *buffer = calloc(len, sizeof(char));
  if (buffer == NULL) {
    return NULL;
  }

  fgets(buffer, len, file);
  size_t len_buffer_2 = 0;
  if (res == NULL) {
    len_buffer_2 = strlen(buffer) + space + 1;
  } else {
    len_buffer_2 = strlen(res) + strlen(buffer) + space + 1;
  }

  char *buffer_2 = calloc(len_buffer_2, sizeof(char));
  if (buffer_2 == NULL) {
    free(buffer);
    return NULL;
  }

  if (res == NULL) {
    memmove(buffer_2, buffer, len);
  } else {
    snprintf(buffer_2, len_buffer_2, "%s%s", res, buffer);
  }

  ++len_buffer_2;
  char *return_str = calloc(len_buffer_2, sizeof(char));

  if (return_str == NULL) {
    free(res);
    free(buffer);
    free(buffer_2);
    return NULL;
  }
  memmove(return_str, buffer_2, --len_buffer_2);
  *flag = 1;
  free(res);
  free(buffer);
  free(buffer_2);
  return return_str;
}

int check_header(const char *search, char *str, int *flag, FILE *file, char *res_header
    , data_t *data, state_t st) {
  if (strcasecmp(search, str) == 0 && *flag == 0) {
    char next_char = fgetc(file);
    fseek(file, -1, SEEK_CUR);

    if (next_char == ' ') {
      return 2;
    }

    if (alloc_mem_struct(data, res_header, st)) {
      return EXIT_FAILURE;
    }

    insert_to_data(data, res_header, flag, st);
  }

  return EXIT_SUCCESS;
}

int insert_to_header(char *res_header, char *str, FILE *file
    , flags_t *flags, data_t *data, state_t state) {
  int check_err = 0;
  if (flags->flag == 1) {
    switch (state) {
      case STATE_FROM:
        check_err = check_header("From:", str, &flags->flag_from, file, res_header, data, state);
        break;

      case STATE_TO:
        check_err = check_header("To:", str, &flags->flag_to, file, res_header, data, state);
        break;

      case STATE_DATE:
        check_err = check_header("Date:", str, &flags->flag_date, file, res_header, data, state);
        break;
      default:
        break;
    }
  }

  return check_err;
}

int find_header(char *str, flags_t *flags, state_t *state_header
    , char **res_header, char c, FILE *file) {
  if (!strcasecmp("From:", str) && !flags->flag_from) {
    *res_header = add_to_text(*res_header, c, &flags->flag, file);
    *state_header = STATE_FROM;
    if (res_header == NULL) {
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  }

  if (!strcasecmp("To:", str) && !flags->flag_to) {
    *state_header = STATE_TO;
    *res_header = add_to_text(*res_header, c, &flags->flag, file);
    if (res_header == NULL) {
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  }

  if (!strcasecmp("Date:", str) && !flags->flag_date) {
    *res_header = add_to_text(*res_header, c, &flags->flag, file);
    *state_header = STATE_DATE;
    if (res_header == NULL) {
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  }

  return EXIT_SUCCESS;
}
