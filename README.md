# Yaaraa (Yet Another Audio Recorder and Analyzer)
*******************************************************************
Read the following to understand how the Audio Recording and 
Analysis software _Yaaraa_ works. Content is broken up as follows:

1. PURPOSE
  1. EXECUTION FLOW
2. BASIC USE
3. INSTALL
  3. PHYSICAL
  3. SOFTWARE
    3. DEPENDANCIES
4. RUN
  4. CONFIG FILES
    4. CONFIG EXAMPLE
  4. FEATURE PLAN (AUDIO ANALYSIS - YAAFE)
    4. FEATURE PLAN EXAMPLE
    4. START RECORDING
    4. STOP RECORDING
5. CLEAN UP
6. EXAMPLE
7. REFERENCES


*******************************************************************
## 1. PURPOSE
*******************************************************************
The purpose of the _Yaaraa_ software is to remotely record and analyize 
audio. _Yaaraa_ stands for "Yet Another Audio Recording and Analysis".
_Yaaraa_ is designed to work on a **Rasberry Pi** using the **Rasbian OS**.
 - Recording are made via the UNIX software called _**arecord**_. 
 - Recording analysis is done via the UNIX software called _**Yaafe**_.



Questions, comments, or bugs should be reported to:
`cameron.embree748@myci.csuci.edu`

*******************************************************************
### 1.1 EXECUTION FLOW
*******************************************************************
  1. Make a recording to temporary 'analysis' directory
  2. IF audio filtering is being performed: 
    2. Extract "Filter Features" in 'analysis'
    2. Analize "Filter Features" in 'analysis'
  3. Perform full feature extraction in 'analysis'
  4. Move extracted audio features and audio to 'data' directory
    4. IF 'FILES' format chosen in config - move all files
    4. IF 'FORMATTED' format chosen in config - combine all _Yaafe_ files into 1 json file

*******************************************************************
## 2. BASIC USE
*******************************************************************
Install depednancies and _Yaaraa_ with:
```bash
  ./install.sh
```
Edit config file with:
```bash
  nano sound_setting.conf
```
Run code with:
```bash
  ./start_sound.sh
```

*******************************************************************
## 3. INSTALL
*******************************************************************
First install a physical sound card (if your RPi does not have one 
integrated) by (3.1) and then install the software and dependancies 
by (3.2).


*******************************************************************
### 3.1 PHYSICAL
*******************************************************************
Two physical installations are needed by the software:
  1. A sound card
  2. A microphone that the sound card can talk to

Rasberry Pi's older than the B+ version have no on board sound card
so you will need a USB sound card.

 1. First, install the USB sound card into an available USB slot. 
Your RPi should recognise the sound card without any more assistance.
 2. Second, install a microphone. If you have an external sound card
then the microphone will be installed into that. If you have an
on board sound card then install your microphone into the RPi.

In either case, the microphone will be recognized by the sound card

Ensure your installation is correct by performing the following in
your terminal:

```bash
  $ lsusb
```
You should see your sound card in the output. Example output:
```bash
  pi@raspberrypi ~/yaaraa lsusb
  Bus 001 Device 002: ID 0424:9512 Standard Microsystems Corp. 
  Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
  Bus 001 Device 003: ID 0424:ec00 Standard Microsystems Corp. 
  Bus 001 Device 004: ID 0d8c:0008 C-Media Electronics, Inc. 
  Bus 001 Device 005: ID 04ca:0027 Lite-On Technology Corp. 
```

My USB sound card is called 'C-Media Electronics, Inc.', so my
sound card is recongized.

Try making a recording using the arecord software with the
following terminal command:
```bash
  $ arecord -D plughw:1 --duration=2 -f cd -vv ~/test.wav 
```

There should now be an audio file called "test.wav" in your home 
directory. Play the sound file someplace with speakers to ensure 
the recording was successful.

*******************************************************************
### 3.2 SOFTWARE
*******************************************************************
To install the _Yaara_ code perform the following:
```bash
  $ ./install.sh |& tee log/install.log
```

After the install script finishes, a log file "install.log" should
be in the 'log/' directory for future reference about the install.

The installation script is defined as follows:
```bash
./install [-l|--local]
          [-v|--verbose]
          [-u|--update]
          [-nu|--noupdate]
          [-c|--compile]
          [-nc|--nocompile]
          [-tf|--testframework]
          [-ntf|--notestframework]
```

The installation script takes the following OPTIONAL arguments:

* **-l|--local)** 
 * Only generate start and stop sound scripts locally. Does not attempt to move start/stop scripts to the $CIRAINBOW/bin/ |
* **-v|--verbose)** 
 * Turns on (DEFAULT is off) print statements during installation
* **-u|--update)** 
 * Turns on installation job of checking for system updates and dependant libraray existance/updates 
* **-nu|--noupdate)** 
 * Turns off DEFAULT installation job of checking for system updates and dependant libraray existance/updates 
* **-c|--compile)** 
 * Turns on installation job of cleaning and remaking the local _Yaaraa_ code.
