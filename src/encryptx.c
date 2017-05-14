#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	// Ensure arguments
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return 0;
	}

	// Check if file exists
	if (access(argv[1], F_OK) == -1){
		fprintf(stderr, "cannot find file: %s\n", argv[1]);
		return -1;
	}

	// Initial regs
	
	// Password confirmation
	char *key = getpass("Enter key: ");
	char *key_safe = malloc(strlen(key));
	strcpy(key_safe, key);
	
	char *key_conf = getpass("Confirm key: ");
	key = key_safe;

	if ( strcmp(key, key_conf) != 0 ) {
		printf("Keys don't match. Try again.\n");
		return 0;
	}

	int key_size = strlen(key);

	// Open input and output files
	char *file_out_name = malloc(strlen(argv[1]) + 4);
	sprintf(file_out_name, "%s_out", argv[1]);

	FILE *file_in, *file_out;
	file_in = fopen(argv[1], "r");
	file_out = fopen(file_out_name, "w+");
	
	// Empty mem location for the character byte
	char *read_byte = malloc(1);
	int counter = 0;
	
	while (fread(read_byte,(size_t) 1, 1, file_in) == 1) {
		
		// Change the read_byte
		read_byte[0] = (char) (((int) read_byte[0])^((int) key[counter]));
		
		// Change key character
		counter++;
		counter %= key_size;
		
		// Write to output file
		fwrite(read_byte, (size_t) 1, 1, file_out);
	}

	char *cmd1, *cmd2;
	cmd1 = malloc(strlen(argv[1]) + 3);
	cmd2 = malloc(2*strlen(argv[1]) + 10);

	sprintf(cmd1, "rm %s", argv[1]);
	sprintf(cmd2, "mv %s %s", file_out_name, argv[1]);

	system(cmd1);
	system(cmd2);
}
