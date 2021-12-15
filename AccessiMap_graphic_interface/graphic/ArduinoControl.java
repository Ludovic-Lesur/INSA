/**
 * Javadoc
 * 
 * @author Ludovic Lesur
 * @since 18/07/2016
 */


package graphic ;
import barChart.* ;
import java.io.* ;
import gnu.io.* ;
import java.util.* ;
import java.awt.* ;
import java.awt.event.* ;
import javax.swing.* ;


public class ArduinoControl extends JFrame implements ActionListener {
	
	private static final long serialVersionUID = 1L ;
	
	// Mother class
	private ModuleControl moduleControl ;
	
	// Panel and GBC
	private JPanel panel ;
	private GridBagConstraints gbc ;
	
	// Graphic components
	private JLabel title ;
	private JComboBox<String> listPortsCOM ;
	private JButton connect ;
	private JLabel stateConnexion ;
	private JButton calibrate ;
	
	// Data members
	private boolean connected ;
	private String currentPortCOM ;
	private static int numberOfModules ;
	
	
	/**
		CONSTRUCTOR FOR CLASS ARDUINO CONTROL.
		@param pModuleControl	The mother-class object (ModuleControl).
		@param mainPanel		The panel of the main interface.
		@param mainGbc			The layout constraints of the main interface.
	    @return 				None.
	*/
	public ArduinoControl(ModuleControl pModuleControl, JPanel mainPanel, GridBagConstraints mainGbc) {
		
		// Mother-class object
		moduleControl = pModuleControl ;
		
		// Panel properties
		panel = new JPanel(new GridBagLayout()) ;
		panel.setBackground(Color.black) ;
		
		// GBC properties
		gbc = new GridBagConstraints() ;
		gbc.insets = new Insets(10, 10, 10, 10) ;
		gbc.anchor = GridBagConstraints.CENTER ;
		gbc.gridwidth = GridBagConstraints.REMAINDER ;
		gbc.gridheight = 1 ;
		
		// Graphic components
		gbc.gridx = 0 ;
		gbc.gridy = 0 ;
		// Displays 'Arduino A', 'Arduino B'...
		title = new JLabel("Arduino " + (char)(65+numberOfModules)) ;
		title.setFont(new Font(Interface.POLICE.getFontName(), 2, 15)) ;
		title.setForeground(Color.blue) ;
		panel.add(title, gbc) ;
		
		gbc.gridx = 0 ;
		gbc.gridy = 2 ;
		stateConnexion = new JLabel(" ") ;
		stateConnexion.setForeground(Color.white) ;
		stateConnexion.setFont(Interface.POLICE) ;
		panel.add(stateConnexion, gbc) ;
		
		gbc.gridwidth = 1 ;
		gbc.gridx = 0 ;
		gbc.gridy = 1 ;
		listPortsCOM = new JComboBox<String>() ;
		listPortsCOM.setFont(Interface.POLICE) ;
		listPortsCOM.addItemListener(new ItemState()) ;
		panel.add(listPortsCOM, gbc) ;
		
		gbc.gridx = 1 ;
		gbc.gridy = 1 ;
		connect = new JButton("Connect") ;
		connect.setFont(Interface.POLICE) ;
		connect.addActionListener(this) ;
		panel.add(connect, gbc) ;
		
		gbc.gridx = 2 ;
		gbc.gridy = 1 ;
		calibrate = new JButton("Calibrate") ;
		calibrate.setFont(Interface.POLICE) ;
		calibrate.addActionListener(this) ;
		calibrate.setEnabled(false) ;
		panel.add(calibrate, gbc) ;
		
		// Data members
		connected = false ;
		numberOfModules++ ;
		
		// Adding ArduinoControl to the main interface
		mainPanel.add(panel, mainGbc) ;
	}
	
	
	/**
		SHOW AVAILABLE COM PORTS.
		@param		None.
	    @return 	None.
	*/
	@SuppressWarnings("rawtypes")
	public void showPortsCOM() {
		Enumeration portEnum = CommPortIdentifier.getPortIdentifiers() ;
		// Empty item used to fix the JComboBox width
		listPortsCOM.addItem("                       ") ;
		while (portEnum.hasMoreElements()) {
			CommPortIdentifier currPortId = (CommPortIdentifier) portEnum.nextElement() ;
			listPortsCOM.addItem(currPortId.getName()) ;
		}		
	}
	
	
	/**
		BUTTONS PROCESSING.
		@param e	Event which activates processing actions.
	    @return 	None.
	*/
	public void actionPerformed(ActionEvent e) {
		// Connection
		if ((e.getSource() == connect) && (connected == false)) {
			// Temporary variable used to try the connection
			Module module = new Module(null, currentPortCOM) ;
			switch (module.connect()) {
			case 1 :
				stateConnexion.setText("Connection OK.") ;
				stateConnexion.setForeground(Color.green) ;
				module.close() ;
				moduleControl.connect(currentPortCOM) ;
				connected = true ;
				calibrate.setEnabled(true) ;
				// Connection is established -> disable the drop down menu and the 'Connect' button
				listPortsCOM.setEnabled(false) ;
				connect.setEnabled(false) ;
				break ;
			case -1 :
				stateConnexion.setText("Serial port allready in use !") ;
				stateConnexion.setForeground(Color.orange) ;
				break ;
			default :
				stateConnexion.setText("Connection failed.") ;
				stateConnexion.setForeground(Color.red) ;
				break ;
			}
		}
		// Calibration
		if (e.getSource() == calibrate) {
			try {
				System.out.println("\nCalibration...") ;
				moduleControl.getModule().getArduino().writeData(Module.INSTRUCTION_CALIBRATION) ;
			}
			catch(IOException ex) {}
		}
	}
	
	
	/**
		DROP-DOWN MENU PROCESSING.
		@param e	Item event.
	    @return 	None.
	*/
	class ItemState implements ItemListener {
	
		public void itemStateChanged(ItemEvent e) {
			if (e.getSource() == listPortsCOM) {
				currentPortCOM = (String)e.getItem() ;
			}
		}
	}
}
