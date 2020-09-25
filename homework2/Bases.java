/**
 * CS 2110 Spring 2019 HW2
 * Part 2 - Coding with bases
 *
 * @author Jared Raiola
 *
 * Global rules for this file:
 * - You may not use more than 2 conditionals per method. Conditionals are
 *   if-statements, else-if statements, or ternary expressions. The else block
 *   associated with an if-statement does not count toward this sum. Boolean
 *   expressions outside of if-statements, else-if statements and ternary
 *   expressions do not count toward this sum either.
 * - You may not use more than 2 looping constructs per method. Looping
 *   constructs include for loops, while loops and do-while loops.
 * - You may not use nested loops.
 * - You may not declare any file-level variables.
 * - You may not declare any objects, other than String in select methods.
 * - You may not use switch statements.
 * - You may not use the unsigned right shift operator (>>>)
 * - You may not write any helper methods, or call any other method from this or
 *   another file to implement any method.
 * - The only Java API methods you are allowed to invoke are:
 *     String.length()
 *     String.charAt()
 * - You may not invoke the above methods from string literals.
 *     Example: "12345".length()
 * - When concatenating numbers with Strings, you may only do so if the number
 *   is a single digit.
 *
 * Method-specific rules for this file:
 * - You may not use multiplication, division or modulus in any method, EXCEPT
 *   decimalStringToInt.
 * - You may declare exactly one String variable each in intToBinaryString, intToOctalString,
 *   and intToHexString.
 */
public class Bases
{
    /**
     * Convert a string containing ASCII characters (in binary) to an int.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid binary numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: binaryStringToInt("111"); // => 7
     */
    public static int binaryStringToInt(String binary)
    {
    	int binarySum = 0;
    	for (int index = 0; index < binary.length(); index++) {
    		//loops through, checks to see if the char is a 1, if it is
    		//then add to the sum
    		if (binary.charAt(binary.length() - index - 1) == '1') {
    			binarySum = binarySum + (0x1 << index);
    		}
    	}
        return binarySum;
    }

    /**
     * Convert a string containing ASCII characters (in decimal) to an int.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid decimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: decimalStringToInt("123"); // => 123
     *
     * You may use multiplication, division, and modulus in this method.
     */
    public static int decimalStringToInt(String decimal)
    {
    	int decimalSum = 0;
    	//indicates 1's place as beginning
    	int decimalPlace = 1;
    	for (int index = 1; index < decimal.length() + 1; index++) {
    		//loops through, finds char at the index (back to front), subtracts to 0
    		//multiplies it by the decimal place (starts at 1's place)
    		decimalSum = decimalSum + ((decimal.charAt(decimal.length() - index) - 0x30) * decimalPlace);
    		//increases decimal places (10's -> 100's ...)
    		decimalPlace *= 10;
    	}
        return decimalSum;
    }

    /**
     * Convert a string containing ASCII characters (in octal) to an int.
     * The input string will only contain the numbers 0-7. You do not need to handle
     * negative numbers. The strings we will pass in will be valid octal numbers, and
     * able to fit in a 32-bit signed integer.
     *
     * Example: octalStringToInt("17"); // => 15
     */
    public static int octalStringToInt(String octal)
    {
    	int octalSum = 0;
    	int octalPlace = 0;
    	for (int index = 1; index < octal.length() + 1; index++) {
    		octalSum += (octal.charAt(octal.length() - index) - 48) << octalPlace;
    		octalPlace = octalPlace + 3;
    	}
        return octalSum;
    }

    /**
     * Convert a string containing ASCII characters (in hex) to an int.
     * The input string will only contain numbers and uppercase letters A-F.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid hexadecimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: hexStringToInt("A6"); // => 166
     */
    public static int hexStringToInt(String hex)
    {
    	int hexSum = 0;
    	for (int index = 0; index < hex.length(); index++) {
    		if (hex.charAt(hex.length() - index - 1) < 0x41) {
    			hexSum = hexSum + 
    			((hex.charAt(hex.length() - index - 1) - 0x30) 
    				<< (index << 2));
    		} else {
    			hexSum = hexSum + 
    			((hex.charAt(hex.length() - index - 1) - 0x41 + 0xA) 
    				<< (index << 2));
    		}
    	}
        return hexSum;
    }

    /**
     * Convert a int into a String containing ASCII characters (in binary).
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters necessary to
     * represent the number that was passed in.
     *
     * Example: intToBinaryString(7); // => "111"
     *
     * You may declare one String variable in this method.
     */
    public static String intToBinaryString(int binary)
    {
    	String binaryString = "";
    	do  {
    		binaryString = (((binary & 0x1) != 0) ? "1" : "0") + binaryString;

    		binary >>= 1;
    	} while (binary != 0 && binary != ~0x0);
        return binaryString;
    }

    /**
     * Convert a int into a String containing ASCII characters (in octal).
     * The output string should only contain numbrs 0-7.
     * Tou do not need to handle negative numbers.
     * The String returned should contain the minimum numbers of characters necessary to
     * represent the number that was passed in.
     *
     * Example: intToOctalString(17); // => "21"
     */
    public static String intToOctalString(int octal)
    {
        String octalString = "";
    	do {
    		octalString = ((octal & 0x7) + octalString);

    		octal >>= 3;
    	} while (octal != 0 && octal != ~0x0);
        return octalString;
    }

    /**
     * Convert a int into a String containing ASCII characters (in hexadecimal).
     * The output string should only contain numbers and uppercase letters A-F.
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters necessary to
     * represent the number that was passed in.
     *
     * Example: intToHexString(166); // => "A6"
     *
     * You may declare one String variable in this method.
     */
    public static String intToHexString(int hex)
    {
    	String hexString = "";
    	long mask = 0xF;
    	int count = 0;
    	while (mask <= hex) {
    		count++;
    		mask <<= 4;
    	}
    	while (mask > 0) {
    		int placeholder = (int) (mask & hex) >> (count << 2);
    		mask >>= 4;
    		count--;
    		if (!(placeholder >= 0xA)) {
    			hexString = hexString + (char) (placeholder + 0x30);
    		} else {
    			hexString = hexString + (char) (placeholder + 0x41 - 0xA);
    		}
    	}
        return hexString;
    }
}
