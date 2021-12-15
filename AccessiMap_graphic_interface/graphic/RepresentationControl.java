/**
 * Javadoc
 * 
 * @author Ludovic Lesur
 * @since 19/07/2016
 */


package graphic ;
import java.awt.* ;
import java.awt.event.* ;
import javax.swing.* ;
import javax.swing.event.* ;


public class RepresentationControl implements DocumentListener {
	
	// Mother class
	private Interface graphicInterface ;
	
	// Panel and GBC
	private JPanel panel ;
	private GridBagConstraints gbc ;
	
	// Graphic components
	private JLabel title ;
	private JComboBox<String> menuMethods ;
	private JLabel min ;
	private JTextField fieldMin ;
	private JLabel max ;
	private JTextField fieldMax ;
	private JLabel error ;
	
	// Data members
	private int scaleMode ;
	public static final String SCALE_MODE_0 = "Pourcentage" ;
	public static final String SCALE_MODE_1 = "Maximum contrast" ;
	public static final String SCALE_MODE_2 = "Absolute" ;
	private int minAxis ;
	private int maxAxis ;
	

	/**
		CONSTRUCTOR FOR CLASS REPRESENTATION CONTROL.
		@param pGraphicInterface :	The mother-class object (Interface).
		@param mainPanel :			The panel of the main interface.
		@param mainGbc :			The layout constraints of the main interface.
	    @return 					None.
	*/
	public RepresentationControl(Interface pGraphicInterface, JPanel mainPanel, GridBagConstraints mainGbc) {
		
		// Mother-class object
		graphicInterface = pGraphicInterface ;
		
		// Panel properties
		panel = new JPanel(new GridBagLayout()) ;
		panel.setBackground(Color.darkGray) ;
		
		// GBC properties
		gbc = new GridBagConstraints() ;
		gbc.insets = new Insets(10, 20, 10, 20) ;
		gbc.anchor = GridBagConstraints.CENTER ;
		
		// Graphic components
		gbc.gridheight = 1 ;
		gbc.gridwidth = 3 ;
		gbc.gridx = 0 ;
		gbc.gridy = 0 ;
		title = new JLabel("Representation Control") ;
		title.setFont(new Font(Interface.POLICE.getFontName(), 2, 15)) ;
		title.setForeground(Color.yellow) ;
		panel.add(title, gbc) ;
		
		
		gbc.anchor = GridBagConstraints.WEST ;
		gbc.gridwidth = 1 ;
		gbc.gridx = 0 ;
		gbc.gridy = 1 ;
		String[] boxSeries = {SCALE_MODE_0, SCALE_MODE_1, SCALE_MODE_2} ;
		menuMethods = new JComboBox<String>(boxSeries) ;
		menuMethods.addItemListener(new ItemState()) ;
		menuMethods.setFont(Interface.POLICE) ;
		panel.add(menuMethods, gbc) ;
		gbc.insets.bottom = 0 ;
		
		gbc.gridx = 1 ;
		gbc.gridy = 1 ;
		max = new JLabel("Max") ;
		max.setForeground(Color.gray) ;
		max.setFont(Interface.POLICE) ;
		panel.add(max, gbc) ;
		
		gbc.gridx = 2 ;
		gbc.gridy = 1 ;
		fieldMax = new JTextField(8) ;
		fieldMax.setText("0") ;
		fieldMax.setFont(Interface.POLICE) ;
		fieldMax.setEditable(false) ;
		fieldMax.getDocument().addDocumentListener(this) ;
		panel.add(fieldMax, gbc) ;
		
		gbc.insets.bottom = 10 ;
		gbc.insets.top = 0 ;
		gbc.gridx = 1 ;
		gbc.gridy = 2 ;
		min = new JLabel("Min") ;
		min.setForeground(Color.gray) ;
		min.setFont(Interface.POLICE) ;
		panel.add(min, gbc) ;
		
		gbc.gridx = 2 ;
		gbc.gridy = 2 ;
		fieldMin = new JTextField(8) ;
		fieldMin.setText("0") ;
		fieldMin.setFont(Interface.POLICE) ;
		fieldMin.setEditable(false) ;
		fieldMin.getDocument().addDocumentListener(this) ;
		panel.add(fieldMin, gbc) ;
		
		gbc.gridx = 2 ;
		gbc.gridy = 3 ;
		error = new JLabel("Syntax error") ;
		error.setFont(Interface.POLICE) ;
		error.setForeground(Color.darkGray) ;
		panel.add(error, gbc) ;	
		
		// Data members
		scaleMode = 0 ;
		minAxis = 0 ;
		maxAxis = 0 ;
		
		// Adding RepresentationControl to the main interface.
		mainPanel.add(panel, mainGbc) ;
	}
	
	
	/**
		ENABLE ABSOLUTE SCALING (MAKES TEXT FIELDS EDITABLE).
		@param		None.
	    @return 	None.
	*/
	private void enableAbsoluteScaling() {
		fieldMin.setEditable(true) ;
		fieldMax.setEditable(true) ;
		min.setForeground(Color.white) ;
		max.setForeground(Color.white) ;
		checkAxis() ;
	}
	
	
	/**
		DISABLE ABSOLUTE SCALING (MAKES TEXT FIELDS DISABLED).
		@param		None.
	    @return 	None.
	*/
	private void disableAbsoluteScaling() {
		fieldMin.setEditable(false) ;
		fieldMax.setEditable(false) ;
		min.setForeground(Color.gray) ;
		max.setForeground(Color.gray) ;
		error.setForeground(Color.darkGray) ;
	}
	
	
	/**
		GET SCALE MODE.
		@param					None.
	    @return scaleMode : 	Indicates the scaling method.
		    						0 = pourcentage method.
		    						1 = maximum contrast method.
		    						2 = absolute method.
	*/
	public int getScaleMode() {
		return scaleMode ;
	}
	
	
	/**
		GET THE MINIMUM VALUE OF Y-AXIS.
		@param					None.
	    @return minimumValue	Minimum value of y-axis read in text field.
	    							= 0 if syntaxe error is found
	*/
	public int getScaleMin() {
		return minAxis ;
	}
	
	
	/**
		GET THE MAXIMUM VALUE OF Y-AXIS.
		@param					None.
	    @return maximumValue	Maximum value of y-axis read in text field.
	    							= 0 if syntaxe error is found.
	*/
	public int getScaleMax() {
		return maxAxis ;
	}
	
	
	/**
		DROP-DOWN MENU PROCESSING.
		@param e	Item event.
	    @return 	None.
	*/
	class ItemState implements ItemListener {
	
