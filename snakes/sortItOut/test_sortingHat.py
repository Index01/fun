
import pytest
from collections import deque
from sortingHat import SortingHat, MergeSorter, InsertionSorter, QuickSorter


sorted_list = [1,2,3,4,5,6,7]

def unsort_list(listy):
    unsorted_list = deque(sorted_list)
    unsorted_list.rotate(-3)
    return list(unsorted_list)
    

@pytest.fixture
def fixture_sorting_hat():
    sorta = SortingHat(unsort_list(sorted_list))
    yield sorta
    setattr(sorta, "list_in", unsort_list(sorted_list))

@pytest.fixture
def fixture_merge_sorter():
    sorta = MergeSorter(unsort_list(sorted_list))
    yield sorta
    setattr(sorta, "list_in", unsort_list(sorted_list))

@pytest.fixture
def fixture_insertion_sorter():
    sorta = InsertionSorter(unsort_list(sorted_list))
    yield sorta
    setattr(sorta, "list_in", unsort_list(sorted_list))

@pytest.fixture
def fixture_quick_sorter():
    sorta = QuickSorter(unsort_list(sorted_list))
    yield sorta
    setattr(sorta, "list_in", unsort_list(sorted_list))


def test_sorting_hat(fixture_sorting_hat):
    fixture_sorting_hat.sort()
    assert fixture_sorting_hat.list_in == sorted_list

def test_merge_sort(fixture_merge_sorter):
    fixture_merge_sorter.sort()
    assert fixture_merge_sorter.list_in == sorted_list

def test_insertion_sort(fixture_insertion_sorter):
    fixture_insertion_sorter.sort()
    assert fixture_insertion_sorter.list_in == sorted_list

def test_quick_sort(fixture_quick_sorter):
    fixture_quick_sorter.sort()
    assert fixture_quick_sorter.list_in == sorted_list

