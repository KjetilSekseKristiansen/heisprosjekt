
static double timer;

void start_timer(){
	timer = time(null);
}

int checkTimer(){
	if(timer>=3)
		return 1;
	else
		return 0;
}