/**
 * Javadoc
 * 
 * @author Ludovic Lesur
 * @since 13/07/2016
 */


package graphic ;
import barChart.* ;
import java.awt.* ;
import java.awt.event.* ;
import javax.swing.* ;


public class MovementControl extends JFrame implements ActionListener {
	
	private static final long serialVersionUID = 1L ;
	
	// Mother class
	private Interface graphicInterface ;
	
	// Panel and GBC
	private JPanel panel ;
	private GridBagConstraints gbc ;
		
	// Graphic components
	private JLabel title ;
	private JRadioButton heightControl ;
	private JRadioButton movementControl ;
	private ButtonGroup buttonGroup ;
	private JButton apply ;
	
	// Data members
	private int[] matrix ;
	private boolean repOK ;
	private boolean barOK ;
	private boolean movementActived ;
	

	/**
		CONSTRUCTOR FOR CLASS MOVEMENT CONTROL.
		@param pGraphicInterface :	The mother-class object (Interface).
		@param mainPanel :			The panel of the main interface.
		@param mainGbc :			The layout constraints of the main interface.
	    @return 	None.
	*/
	public MovementControl(Interface pGraphicInterface, JPanel mainPanel, GridBagConstraints mainGbc) {
		
		// Mother class
		graphicInterface = pGraphicInterface ;
		
		// Panel properties
		panel = new JPanel(new GridBagLayout()) ;
		panel.setBackground(Color.darkGray) ;
		
		// GBC properties
		gbc = new GridBagConstraints() ;
		gbc.insets = new Insets(10, 20, 10, 20) ;
		gbc.gridheight = 1 ;
		gbc.anchor = GridBagConstraints.CENTER ;	
		gbc.gridwidth = GridBagConstraints.REMAINDER ;
		
		// Graphic components
		gbc.gridx = 0 ;
		gbc.gridy = 0 ;
		title = new JLabel("Movement Control") ;
		title.setFont(new Font(Interface.POLICE.getFontName(), 2, 15)) ;
		title.setForeground(Color.yellow) ;
		panel.add(title, gbc) ;
		
		gbc.anchor = GridBagConstraints.WEST ;	
		gbc.gridwidth = 1 ;
		gbc.gridx = 0 ;
		gbc.gridy = 1 ;
		heightControl = new JRadioButton("Height Control") ;
		heightControl.setForeground(Color.white) ;
		heightControl.setFont(Interface.POLICE) ;
		heightControl.setOpaque(false) ;
		heightControl.addActionListener(this) ;
		heightControl.setSelected(true) ;
		panel.add(heightControl, gbc) ;
		
		gbc.gridx = 0 ;
		gbc.gridy = 2 ;
		movementControl = new JRadioButton("Movement") ;
		movementControl.setForeground(Color.gray) ;
		movementControl.setFont(Interface.POLICE) ;
		movementControl.setOpaque(false) ;
		movementControl.addActionListener(this) ;
		movementControl.setSelected(false) ;
		panel.add(movementControl, gbc) ;
		
		 
		gbc.gridheight = GridBagConstraints.REMAINDER ;
		gbc.gridx = 1 ;
		gbc.gridy = 1 ;
		apply = new JButton("APPLY") ;
		apply.setFont(new Font(Interface.POLICE.getFontName(), 2, 15)) ;
		apply.addActionListener(this) ;
		apply.setEnabled(false) ;
		panel.add(apply, gbc) ;
		
		buttonGroup = new ButtonGroup() ;
		buttonGroup.add(heightControl) ;
		buttonGroup.add(movementControl) ;
		
		// Data members
		matrix = new int[Module.NUMBER_OF_BARS] ;
		repOK = true ;
		barOK = true ;
		movementActived = false ;
		
		// Adding MovementControl to the main interface
		mainPanel.add(panel, mainGbc) ;
	}
	
	
	/**
		DEFAULT DISPLAY AT INITIALISATION.
		@param		None.
	    @return 	None.
	*/
	public void init() {
		enableHeight() ;
		movementActived = false ;
		enableHeight() ;
	}
	
	
	/**
		ENABLE APPLY BUTTON (AXIS OK)
		@param		None.
	    @return 	None.
	*/
	public void enableApplyRep() {
		repOK = true ;
		if (barOK == true) {
			apply.setEnabled(true) ;
		}
		else {
			apply.setEnabled(false) ;
		}
	}
	
	
	/**
		DISABLE APPLY BUTTON (AXIS ERROR)
		@param		None.
	    @return 	None.
	*/
	public void disableApplyRep() {
		repOK = false ;
		apply.setEnabled(false) ;
	}
	
	
	/**
		ENABLE APPLY BUTTON (HEIGHTS OK)
		@param		None.
	    @return 	None.
	*/
	public void enableApplyBar() {
		barOK = true ;
		if (repOK == true) {
			apply.setEnabled(true) ;
		}
		else {
			apply.setEnabled(false) ;
		}
	}
	
	
	/**
		DISABLE APPLY BUTTON (HEIGHT ERROR)
		@param		None.
	    @return 	None.
	*/
	public void disableApplyBar() {
		barOK = false ;
		apply.setEnabled(false) ;
	}
	
	
	/**
		ENABLE ALL MOVEMENT RADIO BUTTONS.
		@param		None.
	    @return 	None.
	*/
	private void enableMovement() {
		int i = 0 ;
		for (i=0 ; i<Module.NUMBER_OF_BARS ; i++) {
			graphicInterface.enableMovement() ;
		}
	}
	
	
	/**
		ENABLE HEIGHT CONTROL (MAKING ALL TEXT FIELDS EDITABLE).
		@param		None.
	    @return 	None.
	*/
	private void enableHeight() {
		int i = 0 ;
		for (i=0 ; i<Module.NUMBER_OF_BARS ; i++) {
			graphicInterface.enableHeight() ;
		}
	}
	
	
	/**
		BUTTONS PROCESSING.
		@param e :	Action event.
	    @return 	None.
	*/	
	public void actionPerformed(ActionEvent e) {
		
		if (e.getSource() == heightControl) {
			enableHeight() ;
			movementActived = false ;
			heightControl.setForeground(Color.white) ;
			movementControl.setForeground(Color.gray) ;
			graphicInterface.enableRepresentation() ;
		}
		
		if (e.getSource() == movementControl) {
			enableMovement() ;
			movementActived = true ;
			heightControl.setForeground(Color.gray) ;
			movementControl.setForeground(Color.white) ;
			graphicInterface.disableRepresentation() ;
			apply.setEnabled(true) ;
		}
		
		if (e.getSource() == apply) {
			int i = 0 ;
			int j = 0 ;
			// For each module...
			for (j=0 ; j<Module.NUMBER_OF_MODULES ; j++) {
				ModuleControl currentModule = graphicInterface.getModules()[j] ;
				// Movement instructions
				if (movementActived) {
					for (i=0 ; i<Module.NUMBER_OF_BARS ; i++) {
						matrix[i] = currentModule.getBars()[i].getInstruction() ;
						
					}
					currentModule.sendData(matrix, true) ;
				}
				// Height control
				else {
					for (i=0 ; i<Module.NUMBER_OF_BARS ; i++) {
						matrix[i] = currentModule.getBars()[i].getHeight() ;
					}
					currentModule.sendData(matrix, false) ;
				}
			}
		}
	}
}
