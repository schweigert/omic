#include <Adafruit_GFX.h>
#include <UTFTGLUE.h>

UTFTGLUE myGLCD(0x0154,A2,A1,A3,A4,A0);

#if !defined(SmallFont)
extern uint8_t SmallFont[];
#endif


class Sound{
  int pin_sound;

  boolean is_actived;
  long avg;

 public:
  Sound(int pin){
    pin_sound = pin;
    pinMode(pin_sound, INPUT);
  }

  ~Sound(){}

  void setup(){
    for(int i = 0; i < 128; i++){
     avg+= level();
    }
    avg /= 128;
  }

  long level() {
    long sound_avr = 0;

    for(int i = 0; i < 64; i++){
      sound_avr += analogRead(pin_sound);
    }

    sound_avr /= 64;

    return sound_avr;
  }

  void work() {
    is_actived = level() > avg + 10;
  }

  boolean actived() {
     return is_actived;
  }
};
class Screen{
  public:
  Screen(){
    randomSeed(analogRead(5));
    pinMode(A0, OUTPUT);
    digitalWrite(A0, HIGH);

    myGLCD.InitLCD();
    myGLCD.setFont(SmallFont);
  }

  ~Screen(){
    myGLCD.clrScr();
  }

  void clear(){
    myGLCD.clrScr();
  }

  void write_on_center(char* txt, int height){
    myGLCD.print(txt, CENTER, height);
  }

  void draw_pixel(int x, int y){
    myGLCD.drawPixel(x,y);
  }

  void draw_row(int row, int start, int ends){
    for(int i = start; i <= ends; i++){
      draw_pixel(i,row);
    }
  }

  void use_color(int r, int g, int b){
    myGLCD.setColor(r,g,b);
  }

  void write_title(char* txt){
    this->use_color(255,40,40);
    this->write_on_center(txt, 5);
  }
};
class Dinossaur{
  private:
    Screen* screen;

    boolean jumping;
    int     jumping_time;

    int x,y,frame;

  public:
    Dinossaur(Screen* s){
     this->screen = s;
     this->x = 0;
     this->y = 200;

     this->jumping = false;
    }

    int get_x(){return x;}
    int get_y(){return y;}

    void translate(int x, int y){
      this->undraw();
      this->x += x;
      this->y += y;
      this->x %= 320;
      this->y %= 240;
    }

    void mask(){
      screen->draw_row(1+y,12+x,19+x);
      screen->draw_row(2+y,11+x,12+x);
      screen->draw_row(2+y,15+x,20+x);
      screen->draw_row(3+y,11+x,12+x);
      screen->draw_row(3+y,15+x,20+x);
      screen->draw_row(4+y,11+x,20+x);
      screen->draw_row(5+y,11+x,20+x);
      screen->draw_row(6+y,11+x,13+x);
      screen->draw_row(7+y,11+x,13+x);
      screen->draw_row(8+y,10+x,17+x);
      screen->draw_row(9+y,10+x,17+x);
      screen->draw_row(10+y,7+x,12+x);
      screen->draw_row(11+y,6+x,15+x);
      screen->draw_row(12+y,0+x,11+x);
      screen->draw_row(12+y,15+x,15+x);
      screen->draw_row(13+y,0+x,11+x);
      screen->draw_row(14+y,0+x,11+x);
      screen->draw_row(15+y,1+x,11+x);
      screen->draw_row(16+y,2+x,10+x);
      screen->draw_row(17+y,3+x,5+x);
      screen->draw_row(17+y,8+x,9+x);
      screen->draw_row(18+y,3+x,4+x);
      screen->draw_row(18+y,9+x,9+x);
      screen->draw_row(11+y,0+x,3+x);
      screen->draw_row(10+y,0+x,2+x);
      screen->draw_row(9+y,0+x,1+x);
      screen->draw_row(8+y,0+x,0+x);
      screen->draw_row(7+y,0+x,0+x);

      if(frame == 0){
       screen->draw_row(19+y,10+x,10+x);
       screen->draw_row(20+y,10+x,11+x);
       screen->draw_row(19+y,3+x,3+x);
       screen->draw_row(20+y,3+x,4+x);
      } else {
       screen->draw_row(19+y,8+x,8+x);
       screen->draw_row(20+y,8+x,9+x);
       screen->draw_row(19+y,5+x,5+x);
       screen->draw_row(20+y,5+x,6+x);
      }
    }

