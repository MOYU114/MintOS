void  echo_string(int argc, char * argv[]) {
    int i;
	for (i = 1; i < argc; i++) {
		printf("%s%s", i == 1 ? "" : " ", argv[i]);
	}
	printf("\n");
}