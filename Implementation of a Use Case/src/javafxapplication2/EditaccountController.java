
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
import java.util.Map;
import java.util.ResourceBundle;
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
public class EditaccountController implements Initializable {

    @FXML
    private JFXTextField regUserName;
    @FXML
    private JFXTextField regEmail;
    @FXML
    private JFXPasswordField pass1;
    @FXML
    private JFXPasswordField pass2;
    @FXML
    private Label message;
    @FXML
    private JFXButton updateButton;
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
        regEmail.setStyle("-fx-text-inner-color: white;");
        pass1.setStyle("-fx-text-inner-color: white;");
        pass2.setStyle("-fx-text-inner-color: white;");
        
        message.setText("User ID:"+Main.loggedInUser+".Please update the following as required.");
         pass2.focusedProperty().addListener(new ChangeListener<Boolean>()
        {
            public void changed(ObservableValue<? extends Boolean> arg0, Boolean oldPropertyValue, Boolean newPropertyValue)
            {
                if (newPropertyValue) {
                    //System.out.println("Textfield on focus");
                    message2.setText("");
                }
                else{
                        if (!Main.validatePassword(pass1.getText())){
                             pass1.setText("");
                             pass2.setText("");
                             message2.setText(Main.passValMsg);
                            }
                        if (!pass1.getText().equals(""))
                         if(!pass1.getText().equals(pass2.getText())){
                             pass1.setText("");
                             pass2.setText("");
                             message2.setText("Passwords dont't match.");
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
                    message2.setText("");
                }
                else{
                        if (!Main.validatePassword(pass1.getText())){
                             pass1.setText("");
                             pass2.setText("");
                             message2.setText(Main.passValMsg);
                            }
                        if (!pass2.getText().equals(""))
                         if(!pass2.getText().equals(pass1.getText())){
                             pass1.setText("");
                             pass2.setText("");
                             message2.setText("Passwords dont't match.");
                            }
                       
                     
                }
            }
        });
         regEmail.focusedProperty().addListener(new ChangeListener<Boolean>()
        {
            public void changed(ObservableValue<? extends Boolean> arg0, Boolean oldPropertyValue, Boolean newPropertyValue)
            {
                if (newPropertyValue) {
                    //System.out.println("Textfield on focus");(
                    message2.setText("");
                }
                else{
                    
                         if(!Main.validateEmail(regEmail.getText())){
                             regEmail.setText("");
                             
                             message2.setText("Invalid E-mail ID");
                            }
                       
                     
                }
            }
        });
    }    


    @FXML
    private void checkpass(ActionEvent event) {
    }

    @FXML
    private void update(ActionEvent event) throws IOException {
        String target = Main.loggedInUser;
        
      if ((!pass1.equals(""))&&(!regEmail.equals(""))&&(!regUserName.equals(""))){ 
        ArrayList<securityPerson> tmp = null;
        ObjectInputStream objIs = null;
        File f=new File("persons.txt");
        f.createNewFile();
            try{
                FileInputStream fileIs = new FileInputStream("persons.txt");
                objIs = new ObjectInputStream(fileIs);
                ArrayList<securityPerson> persons= (ArrayList<securityPerson>) objIs.readObject();
                tmp= new ArrayList();
                securityPerson p;
                objIs.close();
                for (Iterator<securityPerson> it = persons.iterator(); it.hasNext();) {
                        p = it.next();
                        if (p.getUserId().equals(target)){
                            p.setName(regUserName.getText());
                            p.setPassword(pass1.getText());
                            p.setMail(regEmail.getText());
                            p.setUserId(target);
                            //securityPerson updatedP=new securityPerson(regUserName.getText(),target,pass1.getText(),regEmail.getText());
                            tmp.add(p);
                        }
                        else{
                            tmp.add(p);
                        }
                            
                            
                    }
                
           
            }
             catch(EOFException ex){
                if (objIs!=null)
                     objIs.close();
            }
            catch (IOException | ClassNotFoundException ex) {
                if (objIs!=null)
                     objIs.close();
               
            }
             ObjectOutputStream oout = null;
            try{
                FileOutputStream out = new FileOutputStream("persons.txt",false);
                oout = new ObjectOutputStream(out);
                ArrayList<securityPerson> persons=tmp;
                oout.writeObject(persons);
                oout.close();
            }
            catch(Exception ex){
            }
            finally{
                if (oout!=null)
                    oout.close();
            }
        
      
        Stage stage = (Stage) updateButton.getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("dashboard.fxml"));
        Scene scene=new Scene(root);
        stage.setScene(scene);
        stage.show();
       }     //end of null entry if
         else{
             message3.setText("All fields are compulsory to be filled up");
             regUserName.setText("");
             regEmail.setText("");
             
             pass1.setText("");
             pass2.setText("");
         }
    }
    
}
