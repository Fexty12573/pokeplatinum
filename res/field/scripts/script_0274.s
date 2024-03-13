    .include "macros/scrcmd.inc"

    .data

    .long _00B6-.-4
    .long _0126-.-4
    .long _0365-.-4
    .long _0140-.-4
    .long _0365-.-4
    .long _1084-.-4
    .long _07F2-.-4
    .long _0800-.-4
    .long _08D8-.-4
    .long _08EB-.-4
    .long _090A-.-4
    .long _091D-.-4
    .long _0930-.-4
    .long _0943-.-4
    .long _0962-.-4
    .long _0975-.-4
    .long _10AA-.-4
    .long _118B-.-4
    .long _1199-.-4
    .long _11A7-.-4
    .long _11B5-.-4
    .long _11C3-.-4
    .long _11D1-.-4
    .long _11DF-.-4
    .long _11ED-.-4
    .long _11FB-.-4
    .long _1209-.-4
    .long _1217-.-4
    .long _1225-.-4
    .long _1233-.-4
    .long _1241-.-4
    .long _124F-.-4
    .long _125D-.-4
    .long _126B-.-4
    .long _1279-.-4
    .long _1287-.-4
    .long _1295-.-4
    .long _12A3-.-4
    .long _12B1-.-4
    .long _12BF-.-4
    .long _12CD-.-4
    .long _12DB-.-4
    .long _12E9-.-4
    .long _12F7-.-4
    .long _174A-.-4
    .short 0xFD13

_00B6:
    ScrCmd_01E 0x9CC
    ScrCmd_01E 0x2A1
    ScrCmd_2DF 0x40AB
    ScrCmd_1B7 0x4002, 5
    ScrCmd_011 0x4002, 0
    ScrCmd_01C 1, _00FE
    ScrCmd_011 0x4002, 1
    ScrCmd_01C 1, _0108
    ScrCmd_011 0x4002, 2
    ScrCmd_01C 1, _0112
    ScrCmd_011 0x4002, 3
    ScrCmd_01C 1, _011C
    ScrCmd_002

_00FE:
    ScrCmd_186 15, 28, 14
    ScrCmd_002

_0108:
    ScrCmd_186 15, 38, 8
    ScrCmd_002

_0112:
    ScrCmd_186 15, 40, 21
    ScrCmd_002

_011C:
    ScrCmd_186 15, 48, 41
    ScrCmd_002

_0126:
    ScrCmd_060
    ScrCmd_028 0x8001, 1
    ScrCmd_05E 0xFF, _03B0
    ScrCmd_05F
    ScrCmd_016 _015A
    ScrCmd_002

_0140:
    ScrCmd_060
    ScrCmd_028 0x8001, 2
    ScrCmd_05E 0xFF, _03B8
    ScrCmd_05F
    ScrCmd_016 _015A
    ScrCmd_002

_015A:
    ScrCmd_22D 2, 0x800C
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _0195
    ScrCmd_016 _0174
    ScrCmd_002

_0174:
    ScrCmd_028 0x4000, 0
    ScrCmd_016 _0994
    ScrCmd_002

_0182:
    ScrCmd_02C 0
    ScrCmd_034
    ScrCmd_05E 0xFF, _03C0
    ScrCmd_05F
    ScrCmd_061
    ScrCmd_002

_0195:
    ScrCmd_028 0x4000, 1
    ScrCmd_016 _0ACC
    ScrCmd_002

_01A3:
    ScrCmd_02C 1
    ScrCmd_034
    ScrCmd_05E 0xFF, _03C0
    ScrCmd_05F
    ScrCmd_061
    ScrCmd_002

_01B6:
    ScrCmd_028 0x400A, 0
    ScrCmd_177 0x400B
    ScrCmd_028 0x400C, 0
    ScrCmd_016 _01CE
    ScrCmd_002

_01CE:
    ScrCmd_198 0x400A, 0x800C
    ScrCmd_011 0x800C, 0
    ScrCmd_01C 1, _026D
    ScrCmd_011 0x4000, 0
    ScrCmd_01D 1, _0C50
    ScrCmd_011 0x4000, 1
    ScrCmd_01D 1, _0D36
    ScrCmd_011 0x800C, 0
    ScrCmd_01C 1, _026D
    ScrCmd_0D6 0, 0x400A
    ScrCmd_011 0x400C, 0
    ScrCmd_01C 1, _0229
    ScrCmd_011 0x400C, 0
    ScrCmd_01C 5, _024B
    ScrCmd_002

_0229:
    ScrCmd_026 0x400C, 1
    ScrCmd_02C 2
    ScrCmd_03E 0x800C
    ScrCmd_011 0x800C, 0
    ScrCmd_01C 1, _0299
    ScrCmd_016 _026D
    ScrCmd_002

_024B:
    ScrCmd_026 0x400C, 1
    ScrCmd_02C 4
    ScrCmd_03E 0x800C
    ScrCmd_011 0x800C, 0
    ScrCmd_01C 1, _0299
    ScrCmd_016 _026D
    ScrCmd_002

_026D:
    ScrCmd_026 0x400A, 1
    ScrCmd_027 0x400B, 1
    ScrCmd_011 0x400B, 0
    ScrCmd_01C 5, _01CE
    ScrCmd_02C 5
    ScrCmd_034
    ScrCmd_05E 0xFF, _03C0
    ScrCmd_05F
    ScrCmd_061
    ScrCmd_002

