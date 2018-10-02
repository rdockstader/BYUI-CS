package prove02;

import java.awt.*;
import java.util.Random;

public class Wolf extends Creature implements Movable, Aware, Aggressor, Spawner {
    private Shape shape = Shape.Circle;
    private Color color = Color.gray;
    private Direction preferredDirection;
    private Boolean canSpawn = false;

    Random _rand;

    public Wolf() {
        _rand = new Random();
        _health = 1;
        switch (_rand.nextInt(4)) {
            case 0:
                preferredDirection = Direction.above;
                break;
            case 1:
                preferredDirection = Direction.below;
                break;
            case 2:
                preferredDirection = Direction.left;
                break;
            case 3:
                preferredDirection = Direction.right;
                break;
            default:
                break;
        }
    }

    public Wolf(Point location) {
        this();
        _location = location;
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
        if(preferredDirection == Direction.above) {
            _location.y++;
        } else if (preferredDirection == Direction.below) {
            _location.y--;
        } else if (preferredDirection == Direction.left) {
            _location.x--;
        } else {
            _location.x++;
        }
    }

    public void attack(Creature target) {
        if(target instanceof Animal) {
            System.out.println("Wolf Attack!");
            target.takeDamage(5);
            _health++;
            if(!target.isAlive()) {
                canSpawn = true;
            }
        }
    }

    public void senseNeighbors(Creature above, Creature below, Creature left, Creature right) {
        // right up left down
        if(preferredDirection == Direction.above) {
            if(above != null && above instanceof Animal) {
                preferredDirection = Direction.above;
            } else if(left != null && above instanceof Animal) {
                preferredDirection = Direction.left;
            } else if(below != null && above instanceof Animal) {
                preferredDirection = Direction.below;
            } else if(right != null && above instanceof Animal) {
                preferredDirection = Direction.right;
            }
        } else if(preferredDirection == Direction.left) {
            if (left != null && above instanceof Animal) {
                preferredDirection = Direction.left;
            } else if (below != null && above instanceof Animal) {
                preferredDirection = Direction.below;
            } else if (right != null && above instanceof Animal) {
                preferredDirection = Direction.right;
            } else if (above != null && above instanceof Animal) {
                 preferredDirection = Direction.above;
            }
        } else if(preferredDirection == Direction.below) {
            if (below != null && above instanceof Animal) {
                preferredDirection = Direction.below;
            } else if (right != null && above instanceof Animal) {
                preferredDirection = Direction.right;
            } else if (above != null && above instanceof Animal) {
                preferredDirection = Direction.above;
            } else if (left != null && above instanceof Animal) {
                preferredDirection = Direction.left;
            }
        } else if(preferredDirection == Direction.right) {
            if (right != null && above instanceof Animal) {
                preferredDirection = Direction.right;
            } else if (above != null && above instanceof Animal) {
                preferredDirection = Direction.above;
            } else if (left != null && above instanceof Animal) {
                preferredDirection = Direction.left;
            } else if (below != null && above instanceof Animal) {
                preferredDirection = Direction.below;
            }
        }
    }

    public Creature spawnNewCreature() {
        if(canSpawn) {
            canSpawn = false;
            Point spawnLocation = new Point(_location);
            spawnLocation.x--;
            System.out.println("Wolf Spawned at point " + spawnLocation.toString() + " from wolf at " + _location.toString());
            return new Wolf(spawnLocation);
        }

        return null;
    }
}
