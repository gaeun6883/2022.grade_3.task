import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.geom.*;

public class Draw {
	public static int x1;
	public static int x2;
	public static int y1;
	public static int y2;
	public void main(int x1,int y1,int x2,int y2) {
		MyFrame f = new MyFrame("Main frame");
		this.x1 = x1;
		this.x2 = x2;
		this.y1 = -y1;
		this.y2 = -y2;
	}
}

class MyFrame extends JFrame {
  public static Algorithm b = new Algorithm();
	MyFrame(String title) {
		super(title);
		setSize(1000, 1000);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		screen();
		setVisible(true);
	}

	private void screen() {
		setLayout(null);
		MyPanel p = new MyPanel();
		p.setBounds(0,0,1000,1000);
		add(p);
		JLabel xTrans = new JLabel("dx");
		JLabel yTrans = new JLabel("dy");
		JTextField xTransfield = new JTextField(20);
		JTextField yTransfield = new JTextField(20);
		xTrans.setBounds(50,650,50,30);
		xTransfield.setBounds(110,650,100,30);
		yTrans.setBounds(50,690,50,30);
		yTransfield.setBounds(110,690,100,30);
		add(xTrans);
		add(yTrans);
		add(xTransfield);
		add(yTransfield);
		JButton done = new JButton("complete");
		done.setBounds(230,650,100,30);
		add(done);
    
		done.addActionListener(new ActionListener() {
		@Override
  		public void actionPerformed(ActionEvent e) {
        int dx = Integer.parseInt(xTransfield.getText());
			  int dy = Integer.parseInt(yTransfield.getText());
        b.move(dx, dy);
      } 
    });
  }
}

class MyPanel extends JPanel {
	public static int i = 0;
	public static Graphics2D g2;
	protected void paintComponent(Graphics g) {
		g2 = (Graphics2D) g;
		float dash0[] = { 1, 0f };
		float dash3[] = { 3, 3f };
		g2.translate(300, 300); // 원점: (300, 300)

		g2.setStroke(new BasicStroke(1, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 1, dash3, 0));
		for (int i = -300; i <= 300; i = i + 20) 
			g2.draw(new Line2D.Float(-300, i, 300, i)); // x축과 평행선을 그린다.
		for (int j = -300; j <= 300; j = j + 20) 
			g2.draw(new Line2D.Float(j, -300, j, 300)); // y축과 평행선을 그린다.

		g2.setStroke(new BasicStroke(2, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 1, dash0, 0));
		g2.draw(new Line2D.Float(-300, 0, 300, 0)); // x축
		g2.draw(new Line2D.Float(0, -300, 0, 300)); // y축

    draw_mid();
    if(Algorithm.moveX!=null)
      draw_move();
	}
  void draw_mid(){
    g2.setColor(Color.BLUE);
    for (int i = 0; i<Algorithm.cnt;i++ ) {
			int x = Algorithm.arrX[i];
			int y = Algorithm.arrY[i];
			g2.fillOval(x-5 , -(y)-5, 10, 10);
		}
		g2.setColor(Color.RED);
		g2.drawLine(Draw.x1,Draw.y1,Draw.x2,Draw.y2);
  }
  
  void draw_move(){
    g2.setColor(Color.GREEN);
    for (int i = 0; i<Algorithm.cnt;i++ ) {
			int x = Algorithm.moveX[i];
			int y = Algorithm.moveY[i];
			g2.fillOval(x-5 , -(y)-5, 10, 10);
		}
  }
}