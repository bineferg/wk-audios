#include "midi_message.h"
#include <iostream>

midi_message::midi_message(long message) {
	std::cout<<message<<std::endl;
	channel = message & 0x0f; 
	note_on = (message >> 4) & 0x01; 
	note = (message >> 8) & 0xff; 
	velocity = (message >> 16) & 0xff; 
	
	std::cout<<"Channel: "<<channel+1<<" | Note on: "<<note_on<<" | Note: "<<static_cast<unsigned>(note)<<" | Velocity: "<<static_cast<unsigned>(velocity)<<std::endl;
}

bool midi_message::get_note_on() {
	return note_on;
}

uint8_t midi_message::get_note() {
	return note;
}

uint8_t midi_message::get_velocity() {
	return velocity;
}
