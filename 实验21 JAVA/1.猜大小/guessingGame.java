import java.util.Random;
import java.util.Scanner; 
 
public class guessingGame {
    public static void main(String[] args) {
    	Random rand = new Random();
    	Scanner playerInput = new Scanner(System.in);
        int playerGuess;
    	int toGuess = rand.nextInt(100);
    	do {
            System.out.println("Input a number: ");
            playerGuess = playerInput.nextInt();
            if(playerGuess&lt;toGuess) 
            	System.out.println("To small.");
            	else
            	if(playerGuess&gt;toGuess)
            		System.out.println("To Big.");
            	else
            		System.out.println("Bingo!");
    	}while(playerGuess!=toGuess);
    }
}