    void draw(){
      screen->use_color(255,255,255);
      if(jumping){
       if(jumping_time == 5) y = 190;
       if(jumping_time == 4) y = 180;
       if(jumping_time == 3) y = 180;
       if(jumping_time == 2) y = 185;
       if(jumping_time == 1) y = 190;
      }else{
       y = 200;
       frame++;
       frame %= 2;
      }
      mask();
    }

    void undraw(){
      screen->use_color(0,0,0);
      mask();
    }

    boolean get_jumping(){return jumping;}

    void jump(){
      if(jumping)
        return;

      jumping = true;
      jumping_time = 0;
    }

    void work(){
     if(jumping){
       jumping_time++;
     }

     if(jumping_time >= 6){
      jumping_time = 0;
      jumping = false;
     }
    }
};
class Terrain {
  private:
    Screen* screen;

  public:
  Terrain(Screen* s){
    this->screen = screen;
  }

  void mask(){
   for(int i = 0; i < 320; i+= 2){
    screen->draw_pixel(i,221);
    screen->draw_pixel(i+1,222);
    screen->draw_pixel(i+2,223);
   }
   for(int i = 0; i < 320; i+= 4){
    screen->draw_pixel(i,223);
    screen->draw_pixel(i+1,224);
    screen->draw_pixel(i+2,225);
   }
   for(int i = 0; i < 320; i+= 6){
    screen->draw_pixel(i,225);
    screen->draw_pixel(i+1,226);
    screen->draw_pixel(i+2,227);
   }
   for(int i = 0; i < 320; i+= 8){
    screen->draw_pixel(i,227);
    screen->draw_pixel(i+1,228);
    screen->draw_pixel(i+2,228);
   }
   for(int i = 0; i < 320; i+= 10){
    screen->draw_pixel(i,229);
    screen->draw_pixel(i+1,230);
    screen->draw_pixel(i+2,231);
   }
   for(int i = 0; i < 320; i+= 12){
    screen->draw_pixel(i,231);
    screen->draw_pixel(i+1,232);
    screen->draw_pixel(i+2,233);
   }
   for(int i = 0; i < 320; i+= 14){
    screen->draw_pixel(i,233);
    screen->draw_pixel(i+1,234);
    screen->draw_pixel(i+2,235);
   }
   for(int i = 0; i < 320; i+= 16){
    screen->draw_pixel(i,235);
    screen->draw_pixel(i+1,236);
    screen->draw_pixel(i+2,237);
   }
   for(int i = 0; i < 320; i+= 18){
    screen->draw_pixel(i,237);
    screen->draw_pixel(i+1,238);
    screen->draw_pixel(i+2,239);
   }
   for(int i = 0; i < 320; i+= 20){
    screen->draw_pixel(i,239);
    screen->draw_pixel(i+1,240);
    screen->draw_pixel(i+2,241);
   }
  }

  void draw(){
   screen->use_color(0,80,0);
   mask();
  }

  void undraw(){
    screen->use_color(0,0,0);
    mask();
  }
};
class Obstacle{
private:
  int x, y;
  Screen* screen;
public:
  Obstacle(Screen* screen){
    this->screen = screen;

    this->x = 160;
    this->y = 210;
  }

