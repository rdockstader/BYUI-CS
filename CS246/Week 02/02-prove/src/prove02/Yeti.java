package prove02;

import java.awt.*;
import java.util.Random;

public class Yeti extends Creature implements Movable, Aware, Aggressor, Spawner, Teleporter  {
    private Shape shape = Shape.Triangle;
    private Color color = Color.BLACK;
    private Direction preferredDirection;
    private Boolean canSpawn = false;

    Random _rand;

    public Yeti() {
        _rand = new Random();
        _health = 10;
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

    public Yeti(Point location) {
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
        if(target != null && !(target instanceof Yeti)) {
            System.out.println("Yeti Attack!");
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
            System.out.println("Yeti Spawned at point " + spawnLocation.toString() + " from wolf at " + _location.toString());
            return new Yeti(spawnLocation);
        }

        return null;
    }

    public void teleport(int rows, int cols) {
        switch (_rand.nextInt(50)) {
            case 47:
                int r = _rand.nextInt(rows);
                int c = _rand.nextInt(cols);
                _location = new Point(r, c);
                System.out.println("Yeti Teleported!");
                break;
            default:
                break;
        }
    }
}