_0299:
    ScrCmd_14E
    ScrCmd_0BC 6, 1, 0, 0
    ScrCmd_0BD
    ScrCmd_029 0x409D, 0x400A
    ScrCmd_198 0x400A, 0x409A
    ScrCmd_016 _0E48
    ScrCmd_002

_02BB:
    ScrCmd_0BC 6, 1, 1, 0
    ScrCmd_0BD
    ScrCmd_002

_02C9:
    ScrCmd_064 0x8002
    ScrCmd_011 0x8001, 1
    ScrCmd_01D 1, _032A
    ScrCmd_011 0x8001, 2
    ScrCmd_01D 1, _0338
    ScrCmd_0BC 6, 1, 1, 0
    ScrCmd_0BD
    ScrCmd_028 0x4099, 1
    ScrCmd_215
    ScrCmd_01A _03DC
    ScrCmd_27C 0, 0x409D
    ScrCmd_02C 3
    ScrCmd_034
    ScrCmd_05E 0xFF, _03C8
    ScrCmd_05E 0x8002, _03C8
    ScrCmd_05F
    ScrCmd_161
    ScrCmd_06D 0x8002, 48
    ScrCmd_061
    ScrCmd_002

_032A:
    ScrCmd_187 0x8002, 12, 2, 47, 2
    ScrCmd_01B

_0338:
    ScrCmd_187 0x8002, 51, 2, 47, 3
    ScrCmd_01B

    .byte 188
    .byte 0
    .byte 6
    .byte 0
    .byte 1
    .byte 0
    .byte 1
    .byte 0
    .byte 0
    .byte 0
    .byte 189
    .byte 0
    .byte 44
    .byte 0
    .byte 5
    .byte 52
    .byte 0
    .byte 94
    .byte 0
    .byte 0xFF
    .byte 0
    .byte 97
    .byte 0
    .byte 0
    .byte 0
    .byte 95
    .byte 0
    .byte 97
    .byte 0
    .byte 2
    .byte 0

_0365:
    ScrCmd_060
    ScrCmd_0BC 6, 1, 0, 0
    ScrCmd_0BD
    ScrCmd_162
    ScrCmd_016 _037D
    ScrCmd_002

_037D:
    ScrCmd_065 5
    ScrCmd_016 _0389
    ScrCmd_002

_0389:
    ScrCmd_0BC 6, 1, 1, 0
    ScrCmd_0BD
    ScrCmd_028 0x4099, 0
    ScrCmd_02C 6
    ScrCmd_034
    ScrCmd_05E 0xFF, _03C0
    ScrCmd_05F
    ScrCmd_061
    ScrCmd_002

    .balign 4, 0
_03B0:
    .short 34, 1
    .short 0xFE, 0x00

    .balign 4, 0
_03B8:
    .short 35, 1
    .short 0xFE, 0x00

    .balign 4, 0
_03C0:
    .short 13, 1
    .short 0xFE, 0x00

    .balign 4, 0
_03C8:
    .short 12, 1
    .short 0xFE, 0x00

    .byte 85
    .byte 0
    .byte 2
    .byte 0
    .byte 2
    .byte 0
    .byte 1
    .byte 0
    .byte 254
    .byte 0
    .byte 0
    .byte 0

_03DC:
    ScrCmd_1B7 0x800C, 5
    ScrCmd_011 0x800C, 0
    ScrCmd_01D 1, _040A
    ScrCmd_011 0x800C, 0
    ScrCmd_01D 5, _0412
    ScrCmd_217 0x409C, 0x409A
    ScrCmd_016 _041A
    ScrCmd_002

_040A:
    ScrCmd_028 0x409B, 0
    ScrCmd_01B

_0412:
    ScrCmd_028 0x409B, 1
    ScrCmd_01B

_041A:
    ScrCmd_1B7 0x800C, 100
    ScrCmd_011 0x800C, 20
    ScrCmd_01C 0, _0490
    ScrCmd_011 0x800C, 35
    ScrCmd_01C 0, _0498
    ScrCmd_011 0x800C, 50
    ScrCmd_01C 0, _04A0
    ScrCmd_011 0x800C, 65
    ScrCmd_01C 0, _04A8
    ScrCmd_011 0x800C, 72
    ScrCmd_01C 0, _04B0
    ScrCmd_011 0x800C, 79
    ScrCmd_01C 0, _04B8
    ScrCmd_011 0x800C, 86
    ScrCmd_01C 0, _04C0
    ScrCmd_011 0x800C, 93
    ScrCmd_01C 0, _04C8
    ScrCmd_016 _04D0
    ScrCmd_002

_0490:
    ScrCmd_028 0x409F, 176
    ScrCmd_01B

_0498:
    ScrCmd_028 0x409F, 175
    ScrCmd_01B

_04A0:
    ScrCmd_028 0x409F, 177
    ScrCmd_01B

_04A8:
    ScrCmd_028 0x409F, 178
    ScrCmd_01B

_04B0:
    ScrCmd_028 0x409F, 179
    ScrCmd_01B

_04B8:
    ScrCmd_028 0x409F, 180
    ScrCmd_01B

_04C0:
    ScrCmd_028 0x409F, 181
    ScrCmd_01B

_04C8:
    ScrCmd_028 0x409F, 182
    ScrCmd_01B

_04D0:
    ScrCmd_028 0x409F, 183
    ScrCmd_01B

_04D8:
    ScrCmd_029 0x8000, 0x409B
    ScrCmd_215
    ScrCmd_01A _03DC
    ScrCmd_011 0x8000, 0
    ScrCmd_01C 1, _04FB
    ScrCmd_016 _056C
    ScrCmd_002

