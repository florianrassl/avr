

/*
###################################
##          PID REGLER           ##
###################################
*/

//proportional–integral–derivative controller
//um sensordaten zu mischen wierd der kalman filter oder Komplementärfilter verwendet.

//http://rn-wissen.de/wiki/index.php/Regelungstechnik#P-Regler

/*
Ta (Abtastzeit)
Kp = proportional anteil
Ki = integral anteil
kd = differenal anteil

esum = esum + e
y = Kp * e + Ki * Ta * esum + Kd * (e – ealt)/Ta
ealt = e
*/

#define TA 0.2

#define KP 1.0
#define KI 1.0
#define KD 1.0

typedef struct PID{	
	int esum;
	int ealt;
}PID;

void update(){
}


void PIDcalc(PID *pid, int e, int *erg){
	pid->esum += e;
	*erg = KP*e+KI*TA*pid->esum+KD*(e-pid->ealt)/TA;
	pid->ealt = e;
}
