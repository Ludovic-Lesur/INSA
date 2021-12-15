/**
 * Javadoc
 * 
 * @author Ludovic Lesur.
 * @since 05/07/2016.
 */


package barChart ;
import arduino.* ;
import graphic.* ;
import java.io.* ;


public class Module {
	
	// Mother classe
	private Interface graphicInterface ;
	
	// Data members
	private ArduinoBoard arduino ;
	private int[] rawMatrix ;
	private int[] matrix ;
	
	// Instructions coding (Java -> Arduino)
	public static final int OFFSET = 128 ;
	public static final int INSTRUCTION_SWING = 229 ;
	public static final int INSTRUCTION_VIBRATION = 230 ;
	public static final int INSTRUCTION_IMMOBILE = 231 ;
	public static final int INSTRUCTION_CALIBRATION = 255 ;
	
	// Number of bars in 1 module
	public static final int NUMBER_OF_BARS = 4 ;
	// Number of modules in the bar chart
	public static final int NUMBER_OF_MODULES = 2 ;
	
	
	/**
		CONSTRUCTOR FOR CLASS MODULE.
		@param pGraphicInterface	The mother-class object (Interface).
	    @param pNumPort	 			Port number to connect. Should be "COMx" (where x is an integer).
	    @return 					None.
	*/
    public Module(Interface pGraphicInterface, String pNumPort) {
    	
    	// Mother class
    	graphicInterface = pGraphicInterface ;
    	
    	// Initialisation of 'matrix' and 'rawMatrix'
    	int i = 0 ;
    	matrix = new int[NUMBER_OF_BARS] ;
    	rawMatrix = new int[NUMBER_OF_BARS] ;
        for (i=0 ; i<NUMBER_OF_BARS ; i++) {
        	rawMatrix[i] = 0 ;
            matrix[i] = 0 ;
        }
        
        // ArduinoBoard object
        arduino = new ArduinoBoard(pNumPort, this) ;
    }
    
    
    /**
		GET THE RAW MATRIX.
	    @param				None.
	    @return raxMatrix 	The array of integers containing raw walues.
	*/
	public int[] getRawMatrix() {
	    return rawMatrix ;
	}
	
	
	/**
		GET THE ARDUINO BOARD OBJECT.
	    @param					None.
	    @return arduinoBoard 	The ArduinoBoard object associated to the module.
	*/
	public ArduinoBoard getArduino() {
	    return arduino ;
	}

    
    /**
		CONNEXION TO ARDUINO BOARD.
	    @param		None.
	    @return 	Integer indicating the state of the serial communication.
	    				= 1 if serial port was successfully opened.
	    				= 0 if the process failed.
	    				= -1 if the serial port is allready in use.
	*/
    public int connect() {
        return arduino.connect() ;
    }
    
    
    /**
		RESCALING BAR CHART HEIGHTS WITH POURCENTAGE METHOD.
	    @param matrix		Initial array of integers modified by the function.
	    @return 			None.
	*/
    private void scaleDataPourcentage(int[] matrix) {
    	int maxValue = graphicInterface.getMaximumValue() ;
        // Convert each value to pourcentage of the maximum
    	int i = 0 ;
        for (i=0 ; i<NUMBER_OF_BARS ; i++) {
            matrix[i] = (int) (100.0*((double)matrix[i]/(double)maxValue)) ;
        }
    }
    
    
    /**
		RESCALING BAR CHART HEIGHTS WITH MAXIMUM CONTRAST METHOD.
	    @param matrix		Initial array of integers modified by the function.
	    @return 			None.
	*/
    private void scaleDataContrast(int[] matrix) {
    	int maxValue = graphicInterface.getMaximumValue() ;
        int minValue = graphicInterface.getMinimumValue() ;
        // Convert each value to pourcentage of the distance between minValue and maxValue
        int i = 0 ;
        double a = (100.0)/(maxValue-minValue) ;
        for (i=0 ; i<NUMBER_OF_BARS ; i++) { 	
            matrix[i] = (int) (a*((double)matrix[i]-(double)minValue)) ;
        }
    }
    
    
    /**
		RESCALING BAR CHART HEIGHTS WITH ABSOLUTE METHOD
	    @param matrix		Initial array of integers modified by the function.
	    @param scaleMin		Minimum value of y-axis.
	    @param scaleMax		Maximum value of y-axis.
	    @return 			None.
	*/
    private void scaleDataAbsolute(int[] matrix, int scaleMin, int scaleMax) {
    	int i = 0 ;
    	for (i=0 ; i<NUMBER_OF_BARS ; i++) {
            matrix[i] = (int) (100.0*((double)matrix[i]-(double)scaleMin)/((double)scaleMax-(double)scaleMin)) ;
            // Ensure pourcentage is between 0 and 100%
            if (matrix[i] < 0) {
            	matrix[i] = 0 ;
            }
            if (matrix[i] > 100){
            	matrix[i] = 100 ;
            }
        }
    }
    
    
    /**
		RESCALING BAR CHART HEIGHTS.
	    @param matrix		Initial array of integers.
	    @param scaleMode 	Indicates the scaling method.
		    					0 = pourcentage method.
		    					1 = maximum contrast method.
		    					2 = absolute method.
	    @return 			None.
	*/
    private void scaleData(int[] matrix, int scaleMode, int scaleMin, int scaleMax) {
    	System.out.println("Rescaling matrix...") ;
    	// Call the right function depending on 'scaleMode'
        switch(scaleMode) {
        case 0 :
        	scaleDataPourcentage(matrix) ;
        	break ;
        case 1 :
        	scaleDataContrast(matrix) ;
        	break ;
        case 2 :
        	scaleDataAbsolute(matrix, scaleMin, scaleMax) ;
        	break ;
        }	
    }
    
    
    /**
		SEND DATA MATRIX TO ARDUINO BOARD.
	    @param matrix		Array of integers to send (and to rescale if necesary).
	    @return 			None.
	*/
    public void sendData(int[] matrix) throws InterruptedException, IOException {
        int i = 0 ;
        for (i=0 ; i<NUMBER_OF_BARS ; i++) {
            // First data = bar state (height or movement) with MSB = 1
            arduino.writeData(matrix[i]) ;
            Thread.sleep(ArduinoBoard.DELAY) ;
            // Second data = bar number with MSB = 0
            arduino.writeData(i) ;
            Thread.sleep(ArduinoBoard.DELAY) ;
        }
    }
    
    
    /**
		COPY A MATRIX OF INTEGERS INTO ANOTHER.
	    @param source		The matrix to copy.
	    @param destination 	The matrix which will be modified (destination = source).
	    @return				None.
	*/	
    private void copyMatrix(int[] source, int[] destination) {
    	if (source.length == destination.length) {
    		int i ;
    		for (i=0 ; i<source.length ; i++) {
    			destination[i] = source[i] ;
    		}
    	}
    }
    
    
    /**
		UPDATE FUNCTION.
	    @param input		Input instruction.
	    @param movement		Boolean indicating the type of instructions to send.
	    						= true if interface is in movement control mode.
	    						= false if interface is in height control mode.
	    @param scaleMode 	Indicates scaling method for the function scaleData().
	    						0 = pourcentage method.
	    						1 = maximum contrast method.
	    						2 = absolute method
	    @param scaleMin		Minimum value of y-axis (used if scaleMode = 2).
	    @param scaleMax		Maximum value of y-axis (used if scaleMode = 2).
	    @return				None.
	*/	
    public void update(int[] input, boolean movement, int scaleMode, int scaleMin, int scaleMax) throws InterruptedException, IOException {
    	copyMatrix(input, matrix) ;
    	if (movement == false) {
    		System.out.println("\nHeight instructions.") ;
    		// Keep the 'rawMatrix' for the voice synthesis, while 'matrix' is going to be rescaled
    		copyMatrix(input, rawMatrix) ;
    		scaleData(matrix, scaleMode, scaleMin, scaleMax) ;
    		int i = 0 ;
    		// We send heights -> values have to be shifted
    		for (i=0 ; i<NUMBER_OF_BARS ; i++) {
    			matrix[i] = matrix[i]+OFFSET ;
      		}
    	}
    	else {
    		// Movement instructions -> matrix is allready correct
    		System.out.println("\nMovement instructions.") ;
    	}
        sendData(matrix) ;
    }
    
    
    /**
		VOICE SYNTHESIS CALLED WHEN A BUTTON IS PRESSED ON THE BAR CHART
	    @param numBar		The bar identifiant (between 0 and NUMBER_OF_BARS-1).
	    @return				None.
	*/
    public void voiceSynthesis(int numBar) {
    	// Here we should call voice synthesis function
    	// Voice have to say <rawMatrix[numBar]>
    	System.out.println("Voice = " + rawMatrix[numBar]) ;
    }
    
    
    /**
		CLOSES ARDUINO SERIAL PORT.
	    @param		None.
	    @return		None.
	*/
    public void close() {
    	arduino.close() ;
    }
}
