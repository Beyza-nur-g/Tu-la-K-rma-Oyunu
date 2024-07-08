#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TM1637TinyDisplay.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUTTON_PIN_SELECT 4   // Seçeneği onaylamak için düğme pini
#define BUTTON_PIN_COLOR_CHANGE 6 // Renk değiştirme butonu pini


#define LED1 7
#define LED2 8
#define LED3 9

#define CLK 2 // CLK pinini tanımlayın
#define DIO 3 // DIO pinini tanımlayın
TM1637TinyDisplay scoredisplay(CLK, DIO);

#define YELLOW 0xFFFF00 // Sarı renk RGB formatında

#define brickRows 4
#define brickCols 6
int brickWidth = 17;
int brickHeight = 13;
int brickGap = 2;
bool bricks[brickRows][brickCols];
int score = 0; // Puan değişkeni

// Oyun değişkenleri
unsigned long timeNow;
unsigned long interval = 250;
int paddleX;
int paddleY = 60;
int paddleWidth = 30;
int paddleHeight = 2;
int ballX = 64;
int ballY = 32;
int ballSpeedX = 2;
int ballSpeedY = 2;
int lives = 3;
int ledPins[] = {2, 3, 4};
int paddleHitRange = 5;
bool gameRunning = false;
bool heartActive = false;
int heartX =0;
int heartY =0;
bool buttonNavigatePressed = false; 
bool buttonSelectPressed = false;

bool colorChangeButtonState = false; // Renk değiştirme butonunun durumu
int brokenBrickX;
int brokenBrickY;
void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(BUTTON_PIN_SELECT, HIGH);
   digitalWrite(BUTTON_PIN_COLOR_CHANGE, HIGH);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 ekran başlatılamadı"));
    for(;;);
  }

  paddleX = (SCREEN_WIDTH - paddleWidth) / 2;

  timeNow = millis();
  Serial.println(" Hoş Geldiniz!\n3 Canınız Var.");
  for(int i=3;i>=0;i--){
    Serial.println(i);
    delay(1000);
  }
  Serial.println("Başlıyoruz!");
   for (int i = 0; i < brickRows; i++) {
    for (int j = 0; j < brickCols; j++) {
      bricks[i][j] = true; // Tüm tuğlaları başlangıçta var olarak işaretle
    }
  }
  scoredisplay.setBrightness(0x0a);
  scoredisplay.showNumberDec(score, false);
}

void loop() {
  int potValue = analogRead(A0);
   colorChangeButtonState = digitalRead(BUTTON_PIN_COLOR_CHANGE);
  if(!gameRunning){
  int menuOption = map(potValue, 0, 1023, 1, 2); // Potansiyometre değerini menü seçeneklerine dönüştür (1: START, 2: EXIT)
  
  // Düğmeye basıldığında menü seçeneğine göre işlem yap
  gameMenu(menuOption);

  // Düğmeye basıldığında menü seçeneğine göre işlem yap
  int buttonSelectState = digitalRead(BUTTON_PIN_SELECT);
  if (buttonSelectState == LOW) {
    if (menuOption == 1) {
      startGame(); // START seçeneği ise oyunu başlat
    } else if (menuOption == 2) {
      exitGame(); // EXIT seçeneği ise programdan çık
    }
  }

  delay(100); // Kararlılık için kısa bir gecikme 
  }
  if (gameRunning) {
     paddleX = map(potValue, 0, 1023, 0, SCREEN_WIDTH - paddleWidth);
    display.clearDisplay();
    drawGame();
    ballX += ballSpeedX;
    ballY += ballSpeedY;
    if (ballX <= 0 || ballX >= SCREEN_WIDTH - 1) {
      ballSpeedX = -ballSpeedX;
    }
    if (ballY <= 0 || ballY >= SCREEN_HEIGHT - 1) {
      ballSpeedY = -ballSpeedY;
    }

    if (ballY >= paddleY - paddleHitRange && ballX >= paddleX && ballX <= paddleX + paddleWidth) {
      ballSpeedY = -abs(ballSpeedY);
      ballSpeedX = random(-1, 2);
    }
    for (int i = 0; i < brickRows; i++) {
  for (int j = 0; j < brickCols; j++) {
    if (bricks[i][j]) {
      int brickX = j * (brickWidth + brickGap);
      int brickY = i * (brickHeight + brickGap);
      
      // Tuğla ve topun çarpışmasını kontrol et
      if (ballX >= brickX && ballX <= brickX + brickWidth && ballY >= brickY && ballY <= brickY + brickHeight) {
        // Top tuğlaya çarptı
        bricks[i][j] = false; // Tuğlayı kaldır
        
        score += 1; // Puanı artır
       ballSpeedY = abs(ballSpeedY); 
       ballSpeedX = random(-1, 2);// Topun yönünü değiştir
       // Kalp düşürme mekanizması
      if (score % 5 == 0 && score != 0 && !heartActive) {
        heartX = brickX + (brickWidth /2); 
        heartY = brickY + (brickHeight /2); 
        heartActive = true; 
      }
         break; // İç döngüden çık
      }
    }
  }
  }
  if (heartActive) {
      // Kalp düşme mekanizması
      heartY += 1; // Kalp yalnızca dikey olarak aşağıya düşer
      if (heartY >= SCREEN_HEIGHT - 1  ) {
        // Kalp ekranın altına düştüğünde
        heartActive = false;
      }

      // Kalp çarpışma kontrolü
      if (heartX >= paddleX && heartX <= paddleX + paddleWidth && heartY >= paddleY && heartY <= paddleY + paddleHeight) {
        if (lives < 3) {
          lives++; // Kalbi yakaladık, canı artır
        }
        heartActive = false; // Kalbi devre dışı bırak
      }
    }
    if (ballY >= SCREEN_HEIGHT - 1) {
      lives--;
      if (lives <= 0) {
        gameRunning = false;
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(16,16);
        display.print("Oyun Bitti!");
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(16,40);
        display.print("Scor :");
        display.print(score);
        score=0;
        display.display();
        delay(3000);
      } else {
        ballX = 64;
        ballY = 32;
        display.clearDisplay();
        drawGame();
        delay(2000);
      }
    }

    if (lives == 3) {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
    } else if (lives == 2) {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, LOW);
    } else if (lives == 1) {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
    } else {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
    }
    scoredisplay.showNumberDec(score, false); 
    delay(10);

    bool allBricksBroken = true;
    for (int i = 0; i < brickRows; i++) {
      for (int j = 0; j < brickCols; j++) {
        if (bricks[i][j]) {
          allBricksBroken = false;
          break;
        }
      }
      if (!allBricksBroken) break;
    }

    if (allBricksBroken) {
      // Bütün tuğlalar kırıldıysa, yeni seviyeye geç
      advanceToNextLevel();
    }

  }
}