  void mask(){
    screen->draw_row(0+y,0+x,10+x);
    screen->draw_row(1+y,0+x,10+x);
    screen->draw_row(2+y,0+x,10+x);
    screen->draw_row(3+y,1+x,1+x);
    screen->draw_row(3+y,9+x,9+x);
    screen->draw_row(4+y,1+x,1+x);
    screen->draw_row(4+y,9+x,9+x);
    screen->draw_row(5+y,1+x,1+x);
    screen->draw_row(5+y,9+x,9+x);
    screen->draw_row(6+y,1+x,1+x);
    screen->draw_row(6+y,9+x,9+x);
    screen->draw_row(7+y,1+x,1+x);
    screen->draw_row(7+y,9+x,9+x);
    screen->draw_row(8+y,1+x,1+x);
    screen->draw_row(8+y,9+x,9+x);
    screen->draw_row(9+y,1+x,1+x);
    screen->draw_row(9+y,9+x,9+x);
  }

  void draw(){
    screen->use_color(255,150,70);
    mask();
  }

  void undraw(){
    screen->use_color(0,0,0);
    mask();
  }
};

class Game
{
  private:
    Sound* sound;
    Screen* screen;

    Terrain* terrain;
    Dinossaur* dinossaur;
    Obstacle* obstacle;

    boolean active_loop;
  public:
    Game(){
      this->sound = new Sound(A9);
      this->screen = new Screen();

      this->active_loop = true;

      this->terrain = new Terrain(this->screen);
      this->dinossaur = new Dinossaur(this->screen);
      this->obstacle = new Obstacle(this->screen);

      this->speed_x = 3;
    }

    ~Game(){
      delete sound;
      delete screen;

      delete terrain;
      delete dinossaur;
      delete obstacle;
    }

    void start(){
      screen->clear();
      screen->write_title("Acrean Olympics");

      terrain->draw();
      dinossaur->draw();
      obstacle->draw();

      sound->setup();
      while(active_loop){
        this->sound->work();
        this->loop();
      }
    }

    int old_x;

    boolean has_changed_scene(){
      boolean r = dinossaur->get_x() < old_x;
      old_x = dinossaur->get_x();
      return r;
    }

    boolean is_colliding(){
      if(!dinossaur->get_jumping() && dinossaur->get_x() >= 160 && dinossaur->get_x() <= 170){
        return true;
      }
      return false;
    }

    int speed_x;
    void loop(){

       dinossaur->translate(speed_x,0);


       if(has_changed_scene() && speed_x < 100)
         speed_x++;

       dinossaur->work();
       if(sound->actived()){
        dinossaur->jump();
       }

       dinossaur->draw();
       obstacle->draw();

       if(is_colliding()){
         finish();
       }
   }

   void finish(){
    active_loop = false;
    screen->use_color(255,0,0);
    for(int i = 0; i < 320; i++){
      for(int j = 0; j < 240; j++){
        if(i%2 == 0 && j%2 == 0 && !(i >= 66 && i <= 254 && j >= 70 && j <= 150))
          screen->draw_pixel(i,j);
      }
    }
    screen->use_color(255,255,255);
    speed_x -= 3;
    if(speed_x <= 3){
     screen->write_on_center("Acertou, desgracado", 80);
    } else if(speed_x <= 4){
     screen->write_on_center("Carai, eu sou um merda mermao", 80);
    } else if(speed_x <= 8){
     screen->write_on_center("Irineu, voce nao sabe nem eu", 80);
    }else if(speed_x <= 10){
     screen->write_on_center("Juliana???", 80);
    } else {
     screen->write_on_center("QUERO CAFEEEEEEEEEEEEEEEEEEE", 80);
    }
    screen->write_on_center("Score:", 100);
    char snum[5];
    itoa(speed_x, snum, 10);
    screen->write_on_center(snum,130);

    delay(10000);
   }

};

Game* game;

void setup() {
  Serial.begin(9600);
}

void loop() {
  game = new Game();
  game->start();
  delete game;
}
