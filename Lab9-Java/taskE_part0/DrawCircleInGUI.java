import java.awt.event.*;
import java.awt.*; 
import java.lang.*; 
import javax.swing.*;
import java.awt.geom.Line2D; 
import java.awt.event.WindowEvent;

class Sketchpad extends JFrame implements
	ActionListener,
	WindowListener
{
	 @Override
    public void windowOpened(WindowEvent e) {

    }

    @Override
    public void windowClosing(WindowEvent e) {
    	System.exit(0);	

    }

    @Override
    public void windowClosed(WindowEvent e) {

    }

    @Override
    public void windowIconified(WindowEvent e) {

    }

    @Override
    public void windowDeiconified(WindowEvent e) {

    }

    @Override
    public void windowActivated(WindowEvent e) {

    }

    @Override
    public void windowDeactivated(WindowEvent e) {

    }
	JPanel control_Panel;
	JTextField editX,editY,radius;
	JButton drawButton;
	JLabel  x_cord,y_cord,rad;
	JLabel error;
	float x_cordinate,y_cordinate,radius1;
	boolean error_present=false;

	public Sketchpad(String s)
	{
		super(s);
		setBackground(Color.white);	

		control_Panel=new JPanel();
		control_Panel.setLayout(null);		

		drawButton=new JButton("Draw Circle");
		drawButton.addActionListener(this);

		x_cord= new JLabel("x-coordinate: ");
	    y_cord= new JLabel("y-coordinate: ");
	    rad= new JLabel("radius: ");
	    editX = new JTextField();
	    editX.setBackground(Color.WHITE);
        editX.setForeground(Color.BLACK);
        editY = new JTextField();
	    editY.setBackground(Color.WHITE);
        editY.setForeground(Color.BLACK);
        radius = new JTextField();
	    radius.setBackground(Color.WHITE);
        radius.setForeground(Color.BLACK);
    	error = new JLabel("This Circle will be out of draw area, try different values.");
		addWindowListener(this);

		drawButton.setLayout(null);
	    editX.setLayout(null);
	    editY.setLayout(null);
	    radius.setLayout(null);
	    x_cord.setLayout(null);
	    y_cord.setLayout(null);
	    rad.setLayout(null);
    	error.setLayout(null);
	    
	    drawButton.setBounds(280, 500, 150, 50);
	    x_cord.setBounds(10, 420, 110, 30);
	    y_cord.setBounds(265, 420, 150, 30);
	    rad.setBounds(540, 420, 150, 30);
	    editX.setBounds(10, 455, 100, 30);
	    editY.setBounds(265, 455, 100, 30);
	    radius.setBounds(540, 455, 150, 30);
    	error.setBounds(250, 550, 590, 50);
	    
	    getContentPane().add(control_Panel);
	    
	    control_Panel.add(drawButton);
	    control_Panel.add(editX);
	    control_Panel.add(editY);
	    control_Panel.add(radius);
	    control_Panel.add(x_cord);
	    control_Panel.add(y_cord);
	    control_Panel.add(rad);
	}

	public void actionPerformed(ActionEvent event)
	{
		x_cordinate = Float.parseFloat(editX.getText());
		y_cordinate = Float.parseFloat(editY.getText());
		radius1 = Float.parseFloat(radius.getText());
		Graphics g = getGraphics();
		paint(g);
		repaint();
	}

	public void paint(Graphics g) 
	{
	    super.paint(g);  
	    Graphics2D g2 = (Graphics2D) g;

	    Dimension size=getSize();
	    double frameWf=size.getWidth();
	    double frameHf=size.getHeight();
	   	int frameW=(int)frameWf;
	    int frameH=(int)frameHf;
	    drawButton.setBounds(3*frameW/8, 5*frameH/6, 3*frameW/16, frameH/12);
	    x_cord.setBounds(frameW/80,  7*frameH/10, frameW/8, frameH/20);
	    y_cord.setBounds(7*frameW/20, 7*frameH/10, frameW/8, frameH/20);
	    rad.setBounds(11*frameW/16,  7*frameH/10, frameW/4, frameH/20);
	    editX.setBounds(frameW/80, 31*frameH/40, frameW/8, frameH/20);
	    editY.setBounds(7*frameW/20, 31*frameH/40, frameW/8, frameH/20);
	    radius.setBounds(11*frameW/16, 31*frameH/40, frameW/4, frameH/20);
    	error.setBounds(5*frameW/16, 11*frameH/12, frameW*3/4, frameH/12);

	    Line2D lin = new Line2D.Float(0, 2*frameH/3, frameW, 2*frameH/3);
	    g2.draw(lin);
	    if(x_cordinate+radius1<=frameWf && y_cordinate+radius1<=2*frameHf/3)
        {
	    	drawCircle(x_cordinate,y_cordinate, radius1);
	    }
	    else
        {
        	control_Panel.add(error);
        	error_present=true;
        }
	}

	public void drawCircle(double x, double y, double rad)
	{
        Graphics g = this.getGraphics();
        Dimension size=getSize();
	   	double frameWf=size.getWidth();
	    double frameHf=size.getHeight();
        if(x-rad>=0 && y-rad>=0 && x+rad<=frameWf&& y+rad<=2*frameHf/3)
        {
        	if(error_present) 
        		{control_Panel.remove(error);}
        	g.drawOval((int)(x-rad), (int)(y-rad), (int)(2*rad),(int)(2*rad));
        	//repaint();
        }
        else
        {
        	control_Panel.add(error);
        	error_present=true;
        }
    }
}


public class DrawCircleInGUI
{
	public static void main(String[] args)
	{
		Sketchpad screen = new Sketchpad("Draw a Circle");
		screen.setSize(800, 600);
		screen.setVisible(true);
	}
}