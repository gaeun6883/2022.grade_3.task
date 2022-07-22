import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.geom.*;

public class Main {
	public static Algorithm a = new Algorithm();
	public static void main(String[] arg) {
		JFrame frame = new JFrame();
		frame.setTitle("algorithm");
		frame.setSize(1000,1000);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		Container c = frame.getContentPane();
		c.setLayout(null);
		
		JLabel point1 = new JLabel("first start Point ");
		JLabel x1 = new JLabel("x1 ");
		JLabel y1 = new JLabel("y1 ");
		JTextField x1field = new JTextField(20);
		JTextField y1field = new JTextField(20);
		
		JLabel point2 = new JLabel("second end Point");
		JLabel x2 = new JLabel("x2 ");
		JLabel y2 = new JLabel("y2 ");
		JTextField x2field = new JTextField(20);
		JTextField y2field = new JTextField(20);
		
		point1.setBounds(50,50,200,20);
		x1.setBounds(50,80,50,30);
		x1field.setBounds(110,80,100,30);
		y1.setBounds(50,120,50,30);
		y1field.setBounds(110,120,100,30);
		
		point2.setBounds(50,180,200,20);
		x2.setBounds(50,210,50,30);
		x2field.setBounds(110,210,100,30);
		y2.setBounds(50,250,50,30);
		y2field.setBounds(110,250,100,30);
		
		JButton done  = new JButton("complete");
		done.setBounds(40,300,80,30);
		
		c.add(point1);
		c.add(x1);
		c.add(x1field);
		c.add(y1);
		c.add(y1field);
		
		c.add(point2);
		c.add(x2);
		c.add(x2field);
		c.add(y2);
		c.add(y2field);
		
		c.add(done);
		
		frame.setVisible(true);
		
		done.addActionListener(new ActionListener() {
			@Override
	  		public void actionPerformed(ActionEvent e) {
				int x1 = Integer.parseInt(x1field.getText());
				int y1 = Integer.parseInt(y1field.getText());
				int x2 = Integer.parseInt(x2field.getText());
				int y2 = Integer.parseInt(y2field.getText());
	  		a.algorithm(x1, y1, x2, y2);
	  		}
	  	});
	}
}

