Online Campus Security Management System :ARKAJYOTI PAL 15CS30003

#UI Idea:       Special focus has been given to make the UI easy-to-use and making it visually appealing 
               appealing at the same time.

Use Case wrt the security personnel side have been implemented which includes the following:
	~ Sign In
	~ Sign Up
	~ Edit Account
	~ View Timetable
	~ Make Request for Leave/Overtime
	~ View leaves Left
	~ View (status of) requests

Description of Use Cases along with features added to them:

1.Sign In: Allows user to sign in with his registered Institute ID and password.

2.Sign Up: Allows user to sign up by entering his credentials.
	      Features added: 	~ Password must contain at least one upper case letter,one lower case letter,one special character,one digit 
	      	       	      	  (Implemented using REGEX).
			        ~ User ID is unique and checked if the entered user ID has beeen used 
			          with a previous existing account or not.
			        ~ Fields can not be left blank (Checked).
			        ~ Password are to be entered twice and checked to be same or not.
			        ~ Validity of email adress also checked using JavaMail

3.Edit Account : Allows a logged in user to change password,mail etc.

4.View leaves left : View leaves left to be availed without invoking penaltyin the dashboard.User 	
		     also warned of penalty if leaves exceed allowed number.

5.Make request for Leave/Overtime : User can make request for leave or overtime from a calendar.

6.View Timetable : User can view timetable in a tabular format with the necessary detail ( hardcoded as manager functionalities are not considered).

7.View Requests :  Once user updates a requst, s/he can view all the requests along with their status .



----------------  ------------------  ------------------------- ---------------------------  -------------------------  --------------------

TESTING:


Test Cases:

S No. |   Input                                    |              Expected Output                  |       Output           |   Testing Remarks

1.      Need to sign up initially for log in.		Password field reset as password must conta	Password field reset   		Correct
	Sign Up input: Name:user123, id:user		-in at least one capital letter			and user asked to re
	password: pass123 Re_password:pass123								-enter password
	email:user@google.com

2.      Need to sign up initially for log in.		Password field reset as password must conta	Password field reset   		Correct
	Sign Up input: Name:user123, id:user		-in at least one special character  		and user asked to re
	password: Pass123 Re_password:Pass123								-enter password
	email:user@google.com
	
3.      Need to sign up initially for log in.		Email id not valid and hence reset to null	Email field reset   		Correct
	Sign Up input: Name:user123, id:user								and user asked to re
	password:Pass@123 Re_password:Pass@123								-enter email id.
	email:useremail


4.      Need to sign up initially for log in.		No field can be left blank and user asked to  	user asked to 			Correct
	Sign Up input: Name:, id:			enter the details				enter all the 
	password: Re_password:										details.
	email:user@google.com
	
5.      Need to sign up initially for log in.		Re entered password must match the first one	Password fields reset  		Correct
	Sign Up input: Name:user123, id:user		hence password fiels reset(both of them).	and user asked to re
	password: pass123 Re_password:Pass123								-enter passwords.
	email:user@google.com

6.      Need to sign up initially for log in.		All field valid hence sign up succesful		Dashboard displayed  		Correct
	Sign Up input: Name:user123, id:user		and dashboard is displayed with message that	with options for other
	password:Pass@123 Re_password:Pass@123		5 leaves(default) are left to be availed.	functionalities.
	email:user@google.com

7.	Log out option selected.			Main load screen to be loaded.			Log In Screen Displayed		Correct


8.     Logged In with user name user and password:     Dashboard Page appears showing 5 (default)      	Same as expected		Correct
       Hello@1997                                      leaves left as no leave request has been 
       						       entered.


9.     Logged In with the mentioned account and        Since no requests have been entered table is     Empty Table.			Correct
       View Requests option selected.		       to be empty.
       
10.     Following from the last state,returned to dash  Table should show date:31/03/2017 and nature     As expected			Correct
       board,request option selected and 31 March,     of request as leave and status as processing
       2017 selected from calendar,leave
       selected from drop down menu ,update button 
       cliced,return to dashboard->view requests.		      

11.     From last state returned to dashboard		Dashboard should display 4 leaves left to be 	As expected			Correct
							availed as 1 is requested.

12.     View Timetable button clicked			A hardcoded timetable is to be displayed with	Expected table displayed	Correct
							date,place,start time and end time. 

13.	Logged out and from sign up menu	        Since a previous account exists with  the id	Expected message displayed	Correct
	Institute Id:user (entered along with		hence ID field reset and user asked to enter		
	other details).     				new ID.	













