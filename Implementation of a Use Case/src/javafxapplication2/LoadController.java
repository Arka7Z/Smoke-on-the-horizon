
package javafxapplication2;

import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXPasswordField;
import com.jfoenix.controls.JFXTextField;
import java.io.EOFException;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.URL;
import java.util.ArrayList;
import java.util.Iterator;
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
public class LoadController implements Initializable {

    @FXML
    private JFXButton inbutton;
    @FXML
    private JFXButton upbutton;
    @FXML
    private JFXTextField name;
    @FXML
    private JFXPasswordField pass;
    @FXML
    private Label message;
    @FXML
    private Label nameLabel;
    @FXML
    private Label nameLabel2;
 
    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
       name.setStyle("-fx-text-inner-color: white;");
       pass.setStyle("-fx-text-inner-color: white;");
       name.focusedProperty().addListener(new ChangeListener<Boolean>()
        {
            public void changed(ObservableValue<? extends Boolean> arg0, Boolean oldPropertyValue, Boolean newPropertyValue)
            {
                if (newPropertyValue) {
                    //System.out.println("Textfield on focus");
                    nameLabel.setText("Username");
                    message.setText("");
                }
                else{
                    nameLabel.setText("");
            
                }
            }
        });
       pass.focusedProperty().addListener(new ChangeListener<Boolean>()
        {
            public void changed(ObservableValue<? extends Boolean> arg0, Boolean oldPropertyValue, Boolean newPropertyValue)
            {
                if (newPropertyValue) {
                    //System.out.println("Textfield on focus");
                    message.setText("");
                    nameLabel2.setText("Password");
                }
                else{
                    nameLabel2.setText("");
            
                }
            }
        });
    }    
    private boolean verifyLogIn(String id,String pass) throws IOException{       
        ObjectInputStream objIs = null;
        File f=new File("persons.txt");
        if (!f.exists())
            return false;
        try{
                FileInputStream fileIs = new FileInputStream("persons.txt");
                objIs = new ObjectInputStream(fileIs);
                ArrayList<securityPerson> persons= (ArrayList<securityPerson>) objIs.readObject();
                securityPerson p;
                objIs.close();
           
                for (Iterator<securityPerson> it = persons.iterator(); it.hasNext();) {
                        securityPerson tmp;
                        p = it.next();
                        if (p.getUserId().equals(id) && p.getPassword().equals(pass)){
                            Main.loggedInUser=p.getUserId();
                            return true;
                        }
                    }
                return false;
           
            }
             catch(EOFException ex){
                if (objIs!=null)
                     objIs.close();
                return false;
            }
            catch (IOException | ClassNotFoundException ex) {
                return false;
            }
        
        
    }
    
    @FXML
    private void newsignin(ActionEvent event) throws IOException {
        String n=name.getText();
        String p=pass.getText();
    
        if (verifyLogIn(n, p)){
            Main.loggedIn.put(n,1);
            Main.loggedInUser=n;
            Stage stage = (Stage) inbutton.getScene().getWindow();
            Parent root = FXMLLoader.load(getClass().getResource("dashboard.fxml"));
            Scene scene=new Scene(root);
            stage.setScene(scene);
            stage.show();
        }
        else{
         message.setText("Invalid Username or Password");
         name.setText("");
         pass.setText("");
    
        }    
    }

    @FXML
    private void newsignup(ActionEvent event) throws IOException {
              Stage stage = (Stage) upbutton.getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("register.fxml"));
        Scene scene=new Scene(root);
        stage.setScene(scene);
        stage.show();
    }
    
}
