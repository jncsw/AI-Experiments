import java.util.*;
import static org.fusesource.jansi.Ansi.*;
import static org.fusesource.jansi.Ansi.Color.*;

public class Main {
    static final int horizon = 10;// 4方向cost
    static final int diagonal = 14;// 对角方向cost
    public static int[][] mp = null;
    public static List<Node> openList = new ArrayList<Node>();// openList
    public static List<Node> closeList = new ArrayList<Node>();// closeList
    public static int cho = 0;


    public static int getHorizon() {
        return horizon;
    }

    public static int getDiagonal() {
        return diagonal;
    }

    public static int[][] getMp() {
        return mp;
    }

    public static void setMp(int[][] mp) {
        Main.mp = mp;
    }

    public static List<Node> getOpenList() {
        return openList;
    }

    public static void setOpenList(List<Node> openList) {
        Main.openList = openList;
    }

    public static List<Node> getCloseList() {
        return closeList;
    }

    public static void setCloseList(List<Node> closeList) {
        Main.closeList = closeList;
    }

    public static int getCho() {
        return cho;
    }

    public static void setCho(int cho) {
        Main.cho = cho;
    }

    private static boolean AStar(int[][] arr, Node st, Node ed, int row, int col) {

        Node cur = st;
        if (st.x < 0 || st.y > col || ed.x < 0 || ed.y > col || arr[st.x][st.y] == 0 || arr[ed.x][ed.y] == 0) {
            System.err.println("初始坐标错误！");
            return false;
        }

        openList.add(st);
        while (!openList.isEmpty() && !openList.contains(ed)) {
            cur = findMin(openList);
            if (cur.x == ed.x && cur.y == ed.y || openList.contains(ed)) {
                System.out.println("找到最短路径!");
                while(!(cur.x==st.x && cur.y==st.y)){
                    System.out.print("<"+cur.x+","+cur.y+"> ->");
                    mp[cur.x][cur.y]=2;
                    if (cur.fa!=null) {
                        cur=cur.fa;
                    }
                }
                System.out.println("<"+st.x+","+st.y+">");
                mp[st.x][st.y]=2;
                return true;
            }
            // 上
            if (cur.y - 1 >= 0) {
                canGo(cur.x, cur.y - 1, cur, ed,horizon);
            }
            // 下
            if (cur.y + 1 < col) {
                canGo(cur.x, cur.y + 1, cur, ed,horizon);
            }
            // 左
            if (cur.x - 1 >= 0) {
                canGo(cur.x - 1, cur.y, cur, ed,horizon);
            }
            // 右
            if (cur.x + 1 < row) {
                canGo(cur.x + 1, cur.y, cur, ed,horizon);
            }
            if(cho==8){
                // 左上
                if (cur.x - 1 >= 0 && cur.y - 1 >= 0) {
                    canGo(cur.x - 1, cur.y - 1, cur, ed,diagonal);
                }
                // 左下
                if (cur.x - 1 >= 0 && cur.y + 1 < col) {
                    canGo(cur.x - 1, cur.y + 1, cur, ed,diagonal);
                }
                // 右上
                if (cur.x + 1 < row && cur.y - 1 >= 0) {
                    canGo(cur.x + 1, cur.y - 1, cur, ed,diagonal);
                }
                // 右下
                if (cur.x + 1 < row && cur.y + 1 < col) {
                    canGo(cur.x + 1, cur.y + 1, cur, ed,diagonal);
                }
            }
            openList.remove(cur);
            closeList.add(cur);
        }
        return false;
    }

    // 核心算法---检测节点是否通路
    private static boolean canGo(int x, int y, Node preNode, Node ed,int c) {
        Node node = new Node(x, y, preNode);
        // 不能通过
        if (mp[x][y] == 0) {
            closeList.add(node);
            return false;
        }
        if (Contains(closeList, x, y) != -1) {//在closeList中
            return false;
        }
        int index = -1;
        if ((index = Contains(openList, x, y)) != -1) {//在OpenList中
            // 是否更新G，F
            if ((preNode.g + c) < openList.get(index).g) {
                calcG(node, ed, c);
                calcF(node);
                openList.set(index, node);
            }
        } else {
            // 添加到OpenList
            node.setFa(preNode);
            calc(node, ed, c);
            openList.add(node);
        }
        return true;
    }
    private static void calc(Node node, Node eNode, int cost) {// 计算G,H,F
        calcG(node, eNode, cost);
        calcH(node, eNode);
        calcF(node);
    }

