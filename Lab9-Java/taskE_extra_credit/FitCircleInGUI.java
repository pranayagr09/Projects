import java.awt.event.*;
import java.awt.*; 
import javax.swing.*;
import java.awt.geom.Line2D; 
import java.awt.geom.Point2D; 
import java.util.*;
import java.awt.geom.*;

class DrawPad extends JComponent{
  Image image;
  Graphics2D graphics2D;
  int currentX, currentY, oldX, oldY;
  public int value1,value2,value3;
  JTextField position;
  ArrayList <Point2D.Double> contour_list = new ArrayList <Point2D.Double>();
  public DrawPad() {
    setDoubleBuffered(false);
    value1=0;
    value2=0;
    value3=0;
    position=new JTextField();
    position.setBackground(Color.WHITE);
    position.setForeground(Color.BLACK);
    position.setBounds(1,1,70,20);
    add(position);

    addMouseListener(new MouseAdapter() {
      public void mousePressed(MouseEvent e) {
        oldX = e.getX();
        oldY = e.getY();
        position.setText("["+String.valueOf((int)e.getX())+","+String.valueOf((int)e.getY())+"]");
      }
    });
    addMouseMotionListener(new MouseMotionAdapter() {
      public void mouseDragged(MouseEvent e) {
        currentX = e.getX();
        currentY = e.getY();
        Point2D.Double contour= new Point2D.Double(currentX,currentY);
        contour_list.add(contour);
        if (graphics2D != null)
          graphics2D.drawLine(oldX, oldY, currentX, currentY);
        repaint();
        oldX = currentX;
        oldY = currentY;
        position.setText("["+String.valueOf((int)e.getX())+","+String.valueOf((int)e.getY())+"]");
      }
      public void mouseMoved(MouseEvent e){
        position.setText("["+String.valueOf((int)e.getX())+","+String.valueOf((int)e.getY())+"]");      }
    });
  }

  public void paintComponent(Graphics g) {
    if (image == null) {
      image = createImage(getSize().width, getSize().height);
      graphics2D = (Graphics2D) image.getGraphics();
      graphics2D.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
          RenderingHints.VALUE_ANTIALIAS_ON);
      clear();
    }
    g.drawImage(image, 0, 0, null);
  }
  public void clear() {
    graphics2D.setPaint(Color.white);
    graphics2D.fillRect(0, 0, getSize().width, getSize().height);
    graphics2D.setPaint(Color.red);
    contour_list.clear();
    repaint();
  }
  public void circle_fit()
  {
  	CircleFitter fit_Circle;
  	fit_Circle= new CircleFitter(contour_list);
    int[] values=new int[3];
    
  	values=fit_Circle.run();
    value1=values[0];
    value2=values[1];
    value3=values[2];

  	graphics2D.setPaint(Color.green);
  	graphics2D.drawOval(values[0]-values[2],values[1]-values[2],2*values[2],2*values[2]);
    contour_list.clear();
  	repaint();
  }
}

class Sketchpad extends JFrame implements
	ActionListener,    
  MouseListener,
  MouseMotionListener,
	WindowListener
{
	 @Override
    public void windowOpened(WindowEvent e) {

    }

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
     @Override
    public void actionPerformed(ActionEvent e) {

    }
    
    @Override
    public void mouseExited(MouseEvent e) {

    }
    @Override
    public void mouseEntered(MouseEvent e) {

    }
    @Override
    public void mouseReleased(MouseEvent e) {

    }
    @Override
    public void mouseClicked(MouseEvent e) {

    }

	JPanel control_Panel;
	JButton clearButton,fit_button;
  JLabel error;
  boolean error_present=false;
  JTextField position;
  int X;int Y;

	public Sketchpad(String s)
	{
		super(s);
		setBackground(Color.white);	
		DrawPad drawPad=new DrawPad();
		control_Panel=new JPanel();
		control_Panel.setLayout(null);		

    error=new JLabel("");
		clearButton=new JButton("Clear Screen");
		clearButton.addActionListener(new ActionListener() {
	      public void actionPerformed(ActionEvent e) {
	       	drawPad.clear();
          if(error_present) 
            {control_Panel.add(error);
              error.setText("");
              error_present=false;}
	      }
    	});

		fit_button=new JButton("Fit the Circle now");
		fit_button.addActionListener(new ActionListener() {
	      public void actionPerformed(ActionEvent e) {
	       	drawPad.circle_fit();
          control_Panel.add(error);
          error_present=true;
          error.setText("Fit Circle- Centre:(" + drawPad.value1 + "," + drawPad.value2 + ") and Radius: " + drawPad.value3);
	      }
    	});
		
    position=new JTextField();
    position.setBackground(Color.WHITE);
    position.setForeground(Color.BLACK);
    position.setLayout(null);
		clearButton.setLayout(null);
		fit_button.setLayout(null);
    error.setLayout(null);
		drawPad.setLayout(null); 
    position.setBounds(1,1,70,20);
    drawPad.setBounds(0,0,800,450);
    clearButton.setBounds(400, 480, 150, 50);
    fit_button.setBounds(150,480,200,50);
    error.setBounds(250, 520, 590, 50);
    getContentPane().add(position);
    getContentPane().add(drawPad);
    getContentPane().add(control_Panel);
  //  control_Panel.add(position);
    control_Panel.add(clearButton);
    control_Panel.add(fit_button);
    addWindowListener(this);
    addMouseMotionListener(this);
    addMouseListener(this);
	}

  protected void displayMouseCoordinates(int x, int y)
  {
    position.setText("["+String.valueOf(x)+","+String.valueOf(y)+"]");
  }

  



  public void mouseDragged(MouseEvent event)
  {
    Graphics g = getGraphics();
    
    X=(int)event.getX();
    Y=(int)event.getY();    
    displayMouseCoordinates(X,Y);    
  }

  //----------------------------------------------------------------

  public void mouseMoved(MouseEvent event)
  {
    displayMouseCoordinates((int)event.getX(),(int) event.getY());
  }

  public void mousePressed(MouseEvent event)
  {
    X=(int)event.getX(); 
    Y=(int)event.getY();
    Graphics g = getGraphics();
    displayMouseCoordinates((int)event.getX(),(int) event.getY());
  }
}
class FitCircleInGUI
{
	public static void main(String[] args)
	{
		Sketchpad screen = new Sketchpad("Extra Credit:Draw a Circle");
		screen.setSize(800,600);
		screen.setVisible(true);
	}
}