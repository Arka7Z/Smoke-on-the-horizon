package javafxapplication2;

import javafx.beans.property.SimpleStringProperty;

/**
 *
 * @author arkaPal
 */
public class tabledRequest {
    
    private SimpleStringProperty nature;
    private SimpleStringProperty date;
    private SimpleStringProperty status;
    tabledRequest(String nature,String date){
        this.nature=new SimpleStringProperty(nature);
        this.date  =new SimpleStringProperty(date);
        this.status=new SimpleStringProperty("Processing");
    }

    /**
     * @return the nature
     */
    public String getNature() {
        return nature.get();
    }

    /**
     * @return the date
     */
    public String getDate() {
        return date.get();
    }

    /**
     * @return the status
     */
    public String getStatus() {
        return status.get();
    }
    
    
    
    
}
