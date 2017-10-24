
package javafxapplication2;

import com.jfoenix.controls.JFXButton;
import java.io.EOFException;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.net.URL;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextArea;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

/**
 * FXML Controller class
 *
 * @author arkaPal
 */
public class ViewrequestsController implements Initializable {

    @FXML
    private TableColumn<tabledRequest,String> natureCol;
    @FXML
    private TableColumn<tabledRequest,String> dateCol;
    @FXML
    private TableColumn<tabledRequest,String> statusCol;
    @FXML
    private TableView<tabledRequest> table;
    @FXML
    private Label label;
    @FXML
    private JFXButton dashBUtton;

    /**
     * Initializes the controller class.
     * @throws java.io.IOException
     */
    @Override
    public void initialize(URL url, ResourceBundle rb)  {
        dateCol.setCellValueFactory(new PropertyValueFactory<tabledRequest,String>("date") );
        natureCol.setCellValueFactory(new PropertyValueFactory<tabledRequest,String>("nature") );
        statusCol.setCellValueFactory(new PropertyValueFactory<tabledRequest,String>("status") );
        ObservableList<tabledRequest> data;
        List list=new ArrayList();
        
        
        
        
           String target = null;
        for (Iterator it = Main.loggedIn.entrySet().iterator(); it.hasNext();) {
            //System.out.println("inside for loop"+"size: "+Main.loggedIn.size());
            Map.Entry<String, Integer > entry = (Map.Entry<String, Integer >) it.next();
            String name=entry.getKey();
            int flag=entry.getValue();
            if (flag==1){
               target=name;
               //System.out.println(target);
            }
        }
        Main.loggedInUser=target;
        label.setText("UserID: "+target);
                                    
         ArrayList<securityPerson> tmp = null;
        ObjectInputStream objIs = null;
        File f=new File("persons.txt");
        try {
            f.createNewFile();
        } catch (IOException ex) {
            Logger.getLogger(ViewrequestsController.class.getName()).log(Level.SEVERE, null, ex);
        }
            try{
                FileInputStream fileIs = new FileInputStream("persons.txt");
                objIs = new ObjectInputStream(fileIs);
                ArrayList<securityPerson> persons= (ArrayList<securityPerson>) objIs.readObject();
               
                securityPerson p;
                objIs.close();
           
                for (Iterator<securityPerson> it = persons.iterator(); it.hasNext();) {
                        p = it.next();
                        if (p.getUserId().equals(target)){
                            for (Iterator<requestEntry> i=p.requests.iterator();i.hasNext();){
                                
                                requestEntry rE=i.next();
                                if(rE.requested==true)
                                
                                list.add(new tabledRequest(rE.leave?"Leave":"Overtime",rE.date));
                                
                             }
                           
                        }
       
                    }
                data=FXCollections.observableList(list);
                table.setItems(data);
                
                
           
            }
             catch(EOFException ex){
                if (objIs!=null)
                     try {
                         objIs.close();
                } catch (IOException ex1) {
                    Logger.getLogger(ViewrequestsController.class.getName()).log(Level.SEVERE, null, ex1);
                }
            }
            catch (IOException | ClassNotFoundException ex) {
                if (objIs!=null)
                     try {
                         objIs.close();
                } catch (IOException ex1) {
                    Logger.getLogger(ViewrequestsController.class.getName()).log(Level.SEVERE, null, ex1);
                }
               
            }
        // TODO
    }    

    @FXML
    private void gotoDash(ActionEvent event) throws IOException {
         Stage stage = (Stage) dashBUtton.getScene().getWindow();
        Parent root = FXMLLoader.load(getClass().getResource("dashboard.fxml"));
        Scene scene=new Scene(root);
        stage.setScene(scene);
        stage.show();
    }
    
}
