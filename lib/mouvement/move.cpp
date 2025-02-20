#include "move.h"



long int total_Steps_R = 0;
long int total_Steps_L = 0;


//float x_position= 1355 ; // 1= 1452 2=1355 3=1260 4=1170

# ifdef PAMI_1
float x_position = 0;
float teta_actuelle = 0;
# endif
# ifdef PAMI_2
float x_position = 1355;
float teta_actuelle = 0;
# endif
# ifdef PAMI_3
float x_position = 1260;
float teta_actuelle = 0;
# endif
# ifdef PAMI_4
float x_position = 100;
float teta_actuelle = 0;
# endif

float y_position= 0;

int evitement = 0 ;

//float x_goal_position= 1850;
//float y_goal_position= 650;

BasicStepperDriver stepperR(MOTOR_STEPS, DIR_X, STEP_X);
BasicStepperDriver stepperL(MOTOR_STEPS, DIR_Y, STEP_Y);
SyncDriver controller(stepperR, stepperL);

void configureMotors(){ 
stepperR.begin(MOTOR_RPM, MICROSTEPS);
stepperL.begin(MOTOR_RPM, MICROSTEPS);
stepperR.setSpeedProfile(stepperR.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
stepperL.setSpeedProfile(stepperL.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
}

void straight(float distance_){
  Serial.print("debut du straight");
  if(distance_ < 1) { 
  Serial.print("erreur distance < 0");
  return ;
  }
  //stepperR.setRPM(TRANSLATION_RPM);
  //stepperL.setRPM(TRANSLATION_RPM);
  float mm = (MOTOR_STEPS * MICROSTEPS * COEF_STRAIGHT) / 195 ;// 200*MICROSTEPS = périmètre de la roue (diamètre = 62)* M_PI = 195 mm
  float distance = distance_ * mm  ;
  Serial.print("distance à parcourir:");
  Serial.print(distance_);
  Serial.print(" nombre de step à parcourir:");
  Serial.print(distance);
  controller.move(distance, distance);
  position();
  Serial.println("la fin du straight");
}

void rotate (float angle){
  int sauvegarde_evitement;
  sauvegarde_evitement = evitement ;
  evitement = -1;

  //stepperR.setRPM(ROTATION_RPM);
  //stepperL.setRPM(ROTATION_RPM);

  stepperR.setSpeedProfile(stepperR.LINEAR_SPEED, MOTOR_ACCEL_DECEL_ROTATE, MOTOR_ACCEL_DECEL_ROTATE);
  stepperL.setSpeedProfile(stepperL.LINEAR_SPEED, MOTOR_ACCEL_DECEL_ROTATE, MOTOR_ACCEL_DECEL_ROTATE);

  Serial.print("debut du rotate");
  float angl= angle * COEF_ROTATE / 360 ;
  Serial.print(" angle:");
  Serial.println(angle);
  controller.rotate(angl, -angl);
  teta_actuelle += angle;

  if (teta_actuelle >= 360.0f) {
    teta_actuelle -= 360.0f;
  } else if (teta_actuelle < 0.0f) {
    teta_actuelle += 360.0f;
  }
  Serial.print(" nouvelle orientation");
  Serial.println(teta_actuelle);
  Serial.println("fin du rotate");

  stepperR.setSpeedProfile(stepperR.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
  stepperL.setSpeedProfile(stepperL.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);

  evitement = sauvegarde_evitement ;
}

void stop(){
  stepperR.stop(); stepperL.stop();
}

bool moving(){ 
  if (controller.isRunning() == true){
    return true ;
  } else{
    return false ;
  }
}

void go_to(float go_x, float go_y){
  Serial.println("debut du go_to");
  float teta_goal = 0;
  float teta_objectif = 0;
  float to_do_x = go_x - x_position;
  float to_do_y = go_y - y_position;
  Serial.print("to do_y:");
  Serial.print(to_do_y);
  Serial.print("  to do_x: ");
  Serial.print(to_do_x);

  float distance = sqrt(to_do_x*to_do_x + to_do_y*to_do_y );
  //float teta_calcule = atan(abs(to_do_y) / abs(to_do_x));
  float teta_calcule = atan2(to_do_x, to_do_y);
  teta_objectif = (teta_calcule * 180 / M_PI);



  Serial.print(" teta_objectif : ");
  Serial.println(teta_objectif);

  teta_goal = teta_objectif - teta_actuelle;

  if(teta_goal >= 180){
    teta_goal = teta_objectif - teta_actuelle - 360;
    //Serial.print(" teta_goal > 180");
  } 

  if (teta_goal < -180){
    teta_goal = teta_objectif - teta_actuelle + 360;
  }
  Serial.print("teta_goal : ");
  Serial.print(teta_goal);
  rotate(teta_goal );
  //evitement = 0;
  //Serial.print("evitement: ");
  //Serial.print(evitement);
  //Serial.print(" valeur distance:");
  //Serial.println(distance);
  straight(distance);
  Serial.println("fin du go_to");
  return;
}

void debug_position(){
  Serial.print("stepperR.getStepsCompleted() ");
  Serial.print(stepperR.getStepsCompleted());
/* 
  total_Steps_R += stepperR.getStepsCompleted();
  total_Steps_L += stepperL.getStepsCompleted();
  Serial.print("total_Steps_R : ");
  Serial.print(total_Steps_R);
  Serial.print(" total_Steps_L : ");
  Serial.println(total_Steps_L);*/
}

void evitement_droit(){
  Serial.print("evitement droit");
  rotate(70);
  straight(150);
  Serial.print("fin evitement droit ");
}

void evitement_gauche(){
  Serial.print("evitement gauche");
  rotate(-70);
  straight(150);
  Serial.print("fin evitement gauche ");
}

void position(){
  Serial.println("debut de la fonction position");
  int current_StepsR = stepperR.getStepsCompleted();
  int current_StepsL = stepperL.getStepsCompleted();
  total_Steps_R += current_StepsR ;
  total_Steps_L += current_StepsL ;
  float distance_x ;
  float distance_y ; 
 
  //  il faut verifier que les rotation n'ont pas d'influence car on utilise que la variable "current_StepsR"
  float distance = current_StepsR / ((MOTOR_STEPS * MICROSTEPS * COEF_STRAIGHT) / 195); // mm
  //Serial.print("current_StepsR");
  //Serial.println(current_StepsR);
  Serial.print(" distance parcouru : ");
  Serial.print(distance);
// le changement du teta s'actualise dans la fonction rotate. 

  //float displacement_x = distance_traveled * cos(teta_actuelle * M_PI / 180.0f); // M_PI / 180.0f pour la convertion en radian
  //float displacement_y = distance_traveled * sin(teta_actuelle * M_PI / 180.0f);

  /*
  float teta_actuelle_ = fmod(teta_actuelle, 90.0f);
  Serial.print("fmod(teta_actuelle, 90.0f) : ");
  Serial.print(teta_actuelle_); */

  

  distance_y = distance * cos(teta_actuelle * M_PI / 180.0f); // M_PI / 180.0f pour la convertion en radian
  distance_x = distance * sin(teta_actuelle * M_PI / 180.0f);

  Serial.print(" distance_x_ajouter : ");
  Serial.print(distance_x);
  Serial.print(" distance_y_ajouter : ");
  Serial.print(distance_y);

  x_position += distance_x;
  y_position += distance_y;

  Serial.print(" nouvelle position x ");
  Serial.print(x_position);
  Serial.print(" nouvelle position y ");
  Serial.println(y_position);
  Serial.println("fin du calcule de position");
}


void SetRPM(int rpm)
{
  stepperL.setRPM(rpm);
  stepperR.setRPM(rpm);
}