_04FB:
    ScrCmd_029 0x8004, 0x409F
    ScrCmd_028 0x8005, 1
    ScrCmd_07D 0x8004, 0x8005, 0x800C
    ScrCmd_011 0x800C, 0
    ScrCmd_01C 1, _0595
    ScrCmd_016 _054D
    ScrCmd_002

_0524:
    ScrCmd_029 0x8004, 0x409F
    ScrCmd_028 0x8005, 1
    ScrCmd_07D 0x8004, 0x8005, 0x800C
    ScrCmd_011 0x800C, 0
    ScrCmd_01C 1, _05DD
    ScrCmd_016 _054D
    ScrCmd_002

_054D:
    ScrCmd_04C 0x409A, 0
    ScrCmd_02C 22
    ScrCmd_04D
    ScrCmd_27C 1, 0x8004
    ScrCmd_1E5 51
    ScrCmd_014 0x7E0
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_056C:
    ScrCmd_029 0x8004, 0x409C
    ScrCmd_028 0x8005, 1
    ScrCmd_1D3 0x8004, 0x8005, 0x800C
    ScrCmd_011 0x800C, 0
    ScrCmd_01C 1, _0524
    ScrCmd_016 _05BE
    ScrCmd_002

_0595:
    ScrCmd_029 0x8004, 0x409C
    ScrCmd_028 0x8005, 1
    ScrCmd_1D3 0x8004, 0x8005, 0x800C
    ScrCmd_011 0x800C, 0
    ScrCmd_01C 1, _05DD
    ScrCmd_016 _05BE
    ScrCmd_002

_05BE:
    ScrCmd_04C 0x409A, 0
    ScrCmd_02C 22
    ScrCmd_04D
    ScrCmd_27C 2, 0x8004
    ScrCmd_1E5 51
    ScrCmd_014 0x7DF
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_05DD:
    ScrCmd_0D6 0, 0x409D
    ScrCmd_04C 0x409A, 0
    ScrCmd_011 0x409A, 0x184
    ScrCmd_01C 1, _0719
    ScrCmd_011 0x409A, 0x185
    ScrCmd_01C 1, _0719
    ScrCmd_011 0x409A, 0x187
    ScrCmd_01C 1, _0719
    ScrCmd_011 0x409A, 0x188
    ScrCmd_01C 1, _0719
    ScrCmd_011 0x409A, 0x18A
    ScrCmd_01C 1, _0719
    ScrCmd_011 0x409A, 0x18B
    ScrCmd_01C 1, _0719
    ScrCmd_1B7 0x800C, 9
    ScrCmd_011 0x800C, 0
    ScrCmd_01C 1, _06AC
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _06B7
    ScrCmd_011 0x800C, 2
    ScrCmd_01C 1, _06C2
    ScrCmd_011 0x800C, 3
    ScrCmd_01C 1, _06CD
    ScrCmd_011 0x800C, 4
    ScrCmd_01C 1, _06D8
    ScrCmd_011 0x800C, 5
    ScrCmd_01C 1, _06E3
    ScrCmd_011 0x800C, 6
    ScrCmd_01C 1, _06EE
    ScrCmd_011 0x800C, 7
    ScrCmd_01C 1, _06F9
    ScrCmd_016 _0704
    ScrCmd_002

_06AC:
    ScrCmd_02C 13
    ScrCmd_016 _070F
    ScrCmd_002

_06B7:
    ScrCmd_02C 14
    ScrCmd_016 _070F
    ScrCmd_002

_06C2:
    ScrCmd_02C 15
    ScrCmd_016 _070F
    ScrCmd_002

_06CD:
    ScrCmd_02C 16
    ScrCmd_016 _070F
    ScrCmd_002

_06D8:
    ScrCmd_02C 17
    ScrCmd_016 _070F
    ScrCmd_002

_06E3:
    ScrCmd_02C 18
    ScrCmd_016 _070F
    ScrCmd_002

_06EE:
    ScrCmd_02C 19
    ScrCmd_016 _070F
    ScrCmd_002

_06F9:
    ScrCmd_02C 20
    ScrCmd_016 _070F
    ScrCmd_002

_0704:
    ScrCmd_02C 21
    ScrCmd_016 _070F
    ScrCmd_002

_070F:
    ScrCmd_04D
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_0719:
    ScrCmd_1B7 0x800C, 9
    ScrCmd_011 0x800C, 0
    ScrCmd_01C 1, _078F
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _079A
    ScrCmd_011 0x800C, 2
    ScrCmd_01C 1, _07A5
    ScrCmd_011 0x800C, 3
    ScrCmd_01C 1, _07B0
    ScrCmd_011 0x800C, 4
    ScrCmd_01C 1, _07BB
    ScrCmd_011 0x800C, 5
    ScrCmd_01C 1, _07C6
    ScrCmd_011 0x800C, 6
    ScrCmd_01C 1, _07D1
    ScrCmd_011 0x800C, 7
    ScrCmd_01C 1, _07DC
    ScrCmd_016 _07E7
    ScrCmd_002

_078F:
    ScrCmd_02C 23
    ScrCmd_016 _070F
    ScrCmd_002

_079A:
    ScrCmd_02C 14
    ScrCmd_016 _070F
    ScrCmd_002

_07A5:
    ScrCmd_02C 15
    ScrCmd_016 _070F
    ScrCmd_002

_07B0:
    ScrCmd_02C 24
    ScrCmd_016 _070F
    ScrCmd_002

