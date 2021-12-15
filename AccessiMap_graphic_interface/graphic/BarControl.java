/**
 * Javadoc
 * 
 * @author Ludovic Lesur
 * @since 18/07/2016
 */


package graphic ;
import barChart.* ;
import java.awt.* ;
import java.awt.event.* ;
import javax.swing.* ;
import javax.swing.event.* ;


public class BarControl extends JFrame implements ActionListener, DocumentListener {
	
	private static final long serialVersionUID = 1L ;
	
	// Mother class
	private ModuleControl moduleControl ;
	
	// Panel and GBC
	private JPanel panel ;
	private GridBagConstraints gbc ;
	
	// Graphic components
	private JLabel name ;
	private JLabel error ;
	private JTextField height ;
	private JRadioButton swing ;
	private JRadioButton vibration ;
	private JRadioButton off ;
	private ButtonGroup buttonGroup ;
	
	// Data members
	private int currentHeight ;
	private boolean errorHeight ;
	private int currentInstruction ;
	private static int numberOfBars ;
	
	
	/**
		CONSTRUCTOR FOR CLASS BAR CONTROL.
		@param pModuleControl	The mother-class object (ModuleControl).
		@param mainPanel		The panel of the main interface.
		@param mainGbc			The layout constraints of the main interface.
	    @return 				None.
	*/
	public BarControl(ModuleControl pModuleControl, JPanel mainPanel, GridBagConstraints mainGbc) {
		
		// Mother class
		moduleControl = pModuleControl ;
		
		// Panel properties
		panel = new JPanel(new GridBagLayout()) ;
		panel.setBackground(Color.darkGray) ;
		
		// GBC properties
		gbc = new GridBagConstraints() ;
		gbc.insets = new Insets(10, 10, 10, 10) ;
		gbc.anchor = GridBagConstraints.WEST ;
		gbc.gridwidth = 1 ;
		gbc.gridheight = 1 ;
		gbc.gridx = 0 ;
		
		// Data members
		currentHeight = 0 ;
		errorHeight = false ;
		currentInstruction = Module.INSTRUCTION_IMMOBILE ;
		numberOfBars++ ;
		
		// Graphic components
		gbc.gridy = 0 ;
		name = new JLabel("--- BAR " + numberOfBars + " ---") ;
		name.setForeground(Color.white) ;
		name.setFont(new Font(Interface.POLICE.getFontName(), 2, 15)) ;
		panel.add(name, gbc) ;
		
		gbc.gridy = 1 ;
		height = new JTextField(6) ;
		height.setText("0") ;
		height.setEditable(true) ;
		height.setFont(new Font(Interface.POLICE.getFontName(), 0, 15)) ;
		height.getDocument().addDocumentListener(this) ;
		panel.add(height, gbc) ;
		
		gbc.gridy = 2 ;
		error = new JLabel("Syntax Error") ;
		error.setForeground(Color.darkGray) ;
		error.setFont(Interface.POLICE) ;
		panel.add(error, gbc) ;
		
		gbc.gridy = 3 ;
		swing = new JRadioButton("Swing") ;
		swing.setForeground(Color.white) ;
		swing.setFont(Interface.POLICE) ;
		swing.setOpaque(false) ;
		swing.setSelected(false) ;
		swing.setEnabled(false) ;
		swing.addActionListener(this) ;
		panel.add(swing, gbc) ;
		
		gbc.gridy = 4 ;
		vibration = new JRadioButton("Vibration") ; 
		vibration.setForeground(Color.white) ;
		vibration.setFont(Interface.POLICE) ;
		vibration.setOpaque(false) ;
		vibration.setSelected(false) ;
		vibration.setEnabled(false) ;
		vibration.addActionListener(this) ;
		panel.add(vibration, gbc) ;
		
		gbc.gridy = 5 ;
		off = new JRadioButton("Off") ; 
		off.setForeground(Color.white) ;
		off.setFont(Interface.POLICE) ;
		off.setOpaque(false) ;
		off.setSelected(true) ;
		off.setEnabled(false) ;
		off.addActionListener(this) ;
		panel.add(off, gbc) ;
		
		// Making the radio buttons mutually exclusive
		buttonGroup = new ButtonGroup() ;
		buttonGroup.add(swing) ;
		buttonGroup.add(vibration) ;
		buttonGroup.add(off) ;
		
		// Adding BarControl to the main interface
		mainPanel.add(panel, mainGbc) ;
	}
	
	
	/**
		RESETS THE RADIO BUTTONS BY SELECTING 'OFF'.
		@param		None.
	    @return 	None.
	*/
	private void resetMovement() {
		swing.setSelected(false) ;
		vibration.setSelected(false) ;
		off.setSelected(true) ;
	}
	
	
	/**
		ENABLE MOVEMENT CONTROL.
		@param		None.
	    @return 	None.
	*/
	public void enableMovement() {
		// Disable height control
		height.setEditable(false) ;
		error.setForeground(Color.darkGray) ;
		// Enable movement control
		swing.setEnabled(true) ;
		vibration.setEnabled(true) ;
		off.setEnabled(true) ;
		resetMovement() ;
	}
	
	
	/**
		ENABLE HEIGHT CONTROL.
		@param		None.
	    @return 	None.
	*/
	public void enableHeight() {
		// Disable movement control
		swing.setEnabled(false) ;
		vibration.setEnabled(false) ;
		off.setEnabled(false) ;
		// Enable height control making the text field editable
		height.setEditable(true) ;
		checkHeight() ;
	}
	
	
	/**
		CHECKS IF A STRING IS ONLY COMPOSED BY NUMERIC CHARACTERS.
	    @param inputString :	The string to analyse.
	    @return 				Boolean indicating if the input string is only composed by numeric characters.
	    							= true if the input string can be converted to integer.
	    							= false otherwise.
	*/
	private boolean isNumeric(String inputString) {
		try {
			Integer.parseInt(inputString) ;
		}
		catch(NumberFormatException ex) {
			return false ;
		}
		return true ;
	}
	
	
	/**
		RETURNS THE VALUE READ IN THE HEIGHT TEXT FIELD.
		@param						None.
	    @return currentHeight :		The current height of the bar.
	*/
	public int getHeight() {
		return currentHeight ;
	}
	
	
	/**
		RETURNS THE INSTRUCTION CORRESPONDING TO THE SELECTED MOVEMENT ITEM.
		@param							None.
	    @return currentInstruction : 	The current movement instruction of the bar.
	*/
	public int getInstruction() {
		return currentInstruction ;
	}
	
	
	/**
		GET ERROR HEIGHT.
		@param					None.
	    @return errorHeight	:	Boolean indicating if the height entered in the text field is correct.	
	    							= true if a syntax error is found in the text field.
	    							= false otherwise.
	*/
	boolean getErrorHeight() {
		return errorHeight ;
	}
	
	
	/**
		RADIO BUTTONS PROCESSING.
		@param e	Action event.
	    @return 	None.
	*/
	public void actionPerformed(ActionEvent e) {
		
		// Assign 'currentInstruction' depending on the selected movement button.
		if (e.getSource() == swing) {
			currentInstruction = Module.INSTRUCTION_SWING ;
		}
		if (e.getSource() == vibration) {
			currentInstruction = Module.INSTRUCTION_VIBRATION ;
		}
		if (e.getSource() == off) {
			currentInstruction = Module.INSTRUCTION_IMMOBILE ;
		}
	}
	
	
	/**
		CHECK IF THE HEIGHT ENTERED IN THE TEXT FIELD IS CORRECT.
		@param e	Keyboard event.
	    @return 	None.
	*/
	@Override
	public void changedUpdate(DocumentEvent e) {
		checkHeight() ;
	}
	
	@Override
	public void insertUpdate(DocumentEvent e) {
		checkHeight() ;
	}
	
	@Override
	public void removeUpdate(DocumentEvent e) {
		checkHeight() ;
	}
	
	private void checkHeight() {
		if (isNumeric(height.getText())) {
			currentHeight = Integer.parseInt(height.getText()) ;
			// Make the error label invisible
			error.setForeground(Color.darkGray) ;
			errorHeight = false ;
		}
		else {
			// Make the error label visible
			error.setForeground(Color.red) ;
			errorHeight = true ;
		}
		// This bar has changed, so we have to check all other bars
		moduleControl.checkBarArray() ;
	}
}
