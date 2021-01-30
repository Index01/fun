"""
    Sorting and sorting accessories
"""


class MergeSorter:
    def __init__(self, list_to_sort):
        """
        The usual, 1)split 2)sort 3)repeat 4)merge 
        """
        self.list_in = list_to_sort

    def split_sort_merge(self, lslice):
        if len(lslice) > 1:
            mid = len(lslice) // 2
            left = lslice[mid:]
            right = lslice[:mid]
            i, j, k = 0, 0, 0

            # print(f'l: {left}, r: {right}')
            self.split_sort_merge(left)
            self.split_sort_merge(right)

            while i < len(left) and j < len(right):
                if left[i] < right[j]:
                    lslice[k] = left[i]
                    i += 1
                else:
                    lslice[k] = right[j]
                    j += 1
                k += 1
            while i < len(left):
                lslice[k] = left[i]
                i += 1
                k += 1
            while j < len(right):
                lslice[k] = right[j]
                j += 1
                k += 1

    def sort(self):
        self.split_sort_merge(self.list_in)


class InsertionSorter:
    def __init__(self, list_to_sort):
        self.list_in = list_to_sort

    def sorted(self):
        """
        Insertion sort has the worst performance on lists that are already sorted, in reverse.
        Check for pre-sorted, check for presorted in reverse and reverse() if so, else do work.

        """
        local_in = self.list_in
        rev_in = self.list_in
        rev_in.reverse()
        if self.list_in == local_in.sort():
            return True
        #TODO:(tb) Calling builtin sort is no good for large input. Fixy.
        elif rev_in == local_in.sort():
            self.list_in.reverse()
            return True
        else:
            return False

    def sort(self):
        if self.sorted():
            return 
        else:
            for ind, val in enumerate(self.list_in):
                if ind == len(self.list_in) - 1:
                    break
                key = self.list_in[ind + 1]
                while key <= self.list_in[ind]:
                    if ind >= 1:
                        self.list_in[ind + 1] = self.list_in[ind]
                        ind -= 1
                    else:
                        self.list_in[ind] = key


class QuickSorter():
    def __init__(self, list_to_sort):
        self.list_in = list_to_sort

    def partition(self, left, right):
        piv_ind = left
        pivot = self.list_in[left]
        left = left + 1
        while 1:

            while left <= right and self.list_in[right] >= pivot:
                right = right - 1

            while left <= right and self.list_in[left] <= pivot:
                left = left + 1

            if left >= right:
                break
            self.list_in[left], self.list_in[right] = self.list_in[right], self.list_in[left]
        self.list_in[piv_ind], self.list_in[right] = self.list_in[right], self.list_in[piv_ind]

        return right 
        
    def quick_sort(self, left, right):
        if left < right:
            parted = self.partition(left, right)
            self.quick_sort(left, parted - 1)
            self.quick_sort(parted + 1, right)

    def sort(self):
        self.quick_sort(0, len(self.list_in) - 1)


class SortingHat:
    def __init__(self, list_to_sort):
        """
        SortingHat is initialized with a list.
        Sort based on a variety of algoriddims.
        """
        self.list_in = list_to_sort
        self.MergeSort = MergeSorter(self.list_in)
        self.InsertionSort = InsertionSorter(self.list_in)

    def sort(self):
        # TODO:tb pre-sorted check
        if len(self.list_in) >= 5:
            self.MergeSort.sort()
        else:
            self.InsertionSort.sort()

