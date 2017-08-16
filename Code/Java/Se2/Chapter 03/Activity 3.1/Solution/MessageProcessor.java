package messenger;

//Import Package
import java.lang.reflect.Field;

class MessageProcessor<X> 
{
    //Generic Variable

    private X message;

    //Generic Constructor
    public MessageProcessor(X a1) 
    {
        message = a1;
    }

    //Processing Logic
    public void printResult() 
    {
        try 
        {
            Field receiverField = message.getClass().getDeclaredField("receiver");

            Object receiverValue = receiverField.get(message);

            Field messagefield = message.getClass().getDeclaredField("message");

            Object messageValue = messagefield.get(message);

            System.out.println("=======================================");
            System.out.println("Message: " + messageValue + " sent to " + receiverValue + " was submitted for processing at " + new java.util.Date().toString());
        } 
        catch (Exception ex) 
        {
            ex.printStackTrace();
        }
    }
}
