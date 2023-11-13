import java.util.Scanner; 
 
abstract class employee{
	public abstract void ComputeSalary();	
	int salary;
}

class manager extends employee
{
    public void ComputeSalary(){
        salary = 18000;
        System.out.println(salary);
    }
}

 class sales extends employee
{
    public void ComputeSalary(){
    	System.out.println("Salary Bounus: ");
    	Scanner bonus = new Scanner(System.in);
        salary = 2500 + bonus.nextInt();
        System.out.println(salary);
    }
}

 class worker extends employee
{
    public void ComputeSalary(){
    	Scanner workingDay = new Scanner(System.in);
        salary =  workingDay.nextInt()*68;
        System.out.println(salary);
    }
}

public class salaryComp {
	public static void main(String[] args) {
		manager mng = new manager();
		sales sale = new sales();
		worker wkr = new worker();
	for(int i =1; i==1;)
	{
		System.out.println("Employee to compute: [1] Manager [2] Salesman [3] Worker");
    	Scanner employeeClass = new Scanner(System.in);
    	if(employeeClass.toString()=="1")
    		mng.ComputeSalary();
    	if(employeeClass.toString()=="2")
    		sale.ComputeSalary();
    	if(employeeClass.toString()=="3")
    		wkr.ComputeSalary();
	}
