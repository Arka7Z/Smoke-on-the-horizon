
package javafxapplication2;

import com.jfoenix.controls.JFXButton;
import java.io.EOFException;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.URL;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Map;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.DatePicker;
import javafx.scene.control.MenuButton;
import javafx.stage.Stage;
import java.util.Date;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * FXML Controller class
 *
 * @author mcqueen
 */
public class RequestController implements Initializable {
    boolean leavesel=false;
   

    @FXML
    private JFXButton updateRequestbutton;
    @FXML
    private MenuButton requesttype;
    @FXML
    private DatePicker date;
    private Button mainmenu;
    @FXML
    private JFXButton button1;

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
      
    }
    public void registerrequest() throws IOException{
        String target = null;
        for (Iterator it = Main.loggedIn.entrySet().iterator(); it.hasNext();) {
           
            Map.Entry<String, Integer > entry = (Map.Entry<String, Integer >) it.next();
            String name=entry.getKey();
            int flag=entry.getValue();
            if (flag==1){
               target=name;
              
            }
        }
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
                String dt;
                
            dt = (date.getValue().getDayOfMonth() +"/")+ (date.getValue().getMonthValue()+"/")+(date.getValue().getYear()+".");
  
           
            for (Iterator<securityPerson> it = persons.iterator(); it.hasNext();) {
                        p = it.next();
                        if (p.getUserId().equals(target)){
                            p.addRequests(dt, leavesel);
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
        

        
        
    }

    @FXML
    private void updaterequest(ActionEvent event) throws IOException {
        
        registerrequest();
        if (leavesel==true){
           
            int count;
            count = (Main.leaves.containsKey(Main.loggedInUser))?(int)Main.leaves.get(Main.loggedInUser):0;
            Main.leaves.put(Main.loggedInUser,count+1);
            
        }
           Stage stage = (Stage) updateRequestbutton.getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("requestupdated.fxml"));
        Scene scene=new Scene(root);
        stage.setScene(scene);
        stage.show();
        
    }

    @FXML
    private void goback(ActionEvent event) throws IOException {
        Stage stage = (Stage) button1.getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("load.fxml"));
        Scene scene=new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    @FXML
    private void leaveselected(ActionEvent event) {
        requesttype.setText("Leave");
        leavesel=true;
       
    }

    @FXML
    private void overtimeselected(ActionEvent event) {
        requesttype.setText("Overtime");
        leavesel=false;
    }

  
   



 
    
}
