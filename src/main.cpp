/*
# define PAMI_1
//# define PAMI_2
//# define PAMI_3
//# define PAMI_4
*/

# define TEST_MODE

# ifdef TEST_MODE
# define GLOBAL_WAIT 2000
# endif
# ifndef TEST_MODE
# define GLOBAL_WAIT 90000
# endif

//# define PRINT_DISTANCES

#include "move.h"
# include "../lib/TeamSelect/TeamSelect.hh"
#include "Superstar.hh"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>  // Si vous utilisez des timers FreeRTOS
#include "ESP32Servo.h"



const uint8_t sensorPinRight = A4;
const uint8_t sensorPinMidel = A2;
const uint8_t sensorPinLeft = A1;
const uint8_t servoPin = 17;
const uint8_t tirette = 11;
const uint8_t bouton_equipe = 10; // low = blue vers le haut, hight= jaune
char equipe = 'B'; // équipe bleu par default
//bool drapeau_task_1 = false ;

uint waypointIndex = 0;

/*
float x_goal = 500; // 1=2500 2=500 3=2400  4=500
float y_goal = 1600; // 1=1400 2=1600 3=1000 4=600
volatile bool go_to_1 = true ;
float x_goal_2 = 200;// 1=3000 2=200 3=2800 4=0
float y_goal_2 = 1800; // 1=1400 2=1800 3=1000 4=600
int avancement_depart = 200 ; //1=1100 2=200 3=600 4=100
int time_start = 2500; //1 = 90000s 2 = 90500s 3 = 90000s 4 = 90500s
int depart = 0 ;

*/

volatile unsigned long Time1; // Variable pour stocker le temps de départ
unsigned long elapsedTime;

int capteur(int sensorPin); 
float symetrie(float coordonne);
//volatile int8_t evitement = 0 ;

Servo myservo;

TaskHandle_t Task1;
TaskHandle_t Task2;
void Task1code(void *pvParameters);
void Task2code(void *pvParameters);

/* True when the superstar is doing the superstar-specific movements, used to change how avoidances are triggered*/
volatile bool SuperStarTime = false;

/* The distance above which we consider there is no floor */
const int SUPERSTAR_FLOOR_THRESHOLD = 75;

void setup() {
	Serial.begin(9600); 
	configureMotors();
	//create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
	xTaskCreatePinnedToCore(
										Task1code,   /* Task function. */
										"Task1",     /* name of task. */
										10000,       /* Stack size of task */
										NULL,        /* parameter of the task */
										1,           /* priority of the task */
										&Task1,      /* Task handle to keep track of created task */
										0);          /* pin task to core 0 */                  
	delay(500); 

	//create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
	xTaskCreatePinnedToCore(
										Task2code,   /* Task function. */
										"Task2",     /* name of task. */
										10000,       /* Stack size of task */
										NULL,        /* parameter of the task */
										1,           /* priority of the task */
										&Task2,      /* Task handle to keep track of created task */
										1);          /* pin task to core 1 */
	//delay(500); 
	myservo.setPeriodHertz(50);    // standard 50 hz servo
	myservo.attach(servoPin, 500, 10000);
	myservo.write(0);
	pinMode(8, OUTPUT);
	digitalWrite(8, LOW); // pour que le enable des  drive soit à low. 
	pinMode(tirette, INPUT_PULLUP);
	pinMode(bouton_equipe, INPUT_PULLUP);
	Serial.print("setup done");
}

void AvoidanceChecksNormal(int sensor_M, int sensor_L, int sensor_R)
{
	if ((evitement == 0) && moving() && avoidance[waypointIndex])
	{
		if (sensor_M > 5 && sensor_M < 200)
		{
			stop();
			Serial.println("obstacle Middle");
			if (sensor_L < sensor_R) evitement = 1; // evitement droit
			else evitement = 2; //evitement gauche
			vTaskDelay(10/portTICK_PERIOD_MS);
		}
		else if (sensor_L > 5 && sensor_L  < 100 )
		{
			stop();
			Serial.println("obstacle Left");
			evitement = 1;
			vTaskDelay(10/portTICK_PERIOD_MS);
		}
		else if (sensor_R > 5 && sensor_R < 100 )
		{
			stop();
			Serial.println("obstacle Right");
			evitement = 2;
			vTaskDelay(10/portTICK_PERIOD_MS);
		}
	}
}

