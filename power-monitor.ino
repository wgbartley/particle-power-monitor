#define POWER_MONITOR_PIN D7

// Global variable to monitor changes in power status
bool powerIsOn = true;


void setup() {
    // Set our power monitor pin to INPUT
    pinMode(POWER_MONITOR_PIN, INPUT);
}


void loop() {
    // Read the state of the power monitor pin
    bool power_state = digitalRead(POWER_MONITOR_PIN);

    // If the power is off but our global variable says it's on, publish an alert
    if(power_state==0 && powerIsOn) {
        // Turn the onboard RGB LED to red
        RGB.control(true);
        RGB.color(255, 0, 0);

        // Publish alert
        Particle.publish("power-monitor", "off");

        // Set our global variable to off
        powerIsOn = false;

    // If the power is on but our global variable says it's off, publish an alert
    } else if(power_state==1 && !powerIsOn) {
        // Return the onboard RGB LED to normal status
        RGB.control(false);

        // Publish alert
        Particle.publish("power-monitor", "on");

        // Set our global variable to on
        powerIsOn = true;
    }
}