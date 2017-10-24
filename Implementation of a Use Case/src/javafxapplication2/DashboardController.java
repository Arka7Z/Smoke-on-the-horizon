
package javafxapplication2;

import com.jfoenix.controls.JFXButton;
import java.io.IOException;
import java.net.URL;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.ResourceBundle;
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
public class DashboardController implements Initializable {

    @FXML
    private JFXButton reqbutton;
    @FXML
    private JFXButton outbutton;
    @FXML
    private JFXButton ttbutton;
    @FXML
    private JFXButton eaccbutton;
    @FXML
    private JFXButton viewReqButton;
    @FXML
    private Label leavemsg;

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        
        int left;
        // TODO
        left = (Main.CONST_LEAVES)-((Main.leaves.containsKey(Main.loggedInUser))?(int)Main.leaves.get(Main.loggedInUser):0);
        if (left>0){
            leavemsg.setText("You have "+left+" leaves left to be availed");
        }
        else{
            leavemsg.setText("Availing further leaves may invoke penalty!!");
        }
        
    }    

    @FXML
    private void req(ActionEvent event) throws IOException {
         Stage stage = (Stage) reqbutton.getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("request.fxml"));
        Scene scene=new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    @FXML
    private void out(ActionEvent event) throws IOException {
        for (Iterator it = Main.loggedIn.entrySet().iterator(); it.hasNext();) {
            Map.Entry<String, Integer > entry = (Map.Entry<String, Integer >) it.next();
            String name=entry.getKey();
            int flag=entry.getValue();
            if (flag==1){
                Main.loggedIn.put(name,0);
                
            }
        }
        Main.loggedInUser="";
         Stage stage = (Stage) outbutton.getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("load.fxml"));
        Scene scene=new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    @FXML
    private void viewtt(ActionEvent event) throws IOException {
         Stage stage = (Stage) ttbutton.getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("timetable.fxml"));
        Scene scene=new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    @FXML
    private void eacc(ActionEvent event) throws IOException {
         Stage stage = (Stage) eaccbutton.getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("editaccount.fxml"));
        Scene scene=new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    @FXML
    private void viewRequests(ActionEvent event) throws IOException {
          Stage stage = (Stage) viewReqButton.getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("viewrequests.fxml"));
        Scene scene=new Scene(root);
        stage.setScene(scene);
        stage.show();
        
    }
    
}
