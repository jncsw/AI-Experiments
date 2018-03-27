public class Node {
    public int x;// X坐标
    public int y;// Y坐标
    public Node fa;// 父类节点
    public int g;// 当前点到起点的cost
    public int h;// 当前点到终点的cost
    public int f;// f=g+h

    public Node(int x, int y, Node fa) {
        this.x = x;
        this.y = y;
        this.fa = fa;
    }

    public int compareTo(Node n) {
        return this.getF() - n.getF();
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public Node getFa() {
        return fa;
    }

    public void setFa(Node fa) {
        this.fa = fa;
    }

    public int getG() {
        return g;
    }

    public void setG(int g) {
        this.g = g;
    }

    public int getH() {
        return h;
    }

    public void setH(int h) {
        this.h = h;
    }

    public int getF() {
        return f;
    }

    public void setF(int f) {
        this.f = f;
    }

}
