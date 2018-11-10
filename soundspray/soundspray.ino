using Pin = unsigned int;
using Milliseconds = unsigned long;

const Pin tilt_sensor {8}, release_button {7};
bool last_shake_state, release_button_previously_pressed;

enum MESSAGE
{
	CHARGE_UP,
	RELEASE_START,
	RELEASE_STOP
};

void setup()
{
	Serial.begin(9600);
	pinMode(tilt_sensor, INPUT);
	pinMode(release_button, INPUT);
	last_shake_state = digitalRead(tilt_sensor);
	release_button_previously_pressed = digitalRead(release_button);
}

void loop()
{
	bool release_button_currently_pressed {digitalRead(release_button)};
	if (release_button_currently_pressed != release_button_previously_pressed)
	{
		Serial.write(release_button_currently_pressed ? RELEASE_START : RELEASE_STOP);
		release_button_previously_pressed = release_button_currently_pressed;
	}

	bool state {digitalRead(tilt_sensor)};
	if (state != last_shake_state)
	{
		last_shake_state = state;
		Serial.write(CHARGE_UP);
	}
}

// misst vergangene Zeit seit letztem Aufruf
Milliseconds delta_time()
{
	static Milliseconds last_time_stamp {millis()};
	Milliseconds delta {millis() - last_time_stamp};
	last_time_stamp = millis();
	return delta;
}

