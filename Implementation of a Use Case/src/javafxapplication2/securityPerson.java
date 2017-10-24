
package javafxapplication2;

import java.io.Serializable;
import java.util.ArrayList;

/**
 * @author arkapal
 */
public class securityPerson implements Serializable {
   
    private int hash;
    private String name;
    private String userId;
    private String password;
    private String mail;
    ArrayList<requestEntry> requests;
    
    public void addRequests(String date,boolean leave){
        requestEntry rE=new requestEntry(date,leave);
        requests.add(rE);
        
    }

    public securityPerson(String name,String userId,String password,String mail) {
        requests=new ArrayList();
        this.hash = 1;
        this.name=name;
        this.userId=userId;
        this.password=password;
        this.mail=mail;
    }
    public securityPerson(securityPerson p){
        this.hash = 1;
        this.name=p.name;
        this.userId=p.userId;
        this.password=p.password;
        this.mail=p.mail;
        
    }

    /**
     * @return the hash
     */
    public int getHash() {
        return hash;
    }

    /**
     * @return the name
     */
    public String getName() {
        return name;
    }

    /**
     * @param name the name to set
     */
    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "securityPerson{" + "hash=" + hash + ", name=" + name + ", userId=" + userId + ", password=" + password + ", mail=" + mail + '}';
    }

    /**
     * @return the userId
     */
    public String getUserId() {
        return userId;
    }

    /**
     * @param userId the userId to set
     */
    public void setUserId(String userId) {
        this.userId = userId;
    }

    /**
     * @return the password
     */
    public String getPassword() {
        return password;
    }

    /**
     * @param password the password to set
     */
    public void setPassword(String password) {
        this.password = password;
    }

    /**
     * @return the mail
     */
    public String getMail() {
        return mail;
    }

    /**
     * @param mail the mail to set
     */
    public void setMail(String mail) {
        this.mail = mail;
    }
    
    
}