* **-nc|--nocompile)** 
 * Turns off DEFAULT installation job of cleaning and remaking the local _Yaaraa_ code.
* **-tf|--testframework)** 
 * Turns on downloading of the GoogleTest framework for various tests. gtest is only needed for testing and is not part of the standard Yaara package.
* **-ntf|--notestframework)** 
 * Turns off downloading of GoogleTest framework. This flag is OFF by default because gtest is not needed by Yaaraa, only for testing.



For example, to generate new start/stop scripts but not re-compile
_Yaaraa_ and not update the RPi, we can do the following:

```bash
  $ ./install -nu -nc
```
OR
```bash
  $ ./install --noupdate --nocompile
```
The installation script by default compiles _Yaaraa_ (unless told
otherwise by argument "-nc", but you can always clean and re-make 
_Yaaraa_ with:
```bash
  $ make clean
  $ make
```

*******************************************************************
### 3.3 DEPENDANCIES
*******************************************************************
_Yaaraa_ uses the software "arecord" and "Yaafe". More information about these 
libraries can be found in the REFERENCES section. 

All dependancies are installed/updated by the "install.sh" script.



*******************************************************************
## 4. RUN
*******************************************************************
To run _Yaaraa_ after the previous INSTALL steps requires two steps:
  1. Edit the config file called "sound_settings.conf" (See Section 3.1).
```bash
    $ nano sound_settings.conf
```
  2. Run the code with "start_sound.sh" script (See Section 4.3).
```bash
    $ ./start_sound.sh
```
  3. (OPTIONALLY) Stop recording with "stop.sh" script (See Section 4.4). Every fininite number of recordings will stop autiomatically (eventually) but infinite recordings run as a Deamon will need to be stopped by this script.
```bash
    $ ./stop_sound.sh
```

*******************************************************************
### 4.1 CONFIG FILES
*******************************************************************
The configuration file, called "sound_settings.conf", is a file 
that litsts how recordings are performed. Config files should have
at least two sections: NODE_INFO and SOUNDS of the form:
```
[NODE_INFO]
...
//Optional Node info line by line
...

[SOUNDS]
...
//sound config details line by line
...
```

Config files contain the following operating details
(Where **(REQ)** means soemthing is **Required** in config file and **(OPT)** means **Optional** in config file) :
* **recordingduration - (REQ)** 
 * Duration of each recoding in seconds 
* **recordingnumber - (REQ)** 
 * Number of recordings to make 
* **samplerate - (REQ)** 
 * Sample rate in Hz of each recording 
* **recordingextention - (REQ)** 
 * recording extention. 
 * **DEFAULT is ".wav"**
* **outputform - (REQ)** 
 * Either output is plan Yaafe using "YAAFE" or output is a json file using "FORMATTED".
 * **DEFAULT: string "FILES"**
* **outputtypeid - (OPT)** 
 * The sensor output ID used for JSON formatted output in data directory. 
 * **DEFAULT: -1**
* **saverecording - (OPT)** 
 * Save audio that is recorded. 
 * **DEAFULT: string "on" - recordings are saved**
* **analysis - (OPT)** 
 * Turn audio analyis (audio feature extraction via Yaafe) off. 
 * **DEAFULT: string "off" - filtering is performed**
* **background - (OPT)** 
 * Turn _Yaaraa_ into a Daemon with "on". 
 * **DEAFULT: string "off" - prints to terminal**
* **filter - (OPT)** 
 * Turn filtering on/off. 
 * **DEAFULT: string "on" - filtering is performed**
* **recordingprefix - (OPT)** 
 * Recording filename prefix. 
 * **DEFAULT: 'rec_' at start of each audio file**
* **featureplanpath - (OPT)** 
 * Path to a feature plan file. 
 * **DEFAULT: local sound directory**
* **featureplanname - (OPT)** 
 * Name of a feature plan. 
 * **DEFAULT: string "featureplan"**
* **filterplanpath - (OPT)** 
 * Path to a filter plan file. 
 * **DEFAULT: local sound directory**
* **filterplanname - (OPT)** 
 * Name of a filter plan file. 
 * **DEFAULT: string "filterplan"**
* **recordinglocation - (OPT)** 
 * Directory path where recordings are saved. Analysis still in 'analysis' dir. 
 * **DEFAULT: local 'analysis' dir**
* **datalocation - (OPT)** 
 * Directory where data finished being recorded and analized goes. 
 * **DEFAULT: local 'data' directory**
* **analysislocation - (OPT)** 
 * Work space for audio recording analysis and filtering. 
 * **DEFAULT: local "analysis" directory**
* **latitude - (OPT)** 
 * Latitude loc, DEFAULT is zero. 
 * **DEAFULT: string "0.0000 W"**
* **longitude - (OPT)** 
 * Longitude location. 
 * **DEAFULT: string "0.0000 N"**
* **rasberrypiid - (OPT)** 
 * Custom string rasberry pi id. 
 * **DEFAULT: string "-1"**
* **simulate - (OPT)** 
 * flag to turn on sim mode where copies of previously recorded data  output files from 'simulationdirectory' to 'data' directory. 
 * **DEFAULT = string "off"**
* **simulationdirectory - (OPT)** 
 * Directory where sim output files are found. Copied to "data" directory if simulateion is "on". 
 * **DEFAULT: durectory "/test/data_yaafe/"**
* **debug - (OPT)** 
 * Turn on/off debug statements
 * **DEFAULT: string "off"**


*******************************************************************
#### 4.1.1 CONFIG EXAMPLE
*******************************************************************
EX 1: Consider the following config file (Generic example):
```
  [NODE_INFO]
  latitude = 17.2343432
  longitude = -119.23423423
  raspberrypiid = 14

  [SOUNDS]
  background = off
  analysis = on
  filter = off
  recordingextention = .wav
  recordingduration = 3
  recordingnumber = 2
  recordingprefix = rec_
  samplerate = 44100
  datalocation = /home/pi/data/
  outputform = YAAFE
```
Two recordings of duration 3 seconds at a sample rate of 44100Hz
will be made. Each recording will be saved as a ".wav" file with the
prefix "rec_". Filtering is off, so extracted audio data from Yaafe, 
directed by the local 'featureplan' file, and recordings are saved 
to the directory called "/home/pi/data/". All output is sent to 
stdout because background is "off".


EX 2: Consider the following config file (Audio analysis, no Filtering):
```
  [SOUNDS]
  background = on
  analysis = on
  recordingextention = .wav
  recordingduration = 5
  recordingnumber = 1
  recordingprefix = rec_
  samplerate = 44100
  datalocation = /home/pi/data/
  outputform = FV
```
One recording of duration 5 seconds at a sample rate of 44100Hz
will be made. The recording will be saved as a ".wav" file with the
prefix "rec_". These recordings are saved to
the directory called "/home/pi/data/". Filtering is NOT perfomered by
deafult because it is not turned "on". Output from YAAFE and also
goes to "home/pi/data/" directory but in the "FV" form (an audio 
file and a single json file containing all the features extracted 
with Yaafe). Everything is done in the background as a daemon.


EX 3: Consider the following config file (No audio analysis):
```
  [SOUNDS]
  recordingextention = .wav
  recordingduration = 10
  recordingnumber = 0
  recordingprefix = rec_
  samplerate = 44100
  datalocation = /home/pi/data/
```
An infinite number (doesn't stop) recordings of duration 10 seconds 
at a sample rate of 44100Hz will be made. The recording will be 
saved as a ".wav" file with the prefix "rec_" and extention ".wav".
These recordings are saved to the directory called "/home/pi/data/".
Audio analysis, sometimes called feature extraction, is NOT 
performed. Further, filtering is NOT performed as well, as it is a
subsetion of audio analysis. All output is sent to stdout because 
background is not specified.


*******************************************************************
### 4.2 FEATURE PLAN (AUDIO ANALYSIS)
*******************************************************************
The Yaafe software used for audio analysis and filtering uses a "featureplan" file to determine what to extract from a recording. Details about the available feature's in a feature plan are here:

  http://yaafe.sourceforge.net/features.html

A deafult feature plan file is already in the working directory.


*******************************************************************
#### 4.2.1 FEATURE PLAN EXAMPLE
*******************************************************************
The following are featues that you might find in a feature plan:
-  lx: Loudness
-  psp: PerceptualSpread
-  psh: PerceptualSharpness
-  ss: SpectralSlope

 
*******************************************************************
### 4.3 START RECORDING
*******************************************************************
Recordings are started after a config file is available with:
```bash
  $ ./start_sound.sh
```

*******************************************************************
### 4.4 STOP RECORDING
*******************************************************************
Recordings currently running can be halted with:
```bash
  $ ./stop_sound.sh
```
This is only necessary when an infinite number of recordings are
being made or you want to end recording early.


*******************************************************************
## 5. CLEANING UP
*******************************************************************
If the recording and analysis direcotrys needs to be cleaned up
locally then perform the following:
```bash
  $ ./cleanup_workspace.sh
```


*******************************************************************
## 6. EXAMPLE
*******************************************************************
Supposing a local config file "sound_setting.conf" already exists
with your correct settings, then perform:
```bash
  $ ./install.sh
  $ ./start_sound.sh
```


*******************************************************************
## 7. REFERENCES
*******************************************************************
Whole documentation can be found in the _Yaaraa_ "docs" directory.

Depedant libraries documention:
 * arecord
  * http://linux.die.net/man/1/arecord
  * http://www.alsa-project.org/main/index.php/Main_Page
 * YAAFE
  * yaafe.sourceforge.net


*******************************************************************
## 7. TODO
*******************************************************************
- [x] Make a TODO list, update README to markdown
- [ ] Update kill script to allow passing of a particular pid
- [ ] test filter for different features from YAAFE
- [ ] Update install script for mac? (currently only Rpi, Raspbian supported)
- [ ] Finish working filter example (consider clapping).
