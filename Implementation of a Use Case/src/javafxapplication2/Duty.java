
package javafxapplication2;

import javafx.beans.property.SimpleStringProperty;

/**
 *
 * @author arkaPal
 */
public class Duty {


    private SimpleStringProperty date;
    private SimpleStringProperty place;
    private SimpleStringProperty start;
    private SimpleStringProperty end;
   
    Duty(String date,String place,String sTime,String eTime){
        this.date =new SimpleStringProperty(date);
        this.place=new SimpleStringProperty(place);
        this.start=new SimpleStringProperty(sTime);
        this.end=new SimpleStringProperty(eTime);
                
    }

        /**
         * @return the date
         */
        public String getDate() {
            return date.get();
        }

        /**
         * @return the place
         */
        public String getPlace() {
            return place.get();
        }

        /**
         * @return the start
         */
        public String getStart() {
            return start.get();
        }

        /**
         * @return the end
         */
        public String getEnd() {
            return end.get();
        }
 
    
}
