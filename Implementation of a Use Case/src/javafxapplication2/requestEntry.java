/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javafxapplication2;

import java.io.Serializable;

/**
 *
 * @author mcqueen7z
 */
public class requestEntry implements Serializable{
    
    String date;
    boolean requested=false;
    boolean leave;    //true immplies leave,else overtime
    requestEntry(String date,boolean leave){
        this.requested=true;
        this.date=date;
        this.leave=leave;
    }
    
}