void AvoidanceChecksSuperstar(int sensor_M, int sensor_L, int sensor_R)
{
	if ((evitement == 0) && moving() && avoidance[waypointIndex])
	{
		if (sensor_M > 5 && sensor_M < 200)
		{
			stop();
			Serial.println("obstacle Middle");
			evitement = 2; //evitement gauche
			vTaskDelay(10/portTICK_PERIOD_MS);
		}
	}
}

void FloorCheckSuperstar(int sensor_M, int sensor_L, int sensor_R)
{
	if ((evitement == 0) && moving())
	{
		if (sensor_L > SUPERSTAR_FLOOR_THRESHOLD && sensor_R > SUPERSTAR_FLOOR_THRESHOLD)
		{
			stop();
			Serial.println("no floor on either side");
			evitement = 3;
			vTaskDelay(1/portTICK_PERIOD_MS);
		}
		else if (sensor_L > SUPERSTAR_FLOOR_THRESHOLD)
		{
			stop();
			Serial.println("no floor on the left");
			evitement = 1; // gauche
			vTaskDelay(1/portTICK_PERIOD_MS);
		}
		else if (sensor_R > SUPERSTAR_FLOOR_THRESHOLD)
		{
			stop();
			Serial.println("no floor on the left");
			evitement = 2; // droite
			vTaskDelay(1/portTICK_PERIOD_MS);
		}
			
	}
}