    private static void calcG(Node node, Node eNode, int cost) {
        if (node.getFa() == null) {
            node.setG(cost);
        } else {
            node.setG(node.getFa().getG() + cost);
        }
    }
    private static void calcH(Node node, Node eNode) {
        node.setF((Math.abs(node.getX() - eNode.getX()) + Math.abs(node.getY() - eNode.getY())) * 10);
    }
    private static void calcF(Node node) {
        node.setF(node.getG() + node.getH());
    }
    private static int Contains(List<Node> list, int x, int y) {//list是否包含某个元素
        for (int i = 0; i < list.size(); i++) {
            Node node = list.get(i);
            if (node.getX() == x && node.getY() == y) {
                return i;
            }
        }
        return -1;
    }
    private static Node findMin(List<Node> list) {// 找最小值
        Iterator<Node> i = list.iterator();
        Node candidate = i.next();

        while (i.hasNext()) {
            Node next = i.next();
            if (next.compareTo(candidate) < 0)
                candidate = next;
        }
        return candidate;
    }
    static void show(int c){
        switch (c){
            case 0:
                System.out.print( ansi().eraseScreen().fg(GREEN).a("* ").reset() );
                break;
            case 1:
                System.out.print( ansi().eraseScreen().fg(BLUE).a(". ").reset() );
                break;
            case 2:
                System.out.print( ansi().eraseScreen().fg(RED).a("+ ").reset() );
                break;
        }
    }
    public static void main(String[] args) {

        System.out.println("************* 欢迎使用迷宫问题求解程序 *************");
        System.out.println("");

        Scanner in = new Scanner(System.in);

        int Row = 0;
        int Col = 0;
        System.out.println("请输入行数：");
        Row = in.nextInt();
        System.out.println("请输入列数：");
        Col = in.nextInt();
        System.out.println("请输入矩阵，以空格分隔,'*'表示障碍物，'.'表示允许走：");
        mp = new int[Row][Col];
        for(int i = 0;i<Row;i++){
            for(int j=0;j<Col;j++){
                String c = in.next();
                mp[i][j] = (c.charAt(0)=='*')?0:1;
            }
        }
        System.out.println("请输入允许的方向数（4/8）：");
        cho = in.nextInt();
        int sx,sy,tx,ty;
        System.out.println("请输入起点坐标（左上角(0,0），右下角(Row-1,Col-1)：");
        sx = in.nextInt();
        sy = in.nextInt();
        System.out.println("请输入终坐标（左上角(0,0），右下角(Row-1,Col-1)：");
        tx = in.nextInt();
        ty = in.nextInt();
        System.out.println("你输入的地图是：");
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++) {
                show(mp[i][j]);
            }
            System.out.println();
        }
        System.out.println("起点：<"+sx+","+sy+"> 终点：<"+tx+","+"> "+(cho==8?8:4)+"方向");

        Node st = new Node(sx, sy, null);
        Node ed = new Node(tx,ty, null);
        long startTime = System.currentTimeMillis();
        boolean found = AStar(mp, st, ed, Row, Col);
        long endTime = System.currentTimeMillis();    //获取结束时间

        if(!found){
            System.out.println( ansi().eraseScreen().fg(RED).a("未找到路径！").reset() );
            return;
        }
        System.out.println();
        for (int i = 0; i < Row; i++) {
            for (int j = 0; j < Col; j++) {
                show(mp[i][j]);
            }
            System.out.println();
        }
        System.out.println("程序运行时间：" + (endTime - startTime) + "ms");    //输出程序运行时间
    }

}

/*

5
5
* * . . *
* * . . .
. . . . .
* * . * *
. * . . .

8
0 2
4 4


 */