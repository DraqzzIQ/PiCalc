# CasioOS
Simulates the firmware of a CASIO fx-87DE PLUS (2nd edition) with some additional features

```
###################################################################################################################################################################################################
# S  A  M  STO  RCL  STAT  CMPLX  MAT  VCT  D  R  G  FIX  SCI  Math                                                                                                                               #
#                                                                                                                                                                                                 #
#                                                                                                                                                                                                 #
#                                                                                                                                                                                                 #
#                                                                                                                                                                                                 #
#                                                                                                                                                                                                 #
#             þ þ þ þ þ þ                 þ þ                 þ þ þ þ þ þ þ þ         þ þ þ þ þ þ         þ þ þ þ þ þ þ þ                 þ þ þ þ þ þ þ þ             þ þ þ þ þ þ þ þ             #
#             þ þ þ þ þ þ                 þ þ                 þ þ þ þ þ þ þ þ         þ þ þ þ þ þ         þ þ þ þ þ þ þ þ                 þ þ þ þ þ þ þ þ             þ þ þ þ þ þ þ þ             #
#         þ þ             þ þ         þ þ     þ þ         þ þ                 þ þ         þ þ         þ þ                 þ þ         þ þ                 þ þ     þ þ                 þ þ         #
#         þ þ             þ þ         þ þ     þ þ         þ þ                 þ þ         þ þ         þ þ                 þ þ         þ þ                 þ þ     þ þ                 þ þ         #
#         þ þ                         þ þ     þ þ         þ þ                             þ þ         þ þ                 þ þ         þ þ                 þ þ     þ þ                             #
#         þ þ                         þ þ     þ þ         þ þ                             þ þ         þ þ                 þ þ         þ þ                 þ þ     þ þ                             #
#         þ þ                     þ þ             þ þ     þ þ                             þ þ         þ þ                 þ þ         þ þ                 þ þ     þ þ                             #
#         þ þ                     þ þ             þ þ     þ þ                             þ þ         þ þ                 þ þ         þ þ                 þ þ     þ þ                             #
#         þ þ                     þ þ             þ þ         þ þ þ þ þ þ þ þ             þ þ         þ þ                 þ þ         þ þ                 þ þ         þ þ þ þ þ þ þ þ             #
#         þ þ                     þ þ             þ þ         þ þ þ þ þ þ þ þ             þ þ         þ þ                 þ þ         þ þ                 þ þ         þ þ þ þ þ þ þ þ             #
#         þ þ                     þ þ þ þ þ þ þ þ þ þ                         þ þ         þ þ         þ þ                 þ þ         þ þ                 þ þ                         þ þ         #
#         þ þ                     þ þ þ þ þ þ þ þ þ þ                         þ þ         þ þ         þ þ                 þ þ         þ þ                 þ þ                         þ þ         #
#         þ þ                     þ þ             þ þ                         þ þ         þ þ         þ þ                 þ þ         þ þ                 þ þ                         þ þ         #
#         þ þ                     þ þ             þ þ                         þ þ         þ þ         þ þ                 þ þ         þ þ                 þ þ                         þ þ         #
#         þ þ             þ þ     þ þ             þ þ                         þ þ         þ þ         þ þ                 þ þ         þ þ                 þ þ                         þ þ         #
#         þ þ             þ þ     þ þ             þ þ                         þ þ         þ þ         þ þ                 þ þ         þ þ                 þ þ                         þ þ         #
#             þ þ þ þ þ þ         þ þ             þ þ         þ þ þ þ þ þ þ þ         þ þ þ þ þ þ         þ þ þ þ þ þ þ þ                 þ þ þ þ þ þ þ þ             þ þ þ þ þ þ þ þ             #
#             þ þ þ þ þ þ         þ þ             þ þ         þ þ þ þ þ þ þ þ         þ þ þ þ þ þ         þ þ þ þ þ þ þ þ                 þ þ þ þ þ þ þ þ             þ þ þ þ þ þ þ þ             #
#                                                                                                                                                                                                 #
#                                                                                                                                                                                                 #
#                                                                                                                                                                                                 #
#                                                                                                                                                                                                 #
#                                                                                                                                                                                                 #
#                                                                                                                                                                                                 #
#                                                                                                                                                                                                 #
#                                                                                                                                                                                                 #
###################################################################################################################################################################################################
```

## How To Start
- Clone and open repo with an editor of your choice

### Secrets
Create a file called `secrets` in the project root folder
and add your secrets in the following format:
```
WOLFRAMALPHA_APPID=DEMO
OPENAI_API_KEY=DEMO
PICO_WIFI_SSID=DEMO
PICO_WIFI_PASSWORD=DEMO
```

### JetBrains Fleet or CLion
- Select Run config (e.g.: "Run CasioOS")
- Click on the Start button

## Dependencies
[SDL2](https://github.com/libsdl-org/SDL)

[cpp-httplib](https://github.com/yhirose/cpp-httplib)

[no-OS-FatFS-SD-SPI-RPi-Pico](https://github.com/carlk3/no-OS-FatFS-SD-SPI-RPi-Pico)

openssh
