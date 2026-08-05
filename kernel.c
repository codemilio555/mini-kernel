
void print(char *value, char *video);

void main(){
	//My kernel!!!
	
	char *video =(char*)0xB8000;

	video[0]='A';
	video[1]=0x07;
	while(1){}
}

void print(char *value, char *video){
	int d = 0;
	for(int i=0;value[i]!=0;i++){
		video[d]=value[i];
		d++;
		video[d]=0x07;
		d++;
	}
	
}