_07BB:
    ScrCmd_02C 17
    ScrCmd_016 _070F
    ScrCmd_002

_07C6:
    ScrCmd_02C 25
    ScrCmd_016 _070F
    ScrCmd_002

_07D1:
    ScrCmd_02C 26
    ScrCmd_016 _070F
    ScrCmd_002

_07DC:
    ScrCmd_02C 27
    ScrCmd_016 _070F
    ScrCmd_002

_07E7:
    ScrCmd_02C 21
    ScrCmd_016 _070F
    ScrCmd_002

_07F2:
    ScrCmd_028 0x400A, 0
    ScrCmd_016 _080E
    ScrCmd_002

_0800:
    ScrCmd_028 0x400A, 1
    ScrCmd_016 _080E
    ScrCmd_002

_080E:
    ScrCmd_049 0x5DC
    ScrCmd_060
    ScrCmd_068
    ScrCmd_0D6 0, 0x409D
    ScrCmd_1B7 0x800C, 6
    ScrCmd_011 0x800C, 0
    ScrCmd_01D 1, _0884
    ScrCmd_011 0x800C, 1
    ScrCmd_01D 1, _0889
    ScrCmd_011 0x800C, 2
    ScrCmd_01D 1, _088E
    ScrCmd_011 0x800C, 3
    ScrCmd_01D 1, _0893
    ScrCmd_011 0x800C, 4
    ScrCmd_01D 1, _0898
    ScrCmd_011 0x800C, 5
    ScrCmd_01D 1, _089D
    ScrCmd_011 0x400A, 0
    ScrCmd_01C 1, _08A2
    ScrCmd_016 _08B4
    ScrCmd_002

_0884:
    ScrCmd_02C 7
    ScrCmd_01B

_0889:
    ScrCmd_02C 8
    ScrCmd_01B

_088E:
    ScrCmd_02C 9
    ScrCmd_01B

_0893:
    ScrCmd_02C 10
    ScrCmd_01B

_0898:
    ScrCmd_02C 11
    ScrCmd_01B

_089D:
    ScrCmd_02C 12
    ScrCmd_01B

_08A2:
    ScrCmd_031
    ScrCmd_034
    ScrCmd_05E 0, _08C8
    ScrCmd_05F
    ScrCmd_061
    ScrCmd_002

_08B4:
    ScrCmd_031
    ScrCmd_034
    ScrCmd_05E 1, _08D0
    ScrCmd_05F
    ScrCmd_061
    ScrCmd_002

    .balign 4, 0
_08C8:
    .short 3, 1
    .short 0xFE, 0x00

    .balign 4, 0
_08D0:
    .short 2, 1
    .short 0xFE, 0x00

_08D8:
    ScrCmd_049 0x5DC
    ScrCmd_060
    ScrCmd_068
    ScrCmd_02C 28
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_08EB:
    ScrCmd_049 0x5DC
    ScrCmd_060
    ScrCmd_068
    ScrCmd_04B 0x5DC
    ScrCmd_04C 0x1A9, 0
    ScrCmd_02C 29
    ScrCmd_04D
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_090A:
    ScrCmd_049 0x5DC
    ScrCmd_060
    ScrCmd_068
    ScrCmd_02C 30
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_091D:
    ScrCmd_049 0x5DC
    ScrCmd_060
    ScrCmd_068
    ScrCmd_02C 31
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_0930:
    ScrCmd_049 0x5DC
    ScrCmd_060
    ScrCmd_068
    ScrCmd_02C 32
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_0943:
    ScrCmd_049 0x5DC
    ScrCmd_060
    ScrCmd_068
    ScrCmd_04B 0x5DC
    ScrCmd_04C 25, 0
    ScrCmd_02C 33
    ScrCmd_04D
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_0962:
    ScrCmd_049 0x5DC
    ScrCmd_060
    ScrCmd_068
    ScrCmd_02C 34
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_0975:
    ScrCmd_049 0x5DC
    ScrCmd_060
    ScrCmd_068
    ScrCmd_04B 0x5DC
    ScrCmd_04C 35, 0
    ScrCmd_02C 35
    ScrCmd_04D
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_0994:
    ScrCmd_1C0 0x800C, 25
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 35
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 54
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x1A1
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x1A9
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x1AB
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x1B8
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x183
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x184
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x185
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x186
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x187
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x188
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x189
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x18A
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x18B
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_016 _0182
    ScrCmd_002

_0ACC:
    ScrCmd_1C0 0x800C, 25
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 35
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 54
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x1A1
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x1A9
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x1AB
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x1B8
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 39
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0xFF
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x12C
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x11D
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x183
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x184
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x185
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x186
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x187
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x188
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x189
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x18A
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_1C0 0x800C, 0x18B
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _01B6
    ScrCmd_016 _01A3
    ScrCmd_002

_0C50:
    ScrCmd_198 0x400A, 0x800C
    ScrCmd_011 0x800C, 25
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 35
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 54
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x1A1
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x1A9
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x1AB
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x1B8
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x183
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x184
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x185
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x186
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x187
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x188
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x189
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x18A
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x18B
    ScrCmd_01C 1, _0D2E
    ScrCmd_028 0x800C, 0
    ScrCmd_01B

_0D2E:
    ScrCmd_028 0x800C, 1
    ScrCmd_01B

