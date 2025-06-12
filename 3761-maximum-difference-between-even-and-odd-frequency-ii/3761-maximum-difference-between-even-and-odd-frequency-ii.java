class Solution {
    public int maxDifference(String s, int k) {
        int ans = Integer.MIN_VALUE;
        int n = s.length();

        for(char character_1 = '0'; character_1 <= '4'; character_1++ )
        {
            for(char character_2 = '0'; character_2 <= '4'; character_2++ )
            {
                if(character_1 == character_2) continue;

                int left_pointer = -1;
                int[] best_array = new int[4];
                Arrays.fill(best_array , Integer.MAX_VALUE);
                
                int count_character_1 = 0, count_character_2 =0;
                int prev_count_character_1 =0, prev_count_character_2 =0;

                for (int right_pointer = 0; right_pointer < n; right_pointer++)
                {
                    if(s.charAt(right_pointer) == character_1 ) count_character_1++;
                    else if(s.charAt(right_pointer) == character_2 ) count_character_2++;

                    while( right_pointer - left_pointer >= k && count_character_2 - prev_count_character_2 >= 2 )
                    {
                        int prev_parity = (prev_count_character_1 % 2)*2 + ( prev_count_character_2 % 2);
                        best_array[prev_parity] = Math.min(best_array[prev_parity] , prev_count_character_1 - prev_count_character_2);

                        left_pointer++;
                        if(s.charAt(left_pointer) == character_1 ) prev_count_character_1++;
                        else if(s.charAt(left_pointer) == character_2 ) prev_count_character_2++;
                        
                    }

                    int current_parity = (count_character_1 % 2)*2 + ( count_character_2 % 2);
                    int prev_desired_parity = current_parity ^ 2;
                    if(best_array[prev_desired_parity] != Integer.MAX_VALUE )
                    {
                        ans = Math.max(ans, count_character_1 - count_character_2 - best_array[prev_desired_parity]);
                    }
                }

            }
        }
        return ans; 
    }
}