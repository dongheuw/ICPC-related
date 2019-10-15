import java.math.*;
import java.util.*;

public class i{
	public static void main(String[] args){
		Scanner cin = new Scanner(System.in);
		int i = 0;
		while (cin.hasNextBigInteger()){
			i ++;
			if (i != 1) System.out.println();
			BigInteger a = cin.nextBigInteger();
			BigInteger b = cin.nextBigInteger();
			System.out.println(a.gcd(b));
		}
	}
}