_0D36:
    ScrCmd_198 0x400A, 0x800C
    ScrCmd_011 0x800C, 25
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 35
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 54
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x1A1
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x1A9
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x1AB
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x1B8
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 39
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0xFF
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x12C
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x11D
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x183
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x184
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x185
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x186
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x187
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x188
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x189
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x18A
    ScrCmd_01C 1, _0D2E
    ScrCmd_011 0x800C, 0x18B
    ScrCmd_01C 1, _0D2E
    ScrCmd_028 0x800C, 0
    ScrCmd_01B

_0E48:
    ScrCmd_029 0x8008, 0x409A
    ScrCmd_011 0x8008, 25
    ScrCmd_01C 1, _0F5A
    ScrCmd_011 0x8008, 0xFF
    ScrCmd_01C 1, _0F68
    ScrCmd_011 0x8008, 35
    ScrCmd_01C 1, _0F76
    ScrCmd_011 0x8008, 54
    ScrCmd_01C 1, _0F84
    ScrCmd_011 0x8008, 0x1A1
    ScrCmd_01C 1, _0F92
    ScrCmd_011 0x8008, 0x1A9
    ScrCmd_01C 1, _0FA0
    ScrCmd_011 0x8008, 0x1AB
    ScrCmd_01C 1, _0FAE
    ScrCmd_011 0x8008, 0x1B8
    ScrCmd_01C 1, _0FBC
    ScrCmd_011 0x8008, 39
    ScrCmd_01C 1, _0FCA
    ScrCmd_011 0x8008, 0x12C
    ScrCmd_01C 1, _0FD8
    ScrCmd_011 0x8008, 0x11D
    ScrCmd_01C 1, _0FE6
    ScrCmd_011 0x8008, 0x183
    ScrCmd_01C 1, _0FF4
    ScrCmd_011 0x8008, 0x184
    ScrCmd_01C 1, _1002
    ScrCmd_011 0x8008, 0x185
    ScrCmd_01C 1, _1010
    ScrCmd_011 0x8008, 0x186
    ScrCmd_01C 1, _101E
    ScrCmd_011 0x8008, 0x187
    ScrCmd_01C 1, _102C
    ScrCmd_011 0x8008, 0x188
    ScrCmd_01C 1, _103A
    ScrCmd_011 0x8008, 0x189
    ScrCmd_01C 1, _1048
    ScrCmd_011 0x8008, 0x18A
    ScrCmd_01C 1, _1056
    ScrCmd_011 0x8008, 0x18B
    ScrCmd_01C 1, _1064
    ScrCmd_016 _02BB
    ScrCmd_002

_0F5A:
    ScrCmd_028 0x4020, 71
    ScrCmd_016 _1072
    ScrCmd_002

_0F68:
    ScrCmd_028 0x4020, 78
    ScrCmd_016 _1072
    ScrCmd_002

_0F76:
    ScrCmd_028 0x4020, 72
    ScrCmd_016 _1072
    ScrCmd_002

_0F84:
    ScrCmd_028 0x4020, 74
    ScrCmd_016 _1072
    ScrCmd_002

_0F92:
    ScrCmd_028 0x4020, 204
    ScrCmd_016 _1072
    ScrCmd_002

_0FA0:
    ScrCmd_028 0x4020, 185
    ScrCmd_016 _1072
    ScrCmd_002

_0FAE:
    ScrCmd_028 0x4020, 206
    ScrCmd_016 _1072
    ScrCmd_002

_0FBC:
    ScrCmd_028 0x4020, 207
    ScrCmd_016 _1072
    ScrCmd_002

_0FCA:
    ScrCmd_028 0x4020, 73
    ScrCmd_016 _1072
    ScrCmd_002

_0FD8:
    ScrCmd_028 0x4020, 79
    ScrCmd_016 _1072
    ScrCmd_002

_0FE6:
    ScrCmd_028 0x4020, 205
    ScrCmd_016 _1072
    ScrCmd_002

_0FF4:
    ScrCmd_028 0x4020, 220
    ScrCmd_016 _1072
    ScrCmd_002

_1002:
    ScrCmd_028 0x4020, 221
    ScrCmd_016 _1072
    ScrCmd_002

_1010:
    ScrCmd_028 0x4020, 222
    ScrCmd_016 _1072
    ScrCmd_002

_101E:
    ScrCmd_028 0x4020, 223
    ScrCmd_016 _1072
    ScrCmd_002

_102C:
    ScrCmd_028 0x4020, 224
    ScrCmd_016 _1072
    ScrCmd_002

_103A:
    ScrCmd_028 0x4020, 225
    ScrCmd_016 _1072
    ScrCmd_002

_1048:
    ScrCmd_028 0x4020, 226
    ScrCmd_016 _1072
    ScrCmd_002

_1056:
    ScrCmd_028 0x4020, 227
    ScrCmd_016 _1072
    ScrCmd_002

_1064:
    ScrCmd_028 0x4020, 228
    ScrCmd_016 _1072
    ScrCmd_002

_1072:
    ScrCmd_028 0x8002, 5
    ScrCmd_01F 0x2A1
    ScrCmd_016 _02C9
    ScrCmd_002

_1084:
    ScrCmd_049 0x5DC
    ScrCmd_060
    ScrCmd_068
    ScrCmd_0D6 0, 0x409D
    ScrCmd_216 0x800C
    ScrCmd_011 0x800C, 200
    ScrCmd_01C 4, _04D8
    ScrCmd_016 _05DD
    ScrCmd_002

