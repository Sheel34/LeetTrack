class Solution {
    public String robotWithString(String s) {
        Stack<Character> stack = new Stack<>();
    	int frq[] = new int [26];
    	for(char i : s.toCharArray())
    	{
    		frq[i-'a']++;
    	}
    	int ind = 0;
    	int start = 0;
    	StringBuffer sb = new StringBuffer();
    	while(ind < s.length())
    	{
    		char ch = (char)(125);
    		if(!stack.isEmpty())
    		{
    			ch = stack.peek();
    		}
    		char temp = (char)(126);
    		for(int i = start; i < 26; i++)
    		{
    			if(frq[i] != 0)
    			{
    				temp = (char)(i + 'a');
    				start = i;
    				break;
    			}
    		}
    		if(!stack.isEmpty() && ch <= temp)
    		{
    			sb.append(stack.pop());
    		}
    		else
    		{
    			for(; ind < s.length(); ind++)
    			{
    				frq[s.charAt(ind)-'a']--;
    				if(temp == s.charAt(ind))
    				{
    					sb.append(temp);
    					ind++;
    					break;
    				}
    				stack.push(s.charAt(ind));
    			}
    			
    		}
    	}
    	while(!stack.isEmpty())
    	{
    		sb.append(stack.pop());
    	}
        return sb.toString();
    }
}