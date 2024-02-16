#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

float Scale_w = 1.5;
int Width_w = 500*Scale_w;
int Lenght_w = 500*Scale_w;
int status = 0;

bool cheat = false;

RenderWindow app(VideoMode(Width_w, Lenght_w), "MORNING WOOD");

int Tree_Branch[100];

class Tree{
    public:
        int Xmin_t;
        int Ymin_t;

        Texture texture_t;
        Sprite sprite_t;

        Tree(){
            Xmin_t = 225*Scale_w;
            Ymin_t = 360*Scale_w;

            texture_t.loadFromFile("data/images/tree-status-sheet.png");
            sprite_t.setTexture(texture_t);
        }

        void display(){
            for(int i=0; i<9; i++){
                int sli = 0;
                if(Tree_Branch[i]==0){
                    sprite_t.setTextureRect(IntRect(125, 0, 50, 60));
                }
                else if(Tree_Branch[i]==1){
                    sprite_t.setTextureRect(IntRect(125, 60, 150, 60));
                }
                else if(Tree_Branch[i]==-1){
                    sprite_t.setTextureRect(IntRect(25, 120, 150, 60));
                    sli = 100*Scale_w;
                }
                sprite_t.setScale(Scale_w, Scale_w);
                sprite_t.setPosition(Xmin_t-sli, Ymin_t-(i*60*Scale_w));
                app.draw(sprite_t);
            }
        }

};
class Tree T;

class Player{
    public:
        int Xmin_p;
        int Ymin_p;
        int Side;

        bool Dead, Hit, Parry, Duck;

        Texture texture_p;
        Sprite sprite_p;

        int Frame;
        Clock animationTimer;

        Player(){
            Ymin_p = 372*Scale_w;
            Side = -1;

            texture_p.loadFromFile("data/images/lumberjack-sprite-sheet.png");
            sprite_p.setTexture(texture_p);

            Frame = 0;
            animationTimer.restart();
        }

        void refresh(){
            Dead = false;
            Hit = false;
            Parry = false;
            Duck = false;
        }

        void display(){
            if(animationTimer.getElapsedTime().asSeconds() >= 0.25f){
                Frame += 50.f;
                if(Frame >= 200.f){
                    Frame = 0;
                }
                animationTimer.restart();
            }
            if(Dead){
                if(Side==-1){
                    Xmin_p = 175*Scale_w;
                }
                else if(Side==1){
                    Xmin_p = 275*Scale_w;
                }
                sprite_p.setTextureRect(IntRect(Frame, 400, 50, 50));
            }
            else if(Hit){
                if(Side==-1){
                    Xmin_p = 175*Scale_w;
                    sprite_p.setTextureRect(IntRect(Frame, 100, 50, 50));
                }
                else if(Side==1){
                    Xmin_p = 275*Scale_w;
                    sprite_p.setTextureRect(IntRect(Frame, 150, 50, 50));
                }
            }
            else if(Parry){
                if(Side==-1){
                    Xmin_p = 175*Scale_w;
                    sprite_p.setTextureRect(IntRect(Frame, 200, 50, 50));
                }
                else if(Side==1){
                    Xmin_p = 275*Scale_w;
                    sprite_p.setTextureRect(IntRect(Frame, 250, 50, 50));
                }

            }
            else if(Duck){
                if(Side==-1){
                    Xmin_p = 175*Scale_w;
                    sprite_p.setTextureRect(IntRect(Frame, 300, 50, 50));
                }
                else if(Side==1){
                    Xmin_p = 275*Scale_w;
                    sprite_p.setTextureRect(IntRect(Frame, 350, 50, 50));
                }

            }
            else if((!Dead) && (!Hit) && (!Parry) && (!Duck)){
                if(Side==-1){
                    Xmin_p = 175*Scale_w;
                    sprite_p.setTextureRect(IntRect(Frame, 0, 50, 50));
                }
                else if(Side==1){
                    Xmin_p = 275*Scale_w;
                    sprite_p.setTextureRect(IntRect(Frame, 50, 50, 50));
                }
            }
            sprite_p.setScale(Scale_w, Scale_w);
            sprite_p.setPosition(Xmin_p, Ymin_p);
            app.draw(sprite_p);
        }
};
class Player P;

class Bee{
    public:
        int Xmin_b;
        int Ymin_b;
        int Side;
        int Hive;

