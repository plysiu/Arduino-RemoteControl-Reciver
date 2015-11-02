// Do not remove the include below
#include "RemoteControlReciver.h"
#include "StandardCplusplus.h"
#include <RemoteControl.h>
#include <VirtualWire.h>
#include <vector>

const int led_pin = 13;
const int transmit_pin = 12;
const int receive_pin = 10;
const int transmit_en_pin = 3;

void setup() {
	Serial.begin(9600);

	vw_set_tx_pin(transmit_pin);
	vw_set_rx_pin(receive_pin);
	vw_set_ptt_pin(transmit_en_pin);
	vw_set_ptt_inverted(true);
	vw_setup(12000);
	vw_rx_start();

	pinMode(led_pin, OUTPUT);
}
std::vector<RemoteControl::Token> recive() {
	std::vector<RemoteControl::Token> tokens;
	uint8_t buf[VW_MAX_MESSAGE_LEN];
	uint8_t buflen = VW_MAX_MESSAGE_LEN;

	if (vw_get_message(buf, &buflen)) {
		digitalWrite(led_pin, HIGH);
		RemoteControl::Tokenizer tokenizer((char*) buf);
		for (RemoteControl::Token token = tokenizer.next();
				token.type != RemoteControl::TokenType::End;
				token = tokenizer.next()) {
			tokens.insert(tokens.begin(), token);
		}
	}
	digitalWrite(led_pin, LOW);
	return tokens;
}
std::vector<RemoteControl::Signal> signals;
void loop() {
	signals = RemoteControl::transformTokensToSignal(recive());
	if (signals.size() > 0) {
		for (unsigned int i = 0; i < signals.size(); i++) {

			switch (signals[i].id) {
			case 0:
				Serial.print("Signal: ");
				Serial.print(signals[i].id);
				Serial.print(" Value: ");
				Serial.println(signals[i].value);
				break;
			case 1:
				Serial.print("Signal: ");
				Serial.print(signals[i].id);
				Serial.print(" Value: ");
				Serial.println(signals[i].value);
				break;
			case 2:
				Serial.print("Signal: ");
				Serial.print(signals[i].id);
				Serial.print(" Value: ");
				Serial.println(signals[i].value);
				break;
			case 3:
				Serial.print("Signal: ");
				Serial.print(signals[i].id);
				Serial.print(" Value: ");
				Serial.println(signals[i].value);
				break;

//			case 4:
//				Serial.print("Signal: ");
//				Serial.print(signals[i].id);
//				Serial.print(" Value: ");
//				Serial.println(signals[i].value);
//				break;
//
//			case 5:
//				Serial.print("Signal: ");
//				Serial.print(signals[i].id);
//				Serial.print(" Value: ");
//				Serial.println(signals[i].value);
//				break;
			}
		}
	}
}
