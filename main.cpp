#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace sf;





class Snake {
public:
    Snake(int x, int y)
    {
        tail.push_back(Pos);
        tail.push_back(Pos);
        tail.push_back(Pos);
        tail.push_back(Pos);
        tail.at(0).setPosition(Vector2f(x, y));
        tail.at(0).setFillColor(Color::Blue);




        tail.at(1).setPosition(Vector2f(x + 30, y));
        tail.at(1).setFillColor(Color::Blue);
        tail.at(1).setSize(Vector2f(30, 30));

        tail.at(2).setPosition(Vector2f(x + 60, y));
        tail.at(2).setFillColor(Color::Blue);
        tail.at(2).setSize(Vector2f(30, 30));


        tail.at(3).setPosition(Vector2f(x + 90, y)); 
        tail.at(3).setFillColor(Color::Blue);
        tail.at(3).setSize(Vector2f(30, 30));

    }

    void SetDirection(char dir) {
        this->dir = dir;


    }
    char GetDirection() {
        return this->dir;
    }

    void  SizeIncreaseBy1() {
        tail.insert(tail.begin(), Pos);
        tail.at(0).setFillColor(Color::Blue);
        tail.at(0).setSize(Vector2f(30, 30));
    }

 

    void MoveBym(RectangleShape& shape)
    {

        switch (dir)
        {
        case 'L': {shape.setPosition(shape.getPosition().x - m, shape.getPosition().y); }; break;
        case 'R': { shape.setPosition(shape.getPosition().x + m, shape.getPosition().y);  }; break;
        case 'U': {shape.setPosition(shape.getPosition().x, shape.getPosition().y - m); }; break;
        case 'D': {shape.setPosition(shape.getPosition().x, shape.getPosition().y + m); }; break;
        default: { shape.setPosition(shape.getPosition().x + m, shape.getPosition().y);  }; break;

        }
    }

    std::vector< RectangleShape> tail;
    RectangleShape Pos;
    char dir;

    const float m = 10;

};





void modifyRec(RectangleShape& rec, int x, int y, Color col, int a, int b, int rot = 0)
{
    rec.setPosition(Vector2f(x, y));
    rec.setFillColor(col);
    rec.rotate(rot);
    rec.setSize(Vector2f(a, b));
}

//giving random cordinates to fruit
void SeedFruit(RectangleShape& fruit)
{

    srand(time(0));
    int fruitx, fruity;
    fruitx = (rand() % 570) + 7;
    fruity = (rand() % 570) + 8;
    fruit.setPosition(fruitx, fruity);
}


bool collide(RectangleShape shape, RectangleShape shape2)
{
    FloatRect shapebounds = shape.getGlobalBounds();
    FloatRect shape2bounds = shape2.getGlobalBounds();
    if (shapebounds.intersects(shape2bounds)) return true;
    else return false;

}