_10AA:
    ScrCmd_049 0x5DC
    ScrCmd_060
    ScrCmd_068
    ScrCmd_020 0xAB5
    ScrCmd_01C 1, _117C
    ScrCmd_02C 36
    ScrCmd_2E1 0x40AB, 0x8004
    ScrCmd_2E0 0x40AB, 0x800C
    ScrCmd_011 0x800C, 0
    ScrCmd_01C 1, _10E1
    ScrCmd_016 _1136
    ScrCmd_002

_10E1:
    ScrCmd_0D1 0, 0x8004
    ScrCmd_02C 37
    ScrCmd_03E 0x800C
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _1161
    ScrCmd_028 0x8005, 5
    ScrCmd_07D 0x8004, 0x8005, 0x800C
    ScrCmd_011 0x800C, 0
    ScrCmd_01C 1, _1172
    ScrCmd_0CD 0
    ScrCmd_33D 1, 0x8004
    ScrCmd_04E 0x486
    ScrCmd_02C 40
    ScrCmd_04F
    ScrCmd_07B 0x8004, 0x8005, 0x800C
    ScrCmd_016 _117C
    ScrCmd_002

_1136:
    ScrCmd_261 0, 0x8004
    ScrCmd_02C 37
    ScrCmd_03E 0x800C
    ScrCmd_011 0x800C, 1
    ScrCmd_01C 1, _1161
    ScrCmd_028 0x8005, 1
    ScrCmd_014 0x7DF
    ScrCmd_016 _117C
    ScrCmd_002

_1161:
    ScrCmd_02C 38
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

    .byte 52
    .byte 0
    .byte 97
    .byte 0
    .byte 2
    .byte 0

_1172:
    ScrCmd_014 0x7E1
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_117C:
    ScrCmd_01E 0xAB5
    ScrCmd_02C 39
    ScrCmd_031
    ScrCmd_034
    ScrCmd_061
    ScrCmd_002

_118B:
    ScrCmd_028 0x8003, 1
    ScrCmd_016 _1305
    ScrCmd_002

_1199:
    ScrCmd_028 0x8003, 2
    ScrCmd_016 _1305
    ScrCmd_002

_11A7:
    ScrCmd_028 0x8003, 3
    ScrCmd_016 _1305
    ScrCmd_002

_11B5:
    ScrCmd_028 0x8003, 4
    ScrCmd_016 _1305
    ScrCmd_002

_11C3:
    ScrCmd_028 0x8003, 5
    ScrCmd_016 _1305
    ScrCmd_002

_11D1:
    ScrCmd_028 0x8003, 6
    ScrCmd_016 _1305
    ScrCmd_002

_11DF:
    ScrCmd_028 0x8003, 7
    ScrCmd_016 _1305
    ScrCmd_002

_11ED:
    ScrCmd_028 0x8003, 8
    ScrCmd_016 _1305
    ScrCmd_002

_11FB:
    ScrCmd_028 0x8003, 9
    ScrCmd_016 _1305
    ScrCmd_002

_1209:
    ScrCmd_028 0x8003, 10
    ScrCmd_016 _1305
    ScrCmd_002

_1217:
    ScrCmd_028 0x8003, 11
    ScrCmd_016 _1305
    ScrCmd_002

_1225:
    ScrCmd_028 0x8003, 12
    ScrCmd_016 _1305
    ScrCmd_002

_1233:
    ScrCmd_028 0x8003, 13
    ScrCmd_016 _1305
    ScrCmd_002

_1241:
    ScrCmd_028 0x8003, 14
    ScrCmd_016 _1305
    ScrCmd_002

_124F:
    ScrCmd_028 0x8003, 15
    ScrCmd_016 _1305
    ScrCmd_002

_125D:
    ScrCmd_028 0x8003, 16
    ScrCmd_016 _1305
    ScrCmd_002

_126B:
    ScrCmd_028 0x8003, 17
    ScrCmd_016 _1305
    ScrCmd_002

_1279:
    ScrCmd_028 0x8003, 18
    ScrCmd_016 _1305
    ScrCmd_002

_1287:
    ScrCmd_028 0x8003, 19
    ScrCmd_016 _1305
    ScrCmd_002

_1295:
    ScrCmd_028 0x8003, 20
    ScrCmd_016 _1305
    ScrCmd_002

_12A3:
    ScrCmd_028 0x8003, 21
    ScrCmd_016 _1305
    ScrCmd_002

_12B1:
    ScrCmd_028 0x8003, 22
    ScrCmd_016 _1305
    ScrCmd_002

_12BF:
    ScrCmd_028 0x8003, 23
    ScrCmd_016 _1305
    ScrCmd_002

_12CD:
    ScrCmd_028 0x8003, 24
    ScrCmd_016 _1305
    ScrCmd_002

_12DB:
    ScrCmd_028 0x8003, 25
    ScrCmd_016 _1305
    ScrCmd_002

_12E9:
    ScrCmd_028 0x8003, 26
    ScrCmd_016 _1305
    ScrCmd_002

_12F7:
    ScrCmd_028 0x8003, 27
    ScrCmd_016 _1305
    ScrCmd_002

