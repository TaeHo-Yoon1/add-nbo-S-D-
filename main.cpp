#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t my_ntohl(uint32_t netlong) {
    return ((netlong & 0xFF000000) >> 24) |
           ((netlong & 0x00FF0000) >> 8) |
           ((netlong & 0x0000FF00) << 8) |
           ((netlong & 0x000000FF) << 24);
}
	

int main(int argc, char *argv[]){

	uint32_t nums[argc - 1];
	FILE *files[argc - 1];

	if(argc < 3) return 1;

	for(int i=0; i < argc - 1; i++){
		files[i] = fopen(argv[i+1], "rb");
		if(!files[i]) return 1;

	}
	
	for(int i = 0; i < argc - 1; i++){
		fseek(files[i], 0, SEEK_END);
		long size = ftell(files[i]);
		if (size < 4) {
			for(int j = 0; j <= i; j++){
				fclose(files[j]);
			}
			return 1;
		}
		fseek(files[i], 0, SEEK_SET);

		// 파일 읽기
		if(fread(&nums[i], sizeof(uint32_t), 1, files[i]) != 1){
			for(int j = 0; j <= i; j++){
				fclose(files[j]);
			}
			return 1;
		}
	}


	for(int i=0; i < argc -1; i++){

		fclose(files[i]);

	}	
	
	uint32_t sum = 0;
    	for(int i = 0; i < argc - 1; i++){
        	nums[i] = my_ntohl(nums[i]);
       		sum += nums[i];
    	}

    	for(int i = 0; i < argc - 2; i++){
        	printf("%u(0x%x) + ", nums[i], nums[i]);
    	}
    	printf("%u(0x%x) = %u(0x%x)\n",    nums[argc-2], nums[argc-2], 
           sum, sum);



	return 0;

}
