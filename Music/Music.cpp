#include "Music.h"
#include <Arduino.h>

void playMusic(int PIN, note notes[], int bpm)
{
    int i;
    int beat = 240000 / bpm;
    while (notes[i].frequency != fine)
    {
        double noteDuration = beat / notes[i].duration / 1.30;
        tone(PIN, notes[i].frequency, noteDuration);
        double pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        noTone(PIN);
        i++;
    }
    // int lengthNotes = sizeof(notes) / sizeof(notes[0]);
    // int beat = 240 * 1000 / bpm;
    // for (int i = 0; i < lengthNotes; i++)
    // {
    //     if (notes[i].frequency > 0)
    //     {
    //         double noteDuration = notes[i].duration / beat / 1.30;
    //         tone(PIN, notes[i].frequency, noteDuration);
    //         double pauseBetweenNotes = noteDuration * 1.30;
    //         delay(pauseBetweenNotes);
    //         // noTone(PIN);
    //     }else{
    //         noTone(PIN);
    //         delay(notes[i].duration);
    //     }
    // }
}