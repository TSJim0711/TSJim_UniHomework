import java.util.Scanner; 
import java.util.InputMismatchException;
 
abstract class employee{
	public abstract void ComputeSalary();	
	int salary;
}

class manager extends employee
{
    public void ComputeSalary(){
        salary = 18000;
        System.out.println("Salary: "+ salary);
    }
}

 class sales extends employee
{
    public void ComputeSalary(){
    	System.out.println("Salary Bounus: ");
    	Scanner bonus = new Scanner(System.in);
        salary = 2500 + bonus.nextInt();
        System.out.println("Salary: "+ salary);
    }
}

 class worker extends employee
{
    public void ComputeSalary(){
    	System.out.println("Working day(s): ");
    	Scanner workingDay = new Scanner(System.in);
        salary =  workingDay.nextInt()*68;
        System.out.println("Salary: "+ salary);
    }
}

public class salaryComp {
	public static void main(String[] args) {
		manager mng = new manager();
		sales sale = new sales();
		worker wkr = new worker();
		Scanner userInput;
		int employeeClass;
		do
		{
			System.out.println("Employee to compute: [1] Manager [2] Salesman [3] Worker [4] Exit;");
			userInput = new Scanner(System.in);
			try {employeeClass = userInput.nextInt();}
			catch(InputMismatchException e )
			{
				System.out.println("Numbers only.");
				employeeClass=0;
			}
	    	if(employeeClass==1)
	    		mng.ComputeSalary();
	    	else if(employeeClass==2)
	    		sale.ComputeSalary();
	    	else if(employeeClass==3)
	    		wkr.ComputeSalary();
		}while (employeeClass<=3);
	}
}
