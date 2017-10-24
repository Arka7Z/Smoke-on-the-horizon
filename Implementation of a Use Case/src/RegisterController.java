
package javafxapplication2;

import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXPasswordField;
import com.jfoenix.controls.JFXTextField;
import java.io.EOFException;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.URL;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.ResourceBundle;
import java.util.concurrent.TimeUnit;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.stage.Stage;

/**
 * FXML Controller class
 *
 * @author arkaPal
 */
public class RegisterController implements Initializable {
    static int entries=0;

    @FXML
    private JFXTextField regUserName;
    
    
    @FXML
    private JFXTextField regInstiID;
    @FXML
    private JFXTextField regEmail;
    @FXML
    private JFXButton registerButton;
    @FXML
    private JFXPasswordField pass1;
    @FXML
    private JFXPasswordField pass2;

    @FXML
    private Label message;
    @FXML
    private Label message2;
    @FXML
    private Label message3;

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        regUserName.setStyle("-fx-text-inner-color: white;");
        regInstiID.setStyle("-fx-text-inner-color: white;");
        regEmail.setStyle("-fx-text-inner-color: white;");
        pass1.setStyle("-fx-text-inner-color: white;");
        pass2.setStyle("-fx-text-inner-color: white;");
        
        pass2.focusedProperty().addListener(new ChangeListener<Boolean>()
        {
            public void changed(ObservableValue<? extends Boolean> arg0, Boolean oldPropertyValue, Boolean newPropertyValue)
            {
                if (newPropertyValue) {
                    //System.out.println("Textfield on focus");
                     //message.setText("");
                }
                else{
                       
                        if (!pass1.getText().equals(""))
                        if(!pass1.getText().equals(pass2.getText())){
                             pass1.setText("");
                             pass2.setText("");
                             message.setText("Passwords dont't match.");
                         }
                         
                }
            }
        });
                pass1.focusedProperty().addListener(new ChangeListener<Boolean>()
        {
            public void changed(ObservableValue<? extends Boolean> arg0, Boolean oldPropertyValue, Boolean newPropertyValue)
            {
                if (newPropertyValue) {
                    //System.out.println("Textfield on focus");
                    //message.setText("");
                }
                else{
                   
                        if(!Main.validatePassword(pass1.getText())){
                             pass1.setText("");
                             pass2.setText("");
                             message.setText(Main.passValMsg);
                         }
                      if (!pass2.getText().equals("")){
                        if(!pass1.getText().equals(pass2.getText())){
                             pass1.setText("");
                             pass2.setText("");
                             message.setText("Passwords dont't match.");
                         }
                    }
                         
                }
            }
        });
        regEmail.focusedProperty().addListener(new ChangeListener<Boolean>()
        {
            public void changed(ObservableValue<? extends Boolean> arg0, Boolean oldPropertyValue, Boolean newPropertyValue)
            {
                if (newPropertyValue) {
                    //System.out.println("Textfield on focus");
                    message3.setText("");
                }
                else{
                        if(!Main.validateEmail(regEmail.getText())){
                             regEmail.setText("");
                             
                             message3.setText("Invalid E-mail ID");
                            
                             
                         }
                   
                         
                }
            }
        });
                
        
        
        regInstiID.focusedProperty().addListener(new ChangeListener<Boolean>()
        {
            public void changed(ObservableValue<? extends Boolean> arg0, Boolean oldPropertyValue, Boolean newPropertyValue)
            {
                if (newPropertyValue) {
                    //System.out.println("Textfield on focus");
                    message2.setText("");
                }
                else{
                     //System.out.println("Textfield out focus");
                    ObjectInputStream objIs = null;
                    try{
                        File f=new File("persons.txt");
                    f.createNewFile();
                    objIs = null;
                    FileInputStream fileIs = new FileInputStream("persons.txt");
                    objIs = new ObjectInputStream(fileIs);
                    ArrayList<securityPerson> persons= (ArrayList<securityPerson>) objIs.readObject();
                    objIs.close();
                    
                    for (Iterator<securityPerson> it = persons.iterator(); it.hasNext();) {
                    securityPerson tmp,p;
                        p = it.next();
                        if (p.getUserId().equals(regInstiID.getText())){
                            message2.setText("User ID exists already.Please enter a new one");
                            regInstiID.setText("");
                        }
                    }
           
                    }
                    catch(EOFException ex){
                        if (objIs!=null)
                            try {
                                objIs.close();
                        } catch (IOException ex1) {
                            Logger.getLogger(RegisterController.class.getName()).log(Level.SEVERE, null, ex1);
                        }}
                    catch (IOException | ClassNotFoundException ex) {
                    }
                     
                     
            }
            }
            
        });
  
