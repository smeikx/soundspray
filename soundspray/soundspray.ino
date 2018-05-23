using Pin = unsigned int;
using Milliseconds = unsigned long;

const Pin tilt_sensor {8}, release_button {7};
bool last_state;
int count {0}; 
const unsigned int decrease_rate {5}; // per second

void setup()
{
	Serial.begin(9600);
	pinMode(tilt_sensor, INPUT);
	pinMode(release_button, INPUT);
	last_state = digitalRead(tilt_sensor);
}

void loop()
{
	if (digitalRead(release_button))
		count = 0;

	bool state {digitalRead(tilt_sensor)};
	if (state != last_state)
	{
		count++;
		last_state = state;
		Serial.println(count);
	}

	count -= delta_time() / 1000.0f * decrease_rate;
	count = max(count, 0);

	Serial.write(count);
	delay(10);
}

// misst vergangene Zeit seit letztem Aufruf
Milliseconds delta_time()
{
	static Milliseconds last_time_stamp {millis()};
	Milliseconds delta {millis() - last_time_stamp};
	last_time_stamp = millis();
	return delta;
}

