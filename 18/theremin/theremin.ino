
#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

#define RECMAXLEN 500
#define SAMPLE 10

char ldrPin = A0;
char speakerPin = 9;
char ledRed = 2, ledGreen = 4;
double gap = 1.148698355;

short record[RECMAXLEN];
short recordLen = 0;
short playPosition = 0;
long  lastProbe = 0; // millis

char btnRecord = 7, btnPlay = 8;
char btnSetFreq = 6;
char btnRecordState = LOW,
     btnPlayState = LOW,
     btnSetFreqState = LOW;

/* Modes: 0 -> normal, 1 -> playing */
char mode = 0;
char doRecord = 0; 

short ldrMin = 1000;
short ldrMax = 0;
short freqMin = 131;
short freqMax = 1048;

double factor  = 0;
double shift = 0;

double normf, logf;
int ilogf;
short i, ldrRead, freq, btnRead;
long probe;

void setup()
{
    pinMode(speakerPin, OUTPUT);
    pinMode(ledRed, OUTPUT);
    pinMode(ledGreen, OUTPUT);
    
    /* Calibration loop: determine resonable min/max
       values of LDR reads and map them to frequencies. */
    /*digitalWrite(ledRed, HIGH);
    for (i = 0; i < 500; ++i) {         // takes 5 seconds
        ldrRead = analogRead(ldrPin);
        tone(speakerPin, ldrRead);      // raw tone, calibration helper
        ldrMax = MAX(ldrRead, ldrMax);
        ldrMin = MIN(ldrRead, ldrMin);
        delay(10);
    }
    digitalWrite(ledRed, LOW);*/
    
    // turn of auto-tune
    ldrMax = 1000;
    ldrMin = 0;
    
    factor = (double)(freqMax - freqMin) / (double)(ldrMax - ldrMin); 
    shift = factor * ldrMin - freqMin;
}

inline void setMode(char m)
{
    mode = m;
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, LOW);
}

inline void startRecording(void) 
{
    lastProbe = 0;
    recordLen = 0;
    doRecord = 1;
    
    digitalWrite(ledRed, HIGH);
}

inline void stopRecording(void) 
{
    doRecord = 0;
    digitalWrite(ledRed, LOW);
} 

inline void startPlaying(void)
{
    lastProbe = 0;
    doRecord = 0;
    playPosition = 0;
    digitalWrite(ledGreen, HIGH);
}

inline void stopPlaying()
{
    setMode(0);
}

void loop()
{
    /* Check buttons */
    btnRead = digitalRead(btnRecord);
    if (btnRead != btnRecordState) {  // event: record button state has changed
        btnRecordState = btnRead;
        
        if (btnRecordState == HIGH) { // event: record button has been pressed
            setMode(0);               // force normal/recording mode
            if (doRecord == 1)        // if already recording, turn of
                stopRecording();
            else                      // otherwise start recording
                startRecording();
        }
    }
    
    btnRead = digitalRead(btnPlay);
    if (btnRead != btnPlayState) {    // event: play button state has changed
        btnPlayState = btnRead;
        
        if (btnPlayState == HIGH) {   // event: play button has been pressed         
            setMode(1);
            startPlaying();
        }
    }
    
    btnRead = digitalRead(btnSetFreq);
    if (btnRead != btnSetFreqState) {  // event: minfreq button state has changed
        btnSetFreqState = btnRead;
      
        if (btnSetFreqState == HIGH && mode == 0) {  // event: minfreq button state has been pressed
            ldrRead = analogRead(ldrPin);
            ldrMin = ldrRead;
            
            factor = (double)(freqMax - freqMin) / (double)(ldrMax - ldrMin); 
            shift = factor * ldrMin - freqMin;        
        }  
    }

    if (mode == 0) {
        ldrRead = analogRead(ldrPin);
        freq = factor * ldrRead - shift;
        
        /* Round frequency to the nearest note.
           Uses pentathonic scale: CDEGAC, 
           note_freq(n) = C * sqrt(5)^(n)  */
        normf = freq / (double)freqMin;
        logf = log(normf) / log(gap);
        ilogf = round(logf);
        freq = freqMin * pow(gap, ilogf);
        
        if (doRecord == 1) {
            probe = millis();
            if (probe - lastProbe > SAMPLE) {
                if (recordLen < RECMAXLEN) {
                    lastProbe = probe;
                    record[recordLen++] = freq;
                } else {
                    stopRecording();
                }
            }
        }
        
        tone(speakerPin, freq);
    }
    
    if (mode == 1) {
        //Serial.print(playPosition); Serial.print("  "); Serial.println(recordLen);
        if (playPosition < recordLen) {
            tone(speakerPin, record[playPosition]);
            probe = millis();
            if (probe - lastProbe > SAMPLE) {
                lastProbe = probe;
                ++playPosition;
            }
        } else {
            stopPlaying();
        }  
    }
}
