class ticketSelling extends station implements Runnable
{
    public void run() {
    	while(ticketSold<21) {
    		this.sellProcess();
        	try {
				Thread.sleep(50);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
        }
    }

	public synchronized void sellProcess()
	{
		if(ticketSold < 20)
		{
			ticketSold ++;
			System.out.println(Thread.currentThread().getName()+"卖出了第"+ticketSold+"张票。");
		}else
			{		
			ticketSold ++;
			System.out.println("票卖完了！");}
	}
}

public class station{
	public static int ticketSold = 0;
	public static void main(String [] args)
	{
		ticketSelling ticSell = new ticketSelling();
		Thread threadWindow1 = new Thread(ticSell,"窗口1");
		Thread threadWindow2 = new Thread (ticSell, "窗口2");
		Thread threadWindow3 = new Thread (ticSell, "窗口3");
		threadWindow1.start();
		threadWindow2.start();
		threadWindow3.start();
	}
}
