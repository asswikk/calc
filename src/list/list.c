#include "list.h"

int load_template_and_replace(const char*  filename, 
			      const char*  placeholder, 
			      const char*  replacement,
			            char** result_ptr) {
    int flag_error = ERR_OK;

    FILE* file = fopen(filename, "r");
    if(  !file)
	flag_error = ERR_FILE_NOT_FOUND;
    else {
	fseek( file, 0, SEEK_END);
	long len = ftell(file);
	rewind(file);

	char* buffer = malloc(len + 1);
	if(  !buffer)
	    flag_error = ERR_ALLOCATION;
	else {
	    fread(buffer, 1, len, file);
	    buffer[len] = '\0';
	    fclose(file);

	    char* pos = strstr(buffer, placeholder);
	    if(  !pos)
		flag_error = ERR_SEARCH;
	    else {
		size_t new_len = len + strlen(replacement) - strlen(placeholder);
		char* local_result = malloc(new_len + 1);
		if(  !local_result)
		    flag_error = ERR_ALLOCATION;
		else {
		    size_t 	 prefix_len = pos - buffer;
		    strncpy(local_result, buffer, prefix_len);
		    local_result[prefix_len] = '\0';

		    strcat(local_result, replacement);
		    strcat(local_result, pos + strlen(placeholder));

		    *result_ptr = local_result;
		    local_result = NULL;
		}
	    }
	    free(buffer);
	}
    }

    return flag_error;
}

int parse_string(const char* input, 
	char*       output,
	size_t      output_size,
	char*       type_parse) {
int flag_error = ERR_OK;

type_parse[MAX_TYPE_PARSE_LEN - 1] = '\0';
int type = atoi(type_parse);

char* temp_str = strdup(input);
if (!temp_str) {
flag_error = ERR_ALLOCATION;
} else {
const char* delimiters = ", ";
char* token = strtok(temp_str, delimiters);

int result = 0;
int count = 0;
int division_by_zero = 0;

while (token != NULL && count < MAX_WORDS) {
double num = atof(token);

if (count == 0) {
   result = num; // инициализация результатом первого числа
} else {
   switch (type) {
	   case 1: // сложение
		   result += num;
		   break;
	   case 2: // вычитание
		   result -= num;
		   break;
	   case 3: // умножение
		   result *= num;
		   break;
	   case 4: // деление
		   if (num == 0) {
			   division_by_zero = 1;
		   } else {
			   result /= num;
		   }
		   break;
	   default:
		   flag_error = ERR_INVALID_TYPE;
		   break;
   }
}

count++;
token = strtok(NULL, delimiters);
}

if (division_by_zero) {
snprintf(output, output_size, "ДЕЛЕНИЕ НА 0");
flag_error = ERR_DIVISION_BY_ZERO;
} else if (flag_error == ERR_OK) {
snprintf(output, output_size, "РЕЗУЛЬТАТ: %d", result);
}

free(temp_str);
}

return flag_error;
}


