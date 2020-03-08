#include "utils.h"

int main(void){
		int choice = 0;
		FILE *ptr, *ptr_2, *blackrecord;
        Data client_data = {0};
        Data transfer = {0};
        output_menu(3);
    
        while (scanf("%d", &choice) != -1) {
            switch(choice) {
				case 1:
                    ptr = fopen(filename_1, "a");
                    
                    if(ptr == NULL) {
                        puts("Not acess");
                    }
                    else {
                        masterWrite(ptr, client_data);
                        fclose(ptr);
                    }
                    
                    break;
				case 2:
                    ptr = fopen(filename_2, "a");
                    
                    if(ptr == NULL) {
                        puts("Not acess");
                    }
                    else {
                        transactionWrite(ptr, transfer);
                        fclose(ptr);
                    }
                    
                    break;
				case 3:
                    ptr = fopen(filename_1, "r");
                    ptr_2 = fopen(filename_2, "r");
                    blackrecord = fopen(filename_3, "w");
                        
                    if(ptr == NULL || ptr_2 == NULL || &blackRecord == NULL) {
                        puts("exit");
                    }
                    else {
                        blackRecord(ptr, ptr_2, blackrecord, client_data,  transfer);
                        fclose(ptr);
                        fclose(ptr_2);
                        fclose(blackrecord);
                    }
                    
                    break;
                default:
					puts("error");
					break ;
				}
            
            output_menu(3);
		}
    
  return 0;
}
