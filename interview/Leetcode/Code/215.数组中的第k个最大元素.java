class Solution {
    
    public static void main(String[] args){
        int[] arr = {3,2,3,1,2,4,5,5,3};
        int i = findKthLargest(arr,4);

        int j = 0;
        j ++;
    }


    public static int findKthLargest(int[] nums, int k) {
        return quickSort(nums, 0, nums.length - 1, k);
    }

    public static int quickSort(int[] arr, int l, int r, int k) {
        if (l >= r) {
            return arr[l];
        }

        int compareValue = arr[l];

        int i = l;
        int j = r + 1;

        while (i < j) {
            do i++; while(arr[i] >= compareValue);
            do j--; while(arr[j] < compareValue);
            if(i < j) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        if(j == k-1) {
            return arr[l];
        } else if (j < k-1) {
            return quickSort(arr, j + 1, r, k);
        } else {
            return quickSort(arr, l, j, k);
        }
    }
}