_1305:
    ScrCmd_0BC 6, 1, 0, 0
    ScrCmd_0BD
    ScrCmd_060
    ScrCmd_003 1, 0x800C
    ScrCmd_32D
    ScrCmd_338
    ScrCmd_05E 5, _1758
    ScrCmd_05F
    ScrCmd_049 0x632
    ScrCmd_011 0x8003, 1
    ScrCmd_01D 1, _14C2
    ScrCmd_011 0x8003, 2
    ScrCmd_01D 1, _14DA
    ScrCmd_011 0x8003, 3
    ScrCmd_01D 1, _14F2
    ScrCmd_011 0x8003, 4
    ScrCmd_01D 1, _150A
    ScrCmd_011 0x8003, 5
    ScrCmd_01D 1, _1522
    ScrCmd_011 0x8003, 6
    ScrCmd_01D 1, _153A
    ScrCmd_011 0x8003, 7
    ScrCmd_01D 1, _1552
    ScrCmd_011 0x8003, 8
    ScrCmd_01D 1, _156A
    ScrCmd_011 0x8003, 9
    ScrCmd_01D 1, _1582
    ScrCmd_011 0x8003, 10
    ScrCmd_01D 1, _159A
    ScrCmd_011 0x8003, 11
    ScrCmd_01D 1, _15B2
    ScrCmd_011 0x8003, 12
    ScrCmd_01D 1, _15CA
    ScrCmd_011 0x8003, 13
    ScrCmd_01D 1, _15E2
    ScrCmd_011 0x8003, 14
    ScrCmd_01D 1, _15FA
    ScrCmd_011 0x8003, 15
    ScrCmd_01D 1, _1612
    ScrCmd_011 0x8003, 16
    ScrCmd_01D 1, _162A
    ScrCmd_011 0x8003, 17
    ScrCmd_01D 1, _1642
    ScrCmd_011 0x8003, 18
    ScrCmd_01D 1, _165A
    ScrCmd_011 0x8003, 19
    ScrCmd_01D 1, _1672
    ScrCmd_011 0x8003, 20
    ScrCmd_01D 1, _168A
    ScrCmd_011 0x8003, 21
    ScrCmd_01D 1, _16A2
    ScrCmd_011 0x8003, 22
    ScrCmd_01D 1, _16BA
    ScrCmd_011 0x8003, 23
    ScrCmd_01D 1, _16D2
    ScrCmd_011 0x8003, 24
    ScrCmd_01D 1, _16EA
    ScrCmd_011 0x8003, 25
    ScrCmd_01D 1, _1702
    ScrCmd_011 0x8003, 26
    ScrCmd_01D 1, _171A
    ScrCmd_011 0x8003, 27
    ScrCmd_01D 1, _1732
    ScrCmd_05E 0xFF, _1764
    ScrCmd_05F
    ScrCmd_0BC 6, 1, 1, 0
    ScrCmd_0BD
    ScrCmd_05E 5, _1764
    ScrCmd_05F
    ScrCmd_061
    ScrCmd_05E 0xFF, _1770
    ScrCmd_05F
    ScrCmd_32E
    ScrCmd_339
    ScrCmd_003 2, 0x800C
    ScrCmd_002

_14C2:
    ScrCmd_05E 0xFF, _1778
    ScrCmd_05F
    ScrCmd_187 5, 35, 2, 15, 1
    ScrCmd_01B

_14DA:
    ScrCmd_05E 0xFF, _1780
    ScrCmd_05F
    ScrCmd_187 5, 35, 2, 15, 1
    ScrCmd_01B

_14F2:
    ScrCmd_05E 0xFF, _178C
    ScrCmd_05F
    ScrCmd_187 5, 35, 2, 15, 1
    ScrCmd_01B

_150A:
    ScrCmd_05E 0xFF, _1798
    ScrCmd_05F
    ScrCmd_187 5, 17, 2, 16, 1
    ScrCmd_01B

_1522:
    ScrCmd_05E 0xFF, _17A4
    ScrCmd_05F
    ScrCmd_187 5, 17, 2, 16, 1
    ScrCmd_01B

_153A:
    ScrCmd_05E 0xFF, _17B0
    ScrCmd_05F
    ScrCmd_187 5, 17, 2, 16, 1
    ScrCmd_01B

_1552:
    ScrCmd_05E 0xFF, _17BC
    ScrCmd_05F
    ScrCmd_187 5, 47, 4, 8, 1
    ScrCmd_01B

_156A:
    ScrCmd_05E 0xFF, _17C8
    ScrCmd_05F
    ScrCmd_187 5, 33, 5, 7, 1
    ScrCmd_01B

_1582:
    ScrCmd_05E 0xFF, _17D4
    ScrCmd_05F
    ScrCmd_187 5, 15, 4, 10, 1
    ScrCmd_01B

_159A:
    ScrCmd_05E 0xFF, _17E0
    ScrCmd_05F
    ScrCmd_187 5, 52, 4, 25, 1
    ScrCmd_01B

_15B2:
    ScrCmd_05E 0xFF, _17EC
    ScrCmd_05F
    ScrCmd_187 5, 15, 4, 10, 1
    ScrCmd_01B

_15CA:
    ScrCmd_05E 0xFF, _17F8
    ScrCmd_05F
    ScrCmd_187 5, 33, 5, 7, 1
    ScrCmd_01B

_15E2:
    ScrCmd_05E 0xFF, _1804
    ScrCmd_05F
    ScrCmd_187 5, 52, 4, 25, 1
    ScrCmd_01B

_15FA:
    ScrCmd_05E 0xFF, _1810
    ScrCmd_05F
    ScrCmd_187 5, 26, 6, 9, 1
    ScrCmd_01B

_1612:
    ScrCmd_05E 0xFF, _181C
    ScrCmd_05F
    ScrCmd_187 5, 41, 3, 16, 1
    ScrCmd_01B

_162A:
    ScrCmd_05E 0xFF, _1828
    ScrCmd_05F
    ScrCmd_187 5, 52, 4, 25, 1
    ScrCmd_01B

