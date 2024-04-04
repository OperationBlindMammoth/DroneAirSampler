void grabSample(){
    Serial.println("grabSample()");
    report('grab order received');
    myMotor->setSpeed(255);
    myMotor->run(BACKWARD);    //    RED LEFT     BLACK RIGHT
    datalog("grab sample begin");
    report('Valve open');
    delay(2000);
    myMotor->run(RELEASE);
    datalog("grab sample end");
    report('Valve closed');
}
