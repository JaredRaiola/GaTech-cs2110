Lab 12

A 2110 student was trying to write some assembly code and is stuck trying to figure out what is wrong with their code. Your job is to help them debug it!
Their code should be iterating over items in an array (located at memory location 0x6000) and either add or subtract them, depending on their index.
(numbers at even indices will be added, and numbers at odd indices will be subtracted). 
Therefore, the element at index 0 will be added, the element at index 1 will be subtracted, the element at index 2 will be added, etc untl you reach the end of the array. 
Once you have the result, save it at the memory location given by the label RESULT.

Ex: array: [47, 36, 25, 9, 14, 11, 42] will result in 
+47 - 36 + 25 - 9 + 14 - 11 + 42 = 72


Pseudocode:
addsubtract(int arr[], int length) {
	int currentState = 0; // 0 for add, 1 for subtract
	int result = 0;
	for (int i = 0; i < length; i++) {
		int element = arr[i];
		if (currentState) {
			result = result - element;
			currentState = 0;
		} else {
			result = result + element;
			currentState = 1;
		}
	}
	return result;
}

Check out the debugging guide on canvas to help! (Files -> Lecitation Resources -> Guides -> Debugging in Complx)
Show your TAs the fixed program working properly in order to get checked off early.