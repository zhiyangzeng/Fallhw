//CSCE-314-501
//Zhiyang Zeng
//UIN 720005338
//Help received: stackoverflow, textbook,tutorialpoints.com, oracle.com, piazza


//this program uses synchronized block to automatically synchronize, so there is no explanation needed. 
//Inside a folder called POB2 there is a similar program using lock and unlock to manually synchronize. 
//It contains comments for my reasoning of the locks if that's what you are looking for. Both works


import java.util.concurrent.*;
import java.util.*;


class PostBox implements Runnable {
  static final int MAX_SIZE = 10;

  class Message {
    String sender;
    String recipient;
    String msg;
    Message(String sender, String recipient, String msg) {
      this.sender = sender;
      this.recipient = recipient;
      this.msg = msg;
      }
  }

  private final LinkedBlockingDeque<Message> messages;
  private LinkedBlockingDeque<Message> myMessages;
  private String myId;
  private boolean stop = false;

  //private Thread thread;
  private volatile boolean exit = false;

  public PostBox(String myId) {
    messages = new LinkedBlockingDeque<Message>();
    this.myId = myId;
    this.myMessages = new LinkedBlockingDeque<Message>();
    new Thread(this).start();
}

  public PostBox(String myId, PostBox p) {
    this.myId = myId;
    this.messages = p.messages;
    this.myMessages = new LinkedBlockingDeque<Message>();
    new Thread(this).start();
}

  public String getId() { return myId; }

  public void stop() {
    // make it so that this Runnable will stop
    //if (thread!=NULL) thread.interrupt();
    exit=true;
  }

  public synchronized void send(String recipient, String msg) {
    // add a message to the shared message queue
      messages.add(new Message(myId, recipient, msg));
  }

  public synchronized List<String> retrieve(){
    // return the contents of myMessages

        List<String> mes= new ArrayList<String>();

        for (Message e : myMessages){
          String temp=("From "+e.sender+" to "+e.recipient+" :"+e.msg);
          mes.add(temp);
        }
        // and empty myMessages
         while (!myMessages.isEmpty()) {
          myMessages.removeFirst();
        }
       
        return mes;
  }

 // public synchronized void cleraPrivate

  public synchronized void getMessage() {  //get all message addgressed to here from sharedmsg

      
      //   1. approximately once every second move all messages
      //      addressed to this post box from the shared message
      //      queue to the private myMessages queue

      if (messages.size()==0) return;
      Iterator<Message> it=messages.iterator();
      //for (Iterator<Message> it=messages.listIterator(); it.hasNext(); ){
      while (it.hasNext()){
          //SEPARATE RETRIEVE AND APPEND TO MYMSG IN ANOTHER METHOD?
          Message e= it.next();
          if (e!=null) {
          if (e.recipient==this.myId){
            myMessages.addLast(e); //new msg goes to back
            it.remove();//remove from public msg
        }
        }
      }
  }
  public synchronized void clearMessage() { 

      //   2. also approximately once every second, if the message
    //      queue has more than MAX_SIZE messages, delete oldest messages
    //      so that size is at most MAX_SIZE
      while (messages.size()>MAX_SIZE){  
        messages.removeFirst();
      }
}

public void run() {

  try{
    //thread=Thread.thread();
    while (true){
      getMessage();
      clearMessage();
      //exit if stop method is called
      if (exit == true){
        return;
      }
      //pause 1000ms
      Thread.sleep(1000);
   
    }
  }
  catch (InterruptedException e) {
      System.out.println("Runtime Exception: " +e.getMessage());
  }
} 

}
