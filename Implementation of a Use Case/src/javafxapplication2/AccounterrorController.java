
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
public class AccounterrorController implements Initializable {

    private JFXButton retrybutton;
    /**
     * Initializes the controller class.
     * 
     */
    
     @FXML
    private void retry(ActionEvent event) throws IOException {
        Stage stage = (Stage) retrybutton.getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("load.fxml"));
        Scene scene=new Scene(root);
        stage.setScene(scene);
        stage.show();
    }
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
    }    
    
}
