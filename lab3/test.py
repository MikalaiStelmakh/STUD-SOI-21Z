from os import wait
import threading
from collections import deque
import random
from datetime import datetime
import time




def check_magazine(path):
    with open(path, "r") as f:
        return int(f.read())


def update_magazine(path, new_value):
    with open(path, 'w') as f:
        f.write(str(new_value))


class Buffer:
    def __init__(self, size, magazine_path) -> None:
        self.mutex = threading.Lock()
        self.size = size
        self.magazine_path = magazine_path
        self._items = self.get_items()
        self.full = threading.Condition(self.mutex)
        self.empty = threading.Condition(self.mutex)

    def get_items(self):
        with open(self.magazine_path, "r") as f:
            self._items = int(f.read())
            return self._items

    def enter(self, n):
        self.mutex.acquire()
        print("-----------------------------")
        print("Magazine: ", self.get_items())
        print(f"Thread {threading.get_ident()%10} is trying to insert {n} items.")
        if self.get_items() + n >= self.size:
            self.full.wait()
        print(f"Thread {threading.get_ident()%10} inserted {n} items.")
        update_magazine(self.magazine_path, self._items + n)
        print("Magazine: ", self.get_items())
        print("-----------------------------")
        if self.get_items() > 0:
            self.empty.notify()
        self.mutex.release()

    def remove(self, n):
        self.mutex.acquire()
        print("-----------------------------")
        print("Magazine: ", self.get_items())
        print(f"Thread {threading.get_ident()%10} is trying to consume {n} items.")
        if self.get_items() - n < 0:
            self.empty.wait()
        print(f"Thread {threading.get_ident()%10} consumed {n} items.")
        update_magazine(self.magazine_path, self._items - n)
        print("Magazine: ", self.get_items())
        print("-----------------------------")
        if self._items < self.size:
            self.full.notify()
        self.mutex.release()



def producer(min_n, max_n, log_path):
        while True:
            n = random.randint(min_n, max_n)
            with open(log_path, "a") as f:
                f.write(f"({datetime.now().strftime('%H:%M:%S')}) Trying to insert {n} items.\n")
            BUFFER.enter(n)
            with open(log_path, "a") as f:
                f.write(f"({datetime.now().strftime('%H:%M:%S')}) Inserted {n} items.\n")
            time.sleep(1)


def consumer(min_n, max_n, log_path):
        while True:
            n = random.randint(min_n, max_n)
            with open(log_path, "a") as f:
                f.write(f"({datetime.now().strftime('%H:%M:%S')}) Trying to consume {n} items.\n")
            BUFFER.remove(n)
            with open(log_path, "a") as f:
                f.write(f"({datetime.now().strftime('%H:%M:%S')}) Consumed {n} items.\n")
            time.sleep(1)





# def producer(min_n: int, max_n: int, log_path: str, magazine_capacity: int, magazine_path: str):
#     while True:
#         n = random.randint(min_n, max_n)
#         with open(log_path, "a") as f:
#             f.write(f"({datetime.now().strftime('%H:%M:%S')}) Trying to insert {n} items.\n")
#         MUTEX.acquire()
#         print(f"Thread {threading.get_ident()} is started")
#         current = check_magazine(magazine_path)
#         if magazine_capacity - current >= n:
#             update_magazine(magazine_path, current + n)
#             with open(log_path, "a") as f:
#                 f.write(f"({datetime.now().strftime('%H:%M:%S')}) Inserted {n} items.\n")
#         else:
#             with open(log_path, "a") as f:
#                 f.write(f"({datetime.now().strftime('%H:%M:%S')}) Not enough space for {n} items.\n")
#         print(f"Thread {threading.get_ident()} ended")
#         MUTEX.release()
#         time.sleep(5)


# def consumer(min_n: int, max_n: int, log_path: str, magazine_path: str):
#     while True:
#         n = random.randint(min_n, max_n)
#         with open(log_path, "a") as f:
#             f.write(f"({datetime.now().strftime('%H:%M:%S')}) Trying to consume {n} items.\n")
#         MUTEX.acquire()
#         print(f"Thread {threading.get_ident()} is started")
#         current = check_magazine(magazine_path)
#         if current >= n:
#             update_magazine(magazine_path, current - n)
#             with open(log_path, "a") as f:
#                 f.write(f"({datetime.now().strftime('%H:%M:%S')}) Consumed {n} items.\n")
#         else:
#             with open(log_path, "a") as f:
#                 f.write(f"({datetime.now().strftime('%H:%M:%S')}) No {n} items in magazine.\n")
#         print(f"Thread {threading.get_ident()} ended")
#         MUTEX.release()
#         time.sleep(5)


if __name__ == "__main__":
    # mutex.release()
    number_of_producers = 2
    number_of_consumers = 1
    magazine_capacity = 5
    magazine_path = "lab3/magazine.txt"
    min_n = 1
    max_n = 3
    # producer_log_path = "producer.txt"
    # for i in range(number_of_producers):
    #     log_path = f"producers_log/producer{i+1}.txt"
    #     with open(log_path, 'w') as f:
    #         f.write("")
    #     t = threading.Thread(target=producer, args=(1, 3, log_path, magazine_capacity, magazine_path))
    #     t.start()
    # for i in range(number_of_consumers):
    #     log_path = f"consumers_log/consumer{i+1}.txt"
    #     with open(log_path, 'w') as f:
    #         f.write("")
    #     t = threading.Thread(target=consumer, args=(1, 3, log_path, magazine_path))
    #     t.start()
    BUFFER = Buffer(magazine_capacity, magazine_path)
    for i in range(number_of_producers):
        log_path = f"lab3/producer{i+1}.txt"
        t = threading.Thread(target=producer, args=(min_n, max_n, log_path))
        t.start()
    for i in range(number_of_consumers):
        log_path = f"lab3/consumer{i+1}.txt"
        t = threading.Thread(target=consumer, args=(min_n, max_n, log_path))
        t.start()


    # check_magazine("magazine.txt")
