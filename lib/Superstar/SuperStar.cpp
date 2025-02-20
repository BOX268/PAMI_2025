# include "Superstar.hh"

void MoveToEdge()
{
    float rpmStore = stepperL.getRPM();
    stepperR.setSpeedProfile(stepperR.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
    stepperL.setSpeedProfile(stepperL.LINEAR_SPEED, MOTOR_ACCEL, MOTOR_DECEL);
    stepperL.setRPM(APPROACH_SPEED);
    stepperR.setRPM(APPROACH_SPEED);
    while (true)
    {
        // make sure avoidance is on
        evitement = 0;
        straight(1000);

        // when reaching this point, either the move is finished or an avoidance happened

        if (evitement == 0)
        {
            Serial.println("no edge detected");
        }
        if (evitement == 1) rotate(-3);
        if (evitement == 2) rotate(3);
        if (evitement == 3) break;
    }

    stop();

    straight(TRANSLATION_DISTANCE_AFTER_EDGE);

    stepperL.setRPM(rpmStore);
    stepperR.setRPM(rpmStore);

    // avoid the motors getting the power cut at the end of the program too soon
    vTaskDelay(5000 / portTICK_PERIOD_MS);
}