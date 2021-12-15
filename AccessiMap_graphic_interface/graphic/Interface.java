/**
 * Javadoc
 * 
 * @author Ludovic Lesur
 * @since 20/07/2016
 */


package graphic ;
import barChart.* ;
import java.awt.* ;
import java.io.* ;
import javax.swing.* ;


public class Interface {
	
	// Window, panel and layout constraints properties
	private JFrame fenetre ;
	private JPanel mainPanel ;
	private JLabel mainTitle ;
	private GridBagConstraints mainGbc ;
	// Default font of the interface
	public final static Font POLICE = new Font("Calibri", 1, 11) ;
	
	// Graphic components
	private ModuleControl[] modulesControl ;
	private MovementControl movementControl ;
	private RepresentationControl representationControl ;
	
	
	/**
		CONSTRUCTOR FOR CLASS INTERFACE.
		@param		None.
	    @return 	None.
	*/
	public Interface() {
		
		// Windows properties
		fenetre = new JFrame() ;
		fenetre.setTitle("ACCESSI MAP - 3D BAR CHART CONTROL") ;
		fenetre.setLocationRelativeTo(null) ;	
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE) ;
		fenetre.setExtendedState(JFrame.MAXIMIZED_BOTH) ;
		
		// Panel properties
		mainPanel = new JPanel(new GridBagLayout()) ;
		mainPanel.setBackground(Color.darkGray) ;
		
		// GBC properties
		mainGbc = new GridBagConstraints() ;
		mainGbc.insets = new Insets(10, 40, 10, 40) ;
		mainGbc.anchor = GridBagConstraints.CENTER ;
		
		// Graphic components
		mainGbc.gridwidth = GridBagConstraints.REMAINDER ;
		mainGbc.gridx = 0 ;
		mainGbc.gridy = 0 ;
		mainTitle = new JLabel("ACCESSI MAP - 3D BAR CHART CONTROL") ;
		mainTitle.setFont(new Font(POLICE.getFontName(), 2, 25)) ;
		mainTitle.setForeground(Color.white) ;
		mainPanel.add(mainTitle, mainGbc) ;
		
		// Representation control
		mainGbc.gridwidth = 1 ;
		mainGbc.gridheight = 1 ;
		mainGbc.gridx = 0 ;
		mainGbc.gridy = 1 ;
		representationControl = new RepresentationControl(this, mainPanel, mainGbc) ;
		
		// Movement control
		mainGbc.gridx = 1 ;
		mainGbc.gridy = 1 ;
		movementControl = new MovementControl(this, mainPanel, mainGbc) ;
		
		// Modules control
		mainGbc.gridx = 0 ;
		mainGbc.gridy = 2 ;
		modulesControl = new ModuleControl[Module.NUMBER_OF_MODULES] ;
		int i = 0 ;
		for (i=0 ; i<Module.NUMBER_OF_MODULES ; i++) {
			mainGbc.gridx = i ;
			modulesControl[i] = new ModuleControl(this, representationControl, mainPanel, mainGbc) ;
		}
		
		// Opening interface
		fenetre.setContentPane(mainPanel) ;
		fenetre.setVisible(true) ;
	}
	
	
	/**
		INITIALISATION OF GRAPHIC INTERFACE.
	    @param 		None.
	    @return		None.
	*/	
	void init() {
		movementControl.init() ;
	}
	
	
	/**
		GET THE ARRAY OF MODULES.
	    @param 						None.
	    @return	modulesControl :	Array of objects ModuleControl.
	*/	
	ModuleControl[] getModules() {
		return modulesControl ;
	}
	
	
	/**
		GET THE MAXIMUM HEIGHT OF THE WHOLE BAR CHART.
	    @param 					None.
	    @return	minValue		Maximum value of all the bars.
	*/	
	public int getMaximumValue() {
		int maxValue = Integer.MIN_VALUE ;
        int i = 0 ;
        int j = 0 ;
        // Modules loop...
        for (i=0 ; i<Module.NUMBER_OF_MODULES ; i++) {
        	BarControl[] currentGroup = modulesControl[i].getBars() ;
        	// Bars loop...
		    for (j=0 ; j<Module.NUMBER_OF_BARS ; j++) {
		    	BarControl currentBar = currentGroup[j] ;
		    	if (currentBar.getHeight() > maxValue) {
		    		maxValue = currentBar.getHeight() ;
		        }
		    }
        }
        return maxValue ;
	}
	
	
	/**
		GET THE MINIMUM HEIGHT OF THE WHOLE BAR CHART.
	    @param 					None.
	    @return	minValue		Minimum value of all the bars.
	*/	
	public int getMinimumValue() {
		int minValue = Integer.MAX_VALUE ;
        int i = 0 ;
        int j = 0 ;
        // Modules loop...
        for (i=0 ; i<Module.NUMBER_OF_MODULES ; i++) {
        	BarControl[] currentGroup = modulesControl[i].getBars() ;
        	// Bars loop...
		    for (j=0 ; j<Module.NUMBER_OF_BARS ; j++) {
		    	BarControl currentBar = currentGroup[j] ;
		    	if (currentBar.getHeight() < minValue) {
		    		minValue = currentBar.getHeight() ;
		        }
		    }
        }
        return minValue ;
	}
	
	
	/**
		ENABLE APPLY BUTTON (AXIS OK)
		@param		None.
	    @return 	None.
	*/
	public void enableApplyRep() {
		movementControl.enableApplyRep() ;
	}
	
	
	/**
		DISABLE APPLY BUTTON (AXIS ERROR)
		@param		None.
	    @return 	None.
	*/
	public void disableApplyRep() {
		movementControl.disableApplyRep() ;
	}
	
	
	/**
		ENABLE ALL MOVEMENT RADIO BUTTONS.
		@param		None.
	    @return 	None.
	*/
	public void enableMovement() {
		int i = 0 ;
		for (i=0 ; i<Module.NUMBER_OF_MODULES ; i++) {
			modulesControl[i].enableMovement() ;
		}
	}
	
	
	/**
		ENABLE HEIGHT CONTROL (MAKING ALL TEXT FIELDS EDITABLE).
		@param		None.
	    @return 	None.
	*/
	public void enableHeight() {
		int i = 0 ;
		for (i=0 ; i<Module.NUMBER_OF_MODULES ; i++) {
			modulesControl[i].enableHeight() ;
		}
	}
	
	
	/**
		ENABLE REPRESENTATION CONTROL (HEIGHT CONTROL ACTIVED)
	    @param 		None.
	    @return 	None.
	*/
	void enableRepresentation() {
		representationControl.enable() ; 
	}
	
	
	/**
		DISABLE REPRESENTATION CONTROL (MOVEMENT CONTROL ACTIVED)
	    @param 		None.
	    @return 	None.
	*/
	void disableRepresentation() {
		representationControl.disable() ;
	}
	
	
	/**
		CHECKS IF HEIGHTS ARE CORRECT FOR ALL THE MODULES.
		@param		None.
	    @return 	None.
	*/
	public void checkModuleArray() {
		movementControl.enableApplyBar() ;
		int i = 0 ;
		for (i=0 ; i<Module.NUMBER_OF_MODULES ; i++) {
			if(modulesControl[i].getErrorHeight() == true) {
				movementControl.disableApplyBar() ;
			}
		}
	}

	
	/**
		MAIN FUNCTION.
		@param		None.
	    @return 	None.
	*/
	public static void main(String[] args) throws IOException {
	
		// Lauching interface...
		Interface IHM = new Interface() ;
		IHM.init() ;
	}
}