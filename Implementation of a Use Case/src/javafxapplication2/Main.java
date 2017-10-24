/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javafxapplication2;

import java.util.HashMap;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javax.mail.internet.AddressException;
import javax.mail.internet.InternetAddress;

/**
 *
 * @author arkapal
 */
public class Main extends Application {
 
    public static HashMap loggedIn=new HashMap();
    public static HashMap leaves=new HashMap();

    /**
     *number of leaves available
     */
    public static int CONST_LEAVES=5;
    public static String loggedInUser="";
    public static String passValMsg="";
    
    public static boolean validatePassword(String password){
        boolean valid=true;
        if (password.length()<6){
            passValMsg="Password must contain atleast 6 characters";
            valid=false;
        }
        String upperCaseChars = "(.*[A-Z].*)";
        if (!password.matches(upperCaseChars )){
            valid = false;
            passValMsg="Password must contain atleast one uppercase letter";
        }
        String lowerCaseChars = "(.*[a-z].*)";
        if (!password.matches(lowerCaseChars )){
            valid = false;
             passValMsg="Password must contain atleast one lowercase letter";
        }
        String numbers = "(.*[0-9].*)";
        if (!password.matches(numbers )) {
            valid = false;
             passValMsg="Password must contain atleast one number";
        }
        String specialChars = "(.*[,~,!,@,#,$,%,^,&,*,(,),-,_,=,+,[,{,],},|,;,:,<,>,/,?].*$)";
        if (!password.matches(specialChars )){
             passValMsg="Password must contain atleast one special character";
            valid = false;
        }      
        
        
        return valid;
    }
    
    public static boolean validateEmail(String email){
        boolean valid=true;
         try {
            InternetAddress internetAddress = new InternetAddress(email);
            internetAddress.validate();
            valid = true;
        } catch (AddressException e) {
            valid=false;
        }
         return valid;
    }
    
    @Override
    public void start(Stage stage) throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("FXMLDocument.fxml"));
        
        Scene scene = new Scene(root);
        
        stage.setScene(scene);
        stage.show();
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
    
}