        float x;

        bool Move, Play;

        Texture texture_b;
        Sprite sprite_b;

        int Frame;
        Clock animationTimer;
        Clock beeCooldown;

        SoundBuffer BeeBuffer;
        SoundBuffer AttackBuffer;
        Sound BeeSound;
        Sound AttackSound;

        Bee(){
            Ymin_b = 272*Scale_w;
            Side = rand()%2;
            if(Side==0){
                Side = -1;
            }
            Hive = 30;

            Move = false;
            Play = false;

            texture_b.loadFromFile("data/images/bee-sprite-sheet.png");
            sprite_b.setTexture(texture_b);

            BeeBuffer.loadFromFile("data/audios/bee-buzz.wav");
            AttackBuffer.loadFromFile("data/audios/bee-sting.wav");
            BeeSound.setBuffer(BeeBuffer);
            AttackSound.setBuffer(AttackBuffer);

            Frame = 0;
            animationTimer.restart();
            beeCooldown.restart();
        }

        void respawn(){
            Ymin_b = 272*Scale_w;
            Side = rand()%2;
            if(Side==0){
                Side = -1;
            }
            Hive = 30;
            Play = false;
        }

        void soundfx(){
            if(Hive==0){
                BeeSound.play();
                Hive--;
            }
            if((Ymin_b>=273*Scale_w) && (!Play)){
                AttackSound.play();
                Play = true;
            }
        }

        void display(){
            if(Hive<=0){
                soundfx();
                if(beeCooldown.getElapsedTime().asSeconds() >= 3.f){
                    if(Side==-1){
                        sprite_b.setTextureRect(IntRect(50, 0, 50, 50));
                        Xmin_b +=5*Scale_w;
                    }
                    else if(Side==1){
                        sprite_b.setTextureRect(IntRect(50, 50, 50, 50));
                        Xmin_b -=5*Scale_w;
                    }
                    Ymin_b +=5*Scale_w;
                    sprite_b.setPosition(Xmin_b, Ymin_b);
                    app.draw(sprite_b);
                    if(Ymin_b>=372*Scale_w){
                        respawn();
                    }
                }
                else{
                    if(animationTimer.getElapsedTime().asSeconds() >= 0.15f){
                        Frame += 50.f;
                        if(Frame >= 200.f){
                            Frame = 0;
                        }
                        animationTimer.restart();
                    }
                    if(Side==-1){
                        Xmin_b = 75*Scale_w;
                        sprite_b.setTextureRect(IntRect(Frame, 0, 50, 50));
                    }
                    else if(Side==1){
                        Xmin_b = 375*Scale_w;
                        sprite_b.setTextureRect(IntRect(Frame, 50, 50, 50));
                    }
                    sprite_b.setScale(Scale_w, Scale_w);
                    sprite_b.setPosition(Xmin_b, Ymin_b);
                    app.draw(sprite_b);
                }
            }
            else{
                beeCooldown.restart();
            }
        }
};
class Bee B;

class Countdown{
    public:
        float Bar = 4*Scale_w*15;
        Clock timer;

        void restart(){
            Bar = 4*Scale_w*15;
            timer.restart();
        }

        float limiter(){
            if(Bar >= 4*Scale_w*15){
                Bar = 4*Scale_w*15;
            }
            else if(Bar <= 0){
                Bar = 0;
            }
            return Bar;
        }

        float bonus(){
            Bar = Bar + 4*Scale_w;
            limiter();
            timer.restart();

            return Bar;
        }

        void display(){
            if(timer.getElapsedTime().asSeconds() >= 0.1f){
                Bar -= 2*Scale_w;
                limiter();
                timer.restart();
            }
            RectangleShape shape(Vector2f(Bar, 15*Scale_w));
            shape.setPosition(Width_w/100, Lenght_w/20);
            shape.setFillColor(Color(0, 200, 35));
            app.draw(shape);
        }
};
class Countdown C;

void background(){
    Texture texture_b;
    texture_b.loadFromFile("data/images/background.png");
    Sprite sprite_b;
    sprite_b.setTexture(texture_b);
    sprite_b.setScale(Scale_w, Scale_w);
    app.draw(sprite_b);
}