int main()
{

    RenderWindow window(
        VideoMode(660, 660),
        " Snake", Style::Default);

    //Fruit
    RectangleShape fruit(Vector2f(30, 30));
    fruit.setFillColor(Color::Green);
    SeedFruit(fruit);

    //walls
    RectangleShape line1;
    modifyRec(line1, 0, 0, Color::Red, 5, 600);
    RectangleShape line2;
    modifyRec(line2, 660, 0, Color::Red, 5, 660, 90);
    RectangleShape line3;
    modifyRec(line3, 655, 0, Color::Red, 5, 600);
    RectangleShape line4;
    modifyRec(line4, 660, 600, Color::Red, 5, 660, 90);


    Snake snakeobj(10, 10);

    float velocity = 0.05;

    //int counter = 0;

    //font load
    Font font;
    if (!font.loadFromFile("font.ttf"))
    {
        std::cout << "Error Font was not loaded";
    }
    Text point;
    point.setFont(font);

    //to store points;
    int pointt = 0;

    while (window.isOpen())
    {
        Event event;
        while (
            window.pollEvent(event))
            if (event.type ==
                Event::Closed)
                window.close();

        // snakeobj.SetDirection('R');
        if (Keyboard::isKeyPressed(Keyboard::Left) && snakeobj.GetDirection() != 'R') snakeobj.SetDirection('L');
        if (Keyboard::isKeyPressed(Keyboard::Right) && snakeobj.GetDirection() != 'L') snakeobj.SetDirection('R');
        if (Keyboard::isKeyPressed(Keyboard::Up) && snakeobj.GetDirection() != 'D') snakeobj.SetDirection('U');
        if (Keyboard::isKeyPressed(Keyboard::Down) && snakeobj.GetDirection() != 'U') snakeobj.SetDirection('D');


        // snakeobj.MoveBym(snakeobj.tail.at(0));
         //sleep(seconds(1));
        int n = snakeobj.tail.size();
        float oldx = snakeobj.tail.at(n - 1).getPosition().x;
        float oldy = snakeobj.tail.at(n - 1).getPosition().y;
        snakeobj.MoveBym(snakeobj.tail.at(n - 1));
        for (int i = n - 2; i >= 0; i--)
        {
            //sleep(seconds(1));

            float newx = oldx;
            float newy = oldy;
            oldx = snakeobj.tail.at(i).getPosition().x;
            oldy = snakeobj.tail.at(i).getPosition().y;
            snakeobj.tail.at(i).setPosition(newx, newy);
            // std::cout << "oldx=" << oldx << " oldy=" << oldy << std::endl;
            // std::cout << "newx=" << oldx << " newy=" << oldy << std::endl;
        }




        if (collide(snakeobj.tail.at(n - 1), fruit)) {

            Vector2f OldPos = snakeobj.tail.at(0).getPosition();
            snakeobj.SizeIncreaseBy1();
            // std::cout << snakeobj.tail.size() << "\n";
             //snakeobj.tail.at(0).setPosition(fruit.getPosition());
            switch (snakeobj.dir)
            {
            case 'L': { snakeobj.tail.at(0).setPosition(OldPos.x - snakeobj.m, OldPos.y); }; break;
            case 'R': { snakeobj.tail.at(0).setPosition(OldPos.x + snakeobj.m, OldPos.y);  }; break;
            case 'U': {snakeobj.tail.at(0).setPosition(OldPos.x, OldPos.y - snakeobj.m); }; break;
            case 'D': { snakeobj.tail.at(0).setPosition(OldPos.x, OldPos.y + snakeobj.m); }; break;

            }
            sleep(seconds(0.2));
            SeedFruit(fruit);
            if (velocity > 0.01)
                //dicreases sleep amount
                velocity = velocity - 0.0008;
            pointt += 10;


        }

        //purple head
        for (int i = 0; i < n; i++)
            if (i != n - 1)
                snakeobj.tail.at(i).setOutlineThickness(0);
            else
            {
                snakeobj.tail.at(i).setOutlineColor(Color::Magenta);
                snakeobj.tail.at(i).setOutlineThickness(2);
            }

        for (int i = 0; i < snakeobj.tail.size(); i++)
            window.draw(snakeobj.tail[i]);

        //collusion detection
        if (collide(snakeobj.tail[n - 1], line1) ||
            collide(snakeobj.tail[n - 1], line2) ||
            collide(snakeobj.tail[n - 1], line3) ||
            collide(snakeobj.tail[n - 1], line4)
            )
        {
            std::cout << "\aGame Over";
            return 1;
        }


        //  if(snakeobj.tail.size()>1)
        //  std::cout << snakeobj.tail.at(1).getPosition().x << " " << snakeobj.tail.at(1).getPosition().y << std::endl;
        point.setString(std::to_string(pointt));
        point.setFillColor(Color::Yellow);
        point.setStyle(sf::Text::Bold | sf::Text::Underlined);
        point.setPosition(5, 610);
        window.draw(fruit);
        window.draw(line1);
        window.draw(line2);
        window.draw(line3);
        window.draw(line4);
        window.draw(point);
        window.display();
        sleep(seconds(velocity));
        window.clear();


    }
    return 0;
}