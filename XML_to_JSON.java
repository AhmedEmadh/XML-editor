/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package DS;

import org.json.*; 
import java.io.*;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Scanner;

/**
 *
 * @author Mohamed Hassan
 */
public class XML_to_JSON {
    
    //Scanner xmlString = new Scanner (System.in);
    ///public String xml2 = xmlString.next();
    public static String xml = ReadText.Readtext();
    public static void Convert() {
    
        try {  
                 JSONObject json = XML.toJSONObject(xml);   
                 String jsonString = json.toString(4);  
                 System.out.println(jsonString);  
  
}
          
          catch (JSONException e) {  
// TODO: handle exception  
          System.out.println(e.toString());  
             }  
  
           } 
        

    
    }
