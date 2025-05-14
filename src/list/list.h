#ifndef LIST_H
#define LIST_H

#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../constants/constants.h"

int load_template_and_replace(const char*  filename, 
                  	      const char*  placeholder, 
                  	      const char*  replacement,
                        	    char** result_ptr);

int parse_string(const char* input, 
         	 char*       output,
         	 size_t      output_size,
		 char*	     type_parse);

#endif
