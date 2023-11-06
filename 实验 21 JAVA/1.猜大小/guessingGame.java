/*编写一个 Java 应用程序，在主类的 main 方法中实现下列功能。
• 程序随机分配给用户一个 1 至 100 之间的整数
• 用户通过键盘输人自己的猜测
• 程序返回提示信息，提示信息分别是：“猜大了”、“猜小了”和“猜对了”
• 用户可根据提示信息再次输入猜测，直到提示信息是“猜对了”
• 用户猜对以后，显示猜测次数，并提供“重新开始”和“退出”功能*/
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
