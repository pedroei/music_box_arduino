/////////////////////////////////////////////////
//
// Desafio - Programação em C/Arduino C
// CMMS - MEI - Maio de 2021
// Pedro Araújo - 20780
//
/////////////////////////////////////////////////

#include <LiquidCrystal.h>

enum{
    LCD_RS = A0,
    LCD_EN = A1,
    LCD_D4 = A2,
    LCD_D5 = A3,
    LCD_D6 = A4,
    LCD_D7 = A5
};

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

#define BTN1 	2  	// Verde
#define BTN2 	3  	// Amarelo
#define BTN3 	4 	// Laranja
#define BTN4 	6 	// Castanho
#define BTN5 	7 	// Rosa

#define BTN_REC 5 	// Roxo

#define BUZZER 	11  // BUZZER

#define LED_REC 13 	// LED connected in pin 13

struct AllSongs {
  unsigned int ONE, TWO, THREE, FOUR, FIVE;
};
AllSongs all_songs[50] = {};
int count_songs = 1;
int song_to_play = 0;

int recording = 0;
int reacorded_song[100];
int count = 0;

/////////////////////////////////////////////////
// Função Setup - Inicialização
/////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  
  // Define pinos dos push buttons como entradas
  pinMode(BTN1, INPUT);
  pinMode(BTN2, INPUT);
  pinMode(BTN3, INPUT);
  pinMode(BTN4, INPUT);
  pinMode(BTN5, INPUT);
  
  pinMode(BTN_REC, INPUT);
  pinMode(LED_REC, OUTPUT);
  
  int len_all_songs = sizeof (all_songs) / sizeof (all_songs[0]);
  
  lcd.begin(16, 2);
  }

/////////////////////////////////////////////////
// Função Loop - Loop de controlo
/////////////////////////////////////////////////
void loop() {
  int state_btn1 = digitalRead(BTN1);
  int state_btn2 = digitalRead(BTN2);
  int state_btn3 = digitalRead(BTN3);
  int state_btn4 = digitalRead(BTN4);
  int state_btn5 = digitalRead(BTN5);
  
  int state_btn_rec = digitalRead(BTN_REC);
  
  if (state_btn_rec == HIGH) {
    noTone(BUZZER);
  	recording = 1;
    lcd_print_string("Recording...", 0, 0, false);
  }
  if (state_btn_rec == LOW){
  	recording = 0;
    digitalWrite(LED_REC, LOW);
    lcd_print_string("", 0, 0, true);
  }
  
  while (recording == 1) {
  	digitalWrite(LED_REC, HIGH);
    int state_btn1_rec = digitalRead(BTN1);
  	int state_btn2_rec = digitalRead(BTN2);
  	int state_btn3_rec = digitalRead(BTN3);
    
    int state_btn_stop_rec = digitalRead(BTN_REC);
    
    if (state_btn_stop_rec == HIGH){
    	noTone(BUZZER);
      	recording = 0;
      	return;
    }
    
    if (state_btn1_rec == HIGH){
    	tone(BUZZER, 4978);
      	reacorded_song[count] = 4978;
      	count++;
      	delay(300);
    	noTone(BUZZER);
    }
    if (state_btn2_rec == HIGH){
    	tone(BUZZER, 1245);
      	reacorded_song[count] = 1245;
      	count++;
      	delay(300);
    	noTone(BUZZER);
    }
    if (state_btn3_rec == HIGH){
    	tone(BUZZER, 208);
      	reacorded_song[count] = 208;
      	count++;
      	delay(300);
    	noTone(BUZZER);
    }
    
  }
  
  if (state_btn1 == HIGH) {
    tone(BUZZER, 4978);
	delay(300);
    noTone(BUZZER);
  }
  
  if (state_btn2 == HIGH) {
  	tone(BUZZER, 1245);
    delay(300);
    noTone(BUZZER);
  }
  
  if (state_btn3 == HIGH) {
  	tone(BUZZER, 208);
    delay(30);
    noTone(BUZZER);
  }
  
  if (count != 0){
	for(int i = 0; i < count; i++){
      	tone(BUZZER, reacorded_song[i]);
    /*if (count_songs != 1 && count_songs != 2 && count_songs != 3){
      	count_songs = 1;
      }*/
      if (count_songs == 1){
      	all_songs[i].ONE = reacorded_song[i];
      	Serial.println(all_songs[i].ONE);
      }
      if (count_songs == 2){
      	all_songs[i].TWO = reacorded_song[i];
      	Serial.println(all_songs[i].TWO);
      }
      if (count_songs == 3){
      	all_songs[i].THREE = reacorded_song[i];
      	Serial.println(all_songs[i].THREE);
      }
      if (count_songs == 4){
      	all_songs[i].FOUR = reacorded_song[i];
      	Serial.println(all_songs[i].FOUR);
      }
      if (count_songs == 5){
      	all_songs[i].FIVE = reacorded_song[i];
      	Serial.println(all_songs[i].FIVE);
      }
       	delay(300);
    }
    count = 0;
    count_songs++;
    if (song_to_play == 0) {song_to_play++;}
    noTone(BUZZER);
  }
  
  if (state_btn4 == HIGH) {
	playRecordedSong();
  }
  
  if (state_btn5 == HIGH) {
    song_to_play++;
    playRecordedSong();
  }
     
} 

//ADD IN EVERY FOR AN IF TO CHECK IF all_songs[j].XXX == 0
void playRecordedSong(){
    int j = 0;
    if (song_to_play >= count_songs) { 
      song_to_play = 1;
    }
    if (count_songs > 1 && song_to_play == 1) {
      int size_song = sizeof (all_songs[0].ONE) + 1;
  		for (j = 0; j < size_song; j++){      
      		tone(BUZZER, all_songs[j].ONE);
          	Serial.println(all_songs[j].ONE);
          	delay(300);
    	}
      noTone(BUZZER);
    }
    if (count_songs > 2 && song_to_play == 2) {
      int size_song = sizeof (all_songs[0].TWO) + 1;
  		for (j = 0; j < size_song; j++){      
          	delay(300);
      		tone(BUZZER, all_songs[j].TWO);
          	Serial.println(all_songs[j].TWO);
    	}
      noTone(BUZZER);
    }
    if (count_songs > 3 && song_to_play == 3) {
      int size_song = sizeof (all_songs[0].THREE) + 1;
  		for (j = 0; j < size_song; j++){ 
          	delay(300);
      		tone(BUZZER, all_songs[j].THREE);
          	Serial.println(all_songs[j].THREE);
    	}
      noTone(BUZZER);
    }
  
    if (count_songs > 4 && song_to_play == 4) {
      int size_song = sizeof (all_songs[0].FOUR) + 1;
  		for (j = 0; j < size_song; j++){ 
          	delay(300);
      		tone(BUZZER, all_songs[j].FOUR);
          	Serial.println(all_songs[j].FOUR);
    	}
      noTone(BUZZER);
    }
    if (count_songs > 5 && song_to_play == 5) {
      int size_song = sizeof (all_songs[0].FIVE) + 1;
  		for (j = 0; j < size_song; j++){ 
          	delay(300);
      		tone(BUZZER, all_songs[j].FIVE);
          	Serial.println(all_songs[j].FIVE);
    	}
      noTone(BUZZER);
    }
}

void lcd_print_string(String s, int col, int row, bool clear)
{
    if(clear)
    {
        lcd.clear();
    }

    lcd.setCursor(col, row);
    lcd.print(s);
}