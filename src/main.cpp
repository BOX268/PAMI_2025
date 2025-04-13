#include "move.h"
#include "config_robots.hh"
#include "Superstar.hh"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>  
#include "ESP32Servo.h"

uint waypointIndex = 0;

volatile unsigned long Time1; // Variable pour stocker le temps de départ
volatile bool SuperStarTime = false; // Variable pour indiquer si la superstar est active
unsigned long elapsedTime;

int capteur(int sensorPin); 
float symetrie(float coordonne);
//volatile int8_t evitement = 0 ;

Servo myservo;

TaskHandle_t Task1;
TaskHandle_t Task2;
void Task1code(void *pvParameters);
void Task2code(void *pvParameters);

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
	delay(2000); 

	//create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
	xTaskCreatePinnedToCore(
										Task2code,   /* Task function. */
										"Task2",     /* name of task. */
										10000,       /* Stack size of task */
										NULL,        /* parameter of the task */
										1,           /* priority of the task */
										&Task2,      /* Task handle to keep track of created task */
										1);          /* pin task to core 1 */
	delay(500); 
	myservo.setPeriodHertz(50);    // standard 50 hz servo
	myservo.attach(servoPin, 500, 10000);
	myservo.write(0);
	pinMode(ENABLE, OUTPUT);
	digitalWrite(ENABLE, LOW); // pour que le enable des  drive soit à low. 
	pinMode(tirette, INPUT_PULLUP);
	pinMode(bouton_equipe, INPUT_PULLUP);
	Serial.println("setup done");
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
	vTaskDelay(3000);

	myservo.write(0);
	while (!(digitalRead(tirette))){
		vTaskDelay(20);
		Serial.println("wait la tirette task 1");
	}
	myservo.write(0); // to be REALLY redundant

	for(;;){

		static int depart = 1;
		if (depart == 1){
			depart ++;
			Serial.print("debut du compte à rebourt");
			Time1 = millis();
		}
		
		elapsedTime = millis() - Time1;

		if ((elapsedTime >100000)){
			stop();
			vTaskDelay(10);
			digitalWrite(ENABLE, HIGH);
			Serial.print("FIN du temps des 100sec ");
			while(1){
				static unsigned long elapsedTime2 = 0;
				elapsedTime2 = millis() - Time1;
				if((elapsedTime2 < 150000) && (elapsedTime2 >100000)){
					vTaskDelay(1000);
					myservo.write(0);
					vTaskDelay(1000);
					myservo.write(180);
					Serial.print("pami dance ");
					Serial.print("elapsedTime2:");
					Serial.println(elapsedTime2);
				}
				else if (elapsedTime2 > 150000){ 
					Serial.println("FIN du programme core 1 / fin du match depuis longtemps ");
					vTaskDelay(2000);
				}
			}
		}
		#ifdef EVITEMENT
		int sensor_M = capteur(sensorPinMidel);
		int sensor_L = capteur(sensorPinLeft);
		int sensor_R = capteur(sensorPinRight);
		#endif

		# ifdef PRINT_DISTANCES
	//Serial.print(" evitement:");
	//Serial.print(evitement);
		Serial.print("elapsedTime:");
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
		//Serial.print(" stepperR:");
		//Serial.print(stepperR.getStepsCompleted());
		//Serial.print(" total_Steps_R:");
		//Serial.print(total_Steps_R); 
		Serial.print(" position x:");
		Serial.print(x_position);
		Serial.print(" position y:");
		Serial.print(y_position);
		Serial.print(" evitement:");
		Serial.println(evitement);
		# endif
		
		#if defined(PAMI_1) && defined(EVITEMENT)
		if (!(SuperStarTime)) AvoidanceChecksSuperstar(sensor_M, sensor_L, sensor_R); // maybe this fonction will need to be remove due to the hill
		if (SuperStarTime) FloorCheckSuperstar(sensor_M, sensor_L, sensor_R);
		// The superstar tries to avoid the slope if this is uncommented
		//else AvoidanceChecksSuperstar(sensor_M, sensor_L, sensor_R);
		# endif
		#if (!defined(PAMI_1)) && defined(EVITEMENT)
		AvoidanceChecksNormal(sensor_M, sensor_L, sensor_R);
		# endif
				
	vTaskDelay(1/portTICK_PERIOD_MS);
	}
}

void Task2code( void * pvParameters ){
	vTaskDelay(3000);

	while (!(digitalRead(tirette))){
		vTaskDelay(20);
		Serial.println("wait la tirette task 2");
	} 
		
	 //vTaskDelay(200);
	if (!digitalRead(bouton_equipe)){

		for (int i = 0; i < numPoints; i++)
		{
			waypoints[i].x = symetrie(waypoints[i].x);
			// la symetrie est à revoir 
		}

		equipe = 'J';
	} 
	Serial.print("equipe_couleur :");
	Serial.println(equipe);
	Serial.println("wait start...");
	vTaskDelay(GLOBAL_WAIT); 

	while (true)
		{
		Serial.println("start boucle while core 2");

		if (evitement == 1){  
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
			Serial.print("Next Waypoint, x:");
			Serial.print(waypoints[waypointIndex].x);
			Serial.print(" y:");
			Serial.println(waypoints[waypointIndex].y);
		}
			
	}

	Serial.println("sortie du while core 2");

	#if defined(PAMI_1) && defined(EVITEMENT)
	SuperStarTime = true;
	MoveToEdge();
	#endif

	vTaskDelay(10);
	digitalWrite(ENABLE, HIGH);

	// prevent the loop from going on
	while (true) {
		Serial.println("FIN du programme du core 2");
		vTaskDelay(2000);
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
