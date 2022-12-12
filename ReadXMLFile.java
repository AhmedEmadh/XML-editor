package DS;
import java.io.*;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Mohamed Hassan
 */
public class ReadText {
    
    public static String Readtext() {
    
      
            try {
                // Creating a path choosing file from local
                // directory by creating an object of Path class
                Path fileName = Path.of("D:\\XMLFile.xml");
                
                // Now calling Files.readString() method to
                // read the file
                 String str = Files.readString(fileName);
                
                // Printing the string
                System.out.println(str);
                
                
            } catch (IOException ex) {
                Logger.getLogger(ReadText.class.getName()).log(Level.SEVERE, null, ex);
            }
               return "" ;
                
    }
    
   
              
    
}
