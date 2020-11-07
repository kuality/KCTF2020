#include <stdio.h>
#include <string.h>

int main2(int argc, char * argv[]) {

	//char flag[] = "FLAG is KCTF{D0_Y0U_Kn0W_PE_f0rm4t??}";
	char enc[] = "FMCD$lu'CJ^MwI>PI!GL_{&@GI_Dz-lr\x14U\x1d\x1cY";

	for (int i = 0; i < strlen(enc); i++) {
		printf("%c", enc[i] ^ i);
	}
	printf("\n");

	return 0;
}