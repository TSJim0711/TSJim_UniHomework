import java.util.Random;
import java.util.Scanner; 
 
public class guessingGame {
    public static void main(String[] args) {
    	Random rand = new Random();
    	Scanner playerInput = new Scanner(System.in);
        int playerGuess=-1, attTimes = 1, toGuess;
        do {
		    	toGuess = rand.nextInt(100);//设定目标数目
		    	for (;playerGuess!=toGuess;attTimes++)
		    	{
		            System.out.println("Input a number: ");
		            playerGuess = playerInput.nextInt();//用户输入
		            if(playerGuess<toGuess) 
		            	System.out.println("To small.");//太小
		            	else
		            	if(playerGuess>toGuess)
		            		System.out.println("To Big.");//太大
		    	}//如果等于,将满足for的condition
		    	System.out.println("Bingo! And you made " + attTimes + " attemps.");//猜对后结算
		    	do {
		    		System.out.println("[1] Reattemp the game.\n[2] Exit. "); 
		    		playerGuess=playerInput.nextInt()-10;//playerGuess-10，否则重新开始时，playerGuess将可能刚好=toGuess，如此一来，则能免去初始化playerGuess。
		    	}while(playerGuess!=-9 && playerGuess!=-8);
        } while (playerGuess==-9);//因只允许1/2通过do while，如果不是1（-9），就是2。
    }
}
