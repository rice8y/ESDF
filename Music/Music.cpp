#include "Music.h"
#include <Arduino.h>

note twinkle[] = {
  {nc4, 4},
  {nc4, 4},
  {ng4, 4},
  {ng4, 4},
  {na5, 4},
  {na5, 4},
  {ng4, 2},
  {nf4, 4},
  {nf4, 4},
  {ne4, 4},
  {ne4, 4},
  {nd4, 4},
  {nd4, 4},
  {nc4, 2},
  {ng4, 4},
  {ng4, 4},
  {nf4, 4},
  {nf4, 4},
  {ne4, 4},
  {ne4, 4},
  {nd4, 2},
  {ng4, 4},
  {ng4, 4},
  {nf4, 4},
  {nf4, 4},
  {ne4, 4},
  {ne4, 4},
  {nd4, 2},
  {nc4, 4},
  {nc4, 4},
  {ng4, 4},
  {ng4, 4},
  {na5, 4},
  {na5, 4},
  {ng4, 2},
  {nf4, 4},
  {nf4, 4},
  {ne4, 4},
  {ne4, 4},
  {nd4, 4},
  {nd4, 4},
  {nc4, 2},
  {fine, 1}
};

note alert_1[] = {
  { nc5, 16 },
  { nr, 16 },
  { nc5, 16 },
  { nr, 4 },
  { nc5, 16 },
  { nr, 16 },
  { nc5, 16 },
  { nr, 4 },
  { nc5, 16 },
  { nr, 16 },
  { nc5, 16 },
  { nr, 4 },
  { nc5, 16 },
  { nr, 16 },
  { nc5, 16 },
  { nr, 4 },
  { nc5, 32 },
  { nr, 32 },
  { nc5, 32 },
  { nr, 32 },
  { nc5, 32 },
  { nr, 32 },
  { nc5, 32 },
  { nr, 4 },
  { nc5, 32 },
  { nr, 32 },
  { nc5, 32 },
  { nr, 32 },
  { nc5, 32 },
  { nr, 32 },
  { nc5, 32 },
  { nr, 4 },
  { nc5, 32 },
  { nr, 32 },
  { nc5, 32 },
  { nr, 32 },
  { nc5, 32 },
  { nr, 32 },
  { nc5, 32 },
  { nr, 4 },
  { nc5, 32 },
  { nr, 32 },
  { nc5, 32 },
  { nr, 32 },
  { nc5, 32 },
  { nr, 32 },
  { nc5, 32 },
  { nr, 4 },
  { fine, 1 }
};

note alert_2[] = {
  { nc5, 32 },
  { nr, 32 },
  { fine, 1 }
};

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
}