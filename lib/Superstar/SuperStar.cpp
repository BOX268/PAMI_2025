# include "Superstar.hh"

void MoveToEdge()
{
    Serial.println("start function MoveToEdge");
    //float rpmStore = stepperL.getRPM();
    stepperR.setSpeedProfile(stepperR.LINEAR_SPEED, APPROACH_ACCEL, APPROACH_DECEL);
    stepperL.setSpeedProfile(stepperL.LINEAR_SPEED, APPROACH_ACCEL, APPROACH_DECEL);
    stepperL.setRPM(APPROACH_SPEED);
    stepperR.setRPM(APPROACH_SPEED);
    while (true)
    {
        Serial.println("boucle approaching edge");
        // make sure avoidance is on
        evitement = 0;
        straight(1000);

        // when reaching this point, either the move is finished or an avoidance happened

        if (evitement == 0)
        {
            Serial.println("no edge detected");
            //finishing_edge();
            break;
        }
        if (evitement == 1) rotate(-3);
        if (evitement == 2) rotate(3);
        if (evitement == 3) break;
    }

    stop();

    straight(TRANSLATION_DISTANCE_AFTER_EDGE);

    //stepperL.setRPM(rpmStore);
    //stepperR.setRPM(rpmStore);

    // avoid the motors getting the power cut at the end of the program too soon
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    Serial.println("end function MoveToEdge");
}

void finishing_edge (){
    Serial.println(" function finishing_edge");
    straight(-10);
    straight(19);
    if (evitement == 1){
        rotate(-2);
        return;
    }
    if (evitement == 2){
        rotate(2);
        return;
    } 

    Serial.println("error finishing edge, no avoidance detected");
    return;

}