void text(int status, int score){
    Font font;
    font.loadFromFile("data/fonts/INTTERNO.otf");

    Text text1;
    Text text2;

    text1.setFont(font);
    text2.setFont(font);

    Text score_t;
    score_t.setFont(font);
    stringstream ss;
    ss << score;
    string score_s;
    ss >> score_s;
    score_t.setString(score_s);

    if(status==-1){
        text1.setString("GAME OVER");
        text1.setCharacterSize(60*Scale_w);
        text1.setColor(Color(170, 20, 24));
        text1.setPosition(Width_w/4, Lenght_w/4);
        app.draw(text1);

        text2.setString("YOUR SCORE: ");
        text2.setCharacterSize(20*Scale_w);
        text2.setPosition(Width_w/3, Lenght_w/2.5);
        app.draw(text2);

        score_t.setCharacterSize(20*Scale_w);
        score_t.setPosition(Width_w/3 + 110*Scale_w, Lenght_w/2.5);
        app.draw(score_t);
    }
    else if(status==0){
        text1.setString("MORNING WOOD");
        text1.setCharacterSize(80*Scale_w);
        text1.setColor(Color(250, 193, 35));
        text1.setPosition(Width_w/12, Lenght_w/5);
        app.draw(text1);

        text2.setString("Press ENTER to Start");
        text2.setCharacterSize(25*Scale_w);
        text2.setPosition(Width_w/3.3, Lenght_w/1.1);
        app.draw(text2);
    }
    else if(status==1){
        text1.setString("SCORE: ");
        text1.setCharacterSize(15*Scale_w);
        text1.setPosition(Width_w/100, Lenght_w/100);
        app.draw(text1);

        if(cheat){
            text2.setString("CHEAT IS ACTIVE");
            text2.setCharacterSize(15*Scale_w);
            text2.setPosition(Width_w/100, Lenght_w/1.05);
            app.draw(text2);
        }

        score_t.setCharacterSize(15*Scale_w);
        score_t.setPosition(Width_w/100 + 40*Scale_w, Lenght_w/100);
        app.draw(score_t);
    }
}

void reset(){
    for(int i=0; i<100; i++){
        Tree_Branch[i] = 0;
    }
    B.respawn();
}

void reduced(){
    for(int i=0; i<100; i++){
        Tree_Branch[i] = Tree_Branch[i+1];
    }
    B.Hive--;
}

void extend(){
    for(int i=0; i<100; i++){
        if((Tree_Branch[i]==1)&&(Tree_Branch[i+1]==-1)){
            int temp = i+1;
            for(int j=99; j>temp; j--){
                Tree_Branch[j] = Tree_Branch[j-1];
            }
            Tree_Branch[temp] = 0;
        }
        if((Tree_Branch[i]==-1)&&(Tree_Branch[i+1]==1)){
            int temp = i+1;
            for(int j=99; j>temp; j--){
                Tree_Branch[j] = Tree_Branch[j-1];
            }
            Tree_Branch[temp] = 0;
        }
    }
}

void randomize(){
    for(int i=2; i<100; i++){
        int Bloc = rand()%3;
        Tree_Branch[i] = Bloc-1;
    }
    extend();
}

int newChunks(int chunks){
    if(chunks==50){
        for(int i=chunks; i<100; i++){
            int Bloc = rand()%3;
            Tree_Branch[i] = Bloc-1;
        }
        extend();
        chunks = 0;
    }
    return chunks;
}

bool survive(){
    if(cheat){
        return 1;
    }
    else if((P.Side==-1) &&(Tree_Branch[0]==-1)){
        return 0;
    }
    else if((P.Side==1) && (Tree_Branch[0]==1)){
        return 0;
    }
    else if(C.Bar==0){
        return 0;
    }
    else if((P.Side==B.Side) && (B.Ymin_b>=352*Scale_w)){
        if(!P.Parry){
            return 0;
        }
        B.respawn();
    }
    return 1;
}

