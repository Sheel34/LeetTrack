class Solution {
    public int maxTwoEvents (int [] [] events) {

        int result = 0, maxOfCompletedEvents = 0;

	    Arrays.sort (events, (x ,y) -> x [0] - y [0]);

	    PriorityQueue <int []> inProgressQueue = new PriorityQueue <> ((x,y)-> x [1] - y [1]);

	    for (int [] currentEvent : events) {
		    while (!inProgressQueue.isEmpty () && inProgressQueue.peek () [1] < currentEvent[0])
			    maxOfCompletedEvents = Math.max (maxOfCompletedEvents, inProgressQueue.poll () [2]);

		result = Math.max (result, maxOfCompletedEvents + currentEvent [2]);
        
		inProgressQueue.offer (currentEvent);
	}
	return result;
    }
}