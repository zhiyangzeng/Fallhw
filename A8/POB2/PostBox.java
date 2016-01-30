//CSCE-314-501
//Zhiyang Zeng
//UIN 720005338
//Help received: stackoverflow, textbook
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.TimeUnit;
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
  private Lock sharedMessageLock = new ReentrantLock(); //lock whenever messages is used
  private Lock privateMessageLock= new ReentrantLock();  //lock whenever myMessage is used
  private Condition doneSendCondition = sharedMessageLock.newCondition(); 
  private Condition donerecCondition = privateMessageLock.newCondition(); 


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

  public void send(String recipient, String msg) {
    // add a message to the shared message queue
    sharedMessageLock.lock(); //lock because messages is being edited
    try {
      messages.add(new Message(myId, recipient, msg));
      doneSendCondition.signalAll(); //message is present
    }  
    finally {
      sharedMessageLock.unlock();
    }
  }

  public List<String> retrieve(){
    // return the contents of myMessages
    
    privateMessageLock.lock();  //lock because myMessage is being edited
    try {
        List<String> mes= new ArrayList<String>();
 
        for (Message e : myMessages){
          String temp=("From "+e.sender+" to "+e.recipient+" :"+e.msg);
          mes.add(temp);
        }
        // and empty myMessages
         while (!myMessages.isEmpty()) {
          myMessages.removeFirst();
        }
       
        donerecCondition.signalAll();
        return mes;
    } 
    
    finally {
       
        privateMessageLock.unlock();
    }
  }

  public void getMessage() {  //get all message addgressed to here from sharedmsg, both messages edited, 2 locks
    sharedMessageLock.lock();
    privateMessageLock.lock();
    try{
      
      //   1. approximately once every second move all messages
      //      addressed to this post box from the shared message
      //      queue to the private myMessages queue

      //check first if it's empty, while iterator hasnext

      for (Iterator<Message> it=messages.iterator(); it.hasNext(); ){
          Message e= it.next();
          if (e.recipient==myId){
            myMessages.addLast(e); //new msg goes to back
            it.remove();//remove from public msg
        }
      }
        doneSendCondition.signalAll(); 
        donerecCondition.signalAll(); 
  }
  
  finally {
        privateMessageLock.unlock();
        sharedMessageLock.unlock();
        
    } 
  }
//combine
  public void clearMessage() {  //get all message addgressed to here from sharedmsg
    sharedMessageLock.lock();

    try{
      
      //   2. also approximately once every second, if the message
    //      queue has more than MAX_SIZE messages, delete oldest messages
    //      so that size is at most MAX_SIZE
      while (messages.size()>MAX_SIZE){  //privateMessageLock
        //System.out.println("message size: "+messages.size());
        messages.removeFirst();
      }
        doneSendCondition.signalAll(); 
  }

  finally {
   sharedMessageLock.unlock();
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

  /*
  private Thread currentThread;

  @Override
  public void run() {
      currentThread = Thread.currentThread();
      // Do here something interruptible
  }

  public void interrupt() {
      if (currentThread != null)
          currentThread.interrupt();
  }
  */

/*
  public void run() {

  //sharedMessageLock.lock();
  //privateMessageLock.lock();
  try{
    //thread=Thread.thread();
    while (true){
    //   1. approximately once every second move all messages
    //      addressed to this post box from the shared message
    //      queue to the private myMessages queue
      for (Message e: messages){
        if (e.recipient==myId){
          myMessages.addFirst(e);  //sharedMessageLock
        }
      }
    //   2. also approximately once every second, if the message
    //      queue has more than MAX_SIZE messages, delete oldest messages
    //      so that size is at most MAX_SIZE
      while (messages.size()>MAX_SIZE){  //privateMessageLock
        messages.removeLast();
      }
      //exit if stop method is called
      if (exit == true){
        return;
      }
      //pause 1000ms
      Thread.sleep(1000);
    doneSendCondition.signalAll(); 
    donerecCondition.signalAll(); 
    }

  }
  catch (InterruptedException e) {
      System.out.println("Runtime Exception: " +e.getMessage());
  }
  
  finally {
        sharedMessageLock.unlock();
        privateMessageLock.unlock();
  } 
} */
}
