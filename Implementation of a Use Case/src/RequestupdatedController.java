
package javafxapplication2;

import com.jfoenix.controls.JFXButton;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

/**
 * FXML Controller class
 *
 * @author arkaPal
 */
public class RequestupdatedController implements Initializable {

    @FXML
    private JFXButton logoutbutton;
    @FXML
    private JFXButton dashbutton;

    /**
     * Initializes the controller class.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
    }    

    @FXML
    private void logout(ActionEvent event) throws IOException {
           Stage stage = (Stage) logoutbutton.getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("FXMLDocument.fxml"));
        Scene scene=new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    @FXML
    private void gotodash(ActionEvent event) throws IOException {
            Stage stage = (Stage) dashbutton.getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("dashboard.fxml"));
        Scene scene=new Scene(root);
        stage.setScene(scene);
        stage.show();
        
    }
    
}
