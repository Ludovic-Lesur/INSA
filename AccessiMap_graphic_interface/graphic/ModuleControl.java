/**
 * Javadoc
 * 
 * @author Ludovic Lesur
 * @since 19/07/2016
 */


package graphic ;
import barChart.* ;
import java.awt.* ;
import java.io.* ;
import javax.swing.* ;


public class ModuleControl extends JFrame {
	
	private static final long serialVersionUID = 1L ;
	
	// Mother classes
	private Interface graphicInterface ;
	private RepresentationControl representationControl ;
	
	// Panel and GBC
	private JPanel panel ;
	private GridBagConstraints gbc ;
	
	// Graphic components
	private BarControl[] barsControl ;
	private ArduinoControl arduinoControl ;
	
	// Data members
	private Module module ;
	private boolean errorHeight ;
	private boolean connected ;
	
	
	/**
		CONSTRUCTOR FOR CLASS MODULE CONTROL.
		@param pGraphicInterface		The mother-class object (Interface).
		@param pRepresentationControl	The mother-class object (RepresentationControl).
		@param mainPanel				The panel of the main interface.
		@param mainGbc					The layout constraints of the main interface.
	    @return 						None.
	*/
	public ModuleControl(Interface pGraphicInterface, RepresentationControl pRepresentationControl, JPanel mainPanel, GridBagConstraints mainGbc) {
		
		// Mother classes
		graphicInterface = pGraphicInterface ;
		representationControl = pRepresentationControl ;
		
		// Panel properties
		panel = new JPanel(new GridBagLayout()) ;
		panel.setBackground(Color.black) ;
		
		// GBC properties
		gbc = new GridBagConstraints() ;
		gbc.insets = new Insets(10, 10, 10, 10) ;
		gbc.anchor = GridBagConstraints.CENTER ;
		gbc.gridheight = 1 ;
		
		// Arduino control
		gbc.gridwidth = GridBagConstraints.REMAINDER ;
		gbc.gridx = 0 ;
		gbc.gridy = 0 ;
		arduinoControl = new ArduinoControl(this, panel, gbc) ;
		arduinoControl.showPortsCOM() ;
		
		// Bars control
		gbc.gridwidth = 1 ;
		gbc.gridy = 1 ;
		barsControl = new BarControl[Module.NUMBER_OF_BARS] ;
		int i = 0 ;
		for (i=0 ; i<Module.NUMBER_OF_BARS ; i++) {
			barsControl[i] = new BarControl(this, panel, gbc) ;
			gbc.gridx++ ;
		}
		
		// Data members
		connected = false ;
		errorHeight = false ;
		
		// Adding ModuleControl to the main interface
		mainPanel.add(panel, mainGbc) ;
	}
	
	
	/** GET THE MODULE OBJECT.
	    @param 				None.
	    @return	module		The Module object associated to ModuleControl.
	*/	
	Module getModule() {
		return module ;
	}
	
	
	/**
		GET THE ARRAY OF BARS.
	    @param 					None.
	    @return	barsControl		The array of BarControl objects associated to ModuleControl.
	*/	
	BarControl[] getBars() {
		return barsControl ;
	}
	
	
	/**
		CONNEXION TO ARDUINO BOARD.
		@param	currentPortCOM		Port number to connect. Should be "COMx" (where x is an integer).			
		@return 					None.
	*/
	public void connect(String currentPortCOM) {
		module = new Module(graphicInterface, currentPortCOM) ;
		if (module.connect() == 1) {
			connected = true ;
		}
	}
	
	
	/**
		SEND DATA TO ARDUINO BOARD.
	    @param input		Input instructions matrix.
	    @param movement		Boolean indicating the type of instructions to send.
	    						= true if interface is in movement control mode.
	    						= false if interface is in height control mode.
	    @return				None.
	*/	
	public void sendData(int[] matrix, boolean movement) {
		if (connected) {
			try {
				int scaleMode = representationControl.getScaleMode() ;
				int scaleMin = representationControl.getScaleMin() ;
				int scaleMax = representationControl.getScaleMax() ;
				module.update(matrix, movement, scaleMode, scaleMin, scaleMax) ;
			}
			catch (InterruptedException e) {}
			catch (IOException e) {}
		}
	}
	
	
	/**
		ENABLE ALL MOVEMENT RADIO BUTTONS.
		@param		None.
	    @return 	None.
	*/
	public void enableMovement() {
		int i = 0 ;
		for (i=0 ; i<Module.NUMBER_OF_BARS ; i++) {
			barsControl[i].enableMovement() ;
		}
	}
	
	
	/**
		ENABLE HEIGHT CONTROL (MAKING ALL THE TEXT FIELDS EDITABLE).
		@param		None.
	    @return 	None.
	*/
	public void enableHeight() {
		int i = 0 ;
		for (i=0 ; i<Module.NUMBER_OF_BARS ; i++) {
			barsControl[i].enableHeight() ;
		}
	}
	
	
	/**
		CHECK IF HEIGHTS ARE CORRECT FOR ALL THE BARS OF THE MODULE.
		@param		None.
	    @return 	None.
	*/
	public void checkBarArray() {
		int i = 0 ;
		errorHeight = false ;
		for (i=0 ; i<Module.NUMBER_OF_BARS ; i++) {
			if(barsControl[i].getErrorHeight() == true) {
				errorHeight = true ;
			}
		}
		// After updating errorHeight -> check all modules
		graphicInterface.checkModuleArray() ;
	}
	
	
	/**
		GET ERROR HEIGHT.
		@param					None.
	    @return errorHeight		Boolean indicating if all the heights entered are correct.
	    							= true if syntax error is found in the height of one bar (at least).
	    							= false otherwise.
	*/
	boolean getErrorHeight() {
		return errorHeight ;
	}
}