void Task1code( void * pvParameters ){
	//vTaskDelay(1000);

	myservo.write(0);
	while (!(digitalRead(tirette))){
		vTaskDelay(20);
		Serial.println("wait la tirette task 1");
	}
	myservo.write(0); // to be REALLY redundant

	for(;;){

		
		if (depart == 1){
			depart ++;
			Serial.print("debut du compte à rebourt");
			Time1 = millis();
		}
		

		elapsedTime = millis() - Time1;

		if ((elapsedTime >10000) && (depart == 2)){
			stop();
			
				myservo.write(180);
				vTaskDelay(100);
				digitalWrite(8, HIGH);
				Serial.print("FIN");
				depart = 3;
				//while(1){}
		}

		int sensor_M = capteur(sensorPinMidel);
		int sensor_L = capteur(sensorPinLeft);
		int sensor_R = capteur(sensorPinRight);

		# ifdef PRINT_DISTANCES
		
	//Serial.print(" evitement:");
	//Serial.print(evitement);
		Serial.print("time:");
		Serial.print(elapsedTime);
		Serial.print(" equipe:");
		Serial.print(equipe);
		Serial.print(" R:");
		Serial.print(sensor_R);
		Serial.print(" M:");
		Serial.print(abs(sensor_M));
		Serial.print(" L:");
		Serial.print(sensor_L);
		//vTaskDelay(1000);
		//stepperR.stop(); stepperL.stop();
		Serial.print(" teta_actuelle:");
		Serial.print(teta_actuelle);
		Serial.print(" stepperR:");
		Serial.print(stepperR.getStepsCompleted());
		//Serial.print(" total_Steps_R:");
		//Serial.print(total_Steps_R); 
		Serial.print(" position x ");
		Serial.print(x_position);
		Serial.print(" position y ");
		Serial.print(y_position);
		Serial.print(" evitement ");
		Serial.println(evitement);

		# endif
		
		/* 
		
		if((abs(sensor_M) < 250)  && (evitement == true)  && (stepperR.getStepsCompleted() > 10) && (go_to_1) ){
			Serial.println("obstacle_midel");
			//xSemaphoreGive(stateChangeSemaphore);
			stop();
			Serial.println("end of the break");
			evitement = false;
			vTaskDelay(10/portTICK_PERIOD_MS); //pour laisser le temps au corps 2 de refaire ça boucle. 
			//xSemaphoreGive(stateChangeSemaphore);

		}
		*/ 

		# ifdef SUPERSTAR
		if (SuperStarTime) FloorCheckSuperstar(sensor_M, sensor_L, sensor_R);
		// The superstar tries to avoid the slope if this is uncommented
		//else AvoidanceChecksSuperstar(sensor_M, sensor_L, sensor_R);
		# endif
		# ifndef SUPERSTAR
		AvoidanceChecksNormal(sensor_M, sensor_L, sensor_R);
		# endif


				
	vTaskDelay(1/portTICK_PERIOD_MS);
	}
}
//Task2code: blinks an LED every 700 ms
void Task2code( void * pvParameters ){
 
	while (!(digitalRead(tirette))){
		vTaskDelay(20);
		Serial.println("wait la tirette task 2");
	} 
		
	 //vTaskDelay(200);
	if (digitalRead(bouton_equipe)){

		for (int i = 0; i < numPoints; i++)
		{
			waypoints[i].x = symetrie(waypoints[i].x);
		}

		equipe = 'J';
	} 
	Serial.println("debut core 2");
	Serial.println(equipe);
	vTaskDelay(GLOBAL_WAIT); 
	
	//1 = 10s 2 = 12s 3 = 10s 4 = 12s
//straight(400); //1=400 2=200 3=400 4=200

	if(depart==0){
		depart ++;
		Serial.println("go_to depart");
	}
	

		
	

	for (;;) {
	/* 

	if (evitement == false){  // xSemaphoreTake(stateChangeSemaphore, SEMAPHORE_WAIT_TIME) == pdTRUE
		evitement_droit();
		evitement = true;
	}

	*/ 
		//evitement = false;
		//vTaskDelay(300000/portTICK_PERIOD_MS);
		//straight(20000); // pour que le pami démarre meme s'il y a un obstacle devant lui. 
		//evitement = true; // pour que le pami démarre meme s'il y a un obstacle devant lui. 
		//vTaskDelay(300000/portTICK_PERIOD_MS);

		/*
		while (!((x_position >= waypoints[waypointIndex].x - 1 && x_position <= waypoints[waypointIndex].x + 1)
			&& (y_position >= waypoints[waypointIndex].y - 1 && y_position <= waypoints[waypointIndex].y + 1))) { */
		while (true)
		{
			Serial.println("debut du while");
/* 
			if (evitement == false){  // xSemaphoreTake(stateChangeSemaphore, SEMAPHORE_WAIT_TIME) == pdTRUE
				evitement_droit();
				evitement = true;
			}
*/

			if (evitement == 1){  // xSemaphoreTake(stateChangeSemaphore, SEMAPHORE_WAIT_TIME) == pdTRUE
				evitement_droit();
				evitement = 0;
			}
			else if (evitement == 2){
				evitement_gauche();
				evitement = 0;
			}

			go_to(waypoints[waypointIndex].x, waypoints[waypointIndex].y);

			if( (abs(x_position - waypoints[waypointIndex].x)<150) && (abs(y_position - waypoints[waypointIndex].y)<150) ){ // une fois que l'on est proche de la zone on quitte le while 
				
				waypointIndex ++;
				if (waypointIndex >= numPoints) break; // we reached the end of the waypoints 
				Serial.println("Next Waypoint");
			}
			
		}

	Serial.println("sortie du while");
	/*
	Serial.print("arrivé à la zone");
	//vTaskDelay(1000000);
	go_to_1 = false ; // pour désactiver l'evitement. 
	stepperR.setSpeedProfile(stepperR.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL_FINISH);
	stepperL.setSpeedProfile(stepperL.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL_FINISH);
	Serial.println("go_to_2");
	go_to(x_goal_2,y_goal_2);
	*/

	# ifdef SUPERSTAR
	SuperStarTime = true;
	MoveToEdge();
	# endif

	
	myservo.write(180);
	vTaskDelay(10);
	digitalWrite(8, HIGH);

	// prevent the loop from going on
	while (true) {}
	

	/* 
	if (conteur < 2){ 
	straight(1000);
	//go_to(1500,700); // attention durant les rotations du go_to elle l'évitement peut s'activer
	conteur ++;
	}
	*/ 
	}
}

//////////////////////////////////////////////////////////////////////////////

void loop() {
	vTaskDelete(NULL);
	Serial.println("dans le loop");
}



float symetrie(float coordonne) {
	coordonne = 1500 - (coordonne - 1500);
	return coordonne ;
}

int capteur(int sensorPin){
	int16_t d ;
	int16_t t = pulseIn(sensorPin, HIGH);
// Serial.print(" t:");
// Serial.print(t);
// Serial.print("  ");
	if ( t==0)
	{
		Serial.print("Timeout ");
		Serial.println(sensorPin);
		//t = 1;
	}
	else if (t > 1850)
	{
		 //Serial.print("Pas de détection capteur ");// No detection.
	}
	else
	{
		// Valid pulse width reading. Convert pulse width in microseconds to distance in millimeters.
		d = (t - 1000) * 2;
 
		// Limit minimum distance to 0.
		if (d < 0) { d = 0; } 
		//Serial.print(d);
		//Serial.println(" mm");
	}
	return d;
}