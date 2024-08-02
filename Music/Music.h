#ifndef MUSIC_H
#define MUSIC_H

#define nc0s 34.647
#define nd0 36.708
#define nd0s 38.890
#define ne0 41.203
#define nf0 43.653
#define nf0s 46.249
#define ng0 48.999
#define ng0s 51.913
#define na0 55.000
#define na0s 58.270
#define nb0 61.735
#define nc1 65.406

#define nc1s 69.296
#define nd1 73.416
#define nd1s 77.782
#define ne1 82.407
#define nf1 87.307
#define nf1s 92.499
#define ng1 97.999
#define ng1s 103.826
#define na1 110.000
#define na1s 116.541
#define nb1 123.471
#define nc2 130.813

#define nc2s 138.591
#define nd2 146.832
#define nd2s 155.563
#define ne2 164.814
#define nf2 174.614
#define nf2s 184.997
#define ng2 195.998
#define ng2s 207.652
#define na2 220.000
#define na2s 233.082
#define nb2 246.942
#define nc3 261.626

#define nc3s 277.183
#define nd3 293.665
#define nd3s 311.127
#define ne3 329.628
#define nf3 349.228
#define nf3s 369.994
#define ng3 391.995
#define ng3s 415.305
#define na3 440.000
#define na3s 466.164
#define nb3 493.883
#define nc4 523.251

#define nc4s 554.365
#define nd4 587.330
#define nd4s 622.254
#define ne4 659.255
#define nf4 698.456
#define nf4s 739.989
#define ng4 783.991
#define ng4s 830.609
#define na4 880.000
#define na4s 932.328
#define nb4 987.767
#define nc5 1046.502

#define nc5s 1108.731
#define nd5 1174.659
#define nd5s 1244.508
#define ne5 1318.510
#define nf5 1396.913
#define nf5s 1479.978
#define ng5 1567.982
#define ng5s 1661.219
#define na5 1760.000
#define na5s 1864.655
#define nb5 1975.533
#define nc6 2093.005

#define nc6s 2217.461
#define nd6 2349.318
#define nd6s 2489.016
#define ne6 2637.020
#define nf6 2793.826
#define nf6s 2959.955
#define ng6 3135.963
#define ng6s 3322.438
#define na6 3520.000
#define na6s 3729.310
#define nb6 3951.066
#define nc7 4186.009

#define nc7s 4434.922
#define nd7 4698.636
#define nd7s 4978.032
#define ne7 5274.041
#define nf7 5587.652
#define nf7s 5919.911
#define ng7 6271.927
#define ng7s 6644.875
#define na7 7040.000
#define na7s 7458.620
#define nb7 7902.133
#define nc8 8372.018

#define nc8s 8869.844
#define nd8 9397.272
#define nd8s 9956.064
#define ne8 10548.082
#define nf8 11175.304
#define nf8s 11839.822
#define ng8 12543.854
#define ng8s 13289.750
#define na8 14080.000
#define na8s 14917.240
#define nb8 15804.264
#define nc9 16744.036

#define nc9s 17739.688
#define nd9 18794.544
#define nd9s 19912.128
#define ne9 21096.164
#define nf9 22350.608
#define nf9s 23679.644
#define ng9 25087.708
#define ng9s 26579.500
#define na9 28160.000
#define na9s 29834.480
#define nb9 31608.528

#define fine -1.0
#define nr 0.0

struct note
{
    float frequency;
    double duration;
};

void playMusic(int PIN, note notes[], int bpm);
extern note twinkle[];
extern note alert_1[];
extern note alert_2[];

#endif