int main(){
    app.setFramerateLimit(60);

    bool Kpress, Krelease;

    int chunks = 0;
    int score = 0;

    SoundBuffer buffer;
    buffer.loadFromFile("data/audios/axe-chop.wav");
    Sound sound;
    sound.setBuffer(buffer);

	// Start the game loop
    while(app.isOpen()){
        // Game Over
        while(status==-1){
            // Process events
            Event event;
            while(app.pollEvent(event)){
                // Close window : exit
                if(event.type == Event::Closed)
                    app.close();
            }

            // Clear screen
            app.clear();
            B.BeeSound.stop();
            B.AttackSound.stop();

            // Draw the sprites
            background();
            T.display();
            P.Dead = true;
            P.display();
            B.respawn();
            text(status, score);

            // Controls
            if(Keyboard::isKeyPressed(Keyboard::Escape)){
                Kpress = true;
                if((Kpress) && (Krelease)){
                    status = 0;
                    Krelease = false;
                }
            }
            else if(Keyboard::isKeyPressed(Keyboard::R)){
                Kpress = true;
                if((Kpress) && (Krelease)){
                    status = 1;
                    chunks = 0;
                    score = 0;
                    randomize();
                    Tree_Branch[0] = 0;
                    Tree_Branch[1] = 0;
                    Krelease = false;
                }
            }
            else if(Keyboard::isKeyPressed(Keyboard::C)){
                Kpress = true;
                if((Kpress) && (Krelease)){
                    if(cheat){
                        cheat = false;
                    }
                    else cheat = true;
                    Krelease = false;
                }
            }
            else{
                Kpress = false;
                Krelease = true;
                P.refresh();
            }

            // Update the window
            app.display();
            C.restart();
        }

        // Game Menu
        while(status==0){
            // Process events
            Event event;
            while(app.pollEvent(event)){
                // Close window : exit
                if(event.type == Event::Closed)
                    app.close();
            }

            // Clear screen
            app.clear();

            // Draw the sprites
            background();
            reset();
            text(status, score);

            // Controls
            if(Keyboard::isKeyPressed(Keyboard::Enter)){
                Kpress = true;
                if((Kpress) && (Krelease)){
                    status = 1;
                    chunks = 0;
                    score = 0;
                    randomize();
                    Krelease = false;
                }
            }
            else if(Keyboard::isKeyPressed(Keyboard::C)){
                Kpress = true;
                if((Kpress) && (Krelease)){
                    if(cheat){
                        cheat = false;
                    }
                    else cheat = true;
                    Krelease = false;
                }
            }
            else{
                Kpress = false;
                Krelease = true;
            }

            // Update the window
            app.display();
            C.restart();
        }

        // Game Running
        while(status==1){
            // Process events
            Event event;
            while(app.pollEvent(event)){
                // Close window : exit
                if(event.type == Event::Closed)
                    app.close();
            }

            // Clear screen
            app.clear();

            // Draw the sprites
            background();
            P.display();
            T.display();
            B.display();
            C.display();
            text(status, score);

            // Controls
            if(Keyboard::isKeyPressed(Keyboard::Escape)){
                Kpress = true;
                if((Kpress) && (Krelease)){
                    status = 0;
                    Krelease = false;
                }
            }
            else if(Keyboard::isKeyPressed(Keyboard::Left)){
                Kpress = true;
                if((Kpress) && (Krelease)){
                    sound.play();
                    P.Hit = true;
                    P.Side = -1;
                    if(!survive()){
                        status = -1;
                        break;
                    }
                    reduced();
                    if(!survive()){
                        status = -1;
                        break;
                    }
                    C.bonus();
                    score++;
                    chunks++;
                    Krelease = false;
                }
            }
            else if(Keyboard::isKeyPressed(Keyboard::Right)){
                Kpress = true;
                if((Kpress) && (Krelease)){
                    sound.play();
                    P.Hit = true;
                    P.Side = 1;
                    if(!survive()){
                        status = -1;
                        break;
                    }
                    reduced();
                    if(!survive()){
                        status = -1;
                        break;
                    }
                    C.bonus();
                    score++;
                    chunks++;
                    Krelease = false;
                }
            }
            else if(Keyboard::isKeyPressed(Keyboard::Up)){
                Kpress = true;
                if((Kpress) && (Krelease)){
                    P.Parry = true;
                    Krelease = false;
                }
            }
            else if(Keyboard::isKeyPressed(Keyboard::Down)){
                Kpress = true;
                if((Kpress) && (Krelease)){
                    P.Duck = true;
                    Krelease = false;
                }
            }
            else{
                Kpress = false;
                Krelease = true;
                P.refresh();
            }

            // Update the window
            app.display();
            chunks = newChunks(chunks);
            if(!survive()){
                status = -1;
            }
        }
    }

    return EXIT_SUCCESS;
}