void drawGame() {
   uint16_t backgroundColor = colorChangeButtonState ? BLACK : WHITE; // Ekranın zemin rengini belirle

  display.clearDisplay();
  display.fillScreen(backgroundColor); // Ekranın zemin rengini ayarla
  uint16_t objectColor = colorChangeButtonState ? WHITE : BLACK; // Nesne rengini belirle
  // Tuğlaları, paleti ve topu ekrana çizme
  for (int i = 0; i < brickRows; i++) {
    for (int j = 0; j < brickCols; j++) {
      if (bricks[i][j]) {
        int brickX = j * (brickWidth + brickGap);
        int brickY = i * (brickHeight + brickGap);
        display.fillRect(brickX, brickY, brickWidth, brickHeight, objectColor); // Tuğlanın rengini ekranın zemin rengi olarak belirle
      }
    }
  }
  // Top ve paleti ekrana çizme
  display.fillCircle(ballX, ballY, 2, objectColor);
  display.drawRect(paddleX, paddleY, paddleWidth, paddleHeight, objectColor);
  if (heartActive) {
    display.fillCircle(heartX, heartY, 2, objectColor);
  }

  // Ekrana çizilen nesneleri gösterme
  display.display();
}


void advanceToNextLevel() {
  // Yeni seviyeye geçiş işlemleri
  // Tuğla boyutlarını küçült
  brickWidth -= 3;
  brickHeight -= 3;

  brickGap +=4;
  // Top hızını artır
  ballSpeedX += 1;
  ballSpeedY += 1;

  // Yeni seviye yazısını ekrana yazdır
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(16, 16);
  display.print("Yeni Seviye !");
  display.display();
  delay(2000);

  // Yeni seviye başlat
  resetGame();
  lives = 3;
  ballX = 64;
  ballY = 32;
  gameRunning = true;
}

void resetGame() {
  // Oyun değişkenlerini başlangıç değerlerine geri yükle
  for (int i = 0; i < brickRows; i++) {
    for (int j = 0; j <brickCols; j++) {
      bricks[i][j] = true; // Tüm tuğlaları başlangıçta var olarak işaretle
      if (random(10) < 3) { 
        bricks[i][j] = false;
      }    
    }
  }
 
}

void gameMenu(int selectedOption) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(16, 8);
  display.print("Block Shooter");

  // Menü seçeneklerini ekrana yaz
  display.setCursor(16, 24);
  display.print(selectedOption == 1 ? ">" : " ");
  display.print("1 - START");

  display.setCursor(16, 40);
  display.print(selectedOption == 2 ? ">" : " ");
  display.print("2 - EXIT");

  display.display();
}

void startGame() {
  gameRunning = true;
  lives = 3;
  ballX = 64;
  ballY = 32;
  ballSpeedX = 2;
  ballSpeedY = 2;
  brickWidth = 17;
  brickHeight = 13;
  brickGap = 2;
  heartX =0;
  heartY =0;
  heartActive = false;
  buttonNavigatePressed = false; 
  buttonSelectPressed = false;
  resetGame();
}

void exitGame() {
  gameRunning = false;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(16, 16);
  display.print("Oyun Durduruldu");
  display.display();
  delay(2000);
}