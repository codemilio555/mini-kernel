#define WIDTH 80

#define HEIGHT 40
void print(char *value, char *video);
int write = 0;

void main(){
	//My kernel!!!
	
	char *video =(char*)0xB8000;

	print("Hallo Welt",video);
	print("new\nline", video);
	while(1){}
}
/*
void set_cursor(int pos){
	int *low = (int*)0x3D4;
	int *high = (int*)0x3D5;

	low=0x01;
	high=0x00;
}
*/
//print
void print(char *value, char *video){
	for(int i=0;value[i]!=0;i++){
		if(value[i]=='\n'){
			//*2 beacuse every char is 2 bytes (char, color)
			//setting write to a line start and adding a new line
			write= (write - (write%(WIDTH*2)))+(WIDTH*2);
			continue;
		}
		//writing char
		video[write]=value[i];
		write++;
		//writing color
		video[write]=0x07;
		write++;
	}
	
}
