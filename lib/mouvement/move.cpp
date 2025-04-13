#include "move.h"


long int total_Steps_R = 0;
long int total_Steps_L = 0;

float x_position = X_POSITION_START;
float y_position = Y_POSITION_START;
float teta_actuelle = TETA_POSITION_START;

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

void straight(float distance_){  // positive and negatif value allowed
  Serial.println("debut du straight");
  //stepperR.setRPM(TRANSLATION_RPM);
  //stepperL.setRPM(TRANSLATION_RPM);
  float mm = (MOTOR_STEPS * MICROSTEPS * COEF_STRAIGHT) / 195 ;// 200*MICROSTEPS = périmètre de la roue (diamètre = 62)* M_PI = 195 mm
  float distance = distance_ * mm  ;
  Serial.print("distance à parcourir:");
  Serial.print(distance_);
  Serial.print(" nombre de step à parcourir:");
  Serial.println(distance);
  controller.move(distance, distance);
  position();
  Serial.println("end function straight");
}

void rotate (float angle){
  Serial.println("start fonction rotate");
  int sauvegarde_evitement;
  sauvegarde_evitement = evitement ;
  evitement = -1;

  stepperR.setSpeedProfile(stepperR.LINEAR_SPEED, MOTOR_ACCEL_DECEL_ROTATE, MOTOR_ACCEL_DECEL_ROTATE);
  stepperL.setSpeedProfile(stepperL.LINEAR_SPEED, MOTOR_ACCEL_DECEL_ROTATE, MOTOR_ACCEL_DECEL_ROTATE);

  float angl= angle * COEF_ROTATE / 360 ; // pourquoi diviser pas 360 ?
  Serial.print(" rotation_of ...:");
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

  stepperR.setSpeedProfile(stepperR.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
  stepperL.setSpeedProfile(stepperL.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);

  evitement = sauvegarde_evitement ;
  Serial.println("end fonction rotate");
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
  Serial.print("start fonction go_to, go_x:");
  Serial.print(go_x);
  Serial.print(" go_y:");
  Serial.println(go_y);
  float teta_to_do = 0;
  float teta_objectif = 0;
  float to_do_x = go_x - x_position;
  float to_do_y = -(go_y - y_position); // on rajoute un moins pour que l'axe y soit inverser. l'axe y sur le vinil de surdiabotique est inverser par rapport au cercle trigo. 
  Serial.print(" to do_y:");
  Serial.print(to_do_y);
  Serial.print(" to do_x:");
  Serial.print(to_do_x);

  float distance = sqrt(to_do_x*to_do_x + to_do_y*to_do_y );
  //float teta_calcule = atan(abs(to_do_y) / abs(to_do_x));
  float teta_calcule = atan2(to_do_y, to_do_x);
  float teta_objectif_ = (teta_calcule * 180 / M_PI);
  teta_objectif = - teta_objectif_ ; // on rajoute le - pour avoir le sens de rotation positive -->clockwise. 
  Serial.print(" teta_objectif:");
  Serial.print(teta_objectif);

  teta_to_do = teta_objectif - teta_actuelle;

  if(teta_to_do >= 180){
    teta_to_do = teta_objectif - teta_actuelle - 360;
    //Serial.print(" teta_goal > 180");
  } 

  if (teta_to_do < -180){
    teta_to_do = teta_objectif - teta_actuelle + 360;
  }
  Serial.print(" teta_to_do:");
  Serial.print(teta_to_do);
  rotate(teta_to_do );
  //evitement = 0;
  //Serial.print("evitement: ");
  //Serial.print(evitement);
  //Serial.print(" valeur distance:");
  //Serial.println(distance);
  straight(distance);
  Serial.println("end fonction go_to");
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
  Serial.println("start evitement droit");
  rotate(70);
  straight(150);
  Serial.println("end evitement droit ");
}

void evitement_gauche(){
  Serial.println("start evitement gauche");
  rotate(-70);
  straight(150);
  Serial.println("end evitement gauche ");
}

void position(){
  Serial.println("start fonction position");
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
  Serial.print(" distance parcouru:");
  Serial.print(distance);
  
  distance_x = distance * cos(teta_actuelle * M_PI / 180.0f); // M_PI / 180.0f pour la convertion en radian
  distance_y = distance * sin(teta_actuelle * M_PI / 180.0f); // il y a un signe moins au debut car on conconsidère le cercle trigonométrique avec le 0 vers la cuisine, l'axe des x est correcte, mais l'axe des y est inversé par rapport au cercle trigo. 

  Serial.print(" distance_x_ajouter:");
  Serial.print(distance_x);
  Serial.print(" distance_y_ajouter:");
  Serial.print(distance_y);

  x_position += distance_x;
  y_position += distance_y;

  Serial.print(" new position x:");
  Serial.print(x_position);
  Serial.print(" new position y:");
  Serial.println(y_position);
  Serial.println("end fonction position");
}


void SetRPM(int rpm)
{
  stepperL.setRPM(rpm);
  stepperR.setRPM(rpm);
}

void Set_Decelerate(int decel){
  stepperR.setSpeedProfile(stepperR.LINEAR_SPEED, MOTOR_ACCEL, decel);
  stepperL.setSpeedProfile(stepperL.LINEAR_SPEED, MOTOR_ACCEL, decel);
}
