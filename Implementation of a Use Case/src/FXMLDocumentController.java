
package javafxapplication2;

import com.jfoenix.controls.JFXButton;
import com.jfoenix.controls.JFXPasswordField;
import com.jfoenix.controls.JFXTextField;
import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;

/**
 *
 * @author arkaPal
 */
public class FXMLDocumentController implements Initializable {
    
    private Label label;
    @FXML
    private Pane pane;
    @FXML
    private JFXButton signinbutton;
    
    private void handleButtonAction(ActionEvent event) {
        System.out.println("You clicked me!");
        label.setText("Hello World!");
    }
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
    }    

    @FXML
    private void signin(ActionEvent event) throws IOException {
        Stage stage = (Stage) signinbutton.getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("load.fxml"));
        Scene scene=new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

  

    
}
