package prove02;

import java.awt.*;
import java.util.Random;

public class Zombie extends Creature implements Movable, Aggressor {
    private Shape shape = Shape.Square;
    private Color color = Color.blue;

    Random _rand;

    public Zombie() {
        _rand = new Random();
        _health = 1;
    }


    public Shape getShape() {
        return this.shape;
    }

    public Color getColor() {
        return this.color;
    }

    public Boolean isAlive() {
        return _health > 0;
    }

    public void move() {
        switch(_rand.nextInt(2)) {
            case 0:
                _location.x++;
                break;
            case 1:
                _location.x--;
                break;
            default:
                break;
        }
    }

    public void attack(Creature target) {
        if(target != null && !(target instanceof Plant)) {
            System.out.println("Zombie Attack!");
            target.takeDamage(10);
            _health++;
        }
    }
}
