#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *imageFile, *outFile;
	int i, data, nextData;
	int cnt = 0;

	if((imageFile = fopen("test.bmp", "rb")) == NULL)
	{
		printf("can't open imgFile.");
		exit(1);
	}

	if((outFile = fopen("Lena.cod", "wb")) == NULL)
	{
		printf("can't open outFile.");
		exit(1);
	}

	while(!feof(imageFile))
	{
		data = fgetc(imageFile);
		cnt++;

		if (cnt >= 1078)
		{
			cnt = 1;
			fputc(data, outFile);
			while(!feof(imageFile)){
				nextData = fgetc(imageFile);
				if(data != nextData){
					fputc(cnt % 256, outFile);
					cnt /= 256;
					fputc(cnt, outFile);
					cnt = 0;
					data = nextData;
				}
				cnt++;
			}
			goto closeFile;
		}
		fputc((char)data, outFile);
	}
	closeFile:
		if (fclose(imageFile))
			exit(1);
		if (fclose(outFile))
			exit(1);
		system("pause");
		return 0;
}