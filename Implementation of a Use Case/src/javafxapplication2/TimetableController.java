
package javafxapplication2;

import com.jfoenix.controls.JFXButton;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;


public class TimetableController implements Initializable {

    @FXML
    private JFXButton dash2;
    @FXML
    private TableView<Duty> table;
    @FXML
    private TableColumn<Duty,String> dateCol;
    @FXML
    private TableColumn<Duty,String> placeCol;
    @FXML
    private TableColumn<Duty,String>  sCol;
    @FXML
    private TableColumn<Duty,String> eCol;

    /**
     * Initializes the controller class.
     */
      private ObservableList getInitialTableData() {
          
        List list = new ArrayList();     
        list.add(new Duty("09/4/2017","Central","10:45","11:45"));
        list.add(new Duty("11/4/2017","Gate 5","13:45","11:50"));
        list.add(new Duty("13/4/2017","Acad Building","14:00","15:10"));
        list.add(new Duty("14/4/2017","GolC","10:45","11:45"));
        list.add(new Duty("22/4/2017","Nalanda","10:45","11:45"));
        list.add(new Duty("23/4/2017","TSG","11:45","12:45"));
        list.add(new Duty("26/4/2017","TGH","10:45","16:45"));
        ObservableList data = FXCollections.observableList(list);

        return data;

    }

    @Override
    public void initialize(URL url, ResourceBundle rb) {
       dateCol.setCellValueFactory(new PropertyValueFactory<Duty,String>("date") );
       placeCol.setCellValueFactory(new PropertyValueFactory<Duty,String>("place") );
       sCol.setCellValueFactory(new PropertyValueFactory<Duty,String>("start") );
       eCol.setCellValueFactory(new PropertyValueFactory<Duty,String>("end") );
       ObservableList<Duty> data=getInitialTableData();
       table.setItems(data);
       
       
       
    }    

    @FXML
    private void godash(ActionEvent event) throws IOException {
            Stage stage = (Stage) dash2.getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("dashboard.fxml"));
        Scene scene=new Scene(root);
        stage.setScene(scene);
        stage.show();
    }
    
}