		public void itemStateChanged(ItemEvent e) {
			if (e.getSource() == menuMethods) {
				String item = (String)e.getItem() ;
				// Assign 'scaleMode' depending on the selected representation method
				if (item.compareTo(SCALE_MODE_0) == 0) {
					scaleMode = 0 ;
					disableAbsoluteScaling() ;
				}
				if (item.compareTo(SCALE_MODE_1) == 0) {
					scaleMode = 1 ;
					disableAbsoluteScaling() ;
				}
				if (item.compareTo(SCALE_MODE_2) == 0) {
					scaleMode = 2 ;
					enableAbsoluteScaling() ;
				}
			}
		}
	}
	
	
	/**
		ENABLE REPRESENTATION CONTROL (HEIGHT CONTROL ACTIVED)
	    @param 		None.
	    @return 	None.
	*/
	void enable() {
		menuMethods.setEnabled(true) ;
		if (scaleMode == 2) {
			fieldMin.setEditable(true) ;
			fieldMax.setEditable(true) ;
			min.setForeground(Color.white) ;
			max.setForeground(Color.white) ;
			checkAxis() ;
		}
	}
	
	
	/**
		DISABLE REPRESENTATION CONTROL (MOVEMENT CONTROL ACTIVED)
	    @param 		None.
	    @return 	None.
	*/
	void disable() {
		menuMethods.setEnabled(false) ;
		fieldMin.setEditable(false) ;
		fieldMax.setEditable(false) ;
		min.setForeground(Color.gray) ;
		max.setForeground(Color.gray) ;
		error.setForeground(Color.darkGray) ;
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
		CHECKS IF MIN AND MAX VALUES ARE CORRECT
		@param e	Keyboard event.
	    @return 	None.
	*/
	@Override
	public void changedUpdate(DocumentEvent e) {
		checkAxis() ;
	}

	@Override
	public void insertUpdate(DocumentEvent e) {
		checkAxis() ;
	}

	@Override
	public void removeUpdate(DocumentEvent e) {
		checkAxis() ;
	}
	
	private void checkAxis() {
		error.setText("Syntax error") ;
		boolean errorFound = true ;
		
		// Check if min value is a number...
		if (isNumeric(fieldMin.getText()) == false) {
			// Make error label visible
			error.setForeground(Color.red) ;
		}
		else {
			minAxis = Integer.parseInt(fieldMin.getText()) ;
			// Check if max value is a number...
			if (isNumeric(fieldMax.getText()) == false) {
				// Make error label visible
				error.setForeground(Color.red) ;
			}
			else {
				maxAxis = Integer.parseInt(fieldMax.getText()) ;
				// Check if min < max
				if (minAxis > maxAxis) {
					error.setText("Max < Min") ;
					error.setForeground(Color.red) ;
				}
				else {
					error.setForeground(Color.darkGray) ;
					errorFound = false ;
				}
			}
		}
		if (errorFound == true) {
			// If a syntax error is found -> disable 'Apply' button
			graphicInterface.disableApplyRep() ;
		}
		else {
			graphicInterface.enableApplyRep() ;
		}
	}
}
