#include <iostream>
#include <algorithm>

// 策略模式: 定义一系列算法，使他们可以相互转化
// 参与者:
// Strategy: (策略，定义所有支持算法的公共接口)
// ConcreteStrategy: (具体策略， 实现定义的接口)
// Context: (上下文， 用一个ConcreteStrategy对象配置，维护一个Stategy对象的引用，可以定义一个接口让strategy访问它的数据)

class Strategy
{
    public:
        virtual void sort(int *nums, int size) = 0;
};

class bubble : public Strategy
{
    public:
        virtual void sort(int *nums, int size) final
        {
            for(int i = 0; i < size; ++i)
            {
                for(int j = size - 1; j >= i; --j)
                {
                    if(nums[j] > nums[j + 1])
                        std::swap(nums[j], nums[j + 1]);
                }
            }
        }
};

class quicksort : public Strategy
{
    public:
        virtual void sort(int *nums, int size) final
        {
            quicksorting(nums, 0, size - 1);
        }
    private:
        void quicksorting(int *nums, int left, int right)
        {
            if(left < right)
            {
                int mid = quickpass(nums, left, right);
                quicksorting(nums, left, mid - 1);
                quicksorting(nums, mid + 1, right);
            }
        }
        int quickpass(int *nums, int left, int right)
        {
            int mid = left + (right - left) / 2;
            std::swap(nums[left], nums[mid]);
            int pivot = nums[left];
            while(left < right)
            {
                while(left < right && pivot < nums[right])
                    right--;
                if(left < right){
                    nums[left] = nums[right];
                    left++;
                }
                while(left < right && pivot > nums[left])
                {
                    left++;
                }
                if(left < right)
                {
                    nums[right] = nums[left];
                    right--;
                }
            }
            nums[left] = pivot;
            return left;
        }
};

class mergesorting : public Strategy
{
    public:
        virtual void sort(int *nums, int size) final
        {
            mergesort(nums, 0, size - 1);
        }
    private:
        void mergesort(int *nums, int left, int right)
        {
            if(left < right)
            {
                int mid = (left + right) / 2;
                mergesort(nums, left, mid);
                mergesort(nums, mid + 1, right);
                merge(nums, left, right, mid);
            }
        }
        void merge(int *nums, int left, int right, int mid)
        {
            int size = right - left + 1;
            int *tmp = new int[size];
            int i = left,j = mid + 1, k = 0;
            while(i <= mid && j <= right){
                if(nums[i] <= nums[j])
                    tmp[k++] = nums[i++];
                else
                    tmp[k++] = nums[j++];
            }
            while(i <= mid)
                tmp[k++] = nums[i++];
            while(j <= right)
                tmp[k++] = nums[j++];
            for(int t = 0; t < size; ++t){
                nums[left + t] = tmp[t];     
            }
        }
};

class Context
{
    public:
        Context(Strategy* strategy) : _strategy(strategy) 
        {
        }
        void trysort(int *nums, int size)
        {
            _strategy->sort(nums, size);
        }
    private:
        Strategy *_strategy;
};

int main()
{
    int nums1[] = {5,1,1,2,0,0};
    int nums2[] = {5,1,1,2,0,0};

    int size = sizeof(nums1) / sizeof(int);
    Context *con = new Context(new mergesorting());
    con->trysort(nums1, size);
    for(int i = 0; i < size; ++i){
        std::cout << nums1[i] << " ";
    }
    std::cout << std::endl;
    Context *con2 = new Context(new quicksort());
    con2->trysort(nums2, size);
    for(int i = 0; i < size; ++i){
        std::cout << nums2[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}