_1642:
    ScrCmd_05E 0xFF, _1834
    ScrCmd_05F
    ScrCmd_187 5, 41, 3, 16, 1
    ScrCmd_01B

_165A:
    ScrCmd_05E 0xFF, _1840
    ScrCmd_05F
    ScrCmd_187 5, 26, 6, 9, 1
    ScrCmd_01B

_1672:
    ScrCmd_05E 0xFF, _184C
    ScrCmd_05F
    ScrCmd_187 5, 47, 4, 8, 1
    ScrCmd_01B

_168A:
    ScrCmd_05E 0xFF, _1854
    ScrCmd_05F
    ScrCmd_187 5, 47, 2, 34, 1
    ScrCmd_01B

_16A2:
    ScrCmd_05E 0xFF, _1860
    ScrCmd_05F
    ScrCmd_187 5, 15, 4, 10, 1
    ScrCmd_01B

_16BA:
    ScrCmd_05E 0xFF, _186C
    ScrCmd_05F
    ScrCmd_187 5, 47, 4, 8, 1
    ScrCmd_01B

_16D2:
    ScrCmd_05E 0xFF, _1878
    ScrCmd_05F
    ScrCmd_187 5, 33, 5, 7, 1
    ScrCmd_01B

_16EA:
    ScrCmd_05E 0xFF, _1884
    ScrCmd_05F
    ScrCmd_187 5, 47, 2, 34, 1
    ScrCmd_01B

_1702:
    ScrCmd_05E 0xFF, _1890
    ScrCmd_05F
    ScrCmd_187 5, 52, 4, 25, 1
    ScrCmd_01B

_171A:
    ScrCmd_05E 0xFF, _189C
    ScrCmd_05F
    ScrCmd_187 5, 15, 4, 10, 1
    ScrCmd_01B

_1732:
    ScrCmd_05E 0xFF, _18A8
    ScrCmd_05F
    ScrCmd_187 5, 33, 5, 7, 1
    ScrCmd_01B

_174A:
    ScrCmd_060
    ScrCmd_028 0x40AC, 0
    ScrCmd_061
    ScrCmd_002

    .balign 4, 0
_1758:
    .short 1, 1
    .short 69, 1
    .short 0xFE, 0x00

    .balign 4, 0
_1764:
    .short 1, 1
    .short 70, 1
    .short 0xFE, 0x00

    .balign 4, 0
_1770:
    .short 13, 1
    .short 0xFE, 0x00

    .balign 4, 0
_1778:
    .short 23, 18
    .short 0xFE, 0x00

    .balign 4, 0
_1780:
    .short 23, 19
    .short 20, 1
    .short 0xFE, 0x00

    .balign 4, 0
_178C:
    .short 23, 17
    .short 20, 1
    .short 0xFE, 0x00

    .balign 4, 0
_1798:
    .short 22, 18
    .short 21, 2
    .short 0xFE, 0x00

    .balign 4, 0
_17A4:
    .short 22, 17
    .short 21, 1
    .short 0xFE, 0x00

    .balign 4, 0
_17B0:
    .short 22, 19
    .short 21, 1
    .short 0xFE, 0x00

    .balign 4, 0
_17BC:
    .short 22, 5
    .short 20, 16
    .short 0xFE, 0x00

    .balign 4, 0
_17C8:
    .short 22, 18
    .short 20, 18
    .short 0xFE, 0x00

    .balign 4, 0
_17D4:
    .short 22, 38
    .short 20, 15
    .short 0xFE, 0x00

    .balign 4, 0
_17E0:
    .short 23, 5
    .short 21, 18
    .short 0xFE, 0x00

    .balign 4, 0
_17EC:
    .short 22, 31
    .short 21, 2
    .short 0xFE, 0x00

    .balign 4, 0
_17F8:
    .short 22, 15
    .short 20, 1
    .short 0xFE, 0x00

    .balign 4, 0
_1804:
    .short 23, 37
    .short 21, 16
    .short 0xFE, 0x00

    .balign 4, 0
_1810:
    .short 23, 12
    .short 20, 1
    .short 0xFE, 0x00

    .balign 4, 0
_181C:
    .short 23, 25
    .short 21, 6
    .short 0xFE, 0x00

    .balign 4, 0
_1828:
    .short 23, 19
    .short 21, 19
    .short 0xFE, 0x00

    .balign 4, 0
_1834:
    .short 23, 9
    .short 21, 9
    .short 0xFE, 0x00

    .balign 4, 0
_1840:
    .short 22, 8
    .short 21, 2
    .short 0xFE, 0x00

    .balign 4, 0
_184C:
    .short 23, 21
    .short 0xFE, 0x00

    .balign 4, 0
_1854:
    .short 23, 22
    .short 21, 25
    .short 0xFE, 0x00

    .balign 4, 0
_1860:
    .short 22, 12
    .short 21, 1
    .short 0xFE, 0x00

    .balign 4, 0
_186C:
    .short 23, 6
    .short 20, 7
    .short 0xFE, 0x00

    .balign 4, 0
_1878:
    .short 22, 7
    .short 20, 9
    .short 0xFE, 0x00

    .balign 4, 0
_1884:
    .short 23, 5
    .short 21, 18
    .short 0xFE, 0x00

    .balign 4, 0
_1890:
    .short 23, 5
    .short 20, 8
    .short 0xFE, 0x00

    .balign 4, 0
_189C:
    .short 22, 31
    .short 20, 24
    .short 0xFE, 0x00

    .balign 4, 0
_18A8:
    .short 22, 15
    .short 20, 27
    .short 0xFE, 0x00