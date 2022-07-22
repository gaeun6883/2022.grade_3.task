
public class Algorithm {
	public static int[] arrX = new int[600];
	public static int[] arrY = new int[600];
  public static int[] moveX;
  public static int[] moveY;
  int X1,X2,Y1,Y2;
	public static int cnt = 0;
	public void algorithm(int X1, int Y1, int X2, int Y2) {
    X1*=20;
    Y1*=20;
    X2*=20;
    Y2*=20;
		cnt = 0;
    this.X1=X1;
    this.Y1=Y1;
    this.X2=X2;
    this.Y2=Y2;
    
    midpoint();
  }
  public void midpoint(){
		int dx = X2 - X1; 
    int dy = Y2 - Y1; 
    int d = dy - dx/2; 
    int x = X1, y = Y1; 
    arrX[cnt] = x;
		arrY[cnt] = y;
    while (x <= X2) { 
      x+=20; 
      if (d < 0) 
        d +=dy; 
      else{ //NE
        d += dy-dx; 
        y+=20; 
      }
			cnt++;
			arrX[cnt] = x;
			arrY[cnt] = y;
		}
		Draw draw = new Draw();
		draw.main(X1,Y1,X2,Y2);
	}

  public void move(int dx, int dy){
    moveX=new int[600];
    moveY=new int[600];
    for(int i=0; i<cnt; i++){
      int x = arrX[i];
      int y = arrY[i];
      int nx=x+dx*20;
      int ny=y+dy*20;
      moveX[i]=nx;
      moveY[i]=ny;
    }
    Draw draw = new Draw();
		draw.main(X1,Y1,X2,Y2);
  }
}