        // TODO
    }    

    @FXML
    private void register(ActionEvent event) throws IOException {
         String name=regUserName.getText();
         String mail=regEmail.getText();
         String pass=pass1.getText();
         String id=regInstiID.getText();
         Main.loggedInUser=id;
         securityPerson p=new securityPerson(name,id,pass,mail);
         File f=new File("persons.txt");
         f.createNewFile();
         ObjectInputStream objIs = null;
         if ((!id.equals(""))&&(!pass.equals(""))&&(!name.equals(""))&&(!mail.equals(""))&&(!pass2.getText().equals(""))){
        
        if (entries==0){
            try {
                    FileInputStream fileIs = new FileInputStream("persons.txt");
                    ArrayList<securityPerson> tmp1= new ArrayList();
                objIs = new ObjectInputStream(fileIs);
                  
                   tmp1= (ArrayList<securityPerson>) objIs.readObject();
             
                    objIs.close();
                
                    FileOutputStream out = new FileOutputStream("persons.txt",false);
                    ObjectOutputStream oout = new ObjectOutputStream(out);
                    ArrayList<securityPerson> persons=tmp1;
                    persons.add(p);
                    
                    oout.writeObject(persons);
                    Main.loggedIn.put(p.getUserId(),1);
                    Main.loggedInUser=id;
                    oout.close();
                    entries+=1;
                } 
             catch(EOFException ex){
                    // ArrayList<securityPerson> tmp1= new ArrayList();
                    if (objIs!=null)
                     objIs.close();
                
                    FileOutputStream out = new FileOutputStream("persons.txt",false);
                    ObjectOutputStream oout = new ObjectOutputStream(out);
                    ArrayList<securityPerson> persons=new ArrayList();
                    persons.add(p);
                    oout.writeObject(persons);
                    Main.loggedIn.put(p.getUserId(),0);
                    Main.loggedInUser=id;
                    oout.close();
                    entries+=1;
                              
                              }
            catch (Exception ex) {
                    ex.printStackTrace();
                }
          
            }
        else{
            try{
                    FileInputStream fileIs = new FileInputStream("persons.txt");
                    objIs = new ObjectInputStream(fileIs);
                    ArrayList<securityPerson> persons= (ArrayList<securityPerson>) objIs.readObject();
                    persons.add(p);
                    objIs.close();
                    
                    FileOutputStream out = new FileOutputStream("persons.txt",false);
                    ObjectOutputStream oout = new ObjectOutputStream(out);
                    oout.writeObject(persons);
                    Main.loggedIn.put(p.getUserId(),1);
                    oout.close();
                    entries+=1;
                for (Iterator<securityPerson> it = persons.iterator(); it.hasNext();) {
                    securityPerson tmp;
                        p = it.next();
                        
                }
           
            }
             catch(EOFException ex){
                    // ArrayList<securityPerson> tmp1= new ArrayList();
                    if (objIs!=null)
                     objIs.close();}
            catch (IOException | ClassNotFoundException ex) {
            }
        }
        
        Stage stage = (Stage) registerButton.getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("dashboard.fxml"));
        Scene scene=new Scene(root);
        stage.setScene(scene);
        stage.show();
        }     //end of null entry if
         else{
             message.setText("All fields are compulsory to be filled up");
             regUserName.setText("");
             regEmail.setText("");
             regInstiID.setText("");
             pass1.setText("");
             pass2.setText("");
         }
         
    }

    @FXML
    private void checkpass(ActionEvent event) {
        if (pass1.getText()!=pass2.getText()){
           
            
        }
        else{
            
        }
    }
    
}
