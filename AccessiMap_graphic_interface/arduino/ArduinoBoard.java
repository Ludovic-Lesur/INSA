/**
 * Javadoc
 * 
 * @author Ludovic Lesur
 * @since 05/07/2016
 */


package arduino ;
import barChart.* ;
import java.util.* ;
import java.io.* ;
import gnu.io.* ;


public class ArduinoBoard implements SerialPortEventListener {
	
	// Mother class
	private Module module ;
	
	// Data members
	private String numPort ;
	private SerialPort serialPort ;
	private BufferedReader input ;
	private OutputStream output ;
	private String name = "Arduino" ;
	
	// Serial port settings
	public static final int DELAY = 10 ; // Delay (in ms) between two sending to the Arduino board
	private static final int TIME_OUT = 2000 ; // Time to wait while trying to open serial port
	private static final int BAUD_RATE = 9600 ; // Baud rate
	

	/**
		CONSTRUCTOR FOR CLASS ARDUINOBOARD.
	    @param pNumPort :	Port number to connect, should be "COMx" where x is an integer.
	    @param pModule :	The mother-class object (Module) used for the voice synthesis.
	    @return 			None.
	*/
	public ArduinoBoard(String pNumPort, Module pModule) {
		numPort = pNumPort ;
		module = pModule ;
	}

	
	/**
		INITIALISATION OF SERIAL PORT.
	    @param			None.
	    @return state 	Integer indicating the state of the serial communication.
	    					= 1 if serial port was successfully opened.
	    					= 0 if the process failed.
	    					= -1 if the serial port is allready in use.
	*/
	public int connect() {

		int opened = 0 ;
		
		CommPortIdentifier portId = null ;
		
		// Get all the COM ports currently connected
		@SuppressWarnings("rawtypes")
		Enumeration portEnum = CommPortIdentifier.getPortIdentifiers() ;
		
		while (portEnum.hasMoreElements()) {
			CommPortIdentifier currPortId = (CommPortIdentifier) portEnum.nextElement() ;
			if (currPortId.getName().equals(numPort)) {
				portId = currPortId ;
			}
		}
		System.out.print("Connexion to Arduino board : ") ;
		if (portId == null) {
			System.out.println("failed.") ;
		}
		else {
			try {
				// Open serial port
				serialPort = (SerialPort) portId.open(this.getClass().getName(), TIME_OUT) ;
				serialPort.setSerialPortParams(BAUD_RATE, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE) ;
	
				// Input and output streams
				input = new BufferedReader(new InputStreamReader(serialPort.getInputStream())) ;
				serialPort.addEventListener(this) ;
				serialPort.notifyOnDataAvailable(true) ;
				output = serialPort.getOutputStream() ;
				System.out.println("OK.") ;
				opened = 1 ;
			}
			catch (PortInUseException e) {
				System.out.println("Serial port is allready in use !") ;
				opened = -1 ;
			}
			catch (Exception e) {
				System.err.println(e.toString()) ;
			}
		}
		return opened ;
	}
	
	
	/**
		WRITE DATA ON SERIAL PORT.
	    @param data		Byte to send.
	    @return 		None.
	*/
	public void writeData(int data) throws IOException {
	    if (output != null) {
	    	// Display the binary and decimal representation of the byte sent
	    	System.out.println("Send data '" + Integer.toBinaryString(data) + "' = " + data + " to " + name) ;
	    	output.write(data) ;
	    }
	}
	
	
	/**
		READ DATA FROM SERIAL PORT.
	    @param e		Serial port event.
	    @return 		None.
	*/
	public synchronized void serialEvent(SerialPortEvent e) {
		if (e.getEventType() == SerialPortEvent.DATA_AVAILABLE) {
			try {
				int inputData = input.read() ;
				module.voiceSynthesis(inputData) ;
				
			} catch (Exception ex) {
				System.err.println(ex.toString()) ;
			}
		}
	}

	
	/**
		CLOSE SERIAL PORT.
	    @param		None.
	    @return 	None.
	*/
	public synchronized void close() {
		if (serialPort != null) {
			serialPort.close() ;
			serialPort.removeEventListener() ;
		}
	}
}
