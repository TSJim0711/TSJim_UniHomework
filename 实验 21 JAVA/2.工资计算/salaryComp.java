import java.util.Scanner; 
 
abstract class employee{
	abstract void ComputeSalary();	
	int salary;
}

class manager extends employee
{
    public void ComputeSalary{
        salary = 4000;
        System.out.println(salary);
    }
}

public class salaryComp {
	
}
