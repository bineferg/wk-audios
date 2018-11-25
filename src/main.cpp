#include <iostream>
#include <portaudio.h>
#include "midi_manager.h"
#include "wave_generator.h"
#include "audio_manager.h"

int arr[] = {440, 293, 329, 349, 392};

int main(void) {
    int i, type;
    std::cout<<"Wave Type:"<<std::endl;
    std::string str = "";
    for (i=0; i<5; i++) {
        switch(i) {
            case 0:
                str = "sine";
                break;
            case 1:
                str = "square";
                break;
            case 2:
                str = "saw";
                break;
            case 3:
                str = "triangle";
                break;
            case 4:
                str = "white noise";
                break;
            default:
                break;
        }
        std::cout << "[" << (i+1) << "] " << str << std::endl;
    }
    std::cin >> type;

    wave_generator::wave_type wtype = (wave_generator::wave_type)type;
    wave_generator* wgen = new wave_generator();
    wave* w = new wave(SAMPLE_RATE);
    wgen->generate_wave(w, wtype, SAMPLE_RATE);
    wgen->print_wave(w, SAMPLE_RATE, 256);
    audio_manager* audiom = new audio_manager();
    midi_manager* midim = new midi_manager(w, audiom);

    int count = midim->get_count(), deviceId;

    float freq{0};
    float delta{0.0001};
    bool up{true};
    while (true)
    {
        if (freq > 1000)
        {
            up = false;
        }
        if (freq < 0)
        {
            up = true;
        }
        if (up)
        {
            freq += delta;
        } else
        {
            freq -= delta;
        }
        w->set_freq(freq);
    }

    std::cout<<count<<std::endl;
    std::cout<<"Select a midi input:"<<std::endl;
    do {
        for (i=0; i<count; i++) {
            std::cout<<"["<<i<<"] "<<midim->get_device_name(i)<<std::endl;
        }
        std::cout<<"> ";
        std::cin>>deviceId;
    } while(deviceId < 0 || deviceId > count);

    midim->set_device(deviceId);
    midim->start_read();
}
