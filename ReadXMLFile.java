/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package DS;
import java.io.File; 
import javax.xml.parsers.DocumentBuilderFactory;  
import javax.xml.parsers.DocumentBuilder;
import org.w3c.dom.Document; 
import org.w3c.dom.NodeList;  
import org.w3c.dom.Node;  
import org.w3c.dom.Element;  
import org.w3c.dom.NamedNodeMap;
import java.util.*;


/**
 *
 * @author Mohamed Hassan
 */
public class ReadXMLFile {
    
    // C:\Users\moham\OneDrive\Desktop\Documents\NetBeansProjects\My_Project
    //D:\\
    
  
     public static void printNodeList(NodeList nodeList)  
     { 
           
            for (int count = 0; count < nodeList.getLength(); count++)   
     {  
             Node elemNode = nodeList.item(count);  
             if (elemNode.getNodeType() == Node.ELEMENT_NODE)   
            {  
               // get node name and value  
             System.out.println("\nNode Name =" + elemNode.getNodeName()+ " [OPEN]");  
             System.out.println("Node Content =" + elemNode.getTextContent());  
          if (elemNode.hasAttributes())   
          {  
            NamedNodeMap nodeMap = elemNode.getAttributes();  
             for (int i = 0; i < nodeMap.getLength(); i++)   
             {  
              Node node = nodeMap.item(i);  
             System.out.println(" name : " + node.getNodeName());  
             System.out.println(" value : " + node.getNodeValue());  
             }  
             }  
              if (elemNode.hasChildNodes())   
              {  
//recursive call if the node has child nodes  
                printNodeList(elemNode.getChildNodes());  
               }  
           System.out.println("Node Name =" + elemNode.getNodeName()+ " [CLOSE]");  
           }  
}  
}  
     
     public static void main(String arg[]){
     
         // ReadText.Readtext();
   
         // XML_to_JSON.Convert();
     
         try   
          {  
              System.out.println("Enter file path");
              Scanner input = new Scanner ( System.in );
               String filepath = input.next();
       File file = new File(filepath);  
       DocumentBuilder documentBuilder = DocumentBuilderFactory.newInstance().newDocumentBuilder();  
       Document document = documentBuilder.parse(file);  
       System.out.println("Root element: "+ document.getDocumentElement().getNodeName());  
    if (document.hasChildNodes())   
    {  
           printNodeList(document.getChildNodes());  
    }  
        }   
   catch (Exception e)  
   {  
              System.out.println(e.getMessage());  
   }
     
     
     }
    
    
}
